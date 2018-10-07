/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a2.h"
/*create file .list*/
void createList(struct IntermediateArray *arr,int Index)
{
	int i,k,l;
	FILE *fp;
	fp=fopen("sic.list","w");
	/*check if is NULL or not*/
	if(fp==NULL)
	{
		printf("ERROR: Cannot open sic.list\n");
		exit(1);
	}
	/*set header */
	fprintf(fp, "%-4s\t%-10s%-10s%-10s\t%s\n","LOC","LABEL","OPERATOR","OPERAND","OBJECT CODE");
	for(i=0;i<Index;i++)/*store into file*/
	{
		
		if(!strcmp(arr[i].OperatorCol,"START") || !strcmp(arr[i].OperatorCol,"RESW") || !strcmp(arr[i].OperatorCol,"RESB") || !strcmp(arr[i].OperatorCol,"END"))
			fprintf(fp, "%04X\t%-10s%-10s%-10s\n",arr[i].Loc,arr[i].LabelField,arr[i].OperatorCol,arr[i].OperandCol);
		else
			fprintf(fp, "%04X\t%-10s%-10s%-10s\t%X\n",arr[i].Loc,arr[i].LabelField,arr[i].OperatorCol,arr[i].OperandCol,arr[i].ObjectCode);
	}
	fclose(fp);
}
