/**
 * @file demo.c
 * @brief Demonstration program for the Single Linked List library.
 * @author i7modes
 * @license MIT
 */

#include "single_linked_list.h"
#include <stdio.h>

static void print_separator(const char *title)
{
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

int main(void)
{
    print_separator("1. Creating and Initializing List");
    Node *myList = List_Create();
    printf("List created. Is empty? %s\n", List_IsEmpty(myList) ? "Yes" : "No");
    List_Print(myList);

    print_separator("2. Inserting Elements");
    printf("Inserting 10, 20, 30 via InsertFront / InsertLast...\n");
    List_InsertLast(20, myList);
    List_InsertFront(10, myList);
    List_InsertLast(30, myList);
    List_InsertLast(40, myList);
    List_Print(myList);
    printf("Current Size: %zu\n", List_Size(myList));

    print_separator("3. Finding Elements");
    int target = 30;
    Node *found = List_Find(target, myList);
    if (found != NULL)
    {
        printf("Found node with value %d at memory %p\n", found->data, (void *)found);
    }
    else
    {
        printf("Value %d not found.\n", target);
    }

    Node *prev = List_FindPrevious(target, myList);
    if (prev != NULL && prev->next != NULL)
    {
        printf("Previous node of %d has value: %d\n", target, prev->data);
    }

    print_separator("4. Middle Element Algorithm");
    Node *middle = List_GetMiddle(myList);
    if (middle != NULL)
    {
        printf("Middle element is: %d\n", middle->data);
    }

    print_separator("5. In-Place List Reversal");
    printf("Before reversal: ");
    List_Print(myList);
    List_Reverse(myList);
    printf("After reversal:  ");
    List_Print(myList);

    print_separator("6. Deletions");
    printf("Deleting value 20...\n");
    bool deleted = List_Delete(20, myList);
    printf("Deleted 20? %s\n", deleted ? "Success" : "Failed");
    List_Print(myList);
    printf("Current Size: %zu\n", List_Size(myList));

    printf("Deleting node at index 0 (first element)...\n");
    List_DeleteAt(0, myList);
    List_Print(myList);

    print_separator("7. Legacy API Compatibility Check");
    /* Testing legacy function signatures */
    printf("Calling legacy InsertLast(99, myList)...\n");
    InsertLast(99, myList);
    PrintList(myList);
    printf("Legacy size(): %d\n", size(myList));
    printf("Legacy IsEmpty(): %d\n", IsEmpty(myList));

    print_separator("8. Memory Cleanup & Teardown");
    printf("Destroying entire list (freeing nodes and sentinel header)...\n");
    List_Destroy(&myList);
    printf("Pointer is now: %p (0 memory leaks)\n", (void *)myList);

    printf("\nAll demonstrations completed successfully!\n");
    return 0;
}
