#ifndef jagged_array_h
#define jagged_array_h
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

template<class T> class JaggedArray{
public:
    //constructor
    JaggedArray(){create();}
    JaggedArray(int n){create(n);}
    JaggedArray(const JaggedArray& a){copy(a);}
    JaggedArray& operator=(const JaggedArray& j);
    ~JaggedArray(){destroy();}
    
    //accessors
    int numElements() const{return num_elements;}
    int numBins() const{return num_bins;}
    int numElementsInBin (int bin);
    T getElement(int slot, int bin);
    bool isPacked();
    
    //modifiers;
    void addElement(int num,const T& element);
    void removeElement(int bin, int slot);
    void clear();
    void unpack();
    void pack();
    
    //print function
    void print();
private:
    //private member functions
    void create();
    void create(int n);
    void copy(const JaggedArray<T>& j);
    void destroy();
    void print_unpacked();
    
    //private member variables
    int num_elements;
    int num_bins;
    int* counts;
    T** unpacked_values;
    int* offsets;
    T* packed_values;
    bool packed;
};


//create a constructor;
template<class T> void JaggedArray<T>::create(){
    num_elements = 0;
    num_bins = 0;
    counts = NULL;
    unpacked_values = NULL;
    offsets = NULL;
    packed_values = NULL;
    packed = false;
}

//create a constructor with size n
template<class T> void JaggedArray<T>::create(int n){
    num_elements = 0;
    num_bins = n;
    counts = new int[n];
    for(int i=0; i<n;i++){
        counts[i] = 0;
    }
    unpacked_values = new T*[n];
    for(int i=0; i< n;i++){
        unpacked_values[i] = nullptr;
    }
    offsets = nullptr;
    packed_values = nullptr;
    packed = false;
}

//function for destructor
template<class T> void JaggedArray<T>::destroy(){
    //if it is unpacked
    if(this->packed == false){
        delete[] counts;
        for(unsigned int i=0; i<num_bins;i++){
            delete[] unpacked_values[i];
        }
        delete[] unpacked_values;
    }
    //if it is packed
    else if(this->packed ==true){
        delete[] packed_values;
        delete[] offsets;
    }
}

//function for copy constructor
template<class T> void JaggedArray<T>::copy(const JaggedArray<T>& a){
    this->num_elements = a.num_elements;
    this->num_bins = a.num_bins;
    this->packed = a.packed;
    //if it is unpacked copy counts and unpacked vlaues
    if(packed == false){
        this->counts = new int[num_bins];
        this->unpacked_values = new T*[num_bins];
        for(int i=0; i<num_bins;i++){
            this->counts[i] = a.counts[i];
            this->unpacked_values[i] = new T[counts[i]];
            for(int j=0; j<counts[i];j++){
                this->unpacked_values[i][j] = a.unpacked_values[i][j];
            }
        }
    }
    //if it is packed copy offsets and packed values
    else if(packed == true){
        this->offsets = new int[num_bins];
        this->packed_values = new T[num_elements];
        for(int i=0; i<num_bins;i++){
            this->offsets[i] = a.offsets[i];
        }
        for(int j=0; j<num_elements;j++){
            this->packed_values[j] = a.packed_values[j];
        }
    }
}

//implementation of operator =
template<class T>JaggedArray<T>& JaggedArray<T>::operator=(const JaggedArray<T>& j){
    //if they are not the same jagged array
    if(this!=&j){
        destroy();
        this->copy(j);
    }
    return *this;
}

//function for number of elements in Bin
template<class T> int JaggedArray<T>::numElementsInBin (int bin){
    if(!packed){
        return counts[bin];
    }
    else{
        if(bin==num_bins-1){
            return num_elements -offsets[bin];
        }
        return offsets[bin+1]-offsets[bin];
    }
}

//gets the element in that bin number, slot number
template<class T> T JaggedArray<T>::getElement(int bin, int slot){
    //error checking for invalid bin number, exit(1) causes memory leaks.
    //(confirmed by prof. Plum to just ignore it)
    if(bin>=num_bins||bin<0){
        std::cerr<<"Invalid Bin Number"<<std::endl;
        exit(1);
    }
    //if it is unpacked
    if(!packed){
        //error checking for invalid slot number;
        if(counts[bin]==0||slot<0||slot>=counts[bin]){
            std::cerr<<"Invalid Slot Number"<<std::endl;
            exit(1);
        }
        return unpacked_values[bin][slot];
    }
    //if it is packed
    else{
        int bin_num_elem;
        //when the it is the last bin
        if(bin == num_bins-1){
            bin_num_elem = num_elements-offsets[bin];
        }
        //when it is not the last bin
        else{
            bin_num_elem = offsets[bin+1]-offsets[bin];
        }
        //error checking for invalid slot number
        if(bin_num_elem==0 || slot>=bin_num_elem || slot<0){
            std::cerr<<"Invalid Slot Number"<<std::endl;
            exit(1);
        }
        return *(packed_values+offsets[bin]+slot);
    }
}

//function to check if the class is packed
template<class T> bool JaggedArray<T>::isPacked(){
    return packed;
}

//function for adding element in that bin number
template<class T> void JaggedArray<T>::addElement(int num,const T& element){
    //error checkings
    if(packed){
        std::cerr<<"Can't make changes when it is packed"<<std::endl;
        return;
    }
    if(num <0){
        std::cerr<<"Invalid Bin number"<<std::endl;
        return;
    }
    //if that bin number is greater than current bin create a bigger bin
    if(num>num_bins-1){
        //create new counts and copy value, add element
        //then delete old counts
        int* new_counts = new int[num+1];
        for(int i=0; i<num_bins;i++){
            new_counts[i] = counts[i];
        }
        delete[] counts;
        counts = new_counts;
        
        //create new unpacked_values and copy value,add element
        //then delete old unpacked values
        T**new_values = new T*[num+1];
        for(int i=0;i<num+1;i++){
            new_values[i] = nullptr;
        }
        for(int i=0; i<num_bins;i++){
            new_values[i] = new T[counts[i]];
            for(int j=0; j<counts[i];j++){
                new_values[i][j] = unpacked_values[i][j];
                delete[] unpacked_values[i];
            }
        }
        new_values[num] = new T[1];
        new_values[num][0] = element;
        delete[] unpacked_values;
        unpacked_values  = new_values;
        num_bins=num+1;
    }
    //if that bin number already exists
    else{
        if(counts[num]==0){
            unpacked_values[num] = new T[1];
            unpacked_values[num][0] = element;
        }
        else{
            T* new_values = new T[counts[num]+1];
            for(int i=0; i<counts[num];i++){
                new_values[i] = unpacked_values[num][i];
            }
            new_values[counts[num]] = element;
            delete[] unpacked_values[num];
            unpacked_values[num] = new_values;
        }
    }
    counts[num]+=1;
    num_elements+=1;
}

//function for removing element in the bin and slot
template<class T> void JaggedArray<T>::removeElement(int bin, int slot){
    //error checking
    if(packed){
        std::cerr<<"Can't make changes when it is packed"<<std::endl;
        return;
    }
    if(bin<0||bin>=num_bins){
        std::cerr<<"Invalid Bin number"<<std::endl;
        return;
    }
    if(slot<0||slot>=counts[bin]){
        std::cerr<<"Invalid Slot number"<<std::endl;
        return;
    }
    
    //if that bin has 1 element delete the array in unpacked[bin] and set null
    if(counts[bin]==1){
        delete[] unpacked_values[bin];
        unpacked_values[bin] = nullptr;
    }
    
    //if it has more than 1 element in the array create one smaller array and
    //copy value
    else{
        T* new_unpacked =new T[counts[bin]-1];
        int k=0;
        for(int i=0;i<counts[bin];i++){
            if(i==slot){continue;}
            new_unpacked[k]=unpacked_values[bin][i];
            k++;
        }
        delete[] unpacked_values[bin];
        unpacked_values[bin] = new_unpacked;
    }
    counts[bin]-=1;
    num_elements-=1;
}

//function for clearing all the elements in bin
template<class T> void JaggedArray<T>::clear(){
    //error checking for if it is packed
    if(packed){
        std::cerr<<"Can't make changes when it is packed"<<std::endl;
        return;
    }
    //set counts value to 0 and unpacked values to null ptr
    for(int i=0;i<num_bins;i++){
        counts[i] = 0;
        delete[] unpacked_values[i];
        unpacked_values[i] = nullptr;
    }
    num_elements = 0;
}

//function for changing the jagged array into packed mode
template<class T> void JaggedArray<T>::pack(){
    //if it is already packed return
    if(packed == true){return;}
    
    //create array in heap for offsets and packed values
    offsets = new int[num_bins];
    packed_values = new T[num_elements];
    for(int i=0;i<num_bins;i++){
        offsets[i] = 0;
    }
    //put values for offsets.
    for(int i=0;i<num_bins-1;i++){
        offsets[i+1]=counts[i]+offsets[i];
    }
    
    //puts values for packed_values
    int k=0;
    for(int i=0;i<num_bins;i++){
        for(int j=0; j<counts[i];j++){
            packed_values[k]=unpacked_values[i][j];
            k++;
        }
    }
    //delete unpacked values and counts
    delete[] counts;
    for(int i=0;i<num_bins;i++){
        delete[] unpacked_values[i];
    }
    delete[] unpacked_values;
    packed = true;
}

//function for changing the jagged array into unpacked mode.
template<class T> void JaggedArray<T>::unpack(){
    //if it is already unpacked do nothing
    if(!packed){return;}
    
    //create array in heap for counts and unpacked values
    counts = new int[num_bins];
    unpacked_values = new T*[num_bins];
    //initialize default values for counts and unpacked values
    for(int i=0;i<num_bins;i++){
        counts[i] = 0;
    }
    for(int i=0;i<num_bins;i++){
        unpacked_values[i] = nullptr;
    }
    
    //set values for counts
    for(int i=0; i<num_bins-1;i++){
        counts[i] = offsets[i+1]-offsets[i];
    }
    counts[num_bins-1] = num_elements - offsets[num_bins-1];
    
    //sets values for unpacked values
    int k=0;
    for(int i=0;i<num_bins;i++){
        if(counts[i]==0){continue;}
        unpacked_values[i] = new T[counts[i]];
        for(int j=0;j<counts[i];j++){
            unpacked_values[i][j] = packed_values[k];
            k++;
        }
    }
    
    //delete offsets and packed values
    delete[] offsets;
    delete[] packed_values;
    packed = false;
}


//print helper function for redundant parts.
template <class T>void JaggedArray<T>::print_unpacked(){
    std::cout<<"packed JaggedArray"<<std::endl;
    std::cout<<"  num_bins: "<<num_bins<<std::endl;
    std::cout<<"  num_elements: "<<num_elements<<std::endl;
    std::cout<<"  offsets: ";
    for(int i=0; i< num_bins;i++){
        std::cout<<" "<<offsets[i];
    }
    std::cout<<std::endl;
    std::cout<<"  values:  ";
    for(int i=0; i< num_elements;i++){
        std::cout<<" "<<packed_values[i];
    }
    std::cout<<"\n"<<std::endl;
}


//function for print for templated types besides string
template<class T> void JaggedArray<T>::print(){
    //if it is unpacked
    if(!packed){
        std::cout<<"unpacked JaggedArray"<<std::endl;
        std::cout<<"  num_bins: "<<num_bins<<std::endl;
        std::cout<<"  num_elements: "<<num_elements<<std::endl;
        std::cout<<"  counts: ";
        
        //gets max number of elements in array
        int max=0;
        for(int i=0; i< num_bins;i++){
            std::cout<<" "<<counts[i];
            if(counts[i] > max){
                max = counts[i];
            }
        }
        std::cout<<std::endl;
        
        //prints unpacked values
        std::cout<<"  values: ";
        for(int i=0; i<max;i++){
            for(int j=0;j<num_bins;j++){
                if(i>=counts[j]){
                    std::cout<<"  ";
                }
                else{
                    std::cout<<" "<<unpacked_values[j][i];
                }
            }
            std::cout<<std::endl;
            std::cout<<"          ";
        }
        std::cout<<"\n"<<std::endl;
    }
    //if it is packed
    else{
        print_unpacked();
    }
}

//print function for std::string types
template<> void JaggedArray<std::string>::print(){
    if(!packed){
        std::cout<<"unpacked JaggedArray"<<std::endl;
        std::cout<<"  num_bins: "<<num_bins<<std::endl;
        std::cout<<"  num_elements: "<<num_elements<<std::endl;
        std::cout<<"  counts:";
        //get max_length of string
        int max_length = 0;
        for(int i=0; i<num_bins;i++){
            for(int j=0; j<counts[i];j++){
                if(max_length < unpacked_values[i][j].size()){
                    max_length = unpacked_values[i][j].size();
                }
            }
        }
        
        //get max number of elements and print counts
        int max=0;
        for(int i=0; i< num_bins;i++){
            std::cout<<" "<<std::setw(max_length)<<counts[i];
            if(counts[i] > max){
                max = counts[i];
            }
        }
        std::cout<<std::endl;
        
        //print unpacked values
        std::cout<<"  values:";
        for(int i=0; i<max;i++){
            for(int j=0;j<num_bins;j++){
                if(i>=counts[j]){
                    std::cout<<std::string(max_length+1,' ');
                }
                else{
                    std::cout<<" "<<std::setw(max_length)
                    <<unpacked_values[j][i];
                }
            }
            std::cout<<std::endl;
            std::cout<<"         ";
        }
        std::cout<<"\n"<<std::endl;
    }
    //if it is packed
    else{
        print_unpacked();
    }
}


#endif
