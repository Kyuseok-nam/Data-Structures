#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include "Customer.h"

//fucntion for adding the prefernce to preference list
void Customer::add_preference(const std::string& pre){
    preference.push_back(pre);
}

//function for checking if that preference already exists
bool Customer::check_preference_exist(const std::string& name){
    preference_type::iterator itr = preference.begin();
    for(;itr!=preference.end();itr++){
        if(name == *itr){
            return true;
        }
    }
    return false;
}

//function for returning the oldest dvd in possession
std::string Customer::return_oldest(){
    std::string returned;
    preference_type::iterator itr = possession.begin();
    returned = *itr;
    possession.pop_front();
    return returned;
}

//function for returning the newest dvd in possession
std::string Customer::return_newest(){
    std::string returned;
    preference_type::iterator itr = possession.end();
    itr--;
    returned = *itr;
    possession.pop_back();
    return returned;
}

//returns true is it has max number of movies
bool Customer::has_max_num_movies(){
    if(possession.size()==3){
        return true;
    }
    return false;
}

//returns true if the list is empty
bool Customer::preference_list_empty(){
    if(preference.size()==0){
        return true;
    }
    return false;
}

//function that recieves the dvd and puts into possession
//then deletes it from preference list
void Customer::receives(const std::string& dvd){
    possession.push_back(dvd);
    preference_type::iterator itr = preference.begin();
    for(;itr!=preference.end();itr++){
        if(*itr==dvd){
            itr = preference.erase(itr);
            return;
        }
    }
}

//checks to see if that dvd is in possession
bool Customer::in_possession(const std::string& dvd){
    preference_type::iterator itr = possession.begin();
    for(;itr!=possession.end();itr++){
        if(*itr==dvd){
            return true;
        }
    }
    return false;
}

//prints the dvds in possession
void Customer::print_possession(std::ostream &ostr){
    preference_type::iterator itr = possession.begin();
    for(;itr!=possession.end();itr++){
        ostr<<"    "<<*itr<<std::endl;
    }
}

//prints the dvds in preference
void Customer::print_preference(std::ostream &ostr){
    ostr<<"  preference list:"<<std::endl;
    preference_type::iterator itr = preference.begin();
    for(;itr!=preference.end();itr++){
        ostr<<"    "<<*itr<<std::endl;
    }
}
