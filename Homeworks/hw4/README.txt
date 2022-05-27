HOMEWORK 4: DVD LISTS


NAME:  < Kyuseok Nam >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< allenw, avrahb / lecture notes >

Remember: Your implementation for this assignment must be done on your
Maown, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 14 hours >


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.

dvd: O(d) loops through the all DVDS to find if it exists

customer: O(c+p) loops through the customers to find if exists, then loop through
	  num of movies in preference_list in check_preference function

add_preference: O(c+d+p) first loop through customers + loop through different dvds + 
		loop through preference to find if it exists 

ship: O(c*p*(d+p+p)) First it loops through customers O(c)and in that loop it does another
      Loop through preference O(c*p) then in that loop it again does another 
      loop(find_dVD) which is O(c*p*(d)) and then it does one more loop (in_possession)
      Which is O(c*p*(d+p)) and then one more loop(receives()) which is O(c*p*(d+p+p))
      This can be reduced to O(c*p*(d+2p)) = O(c*p*(d+p)). But I wasn't sure which one is
	right so I just wrote the raw version as answer

return_oldest:O(c+d) first loops through customers which is c then do another loop
	      to through different dvd titles to find dvd which is d

return_newest:O(c+d)first loops through customers which is c then do another loop
	      to through different dvd titles to find dvd which is d

print_customer:O(c+p) first searches customer which is O(c) then print preference which is   
	       O(p) so it is O(c+p)

print_dvd: O(d) loops through all dvds to find the dvd then just print



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  






