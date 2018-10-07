/*
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 CSNNNN Assignment 3
Partner: Thon Saetern
Username: masc0954
File: a3
*/
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "a3.h"
using namespace std;

int main()
{
	pid_t pid;
	int amountOfTime;
	
	cout<<"Enter the amount of time for the countdown timer(0 for default): ";
	cin>>amountOfTime;
	if(amountOfTime<=0 )
		amountOfTime=6;
	cout<<"Current time"<<"                          "<<"Remain time";
	cout<<endl;
	
	signal(SIGTERM,messageFriendly);/*set signal to call message after finish count down*/
	pid=fork();
	
	
	if(pid==-1)
	{
		cout<<"error using pork. ";
		exit (1);
	}
	
	if(pid==0)/*first child*/
	{
		currentTimer(amountOfTime);
	}
	
	else/*parent*/
		pid=fork();
	
	if(pid==-1)
	{
		cout<<"error using pork. ";
		exit (1);
	}
	if(pid==0)/*second child*/
	{
		remainTimer(amountOfTime);
	}
	
	return 0;


}
