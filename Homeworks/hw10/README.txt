HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Kyuseok >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< noola, bernha, allenw  / lecture notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 20 hours >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          | O(nlogn) |  O(n^2)  | O(nlogn) | O(nlogn) |O(f+nlogn)|O(l^2 n^2)|
| vector   |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(nlogn) |  O(n^2)  | O(nlogn) | O(nlogn) |O(f+nlogn)|O(l^2 n^2)|
| list     |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(nlogn) | O(nlogn) | O(nlogn) | O(nlogn) |O(f+nlogn)|O(l^2 n^2)|
| bst      |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(nlogn) |    x     | O(nlogn) | O(nlogn) |O(n+flogn)|    x     |
| pq       |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |    x     |    O(n)  |   O(n)   |    x     |    x     |O(l^2 n^2)|
| hash     |          |          |          |          |          |          |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >

---------------------------------------------------------------
Vector:

Sort 	10000 - 0.04s   	k = 1E-6
	20000 - 0.07s	k = 8.13E-7	
	50000 - 0.17s	k = 7.24E-7
	100000 - 0.35s 	k = 7E-7	
			Average k = 8.09E-7


Remove dups	10000 - 0.27s	k = 2.7E-9
		20000 - 1.01s	k = 2.53E-9
		50000 - 5.33s	k = 2.13E-9
		100000 - 17.58s	k = 1.76E-9
				Average k = 2.28E-9

Mode	10000 - 0.03s	k = 7.5E-7
	20000 - 0.05s	k = 5.8E-7
	50000 - 0.12s	k = 5.11E-7
	100000 - 0.23s	k = 4.6E-7
			Average k = 5.75E-7

Closest pair	10000 - 0.02s	k = 5E-7
		20000 - 0.04s	k = 4.65E-7
		50000 - 0.12s	k = 5.11E-7
		100000 - 0.23s	k = 4.6E-7
				Average k = 4.84E-7

First f sorted 	10000 - 0.02s	k = 5E-7
		20000 - 0.05s	k = 4.65E-7	
		50000 - 0.12s	k = 5.11E-7
		100000 - 0.23s	k = 4.6E-7
				Average k = 4.8E-7

Longest subset(l = 5) 	
		100 - 0.01s	k = 9.98E-7
		250 - 0.06s	k = 9.60E-7
		500 - 0.23s	k = 9.20E-7
		1000 - 0.91s 	k = 9.10E-7
				Average k = 9.47E-7

---------------------------------------------------------------
List:

Sort 	10000 - 0.05s	k = 1.25E-6
	20000 - 0.09s	k = 1.05E-6
	50000 - 0.23s	k = 9.79E-7
	100000 - 0.47s	k = 9.4E-7
			Average k = 1.05E-6
			
Remove dups	10000 - 1.80s	k = 1.8E-8
		20000 - 6.82s	k = 1.71E-8
		50000 - 38.76s	k = 1.55E-8
		100000 - 130.91s	k = 1.31E-8
				Average k = 1.59E-8

Mode	10000 - 0.03s	k = 7.5E-7
	20000 - 0.07s	k = 8.14E-7
	50000 - 0.16s	k = 6.81E-7
	100000 - 0.33s	k = 6.6E-7
			Average k = 7.26E-7

Closest pair	10000 - 0.03s	k = 7.5E-7
		20000 - 0.07s	k = 8.14E-7
		50000 - 0.16s	k = 6.81E-7
		100000 - 0.33s	k = 6.6E-7
				Average k = 7.26E-7

First f sorted	10000 - 0.03s	k = 7.5E-7
		20000 - 0.07s	k = 8.14E-7
		50000 - 0.15s	k = 6.38E-7
		100000 - 0.32s	k = 6.40E-7
				Average k = 7.10E-7

Longest subset 	100 - 0.02s	k = 1.99E-6
		250 - 0.08s	k = 1.28E-6
		500 - 0.30s	k = 1.20E-6
		1000 - 1.21s	k = 1.21E-6
				Average k = 1.42E-6

---------------------------------------------------------------
BST:

Sort 	10000 - 0.05s	k = 1.25E-6
	20000 - 0.09s	k = 1.05E-6
	50000 - 0.23s	k = 9.79E-7
	100000 - 0.45s	k = 9E-7
			Average k = 1.04E-6

Remove dups	10000 - 0.05s	k = 1.25E-6
		20000 - 0.09s	k = 1.05E-6
		50000 - 0.25s	k = 1.06E-6
		100000 - 0.47s	k = 9.4E-7
				Average k = 1.075E-6

Mode 	10000 - 0.03s	k = 7.5E-7
	20000 - 0.06s	k = 6.98E-7
	50000 - 0.16s	k = 6.81E-7
	100000 - 0.33s	k = 6.6E-7
			Average k = 6.97E-7
	

Closest pair	10000 - 0.03s	k = 7.5E-7
		20000 - 0.06s	k = 6.98E-7
		50000 - 0.16s	k = 6.81E-7
		100000 - 0.37s	k = 7.4E-7
				Average k = 7.17E-7

First f sorted	10000 - 0.03s	k = 7.5E-7
		20000 - 0.06s	k = 6.98E-7
		50000 - 0.16s	k = 6.81E-7
		100000 - 0.33s	k = 6.6E-7
				Average k = 6.97E-7

Longest subset	100 - 0.02s	k = 1.99E-6
		250 - 0.001s	k = 1.60E-8
		500 - 0.002s	k = 8.00E-9
		1000 - 0.005s	k = 5.00E-9
				Average k = 5.05E-7


---------------------------------------------------------------
Priority Queue:

Sort 	10000 - 0.04s	k = 1E-6
	20000 - 0.09s	k = 1.05E-6
	50000 - 0.21s	k = 8.94E-7
	100000 - 0.44s	k = 8.8E-7
			Average k = 9.56E-7


Remove dups - infeasible

Mode	10000 - 0.03s	k = 7.5E-7
	20000 - 0.06s	k = 6.98E-7
	50000 - 0.15s	k = 6.81E-7
	100000 - 0.30s	k = 6E-7
			Average k = 6.82E-7
	

Closest pair	10000 - 0.03s	k = 7.5E-7
		20000 - 0.06s	k = 6.98E-7
		50000 - 0.15s	k = 6.81E-7
		100000 - 0.30s	k = 6E-7
				Average k = 6.82E-7

First f sorted	10000 - 0.03s	k = 7.5E-7
		20000 - 0.05s	k = 5.81E-7
		50000 - 0.12s	k = 5.11E-7
		100000 - 0.23s	k = 4.6E-7
				Average k = 5.76E-7

Longest subset - infeasible

---------------------------------------------------------------
Hash Table:

Sort  - infeasible

Remove dups	10000 - 0.05s	k = 5E-6
		20000 - 0.09s	k = 4.5E-6
		50000 - 0.21s	k = 4.2E-6
		100000 - 0.40s	k = 4E-6
				Average k = 4.43E-6

Mode 	10000 - 0.03s	k = 3E-6
	20000 - 0.06s	k = 3E-6
	50000 - 0.15s	k = 3E-6
	100000 - 0.28s	k = 2.8E-6
			Average k = 2.95E-6

Closest pair - infeasible

First f sorted - infeasible

Longest subset	100 - 0.02s	k = 1.99E-6
		250 - 0.001s	k = 1.60E-8
		500 - 0.002s	k = 8.00E-9
		1000 - 0.004s	k = 4.00E-9
				Average k = 5.05E-7

DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


< insert your discussion of the results, including your answers to the
above questions >

	The measurements and overall performance did match what I predicted before running 
the actual program. However there was one run time that I did not expect. It was from the
Remove duplicates function that used linked list for its container. The time approximately took 130 seconds which is about 2 mins. I'm not sure why it took the program that much time to work this function. MY guess is that the coefficient is large for linked lists.  I did not update any of my cell in the table. 
	The coefficients for different data types that have the same big o notation did match my 
Intuition. I was surprised by how big the coefficient is for linked list. This will definitely impact my data structure choice in my future programming projects. I experienced how the running time gets 
Affected hugely depending on which data structure is used and that it is significantly important to
Choose the most efficient data structure for different projects. 


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
