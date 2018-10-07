/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username: masc 0710
File: flag_i.c

*************************************************************/
#include<stdio.h>
#include<string.h>
#include "a1.h"
/*get addressing mode by n and i*/
char *flag_n_i(char* ni)
{
	char subone[5];
	char subtwo[5];
	char *amode;
	memcpy(subone,&ni[0],1);/*get n*/
	subone[1]='\0';
	memcpy(subtwo,&ni[1],1);/*get i*/
	subtwo[1]='\0';
	/*compare the value n and i with 0 and 1to get the right addressing mode*/
	if((strcmp(subone,"0")==0)&&(strcmp(subtwo,"1")==0))
		amode="immediate";
	else if((strcmp(subone,"1")==0)&&(strcmp(subtwo,"0")==0))
		amode="indirect";
	else if((strcmp(subone,"0")==0)&&(strcmp(subtwo,"0")==0))
		amode="simple";
	else
		amode="simple";
		
	return amode;
}
/*get addrssing mode with b and p*/
char *flag_b_p(char* nix)
{
	char sone[5];
	char stwo[5];
	char *addmode;
	memcpy(sone,&nix[3],1);/*get b*/
	sone[1]='\0';
	memcpy(stwo,&nix[4],1);/*get p*/
	stwo[1]='\0';
	/*compare b and p with 0 and 1 to get the right addressing mode*/
	if((strcmp(sone,"0")==0)&&(strcmp(stwo,"0")==0))
		addmode="direct";
	else if((strcmp(sone,"0")==0)&&(strcmp(stwo,"1")==0))
		addmode="PC relative";
	else if((strcmp(sone,"1")==0)&&(strcmp(stwo,"0")==0))
		addmode="Base relative";
	else
		addmode="";
		
	return addmode;
}
/*get target machine*/
char *target_machine(char *bi)
{
	char *tmachine;
	
	if(strncmp(bi,"00",2)==0)
		tmachine="SIC";
	else
		tmachine="XE";
	return tmachine;
}
