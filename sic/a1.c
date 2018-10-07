/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username:masc0710
File: a1.c

*************************************************************/
#include <stdio.h> /*example of compiler directives */
#include <string.h>
#include <stdlib.h>
#include "a1.h"


int main(int argc,char *argv[])
{
	
	char gline[100],line1[100];/*declare variable with size 100*/
	char lines[100][100];/*set matrix 2 dimension, because the line can change */
	char subbuff[100];/*for opcode- get 2 first letter in line*/
	int j=0;
   	char *opcode,*tmp;
   	char temp[100][1000],binaryNumber[100][1000]; /*declare variable array with size 1000 and can contain 100 strings*/
   	char *liness;/*single line*/
   	int lngth=0;
   	char *daddress="";/*disp/address*/
   	char *taddress="";/*target address*/
	char subbi[10];/*for nixbpe*/
	char subone[5],subtwo[5]; /*for get 2 last hex number in format 2 */
 	char *tmachine,*fmt,*addmode,*amode; /*target machine, format, addmode n -i, addmode b-p*/
	FILE *fp;
	printf("Starting program\n");
	printf("\n");
	int i=0,n=0;
	
	fp=fopen("a1.sic","r"); /*open the file*/
	 while(fgets(gline, 100, fp) != NULL)/*get the lines*/
   {
	 sscanf (gline, "%s", &line1);
	 if(strcmp(line1,"\0")!=0){	/*check empty line*/ 
	 strcpy(lines[i],line1);	 
	 memcpy(subbuff,&line1[0],2);/*get first 2 letters in line*/
	 subbuff[2]='\0';
	 
	i++;
	n++;
	 
   }}
   printf("OP	 nixbpe		disp/addr	  TA	[Target Machine] -  fmt,addressing mode \n");
 j=4;
 char *nixbpe;
 char *fmat="0";
 char none[5];
 /*begin to run at line 5 with while loop and increase after 1 loop by 1*/
while(j<n)
{	
	daddress="";/*set display and TA empty*/
	taddress="";	
	opcode=instruction_evaluate(lines[j]);	/*get opcode*/
	liness=lines[j];/*get  line j*/	
	tmp='\0';
	tmp=hexatobi(liness);	/*convert from hex to binary*/
	strcpy(temp[j],tmp);	/*copy tmp to temp*/
	memcpy(subbi,&tmp[6],6);	/*get nixbpe in binary*/
	subbi[6]='\0';
	lngth=strlen(lines[j]);/*get length of the current line*/
	
	/*check the length of the line so --> format*/
	if(lngth==2)/*1 byte*/
	{
		daddress="----";
		taddress="-----";
		nixbpe="------";
		addmode="";
		amode="";
		fmat="1";	
	}
		
	tmachine=target_machine(subbi);/*get target machine*/
	if(lngth==4)/*2 bytes*/
	{
		taddress="    ";
		memcpy(subone,&liness[2],1);/*get the third letter*/
		subone[1]='\0';
		memcpy(subtwo,&liness[3],1);/*get the last letter in line*/
		subtwo[1]='\0';
		strcat(subone,", ");/*add , in string*/
		strcat(subone,subtwo);/*add 2 strings*/
		daddress=subone;
		nixbpe="";
		addmode=flag_n_i(subbi);/*get check addressing mode by n and i*/
		amode=flag_b_p(subbi);	/*get addressing mode by b and p*/
		fmat="2";	
	}
	if(lngth==6)/*3 bytes*/
	{	/*check if formaat 3 or zero*/
		if(strncmp(subbi,"000",3)==0)/*compare the first 3 number in nixbpe binary if it == 000*/
		{
		nixbpe="--0---";
		fmat="0";
		char sone[10];
		memcpy(sone,&liness[2],4);
		sone[4]='\0';
		daddress=sone;
		taddress=sone;
		addmode="";
		amode="";
		
		}
		else{
		char sone[10];
		memcpy(sone,&liness[3],3);
		sone[3]='\0';
		daddress=sone;
		nixbpe=subbi;
		addmode=flag_n_i(subbi);/*get check addressing mode by n and i*/
		amode=flag_b_p(subbi); /*get addressing mode by b and p*/
		taddress=t_address(subbi, sone, lines[0],lines[1],lines[2], lines[3],lines[j],lngth);/*get target address with nixbpe, 3 dis, (x, b, pc register), current line, and
		length */
		fmat="3";}
	}
	if(lngth==8)/*4 bytes*/
	{
		char sone[10];
		int a=lngth-3;/*set to get 4 disp*/
		memcpy(sone,&liness[3],a);
		sone[a]='\0';
		daddress=sone;
		nixbpe=subbi;
		addmode=flag_n_i(subbi); /*get check addressing mode by n and i*/
		amode=flag_b_p(subbi); /*get addressing mode by b and p*/
		taddress=t_address(subbi, sone, lines[0],lines[1],lines[2], lines[3],lines[j],lngth);/*get target address with nixbpe, 3 dis, (x, b, pc register), current line, and
		length */
		fmat="4";
	}
	
	j++;
	/*print answer follow current line*/
	printf("%s \t %s\t \t %s \t \t %s\t\t%s\t %s  %s, %s \n",opcode,nixbpe,daddress,taddress,tmachine,fmat,addmode,amode);
}

	fclose(fp);
	printf("Program Finished...\n");
	fflush(stdout);
	exit(0);
}
/***********************[ EOF: a1.c ]*********************/
