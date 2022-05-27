HOMEWORK 9: MINIBLAST


NAME:  < Kyuseok Nam >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Joshua,siddha / lecture notes >

Hash function was copied from last semesters hash_set lab.
http://www.partow.net/programming/hashfunctions/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 10 hours >


HASH FUNCTION DESCRIPTION

Hash function was copied from last semesters hash_set lab.
http://www.partow.net/programming/hashfunctions/ 
JS Hash Function.
Its a bitwise hash function that does bit operations to get the hash.





HASH TABLE IMPLEMENTATION

The Hash table has two vectors each for keys and values
The hash table uses the hash function to get the index for the 
Corresponding keys. Then using that index it stores the keys to 
Key vector, then it stores the values(position) by pushing it back
to a different vector of lists that only stores values at the same index

The hash table uses linear probing so if that index is already full it looks
at the next index until it finds where that key is or finds a blank

The hash table resizes every time when the insert function is called and when the 
Occupancy is greater than number of keys divided by size of m_table vector


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)
n - number of different kmers in m_table

How much memory will the hash table data structure require (order notation for memory use)?

It uses up O(k) + O(n*p). O(n) is the memory for m_table vector and O(k*p) is the memory for
the vector that stores number of different locations for where each kmers are found.


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?


genome: O(number of lines in genome text file) it just loops through each line in that
Text file and then stores that to string genome.

table_size: O(1) just stores the table size value

Occupancy: O(1) just stores occupancy value;

kmer: O(L*(k+(k+n))) = O(L*(2k+n)) = O(L*(k+n) The function first loops through the genome
	which is O(L) then inside that loop it loops through each word in kmer which is O(k)
	and then it uses the insert function which is O(k+n) described below.

query: O(k+n+(p*q)).  first it loops through query k times to get the key from it which is O(k).
	then it calls the find function which is O(k+n) described below. Then it loops again
	through the different positions which is O(p) and inside that loop it loops again
	for the query size which is then O(p*q).
	so the total running time is O(k+k+n+p*q) = O(2k+n+(p*q)) = O(k+n+(p*q))
	

quit:  O(1) just quits the program

Insert: O(k+n) the hash function is O(k) which just loops through each word in kmer.
	then worst case it has to loop through the vector until it finds a blank space 
	or the same kmer, which is O(n) so its O(k+n) worst case. 

find: O(k+n) the hash function is O(k). Then worst case it loops through each kmer inside
 	m_table which is O(n). So worst case it is O(n+k) for this function.

Resize: O(n*p) it first loops through each kmers inside m_table which is O(n) then
	inside that loop it loops again for each positions corresponding to that kmer
	so it's O(n*p)



EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Thank you for grading my work. 

