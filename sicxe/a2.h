/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 2
Partner: Tuan Truong	username :masc0710

*************************************************************/
#include<stdio.h>
#include<string.h>
#ifndef H_INTERMEDIATEARRAY_INCLUDED
#define H_INTERMEDIATEARRAY_INCLUDED
#ifndef H_SYMBOLTAB_INCLUDED
#define H_SYMBOLTAB_INCLUDED
/*intermediate file*/
typedef struct IntermediateArray{
	unsigned short int LineIndex;
	unsigned short int Loc;
	
	unsigned long int ObjectCode;
	char LabelField[32];
	char OperatorCol[32];
	char OperandCol[32];
};
/*symtab*/
typedef struct symbolTab
{
	char Label[50];
	int Address;
};


char *ReadLabel(char *line);/*get label*/
char *ReadOprator(char *line);/*get operator*/
char *ReadOperand(char *line);/*get operand*/
void SkipSpace(char *line);/*skip space*/
int strToHex(char *operand);/*convert str to hex*/
int strToDec(char *operand);/*convert str to Dec*/
int get_length(char *operand);
void createList(struct IntermediateArray *, int Index);/*create file .list*/
void create_objcode(struct IntermediateArray *, int starting_address,int program_length);/*create sic.obj*/
void create_objcodeXE(struct IntermediateArray *, int starting_address,int program_length, int ArrayIndex);/*create sicXE.obj*/
int searchOpcode(char *opcode);/*search opcode*/
int searchSymbol(char *label);/*search symbol*/
void recordSymbolXE(char *label);/*record symbol*/
int searchOpcodeXE(char *opcode);
int searchSymbolXE(char *label);
void recordSymbol(char *label);
char getnewop(char * opcode);
void readfilesic(char *filename);/*read file sic*/
void readfilexe(char *filename);/*read file sicXE*/
void newrecordSym(char *newLabel, unsigned short int newLoc);/*new record*/

int checkDigit (char *operand);/*check if digit or not*/
#endif
#endif

