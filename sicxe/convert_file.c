/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710


*************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "a2.h"

/*convert from string to hex*/
int strToHex(char *operand)
{
	int hexnum=0;
	char temp[100];
	strcpy(temp,operand);
	int len=strlen(temp);
	int k,l;
	for(k=len-1,l=1;k>=0;k--)
	{
		if (temp[k]>='0' && temp[k]<='9')
			hexnum = hexnum + int (temp[k]-'0')*l;
		else if (temp[k]>='A' && temp[k]<='F')
            hexnum = hexnum + int (temp[k]-'A'+10)*l;
		else if (temp[k]>='a' && temp[k]>='f')
            hexnum = hexnum + int (temp[k]-'a'+10)*l;
		else ;
		l = l*16;
	}
	return hexnum;
}
/*convert from string to Dec*/
int strToDec(char* operand){
	int decnum = 0;
	char temp[32];
	strcpy(temp,operand);

	int len = strlen(operand);
	for (int k = len-1, l = 1; k>=0; k--)
	{
		decnum = decnum+int(temp[k]-'0')*l;
		l = l*10;
	}
	return decnum;
}
/*get the length in X'05 and C'EOF'*/
int get_length(char* operand){
	unsigned int b;
	char len[32];
	
	strcpy(len,operand);
	if (len[0] =='C' || len[0] =='c' && len[1] =='\''){
		for (b = 2; b<=strlen(len); b++){
			if (len[b] == '\''){
				b -=2;
				break;
			}
		}
	}
	if (len[0] =='X' || len[0] =='x' && len[1] =='\'')
		b = 1;
	return (b);
}



