#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


//function for mode
template <class T>
void hash_mode(std::unordered_map<T,int> &hm, std::ostream &ostr,
               int &output_count) {
    typename std::unordered_map<T,int>::iterator itr = hm.begin();
    typename std::unordered_map<T,int>::iterator ret;
    int best =0;
    //iterate through the hash table to look for largest value;
    for(;itr!=hm.end();itr++){
        if(itr->second>best){
            best = itr->second;
            ret = itr;
        }
    }
    ostr<<ret->first<<std::endl;
    output_count=1;
}


//fucntion for longet substring
void hash_longest_substring(std::unordered_map<std::string,int> &hm,
                            std::ostream &ostr, int &output_count) {
    
    std::unordered_map<std::string,int>::iterator itr = hm.begin();
    std::string answer = itr->first;
    bool duplicate = false;
    //find the longest key duplicate
    for(;itr!=hm.end();itr++){
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
    itr = hm.begin();
    std::unordered_map<std::string,int>::iterator tmp;
    std::unordered_map<std::string,int>::iterator itr2;
    for(unsigned int i=0; i<hm.size()-1;i++,itr++){
        tmp = itr;
        tmp++;
        itr2 = tmp;
        for(;itr2!=hm.end();itr2++){
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



void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count,int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR 
  // std::unordered_map<std::string,int> ht;

    if (type == "string") {
        std::unordered_map<std::string,int> hm;
        std::unordered_set<std::string> hs;
        std::string s;
        input_count = 0;
        output_count=0;
        if (operation == "remove_duplicates"){
            //search for the string in map, if exist don't print
            //if doesn't exist insert and print.
            std::unordered_set<std::string>::iterator itr;
            while (istr >> s) {
                input_count++;
                itr = hs.find(s);
                if(itr==hs.end()||hs.size()==0){
                    hs.insert(s);
                    ostr<<s<<std::endl;
                    output_count++;
                }
            }
        }
        else if (operation == "mode"){
            //load data to hashtable
            while (istr >> s) {
                input_count++;
                hm[s]++;
            }
            hash_mode(hm,ostr,output_count);
        }
        // "closest_pair" not available for strings
        else if (operation == "longest_substring"){
            while (istr >> s) {
                input_count++;
                hm[s]++;
            }
            hash_longest_substring (hm,ostr,output_count);
        }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }

    else {
        assert (type == "integer");
        std::unordered_map<int,int> hm;
        std::unordered_set<int> hs;
        int v;
        input_count = 0;
        output_count=0;
        if (operation == "remove_duplicates") {
            //search for the string in map, if exist don't print
            //if doesn't exist insert and print.
            std::unordered_set<int>::iterator itr;
            while (istr >> v) {
                input_count++;
                itr = hs.find(v);
                if(itr==hs.end()||hs.size()==0){
                    hs.insert(v);
                    ostr<<v<<std::endl;
                    output_count++;
                }
            }
        }
        else if (operation == "mode"){
            while (istr >> v) {
                //load data to hash table
                input_count++;
                hm[v]++;
            }
            hash_mode(hm,ostr,output_count);
        }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
