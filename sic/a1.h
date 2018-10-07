/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username: masc 0710
File: a1.h

*************************************************************/
#include <stdio.h>
#include <string.h>
#define MAX 1000

void prn_instructions(void);
char *instruction_evaluate(char *subbuff);
char *hexatobi(char *hexaDecimal);
char *flag_n_i(char* ni);
char *flag_b_p(char* nix);
char *target_machine(char *bi);
char * t_address(char *subnix, char *subhex, char *xregis, char *pcregis, char *bregis, char *add50, char *lines,int lngth);
char *sumhex(char *firsthex, char *secondhex);
char *exchangebi(char *binumber);
char *cbtohex(char *bnumber);
