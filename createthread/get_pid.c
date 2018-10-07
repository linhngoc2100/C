/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 Assignment 1
Partner: Thon Saetern
Username: masc0954
File: get_pid.c
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/sem.h>
#include "a1.h"

void get_pid()
{
	pid_t pid;
	pid=fork();
	FILE *fp;
	if(pid==-1)/*check if pid =-1 and print error*/
	{
		fprintf(stderr,"error using fork");
		
	}
	/*parent process- check if it parent */
	if(pid>=1)
	{
		fp=fopen("PROCTAB.txt","a+");/*use file pointer to write to file PROCTAB.txt, a+ upadte file will new one without delete old one by adding at the end of text*/
		fprintf(fp,"PID = %d\n\r",pid);/*print the PID of the child process*/
		fclose(fp);
	}/*if it is not parent, it will create thread in child */
	else
	{
		create_thread();/*call function create_thread*/
	}
}
