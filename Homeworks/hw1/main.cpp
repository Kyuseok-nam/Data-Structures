#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>   //library for atoi
#include <fstream> //read and write files


//function for full left
//prints the line first and then prints the spaces.
void left(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<"| "<<lines1[i]<<std::string(width-(lines1[i].size()-1),' ')<<"|"<<std::endl;
    }
    out_str<<line<<std::endl;
}

//function for flush right
//calculates the number of spaces by subtracting size of a line from width. then prints the line
void right(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<"| "<<std::string(width-(lines1[i].size()-1),' ')<<lines1[i]<<"|"<<std::endl;
    }
    out_str<<line<<std::endl;
}

//function for full justify
void justify(int width, std::vector<std::vector<std::string> >& lines,
             const std::vector<std::string> & lines1,std::ofstream &out_str){
    
    //calculates the additional spaces that need to be added. then using a 2d vector lines,
    //loop through each vector and add one spaces each time from the left until no spaces remain.
    for(unsigned int i=0; i<lines1.size()-1;i++){
        int spaces = 0;
        spaces = width - (lines1[i].size()-1);
        int j =0;
        if(lines[i].size()==1){
            lines[i][0]+=std::string(spaces,' ');
        }
        else{
            while(spaces>0){
                lines[i][j]+=" ";
                spaces-=1;
                j++;
                if(j==(lines[i].size()-1)){j=0;}
            }
        }
    }
    
    //prints the ascii box with words full justified
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines.size();i++){
        out_str<<"| ";
        for(unsigned int j=0; j<lines[i].size();j++){
            out_str<<lines[i][j];
        }
        if(i == lines.size()-1){
            out_str<<std::string(width-(lines1[i].size()-1),' ');
        }
        out_str<<"|"<<std::endl;
    }
    out_str<<line<<std::endl;
}

//a function for creating a trapezoid ascii art and a flush left
void trap_l(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<std::string(i+1,' ')<<"| "<<lines1[i]<<std::string(width-(lines1[i].size()-1),' ')<<"|"<<std::endl;
    }
    out_str<<std::string(lines1.size()+1,' ')<<line<<std::endl;
}

//a function for creating a trapezoid ascii art and a flush right
void trap_r(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<std::string(i+1,' ')<<"| "<<std::string(width-(lines1[i].size()-1),' ')<<lines1[i]<<"|"<<std::endl;
    }
    out_str<<std::string(lines1.size()+1,' ')<<line<<std::endl;
}


int main(int argc,char*argv[]){
    if(argc<5){ //error checking for correct arugments for command line
        std::cerr<<"more arguments for command line needed"<<std::endl;
        exit(1);
    }
    
    //error checking to see if argument 3 is a integer
    std::string num = argv[3];
    for(unsigned int i=0; i<num.size();i++){
        if(!std::isdigit(argv[3][i])){
            std::cerr<<"argument 3 is not an integer"<<std::endl;
            exit(1);
        }
    }
    
    std::ifstream in_str(argv[1]);
    std::ofstream out_str(argv[2]);
    int width = atoi(argv[3]);
    std::string command = argv[4];
    
    //error checking to see if file is accesible
    if(!in_str.good()){ //error checking for reading files
        std::cerr<<"Can't open"<<argv[1]<<std::endl;
        exit(1);
    }
    if(!out_str.good()){ //error checking for writing files
        std::cerr<<"Can't open " << argv[4] << " to write.\n"<<std::endl;
        exit(1);
    }
    
    std::string word="";
    std::vector<std::string> words;
    
    while(in_str >> word){ //reads and stores the words in vetor
        //if a single word is longer than the width divide and add a hyphoon
        if(word.size()>width){
            std::string tmp = "";
            for(unsigned int i=0,j=1; i< word.size();i++,j++){
                if(j==width){
                    tmp+='-';
                    words.push_back(tmp);
                    tmp = "";
                    j=1;
                }
                tmp+=word[i];
                if(i==(word.size()-1)){
                    words.push_back(tmp);
                    break;
                }
            }
        }
        //if word is not longer than the width add to the vector
        else{
             words.push_back(word);
        }
    }
    
    std::vector<std::string> lines1;    //vector that stores each line
    std::string line = "";
    std::vector<std::vector<std::string> > lines; // 2d vector that stores each word for each line
    std::vector<std::string> temp;
    int check = 0; // variable that checks if the word added exceeds the width
    
    //checks and divides the words to each line
    for(unsigned int i=0; i<words.size();i++){
        if((check+words[i].size()) <= (width)){
            line+=(words[i]+" ");
            temp.push_back(words[i]+" ");
            check+=words[i].size()+1;
            if(i == words.size()-1){
                lines.push_back(temp);
                lines1.push_back(line);
            }
        }
        else{
            lines1.push_back(line);
            lines.push_back(temp);
            line = "";
            temp.clear();
            line+= (words[i]+" ");
            temp.push_back(words[i]+" ");
            check = 0;
            check += words[i].size()+1;
            if(i == words.size()-1){
                lines1.push_back(line);
                lines.push_back(temp);
            }
        }
    }
    
    //if command is flush left
    if(command == "flush_left"){
        left(width,lines1,out_str);
    }
    
    //if command is flush right
    else if(command == "flush_right"){
        right(width,lines1,out_str);
    }
    
    //if command is full justify
    else if(command == "full_justify"){
        justify(width,lines,lines1,out_str);
    }
    
    else if(command == "trapezoidal_left"){
        trap_l(width,lines1,out_str);
    }
    else if(command == "trapezoidal_right"){
        trap_r(width,lines1,out_str);
    }
    
    //error checking for invalid commands
    else{
        std::cerr<<"invalid command"<<std::endl;
        exit(1);
    }
}
