#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>

typedef std::map<std::string,int > COSTUME_SHOP_TYPE;
typedef std::map<std::string, std::string> PEOPLE_TYPE;
typedef std::map<std::string, std::list<std::string> > RENTAL;

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop,RENTAL& rent);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people,RENTAL& rent);
void lookup(COSTUME_SHOP_TYPE& costume_shop,RENTAL& rent);
void printPeople(PEOPLE_TYPE& people);

int main() {
    // two data structures store all of the information for efficiency
    COSTUME_SHOP_TYPE costume_shop;
    PEOPLE_TYPE people;
    RENTAL rent;
    char c;
    while (std::cin >> c) {
        if (c == 'a') {
            addCostume(costume_shop,rent);
        } else if (c == 'r') {
            rentCostume(costume_shop,people,rent);
        } else if (c == 'l') {
            lookup(costume_shop,rent);
        } else if (c == 'p') {
            printPeople(people);
        } else {
            std::cerr << "error unknown char " << c << std::endl;
            exit(0);
        }
    }
}

//function that adds the costume and person who rents it
//RENTAL rent is a map that stores costume name as the key, and all the customers who currently
//has that costume in chronological order as the value
void addCostume(COSTUME_SHOP_TYPE& costume_shop,RENTAL& rent) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    //adds the costume if it doens't exist or increment to the previous avail stock
    costume_shop[costume_name]+=num;
    rent[costume_name];
    if(num==1){
        std::cout<<"Added "<<num<<" "<<costume_name<<" costume."<<std::endl;
    }
    else{
        std::cout<<"Added "<<num<<" "<<costume_name<<" costumes."<<std::endl;
    }
}

//a function that is used when someone tries to rent a costume
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people,RENTAL& rent) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    std::string name = last_name+" "+first_name;
    std::string p_name = first_name+" "+last_name;
    PEOPLE_TYPE::iterator p_itr = people.find(name);
    COSTUME_SHOP_TYPE::iterator c_itr = costume_shop.find(costume_name);
    //when the person already has that costume
    if(p_itr->second==costume_name ){
        std::cout<<p_name<<" already has a "<<costume_name<<" costume."<<std::endl;
    }
    //if the costume does not exist in shop
    else if(c_itr == costume_shop.end()){
        people[name];
        std::cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<std::endl;
    }
    //if the costume is currently out of stock
    else if(c_itr->second == 0){
        people[name];
        std::cout<<"No "<<costume_name<<" costumes available."<<std::endl;
    }
    else{
        //if that person is first visiting the shop
        if(p_itr == people.end()){
            people[name] = costume_name;
            rent[costume_name].push_back(p_name);
            std::cout<<p_name<<" rents a "<<costume_name<<" costume."<<std::endl;
        }
        //if that person has previously visited the shop
        else{
            //if that person currently holds no costume rent the costume
            if(p_itr->second == ""){
                people[name] = costume_name;
                rent[costume_name].push_back(p_name);
                std::cout<<p_name<<" rents a "<<costume_name<<" costume."<<std::endl;
            }
            //if the person currently holds a different costume, return that costume
            //and the rent the costume he wants
            else{
                std::cout<<p_name<<" returns a "<<p_itr->second<<" costume before renting a "
                <<costume_name<<" costume."<<std::endl;
                std::list<std::string>::iterator itr =
                std::find(rent[p_itr->second].begin(),rent[p_itr->second].end(),p_name);
                itr = rent[p_itr->second].erase(itr);
                costume_shop[p_itr->second]+=1;
                people[name] = costume_name;
                rent[costume_name].push_back(p_name);
            }
        }
        costume_shop[costume_name]-=1;
    }
}

//function that prints available copies and lists people who current has that costume
void lookup(COSTUME_SHOP_TYPE& costume_shop, RENTAL& rent) {
    std::string costume_name;
    std::cin >> costume_name;
    COSTUME_SHOP_TYPE::iterator c_itr = costume_shop.find(costume_name);
    RENTAL::iterator r_itr = rent.find(costume_name);
    //if that costume doesn't exist in shop
    if(c_itr == costume_shop.end()){
        std::cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<std::endl;
    }
    //if that costume exist in shop
    else{
        //prints out shop information
        std::cout<<"Shop info for "<<costume_name<<" costumes:"<<std::endl;
        if(c_itr->second == 0){}
        else if(c_itr->second == 1){
            std::cout<<"  "<<c_itr->second<<" copy available"<<std::endl;
        }
        else{
            std::cout<<"  "<<c_itr->second<<" copies available"<<std::endl;
        }
        //prints out customer information
        if(r_itr->second.size()==0){}
        else if(r_itr->second.size()==1){
            std::cout<<"  1 copy rented by:"<<std::endl;
            std::cout<<"    "<<r_itr->second.front()<<std::endl;
        }
        else{
            std::cout<<"  "<<r_itr->second.size()<<" copies rented by:"<<std::endl;
            std::list<std::string>::iterator itr =r_itr->second.begin();
            for(;itr!=r_itr->second.end();itr++){
                std::cout<<"    "<<*itr<<std::endl;
            }
        }
    }
}

//helper function that reorders the last and first name that is reversed when stored.
void reorder_name(std::string& name){
    std::string first;
    std::string last;
    int i=0;
    while(name[i]!=' '){
        last+=name[i];
        i++;
    }
    i+=1;
    while(i<name.size()){
        first+=name[i];
        i++;
    }
    name = first+" "+last;
}


//function that prints the people that have attempted to rent costume.
void printPeople(PEOPLE_TYPE& people) {
    PEOPLE_TYPE::iterator p_itr = people.begin();
    if(people.size()==1){
        std::string name = p_itr->first;
        reorder_name(name);
        std::cout<<"Costume info for the 1 party attendee:"<<std::endl;
        if(p_itr->second == ""){
            std::cout<<"  "<<name<<" does not have a costume."<<std::endl;
        }
        else{
            std::cout<<"  "<<name<<" is wearing a "<<p_itr->second<<" costume."<<std::endl;
        }
    }
    else{
        std::cout<<"Costume info for the "<<people.size()<<" party attendees:"<<std::endl;
        //iterate through map and print out all the people who have visited
        for(;p_itr!=people.end();p_itr++){
            std::string name = p_itr->first;
            reorder_name(name);
            //if that person does not have a costume
            if(p_itr->second == ""){
                std::cout<<"  "<<name<<" does not have a costume."<<std::endl;
            }
            //if that person has a costume
            else{
                std::cout<<"  "<<name<<" is wearing a "<<p_itr->second<<" costume."<<std::endl;
            }
        }
    }
}
