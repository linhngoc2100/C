/*
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 3
Partner: Thon Saetern
Username: masc0954
File: time_countdown.cpp
*/
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<signal.h>
#include "a3.h"

using namespace std;

void currentTimer(int nTime)
{
	time_t rawtime=time(0);/*get current time*/
	
	string rawtimeString;
	while(1){
		if(time(0)!=rawtime)
		{
			if(nTime<0)
				raise(SIGTERM);/*get message if remain time <0*/
			rawtime=time(0);/*get current time*/
			rawtimeString=ctime(&rawtime);/*convert time to string*/
			rawtimeString.erase(24,1);
			cout<<"\r";
			cout<<rawtimeString;
			
			fflush(stdout);
			nTime--;
			
			
		}
		
	}


}

void remainTimer(int nTime)
{
	time_t rawtime = time(0);
	string rawtimeString=ctime(&rawtime);
	
	while(1){
		if(time(0)!=rawtime)
		{
			
			cout<<"\r";
			rawtime=time(0);/*get current time*/
			cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<convertSeconds(nTime);/*get remain time and count down*/
			fflush(stdout);
			
			nTime--;
			if(nTime<0)
				exit(1);/*exit if amount time <0*/
		}
	
	
	}

}

string convertSeconds(int se)
{
    stringstream ss;
    int minutes = se / 60;
    int seconds = se % 60;
    ss << ((minutes < 10) ? "0" : "" ) << minutes;
    ss << ":";
    ss << ((seconds < 10) ? "0" : "")  << seconds;

    return ss.str();
}

void messageFriendly(int m)/*print message*/
{
	cout<<endl;
	cout<<"Congratulations. "<<endl;
	exit(0);

}
