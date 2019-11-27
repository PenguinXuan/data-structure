//Zhuoxuan Wang
//CruzID: zwang437
//PA 5

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
}NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int cursorIndex;
    int length;
    
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
// Private.
Node newNode(int node_data){
    Node N = malloc(sizeof(NodeObj));
    N->data = node_data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->cursorIndex = -1;
    L->length = 0;
    return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        Node temp = (*pL)->front;
        while(temp != NULL){
            Node curr = temp;
            temp = temp->next;
            free(curr);
          
        }
        free(*pL);
        *pL = NULL;
    }
    
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
    if(L == NULL){
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return(L->length);
}
// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if(L == NULL){
       printf("List Error: calling index() on NULL List reference\n");
       exit(1);
    }
    return L->cursorIndex;
}

// front()
// Returns front element of L.
// Pre: length() > 0
int front(List L){
    if(L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
     }
    if(length(L) <= 0){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return L->front->data;
}

// back()
// Returns back element of L.
// Pre: length() > 0
int back(List L){
    if(L == NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
      }
    if(length(L) <= 0){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
      }
      return L->back->data;
}

// get()
// Returns cursor element of L.
// Pre: length()>0
// index() >= 0
int get(List L){
    if(L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    if (index(L) < 0){
        printf("List Error: calling get() on undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

// equals()
// Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;
    
    if (A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while(eq && N != NULL){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// clear()
// Resets L to its original empty state.
void clear(List L){
    if(L == NULL){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    Node temp = L->front;
    while(temp != NULL){
        Node curr = temp;
        temp = temp->next;
        free(curr);
        
    }
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if(L == NULL){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if(length(L) > 0){
        L->cursor = L->back;
        L->cursorIndex = length(L) - 1;
    }
    
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if(L == NULL){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling movePrev() on an empty List\n");
        exit(1);
    }
    
    if(L->cursor != NULL && index(L) != 0){
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }
    else if(index(L) == 0){
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if(L == NULL){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling moveNext() on an empty List\n");
        exit(1);
    }
    if(L->cursor != NULL && index(L) != length(L) - 1){
        L->cursor = L->cursor->next;
        L->cursorIndex++;
    }
    else if(index(L) == length(L) - 1 || index(L) == -1){
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
    if(L == NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor != NULL){
        L->cursorIndex++;
    }
    
    Node N = newNode(data);
    
    if(length(L) == 0){
        L->front = N;
        L->back = N;
        L->length++;
    }
    else
    {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        L->length++;
    }
    
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data){
    if(L == NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    
    Node N = newNode(data);
    
    if(length(L) == 0){
        L->front = L->back = N;
        L->length++;
    }
    else if(length(L) == 1){
        N->prev = L->front;
        L->front->next = N;
        L->back = N;
        L->length++;
    }
    else{
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
        L->length++;
        
    }
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
    if(L == NULL){
       printf("List Error: calling insertBefore() on NULL List reference\n");
       exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
       printf("List Error: insertBefore() called with an undefined index on List");
       exit(1);
    }
    if(L->cursor != NULL){
        L->cursorIndex++;
    }
    if(L->cursor == L->front){
        Node N = newNode(data);
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        L->length++;
        return;
    }
    if(length(L) > 0 && index(L) >= 0){
        Node N = newNode(data);
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->length++;
    }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
    if(L == NULL){
       printf("List Error: calling insertAfter() on NULL List reference\n");
       exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
       printf("List Error: insertAfter() called with an undefined index on List");
       exit(1);
    }
    if(L->cursor == L->back){
        append(L,data);
        return;
    }
    if(length(L) > 0 && index(L) >= 0){
        Node N = newNode(data);
        N->prev = L->cursor;
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
        L->cursor->next = N;
        L->length++;
    }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    if(L->cursor != NULL){
        if(L->cursorIndex == 0){
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        else{
            L->cursorIndex--;
        }
        
    }
    Node N = L->front;
    if(length(L) > 1){
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else{
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&N);
    
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
    }
    if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    Node N = L->back;
    if(length(L) > 1){
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else{
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&N);
    
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
           printf("List Error: calling delete() on an empty List\n");
           exit(1);
    }
    if (index(L) < 0){
        printf("List Error: calling get() on undefined cursor\n");
        exit(1);
    }
    Node N = L->cursor;
    if(L->cursor == L->front){
        deleteFront(L);
    }
    else if(L->cursor == L->back){
        deleteBack(L);
    }
    else{
    
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->length--;
        freeNode(&N);
    }
    L->cursorIndex = -1;
}

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    if(L == NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    Node curr = NULL;
    for(curr = L->front; curr != NULL; curr = curr->next){
        fprintf(out, "%d ", curr->data);
    }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    if(L == NULL){
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(1);
    }
    
    List clone = newList();
    Node curr = L->front;
    
    while(curr != NULL){
        append(clone, curr->data);
        curr = curr->next;
        
    }
    return clone;
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B){
    if(A == NULL){
        return B;
    }
    if(B == NULL){
        return A;
    }
    A->back->next = B->front;
    B->front->prev = A->back;
    
    return A;
}







