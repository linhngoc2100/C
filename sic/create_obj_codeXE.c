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
/*create file sicXE.obj*/
void create_objcodeXE(struct IntermediateArray *arr,int starting_address,int program_length,int ArrayIndex)
{
	int first_address;
	int last_address;
	int tmp_address;
	int tmp_objcode[100];
	char t_opcode[100][100];
	int index_one;
	int index_two;
	int a,b;
	int i=0;
	
	char t_operator[100][100];
	char t_operand[100][100];
	
	FILE *fp;
	fp=fopen("sicXE.obj", "w");
	if(fp == NULL )
	{
		printf("ERROR: Cannot open sic.obj.\n");
		exit(1);
	}
	
	if(!strcmp(arr[i].OperatorCol,"START"))
	{
		printf("H%-6s%06x%06x\n",arr[i].LabelField,starting_address,program_length);
		fprintf(fp,"H^%-6s^%06x^%06x\n",arr[i].LabelField,starting_address,program_length);
		i++;
	}
	while(1)/*get objcode, operand of RESB, RESW, and others*/
	{
		first_address=arr[i].Loc;
		last_address=arr[i].Loc+27;
		index_one=i;
		for(a=0,tmp_address=first_address;tmp_address<=last_address;i++)
		{
			if(!strcmp(arr[i].OperatorCol,"END"))
				break;
			else if(strcmp(arr[i].OperatorCol,"RESB") &&
			strcmp(arr[i].OperatorCol,"RESW"))
			{
				tmp_objcode[a]=arr[i].ObjectCode;
				strcpy(t_operator[i],arr[i].OperatorCol);
				strcpy(t_operand[i],arr[i].OperandCol);
				index_two=i+1;
				a++;
			}
			else;
			tmp_address=arr[i+1].Loc;
		}
		printf("T%06x%02x",first_address,(arr[index_two].Loc-arr[index_one].Loc));
		fprintf(fp,"T^%06x^%02x",first_address,(arr[index_two].Loc-arr[index_one].Loc));
		
		for(b=0;b<a;b++)
		{
			if((strncmp(t_operator[b],"BYTE",4)==0) && (t_operand[b][0]=='X' || t_operand[b][0]=='x'))
			{
				printf("%02x",tmp_objcode[b]);
				fprintf(fp, "^%02x",tmp_objcode[b]);
			}
			else
			{
				printf("%06x",tmp_objcode[b]);
				fprintf(fp,"^%06x",tmp_objcode[b]);
			}
		}
		
		
		
		
		printf("\n");
		fprintf(fp,"\n");
		if(!strcmp(arr[i].OperatorCol,"END"))
			break;
	
	}
	int c;
	int d=5;
	for(c=0;c<ArrayIndex;c++)/*get opcode,and calculate address for M*/
		{
			strcpy(t_opcode[c],arr[c].OperatorCol);
			if(!strncmp(t_opcode[c],"+JSUB",5))
				{printf("M%06x%02x",arr[c+1].Loc-3,d);
				fprintf(fp,"M^%06x^%02x",arr[c+1].Loc-3,d);
				printf("\n");
				fprintf(fp,"\n");
				}
		}
	printf("E%06x\n\n",starting_address);
	fprintf(fp,"E^%06x\n\n",starting_address);
	fclose(fp);
}
