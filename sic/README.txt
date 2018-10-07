 Name: Linh Ngoc Nguyen
user masc0755
Partner:Tuan Truong
user masc0710
Class: CS 570, spring 2013
Assignment #1
Filename: README.txt

File manifest:a1.h, a1.c, ins_evaluate.c, hextobi.c, flagn_i.c, target_address.c hexadd.c

This program is used to open the file a1.sic which will contain a assembled
SIC/XE instructions and the evaluate each instruction, one per line, read from
this file until EOF. After evaluating, it will print: opcoe mnemonic, nixbpe
flags (if appropriate), the disp/address field (if appropriate), and the
TA(target address) (if applicable).

a1.h: the header file 
a1.c: the main program 
ins_evaluate.c: evaluate the opcode
hextobi.c: convert from hexadecimal to binary, change x=1 to x=0, convert from
binary to hex.
flagn_i.c: get addressing mode through n and i, b and p; get target machine
target_address.c: get target address 
hexadd.c: adding 2 hexadecimal

To run this program, first you need to type 
gcc -o diss a1.c ins_evaluate.c hextobi.c flagn_i.c target_address.c hexadd.c

or you can type "make" and then you press Enter to compile the program.

After that you type diss and the program will run.

In this program, i think that the target address does not run properly. Some of
the target address appears wrong. When changing x=1 to x=0, the new displacement
return nothing for some reason with causing the target address return wrong.

I have a little confuse with the lesson about the target address when x=1. 
