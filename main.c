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

int main()
{
    // Variable for controlling the interface loop
    int notQuit = 1;
    int choiceNumber = -1;
    int nodeCount = 0;

    printf("-----------------------------------------------------\n");
    printf("Alan Wood implementation of a doubly linked list in C\n");
    printf("-----------------------------------------------------\n");

    // So this returns the input from the user and shows it on the console
    while (notQuit) {
        // Get the node count from dlinkedlist
        nodeCount = get_nodecount();

        // Initial menu prompt
        choiceNumber = getUserChoice(0, nodeCount);

        switch (choiceNumber) {
            case 1:
                addnode(getUserChoice(1, nodeCount));
                break;
            case 2:
                displaynodevalues();
                break;
            case 3:
                removenode(getUserChoice(3, nodeCount));
                break;
            case 4:
                getUserChoice(4, nodeCount);
                break;
            case 5:
                if (checknodessorted) {
                    printf("\nNodes are sorted.\n");
                } else {
                    printf("\nNodes are NOT sorted.\n");
                }
                //getUserChoice(5, nodeCount);
                break;
            case 6:
                printf("\nThe value of the selected node is (%d).\n", examinenode(getUserChoice(6, nodeCount)));
                break;
            case 7:
                notQuit = 0;
                break;
            default:
                notQuit = 0;
        }
    }
    return 0;
}// End main
