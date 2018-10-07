/*************************************************************
CS530 - SPRING 2013
Name: Linh Ngoc Nguyen
username: masc0755
Project: CSNNNN Assignment 1
Partner: Tuan Truong	username: masc0710
File: ins_evaluate.c

*************************************************************/
#include <stdio.h>
#include <string.h>
#include "a1.h"
/*check and evaluate opcode*/
char *instruction_evaluate(char *subbuff)
{
	char *opcode;
/*by compare the first 2 letters of the line to get opcode*/

if((strncmp(subbuff,"18",2)==0)||(strncmp(subbuff,"19",2)==0)||
	(strncmp(subbuff,"1A",2)==0)||(strncmp(subbuff,"1B",2)==0))
	opcode="ADD";
	
else if((strncmp(subbuff,"58",2)==0)||(strncmp(subbuff,"59",2)==0)||
	(strncmp(subbuff,"5A",2)==0)||(strncmp(subbuff,"5B",2)==0))
	opcode="ADDF";
		
else if((strncmp(subbuff,"90",2)==0)||(strncmp(subbuff,"91",2)==0)||
	(strncmp(subbuff,"92",2)==0)||(strncmp(subbuff,"93",2)==0))
	opcode="ADDR";	
	
else if((strncmp(subbuff,"40",2)==0)||(strncmp(subbuff,"41",2)==0)||
	(strncmp(subbuff,"42",2)==0)||(strncmp(subbuff,"43",2)==0))
	opcode="AND";
	
else if((strncmp(subbuff,"B4",2)==0)||(strncmp(subbuff,"B5",2)==0)||
	(strncmp(subbuff,"B6",2)==0)||(strncmp(subbuff,"B7",2)==0))
	opcode="CLEAR";
	
else if((strncmp(subbuff,"28",2)==0)||(strncmp(subbuff,"29",2)==0)||
	(strncmp(subbuff,"2A",2)==0)||(strncmp(subbuff,"2B",2)==0))
	opcode="COMP";
	
else if((strncmp(subbuff,"88",2)==0)||(strncmp(subbuff,"89",2)==0)||
	(strncmp(subbuff,"8A",2)==0)||(strncmp(subbuff,"8B",2)==0))
	opcode="COMPF";	
	
else if((strncmp(subbuff,"A0",2)==0)||(strncmp(subbuff,"A1",2)==0)||
	(strncmp(subbuff,"A2",2)==0)||(strncmp(subbuff,"A3",2)==0))
	opcode="COMPR";	
	
else if((strncmp(subbuff,"24",2)==0)||(strncmp(subbuff,"25",2)==0)||
	(strncmp(subbuff,"26",2)==0)||(strncmp(subbuff,"27",2)==0))
	opcode="DIV";
	
else if((strncmp(subbuff,"64",2)==0)||(strncmp(subbuff,"65",2)==0)||
	(strncmp(subbuff,"66",2)==0)||(strncmp(subbuff,"67",2)==0))
	opcode="DIVF";	
	
else if((strncmp(subbuff,"9C",2)==0)||(strncmp(subbuff,"9D",2)==0)||
	(strncmp(subbuff,"9E",2)==0)||(strncmp(subbuff,"9F",2)==0))
	opcode="DIVR";
	
else if((strncmp(subbuff,"C4",2)==0)||(strncmp(subbuff,"C5",2)==0)||
	(strncmp(subbuff,"C6",2)==0)||(strncmp(subbuff,"C7",2)==0))
	opcode="FIX";
	
else if((strncmp(subbuff,"C0",2)==0)||(strncmp(subbuff,"C1",2)==0)||
	(strncmp(subbuff,"C2",2)==0)||(strncmp(subbuff,"C3",2)==0))
	opcode="FLOAT";
	
else if((strncmp(subbuff,"F4",2)==0)||(strncmp(subbuff,"F5",2)==0)||
	(strncmp(subbuff,"F6",2)==0)||(strncmp(subbuff,"F7",2)==0))
	opcode="HIO";
	
else if((strncmp(subbuff,"3C",2)==0)||(strncmp(subbuff,"3D",2)==0)||
	(strncmp(subbuff,"3E",2)==0)||(strncmp(subbuff,"3F",2)==0))
	opcode="J";
	
else if((strncmp(subbuff,"30",2)==0)||(strncmp(subbuff,"31",2)==0)||
	(strncmp(subbuff,"32",2)==0)||(strncmp(subbuff,"33",2)==0))
	opcode="JEQ";

else if((strncmp(subbuff,"34",2)==0)||(strncmp(subbuff,"35",2)==0)||
	(strncmp(subbuff,"36",2)==0)||(strncmp(subbuff,"37",2)==0))
	opcode="JGT";

else if((strncmp(subbuff,"38",2)==0)||(strncmp(subbuff,"39",2)==0)||
	(strncmp(subbuff,"3A",2)==0)||(strncmp(subbuff,"3B",2)==0))
	opcode="JLT";

else if((strncmp(subbuff,"48",2)==0)||(strncmp(subbuff,"49",2)==0)||
	(strncmp(subbuff,"4A",2)==0)||(strncmp(subbuff,"4B",2)==0))
	opcode="JSUB";

else if((strncmp(subbuff,"00",2)==0)||(strncmp(subbuff,"01",2)==0)||
	(strncmp(subbuff,"02",2)==0)||(strncmp(subbuff,"03",2)==0))
	opcode="LDA";

else if((strncmp(subbuff,"68",2)==0)||(strncmp(subbuff,"69",2)==0)||
	(strncmp(subbuff,"6A",2)==0)||(strncmp(subbuff,"6B",2)==0))
	opcode="LDB";

else if((strncmp(subbuff,"50",2)==0)||(strncmp(subbuff,"51",2)==0)||
	(strncmp(subbuff,"52",2)==0)||(strncmp(subbuff,"53",2)==0))
	opcode="LDCH";

else if((strncmp(subbuff,"70",2)==0)||(strncmp(subbuff,"71",2)==0)||
	(strncmp(subbuff,"72",2)==0)||(strncmp(subbuff,"73",2)==0))
	opcode="LDF";

else if((strncmp(subbuff,"08",2)==0)||(strncmp(subbuff,"09",2)==0)||
	(strncmp(subbuff,"0A",2)==0)||(strncmp(subbuff,"0B",2)==0))
	opcode="LDL";

else if((strncmp(subbuff,"6C",2)==0)||(strncmp(subbuff,"6D",2)==0)||
	(strncmp(subbuff,"6E",2)==0)||(strncmp(subbuff,"6F",2)==0))
	opcode="LDS";

else if((strncmp(subbuff,"74",2)==0)||(strncmp(subbuff,"75",2)==0)||
	(strncmp(subbuff,"76",2)==0)||(strncmp(subbuff,"77",2)==0))
	opcode="LDT";

else if((strncmp(subbuff,"04",2)==0)||(strncmp(subbuff,"05",2)==0)||
	(strncmp(subbuff,"06",2)==0)||(strncmp(subbuff,"07",2)==0))
	opcode="LDX";

else if((strncmp(subbuff,"D0",2)==0)||(strncmp(subbuff,"D1",2)==0)||
	(strncmp(subbuff,"D2",2)==0)||(strncmp(subbuff,"D3",2)==0))
	opcode="LPS";

else if((strncmp(subbuff,"20",2)==0)||(strncmp(subbuff,"21",2)==0)||
	(strncmp(subbuff,"22",2)==0)||(strncmp(subbuff,"23",2)==0))
	opcode="MUL";

else if((strncmp(subbuff,"60",2)==0)||(strncmp(subbuff,"61",2)==0)||
	(strncmp(subbuff,"62",2)==0)||(strncmp(subbuff,"63",2)==0))
	opcode="MULF";

else if((strncmp(subbuff,"98",2)==0)||(strncmp(subbuff,"99",2)==0)||
	(strncmp(subbuff,"9A",2)==0)||(strncmp(subbuff,"9B",2)==0))
	opcode="MULR";

else if((strncmp(subbuff,"C8",2)==0)||(strncmp(subbuff,"C9",2)==0)||
	(strncmp(subbuff,"CA",2)==0)||(strncmp(subbuff,"CB",2)==0))
	opcode="NORM";

else if((strncmp(subbuff,"44",2)==0)||(strncmp(subbuff,"45",2)==0)||
	(strncmp(subbuff,"46",2)==0)||(strncmp(subbuff,"47",2)==0))
	opcode="OR";

else if((strncmp(subbuff,"D8",2)==0)||(strncmp(subbuff,"D9",2)==0)||
	(strncmp(subbuff,"DA",2)==0)||(strncmp(subbuff,"DB",2)==0))
	opcode="RD";

else if((strncmp(subbuff,"AC",2)==0)||(strncmp(subbuff,"AD",2)==0)||
	(strncmp(subbuff,"AE",2)==0)||(strncmp(subbuff,"AF",2)==0))
	opcode="RMO";

else if((strncmp(subbuff,"4C",2)==0)||(strncmp(subbuff,"4D",2)==0)||
	(strncmp(subbuff,"4E",2)==0)||(strncmp(subbuff,"4F",2)==0))
	opcode="RSUB";

else if((strncmp(subbuff,"A4",2)==0)||(strncmp(subbuff,"A5",2)==0)||
	(strncmp(subbuff,"A6",2)==0)||(strncmp(subbuff,"A7",2)==0))
	opcode="SHIFTL";

else if((strncmp(subbuff,"A8",2)==0)||(strncmp(subbuff,"A9",2)==0)||
	(strncmp(subbuff,"AA",2)==0)||(strncmp(subbuff,"AB",2)==0))
	opcode="SHIFTR";
	
else if((strncmp(subbuff,"F0",2)==0)||(strncmp(subbuff,"F1",2)==0)||
	(strncmp(subbuff,"F2",2)==0)||(strncmp(subbuff,"F3",2)==0))
	opcode="SIO";
	
else if((strncmp(subbuff,"EC",2)==0)||(strncmp(subbuff,"ED",2)==0)||
	(strncmp(subbuff,"EE",2)==0)||(strncmp(subbuff,"EF",2)==0))
	opcode="SSK";
	
else if((strncmp(subbuff,"0C",2)==0)||(strncmp(subbuff,"0D",2)==0)||
	(strncmp(subbuff,"0E",2)==0)||(strncmp(subbuff,"0F",2)==0))
	opcode="STA";
	
else if((strncmp(subbuff,"78",2)==0)||(strncmp(subbuff,"79",2)==0)||
	(strncmp(subbuff,"7A",2)==0)||(strncmp(subbuff,"7B",2)==0))
	opcode="STB";

else if((strncmp(subbuff,"54",2)==0)||(strncmp(subbuff,"55",2)==0)||
	(strncmp(subbuff,"56",2)==0)||(strncmp(subbuff,"57",2)==0))
	opcode="STCH";

else if((strncmp(subbuff,"80",2)==0)||(strncmp(subbuff,"81",2)==0)||
	(strncmp(subbuff,"82",2)==0)||(strncmp(subbuff,"83",2)==0))
	opcode="STF";

else if((strncmp(subbuff,"D4",2)==0)||(strncmp(subbuff,"D5",2)==0)||
	(strncmp(subbuff,"D6",2)==0)||(strncmp(subbuff,"D7",2)==0))
	opcode="STI";

else if((strncmp(subbuff,"14",2)==0)||(strncmp(subbuff,"15",2)==0)||
	(strncmp(subbuff,"16",2)==0)||(strncmp(subbuff,"17",2)==0))
	opcode="STL";

else if((strncmp(subbuff,"7C",2)==0)||(strncmp(subbuff,"7D",2)==0)||
	(strncmp(subbuff,"7E",2)==0)||(strncmp(subbuff,"7F",2)==0))
	opcode="STS";

else if((strncmp(subbuff,"E8",2)==0)||(strncmp(subbuff,"E9",2)==0)||
	(strncmp(subbuff,"EA",2)==0)||(strncmp(subbuff,"EB",2)==0))
	opcode="STSW";

else if((strncmp(subbuff,"84",2)==0)||(strncmp(subbuff,"85",2)==0)||
	(strncmp(subbuff,"86",2)==0)||(strncmp(subbuff,"87",2)==0))
	opcode="STT";

else if((strncmp(subbuff,"10",2)==0)||(strncmp(subbuff,"11",2)==0)||
	(strncmp(subbuff,"12",2)==0)||(strncmp(subbuff,"13",2)==0))
	opcode="STX";

else if((strncmp(subbuff,"1C",2)==0)||(strncmp(subbuff,"1D",2)==0)||
	(strncmp(subbuff,"1E",2)==0)||(strncmp(subbuff,"1F",2)==0))
	opcode="SUB";

else if((strncmp(subbuff,"5C",2)==0)||(strncmp(subbuff,"5D",2)==0)||
	(strncmp(subbuff,"5E",2)==0)||(strncmp(subbuff,"5F",2)==0))
	opcode="SUBF";

else if((strncmp(subbuff,"94",2)==0)||(strncmp(subbuff,"95",2)==0)||
	(strncmp(subbuff,"96",2)==0)||(strncmp(subbuff,"97",2)==0))
	opcode="SUBR";

else if((strncmp(subbuff,"B0",2)==0)||(strncmp(subbuff,"B1",2)==0)||
	(strncmp(subbuff,"B2",2)==0)||(strncmp(subbuff,"B3",2)==0))
	opcode="SVC";

else if((strncmp(subbuff,"E0",2)==0)||(strncmp(subbuff,"E1",2)==0)||
	(strncmp(subbuff,"E2",2)==0)||(strncmp(subbuff,"E3",2)==0))
	opcode="TD";

else if((strncmp(subbuff,"F8",2)==0)||(strncmp(subbuff,"F9",2)==0)||
	(strncmp(subbuff,"FA",2)==0)||(strncmp(subbuff,"FB",2)==0))
	opcode="TIO";

else if((strncmp(subbuff,"2C",2)==0)||(strncmp(subbuff,"2D",2)==0)||
	(strncmp(subbuff,"2E",2)==0)||(strncmp(subbuff,"2F",2)==0))
	opcode="TIX";

else if((strncmp(subbuff,"B8",2)==0)||(strncmp(subbuff,"B9",2)==0)||
	(strncmp(subbuff,"BA",2)==0)||(strncmp(subbuff,"BB",2)==0))
	opcode="TIXR";

else if((strncmp(subbuff,"DC",2)==0)||(strncmp(subbuff,"DD",2)==0)||
	(strncmp(subbuff,"DE",2)==0)||(strncmp(subbuff,"DF",2)==0))
	opcode="WD";
																																												
else
	opcode="";							
	return opcode;
}
