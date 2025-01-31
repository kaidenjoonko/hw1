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

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE

  //base case
  if(in == nullptr){
    return;
  }

  Node* curr = in;
  in = in->next;

  //odd
  if(curr->value % 2 == 1){
    curr->next = odds;
    odds = curr;
  //even
  }else if(curr->value % 2 == 0){
    curr->next = evens;
    evens = curr;
  }

  split(in, odds, evens);
}

/*
check if divisible by 2, if so then point current node to even, then split with next node

*/

/* If you needed a helper function, write it here */
