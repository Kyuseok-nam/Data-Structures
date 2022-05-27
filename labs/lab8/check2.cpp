// A simple "caller ID" program
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

int main(int argc, char*argv[]){
    std::ifstream istr(argv[1]);
    std::map<int,int> number;
    int num;
    std::map<int,int>::iterator tmp;
    while(istr>>num){
        std::pair<std::map<int,int>::iterator,bool> tmp1 = number.insert(std::make_pair(num,1));
        if(tmp1.second == false){
            tmp1.first->second+=1;
        }
    }
    
    std::map<int,int>::iterator itr = number.begin();
    std::vector<int> l;
    int max = 0;
    while(itr!=number.end()){
        if(itr->second>max){
            l.clear();
            l.push_back(itr->first);
            max = itr->second;
        }
        else if(itr->second == max){
            l.push_back(itr->first);
        }
        itr++;
    }
    for(unsigned int i=0; i<l.size();i++){
        std::cout<< l[i]<<" ";
    }
    std::cout<<std::endl;
}
