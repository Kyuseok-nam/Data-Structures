#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>


// ================================================================= 

// Info on command line arguments
void usage() {
  std::cerr << "Usage: <executable_name> <type> <input count> <min_length> <max_length>  >  output_file" << std::endl;
    exit(1);
}

// =================================================================

// Create a random string of the specified length for testing
std::string random_string(int min_length, int max_length) {
  // choose the length of this string
  int length = min_length;
  if (max_length > min_length) {
    length += rand()%(max_length-min_length+1);
  }
  // generate the string
  std::string s = "";
  for (int i = 0; i < length; i++) {
    char c = 'a' + rand()%26;
    s += c;
  }
  return s;
}

// =================================================================

// Create a random integer of the specified length for testing
std::string random_integer(int min_length, int max_length) {
  // generate generate digits of the specified maximum length
  std::string s = "";
  for (int i = 0; i < max_length; i++) {
    char c = '0' + rand()%10;
    if (s.size() == 0 && c == '0') {
      // skip leading zeroes
    } else {
      s += c;
    }
  }
  // special case for all leading zeros == zero
  if (s == "") {
    s = "0";
  }
  if (int(s.size()) < min_length) {
    // recurse if we aren't the requested minimum length
    return random_integer(min_length,max_length);
  } else {
    return s;
  }
}

// =================================================================

int main(int argc, char* argv[]) {

  // parse the command line arguments
  if (argc != 5) {
    std::cerr << "Error: wrong number of arguments." << std::endl;
    usage();
  }
  std::string type = argv[1];
  int input_count = atoi(argv[2]);
  int min_length = atoi(argv[3]);
  int max_length = atoi(argv[4]);
  // more argument error checking
  if (type != "string" && type != "integer") {
    std::cerr << "Error: type must be string or integer." << std::endl;
    usage();
  }
  if (min_length < 1 || min_length > max_length) {
    std::cerr << "Error: invalid min/max length values." << std::endl;
    usage();
  }
  
  // repeatable randomness (fixed seed)
  srand(37);
  // using the time as a seed
  //srand(time(0));

  for (int i = 0; i < input_count; i++) {
    if (type == "string") {
      std::cout << random_string(min_length,max_length) << "\n";
    } else {
      assert (type == "integer");
      std::cout << random_integer(min_length,max_length) << "\n";
    }
  }
    
  return 0;
}

// =================================================================
