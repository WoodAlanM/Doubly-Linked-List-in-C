#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

// This will make it easier later on to traverse the
// nodes i think.
static int nodeCount = 0;

// I think typedef makes it so you can define your own
// variable type.  I think struct lets you put a bunch
// of things together.

typedef struct node
{
    int data;
    struct node* nextNode;
    struct node* previousNode;
} node;

node* head = NULL;
node* tail = NULL;
node* temp = NULL;

int get_nodecount() {
    return nodeCount;
}

// This will be to add nodes to the list
// at the end of the doubly linked list.
void addnode(int d)
{
    // Looks like malloc allocates memory dynamically
    // so this will make a new node that i can use
    // later down the line. This addNode function
    // will add a node at the end of the DLL
    // will need to consider memory DEallocation
    node* nodeToAdd = (node*)malloc(sizeof(node*));

    // So it seems the -> thing is used to assign
    // values to different elements of a struct
    // in this case elements of the node
    nodeToAdd->data = d;
    nodeToAdd->nextNode = NULL;
    nodeToAdd->previousNode = NULL;

    // Regardless of whether the head is null a
    // pointer to the new node will be necessary
    // if the head is null i can put that new node
    // in it and assign it to the head node pointer
    if (head == NULL) {
        // Head becomes that empty node that was
        // allocated earlier
        head = nodeToAdd;
        // Since the head did not exist it is now also the tail
        tail = head;
    } else {
        // The tail's next node is assigned the new node
        tail->nextNode = nodeToAdd;
        // New node's previous node is assigned the tail
        nodeToAdd->previousNode = tail;
        // Tail is set to the new node
        tail = nodeToAdd;
    }

    printf("Node with data (%d) added.\n\n", d);

    nodeCount++;
}// End addNode

void displaynodevalues() {
    if (nodeCount > 0) {
        node* workingNode = head;

        // This will loop through each node and display its data value
        while (workingNode != NULL) {
            printf("%d ", workingNode->data);
            workingNode = workingNode->nextNode;
        }
        printf("\n\n");
    } else {
        printf("\nNo nodes to display. Try adding a node.\n");
    }
}// End displaynodevalues

void removenode(int nodeIndex) {
    int indexCounter = 0;
    int notRemoved = 1;

    if (nodeCount == 1 && nodeIndex == 0) {
        // Remove head node
        node* workingNode = head;
        // Set tail designator to NULL
        head = NULL;
        tail = NULL;
        // Free the head and tail node from memory
        free(workingNode);
        nodeCount--;
    } else if (nodeCount > 1 && nodeIndex <= nodeCount - 1) {
        // Remove node at chosen location
        node* workingNode = head;
        while (workingNode != NULL && notRemoved) {
            indexCounter++;
            workingNode = workingNode->nextNode;

            node* tempPrevious;
            node* tempNext;

            // If the index is reached, do the stuff
            if (indexCounter == nodeIndex) {
                // Switch up links
                tempPrevious = workingNode->previousNode;
                tempNext = workingNode->nextNode;

                tempPrevious->nextNode = tempNext;
                tempNext->previousNode = tempPrevious;

                notRemoved = 0;

                // Frees workingNode from memory
                free(workingNode);

                nodeCount--;
            }
        }
    } else {
        // Inform user that chose index is out of bounds.
        printf("\nChosen node index is not valid. There are currently (%d) nodes in the list.\n", nodeCount);
        printf("Please try again with  a valid index.");
    }
}// End removenode

int examinenode(int nodeIndex) {
    int indexCounter = 0;

    if (nodeCount == 1 && nodeIndex == 0) {
        return head->data;
    } else if (nodeCount > 1 && nodeIndex <= nodeCount - 1) {
        // Remove node at chosen location
        node* workingNode = head;
        while (workingNode != NULL) {
            indexCounter++;
            workingNode = workingNode->nextNode;

            // If the index is reached, do the stuff
            if (indexCounter == nodeIndex) {
                return workingNode->data;
            }
        }
    } else {
        // Inform user that chose index is out of bounds.
        printf("\nChosen node index is not valid. There are currently (%d) nodes in the list.\n", nodeCount);
        printf("Please try again with  a valid index.");
    }
    return -1;
}// End examinenode

void changenodevalue(int nodeIndex, int newValue) {
    int indexCounter = 0;

    if (nodeCount == 1 && nodeIndex == 0) {
        head->data = newValue;
    } else if (nodeCount > 1 && nodeIndex <= nodeCount - 1) {
        // Remove node at chosen location
        node* workingNode = head;
        while (workingNode != NULL) {
            indexCounter++;
            workingNode = workingNode->nextNode;

            // If the index is reached, do the stuff
            if (indexCounter == nodeIndex) {
                workingNode->data = newValue;
            }
        }
    } else {
        // Inform user that chose index is out of bounds.
        printf("\nChosen node index is not valid. There are currently (%d) nodes in the list.\n", nodeCount);
        printf("Please try again with  a valid index.");
    }
}// End changenodevalue

// Need a checker that i can run every time a sort is done
// I can use this to end the while loop when the list is finally sorted.

// ** THIS DOES NOT WORK **
int checknodessorted() {
    if (nodeCount > 1) {
        node* workingNode = head;
        node* nextWorkingNode = workingNode->nextNode;
        node* tempNextNext;

        // This will loop through each node and compare it to the next
        // if the next value is ever less than the first it will return 0
        while (workingNode != NULL) {
            if (workingNode->data < nextWorkingNode->data) {
                if (nextWorkingNode->nextNode != NULL) {
                    tempNextNext = nextWorkingNode->nextNode;
                    workingNode = nextWorkingNode;
                    nextWorkingNode = tempNextNext;
                }
            } else {
                return 0;
            }
        }
    }
    return 1;
}// End checknodessorted

void sortnodes() {
    node* workingNode = head;
    node* nextWorkingNode = workingNode->nextNode;
    node* tempWorkingNodeNext;
    node* tempWorkingNodePrevious;
    node* tempNextWorkingNodeNext = nextWorkingNode->nextNode;
    node* tempNextWorkingNodePrevious;;

// This works to flip the first and second node
//    if (workingNode->data > nextWorkingNode->data) {
//        // Swap nodes if the next value is greater than the first
//        if (workingNode == head) {
//
//            head = nextWorkingNode;
//            workingNode->previousNode = nextWorkingNode;
//            workingNode->nextNode = tempNextWorkingNodeNext;
//            nextWorkingNode->nextNode = workingNode;
//            nextWorkingNode->previousNode = NULL;
//
//            free(tempNextWorkingNodeNext);
//        }
//    }

    while (workingNode->nextNode != NULL) {
        if (workingNode->data > nextWorkingNode->data) {
            // Swap nodes if the next value is greater than the first
            if (workingNode == head) {

                head = nextWorkingNode;
                workingNode->previousNode = nextWorkingNode;
                workingNode->nextNode = tempNextWorkingNodeNext;
                nextWorkingNode->nextNode = workingNode;
                nextWorkingNode->previousNode = NULL;

                // Will need to move this to later in the code
                //free(tempNextWorkingNodeNext);
            } else {

            }
        }
    }

}// End sortnodes
