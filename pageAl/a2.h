/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 2
Partner: Thon Saetern
Username: masc0954
File: a2.h
**************************************/
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <list>

#ifndef FRAMES
#define FRAMES

using namespace std;

class Frames
{
public:
	Frames(int inValue);
	~Frames();
	int* openFile(int* tempArray);  
	
	int LRU();
	int clock(int frameSize);
	int OPT(int frameSize);

private:
	Frames(const Frames& src);

	list <int> myListPage;
	int pageFault;
	int* aPage;
	int totalPage;


};

#endif
