#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();

//sorted automatically by the STL class. prints out by priting then popping
template <class T>
void pq_sort(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
             std::ostream &ostr, int &output_count) {
    output_count=0;
    // use the vector sort algorithm
    while(pq.size()!=0){
        ostr<<pq.top()<<std::endl;
        pq.pop();
        output_count++;
    }
}



//Mode function
template <class T>
void pq_mode(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
             std::ostream &ostr, int &output_count) {
    int current_count = 1;
    T mode;
    int mode_count = 0;
    T prev = pq.top();
    pq.pop();
    T current = pq.top();
    //while thers a value inside priority queue it loops
    while(pq.size()!=0){
        //if they are the same elements increment the count
        if(current == prev){
            current_count++;
        }
        //found new mode
        else if(current_count>=mode_count){
            mode = prev;
            mode_count = current_count;
            current_count=1;
        }
        else{
            current_count = 1;
        }
        prev = current;
        pq.pop();
        current = pq.top();
    }
    if(current_count>=mode_count){
        //last entry is a new mode
        mode = prev;
        mode_count = current_count;
    }
    //save the mode to the ouput
    output_count = 1;
    ostr<<mode<<"\n";
}

//function that finds the closeset pair
void pq_closest_pair(std::priority_queue<int,std::vector<int>, std::greater<int> > pq,
                     std::ostream &ostr, int &output_count) {
    //
    int num1 = pq.top();
    pq.pop();
    int num2 = pq.top();
    int diff = num2-num1;
    int best = diff;
    int result1 = num1;
    int result2 = num2;
    //loops while theres not elements in priority queue
    while(pq.size()!=0){
        num2 = pq.top();
        diff = num2-num1;
        //found new closest pair
        if(diff<best){
            best = diff;
            result1 = num1;
            result2 = num2;
        }
        num1 = num2;
        pq.pop();
    }
    output_count = 2;
    ostr<<result1<<std::endl;
    ostr<<result2<<std::endl;
}


//first sorted function
template <class T>
void pq_first_sorted(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
                     std::ostream &ostr, int &output_count, int optional_arg) {
    for(int i=0;i<optional_arg;i++){
        ostr<<pq.top()<<std::endl;
        pq.pop();
        output_count++;
    }
}




void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

    if (type == "string") {
        std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            pq.push(s);
            input_count++;
        }
        if (operation == "sort"){
            pq_sort(pq,ostr,output_count);
            
        }
        else if (operation == "mode"){
            pq_mode(pq,ostr,output_count);
            
        }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted"){
            pq_first_sorted(pq,ostr,output_count,optional_arg);
            
        }
        else {
            std::cerr << "Error: Unknown operation: " << operation << std::endl;
            usage();
            exit(0);
        }
    }

    else {
        assert (type == "integer");
        std::priority_queue<int,std::vector<int>, std::greater<int> > pq;
        int v;
        input_count = 0;
        while (istr >> v) {
            pq.push(v);
            input_count++;
        }
        if(operation == "sort"){
            pq_sort(pq,ostr,output_count);
        }
        else if (operation == "mode"){
            pq_mode(pq,ostr,output_count);
        }
        else if (operation == "closest_pair"){
            pq_closest_pair(pq,ostr,output_count);
        }
        else if (operation == "first_sorted"){
            pq_first_sorted(pq,ostr,output_count,optional_arg);
        }
        // "longest_substring" not available for integers
        else {
            std::cerr << "Error: Unknown operation: " << operation << std::endl;
            usage();
            exit(0);
        }
    }
}
