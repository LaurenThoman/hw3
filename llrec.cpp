#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

// helper funct
static void llpivotHelper(Node* head, Node*& smaller, 
Node*& tailSmaller, Node*& larger, Node*& tailLarger, int pivot) {
  if (head == nullptr) return;    // base case

  Node* next = head->next;
  head->next = nullptr;

  if (head->val <= pivot) {
    if (smaller == nullptr) {   // first node in smaller list
      smaller = head;
      tailSmaller = head;
    } else {
      tailSmaller->next = head;   // appends to end
      tailSmaller = head;
    }
  } else {
    if (larger == nullptr) {    // first node in larger list
      larger = head;
      tailLarger = head;
    } else {
      tailLarger->next = head;  
      tailLarger = head;
    }
  }

  llpivotHelper(next, smaller, tailSmaller, larger, tailLarger, pivot);
}

// llpivot funct
void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
  // Initialize the output lists as empty.
  smaller = nullptr;
  larger = nullptr;
  Node* tailSmaller = nullptr;
  Node* tailLarger = nullptr;

  // process list order
  llpivotHelper(head, smaller, tailSmaller, larger, tailLarger, pivot);
  
  // og list empty
  head = nullptr;
}