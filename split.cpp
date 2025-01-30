/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  // base case if node is empty
  if(in == NULL){
    return;
  }
  // copy head to a temp pointer so we can keep track of where the list starts
  Node* temp = in;
  // change the head pointer to point to the next node for recursion purposes
  in = in->next;

  // deference and access the value at the temp is pointing to 
  if((temp->value % 2 == 0)){
    // if it's even, then the temp needs to point to the evens head
    temp->next = evens;
    evens = temp;
  }
  else{
    // if it's odd, then the temp needs to point to the odds head
    temp->next = odds;
    odds = temp;
  }
  // recursively call the split function for the next node
  split(in, odds, evens);
}

/* If you needed a helper function, write it here */

