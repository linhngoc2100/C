/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username: masc0710
File: target_address.c

*************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "a1.h"


char * t_address(char *subnix, char *subhex, char *xregis, char *pcregis, char *bregis, char *add50, char *lines ,int lngth)
{
	char sone[5];
	char stwo[5];
	char sthree[5];
	char *tadd="";
	char tmp[100];
	char xre[100];
	
	int a,b,c,d;
	a=strlen(xregis);
	memcpy(xre,&xregis[2],a-2);/*get 4 hex number in x register*/
	xre[a-2]='\0';
	
	memcpy(sone,&subnix[3],1);/*get b*/
	sone[1]='\0';
	memcpy(stwo,&subnix[4],1);/*get p*/
	stwo[1]='\0';
	memcpy(sthree,&subnix[2],1);/*get x*/
	sthree[1]='\0';
	
	
	/*check and compare b and p and x*/
	/*if b=1, and p=0 and x=0 then return TA=disp+B*/
	if((strcmp(sone,"1")==0)&&(strcmp(stwo,"0")==0)&&(strcmp(sthree,"0")==0))
		return tadd=sumhex(subhex,bregis);
	 if((strcmp(sone,"0")==0)&&(strcmp(stwo,"1")==0)&&(strcmp(sthree,"0")==0))/*check and compare b=0,p=1,x=0, then return TA=disp+PC*/
		return tadd=sumhex(subhex,pcregis);
	 if((strcmp(sone,"0")==0)&&(strcmp(stwo,"0")==0)&&(strcmp(sthree,"0")==0))/*check and compare b=0,p=10,x=0 then return TA=disp(fmt 3) or TA=add(fmt 4)*/
	{
		if(lngth==6)
			return tadd=subhex;
		if(lngth==8)
			{memcpy(tmp,&add50[1],5);
			tmp[5]='\0';
			tadd=tmp;
			return tadd;	}
		}
	
	if((strcmp(sthree,"1")==0))/*if x=1 */
	{	
			char newhex[100];
			
			memcpy(newhex,&lines[2],lngth-1);
			newhex[lngth-1]='\0';
			
			char *binumber=hexatobi(newhex);
			
			char *hexnumber;
			hexnumber=cbtohex(binumber);/*for some reason, it returns nothing ???*/
			
			
			char *temp;;
			if((strcmp(sone,"1")==0)&&(strcmp(stwo,"0")==0))/*if b=1, and p=0 and x=0 then return TA=disp+B+X*/
				{temp="";
				temp=sumhex(xre,bregis);
				
				tadd="";
					return tadd=sumhex(temp,hexnumber);
					}
					/*check and compare b=0,p=1,x=0, then return TA=disp+PC+X*/
			 if((strcmp(sone,"0")==0)&&(strcmp(stwo,"1")==0)){
			 	tadd="";
				temp="";
				temp=sumhex(xre,pcregis);
				
				return tadd=sumhex(temp,hexnumber);}
				/*check and compare b=0,p=10,x=0 then return TA=disp(fmt 3) +X or TA=add(fmt 4)+X*/
			 if((strcmp(sone,"0")==0)&&(strcmp(stwo,"0")==0))
		{
				if(lngth==6)
					{temp="";
					temp=hexnumber;
					tadd="";
					
						return tadd=sumhex(temp,xre);
					}
				if(lngth==8)
			{memcpy(tmp,&add50[1],5);
				tmp[5]='\0';
				temp="";
				temp=tmp;
				tadd="";
				return tadd=sumhex(temp,xre);
					}
		}
		/*for b and p==1*/
			tadd="";
			tadd=sumhex(xre,hexnumber);
			return tadd;
		
		}
}
	
