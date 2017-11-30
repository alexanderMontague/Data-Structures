Student Information
####################
Alexander Montague
0959687
amontagu@uoguelph.ca
November 2017
Assignment 3

Program Description
####################
This program was created showcase the use of a hash table to store word values in a dictionary by mapping them to unique keys.

Hash Function
####################
For my hash function, I looked at the lose lose algorithm for inspiration, as it seemed to me like the easiest one, that also was contained to the API restraints. The Node->key declaration was an integer, whereas most hash functions deal with longs, so they would overflow if used. I basically multiply the integer representation of each character in the string by whatever position in the string you are at. This works as there is no randomness and can be replicated to figure out the index, as well as keeping every different string to a different key. 

Collision Resolution
####################
In my program I used the strategy of chaining to resolve collision conflicts. This strategy works by treating each element in the Node/Hash Array as a singly linked list. My algorithm works by always adding to the empty first index in the hash array first, and if a collision is detected, it will chain that node onto the first at that index. Ex. INDEX 0: val1->val2->val3 etc. I believe this strategy was one of the easiest to implement with the API, so that is why I chose to use it, as well as having previous experience with linked lists.

Additional Program  Details
####################
- FOR ALL INPUT FILES - Please make sure that there is a newline after the last line of data for both the dictionary and word input files. I have included the example files with a newline in the assets folder

- Run the program using   ./program <file path>   Ex. If the file were to be in the assets folder, you would run ./program ../assets/<filename> or as an example, when asked for the input word file, type ../assets/a3_userFile.txt
