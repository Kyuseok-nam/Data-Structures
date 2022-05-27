#include <iostream>


int num_path(int x, int y,int &num){
    if(y==0 && x==0){
        std::cout<<num<<std::endl;
        return num+=1;
    }
    if(x!=0){
        return num_path(x-1,y,num);
    }
    if(y!=0){
        return num_path(x,y-1,num);
    }
}



int main(int argc, char*argv[]){
    int num = 0;
    int paths = num_path(2,2,num);
    std::cout<<paths<<std::endl;
}
