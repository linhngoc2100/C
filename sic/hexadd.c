/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username:masc 0710
File: hexadd.c

*************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"a1.h"
char *sumhex(char *firsthex, char *secondhex){	
	
	char *end;
	int i=0;
	int rmainder=0;
	char hexsum[100];
	/*Convert from string hex to unsigned integer 32bit*/
	unsigned long nOne=strtoul(firsthex,&end,16);

	unsigned long ntwo=strtoul(secondhex,&end,16);
	
	unsigned long thesum=nOne+ntwo;
	/*convert from decimal to hex*/
	while(thesum !=0)
	{
		rmainder = thesum%16;
		thesum=thesum/16;
		
		switch(rmainder){
			case 0: strcat(hexsum,"0"); break;
			case 1: strcat(hexsum,"1"); break;
			case 2: strcat(hexsum,"2"); break;
			case 3: strcat(hexsum,"3"); break;
			case 4: strcat(hexsum,"4"); break;
			case 5: strcat(hexsum,"5"); break;
			case 6: strcat(hexsum,"6"); break;
			case 7: strcat(hexsum,"7"); break;
			case 8: strcat(hexsum,"8"); break;
			case 9: strcat(hexsum,"9"); break;
			case 10: strcat(hexsum,"A"); break;
			case 11: strcat(hexsum,"B"); break;
			case 12: strcat(hexsum,"C"); break;
			case 13: strcat(hexsum,"D"); break;
			case 14: strcat(hexsum,"E"); break;
			case 15: strcat(hexsum,"F"); break;
			default:printf("Error\n");return 0;
			
	}
	i++;
	}
	
	char newhex[100]="";
	int k=strlen(hexsum);
	char tmp[100];
	int g=1;
	/*invert hex to get the right hex 321->123*/
	while(k>0){
	
		memcpy(tmp,&hexsum[k-1],1);
		
		tmp[g]='\0';
		
		strcat(newhex,tmp);
		
		g++;
		k--;
	}
	
	char *taddress=newhex;
	
	return taddress;
}
