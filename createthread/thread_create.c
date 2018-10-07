/**************************************
CS570 - SUMMER 2013
Name: Linh Ngoc Nguyen
Username: masc0939
Project: CS570 Assignment 1
Partner: Thon Saetern
Username: masc0954
File: thread_create.c
**************************************/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <unistd.h>
#include "a1.h"

sem_t sem;
#define NUMBER_OF_THREADS 10 /*define number of thread*/

void create_thread()
{
	
	pthread_t threads[NUMBER_OF_THREADS];
	int status,i;
	for(i=0;i<NUMBER_OF_THREADS;i++)/* create loop to call 10 threads */
	{
		sem_init(&sem,0,1);/*initiate semaphore*/
		status=pthread_create(&threads[i],NULL,add_thread,(void*)i);
		if(status!=0)/*print error if thread does not exist*/
		{
			printf("Oops, pthread_create returned error code %d0\n",status);
			break;
		}
	}
	sem_destroy(&sem);/*destroy or release semaphore */
	pthread_exit(NULL);
}

void *add_thread(void* tid)
{
	sleep(1);/*each time entered thread sleep 1 second*/
	FILE *fp;
	int threadid;
	pthread_t pthread_self(void);/*give ability to use self*/
	threadid = pthread_self();/*set variable equal to value of current thread id*/
	sem_wait(&sem);/*block thread if another thread is in process*/
	fp=fopen("PROCTAB.txt","a+");
	/*print the current thread and thread id to the file */
	fprintf(fp,"thread ID %d is running from thread %d\n\r",threadid,tid);
	printf("thread ID %i is running\n\r",threadid);
	/*if any thread blocked makes a decision to take next one */
	sem_post(&sem);
	pthread_exit(NULL);/*clean up */
	fclose(fp);
	
}
