#ifndef DVD_h_
#define DVD_h_
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>

class DVD{
public:
    //constructor
    DVD(){create();}
    DVD(const std::string& aname,int num){create(aname,num);}
    
    //accessors
    const std::string& get_name()const {return name;}
    int get_total_copies() const{return total_copies;}
    int get_avail_copies() const{return available_copies;}
    int get_checked_out() const{return total_copies-available_copies;}
    
    //modifiers
    void set_total_copies(int n){total_copies = n;}
    void set_avail_copies(int n){available_copies = n;}
    void shipped();
    
    //checking functions
    bool available(){return available_copies;}
    bool checked_out(){return total_copies-available_copies;}
    
    
private:
    //private constructor functions
    void create();
    void create(const std::string& aname, int num);
    
    std::string name;
    int total_copies;
    int available_copies;
};


#endif
