#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
  if (head == nullptr)
  {
    smaller = nullptr;
    larger = nullptr;
    return;
  }
  
  Node* nextNode = head -> next;

  if (head -> val <= pivot)
  {
    
      smaller = head;
      llpivot(nextNode, smaller -> next, larger, pivot);
  }
  else
  {
      larger = head;
      llpivot(nextNode, smaller, larger -> next, pivot);
  }
  head = nullptr;
}