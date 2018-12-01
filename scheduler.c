/******************************************************************************
*
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* scheduler.c
*
******************************************************************************/

#include "scheduler.h"
#include "pthread.h"

//define constants
#define FCFS 0
#define LIFO 1
#define SJF 2
#define RR 3
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER; //declare pthread lock
// job_t globalVarShortestJob;
/**
handle:
first come first serve
last in first out
shortest job first
round robin
**/

/*
method to get he next job on the stack
check if the size of the list is greater than 0, if so, continue, else, return NULL
*/
job_t *get_next_job(int mode, d_linked_list_t* jobs) {
	if (jobs->size > 0){
		//put lock
		job_t *j;
		pthread_mutex_lock(&lock1);
		//check parameter passed and call appropriate method
		if (mode == FCFS || mode == RR)
			j= firstComeFirstServe(jobs);
		else if (mode == LIFO)
			j= lastInFirstOut(jobs);
		else if (mode == SJF)
			j= shortestJobFirst(jobs);
		//unlock
		pthread_mutex_unlock(&lock1);
		return j;
	}
	return NULL;
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
	printf("\nSJF accessed, stack size %d\n\n", jobs->size);
	//iterate and find the smallest job
	struct d_node *minNode = jobs->head; //set head as the minimum node
	int minValue = ((job_t*)minNode->value)->required_time;
	// printf("head value is: %d and size of list is: %d\n", minValue, jobs->size);
	// printf("min node value is %d\n", ((job_t*)minNode)->required_memory);
	struct d_node *temp = jobs->head;
	for (int i = 1; i < jobs->size; i++){
		temp = temp->next; //iterate through the linked list
		if (((job_t*)temp->value)->required_time < minValue){
			minNode = temp;
			minValue = ((job_t*)temp->value)->required_time;
		}
	}
	//create copy of what minnode is pointing to
	//minNode now points to the node with the smallest valu ein the linked list
	// printf("min node value is: %d\n", minValue);
	struct d_node *shortJob = (struct d_node*)malloc(sizeof(struct d_node));
	memcpy(shortJob, minNode, sizeof(struct d_node)); //copy node
	// printf("shortjob node value is %d\n", ((job_t*)shortJob->value)->required_time);
	erase(jobs, minNode); //call the erase method
	return ((job_t*)shortJob->value);
}
