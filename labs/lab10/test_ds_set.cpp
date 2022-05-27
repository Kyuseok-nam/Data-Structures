#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
        << "The indentation is proportional to the depth of the node\n"
        << "so that the value stored at the root is the only value printed\n"
        << "without indentation.  Also, for each node, the right subtree\n"
        << "can be found above where the node is printed and indented\n"
        << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Checkpoints 2 & 3
  // Write code to test the forwards & backwards iterators!
    std::cout<<"checkpoint 2:"<<std::endl;
    ds_set<int> set5;
    set5.insert(8);
    set5.insert(4);
    set5.insert(12);
    set5.insert(2);
    set5.insert(6);
    set5.insert(10);
    set5.insert(14);
    set5.insert(1);
    set5.insert(3);
    set5.insert(5);
    set5.insert(7);
    set5.insert(9);
    set5.insert(11);
    set5.insert(13);
    set5.insert(15);
    set5.print_as_sideways_tree( std::cout );
    
    
    
    std::cout<<"checkpoint 3"<<std::endl;
    ds_set<int>::iterator itr = set5.begin();
    for(;itr!=set5.end();itr++){
        std::cout<<*itr<<std::endl;
    }
    















  return 0;
}
