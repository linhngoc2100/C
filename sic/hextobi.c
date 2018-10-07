/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username :masc0710
File: hextobi.c

*************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "a1.h"

#define MAX 1000
/* convert hex to binary*/
char *hexatobi(char *hexaDecimal)
{

char binaryNumber[MAX]="";/*set size for char binary*/
char *tmp="";
long int i=0;
char *err="error";
/*begin running from first number to the last number with while loop*/
/*comapre the letter of current number with hex letter and then add that same value in binary into binaryNumber*/
while(hexaDecimal[i]){
         switch(hexaDecimal[i]){
             case '0':  strcat(binaryNumber,"0000");break;
             case '1':  strcat(binaryNumber,"0001");break;
             case '2':  strcat(binaryNumber,"0010");break;
             case '3':  strcat(binaryNumber,"0011");break;
             case '4':  strcat(binaryNumber,"0100");break;
             case '5':  strcat(binaryNumber,"0101");break;
             case '6':  strcat(binaryNumber,"0110");break;
             case '7':  strcat(binaryNumber,"0111");break;
             case '8':  strcat(binaryNumber,"1000");break;
             case '9':  strcat(binaryNumber,"1001");break;
             case 'A':  strcat(binaryNumber,"1010");break;
             case 'B':  strcat(binaryNumber,"1011");break;
             case 'C':  strcat(binaryNumber,"1100");break;
             case 'D':  strcat(binaryNumber,"1101");break;
             case 'E':  strcat(binaryNumber,"1110");break;
             case 'F':  strcat(binaryNumber,"1111");break;
             
             default:  printf("\nInvalid hexadecimal digit %c ",hexaDecimal[i]);/*if the letter not in hex letter, error appears*/
	     return err;
         }
         i++;
    }
    printf("\n");
    
    tmp=binaryNumber;
    
    
    
    return tmp;
}

/*change the x=1 to x=0 in nixbpe*/
char *exchangebi(char *binumber)
{
	
	char subbi[1000];
	char tmp[1000];
	char *newbi="";
	int lth = strlen(binumber);
	/*by creating new string and add 0 to the string and then add the rest of string of the current line begin after x=1*/
	memcpy(subbi,&binumber[1],lth-1);
	subbi[lth-1]='\0';
	

		strcpy(tmp,"0");
		strcat(tmp,subbi);
		newbi=tmp;
		
	return newbi;
}
/*convert from bianry to hex*/
char *cbtohex(char *bnumber)
{
	char *newbi = exchangebi(bnumber);/*call for change x=1 to x=0*/
	
	char newhex[100]="";
	char *hexnew;
	char hexn[100]="";
	char *end;
	char *error="error";
	unsigned long ndecimal=strtoul(newbi,&end,2);/*convert from bianry to decimal */
	
	int rmainder=0;
	/*run the loop to convert*/
	/*divide the number for 16 with the remainder that compare with hex letter then add to hexn until the number(ndecimal) =0*/
	while(ndecimal!=0)
	{
		rmainder=ndecimal%16;
		ndecimal=ndecimal/16;
		switch(rmainder){
			case 0: strcat(hexn,"0"); break;
			case 1: strcat(hexn,"1"); break;
			case 2: strcat(hexn,"2"); break;
			case 3: strcat(hexn,"3"); break;
			case 4: strcat(hexn,"4"); break;
			case 5: strcat(hexn,"5"); break;
			case 6: strcat(hexn,"6"); break;
			case 7: strcat(hexn,"7"); break;
			case 8: strcat(hexn,"8"); break;
			case 9: strcat(hexn,"9"); break;
			case 10: strcat(hexn,"A"); break;
			case 11: strcat(hexn,"B"); break;
			case 12: strcat(hexn,"C"); break;
			case 13: strcat(hexn,"D"); break;
			case 14: strcat(hexn,"E"); break;
			case 15: strcat(hexn,"F"); break;
			default:printf("Error\n");return error;
		}
		
	}
	/*invert the hex because the convert add from top to down not from down to top*/
	int k=strlen(hexn);
	char tmp[100];	
	/*run from k -the length of current hexn*/
	while(k>0){
	
		memcpy(tmp,&hexn[k-1],1);
		tmp[1]='\0';
		strcat(newhex,tmp);
		k--;
	}
	
	hexnew=newhex;
	
	return hexnew;
}
