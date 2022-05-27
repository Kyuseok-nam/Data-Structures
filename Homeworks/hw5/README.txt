HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Kyuseok Nam >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Fu,batisj, zhangz22 / lecture notes, Submitty discussions >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 10 hours >



TESTING & DEBUGGING STRATEGY:
Work step by step. If the something fails find out where or which function the error
occurred. draw diagrams of the code that I wrote and figure out where it could have 
Went wrong. Print the elements to check and fix the code.   



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

n = number of nodes
e = number of elements

The running time is calculated for the worst case 

Node copy constructor: running time:O(e) loops through elements and copy it
			memory usage: O(e) creates a new node with e elements

All Iterator member functions: running time: O(1) just returns an element or move 
					     pointer
				memory usage: NA 

Assignment operator: running time: O(ne + n) = O(ne) worst case it destroys list 
				   which is O(n) then copies it which is O(ne)
		     memory usage: O(ne) creates n nodes with e elements inside

Copy constructor: running time:O(ne) loops through each node then copy each elements
		  memory usage:O(ne) create n nodes with e elements

Destructor: running time: O(n) loops through each node and deletes it
	     memory usage: NA

size():running time: O(1) just returns the size
	memory usage: NA

empty(): running time: O(1)just returns a Boolean if its empty or not
	 memory usage: NA

clear(): running time: O(n) loops through each node and deletes it
	 memory usage: NA

front(): running time: O(1) just returns the front element
    	 memory usage: NA

back(): running time: O(1) just returns the last element
	memory usage: NA

push_front(): running time: O(e) worst case it loops through the elements 
			    to shift it and add the new element
	      memory usage: O(e) for worst case when a new node is created

pop_front(): running time: O(e) worst case it loops through elements and shift
				it left to delete the first element
	     memory usage: NA

push_back(): running time: O(1) it only 
  	     memory usage: O(e) worst case it creates a new node which has an array
				of size e

pop_back(): running time: O(1) it either deletes node which is o(1) or just decrease
			  nuum elements;
	    memory usage: NA

print(): running time: O(ne) loops through each node and then loop through each 
		       element to print it out
	 memory usage: NA

erase(): running time: O(e) worst case it loops through elements and shift it 
	 memory usage: NA

insert(): running time: O(e) it loops through elements to shift it and adds the new
	   		element
	  memory usage: O(e) for worst case. It creates a new node if the node is 
	 		already full

begin(): running time: O(1) returns the iterator that points to the first element
	 memory usage:  NA

end(): running time: O(1)returns the iterator that points to the last element
 	memory usage: NA


For insert, erase, push front, and pop front functions Unrolled list has a running 
Time of O(e) while STL list and ds list has O(1). Which is slower. However considering in this case where e = 6. Its not that much difference in the actual 
Running time. 


For the function to be inefficient it should have a running time of 
O(n^2) however there are no function with a run time with that. Which 
Shows that my functions could be said to be efficient I think. 

The average number of elements is e.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


