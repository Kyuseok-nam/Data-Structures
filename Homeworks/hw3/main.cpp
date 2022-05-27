#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>

#include "jagged_array.h"

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO StudentTests() and MoreTests()
//

// helper testing functions
void SimpleTest();
void StudentTests();
void MoreTests();
void BatchTest(const char* filename, int num);

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO main()
//
int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    std::cout << "Simple test completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;    
    MoreTests();
    std::cout << "More tests completed." << std::endl;    
  } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << std::endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}


//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO SimpleTest()
//
void SimpleTest() {

  JaggedArray<char> ja(7);

  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.isPacked() == false);

  // intialize the values in the JaggedArray
  ja.addElement(1,'a');
  ja.addElement(1,'b');
  ja.addElement(1,'c');
  ja.addElement(3,'d');
  ja.addElement(3,'e');
  ja.addElement(6,'f');

  // verify data is correct
  std::cout << "STARTS UNPACKED" << std::endl;
  assert (!ja.isPacked());
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // pack the structure and verify data is correct
  ja.pack();
  std::cout << "CONVERT TO PACKED" << std::endl;
  assert (ja.isPacked());
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // unpack the structure and verify data is correct
  ja.unpack();
  std::cout << "CONVERT BACK TO UNPACKED" << std::endl;
  assert (!ja.isPacked());
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // add 'g' and verify
  ja.addElement(3,'g');
  std::cout << "ADDED G" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 7);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // remove 'b' and verify
  ja.removeElement(1,1);
  std::cout << "REMOVED B" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 2);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // clear
  ja.clear();
  std::cout << "CLEARED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 0);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 0);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 0);

  // note...  the JaggedArray destructor is implicitly called for the
  // variable 't' when we leave the function and it goes out of scope
}


//
// NOTE: ADD YOUR OWN TESTS TO THIS FUNCTION
//
void StudentTests() {
    
    //testing Jagged array of type int
    JaggedArray<int> a(7);
    //error checkings
    a.addElement(-1,3);
    //error checking
    //exit(1) does not call a destructor and causes memory leak
    //confirmed by prof. that to just comment it out
    //a.getElement(10,2);
    
    a.addElement(1,1);
    a.addElement(1,2);
    a.addElement(1,3);
    a.addElement(3,4);
    a.addElement(3,5);
    a.addElement(6,6);
    
    std::cout << "STARTS UNPACKED" << std::endl;
    assert (!a.isPacked());
    a.print();
    assert (a.numBins() == 7);
    assert (a.numElements() == 6);
    assert (a.numElementsInBin(0) == 0);
    assert (a.numElementsInBin(1) == 3);
    assert (a.numElementsInBin(2) == 0);
    assert (a.numElementsInBin(3) == 2);
    assert (a.numElementsInBin(4) == 0);
    assert (a.numElementsInBin(5) == 0);
    assert (a.numElementsInBin(6) == 1);
    assert (a.getElement(1,0) == 1);
    assert (a.getElement(1,1) == 2);
    assert (a.getElement(1,2) == 3);
    assert (a.getElement(3,0) == 4);
    assert (a.getElement(3,1) == 5);
    assert (a.getElement(6,0) == 6);
    
    a.pack();
    std::cout << "CONVERT TO PACKED" << std::endl;
    assert (a.isPacked());
    a.print();
    assert (a.numBins() == 7);
    assert (a.numElements() == 6);
    assert (a.numElementsInBin(0) == 0);
    assert (a.numElementsInBin(1) == 3);
    assert (a.numElementsInBin(2) == 0);
    assert (a.numElementsInBin(3) == 2);
    assert (a.numElementsInBin(4) == 0);
    assert (a.numElementsInBin(5) == 0);
    assert (a.numElementsInBin(6) == 1);
    assert (a.getElement(1,0) == 1);
    assert (a.getElement(1,1) == 2);
    assert (a.getElement(1,2) == 3);
    assert (a.getElement(3,0) == 4);
    assert (a.getElement(3,1) == 5);
    assert (a.getElement(6,0) == 6);
    
    //Jagged array of type string
    JaggedArray<std::string> ja(7);
    
    ja.addElement(1,"111");
    ja.addElement(1,"222");
    ja.addElement(1,"333");
    ja.addElement(3,"444");
    ja.addElement(3,"555");
    ja.addElement(6,"666");
    
    std::cout << "STARTS UNPACKED" << std::endl;
    assert (!ja.isPacked());
    ja.print();
    assert (ja.numBins() == 7);
    assert (ja.numElements() == 6);
    assert (ja.numElementsInBin(0) == 0);
    assert (ja.numElementsInBin(1) == 3);
    assert (ja.numElementsInBin(2) == 0);
    assert (ja.numElementsInBin(3) == 2);
    assert (ja.numElementsInBin(4) == 0);
    assert (ja.numElementsInBin(5) == 0);
    assert (ja.numElementsInBin(6) == 1);
    assert (ja.getElement(1,0) == "111");
    assert (ja.getElement(1,1) == "222");
    assert (ja.getElement(1,2) == "333");
    assert (ja.getElement(3,0) == "444");
    assert (ja.getElement(3,1) == "555");
    assert (ja.getElement(6,0) == "666");
}


//
// NOTE: UNCOMMENT THESE TEST CASES AS YOU DEBUG YOUR IMPLEMENTATION
//
void MoreTests() {

  
  // test the copy constructor
  JaggedArray<char> a(5);
  a.addElement(1,'t');
  a.addElement(4,'f');
  a.addElement(3,'e');
  a.addElement(1,'s');
  a.addElement(4,'o');
  a.addElement(0,'q');
  assert (a.getElement(1,1) == 's');
  assert (a.numElements() == 6);
  a.print();
  JaggedArray<char> b(a);
  assert (b.numElements() == a.numElements());
  assert (b.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (b.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (b.getElement(i,j) == a.getElement(i,j));
    }
  }
  b.print();
  std::cout << "copy constructor test finished" << std::endl;
  

  
  // test the assignment operator  
  JaggedArray<char> c(12);
  c.addElement(3,'o');
  c.addElement(9,'t');
  c.addElement(1,'s');
  c.addElement(0,'e');
  c.addElement(3,'n');
  assert (c.numBins() == 12);
  c.print();
  c = a;
  assert (c.numElements() == a.numElements());
  assert (c.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (c.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (c.getElement(i,j) == a.getElement(i,j));
    }
  }
  c.print();
  std::cout << "assignment operator test finished" << std::endl;
  

  
  // verify edits happen to the right object
  b.clear();
  assert (b.numElements() == 0);
  assert (a.numElements() == 6);
  assert (a.numBins() == 5);
  assert (b.numBins() == 5);
  a.removeElement(0,0);
  assert (c.numElements() == a.numElements()+1);
  assert (c.numBins() == a.numBins());
  assert (c.numElementsInBin(0) == a.numElementsInBin(0)+1);
  c.addElement(3,'x');
  assert (c.numElements() == a.numElements()+2);
  assert (c.numElementsInBin(3) == a.numElementsInBin(3)+1);
  std::cout << "edits happen to the correct operator test finished" << std::endl;
  

  
  // test the copy constructor on a packed object
  JaggedArray<char> d(3);
  d.addElement(2,'h');
  d.addElement(1,'q');
  d.addElement(2,'b');
  d.addElement(0,'u');
  d.addElement(1,'d');
  d.addElement(2,'i');
  d.addElement(2,'o');
  assert (d.numBins() == 3);
  assert (d.numElements() == 7);
  assert (d.numElementsInBin(0) == 1);
  assert (d.numElementsInBin(1) == 2);
  assert (d.numElementsInBin(2) == 4);
  assert (d.getElement(0,0) == 'u');
  assert (d.getElement(1,0) == 'q');
  assert (d.getElement(1,1) == 'd');
  assert (d.getElement(2,0) == 'h');
  assert (d.getElement(2,1) == 'b');
  assert (d.getElement(2,2) == 'i');
  assert (d.getElement(2,3) == 'o');
  d.print();
  d.pack();
  assert (d.isPacked());
  d.print();
  JaggedArray<char> e(d);
  assert (e.isPacked());
  e.print();
  assert (e.numBins() == 3);
  assert (e.numElements() == 7);
  assert (e.numElementsInBin(0) == 1);
  assert (e.numElementsInBin(1) == 2);
  assert (e.numElementsInBin(2) == 4);
  assert (e.getElement(0,0) == 'u');
  assert (e.getElement(1,0) == 'q');
  assert (e.getElement(1,1) == 'd');
  assert (e.getElement(2,0) == 'h');
  assert (e.getElement(2,1) == 'b');
  assert (e.getElement(2,2) == 'i');
  assert (e.getElement(2,3) == 'o');  
  e.print();
  std::cout << "packed copy constructor tested" << std::endl;
  

  
  // test the assignment operator on a packed structure
  a.pack();
  assert (a.isPacked());
  b = a;
  assert (b.isPacked());
  assert (b.numElements() == a.numElements());
  assert (b.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (b.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (b.getElement(i,j) == a.getElement(i,j));
    }
  }
  b.print();
  std::cout << "packed assignment operator tested" << std::endl;
  

  
  assert (a.isPacked());
  assert (b.isPacked());
  assert (!c.isPacked());
  assert (d.isPacked());
  assert (e.isPacked());
  assert (e.isPacked());
  // on exit, this function will test both the packed (a,b,d,e,&f) and unpacked (c)
  // versions of the destructor
  
}



//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD NOT CONTAIN CHANGES TO BatchTest()
//

// Batch test will repeatedly load & process a file with JaggedArray
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int b,i;

    // create the initial JaggedArray
    istr >> token >> b;
    assert (token == "create");
    // note: here we explicitly allocate memory for the JaggedArray object
    JaggedArray<char> *ja = new JaggedArray<char>(b);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "addElement") {
        istr >> b >> c;
        ja->addElement(b,c);
      } else if (token == "getElement") {
        istr >> b >> i >> c;
        char c2 = ja->getElement(b,i);
        assert (c == c2);
      } else if (token == "removeElement") {
        istr >> b >> i >> c;
	char c2 = ja->getElement(b,i);
        assert (c == c2);
	ja->removeElement(b,i);
      } else if (token == "pack") {
        ja->pack();
      } else if (token == "unpack") {
        ja->unpack();
      } else if (token == "clear") {
        ja->clear();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    // print out the jagged array contents at the end of the last iteration
    if (iters == 0) {
      if (ja->isPacked()) {
	ja->unpack();
      }
      ja->print();
      ja->pack();
      ja->print();
    }

    // Because the JaggedArray memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete ja;
  }

}


