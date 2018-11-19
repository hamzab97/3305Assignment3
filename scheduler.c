/******************************************************************************
*
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* scheduler.c
*
******************************************************************************/

#include "scheduler.h"
#define FCFS 0
#define LIFO 1
#define SJF 2
#define RR 3
/**
handle:
first come first serve
last in first out
shortest job first
round robin
**/

job_t *get_next_job(int mode, d_linked_list_t* jobs) {
	if (mode == FCFS)
		return firstComeFirstServe(jobs);
	else if (mode == LIFO)
		return lastInFirstOut(jobs);
	else if (mode == SJF)
		return shortestJobFirst(jobs);
	else
		return roundRobin(jobs);
}

//method to handle next job if mode is FCFS
job_t *firstComeFirstServe(d_linked_list_t* jobs){
	job_t *j;
	j = dequeue(jobs); //dequeue the first job in the linkedlist
	return j;
}

//method to handle next job if mode is LIFO
job_t *lastInFirstOut(d_linked_list_t* jobs){
	job_t *j;
	j = pop(jobs); //get the last job in the linked list
	return j;
}

//method to handle next job if mode is SJF
job_t *shortestJobFirst(d_linked_list_t* jobs){
	job_t *j;
	j = jobs->head;
	int shortest = j->value;
	job_t *temp;
	temp =
	for (int i = 1; i < jobs->size; i++){

	}
	return j;
}

//method to handle next job if mode is RR
job_t *roundRobin(d_linked_list_t* jobs){
	//same alg as FIFO because it returns hte first job
	//if the first job cant be completed in alloted time, then
	//it gets pushed back to the list
	job_t *j;
	j = dequeue(jobs); //dequeue the first job in the linkedlist
	return j;
}
