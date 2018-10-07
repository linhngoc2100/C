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
#include <ctype.h>
#include "a2.h"

int symIndexXE=0;

int LOCCTRXE[100];

int LocctrCounterXE=0;
typedef struct operatorTab/*intermediate file*/
{
	char Mnemonic[10];
	char Format;
	unsigned long int  theOpcode;
}SICXEOPTAB;

typedef struct SymbolTable/*symtab*/
{
	char Label[15];
	unsigned long int Address;
}SIC_SYMTAB; 

int FoundOnOptabXE_flag ;
int opIndexXE=0;
SIC_SYMTAB SYMTABXE[30];

int SymtabCounter=0;
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
 
 struct IntermediateArray IMArray[100];
 
void readfilexe(char *filename)
{ 
 FILE *fp;
 
 
 int length_line;
 char Buffer[256];

 char label[32],Label[32];
 char opcode[32];
 char operand[32];
 int isDot,starting_address,FoundSymTab;
 char thenewOpcode[32];
 char thenewOperand[32];
 int ArrayIndex=0, line=0,loc=0,Index=0;
 int foundOpcode=0,foundSymbol=0;
 int program_length;
 
 int w,n;
 int symbolplus=0;
 
	
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
	/* check dot comment */
	if(label[0]=='.')
		isDot=1;
	else
		isDot=0;
	/*check if the length >1 and is not comment*/
	if(length_line>1 && isDot!=1)
	{
		Index=0;
		
		IMArray[ArrayIndex].LineIndex=ArrayIndex;/*add line*/
		strcpy(label, ReadLabel(Buffer));/*get label*/
		
		strcpy(IMArray[ArrayIndex].LabelField,label);/*add label to IMArray */
		if(line==0)/*check line ==0 or not */
		{
			strcpy(opcode,ReadOprator(Buffer));/*get opcode*/
			strcpy(IMArray[ArrayIndex].OperatorCol,opcode);/*add opcode to IMArray*/
			
			
			if(!strcmp(opcode,"START"))/* check if it is START or not */
			{
				strcpy(operand,ReadOperand(Buffer));/*get operand*/
				strcpy(IMArray[ArrayIndex].OperandCol,operand);/*add operand to IMArray */
				LOCCTRXE[LocctrCounterXE]=strToHex(operand);
				starting_address=LOCCTRXE[LocctrCounterXE];/*set starting address*/
				
				
			}
			else
			{
				LOCCTRXE[LocctrCounterXE]=0;
				starting_address=LOCCTRXE[LocctrCounterXE];/*set starting address*/
			}
		}
		else/*if line != 0*/
		{
			strcpy(opcode,ReadOprator(Buffer));/*get opcode*/
			
			strcpy(IMArray[ArrayIndex].OperatorCol,opcode);/*add opcode to IMArray */
			strcpy(operand,ReadOperand(Buffer));/*get operand*/
			strcpy(IMArray[ArrayIndex].OperandCol,operand);/*add operand to IMArray*/
			
			if(strcmp(opcode,"END"))/*check if opcode != END*/
			{
				if(label[0]!='\0')
				{
					if(searchSymbolXE(label))/*search Symbol, if it exists, show error*/
					{
						fclose(fp);
						printf("ERROR: Duplicate Symbol\n");
						foundSymbol=0;
						exit(1);
					}
					recordSymbolXE(label);/*record symbol if it doesnot exist*/
				}
				
				
				/*check if the first letter of opcode == + or =*/
				if(opcode[0]=='+' || opcode[0]=='=' )
				{	n=0;
					/*get new opcode if + or = exists*/
					for(w=1;w<=strlen(opcode);w++)
					{	thenewOpcode[n++]=opcode[w];}
						thenewOpcode[n]='\0';
				}
				else
					{strcpy(thenewOpcode,opcode);
					 
					}
					
				int answ= searchOpcodeXE(thenewOpcode);
				/*check if opcode without + or = exists or not to calculate LOCCTR and LocctrCounter for loc*/
				if(searchOpcodeXE(thenewOpcode))
					{
					if(opcode[0]=='+'){
					LOCCTRXE[LocctrCounterXE]=loc + 4;/*loc + 4 if + exists*/
					if(IMArray[ArrayIndex-1].Loc==0)
					{	
						
						IMArray[ArrayIndex].Loc=loc;
					
					}
					else
						{IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
						}
					loc=LOCCTRXE[LocctrCounterXE];
					}
					else{
					LOCCTRXE[LocctrCounterXE]=loc + int (OPTAB[opIndexXE].Format-'0');
					
					IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
					
					loc=LOCCTRXE[LocctrCounterXE];}
					}
				else if(!strcmp(opcode,"WORD"))/*if it = WORD*/
					{LOCCTRXE[LocctrCounterXE]=loc+3;
					IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
					}
				else if(!strcmp(opcode,"RESW"))/* if it =RESW*/
					{
					LOCCTRXE[LocctrCounterXE]=loc+3*strToDec(operand);
					
					IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
					loc=LOCCTRXE[LocctrCounterXE];
					}
				else if(!strcmp(opcode,"RESB"))/*if it = RESB*/
					{
					LOCCTRXE[LocctrCounterXE]=loc+strToDec(operand);
					IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
					loc=LOCCTRXE[LocctrCounterXE];
					}
				else if(!strcmp(opcode,"BYTE"))/*if it = BYTE*/
					{
					LOCCTRXE[LocctrCounterXE]=loc+get_length(operand);	
					IMArray[ArrayIndex].Loc=LOCCTRXE[LocctrCounterXE-1];
					loc=LOCCTRXE[LocctrCounterXE];
					}
				else
					{
					IMArray[ArrayIndex].Loc=0;
					
					loc=LOCCTRXE[LocctrCounterXE-1];
					
					}
			}
			
			
		}
		
		
		LocctrCounterXE++;
		ArrayIndex++;
		
	}
	
	foundOpcode=0;
	line+=1;
	}
	program_length=LOCCTRXE[LocctrCounterXE-2]-LOCCTRXE[0];

/***********PASS 2 ***********/

signed long long fmt;
long long fmts;
long long f_opcode;
long long f_index;
long long f_address;

long long s_address;
long long fs_address;
long long subaddress=0x1000;
long long fcopcode;
int search_symbol;
int sum;
int m;
int k;
int lp=0;
symIndexXE=0;
for(lp=0;lp<ArrayIndex;lp++)/*set new SYMTAB*/
{
	char newlp[100];
	unsigned short int nLOC=IMArray[lp].Loc;
	strcpy(newlp,IMArray[lp].LabelField);
	
		newrecordSym(newlp,nLOC);
}
/*get object code*/
for(m=0;m<ArrayIndex;m++)
{
	f_opcode=0;
	f_index=0;
	f_address=0;
	
	strcpy(opcode,IMArray[m].OperatorCol);
	if(opcode[0]=='+' || opcode[0]=='=' )/*get new opcode(opcode without + or =*/
	{	n=0;
					
		for(w=1;w<=strlen(opcode);w++)
		{	thenewOpcode[n++]=opcode[w];}
			thenewOpcode[n]='\0';
	}
	else
	{strcpy(thenewOpcode,opcode);
					 
	}
	strcpy(operand,IMArray[m].OperandCol);
	if(operand[0]=='@' || operand[0]=='#' || operand[0]=='=')/*get new operand(operand without @, #, or =*/
	{	n=0;
					
		for(w=1;w<strlen(operand);w++)
		{	thenewOperand[n++]=operand[w];}
			thenewOperand[n]='\0';
			
				}
				
	else
		{strcpy(thenewOperand,operand);
					 
	}
	if(!strcmp(opcode,"BASE"))/*check if it BASE or not*/
		{for(search_symbol=0;search_symbol<symIndexXE;search_symbol++)/*search operand symbol for address*/
				{	
					
					if(!strcmp(thenewOperand,SYMTABXE[search_symbol].Label))
					{fs_address=(long)SYMTABXE[search_symbol].Address;
						
					}}
				}
				/* calculate object code with opcode which has + */
	if(opcode[0]=='+')     
	{	f_index=0x00100000;
		f_address=0x00000000;
		if(searchOpcodeXE(thenewOpcode))/*if opcode exist*/
		{	if(operand[0]=='#')
				{f_opcode=OPTAB[opIndexXE].theOpcode+1;/* + 1 to opcode if operand[0]=='#' */
				if(checkDigit(operand)==1)
				
					f_address=strToDec(thenewOperand);
				}
			else if(operand[0]=='@' || operand[0]=='=')
				f_opcode=OPTAB[opIndexXE].theOpcode+2;/* + 2 to opcode if operand[0]=='@' or =*/
			else
				f_opcode=OPTAB[opIndexXE].theOpcode+3;/* + 3 to opcode */
				f_opcode<<=24;
				for(search_symbol=0;search_symbol<symIndexXE;search_symbol++)
				{	
					
					if(!strcmp(thenewOperand,SYMTABXE[search_symbol].Label))
					{f_address=(long)SYMTABXE[search_symbol].Address;
						
					}
				}
				fmt=f_opcode+f_index+f_address;
				IMArray[m].ObjectCode=fmt;
				}}
	else if(searchOpcodeXE(opcode))/*cehck opcode which is without + */
	{	f_index=0x002000;
		fmt=0;
		for(search_symbol=0;search_symbol<symIndexXE;search_symbol++)
		{
		if(strcmp(thenewOperand,SYMTABXE[search_symbol].Label)==0)
			{f_address=(long)SYMTABXE[search_symbol].Address;/*get address of label*/
			
			 s_address=(long)IMArray[m+1].Loc;/*ger address of current operand*/
			printf("check   %x \n",f_address);
			 if(f_address>0x1000)
				f_address=f_address-0x1000;
			if(s_address>0x1000)
				s_address=s_address-0x1000;
			if(f_address>s_address)
				f_address=f_address-s_address;
			else if(f_address<s_address)
				f_address=f_address-s_address;
			else;
				break;
			}
		}
		
		if(operand[0]=='#')/*check if operand[0]=='#' or not to calculate opcode, index, address*/
			{f_opcode=OPTAB[opIndexXE].theOpcode+1;
			if(checkDigit(operand)==1)/*if is digit, convert to Dec*/
				f_address=strToDec(thenewOperand);	
			f_index=0x000000;
			f_opcode<<=16;
			IMArray[m].ObjectCode = f_opcode;}
		else if(operand[0]=='@' || operand[0]=='=')
			{f_opcode=OPTAB[opIndexXE].theOpcode+2;
			f_opcode<<=16;
			IMArray[m].ObjectCode = f_opcode;}
		else if(!strncmp(thenewOpcode,"CLEAR",5) || !strcmp(thenewOpcode,"COMPR")||!strcmp(thenewOpcode,"ADDR")||!strcmp(thenewOpcode,"DIVR")
		||!strcmp(thenewOpcode,"MULR")||!strcmp(thenewOpcode,"RMO")||!strcmp(thenewOpcode,"SHIFTL")||!strcmp(thenewOpcode,"SHIFTR")||
		!strcmp(thenewOpcode,"SUBR")||!strcmp(thenewOpcode,"SVC")||!strcmp(thenewOpcode,"TIXR"))
		{/*check opcode has format 2 and getand set mnemonic, index, address*/
		
		f_index=0x0000;
		f_opcode=OPTAB[opIndexXE].theOpcode+0;
		
		f_opcode <<=8;
		
		
		if(!strcmp(operand,"A")) f_address=0x00;
		else if(!strcmp(operand,"X")) 
		{f_address=0x0010;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"L")) 
		{f_address=0x0020;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"B")) 
		{f_address=0x30;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"S")) 
		{f_address=0x40;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"T")) 
		{f_address=0x50;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"F")) 
		{f_address=0x60;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"PC")) 
		{f_address=0x80;
		fmt=f_opcode+f_index+f_address;}
		else if(!strcmp(operand,"SW")) 
		{f_address=0x90;
		fmt=f_opcode+f_index+f_address;}
		else
		IMArray[m].ObjectCode = fcopcode;
		IMArray[m].ObjectCode=fmt;}
		else{
		f_opcode=OPTAB[opIndexXE].theOpcode+3;
		
		f_opcode <<=16;
		IMArray[m].ObjectCode = f_opcode;}
	
	IMArray[m].ObjectCode=fmt;
	/*check if exist ',' , 'X' or not */
	if(operand[strlen(operand)-2]==',' && operand[strlen(operand)-1]=='X')
	{
		f_index=0x008000;
		operand[strlen(operand)-2]='\0';
	}
	if(!strcmp(opcode,"LDCH") || !(strcmp(opcode,"STCH")))/*check if it LDCH or STCH to get index , address*/
			{f_index=0x00C000;
			f_address=fs_address;
			for(search_symbol=0;search_symbol<symIndexXE;search_symbol++)
				{	
					
					if(!strcmp("BUFFER",SYMTABXE[search_symbol].Label))
					{s_address=(long)SYMTABXE[search_symbol].Address;
						
					}
				}
				if(f_address>s_address)
					f_address=f_address-s_address;
				else
					f_address=s_address-f_address;
			}
	if(strcmp(opcode,"RSUB")==0 )/*check if equal RSUB or not to set address and index*/
		{f_address=0x000000;
		f_index=0x000000;}	
	
	
	fmt=f_opcode +f_index+f_address;
	IMArray[m].ObjectCode=fmt;
	}
	/*check if equal to WORD, BYTE*/
	else if (!strcmp(opcode,"WORD"))
	{
		strcmp(operand,IMArray[m].OperandCol);
		IMArray[m].ObjectCode=strToDec(operand);
	}
	else if (!strcmp(opcode,"BYTE"))
	{
		strcmp(operand,IMArray[m].OperandCol);
		IMArray[m].ObjectCode=0;
		
		if(operand[0]=='C' || operand[0]=='c' && operand[1]=='\'' )/*check C'EOF'*/
		{	
			for(k=2;k<=int(strlen(operand)-2);k++)
			{
				IMArray[m].ObjectCode=IMArray[m].ObjectCode +(int)operand[k];
				IMArray[m].ObjectCode<<=8;
			}
		}
		if(operand[0]=='X' || operand[0]=='x' && operand[1]=='\'')/*cehck X'05' */
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
createList(IMArray,ArrayIndex);/*create file .list*/
create_objcodeXE(IMArray, starting_address,program_length,ArrayIndex);/*create file .obj*/

free(IMArray);	
printf("Finished\n ");
fclose(fp);

}
/*record Symbol into Symtab*/
void recordSymbolXE(char* label){
	strcpy(SYMTABXE[symIndexXE].Label,label);
	
	SYMTABXE[symIndexXE].Address = LOCCTRXE[LocctrCounterXE-1];
	
	symIndexXE++;	
}
/*search Opcode if exist or not*/
int searchOpcodeXE(char * Mnemonic){
	int size = sizeof(OPTAB)/sizeof(SICXEOPTAB);
	FoundOnOptabXE_flag = 0;
	
	for(int i=0;i<size;i++){
		
		if(!strcmp(Mnemonic,OPTAB[i].Mnemonic)){
			opIndexXE = i;
			FoundOnOptabXE_flag = 1;
			break;
		}
	}
	
	return (FoundOnOptabXE_flag);
}
/*search symbol if exist or not*/
int searchSymbolXE(char* label){
	int FoundOnSymtab_flag = 0;

	for (int k= 0; k<=symIndexXE; k++){

		if (!strcmp(SYMTABXE[k].Label,label)){
			FoundOnSymtab_flag = 1;
			return (FoundOnSymtab_flag);
			break;
		}
		
	}
	return (FoundOnSymtab_flag);
}
/*create record into Sym tab */
void newrecordSym(char *newLabel, unsigned short int newLoc)
{
	
	SYMTABXE[symIndexXE].Address=newLoc;
	strcpy(SYMTABXE[symIndexXE].Label,newLabel);
	
	symIndexXE++;
}
