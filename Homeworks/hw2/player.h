#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class player {
public:
    //constructor
    player(){score = 0; gutter = 0; strike = 0;}
    //getters
    std::string get_first_name() const{return first_name;}
    std::string get_last_name() const{return last_name;}
    std::vector<std::vector<int> > get_pins() const{return pins;}
    std::vector<int> get_points() const{return points;}
    int get_score() const{return score;}
    int get_strike() const{return strike;}
    int get_gutter() const{return gutter;}
    
    //setters
    void set_first_name(const std::string &aname);
    void set_last_name(const std::string &aname);
    void set_pins(const std::vector<std::vector<int> > &apins);
    
    //functions
    void calculate_score();
    void print(int max,std::ofstream &out_str);
    
private:
    //private member variables
    std::string first_name;
    std::string last_name;
    //a vector that stores number of pins hit for each round
    std::vector<std::vector<int> > pins;
    //a vector that stores each point earned for each round
    std::vector<int> points;
    int score;
    int gutter;
    int strike;
};

//sort functions
bool sort_name(const player& player1, const player& player2);
bool sort_score(const player& player1, const player& player2);
bool sort_strike(const player& player1, const player& player2);
bool sort_gutter(const player& player1, const player& player2);
