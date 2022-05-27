#ifndef Customer_h_
#define Customer_h_
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>

typedef std::list<std::string> preference_type;

class Customer{
public:
    //constructor
    Customer();
    Customer(const std::string& aname){name = aname;}

    
    //accessors
    std::string get_name(){return name;}
    const std::list<std::string>& get_preferences(){return preference;}
    int num_possession(){return possession.size();}
    
    //modifers
    void add_preference(const std::string& pre);
    std::string return_oldest();
    std::string return_newest();
    
    
    //checking functions
    bool check_preference_exist(const std::string& name);
    bool has_max_num_movies();
    bool preference_list_empty();
    bool in_possession(const std::string& dvd);
    
    void receives(const std::string& dvd);
    
    //print functions
    void print_possession(std::ostream &ostr);
    void print_preference(std::ostream &ostr);
    
private:
    std::string name;
    std::list<std::string> preference;
    std::list<std::string> possession;
};

#endif
