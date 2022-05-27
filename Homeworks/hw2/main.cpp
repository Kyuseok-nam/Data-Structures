#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "player.h"

//function that reads in the file
void read_file(std::ifstream &in_str,std::vector<player> &players){
    std::string first_name, last_name, name;
    player p;
    std::vector<std::vector<int> > tmp_pins;
    
    while(in_str >>first_name >>last_name){
        p.set_first_name(first_name);
        p.set_last_name(last_name);
        int round = 1; //variable to check round number
        std::string word;
        while(round <=10){
            std::vector<int> pin_round;
            int num;
            in_str >> word;
            num = std::stoi(word);
            pin_round.push_back(num);
            //if it is the last round
            if(round == 10){
                int spare = 0;
                spare+=num;
                in_str>>word;
                num = std::stoi(word);
                //if the first pin was a strike get the third pin number.
                if(spare == 10){
                    pin_round.push_back(num);
                    in_str>>word;
                    num = std::stoi(word);
                    pin_round.push_back(num);
                }
                //if the first pin was not a strike
                else{
                    spare+=num;
                    pin_round.push_back(num);
                    //if the first two pins was a spare get the last third pin number
                    if(spare ==10){
                        in_str>>word;
                        num = std::stoi(word);
                        pin_round.push_back(num);
                    }
                }
            }
            //if it is not the last round(round 1~9)
            else{
                //only if the first pin was not a strike get the second pin
                if(num <10){
                    in_str>>word;
                    num = std::stoi(word);
                    pin_round.push_back(num);
                }
            }
            tmp_pins.push_back(pin_round);
            round++;
            pin_round.clear();
        }
        p.set_pins(tmp_pins);
        players.push_back(p);
        tmp_pins.clear();
    }
}




int main(int argc, char*argv[]){
    
    //error checking for 4 arguments
    if(argc != 4){
        std::cerr<<"Usage:\n "<<argv[0]<<"  input file.txt   outputfile.txt    command"<<std::endl;
        exit(1);
    }
    
    std::ifstream in_str(argv[1]);
    //error checking for input file
    if(!in_str){
        std::cerr<<"Could not open"<<argv[1]<<std::endl;
        exit(1);
    }
    
    //error checking for output file
    std::ofstream out_str(argv[2]);
    if(!out_str){
        std::cerr<<"Could not open"<<argv[2]<<std::endl;
        exit(1);
    }
    
    //error checking for invalid command
    std::string command = argv[3];
    if((command != "standard") && (command!= "custom")){
        std::cerr<<command<<"is an invalid command"<<std::endl;
        exit(1);
    }
    
    std::vector<player> players;
    read_file(in_str,players);
    std::sort(players.begin(),players.end(),sort_name);
    int max_name = 0;
    //gets the max_length of name among players
    for(unsigned int i=0; i<players.size();i++){
        if(max_name<players[i].get_first_name().size()+players[i].get_last_name().size()){
            max_name = players[i].get_first_name().size()+players[i].get_last_name().size();
        }
    }
    
    //calculates the score for each player and prints the score board
    for(unsigned int i=0; i<players.size();i++){
        players[i].calculate_score();
        players[i].print(max_name,out_str);
    }
    out_str<<std::string(67+max_name,'-')<<std::endl<<std::endl;
    
    //prints out the final scores for each player if the command is standard
    if(command == "standard"){
        std::sort(players.begin(),players.end(),sort_score);
        for(unsigned int i=0; i<players.size();i++){
            std::string n = players[i].get_first_name()+" "+players[i].get_last_name();
            out_str<<std::left<<std::setw(max_name+2)<<n<<" ";
            out_str<<std::right<<std::setw(3)<<players[i].get_score()<<std::endl;
        }
    }
    
    //if command == custom prints out the custom statistics.
    else if(command == "custom"){
        //sorts by most strikes
        std::sort(players.begin(),players.end(),sort_strike);
        out_str<<"Player Sorted by Most Strikes\n"<<std::endl;
        for(unsigned int i=0; i<players.size();i++){
            std::string n = players[i].get_first_name()+" "+players[i].get_last_name();
            out_str<<std::left<<std::setw(max_name+2)<<n<<" ";
            out_str<<std::right<<std::setw(3)<<players[i].get_strike()<<std::endl;
        }
        
        //sorts by most gutters
        std::sort(players.begin(),players.end(),sort_gutter);
        out_str<<"\n\nPlayer Sorted by Most Gutters\n"<<std::endl;
        for(unsigned int i=0; i<players.size();i++){
            std::string n = players[i].get_first_name()+" "+players[i].get_last_name();
            out_str<<std::left<<std::setw(max_name+2)<<n<<" ";
            out_str<<std::right<<std::setw(3)<<players[i].get_gutter()<<std::endl;
        }
    }
}
