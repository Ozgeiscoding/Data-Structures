#define _CRT_SECURE_NO_WARNINGS
// fig12_01.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>

// self-referential structure with typedef
typedef struct listNode {
    char data;               // each listNode contains a character
    struct listNode* nextPtr; // pointer to next node
} ListNode;                  // typedef for struct listNode

// prototypes
void insert(ListNode** sPtr, char value);
char deleteNode(ListNode** sPtr, char value);
int isEmpty(ListNode* sPtr);
void printList(ListNode* currentPtr);
void instructions(void);

int main(void) {
    ListNode* startPtr = NULL; // initially there are no nodes
    char item = '\0';         // char entered by user

    instructions();           // display the menu
    printf("%s", "? ");
    int choice = 0;          // user's choice
    scanf("%d", &choice);

    // loop while user does not choose 3
    while (choice != 3) {
        switch (choice) {
        case 1: // insert an element
            printf("%s", "Enter a character: ");
            scanf("\n%c", &item);
            insert(&startPtr, item); // insert item in list
            printList(startPtr);
            break;
        case 2: // delete an element
            if (!isEmpty(startPtr)) { // if list is not empty
                printf("%s", "Enter character to be deleted: ");
                scanf("\n%c", &item);

                // if character is found, remove it
                if (deleteNode(&startPtr, item)) { // remove item
                    printf("%c deleted.\n", item);
                    printList(startPtr);
                }
                else {
                    printf("%c not found.\n\n", item);
                }
            }
            else {
                puts("List is empty.\n");
            }
            break;
        default:
            puts("Invalid choice.\n");
            instructions();
            break;
        }

        printf("%s", "? ");
        scanf("%d", &choice);
    }

    puts("End of run.");
    return 0;
}

// display program instructions to user
void instructions(void) {
    puts("Enter your choice:\n"
        " 1 to insert an element into the list.\n"
        " 2 to delete an element from the list.\n"
        " 3 to end.");
}

// insert a new value into the list in sorted order
void insert(ListNode** sPtr, char value) {
    ListNode* newPtr = (ListNode*)malloc(sizeof(ListNode));

    if (newPtr != NULL) { // is space available?
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNode* previousPtr = NULL;
        ListNode* currentPtr = *sPtr;

        // loop to find the correct location in the list
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // insert new node at beginning of list
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else { // insert new node between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    }
}

// delete a list element
char deleteNode(ListNode** sPtr, char value) {
    if (*sPtr == NULL) return '\0'; // empty list

    // delete first node if a match is found
    if (value == (*sPtr)->data) {
        ListNode* tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        free(tempPtr);
        return value;
    }

    ListNode* previousPtr = *sPtr;
    ListNode* currentPtr = (*sPtr)->nextPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && currentPtr->data != value) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }

    // delete node at currentPtr
    if (currentPtr != NULL) {
        ListNode* tempPtr = currentPtr;
        previousPtr->nextPtr = currentPtr->nextPtr;
        free(tempPtr);
        return value;
    }

    return '\0';
}

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNode* sPtr) {
    return sPtr == NULL;
}

// print the list
void printList(ListNode* currentPtr) {
    if (isEmpty(currentPtr)) {
        puts("List is empty.\n");
    }
    else {
        puts("The list is:");

        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("NULL\n");
    }
}
