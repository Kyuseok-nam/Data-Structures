#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "player.h"


//accessors
void player::set_first_name(const std::string & aname){
    first_name = aname;
}

void player::set_last_name(const std::string & aname){
    last_name = aname;
}

void player::set_pins(const std::vector<std::vector<int> > &apins){
    pins = apins;
}


//a function that calculates the score for each round and the final score
void player::calculate_score(){
    std::vector<int> tmp(10,0);
    points = tmp;
    
    //loops through each round til round 9 and calculates score
    for(unsigned int i=0; i<9; i++){
        //if that round is a strike
        if (pins[i].size()==1) {
            //if the second round is also a strike
            if(pins[i+1].size()==1){
                points[i] = 10+pins[i+1][0]+pins[i+2][0];
            }
            else{
                points[i] = 10+pins[i+1][0]+pins[i+1][1];
            }
        }
        //if that round is not a strike
        else{
            //if that round is a spare
            if(pins[i][0]+pins[i][1] == 10){
                points[i] = 10+pins[i+1][0];
            }
            //if that round is not a spare
            else{
                points[i] = pins[i][0]+pins[i][1];
            }
        }
    }
    
    //calculation for round 10
    for(unsigned int i=0; i<pins[9].size();i++){
        points[9]+=pins[9][i];
    }
    //accumulate score for each round til round 10;
    for(int i=1; i<10;i++){
        points[i] += points[i-1];
    }
    //set final score
    score = points[9];
}




//a function to print player's pin and score for each round
// 2 arguments max: max length of name, output stream
void player::print(int max,std::ofstream &out_str){
    out_str<<std::string(67+max,'-')<<std::endl;
    out_str<<"| "<<std::left<<std::setw(max+2)<<first_name+" "+last_name<<"|";
    
    //loops each round until round 9 and prints the pins for each round
    for(unsigned int i=0;i<pins.size()-1;i++){
        //if that round is a strike.
        if(pins[i].size() == 1){
            out_str<<"   X |";
            strike+=1;
        }
        //if it is not a strike
        else{
            //if the first pin of that round is a gutter
            if(pins[i][0]==0){
                out_str<<" " <<"-"<<" ";
                gutter+=1;
            }
            //if the first pin of that round is not a gutter
            else{
                out_str<<" "<<pins[i][0]<<" ";
            }
            //if that round is a spare
            if(pins[i][0]+pins[i][1] == 10){
                out_str<<"/ |";
            }
            //if that round is not a spare
            else{
                //if the second pin of that round is a gutter
                if(pins[i][1] == 0){
                    out_str<<"-"<<" |";
                    gutter+=1;
                }
                //if the second pin of that round is not a gutter
                else{
                    out_str<<pins[i][1]<<" |";
                }
            }
        }
    }
    
    //prints the last round of that player
    std::string tmp;
    int check =0; //variable that is used to check if a mini round is completed
                  //in the 10th round
                  // when check == 0 new 10 pins will be set up
                  // when check == 1 the players hits the rest of the pins
    for(unsigned int i=0; i<pins[9].size();i++){
        if(check ==0){
            if(pins[9][i] == 10){
                strike+=1;
                tmp+=" X";
                check = 0;
            }
            else if(pins[9][i]==0){
                gutter+=1;
                tmp+=" -";
                check =1;
            }
            else{
                tmp+=" "+std::to_string(pins[9][i]);
                check =1;
            }
        }
        else if(check ==1){
            if(pins[9][i]+pins[9][i-1]==10){
                tmp+=" /";
                check =0;
            }
            else if(pins[9][i]==0){
                gutter+=1;
                tmp+=" -";
                check =0;
            }
            else{
                tmp+=" "+std::to_string(pins[9][i]);
                check =0;
            }
        }
    }
    out_str<<std::left<<std::setw(7)<<tmp<<"|";
    out_str<<std::endl;
    
    //starts printing the score for each round (second line for each player)
    out_str<<"|"<<std::string(max+3,' ')<<"|";
    for(int i=0; i<9;i++){
        out_str<<std::right<<std::setw(4)<<points[i]<<" |";
    }
    out_str<<std::right<<std::setw(6)<<points[9]<<" |";
    out_str<<std::endl;
}


//sorting functions

//sorts the players by their last name
bool sort_name(const player& player1, const player& player2){
    return player1.get_last_name() < player2.get_last_name()  ||(player1.get_last_name()==player2.get_last_name()
        && player1.get_first_name() < player2.get_first_name());
}

//sorts the players by their score
bool sort_score(const player& player1, const player& player2){
    return player1.get_score() > player2.get_score()
        || (player1.get_score() == player2.get_score()
        && player1.get_last_name() < player2.get_last_name());
}

//sorts the players by their strike number
bool sort_strike(const player& player1, const player& player2){
    return player1.get_strike() > player2.get_strike()
        || (player1.get_strike() == player2.get_strike()
        && player1.get_last_name() < player2.get_last_name());
}

//sorts the players by their gutter number
bool sort_gutter(const player& player1, const player& player2){
    return player1.get_gutter() > player2.get_gutter()
        || (player1.get_gutter() == player2.get_gutter()
        && player1.get_last_name() < player2.get_last_name());
}
