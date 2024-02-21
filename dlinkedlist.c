#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
        // Set tail designator to NULL
        head = NULL;
        tail = NULL;
        // Free the head and tail node from memory
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
int checknodessorted() {
    if (nodeCount > 1) {
        node* checkNode = head;
        node* checkNextNode = checkNode->nextNode;
        // This will loop through each node and compare it to the next
        // if the next value is ever less than the first it will return 0
        while (checkNode != NULL) {
            if (checkNode->data < checkNextNode->data) {
                if (checkNextNode->nextNode != NULL) {
                    checkNode = checkNode->nextNode;
                    checkNextNode = checkNode->nextNode;
                } else {
                    return 1;
                }
            } else {
                return 0;
            }
        }
    }
    return 1;
}// End checknodessorted

void sortnodes() {
    // So APPARENTLY when it comes to swapping the connections
    // I need to use pointer pointers which i can then use to swap
    // the links between nodes.  Who knew?
    node* workingNode = head;
    node* nextWorkingNode = workingNode->nextNode;
    node** tempNodeOne;
    node** tempNodeTwo;

    int notSorted = 1;
    int nodeCounter = 0;

    // Getting close here
    while (notSorted) {
        nodeCounter++;
        if (workingNode->data > nextWorkingNode->data) {
            // Swap nodes if the next value is greater than the first
            if (workingNode == head) {
                // Swaps the first node with the second
                // and reassigns head and tail
                head = nextWorkingNode;
                nextWorkingNode->previousNode = NULL;
                nextWorkingNode->nextNode = workingNode;
                workingNode->previousNode = nextWorkingNode;
                workingNode->nextNode = NULL;
                if (nodeCount == 2) {
                    tail = workingNode;
                }
            } else if (nextWorkingNode == tail) {
                // Swaps the tail with the node before
                tempNodeOne = &workingNode->previousNode;
                nextWorkingNode->previousNode = *tempNodeOne;
                nextWorkingNode->nextNode = workingNode;
                workingNode->previousNode = nextWorkingNode;
                tail = workingNode;
                tail->nextNode = NULL;
            } else {
                // Swaps the two inner nodes
                // and reconnects outer nodes
                tempNodeOne = &nextWorkingNode->nextNode;
                tempNodeTwo = &workingNode->previousNode;
                workingNode->nextNode = *tempNodeOne;
                workingNode->previousNode = nextWorkingNode;
                nextWorkingNode->previousNode = *tempNodeTwo;
                nextWorkingNode->nextNode = workingNode;

                // Iterate to next set of nodes
                workingNode = workingNode->nextNode;
                nextWorkingNode = nextWorkingNode->nextNode;
            }
        } else {
            workingNode = workingNode->nextNode;
            nextWorkingNode = nextWorkingNode->nextNode;
        }
        if(nodeCounter == nodeCount - 1) {
            if (checknodessorted()) {
                notSorted = 0;
            } else {
                nodeCounter = 0;
                workingNode = head;
                nextWorkingNode = workingNode->nextNode;
            }
        }
    }
}// End sortnodes
