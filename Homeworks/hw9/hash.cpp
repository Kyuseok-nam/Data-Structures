#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include "kyu_hash.h"


class hash_string_obj {
public:
  // ----------------------------------------------------------
  // EXPERIMENT WITH THE HASH FUNCTION FOR CHECKPOINT 1, PART 2

  unsigned int operator() ( const std::string& key ) const {
    //  This implementation comes from
    //  http://www.partow.net/programming/hashfunctions/
    //
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }
};


//helper function for reading in genome file and storing it into string
void read_file(std::ifstream& in_str,std::string& genome){
    std::string word;
    while(in_str>>word){
        genome+=word;
    }
}


typedef ds_hashset<std::string,hash_string_obj> ds_hash_type;
typedef std::list<int>::iterator hash_list_itr;

int main(int argc, char* argv[]){
    std::string word;
    std::string in_file;
    std::string query;
    std::string genome;
    int k=0;
    unsigned int table_size = 100;
    int mismatch;
    float occupancy = 0.5;
    
    
    
    ds_hash_type table(table_size,occupancy);
    
    while(std::cin>>word){
        //genome command
        //read input file than put it insto a string
        if(word == "genome"){
            std::cin>>in_file;
            std::ifstream in_str(in_file);
            if(!in_str){
                std::cerr<<"Could not open"<<in_file<<std::endl;
                exit(1);
            }
            read_file(in_str,genome);
        }
        //table size command
        else if(word == "table_size"){
            std::cin>>table_size;
        }
        //occupancy command
        else if(word == "occupancy"){
            std::cin>>occupancy;
        }
        //kmer command
        //create keys and insert into hash table
        else if(word == "kmer"){
            std::cin>>k;
            for(unsigned int i=0;i<genome.size()-k+1;i++){
                std::string tmp;
                for(int j=0; j<k;j++){
                    tmp+=genome[i+j];
                }
                table.insert(tmp,i);
            }
        }
        //query command
        else if(word == "query"){
            std::cin>>mismatch>>query;
            std::pair<std::list<int> ,bool > result;
            std::string key;
            bool exist = false;
            //get the key from the query
            for(int i=0; i<k;i++){
                key += query[i];
            }
            //search for key in the hash table
            result = table.find(key);
            std::cout<<"Query: "<<query<<std::endl;
            hash_list_itr itr = result.first.begin();
            //if that key was found iterate through the values for that key
            //and search for correspoding strings
            if(result.second){
                for(;itr!=result.first.end();itr++){
                    std::string answer;
                    int num=0;
                    for(int i=0; i<query.size();i++){
                        answer+=genome[(*itr)+i];
                        if(genome[(*itr)+i] != query[i]){
                            num++;
                        }
                    }
                    //if the number of mismatch is less or equal than requirement
                    if(num<=mismatch){
                        std::cout<<*itr<<" "<<num<<" "<<answer<<std::endl;
                        exist = true;
                    }
                }
                //if such string doesn't exist
                if(!exist){
                    std::cout<<"No Match"<<std::endl;
                }
            }
            else{
                std::cout<<"not found"<<std::endl;
            }
        }
        //quit command
        else if(word == "quit"){
            exit(1);
        }
        //invalid command
        else{
            std::cerr<<word<<" invalid command"<<std::endl;
        }
    }
    

}

