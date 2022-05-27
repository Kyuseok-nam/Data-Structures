 #include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <list>

typedef std::vector<std::vector<char> > double_vector;
int num_sol = 0;

//helper function for usage
void usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " [dictionary file] [initial grid file]";
    std::cerr << " [solution mode] [outputmode] [gc]"<<std::endl;
    exit(1);
}

//helper function for reading initial grid
void read_grid(std::vector<std::vector<char> > &grid,std::vector<int>&constraint,
               std::ifstream & istr){
    std::string word;
    while(istr>>word){
        //ignore the sentence after !
        if(word[0]=='!'){
        }
        //save the number after +
        else if(word[0]=='+'){
            std::string tmp;
            for(unsigned int i=1; i<word.size();i++){
                tmp.push_back(word[i]);
            }
            constraint.push_back(stoi(tmp));
        }
        //save the grid in a 2-d vector
        else{
            std::vector<char> tmp;
            for(unsigned int i=0; i<word.size();i++){
                tmp.push_back(word[i]);
            }
            grid.push_back(tmp);
            tmp.clear();
        }
    }
}

//function for printing all solution boards
void print_boards(const std::vector<double_vector>& solutions){
    if(solutions.size()<=0){
        return;
    }
    for(unsigned int i=0; i<solutions.size();i++){
        std::cout<<"Board:"<<std::endl;
        for(unsigned int j=0;j<solutions[0].size();j++){
            for(unsigned int k=0;k<solutions[0][0].size();k++){
                std::cout<<solutions[i][j][k];
            }
            std::cout<<std::endl;
        }
    }
    return;
}

//function for printing a single board
void print_board(const std::vector<double_vector>& solutions){
    if(solutions.size()<=0){
        return;
    }
    std::cout<<"Board:"<<std::endl;
    for(unsigned int j=0;j<solutions[0].size();j++){
        for(unsigned int k=0;k<solutions[0][0].size();k++){
            std::cout<<solutions[0][j][k];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    return;
}
//----------------------------------------------------------

//a function that checks vectically and if the word exist in dict put it into empty grid
double_vector vertical(int x,int y, int l, double_vector grid, double_vector empty,
                       const std::vector<std::string>&dict){
    std::string tmp = "";
    for(int i=0;i<l;i++){
        tmp+=grid[x+i][y];
    }
    //search if it is a valid word
    std::vector<std::string>::const_iterator itr = std::find(dict.begin(),dict.end(),tmp);
    //if it is valid add the word to empty grid
    if(itr!=dict.end()){
        for(int i=0;i<l;i++){
            empty[x+i][y] = tmp[i];
        }
        return empty;
    }
    //if it is not valid mark invalid by putting !
    else{
        empty[0][0]='!';
        return empty;
    }
}

//a function that checks horizontaly and if the word exist in dict put it into empty grid
double_vector horizontal(int x,int y, int l, double_vector grid, double_vector empty,
                         const std::vector<std::string>&dict){
    std::string tmp = "";
    for(int i=0;i<l;i++){
        tmp+=grid[x][y+i];
    }
    //search if it is a valid word
    std::vector<std::string>::const_iterator itr = std::find(dict.begin(),dict.end(),tmp);
    //if word is valid put it into empty grid
    if(itr!=dict.end()){
        for(int i=0;i<l;i++){
            empty[x][y+i] = tmp[i];
        }
        return empty;
    }
    //if it is not valid mark invalid by putting !
    else{
        empty[0][0] = '!';
        return empty;
    }
}

//a helper function that checks if it is a valid solution by searching for all the possible
// words that exist vertically and horizontaly. Then it goes through 3 error checkings.
//1. if the number of words in solution grid is greater than number of words in answer
//2. if the words in solution grid are all valid words in dictionary
//3. if each word's length all match with the constraints given.
bool check_grid(double_vector empty, std::vector<int> constraint,const std::vector<std::string>& dict){
    //temporary vector that stores all the words in the possible solution grid
    std::vector<std::string> tmp;
    //search for all horizontal words inside the possible solution grid
    for(unsigned int i=0;i<empty.size();i++){
        std::string s = "";
        for(unsigned int j=0; j<empty[i].size();j++){
            if(empty[i][j]=='#'){
                if(s.size()>1){
                    tmp.push_back(s);
                }
                s.clear();
                continue;
            }
            s+=empty[i][j];
            if(j==empty[i].size()-1){
                if(s.size()>1){
                    tmp.push_back(s);
                }
            }
        }
    }
    
    //search for all vertical words inside the possible solution grid
    for(unsigned int i =0;i<empty[0].size();i++){
        std::string s = "";
        for(unsigned int j=0;j<empty.size();j++){
            if(empty[j][i]=='#'){
                if(s.size()>1){
                    tmp.push_back(s);
                }
                s.clear();
                continue;
            }
            s+=empty[j][i];
            if(j==empty.size()-1){
                if(s.size()>1){
                    tmp.push_back(s);
                }
            }
        }
    }
    //if number of words that exist in grid is greater
    //than the number of answers return false
    if(tmp.size()!=constraint.size()){
        return false;
    }
    //if number of words that exist in grid is not in dictionary
    //return false
    for(unsigned int i=0; i<tmp.size();i++){
        std::vector<std::string>::const_iterator itr = std::find(dict.begin(),dict.end(),tmp[i]);
        if(itr==dict.end()){
            return false;
        }
    }
    //see if all the words length match the contraints
    for(unsigned int i=0; i<tmp.size();i++){
        std::vector<int>::iterator itr = std::find(constraint.begin(),constraint.end(),tmp[i].size());
        if(itr==constraint.end()){return false;}
        itr = constraint.erase(itr);
    }
    return true;
}


//A recursive function that solves the crossword puzzle
//if check==1 it checked vertical before recursion
//if check==0 it checked horizontal before recursion
void solve(std::vector<double_vector >&solutions,double_vector grid,
           double_vector empty,const std::vector<int>& constraint,
           std::vector<std::string> dict, int rows,int columns,int num,
           int prev_i,int prev_j,int check){
    
    if(num<constraint.size()){
        int l = constraint[num];
        //check if length of word searching for is less than columns
        if(l<=columns){
            //checks horizontally and then call the recursive function again
            //with the next constraint
            for(int i=0;i<rows;i++){
                for(int j=0;j < columns-l+1;j++){
                    //check if it is not repeating the same place as the
                    //recursive function before
                    if(prev_i==i&&prev_j==j && check == 0){continue;}
                    double_vector empty1 = horizontal(i,j,l,grid,empty,dict);
                    //if it is valid move on to the next constraint
                    if(empty1[0][0]!='!'){
                        solve(solutions,grid,empty1,constraint,dict,
                              rows,columns,num+1,i,j,0);
                    }
                }
            }
        }
        //check if length of word searching for is less than rows
        if(l<=rows){
            //checks vertically and then call the recursive function again
            //with the next constraint
            for(int i=0;i<columns;i++){
                for(int j=0; j<rows-l+1;j++){
                    //check if it is not repeating the same place as
                    //the recursive function before
                    if(prev_i == i && prev_j == j &&check==1){continue;}
                    double_vector empty2 = vertical(j,i,l,grid,empty,dict);
                    //if it is valid move on to the next constraint
                    if(empty2[0][0]!='!'){
                        solve(solutions,grid,empty2,constraint,dict,
                              rows,columns,num+1,i,j,1);
                    }
                }
            }
        }
    }
    //base case
    else{
        //check if it is not a redudant solution grid and is valid by check function
        std::vector<double_vector>::iterator itr =
        std::find(solutions.begin(),solutions.end(),empty);
        if(itr==solutions.end()&&check_grid(empty,constraint,dict)){
            solutions.push_back(empty);
        }
        return;
    }
}



//====================================================

int main(int argc,char*argv[]){
    if(argc!=5 && argc!=6){
        std::cerr<<"5 or 6 command line arguments needed"<<std::endl;
        exit(1);
    }
    std::ifstream dstr(argv[1]);
    std::ifstream istr(argv[2]);
    std::string solution = argv[3];
    std::string output = argv[4];
    //error checkings
    if(!dstr){
        std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
        usage(argv[0]);
    }
    if(!istr){
        std::cerr << "ERROR: Could not open " << argv[2] << " for reading." << std::endl;
        usage(argv[0]);
    }
    if(solution != "one_solution" && solution != "all_solutions"){
        std::cerr<< "ERROR: Invalid solution command."<<std::endl;
        exit(1);
    }
    if(output != "count_only" && output!= "print_boards"){
        std::cerr<< "ERROR: Invalid output command."<<std::endl;
        exit(1);
    }
    
    //read dict and store in vector
    std::vector<std::string> dict;
    std::string word;
    while(dstr>>word){
        dict.push_back(word);
    }
    //read Initial grid;
    double_vector grid;
    std::vector<int> constraint;
    read_grid(grid,constraint,istr);
    
    
    unsigned int rows = grid.size();
    unsigned int columns = grid[0].size();

    //empty grid only filled with '#'.
    double_vector empty(rows,std::vector<char>(columns,'#'));
    //a 3-d vector that stores all the solution grids
    std::vector<double_vector> solutions;
    
    solve(solutions,grid,empty,constraint,dict,rows,columns,0,1,1,3);
    //if it is count only only print number of solutions
    if(output == "count_only"){
        if(solution =="one_solution"){
            std::cout<<"Number of solution(s): ";
            if(solutions.size()>0){
                std::cout<<"1"<<std::endl;
            }
            else{
                std::cout<<"0"<<std::endl;
            }
        }
        else{
            std::cout<<"Number of solution(s): "<<solutions.size()<<std::endl;
        }
    }
    //if it is print boards
    else {
        //if it is only one solution only print one solution one board if exist
        if(solution =="one_solution"){
            std::cout<<"Number of solution(s): ";
            if(solutions.size()>0){
                std::cout<<"1"<<std::endl;
            }
            else{
                std::cout<<"0"<<std::endl;
            }
            print_board(solutions);
        }
        //print all solutions board and counts
        else{
            std::cout<<"Number of solution(s): "<<solutions.size()<<std::endl;
            print_boards(solutions);
        }
    }
    return 0;
}
