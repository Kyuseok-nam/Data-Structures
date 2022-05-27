#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();

//print out each key as many times as its values
template <class T>
void map_sort(std::map<T,int> &mp, std::ostream &ostr, int &output_count) {
    output_count = 0;
    typename std::map<T,int>::iterator itr = mp.begin();
    for (;itr!=mp.end();itr++){
        for(int i=0;i<itr->second;i++){
            ostr<<itr->first<<std::endl;
            output_count++;
        }
    }
}


//find the key with largest value
template <class T>
void set_mode(std::map<T,int> &mp, std::ostream &ostr, int &output_count) {
    typename std::map<T,int>::iterator itr = mp.begin();
    typename std::map<T,int>::iterator ret;
    int best = 0;
    for(;itr!=mp.end();itr++){
        if(itr->second > best){
            best = itr->second;
            ret = itr;
        }
    }
    ostr<<ret->first<<std::endl;
    output_count = 1;
}

//compare by iterating through and find the smallest difference
void map_closest_pair(std::map<int,int> &mp, std::ostream &ostr, int &output_count) {
    assert(mp.size()>=2);
    output_count = 2;
    int best = 10000000;
    int diff;
    int prev=-1;
    int current=-1;
    int answer1,answer2;
    std::map<int,int>::iterator itr = mp.begin();
    bool start = true;
    for(;itr!=mp.end();itr++){
        for(int j=0; j<itr->second;j++){
            if(start){
                prev = itr->first;
                start = false;
                continue;
            }
            current = itr->first;
            diff = current - prev;
            if(diff<best){
                best = diff;
                answer1 = prev;
                answer2 = current;
            }
            prev = current;
        }
        
    }
    ostr<<answer1<<std::endl;
    ostr<<answer2<<std::endl;
}

//print out by iterating through each key as many times as its value
template <class T>
void map_first_sorted(std::map<T,int> &mp, std::ostream &ostr, int &output_count, int optional_arg) {
    typename std::map<T,int>::iterator itr = mp.begin();
    int i=0;
    for(;itr!=mp.end();itr++){
        for(int j=0;j<itr->second;j++){
            if(i==optional_arg){
                return;
            }
            ostr<<itr->first<<std::endl;
            i++;
            output_count++;
        }
    }
}

//compare two words by iterating through each character and then increasing til
//it doesn't match, then print out the longest one.
void set_longest_substring(std::map<std::string,int> &mp, std::ostream &ostr, int &output_count) {
    
    std::map<std::string,int>::iterator itr = mp.begin();
    std::string answer = itr->first;
    bool duplicate = false;
    //find the longest key duplicate
    for(;itr!=mp.end();itr++){
        if(itr->second > 1){
            if(!duplicate){
                answer = itr->first;
            }
            duplicate = true;
            if(itr->first.size() > answer.size()){
                answer = itr->first;
            }
        }
    }
    if(duplicate){
        output_count = 1;
        ostr<<answer<<std::endl;
        return;
    }
    //if duplicate doesn't exist
    int best = 0;
    std::string substring;
    itr = mp.begin();
    std::map<std::string,int>::iterator tmp;
    std::map<std::string,int>::iterator itr2;
    for(unsigned int i=0; i<mp.size()-1;i++,itr++){
        tmp = itr;
        tmp++;
        itr2 = tmp;
        for(;itr2!=mp.end();itr2++){
            for(unsigned int k=0;k<itr->first.size();k++){
                for(unsigned int l=0;l<itr2->first.size();l++){
                    int q=0;
                    std::string tmp_s = "";
                    int match = 0;
                    while( (k+q) < itr->first.size() && (l+q) < itr2->first.size() ) {
                        if(itr->first[k+q] == itr2->first[l+q]){
                            tmp_s+=itr->first[k+q];
                            match++;
                            if(match>best){
                                best = match;
                                substring = tmp_s;
                            }
                        }
                        else{
                            break;
                        }
                        q++;
                    }
                }
            }
        }
    }
    output_count = 1;
    ostr<<substring<<std::endl;
    return;
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {
    
  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  // std::map<std::string,int> mp;

    if (type == "string") {
        std::set<std::string> st;
        std::map<std::string,int> mp;
        std::string s;
        input_count = 0;
        if(operation == "sort"){
            // load the data into a map of strings
            while(istr>>s){
                mp[s]++;
                input_count++;
            }
            map_sort(mp,ostr,output_count);
        }
        else if (operation == "remove_duplicates"){
            std::set<std::string>::iterator itr;
            std::string s;
            // load the data into  and set of strings
            while(istr>>s){
                //if key doesn't exist, print and insert
                input_count++;
                itr = st.find(s);
                if(itr==st.end()||st.size()==0){
                    st.insert(s);
                    ostr<<s<<std::endl;
                    output_count++;
                }
            }
        }
        else if (operation == "mode"){
            // load the data into a map of strings
            while(istr>>s){
                mp[s]++;
                input_count++;
            }
            set_mode(mp,ostr,output_count);
        }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted"){
            // load the data into a map of strings
            while(istr>>s){
                input_count++;
                mp[s]++;
            }
            map_first_sorted(mp,ostr,output_count,optional_arg);
        }
        else if (operation == "longest_substring") {
            // load the data into a map of strings
            while(istr>>s){
                input_count++;
                mp[s]++;
            }
            set_longest_substring (mp,ostr,output_count);
        }
        else {
            std::cerr << "Error: Unknown operation: " << operation << std::endl;
            usage();
            exit(0);
        }
    }

    else {
        assert (type == "integer");
        std::set<int> st;
        std::map<int,int> mp;
        input_count=0;
        int v;
        if(operation == "sort"){
            // load the data into a map of strings and set of strings
            while(istr>>v){
                mp[v]++;
                input_count++;
            }
            map_sort(mp,ostr,output_count);
        }
        else if (operation == "remove_duplicates"){
            std::set<int>::iterator itr;
            // load the data into a set of ints
            while(istr>>v){
                input_count++;
                itr = st.find(v);
                //if key don't exist print and insert
                if(itr==st.end()){
                    st.insert(v);
                    ostr<<v<<std::endl;
                    output_count++;
                }
            }
        }
        else if (operation == "mode"){
            // load the data into a map of ints
            while(istr>>v){
                mp[v]++;
                input_count++;
            }
            set_mode(mp,ostr,output_count);
        }
        else if (operation == "closest_pair"){
            // load the data into a map of ints
            while(istr>>v){
                mp[v]++;
                input_count++;
            }
            map_closest_pair(mp,ostr,output_count);
        }
        else if (operation == "first_sorted"){
            // load the data into a map of ints
            while(istr>>v){
                mp[v]++;
                input_count++;
            }
            map_first_sorted(mp,ostr,output_count,optional_arg);
        }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
