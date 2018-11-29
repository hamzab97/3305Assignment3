/******************************************************************************
*
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* scheduler.h
*
******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "job.h"
#include "d_linked_list.h"
#include "helper.h"
// #include "bubbleSort.h"
// #include <pthread.h>

// job_t *get_next_job(int, d_linked_list_t*, int);
job_t *get_next_job(int, d_linked_list_t*);
job_t *firstComeFirstServe(d_linked_list_t*);
job_t *lastInFirstOut(d_linked_list_t*);
job_t *shortestJobFirst(d_linked_list_t*);
job_t *roundRobin(d_linked_list_t*, int);

#endif
