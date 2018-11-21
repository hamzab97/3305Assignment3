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
}

// job_t *get_next_job(int mode, d_linked_list_t* jobs, int time_quantum) {
// 	return roundRobin(jobs, time_quantum);
// }

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
	bubbleSort(jobs);
	return firstComeFirstServe(jobs);
}

//method to handle next job if mode is RR
job_t *roundRobin(d_linked_list_t* jobs, int time_quantum){
	//get time of head of linked last
	//if time of job > quantum time
	//time = time of job - quantum time
	//new job = same as head except update value of time
	//update value of head to be same as quantum time
	//return head
	job_t *j;
	// j = jobs->head; //get the head of the job
	void* timeRequired = jobs->head->value; //get the required_time
	if (timeRequired > time_quantum){
		void *newTime = timeRequired - time_quantum;
		enqueue(jobs, newTime); //enqueue the left over time at the end of the queue
		jobs->head->value = time_quantum;
	}
	j = dequeue(jobs); //dequeue the first job in the linkedlist
	return j;
}
