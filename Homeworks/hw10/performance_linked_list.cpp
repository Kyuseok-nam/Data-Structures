#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lis, std::ostream &ostr, int &output_count) {
    // use the list sort algorithm
    lis.sort();
    output_count = lis.size();
    typename std::list<T>::const_iterator itr = lis.begin();
    for (;itr!=lis.end();itr++)
        ostr << *itr << "\n";
}


template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    typename std::list<T>::const_iterator itr = lst.begin();
    for(;itr!=lst.end();itr++){
        bool dup = false;
        typename std::list<T>::const_iterator itr1 = lst.begin();
        typename std::list<T>::const_iterator tmp = itr;
        tmp--;
        for(;itr1!=tmp;itr1++){
            if(itr!=lst.begin()&&*itr == *itr1){
                dup = true;
                break;
            }
        }
        if(!dup){
            ostr<<*itr<<"\n";
            output_count++;
        }
    }
}

template <class T>
void list_mode(std::list<T> &lis, std::ostream &ostr, int &output_count) {
    // use the list sort algorithm
    
    lis.sort();
    int current_count = 1;
    T mode;
    int mode_count = 0;
    // keep track of two iterators into the structure
    typename std::list<T>::iterator current = lis.begin();
    ++current;
    typename std::list<T>::iterator previous = lis.begin();
    for (; current != lis.end(); ++current, ++previous) {
        if (*current == *previous) {
            // if they are the same element increment the count
            current_count++;
        }
        else if (current_count >= mode_count) {
            // found a new mode!
            mode = *previous;
            mode_count = current_count;
            current_count = 1;
        }
        else {
            current_count = 1;
        }
    }
    if (current_count >= mode_count) {
        // last entry is a new mode!
        mode = *previous;
        mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    ostr << mode << "\n";
}


void list_closest_pair(std::list<int> &lis, std::ostream &ostr, int &output_count) {
    assert (lis.size() >= 2);
    // use the list sort algorithm
    lis.sort();
    int best;
    std::list<int>::iterator current = lis.begin();
    std::list<int>::iterator next = current;
    std::list<int>::iterator result;
    next++;
    // the two elements with closest value must be next to each other in sorted order
    for (unsigned int i=0; i < lis.size()-1; i++) {
        int diff = (*next) - (*current);
        if (current ==lis.begin() || diff < best) {
            best = diff;
            result = current;
        }
        current++;
        next++;
    }
    // print the two elements
    output_count = 2;
    ostr << *result << "\n";
    result++;
    ostr << *result << "\n";
}


template <class T>
void list_first_sorted(std::list<T> &lis, std::ostream &ostr, int &output_count, int optional_arg) {
    assert (optional_arg >= 1);
    assert ((int)lis.size() >= optional_arg);
    // use the list sort algorithm
    lis.sort();
    output_count = optional_arg;
    typename std::list<T>::iterator itr = lis.begin();
    for (int i=0; i < output_count; i++,itr++) {
        ostr << *itr << "\n";
    }
}


//compare two words by iterating through each character and then increasing til it doesn't match
//print out the longest one.
void list_longest_substring(std::list<std::string> &lis, std::ostream &ostr, int &output_count) {
    int best = 0;
    std::string substring;
    std::list<std::string>::iterator itr1 = lis.begin();
    std::list<std::string>::iterator tmp;
    std::list<std::string>::iterator itr2;
    for(unsigned int i=0; i<lis.size()-1;i++,itr1++){
        tmp = itr1;
        tmp++;
        itr2 = tmp;
        for(;itr2!=lis.end();itr2++){
            for(unsigned int k=0;k<(*itr1).size();k++){
                for(unsigned int l=0;l<(*itr2).size();l++){
                    int q=0;
                    std::string tmp_s = "";
                    int match = 0;
                    while( (k+q) < (*itr1).size() && (l+q) < (*itr2).size() ) {
                        if((*itr1)[k+q] == (*itr2)[l+q]){
                            tmp_s+=(*itr1)[k+q];
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
}

void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

    if (type == "string") {
        // load the data into a list of strings
        std::list<std::string> lis;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            lis.push_back(s);
            input_count++;
        }
        if      (operation == "sort"){
            list_sort(lis,ostr,output_count);
        }
        else if (operation == "remove_duplicates") {
            list_remove_duplicates(lis,ostr,output_count);
        }
        else if (operation == "mode")              {
            list_mode(lis,ostr,output_count);
        }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted")      {
            list_first_sorted      (lis,ostr,output_count,optional_arg);
        }
        else if (operation == "longest_substring") {
            list_longest_substring (lis,ostr,output_count);
        }
        else {
            std::cerr << "Error: Unknown operation: " << operation << std::endl;
            usage();
            exit(0);
        }
    }

    else {
        assert (type == "integer");
        // load the data into a list of integers
        std::list<int> lis;
        int v;
        input_count = 0;
        while (istr >> v) {
            lis.push_back(v);
            input_count++;
        }
        if      (operation == "sort"){
            list_sort(lis,ostr,output_count);
        }
        else if (operation == "remove_duplicates"){
            list_remove_duplicates (lis,ostr,output_count); }
        else if (operation == "mode"){
            list_mode(lis,ostr,output_count);
        }
        else if (operation == "closest_pair"){
            list_closest_pair      (lis,ostr,output_count);
        }
        else if (operation == "first_sorted"){
            list_first_sorted      (lis,ostr,output_count,optional_arg);
        }
        // "longest_substring" not available for integers
        else {
            std::cerr << "Error: Unknown operation: " << operation << std::endl;
            usage();
            exit(0);
        }
    }
}
