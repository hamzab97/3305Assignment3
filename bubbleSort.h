/*
name: Hamza Bana
email: hbana3@uwo.ca

bubbleSort.h contains the definitions for the bubbleSort.c file and bubbleSort implementation to be used fo rthe linked_list
*/

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "stdlib.h"
#include "d_linked_list.h"

//void method to sort the given linked list, jobs, passed in as a parameter
void bubbleSort(d_linked_list_t*);

//void method to swpa the data in the given 2 nodes
void swap(struct d_node*, struct d_node*);

#endif
