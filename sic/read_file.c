/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

*************************************************************/
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "a2.h"

int Index=0;
char *ReadLabel(char *line){/*get label*/
	char label[32];
	int j=0;
	Index=0;
	char *Label;
	char tmp[256];
	strcpy(tmp,line);
	
	
	while (tmp[Index] != ' ' && tmp[Index] != '\t' && tmp[Index] != '\n')
		label[j++] = tmp[Index++];
	label[j] = '\0'; 
	Label=label;
		return Label;
}

char *ReadOprator(char *line)/*get operator*/
{
	char mnemonic[32];
	int j=0;
	SkipSpace(line);
	char *Mnemonic;
	char tmp[256];
	strcpy(tmp,line);
	
	
	while (tmp[Index] != ' ' && tmp[Index] != '\t' && tmp[Index] != '\n')
		mnemonic[j++] = tmp[Index++];
	mnemonic[j] = '\0'; 
	Mnemonic=mnemonic;
		
		
		return Mnemonic;
}

char *ReadOperand(char *line)/*get operand*/
{
	char operand[32];
	int j=0;
	SkipSpace(line);
	char *Operand;
	char tmp[256];
	strcpy(tmp,line);
	
	
	while (tmp[Index] != ' ' && tmp[Index] != '\t' && tmp[Index] != '\n')
		operand[j++] = tmp[Index++];
	operand[j] = '\0'; 
	Operand=operand;
		
		return Operand;
}

void SkipSpace(char * line){/*skip space*/
	char Buffer[256];
	strcpy(Buffer,line);
	while (Buffer[Index] == ' ' || Buffer[Index] =='\t')
		Index++;
}

int checkDigit(char *operand)
{
	int k=0;
	int i;
	int l=strlen(operand);
	for(i=1;i<=l;i++)
	{
		if(isdigit(operand[i]))
			k=1;
	}
	return k;
}
