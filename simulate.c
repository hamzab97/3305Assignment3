/******************************************************************************
*
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* simulate.c
*
******************************************************************************/

#include "simulate.h"

int memory, max_memory, mode, time_quantum;
FILE *fp;
d_linked_list_t *jobs;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //declare pthread lock

void* run(void *j)
{
	// printf("mode is %d\n", mode);
	job_t *job;
	// if (time_quantum || mode == 3)//(mode == 3) //if mode is roundRobin then also pass time quantum
	// 	job = roundRobin(jobs, time_quantum);
	// else job = get_next_job(mode, jobs);
	job = get_next_job(mode, jobs);
	int number, required_memory;
	// printf("job number: %d now has time: %d and mem %d\n", job->number, job->required_time, job->required_memory);

	while (job != NULL)
	{

		number = job->number;
		required_memory = job->required_memory;

		/**********************************************************************
		* checks if the memory requested exceeds maximum memory
		**********************************************************************/
		if (required_memory > max_memory)
		{
			/******************************************************************
			* inform user that the job won't run, clean and terminate
			******************************************************************/
			print_exceed_memory(fp, number);
			free(job);
			return NULL;
		}

		/**********************************************************************
		* runs job
		**********************************************************************/
		if (required_memory <= memory) {
			//check for RR
			if (mode == 3 && job->required_time > time_quantum){
				//time greater than quantum
				RRexecuation(job); //execute RR thread
				enqueue(jobs, job); //put the job back on the queue because its not fully complete
			}else
				execute_job(job);
			//junlock
		}

		/**********************************************************************
		* checks if the memory requested exceeds current available memory
		**********************************************************************/
		else
		{
			/******************************************************************
			* inform user that the job doesn't have enough resources at the
			* moment, add the job back to the list
			******************************************************************/
			print_insufficient_memory(fp, number);

			enqueue(jobs, job);
		}
		//update how you get the job
		job = get_next_job(mode, jobs);

	}

	return NULL;
}

/******************************************************************************
*
******************************************************************************/
void simulate(int memory_value, int mode_value, int time_quantum_value,
	d_linked_list_t *list)
{
	/**************************************************************************
	* opens output file
	**************************************************************************/
	fp = fopen(SYSTEM_OUTPUT, WRITE);

	/**************************************************************************
	* check if the system file is in the directory
	**************************************************************************/
	if (fp == NULL)
	{
		printf("Unable to open %s file\n", SYSTEM_OUTPUT);
		exit(FAILURE);
	}

	/**************************************************************************
	* set global variables
	**************************************************************************/
	memory = max_memory = memory_value;

	/**************************************************************************
	* set executing mode
	**************************************************************************/
	mode = mode_value;
	time_quantum = time_quantum_value;
	print_mode(fp, mode);
	jobs = list;

	//initialize lock
	// if (pthread_mutex_init(&lock, NULL) != 0){
	// 	printf("mutex init failed\n");
	// }

	/**************************************************************************
	* create threads and run jobs
	**************************************************************************/
	pthread_t threads[NUMBER_OF_THREADS];
	for (int i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		if (pthread_create(&threads[i], NULL, run, NULL))
		{
			printf("Error: failed to create thread.\n");
			exit(FAILURE);
		}
	}

	/**********************************************************************
	* wait for the jobs to finish executing
	**********************************************************************/
	for (int i = 0; i < NUMBER_OF_THREADS; ++i)
		pthread_join(threads[i], NULL);

	//destroy locks
	// pthread_mutex_destroy(&lock);
}

/*
method for execution of roundRobin alg
*/
void RRexecuation(job_t *job) {
	// printf("\nstart job number: %d now has time: %d and mem %d\n", job->number, job->required_time, job->required_memory);
	// printf("RR accessed, stack size %d\n", jobs->size);
	int number = job->number,
		required_memory = job->required_memory;

	/******************************************************************
	* inform user that the job started executing and allocate mrmory
	******************************************************************/
	print_starting(fp, number);
	allocate_memory(required_memory);

	/******************************************************************
	* run the job
	******************************************************************/
	sleep(time_quantum);

	/******************************************************************
	* inform user that the job finished executing
	******************************************************************/
	print_completed(fp, number);
	// free(job);

	/******************************************************************
	* deallocate memory
	******************************************************************/
	deallocate_memory(required_memory);
	job->required_time = job->required_time - time_quantum; //find the time left to run
	// printf("end job number: %d now has time: %d and mem %d\n\n", job->number, job->required_time, job->required_memory);
}

void execute_job(job_t *job) {


	int number = job->number,
		required_memory = job->required_memory;

	/******************************************************************
	* inform user that the job started executing and allocate mrmory
	******************************************************************/
	print_starting(fp, number);
	allocate_memory(required_memory);

	/******************************************************************
	* run the job
	******************************************************************/
	sleep(job->required_time);

	/******************************************************************
	* inform user that the job finished executing
	******************************************************************/
	print_completed(fp, number);
	if (mode != 2){ //sjf handles memory management
		free(job);
	}

	/******************************************************************
	* deallocate memory
	******************************************************************/
	deallocate_memory(required_memory);

}

void allocate_memory(int r) {
	//put lock
	pthread_mutex_lock(&lock);
	memory -= r;
	print_allocate_memory(fp, memory, r);
	//unlock
	pthread_mutex_unlock(&lock);
}

void deallocate_memory(int r) {
	memory += r;
	print_deallocate_memory(fp, memory, r);
}
