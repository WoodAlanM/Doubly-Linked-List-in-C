#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int getUserChoice(int option, int nodeCount)
{
    // Apparently booleans are not a built-in
    // data type.  So I will use an integer to
    // keep things more vanilla(?)
    int notChosen = 1;
    int userInput;
    int newValue;

    switch (option) {
        // This option is for if the main menu is to be displayed
        case 0:
            printf("\nDLL Operations:\n");
            printf("1. Add node\n");
            printf("2. Display node values\n");
            printf("3. Remove node\n");
            printf("4. Change node value\n");
            printf("5. Sort nodes\n");
            printf("6. Examine node\n");
            printf("7. Insert node\n");
            printf("8. Quit\n");
            printf("---------------\n");
            printf("Make a selection: ");
            // Apparently when you put the "&" symbol in
            // front of a variable it gets the memory
            // address of that variable and not the value
            // associated with it.  I imagine that will
            // become more clear over time.
            while (notChosen) {
                scanf("%d", &userInput);
                notChosen = 0;
            }
            return userInput;
        // This option is for if add node was chosen
        case 1:
            printf("\nEnter an integer for the node value: ");
            while (notChosen) {
                scanf("%d", &userInput);
                notChosen = 0;
            }
            return userInput;
        case 2:
            printf("\nDisplaying node values...\n\n");
            return userInput;
        case 3:
            if (nodeCount > 0) {
                printf("\nEnter an integer for the index of the node to remove: ");
                while (notChosen) {
                    scanf("%d", &userInput);
                    notChosen = 0;
                }
                return userInput;
            } else {
                printf("\nThere are no nodes to remove.  Please try again.\n");
                return -1;
            }
        case 4:
            if (nodeCount > 0) {
                printf("\nEnter the index of the node to change: ");
                while (notChosen) {
                    scanf("%d" , &userInput);
                    notChosen = 0;
                }
                if (userInput <= nodeCount - 1) {
                    notChosen = 1;
                    printf("\nEnter the new value for the node: ");
                    while (notChosen) {
                        scanf("%d", &newValue);
                        notChosen = 0;
                    }
                    changenodevalue(userInput, newValue);
                    printf("\nValue changed to (%d).", newValue);
                    break;
                } else {
                    printf("\nChosen index is out of bounds.  Please try again.\n");
                    break;
                }
            } else {
                printf("\nThere are no nodes to change.  Please try again.\n");
                break;
            }
        case 5:
            if (nodeCount > 1) {
                printf("\nSorting the list...\n");
                sortnodes();
            } else if (nodeCount == 1) {
                printf("\nThere is only one list element.  Please try again.\n");
            } else {
                printf("\nThere are no list elements.  Please try again.\n");
            }
            break;
        case 6:
            printf("\nEnter the index of the node to examine: ");
            while (notChosen) {
                scanf("%d", &userInput);
                notChosen = 0;
            }
            return userInput;
        case 7:
            printf("\nEnter the index after which the node will be inserted: ");
            while (notChosen) {
                scanf("%d", &userInput);
                notChosen = 0;
            }
            if (userInput < nodeCount - 1) {
                notChosen = 1;
                printf("\nEnter the value for the node: ");
                while (notChosen) {
                    scanf("%d", &newValue);
                    notChosen = 0;
                }
                if (insertnodeatindex(newValue, userInput)) {
                    printf("\nNode with value (%d) added at index (%d).", newValue, userInput);
                } else {
                    printf("\nFailed to insert node.");
                }
                break;
            } else if (userInput == nodeCount - 1) {
                printf("\nChosen index is at the end of the list.  User add node instead.\n");
                break;
            } else {
                printf("\nChosen index is out of bounds.  Please try again.\n");
                break;
            }
        default:
            printf("\nWhatcha doin here?");
            break;
    }
    // I don't think it will get here, but putting return 0 eliminates
    // warnings, and I think I like that.
    return 0;
}// End getUserChoice
