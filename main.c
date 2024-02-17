// Doubly Linked List in C
// Rules:
// 1. No using ChatGPT.
// 2. I'll think of this one later.
//
// Instructions from Jon:
// A doubly linked list with a command line menu to
// add nodes, delete nodes, change the value stored
// at a given node, and sort the nodes
//
// Jon did not say, but i think i should probably
// make it so i can see the value of a given node
// and more specifically i should make it so i can
// choose where to put the nodes.

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

// This will make it easier later on to traverse the
// nodes i think.
int nodeCount = 0;

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
}

int main()
{
    // Variable for controlling the interface loop
    int notQuit = 1;
    int choiceNumber = -1;

    printf("-----------------------------------------------------\n");
    printf("Alan Wood implementation of a doubly linked list in C\n");
    printf("-----------------------------------------------------\n\n");

    // So this returns the input from the user and shows it on the console
    while (notQuit) {
        choiceNumber = getUserChoice(0, nodeCount);

        // This should handle if the user chooses to add a node.
        if (choiceNumber == 1) {
            addnode(getUserChoice(1, nodeCount));
        } else if (choiceNumber == 2) {
            displaynodevalues();
        } else if (choiceNumber == 3) {
            removenode(getUserChoice(3, nodeCount));
        } else if (choiceNumber == 7) {
            notQuit = 0;
        }
    }

    return 0;
}// End main
