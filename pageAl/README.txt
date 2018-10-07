/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 2
Partner: Thon Saetern
Username: masc0954
File: README.txt
**************************************/

File manifest:
	a2.cpp
	a2.h
	pageAl.cpp

Compile instruction:
Two choices:
1) Input into shell: "g++ -o a2 a2.cpp page.cpp"
	- This will create a2 
2) Run the make file we have included titled: "Makefile" by typing make

Operating instructions:
Run program by type a2
Then input the number of frames

Novel/significant design decisions:
Following instructions in assignment sheet and using the algorithms in lecture
notes.

Extra features/functionality:
N/A

Deficiencies or bugs:
Wrong answer with some integers for LRU.
For example:
input: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
this input should give the answer for 12 but it is not, it is 16( 3 frames)
Summary of findings:
Input 1: 2 3 2 1 5 2 4 5 3 2 5 2

Input 2: 1 2 3 4 1 2 5 1 2 3 4 5
The more number of page, the more page faults;
At a specific of frame sizes, the page faults will not change. 

Lessons learned:
- Communication is key for a successful team
- Learn some interesting algorithms
