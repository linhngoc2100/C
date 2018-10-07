**********************************************************
CS530 - SPRING 2013
Name:  LINH NGOC NGUYEN
User: masc0755
Project: CSNNNN Assignment 3

**********************************************************
File:	a3.lex
	README.txt
	Makefile

**********************************************************
This program is used to determine if the statement(s) is/are valid from the
input file .txt. This will print out the statemen, and either pass/fail into a
file named out.txt. If it failed, it will print out why (int the same out.txt
file).

Valid statement includes assignment and expression. Assignment shall have the
form: 	ID = EXP ;
Expression shall have the form:		ID OP ID {OP ID} 
An ID will be made up of any combination of digit and char. The first position
of the identifier must contain a char. 
A digit is one of 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 and a char is one of a-z, A-Z. An
op is one of +, - , *, /, %

To run this program, first you need to type:
lex a3.lex
gcc -o a3 lex.yy.c -lfl

or you can type "make" and then press Enter to compile the program

After that, you will type a3 to run the program.

This will have 1 file (.txt):out.txt. Use notepad, or word to read the file
Or type cat, or more to view the file

In this program, my a3.lex file basiclly print out the answer valid or invalid
statement. However, if the statement is out of the rule set, it will print wrong
answer. Moreover, in some cases, the program cannot print out exactly what i want. 

It is hard for me to learn the new computer language> it is better to have more
examples and explanation when studying new computer language.  

A valid statement in Backus-Naur Form:

 <statement> 	::= <assignment> | <expression>
 <assingment> 	::= <id> := <expression> ;
 <id> 		::= <letter> | <id><letter> | <id><digit>
 <expression> 	::= <id> <op> <id> | <expression> <op> <id>
 <op>		::= +|-|*|/|%
 <digit> 	::= 0|1|2|3|4|5|6|7|8|9
 <letter> 	::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|
 		    y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|
 		    W|X|Y|Z
	
The program inputs and the program outputs:
First: It prompts the user to input the file
Second: It will scan the input file; if the file exists, it will process the file, and if not, it will show error:Unable to open the file.
Third It will read each line in the file.
Fourth: It will compare the line with the statement rule.
	If the line is same with the correct rule, it will show print out "valid" and the line
	If the line is not same with the correct rule, it will print out "invalid", what wrong and the line
Fifth: Create the file and store the value.

Example: Output: THIS PROGRAM WILL CHECK IF THE STATEMENT IS VALID OR NOT.
	Output: A VALID STATEMENT WILL BE ID = ID OP ID {OP ID} ;
	Output: With ID is the combine of char and digit and have char at the begin
	Output: And the operator is + - * / %
	Output: please enter the file name(.txt):
	Input: ex.txt
	Output:
	Valid: first = one1 + two2 - three3 / four4 ;
	Valid: second = one1 * (two2 * three3) ;
	INVALID-extra = or operator or INVALID ID: first = = one1 + two2 - three3 / four4 ;
	
	
