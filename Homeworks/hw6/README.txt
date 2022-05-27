HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Kyuseok Nam >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< none / lecture notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Etc. 

Vertical: O(d+l) std::find is O(d) then it does a for loop which is O(l) so in total its O(d+l)

Horizontal: O(d+l) std::find is O(d) then it does a for loop which is O(l) so in total its O(d+l)


check_grid: when considering the number of words in temp is m, the time complexity of check_grid
            is O(wh+md+mc) = O(wh+m(d+c))

solve: its O(wh(d+l)) for checking all horizontals, O(wh(d+l) for checking all verticals,
       And O(wh+m(d+c) + s ) for base case when considering the size of solutions as s. 
       So the total running time for this whole function would be O(log wh(d+l))

DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

Dictionary1:

ALASKA
EXLDFJ
ABCDE
AKDTJ
ABIE
MZY

Dictionary2: 

ALASKA
EXLDFJ
ABCDE
AKDTJ
USE
FLEES
NVI


Puzzle1: 

!Source:Kyuseok
+6
+5
+5
+6
ALASKA
BNVIJK
CEIBND
DWORIT
EXLDFJ

PUZZLE2:
!Source:Kyuseok
+6
+5
+5
+6
+3
ALASKA
BNVIJK
CEIBND
DWORIT
EXLDFJ

Output1 (using dictionary1):

Number of solution(s): 1
Board:
ALASKA
B####K
C####D
D####T
EXLDFJ

Output2 (using dictionary2):

Number of solution(s): 0

I used this test cases for checking corner cases where the board contains 2 letter words which 
Should not be accepted as a solution. I didn't really have a interesting corner case
When testing my function because everything worked well.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

The performance of my program does not matter whether it is printing a single solution
Or all solutions. The algorithm solves all the possible solutions to a vector.
When it prints all solutions it simply loops through the vector and prints each 
Solution grid. When printing only a single solution it prints out the very first
Solution grid inside the vector. Which is very inefficient. If I had more time I 
Would have implemented in a more efficient way so that when printing a single solution
The solve function quits as soon as it hits the very first base case which would save a lot
More time compared to the current algorithm that is implemented in my code. 



MISC. COMMENTS TO GRADER:  
I was confused and wasn't sure about my answer for the time complexity
Of my algorithm. I would appreciate it if there is a description of 
What the correct answer is in the comment when graded. Thank you!


