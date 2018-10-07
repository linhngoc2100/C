/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

*************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a2.h"

int symIndex=0;

int LOCCTR[100];
int LocctrCounter=0;
typedef struct operatorTab/*struture for opcode-intermediate file*/
{
	char Mnemonic[10];
	char Format;
	unsigned short int  theOpcode;
}SICXEOPTAB;

typedef struct SymbolTable/*symtab*/
{
	char Label[10];
	int Address;
}SIC_SYMTAB; 

int FoundOnOptab_flag ;
int opIndex=0;
SIC_SYMTAB SYMTAB[20];

int SYMTABCounter=0;
static SICXEOPTAB OPTAB[]=
{
	{   "ADD",  '3',  0x18},	{  "ADDF",  '3',  0x58},	{  "ADDR",  '2',  0x90},
	{   "AND",  '3',  0x40},	{ "CLEAR",  '2',  0xB4},	{  "COMP",  '3',  0x28},
	{  "COMPF",  '3',  0x88},	{  "COMPR",  '2',  0xA0},	{   "DIV",  '3',  0x24},
	{   "DIVF",  '3',  0x64},	{   "DIVR",  '2',  0x9C},	{   "FIX",  '1',  0xC4},
	{   "FLOAT",  '1',  0xC0},	{   "HIO",  '1',  0xF4},	{     "J",  '3',  0x3C},
	{   "JEQ",  '3',  0x30},	{   "JGT",  '3',  0x34},	{   "JLT",  '3',  0x38},
	{  "JSUB",  '3',  0x48},	{   "LDA",  '3',  0x00},	{   "LDB",  '3',  0x68},
	{  "LDCH",  '3',  0x50},	{   "LDF",  '3',  0x70},	{   "LDL",  '3',  0x08},
	{   "LDS",  '3',  0x6C},	{   "LDT",  '3',  0x74},	{   "LDX",  '3',  0x04},
	{   "LPS",  '3',  0xD0},	{   "MUL",  '3',  0x20},	{   "MULF",  '3',  0x60},
	{   "MULR",  '2',  0x98},	{   "NORM",  '1',  0x20},	{    "OR",  '3',  0x44},
	{    "RD",  '3',  0xD8},	{   "RMO",  '2',  0xAC},	{  "RSUB",  '3',  0x4C},
	{   "SHIFTL",  '2',  0xA4},	{   "SHIFTR",  '2',  0xA8},	{   "SIO",  '1',  0xF0},
	{   "SSK",  '3',  0xEC},	{   "STA",  '3',  0x0C},	{   "STB",  '3',  0x78},
	{  "STCH",  '3',  0x54},	{   "STF",  '3',  0x80},	{   "STI",  '3',  0xD4},
	{   "STL",  '3',  0x14},	{   "STS",  '3',  0x7C},	{  "STSW",  '3',  0xE8},
	{   "STT",  '3',  0x84},	{   "STX",  '3',  0x10},	{   "SUB",  '3',  0x1C},
	{   "SUBF",  '3',  0x5C},	{   "SUBR",  '2',  0x94},	{   "SVC",  '2',  0xB0},
	{    "TD",  '3',  0xE0},	{   "TIO",  '1',  0xF8},	{   "TIX",  '3',  0x2C},
	{   "TIXR",  '2',  0xB8},	{    "WD",  '3',  0xDC},
};
 
void readfilesic(char *filename)
{ 
 FILE *fp;
 struct IntermediateArray IMArray[100];
 
 int length_line;
 char Buffer[256];
 
 char label[32],Label[32];
 char opcode[32];
 char operand[32];
 int isDot,starting_address,FoundSYMTAB;

 int ArrayIndex=0, line=0,loc=0,Index=0;
 int foundOpcode=0,foundSymbol=0;
 int program_length;
	
fp=fopen(filename,"r");
if(fp==NULL)
{
	printf("ERROR: Unable to open the %s file.\n", filename);
	exit(1);
}
char tmp[100];
/************  PASS 1  *************/
while (fgets(Buffer, 256, fp) !=NULL)
{
	length_line =strlen(Buffer);
	Index=0;
	strcpy(label, ReadLabel(Buffer));
	
	strcpy(Label, label);
	if(label[0]=='.')
		isDot=1;
	else
		isDot=0;
	/*check if the length >1 and is not comment*/
	if(length_line>1 && isDot!=1)
	{
		Index=0;
		
		IMArray[ArrayIndex].LineIndex=ArrayIndex;/*add line*/
		strcpy(label, ReadLabel(Buffer));/*get Label and copy to label*/
		
		strcpy(IMArray[ArrayIndex].LabelField,label);/*add label to
		IMArray*/
		if(line==0)
		{
			strcpy(opcode,ReadOprator(Buffer));
			strcpy(IMArray[ArrayIndex].OperatorCol,opcode);
			
			
			if(!strcmp(opcode,"START"))/* check if it is START or not */
			{
				strcpy(operand,ReadOperand(Buffer));/*get operand*/
				strcpy(IMArray[ArrayIndex].OperandCol,operand);/*add operand to IMArray */
				LOCCTR[LocctrCounter]=strToHex(operand);
				starting_address=LOCCTR[LocctrCounter];/*set starting
				address*/
				
				
			}
			else
			{
				LOCCTR[LocctrCounter]=0;
				starting_address=LOCCTR[LocctrCounter];
			}
		}
		else
		{
			strcpy(opcode,ReadOprator(Buffer));
			
			strcpy(IMArray[ArrayIndex].OperatorCol,opcode);
			strcpy(operand,ReadOperand(Buffer));
			strcpy(IMArray[ArrayIndex].OperandCol,operand);
			
			if(strcmp(opcode,"END"))/*if opcode != END, calculate the LOCCTR and LocctrCouner for loc*/
			{
				if(label[0]!='\0')
				{
					if(searchSymbol(label))
					{
						fclose(fp);
						printf("ERROR: Duplicate Symbol\n");
						foundSymbol=0;
						exit(1);
					}
					recordSymbol(label);
				}
				/*check if opcode exist or not to calculate locctr */
				if(searchOpcode(opcode))
					LOCCTR[LocctrCounter]=loc + int (OPTAB[opIndex].Format-'0');
					/* check if it equals to WORD or RESB or RESW or BYTE*/
				else if(!strcmp(opcode,"WORD"))
					LOCCTR[LocctrCounter]=loc+3;
				else if(!strcmp(opcode,"RESW"))
					LOCCTR[LocctrCounter]=loc+3*strToDec(operand);
				else if(!strcmp(opcode,"RESB"))
					LOCCTR[LocctrCounter]=loc+strToDec(operand);
				else if(!strcmp(opcode,"BYTE"))
					LOCCTR[LocctrCounter]=loc+get_length(operand);	
				else
					{fclose(fp);
					printf("ERROR: Invalid operation code.\n");
					exit(1);}
			}
			
			
		}
		loc=LOCCTR[LocctrCounter];
		IMArray[ArrayIndex].Loc=LOCCTR[LocctrCounter-1];
		LocctrCounter++;
		ArrayIndex++;
		
	}
	foundOpcode=0;
	line+=1;
	}
	program_length=LOCCTR[LocctrCounter-2]-LOCCTR[0];

/***********PASS 2 ***********/

unsigned long fmt;
unsigned long f_opcode;
unsigned long f_index;
unsigned long f_address;
int m;
int k;
for(m=0;m<ArrayIndex;m++)
{
	f_opcode=0;
	f_index=0;
	f_address=0;
	
	strcpy(opcode,IMArray[m].OperatorCol);
	/*search if opcode exists*/
	if(searchOpcode(opcode))
	{
		f_opcode=OPTAB[opIndex].theOpcode;
		f_opcode <<=16;
	
	IMArray[m].ObjectCode = f_opcode;
	strcpy(operand,IMArray[m].OperandCol);
	
	if(operand[strlen(operand)-2]==',' && operand[strlen(operand)-1]=='X')
	{
		f_index=0x008000;
		operand[strlen(operand)-2]='\0';
	}
	else
		f_index=0x000000;
		
	int search_symbol;
	for(search_symbol=0;search_symbol<symIndex;search_symbol++)/*search symbol*/
	{
		if(!strcmp(operand,SYMTAB[search_symbol].Label))
			f_address=(long)SYMTAB[search_symbol].Address;
	}
	fmt=f_opcode +f_index+f_address;
	IMArray[m].ObjectCode=fmt;
	}
	else if (!strcmp(opcode,"WORD"))
	{
		strcmp(operand,IMArray[m].OperandCol);
		IMArray[m].ObjectCode=strToDec(operand);
	}
	else if (!strcmp(opcode,"BYTE"))
	{
		strcmp(operand,IMArray[m].OperandCol);
		IMArray[m].ObjectCode=0;
		
		if(operand[0]=='C' || operand[0]=='c' && operand[1]=='\'' )
		{	
			for(k=2;k<=int(strlen(operand)-2);k++)
			{
				IMArray[m].ObjectCode=IMArray[m].ObjectCode +(int)operand[k];
				IMArray[m].ObjectCode<<=8;
			}
		}
		if(operand[0]=='X' || operand[0]=='x' && operand[1]=='\'')
		{
			char *operand_pt;
			operand_pt=&operand[2];
			*(operand_pt+2)='\0';
			
			for(k=2;k<=int(strlen(operand)-2);k++)
			{
				IMArray[m].ObjectCode=IMArray[m].ObjectCode +strToHex(operand_pt);
				IMArray[m].ObjectCode<<=8;
			}
		}
		IMArray[m].ObjectCode>>=8;
	}
	else;
	
				
}
createList(IMArray,ArrayIndex);
create_objcode(IMArray, starting_address,program_length);

free(IMArray);	
printf("Finished\n ");
fclose(fp);

}
/*create reocrd of SYMTAB*/
void recordSymbol(char* label){
	strcpy(SYMTAB[symIndex].Label,label);
	SYMTAB[symIndex].Address = LOCCTR[LocctrCounter-1];
	symIndex++;	
}
/*search opcode */
int searchOpcode(char * Mnemonic){
	int size = sizeof(OPTAB)/sizeof(SICXEOPTAB);
	FoundOnOptab_flag = 0;
	
	for(int i=0;i<size;i++){
		
		if(!strcmp(Mnemonic,OPTAB[i].Mnemonic)){
			opIndex = i;
			FoundOnOptab_flag = 1;
			break;
		}
	}
	
	return (FoundOnOptab_flag);
}
/*search symbol*/
int searchSymbol(char* label){
	int FoundOnSYMTAB_flag = 0;

	for (int k= 0; k<=symIndex; k++){

		if (!strcmp(SYMTAB[k].Label,label)){
			FoundOnSYMTAB_flag = 1;
			return (FoundOnSYMTAB_flag);
			break;
		}
		
	}
	return (FoundOnSYMTAB_flag);
}
