/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 2
Partner: Thon Saetern
Username: masc0954
File: a2.cpp
**************************************/
#include <iostream>
#include <list>
#include "Frames.h"

using namespace std;

int main()
{
	int sizeOfFrames;
	int faults=0;

	cout<< "Enter the number of frames: ";
	cin>>sizeOfFrames;
	cout<<endl;
	
	cout<<"Begin to process"<<endl;
	cout<<endl;
	Frames myFrames1(sizeOfFrames);
	
	
	faults=myFrames1.OPT(sizeOfFrames);
	cout << "Total number of page faults for OPT is: " << faults << endl;
	cout << endl;
	Frames myFrames2(sizeOfFrames);
	
	faults=myFrames2.clock(sizeOfFrames);
	cout << "Total number of page faults for clock is: " << faults << endl;
	cout << endl;
	
	Frames myFrames3(sizeOfFrames); 
	
	faults=myFrames3.LRU();
	cout << "Total number of page faults for LRU is: " << faults << endl;
	cout << endl;	
	cout<<"End process";
	cout<<endl;	
}
