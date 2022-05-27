HOMEWORK 3: JAGGED ARRAY


NAME:  < Kyuseok Nam >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Chitao, willil14, slowij2 / lecture notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 20 hours >



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

//analyzing for worst case scenario

numElements
 unpacked: O(1)
 packed:O(1)

numBins
 unpacked: O(1)
 packed: O(1)

numElementsInBin
 unpacked: O(1)
 packed: O(1)

getElement
 unpacked: O(1)
 packed: O(1)

isPacked
 unpacked: O(1)
 packed: O(1)

clear
 unpacked: O(bk)
 packed: O(1)

addElement
 unpacked: O(bk)  
 packed: O(1)

removeElement
 unpacked: O(k)
 packed: O(1)

pack
 unpacked: O(bk)
 packed: O(1)

unpack
 unpacked: O(1)
 packed: O(bk)

print 
 unpacked: O(bk)
 packed: O(b+k) can't determine which is going to be bigger between b or k

constructor w/ integer argument
 unpacked: O(b)
 packed: NA

copy constructor
 unpacked: O(bk)
 packed: O(b+e) can't determine which is going to be bigger between b or k

destructor
 unpacked: O(bk) delete has a time constant of O(k) so its k *b 
 packed: O(b+e) can't determine which is going to be bigger between b or k

assignment operator
 unpacked: O(bk+bk) = O(bk)
 packed: O(2(b+e)) = O(b+e)




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


