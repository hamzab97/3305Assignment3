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

job_t *get_next_job(int mode, d_linked_list_t* jobs) {
	//put lock
	job_t *j;
	pthread_mutex_lock(&lock1);
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
	// bubbleSort(jobs);
	//iterate and find the smallest job
	struct d_node *minNode = jobs->head; //set head as the minimum node
	int minValue = ((job_t*)minNode->value)->required_time;
	printf("head value is: %d and size of list is: %d\n", minValue, jobs->size);
	// printf("min node value is %d\n", ((job_t*)minNode)->required_memory);
	struct d_node *temp = jobs->head;
	for (int i = 1; i < jobs->size; i++){
		printf("hoi\n");
		// printf("hello\n");
		temp = temp->next; //iterate through the linked list
		if (((job_t*)temp->value)->required_time < minValue){
			minNode = temp;
			minValue = ((job_t*)temp->value)->required_time;
		}
	}
	//create copy of what minnode is pointing to
	//minNode now points to the node with the smallest valu ein the linked list
	printf("min node value is: %d\n", minValue);
	struct d_node *shortJob = (struct d_node*)malloc(sizeof(struct d_node));
	memcpy(shortJob, minNode, sizeof(struct d_node)); //copy node
	erase(jobs, minNode); //call the erase method
	return ((job_t*)shortJob->value);
}

//method to handle next job if mode is RR
// job_t *roundRobin(d_linked_list_t* jobs, int time_quantum){
// 	// pthread_mutex_lock(&lock1);
// 	//get time of head of linked last
// 	//if time of job > quantum time
// 	//time = time of job - quantum time
// 	//new job = same as head except update value of time
// 	//update value of head to be same as quantum time
// 	//return head
// 	job_t *j;
// 	// j = jobs->head; //get the head of the job
// 	j = dequeue(jobs); //dequeue the first job in the linkedlist
// 	int timeRequired = j->required_time; //get the required_time
// 	printf("job time is %d and time quantum is %d\n", timeRequired, time_quantum);
// 	if (timeRequired > time_quantum){
// 		int newTime = timeRequired - time_quantum;
// 		int number = j->number;
// 		int requiredmemory = j->required_memory;
// 		printf("new time is %d, number ios %d, required mem is %d\n", newTime, number, requiredmemory);
// 		enqueue(jobs, (void*)init_job(number, requiredmemory, newTime));
// 		j->required_time = time_quantum;
// 		printf("time for the next job to run is %d\n", j->required_time);
// 	}
// 	// pthread_mutex_lock(&lock1);
// 	return j;
// }
