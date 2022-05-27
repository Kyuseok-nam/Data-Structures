// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "DVD.h"
#include "Customer.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<DVD> inventory_type;
typedef std::list<Customer> customers_type;
typedef std::list<std::string> preference_type;


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);
customers_type::iterator find_customer(customers_type& customers,const std::string& name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
    exit(1);
}


int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 5) {
        usage(argv[0]);
    }

    // open input and output file streams
    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
        usage(argv[0]);
    }
    std::ofstream ostr(argv[2]);
    if (!ostr) {
        std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
        usage(argv[0]);
    }

    // optional parameters for extra credit
    bool use_improved_algorithm = false;
    bool print_analysis = false;
    for (int i = 3; i < argc; i++) {
        if (std::string(argv[i]) == "--improved") {
            use_improved_algorithm = true;
        } else if (std::string(argv[i]) == "--analysis") {
            print_analysis = true;
        } else {
            usage(argv[0]);
        }
    }


    // stores information about the DVDs
    inventory_type inventory;
    // stores information about the customers
    customers_type customers;


  // read in and handle each of the 8 keyword tokens
    std::string token;
    while (istr >> token) {
        if (token == "dvd") {
            std::string dvd_name = read_dvd_name(istr);
            int copies;
            istr >> copies;
            
            DVD vid(dvd_name,copies);
            //search for DVD in inventory
            inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
            //if exists in inventory increment total and avail copies
            if(i_itr != inventory.end()){
                i_itr->set_total_copies(i_itr->get_total_copies()+copies);
                i_itr->set_avail_copies(i_itr->get_avail_copies()+copies);
            }
            //if it doesn't exist in inventory add it
            else{
                inventory.push_back(vid);
            }
            if(copies==1){
                ostr<<copies<<" copy of ";
            }
            else{
                ostr<<copies<<" copies of ";
            }
            ostr<<dvd_name<<" added"<<std::endl;
            
            /* YOU MUST FINISH THIS IMPLEMENTATION */
      
        } else if (token == "customer") {
            std::string customer_name = read_customer_name(istr);
            int num_movies;
            istr >> num_movies;
            
            //search to see if customer already exists
            customers_type::iterator c_itr = find_customer(customers,customer_name);
            if(c_itr!=customers.end()){
                ostr<<"WARNING: Already have a customer named ";
                ostr<<customer_name<<std::endl;
                //loop through to move the istr even if customer doesn't exist
                for (int i = 0; i < num_movies; i++){
                    std::string dvd_name = read_dvd_name(istr);
                }
            }
            
            //if that customer does not exist add to customers
            else if(c_itr == customers.end()){
                Customer person(customer_name);
                //add preference of that customer
                for (int i = 0; i < num_movies; i++) {
                    std::string dvd_name = read_dvd_name(istr);
                    //if that dvd already exist in prefernece
                    if(person.check_preference_exist(dvd_name)){
                        ostr<<"WARNING: Duplicate movie ";
                        ostr<<dvd_name<<" on preference list!"<<std::endl;
                        continue;
                    }
                    //check if dvd exist in inventory
                    inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
                    //if dvd doesn't exist print warning
                    if(i_itr==inventory.end()){
                        ostr<<"WARNING: No movie named ";
                        ostr<<dvd_name<<" in the inventory"<<std::endl;
                        continue;
                    }
                    person.add_preference(dvd_name);
                }
                ostr<<"new customer: "<<customer_name<<std::endl;
                customers.push_back(person);
            }
      /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "ship") {
            shipping_algorithm(inventory,customers,ostr);
      
        } else if (token == "return_oldest") {
            std::string customer_name = read_customer_name(istr);
            customers_type::iterator c_itr = find_customer(customers,customer_name);
            //if customer doens't exist
            if(c_itr == customers.end()){
                ostr<<"WARNING: No customer named "<<customer_name<<std::endl;
            }
            //if customer has no vidoe
            else if(c_itr->num_possession()==0){
                ostr<<"WARNING: "<<customer_name;
                ostr<<" has no DVDs to return!"<<std::endl;
            }
            //returns oldest video
            else{
                std::string dvd_name;
                dvd_name = c_itr->return_oldest();
                inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
                int num = i_itr->get_avail_copies();
                i_itr->set_avail_copies(num+1);
                ostr<<customer_name<<" returns "<<dvd_name<<std::endl;
            }
            
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "return_newest") {
            std::string customer_name = read_customer_name(istr);
            customers_type::iterator c_itr = find_customer(customers,customer_name);
            //if customer doesn't exist
            if(c_itr == customers.end()){
                ostr<<"WARNING: No customer named "<<customer_name<<std::endl;
            }
            //if the customer don't have vidoes
            else if(c_itr->num_possession()==0){
                ostr<<"WARNING: "<<customer_name;
                ostr<<" has no DVDs to return!"<<std::endl;
            }
            //return the newest video
            else{
                std::string dvd_name;
                dvd_name = c_itr->return_newest();
                inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
                int num = i_itr->get_avail_copies();
                i_itr->set_avail_copies(num+1);
                ostr<<customer_name<<" returns "<<dvd_name<<std::endl;
            }
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "print_customer") {
            std::string customer_name = read_customer_name(istr);
            customers_type::iterator c_itr = find_customer(customers,customer_name);
            //if customer doesn't exist
            if(c_itr == customers.end()){
                ostr<<"WARNING: No customer named "<<customer_name<<std::endl;
            }
            //if customer exists print information
            else{
                ostr<<customer_name<<" has ";
                if(c_itr->num_possession()==0){
                    ostr<<"no"<<" movies"<<std::endl;
                }
                else if(c_itr->num_possession()==1){
                    ostr<<c_itr->num_possession()<<" movie:"<<std::endl;
                }
                else{
                    ostr<<c_itr->num_possession()<<" movies:"<<std::endl;
                }
                c_itr->print_possession(ostr);
                if(!c_itr->preference_list_empty()){
                    c_itr->print_preference(ostr);
                }
            }
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "print_dvd") {
            std::string dvd_name = read_dvd_name(istr);
            inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
            //if dvd doesn't exist in inventory
            if(i_itr==inventory.end()){
                ostr<<"WARNING: No movie named ";
                ostr<<dvd_name<<" in the inventory"<<std::endl;
            }
            //if dvd does exist in inventory print information
            else{
                ostr<<dvd_name<<":"<<std::endl;
                if(i_itr->checked_out()){
                    ostr<<"  "<<i_itr->get_checked_out();
                    if(i_itr->get_checked_out()==1){
                        ostr<<" copy checked out";
                    }
                    else{
                        ostr<<" copies checked out";
                    }
                }
                if(i_itr->available()&&i_itr->checked_out()){
                    ostr<<" and "<<i_itr->get_avail_copies();
                    if(i_itr->get_avail_copies()==1){
                        ostr<<" copy available";
                    }
                    else{
                        ostr<<" copies available";
                    }
                }
                if(i_itr->available()&&(!i_itr->checked_out())){
                    ostr<<"  "<<i_itr->get_avail_copies();
                    if(i_itr->get_avail_copies()==1){
                        ostr<<" copy available";
                    }
                    else{
                        ostr<<" copies available";
                    }
                }
                ostr<<std::endl;
            }
            
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "add_preference") {
            std::string customer_name = read_customer_name(istr);
            std::string dvd_name = read_dvd_name(istr);
            //search for dvd and customer in inventory and customers
            customers_type::iterator c_itr = find_customer(customers,customer_name);
            inventory_type::iterator i_itr = find_DVD(inventory,dvd_name);
            //if customer doesn't exist print warning
            if(c_itr==customers.end()){
                ostr<<"WARNING: No customer named "<<customer_name<<std::endl;
            }
            //if dvd doesn't exist in inventory print warning
            else if(i_itr==inventory.end()){
                ostr<<"WARNING: No movie named "<<dvd_name;
                ostr<<" in the inventory"<<std::endl;
            }
            //if that customer already has that dvd in preference list print warning
            else if(c_itr->check_preference_exist(dvd_name)){
                ostr<<"WARNING: "<<customer_name<<" already has ";
                ostr<<dvd_name<<" on his/her preference list!"<<std::endl;
            }
            //if that customer already possess that dvd print warning
            else if(c_itr->in_possession(dvd_name)){
                ostr<<"WARNING: "<<customer_name<<" currently has ";
                ostr<<dvd_name<<"!"<<std::endl;
            }
            //if no errors then add to preference
            else{
                c_itr->add_preference(dvd_name);
            }
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else {
            std::cerr << "ERROR: Unknown token " << token << std::endl;
            exit(1);
        }
    }
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
    std::string first, last;
    istr >> first >> last;
    return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
    std::string token;
    istr >> token;
    assert (token[0] == '"');
    std::string answer = token;
    while (answer[answer.size()-1] != '"') {
        istr >> token;
        answer += " " + token;
    }
    return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
    for (inventory_type::iterator inventory_itr = inventory.begin();
         inventory_itr != inventory.end(); inventory_itr++) {
        if (inventory_itr->get_name() == dvd_name) {
            return inventory_itr;
        }
    }
    // if the DVD is not found, return the .end() iterator
    return inventory.end();
}

//helper function to find customer from customers
customers_type::iterator find_customer(customers_type& customers,const std::string& name){
    for (customers_type::iterator c_itr = customers.begin();
         c_itr != customers.end(); c_itr++) {
        if (c_itr->get_name() == name) {
            return c_itr;
        }
    }
    //if not found return end iterator
    return customers.end();
}



// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {

   

     

    ostr << "Ship DVDs" << std::endl;

    // Loop over the customers in priority order
    //
    // Note that we edit the customers list as we go, to add customers
    // to the back of the list if they receive a DVD.  This allows a
    // customer to receive multiple DVDs in one shipment cycle, but only
    // after all other customers have had a chance to receive DVDs.
    //
    customers_type::iterator customer_itr = customers.begin();
    while (customer_itr != customers.end()) {

        // skip this customer if they already have 3 movies or if their
        // preference list is empty (no outstanding requests)
        if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
            // move on to the next customer
            customer_itr++;
            continue;
        }

        // a helper flag variable
        bool sent_dvd = false;
 
        // loop over the customer's preferences
        const preference_type &preferences = customer_itr->get_preferences();
        for (preference_type::const_iterator preferences_itr = preferences.begin();
             preferences_itr != preferences.end(); preferences_itr++) {

            // locate this DVD in the inventory
            inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
            //if dvd is in inventory and available and that customer don't have it
            //then ship it to that customer
            if (inventory_itr != inventory.end() && inventory_itr->available()
                && (!customer_itr->in_possession(*preferences_itr))) {

                // if the DVD is available, ship it to the customer!
                ostr << "  " << customer_itr->get_name() << " receives " ;
                ostr<< *preferences_itr << std::endl;
                inventory_itr->shipped();
                customer_itr->receives(*preferences_itr);
        
                // move this customer to the back of the priority queue
                // they will get a chance to receive another DVD, but only
                // after everyone else gets a chance
                customers.push_back(*customer_itr);
                customer_itr = customers.erase(customer_itr);

                // after setting the flag to true, leave the iteration over preferences
                sent_dvd = true;
                break;
            }
        }

        // if no DVD was sent to this customer, then we move on to the next customer
        // (do not change this customer's priority for tomorrow's shipment)
        if (!sent_dvd) {
            customer_itr++;
        }
    }
}

// ==================================================================
