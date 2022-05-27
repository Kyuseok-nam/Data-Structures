#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <fstream> //read and write files

void left(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<"| "<<lines1[i]<<std::string(width-(lines1[i].size()-1),' ')<<"|"<<std::endl;
    }
    out_str<<line<<std::endl;
}

void right(int width,const std::vector<std::string>& lines1, std::ofstream &out_str){
    std::string line(width+4,'-');
    out_str<<line<<std::endl;
    for(unsigned int i=0; i<lines1.size();i++){
        out_str<<"| "<<std::string(width-(lines1[i].size()-1),' ')<<lines1[i]<<"|"<<std::endl;
    }
    out_str<<line<<std::endl;
}


void justify(int width, std::vector<std::vector<std::string> >& lines,
             const std::vector<std::string> & lines1,std::ofstream &out_str){
    
    for(unsigned int i=0; i<lines1.size()-1;i++){
        int spaces = 0;
        spaces = width - (lines1[i].size()-1);
        //std::cout<<lines1[i]<<"*"<<lines1[i].size()<<std::endl;
        unsigned int j=0;
        while(spaces>0){
            if(j==lines[i].size()-1){j=0;}
            lines[i][j]+=" ";
            spaces-=1;
            j++;
        }
    }
    
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




int main(int argc,char*argv[]){
    if(argc<5){ //error checking for correct arugments for command line
        std::cerr<<"more arguments for command line needed"<<std::endl;
        exit(1);
    }
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
        else{
             words.push_back(word);
        }
    }
    
    std::vector<std::string> lines1;
    std::string line = "";
    std::vector<std::vector<std::string> > lines;
    std::vector<std::string> temp;
    int check = 0;
    for(unsigned int i=0; i<words.size();i++){
        if((check+words[i].size()) <= width){
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
    
    if(command == "flush_left"){
        left(width,lines1,out_str);
    }
    else if(command == "flush_right"){
        right(width,lines1,out_str);
    }
    
    else if(command == "full_justify"){
        justify(width,lines,lines1,out_str);
    }
    else{
        std::cerr<<"invalid command"<<std::endl;
        exit(1);
    }
}
