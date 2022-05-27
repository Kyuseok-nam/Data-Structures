HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  < Kyuseok Nam >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Siddha / lecture notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 10 hours >



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)

Number of different costumes in shop: n
Maximum number of copies of a costume: m
Customers who visit the shop: c
Length of customer name: k


Addcostume: accessing costume_shop and changing the value is O(log n) and same for rent O(log n)
	    which then for the function is O(2log n) which is just O(log n).


rentCostume: people.find() is O(log c), custome_shop.find() is O(log n). rent[] is O(log n) and then 
	push_back in that list is just O(1). Line 102 where std::find is used to search the list 
	inside rent map is worst case O(c) So in total this function 
	is just O(log c + log n + c) worst case

Lookup: the order notation for the first 2 .find() is O(log n + log n) = O(log n).
	Worst case it then iterates through the value of rent map which is O(c).
	so worst case order notation for this function is O(log n + c)
       

reorder_name: this helper function has order notation of O(k)

PrintPeople: worst case it iterates through people map. Which is O(c) and then use the reorder_name 
	    function each time which is O(k). So the order notation of this function is O(c*k)
 

EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






