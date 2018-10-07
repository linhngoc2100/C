/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

*************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "a2.h"

typedef struct dataRec
{
	char OperatorVal[32];
	char OperandVal[32];
}dataArray;

dataArray * dArray[100];
int main (int argc, char *argv[])
{
	FILE *fp;
	char Buffer[256];
	char label[32],Label[32];
	char opcode[32];
	char operand[32];
	char filename[55];
	int thelength=0;
	int ArrayIndex=0;
	int is_comment=0,line=0;
	 printf("\nEnter the file name you want to assembly (sic.asm):");
	scanf("%s",filename);
/*check if the file exists or not*/	
fp=fopen(filename,"r");
if(fp==NULL)
{
	printf("ERROR: Unable to open the %s file.\n", filename);
	return 1;
}
while(fgets(Buffer,256,fp) !=NULL)
{
	thelength=strlen(Buffer);
	strcpy(label,ReadLabel(Buffer));
	dArray[ArrayIndex]=(dataArray *)malloc(sizeof(dataArray));
	strcpy(Label,label);
	if(Label[0]=='.')
		is_comment=1;
	else
		is_comment=0;
	if(thelength>1 && is_comment!=1)
	{
		if(line==0){
		strcpy(label,ReadLabel(Buffer));
		strcpy(opcode,ReadOperand(Buffer));
		strcpy(dArray[ArrayIndex]->OperatorVal,opcode);
		strcpy(operand,ReadOperand(Buffer));
		strcpy(dArray[ArrayIndex]->OperandVal,operand);}
		else{
		strcpy(opcode,ReadOperand(Buffer));
		strcpy(dArray[ArrayIndex]->OperatorVal,opcode);
		strcpy(operand,ReadOperand(Buffer));
		strcpy(dArray[ArrayIndex]->OperandVal,operand);
		}
		ArrayIndex++;
	}
	line+=1;
}
int i;
int k=0;
/*set Sic and SicXE */
for(i=0;i<ArrayIndex;i++)
{
	strcpy(opcode,dArray[i]->OperatorVal);
	strcpy(operand,dArray[i]->OperandVal);
	if(opcode[0]=='+' || opcode[0]=='=' || operand[0]=='#' ||operand[0]=='@' || operand[0]=='=')
	{
		k=1;
		
		break;
	}
	else
		k=0;}
		
	if(k==1)
		readfilexe(filename);
	else
		readfilesic(filename);

	return 0;
}
