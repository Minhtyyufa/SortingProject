Minh-Thai Nguyen
Made in April 2018
This program sorts the nodes of a linked list given a certain data member of the node. This list will contain 1,000,000±1% data objectsVarious sorting algorithms are used in this project to sort each element efficiently given their unique characteristics. The sorted result is then outputted to  txat file. 

Input File Description:
  The program loads data from an input file specified by the user and creates a linked list of pointers to data objects using the provided C++ list class. Each data object will consist of four fields. The first two fields should be unsigned 32-bit integers (but these two fields will be generated in different manners, as described later). The third field should be a single printable, standard ASCII character. The fourth field should be a C++ string consisting of exactly 25 printable, standard ASCII characters.
  
  After creating the list, the program will sort the list according to one of the four fields, as specified by the user. The sorted list will then be written to an output file. The input and output files will have the same format. The first row will be an integer indicating how many rows follow. Each row after that represents a single data object, with the values of four fields separated by single spaces. There will be no leading or trailing whitespace, and each row will be followed by a Unix-style newline character ('\n'). If items in the column being sorted are identical, their relative positions to each other should not change; i.e., the sort will be stable.
  
The Columns:
  
