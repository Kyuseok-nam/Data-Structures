#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include "DVD.h"

//function for creating constructor
void DVD::create(){
    name = "";
    total_copies = 0;
    available_copies = 0;
}

//function for creating constructor with arguments
void DVD::create(const std::string& aname,int num){
    name = aname;
    total_copies = num;
    available_copies = num;
}

//decrement available copies when shipped
void DVD::shipped(){
    available_copies-=1;
}


