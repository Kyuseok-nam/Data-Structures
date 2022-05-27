#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>


// Info on command line arguments
void usage() {
  std::cerr << "Usage: <executable_name> <data structure> <operation> <type> <optional_arg>  < input_file   > output_file" << std::endl;
  std::cerr << "Usage:    <data structure> = vector, list, bst, priority_queue, hash_table" << std::endl;
  std::cerr << "Usage:    <operation>      = sort, remove_duplicates, mode, closest_pair, first_sorted, or longest_substring" << std::endl;
  std::cerr << "Usage:    <type>           = integer or string" << std::endl;
  std::cerr << "Usage:    integer optional_arg required for first_sorted" << std::endl;
  exit(1);
}


// prototypes of the functions that perform the operations
void vector_test(const std::string &operation, const std::string &type, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count, int optional_arg);
void list_test(const std::string &operation, const std::string &type, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count, int optional_arg);
void bst_test(const std::string &operation, const std::string &type, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count, int optional_arg);
void priority_queue_test(const std::string &operation, const std::string &type, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count, int optional_arg);
void hash_table_test(const std::string &operation, const std::string &type, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count, int optional_arg);


// ===================================================================================================

int main(int argc, char* argv[]) {

  // timing mechanism
  clock_t before_operation, after_operation;

  // parse the command line arguments
  if (argc < 4 || argc > 5) {
    std::cerr << "Error: wrong number of arguments." << std::endl;
    usage();
  }
  std::string data_structure = argv[1];
  std::string operation = argv[2];
  std::string type = argv[3];
  int optional_arg = 0;

  if (operation != "sort" && operation != "remove_duplicates" && operation != "mode" &&
      operation != "closest_pair" && operation != "first_sorted" && operation != "longest_substring") {
    std::cerr << "Error: unknown operation - " << operation << std::endl;
    usage();
  }
  
  if (operation == "first_sorted") {
    if (argc != 5) {
      std::cerr << "Error: wrong number of arguments." << std::endl;
      usage();
    }
    optional_arg = std::stoi(argv[4]);
    if (optional_arg < 1) {
      usage();
    }
  } else {
    if (argc != 4) {
      std::cerr << "Error: wrong number of arguments." << std::endl;
      usage();
    }
  }
  
  // mark the time before we start
  before_operation = clock();

  int input_count;
  int output_count;
  
  // perform the operation
  if (data_structure == "vector") 
    vector_test(operation,type,std::cin,std::cout,input_count,output_count,optional_arg);
  else if (data_structure == "list")
    list_test(operation,type,std::cin,std::cout,input_count,output_count,optional_arg);
  else if (data_structure == "bst")  // STL set or map
    bst_test(operation,type,std::cin,std::cout,input_count,output_count,optional_arg);
  else if (data_structure == "priority_queue")
    priority_queue_test(operation,type,std::cin,std::cout,input_count,output_count,optional_arg);
  else if (data_structure == "hash_table")  // STL unordered_set or unordered_map
    hash_table_test(operation,type,std::cin,std::cout,input_count,output_count,optional_arg);
  else {
    std::cerr << "Error: unknown data structure: " << data_structure << std::endl;
    usage();
    exit(0);
  }

  // mark the time once we are done
  after_operation = clock();

  // print statistics
  double operation_time = double(after_operation-before_operation)/CLOCKS_PER_SEC;
  std::cerr << "operation time:     " << operation_time << std::endl;
  std::cerr << "input/output ratio: " << input_count << ":" << output_count << std::endl;
  return 0;
}

// ===================================================================================================
