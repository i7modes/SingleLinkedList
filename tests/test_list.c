/**
 * @file test_list.c
 * @brief Comprehensive automated unit test suite for Single Linked List.
 * @author i7modes
 * @license MIT
 */

#include "single_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int total_tests = 0;
static int passed_tests = 0;

#define TEST_ASSERT(expr, msg) do { \
    total_tests++; \
    if (expr) { \
        passed_tests++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while (0)

static void test_initialization_and_empty(void)
{
    printf("\n--- Test: Initialization & Empty Check ---\n");
    Node *list = List_Create();
    TEST_ASSERT(list != NULL, "List_Create returns non-NULL sentinel header");
    TEST_ASSERT(List_IsEmpty(list) == true, "New list is empty");
    TEST_ASSERT(List_Size(list) == 0, "New list size is 0");
    List_Destroy(&list);
    TEST_ASSERT(list == NULL, "List_Destroy nullifies list pointer");
}

static void test_insertions_and_order(void)
{
    printf("\n--- Test: Insertions & Order ---\n");
    Node *list = List_Create();

    List_InsertLast(10, list);
    List_InsertLast(20, list);
    List_InsertLast(30, list);
    TEST_ASSERT(List_Size(list) == 3, "Size is 3 after 3 InsertLast calls");

    List_InsertFront(5, list);
    TEST_ASSERT(List_Size(list) == 4, "Size is 4 after InsertFront");

    int buffer[5];
    size_t copied = List_ToArray(list, buffer, 5);
    TEST_ASSERT(copied == 4, "Copied 4 elements to array");
    TEST_ASSERT(buffer[0] == 5 && buffer[1] == 10 && buffer[2] == 20 && buffer[3] == 30,
                "Array elements match expected insertion order (5, 10, 20, 30)");

    // Insert after specific position
    Node *pos = List_Find(10, list);
    TEST_ASSERT(pos != NULL, "Found node with value 10");
    List_Insert(15, list, pos);
    TEST_ASSERT(List_Size(list) == 5, "Size is 5 after inserting 15 after 10");

    Node *node15 = List_GetAt(2, list);
    TEST_ASSERT(node15 != NULL && node15->data == 15, "Node at index 2 is 15");

    List_Destroy(&list);
}

static void test_search_and_get(void)
{
    printf("\n--- Test: Search & Retrieval ---\n");
    Node *list = List_Create();
    List_InsertLast(100, list);
    List_InsertLast(200, list);
    List_InsertLast(300, list);

    TEST_ASSERT(List_Find(200, list) != NULL, "Find existing element 200");
    TEST_ASSERT(List_Find(999, list) == NULL, "Find non-existent element returns NULL");

    Node *prev200 = List_FindPrevious(200, list);
    TEST_ASSERT(prev200 != NULL && prev200->data == 100, "FindPrevious(200) returns node with 100");

    Node *prev100 = List_FindPrevious(100, list);
    TEST_ASSERT(prev100 == list, "FindPrevious on first element returns sentinel header");

    TEST_ASSERT(List_GetAt(0, list)->data == 100, "GetAt(0) returns 100");
    TEST_ASSERT(List_GetAt(2, list)->data == 300, "GetAt(2) returns 300");
    TEST_ASSERT(List_GetAt(10, list) == NULL, "GetAt out of bounds returns NULL");

    List_Destroy(&list);
}

static void test_deletions(void)
{
    printf("\n--- Test: Deletions ---\n");
    Node *list = List_Create();
    List_InsertLast(1, list);
    List_InsertLast(2, list);
    List_InsertLast(3, list);
    List_InsertLast(4, list);

    TEST_ASSERT(List_Delete(99, list) == false, "Delete non-existent value returns false");

    // Delete middle element
    TEST_ASSERT(List_Delete(2, list) == true, "Delete middle element 2 returns true");
    TEST_ASSERT(List_Size(list) == 3, "Size decreases to 3");
    TEST_ASSERT(List_Find(2, list) == NULL, "2 is no longer found in list");

    // Delete at index 0 (front)
    TEST_ASSERT(List_DeleteAt(0, list) == true, "DeleteAt(0) returns true");
    TEST_ASSERT(List_Size(list) == 2, "Size is now 2");
    TEST_ASSERT(List_GetAt(0, list)->data == 3, "New head node data is 3");

    // Delete remaining
    TEST_ASSERT(List_Delete(3, list) == true, "Delete 3");
    TEST_ASSERT(List_Delete(4, list) == true, "Delete 4");
    TEST_ASSERT(List_IsEmpty(list) == true, "List is now empty");
    TEST_ASSERT(List_Size(list) == 0, "List size is 0");

    List_Destroy(&list);
}

static void test_reversal(void)
{
    printf("\n--- Test: List Reversal ---\n");
    Node *list = List_Create();

    // Reversal on empty list
    List_Reverse(list);
    TEST_ASSERT(List_IsEmpty(list) == true, "Reversing empty list is safe");

    // Reversal on 1 element list
    List_InsertLast(42, list);
    List_Reverse(list);
    TEST_ASSERT(List_GetAt(0, list)->data == 42, "Reversing single element list retains element");

    // Multi-element reversal
    List_InsertLast(43, list);
    List_InsertLast(44, list);
    List_InsertLast(45, list); // [42, 43, 44, 45]

    List_Reverse(list); // Should be [45, 44, 43, 42]
    int buffer[4];
    List_ToArray(list, buffer, 4);
    TEST_ASSERT(buffer[0] == 45 && buffer[1] == 44 && buffer[2] == 43 && buffer[3] == 42,
                "List correctly reversed in place");

    List_Destroy(&list);
}

static void test_middle_and_cycle(void)
{
    printf("\n--- Test: Middle Element & Cycle Detection ---\n");
    Node *list = List_Create();

    TEST_ASSERT(List_GetMiddle(list) == NULL, "GetMiddle on empty list returns NULL");
    TEST_ASSERT(List_HasCycle(list) == false, "Empty list has no cycle");

    List_InsertLast(10, list);
    List_InsertLast(20, list);
    List_InsertLast(30, list);
    TEST_ASSERT(List_GetMiddle(list)->data == 20, "Middle of [10, 20, 30] is 20");

    List_InsertLast(40, list);
    TEST_ASSERT(List_GetMiddle(list)->data == 30, "Middle of [10, 20, 30, 40] is 30 (second middle)");

    TEST_ASSERT(List_HasCycle(list) == false, "Linear list has no cycle");

    // Create a temporary cycle for testing: 40 -> 20
    Node *node40 = List_Find(40, list);
    Node *node20 = List_Find(20, list);
    node40->next = node20;

    TEST_ASSERT(List_HasCycle(list) == true, "Cycle detected with Floyd's algorithm");

    // Break the cycle before cleanup
    node40->next = NULL;
    TEST_ASSERT(List_HasCycle(list) == false, "Cycle resolved");

    List_Destroy(&list);
}

int main(void)
{
    printf("========================================\n");
    printf("  Single Linked List Automated Tests\n");
    printf("========================================\n");

    test_initialization_and_empty();
    test_insertions_and_order();
    test_search_and_get();
    test_deletions();
    test_reversal();
    test_middle_and_cycle();

    printf("\n========================================\n");
    printf("  Results: %d/%d assertions passed\n", passed_tests, total_tests);
    printf("========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
