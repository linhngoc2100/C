/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 2
Partner: Thon Saetern
Username: masc0954
File: pageAl.cpp
**************************************/
#include <iostream>
#include <list>
#include "Frames.h"

Frames::Frames(int inValue)
	:myListPage(inValue,0)
{}

Frames::~Frames()
	{delete[] aPage;
}

int* Frames::openFile(int* arrayPage) 
{
	FILE* fp;
	char buffer[256]; 
	char temp[3] = "\0";
	int i = 0;
	totalPage = 0;
	arrayPage = new int[99];

	fp = fopen("pages.txt", "r+");     /*open pages.txt file*/
	fgets(buffer,100,fp);            

	while(buffer[i] != '\0')        /*loop until empty or null*/           
	{
		if(buffer[i] != ' ')/*check if it is not space or not*/
		{
			if(buffer[i+1] != ' ')            /*two digit number */
			{
				temp[0] = buffer[i];          
				temp[1] = buffer[i+1];        
				i++;
			}
			else                              /*single digit number */  
			{
				temp[0] = buffer[i];
				temp[1] = '\0';
			}
			
			arrayPage[totalPage] = atoi(temp); 
			totalPage++;
		}
		i++; 
	}
	 
	
	fclose(fp);
	
	return arrayPage; 
	

}

int Frames::LRU()
{	
	int* pageArray = openFile(aPage);
	list<int>::iterator it = myListPage.begin();
	list<int>::iterator it2 = myListPage.end();
	int p, pageFault = 0;

	for(int i = 0; i < totalPage; i++)
	{
		for (it = myListPage.begin(); it != myListPage.end(); ++it)
		{
			p = *it;

			if(*it == pageArray[i])/*check if page exist or not*/
			/*if it exists, remove and insert the new one*/
			{
				++it;
				
				myListPage.remove(p);
				myListPage.push_front(pageArray[i]);
				goto L1;
							
			
			}
		}

			myListPage.pop_back();  /*delete the last element in list and reduce the size by 1*/
			myListPage.push_front(pageArray[i]);/*insert at the beginning*/
			pageFault++;

L1:;			
	}
	
return pageFault;
}

int Frames::clock(int frameSize)
{
	int* pageArray = openFile(aPage);
	list<int>::iterator it = myListPage.begin();
	list<int>::iterator it2 = myListPage.begin(); // clock pointer

	int* flag;
	int k = 0;
	int checkFlag = 1;
	int f = 0;
	int pageFault = 0;

	int secondFlag = 0;

	flag = new int[frameSize]; 
	for(k = 0; k < frameSize; k++)
		flag[k] = 0;         /*set frames's flag=0*/

	for(int i = 0; i < totalPage; i++)
	{

		/* loop the current frame and flag */
		for (secondFlag = 0,it = myListPage.begin(); it != myListPage.end(), secondFlag < myListPage.size(); ++it,secondFlag++)
		{
			if(*it == pageArray[i])
			{
				flag[secondFlag] = 1;//set use bit to 1
				goto L2;			
			}	
		} 
			
		
		while(checkFlag != 0) /* loop until flag=0 and then put page into memory*/
		{
			if(it2 == myListPage.end()) // check clock pointer and flag 
			{ 
				it2 = myListPage.begin();
				k = 0;
			}
			if(flag[k] == 0)   /*swap if flag  =0*/
			{
				*it2 = pageArray[i];     /*get new value by replace current value*/
				flag[k] = 1;   /*set flag to 1*/
				it2++;                   /*go next one*/
				k++;               
				checkFlag = 0;            /*set flag to 0 after go next one*/
				pageFault++;	/*increase size number fault*/
			}
			else/*set flag =0 and found flag=1 and move clock pointer to next one*/
			{
				flag[k] = 0;
				k++;              
				it2++;                   /*move clock pointer to next one*/
			}	
		}
		checkFlag = 1; /*reset flag to 1*/
L2:   ;
			
	}
delete[] flag;			
	
return pageFault;
	

}

int Frames::OPT(int frameSize)
{
	int* pageArray = openFile(aPage);
	list<int>::iterator it = myListPage.begin();
	list<int>::iterator it2 = myListPage.begin(); 
	
	
	int* flag;
	int k = 0;
	int checkFlag = 1;
	
	int secondFlag = 0;
	int optimal = 0;
	int pageFault = 0;

	flag = new int[frameSize]; 
	for(k = 0; k < frameSize; k++)
		flag[k] = 0;         /*set frames' flag to 0*/

	
	for(int i = 0; i < totalPage; i++)
	{
		optimal=0;
		/*loop for looking the current frame and its current flag */
		for (it = myListPage.begin(),secondFlag = 0; it != myListPage.end(), secondFlag <myListPage.size(); ++it, secondFlag++)
		{

			if(*it == pageArray[i])/*go to next one if page exists*/
			{
				goto L3;			
			}	
		} 
		/*check the next page by loop to get optimal*/
		for(int j = i + 1; j < totalPage; j++)
		{
			
			for (k = 0,it = myListPage.begin(); it != myListPage.end(), k < myListPage.size(); ++it,k++)
			{
				if(*it == pageArray[j])
				{
					optimal++;
					flag[k] = 1;/*set flag to 1 if page exist*/

					if(optimal == (frameSize - 1))
					{
						
						goto L4;
					}
				}	
			}
		}
L4:  
		for (it = myListPage.begin(), k = 0; it != myListPage.end(), k < myListPage.size(); ++it,k++)
		{
			if(flag[k] == 0)
			{
				*it = pageArray[i];
				pageFault++; 

				for(k = 0; k < frameSize; k++)
					flag[k] = 0;         

				goto L3;	
			}
		}
L3:         ;
			
	}

delete [] flag;	
return pageFault;
	
}
