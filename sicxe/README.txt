
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

Files: a2.c
	sic.c
	sicXE.c
	read_file.c
	convert_file.c
	create_file_list.c
	create_obj_code.c
	create_obj_codeXE.c
	a2.h

*************************************************************
This program is used to read assembly source files for SIC/XE and generate an
object code.
Input: the program will read the file from filename provided by the user from
the command line or if blank, prompt the user for the filename of the source
file to be assembled.
This program based on algorithm on page 53 and 54.

To run this program, first you need to type
g++ -o scl a2.c sic.c sicXE.c read_file.c convert_file.c create_file_list.c
create_obj_code.c create_obj_codeXE.c

or you can type "make" and then press Enter to compile the program

After that you type scl and the program will run.
This will have 2 files(.list and .obj): sic.list and sic.obj/sicXE.obj
Use notepad, word, to run read the files
Or type cat, or more in rohan server to view to the files

In this program, my SIC file have some object codes are not right. It is the
same with SICXE file. For some reason, the output does not appear like i want in
SICXE. 
There are some values that i don't know how to calculate in SICXE.

I usnderstand the lesson but there are some parts that are hard for me to
understand, for example, calculate the B relative counter.

 
 
