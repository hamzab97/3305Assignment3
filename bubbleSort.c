/*
name: Hamza Bana
email: hbana3@uwo.ca

bubbleSort.c contains the methods for bubbleSort implementation to be used fo rthe linked_list
*/

#include "bubbleSort.h"

void bubbleSort(d_linked_list_t* jobs){
  struct d_node *head = jobs->head;
  //continue for loop to iterate through the entire linkedlist
  int sorted = 0; //boolean variable to keep track of whetehr the linked list is sorted or not
  //0 is false, 1 is true
  int lastUnsorted = jobs->size-1; //position of the last sorted element
  while (sorted == 0){
    //while array not sorted
    sorted = 1; //set sorted to true, assume its sorted except otherwise
    //iterate through linked list
    for (int i = 0; i < lastUnsorted; i++){
      //iuf value of current element is greater than the value fo the next element
      //means the array is out of order
      if (head->value > head->next->value){
        //call swap to swap values of the two nodes
        swap(head, head->next);
        sorted = 0; //set sorted to false because array was not sorted
      }
      head = head->next; //set head equal to the next element
    }
    lastUnsorted --; //update the positon of the last unsroted variable
  }
}

//create temporary variable and store value of p
//swap value of p with value of q
//update value of q to the old value of p which was stored in temp var
void swap (struct d_node* p, struct d_node* q){
  void *temp = p->value;
  p->value = q->value;
  q->value = temp;
}
