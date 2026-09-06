/**
 * @file single_linked_list.c
 * @brief Implementation of a Singly Linked List with a Sentinel Header Node in C.
 * @author i7modes
 * @license MIT
 */

#include "single_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

Node* List_Create(void)
{
    Node *header = (Node *)malloc(sizeof(Node));
    if (header == NULL)
    {
        fprintf(stderr, "Error: Out of memory in List_Create.\n");
        return NULL;
    }

    header->data = 0;
    header->next = NULL;
    return header;
}

Node* List_MakeEmpty(Node *list)
{
    if (list != NULL)
    {
        List_Clear(list);
        return list;
    }

    return List_Create();
}

void List_Clear(Node *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *current = list->next;
    list->next = NULL;

    while (current != NULL)
    {
        Node *temp = current->next;
        free(current);
        current = temp;
    }
}

void List_Destroy(Node **list_ptr)
{
    if (list_ptr == NULL || *list_ptr == NULL)
    {
        return;
    }

    List_Clear(*list_ptr);
    free(*list_ptr);
    *list_ptr = NULL;
}

/* -------------------------------------------------------------------------- */
/*                              Query / Observers                             */
/* -------------------------------------------------------------------------- */

bool List_IsEmpty(const Node *list)
{
    return (list == NULL || list->next == NULL);
}

bool List_IsLast(const Node *pos, const Node *list)
{
    (void)list;
    return (pos != NULL && pos->next == NULL);
}

size_t List_Size(const Node *list)
{
    if (list == NULL)
    {
        return 0;
    }

    size_t count = 0;
    const Node *current = list->next;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

Node* List_Find(int value, const Node *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    Node *current = list->next;
    while (current != NULL && current->data != value)
    {
        current = current->next;
    }

    return current;
}

Node* List_FindPrevious(int value, const Node *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    Node *current = (Node *)list;
    while (current->next != NULL && current->next->data != value)
    {
        current = current->next;
    }

    return current;
}

Node* List_GetAt(size_t index, const Node *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    Node *current = list->next;
    size_t i = 0;

    while (current != NULL && i < index)
    {
        current = current->next;
        i++;
    }

    return current;
}

/* -------------------------------------------------------------------------- */
/*                              Insertion & Deletion                          */
/* -------------------------------------------------------------------------- */

bool List_Insert(int value, Node *list, Node *pos)
{
    (void)list;
    if (pos == NULL)
    {
        return false;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Out of memory in List_Insert.\n");
        return false;
    }

    newNode->data = value;
    newNode->next = pos->next;
    pos->next = newNode;
    return true;
}

bool List_InsertFront(int value, Node *list)
{
    if (list == NULL)
    {
        return false;
    }
    return List_Insert(value, list, list);
}

bool List_InsertLast(int value, Node *list)
{
    if (list == NULL)
    {
        return false;
    }

    Node *current = list;
    while (current->next != NULL)
    {
        current = current->next;
    }

    return List_Insert(value, list, current);
}

bool List_Delete(int value, Node *list)
{
    if (list == NULL)
    {
        return false;
    }

    Node *prev = List_FindPrevious(value, list);
    if (prev != NULL && prev->next != NULL && prev->next->data == value)
    {
        Node *temp = prev->next;
        prev->next = temp->next;
        free(temp);
        return true;
    }

    return false;
}

bool List_DeleteAt(size_t index, Node *list)
{
    if (list == NULL)
    {
        return false;
    }

    Node *prev = list;
    size_t i = 0;

    while (prev->next != NULL && i < index)
    {
        prev = prev->next;
        i++;
    }

    if (prev->next == NULL || i != index)
    {
        return false;
    }

    Node *temp = prev->next;
    prev->next = temp->next;
    free(temp);
    return true;
}

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

void List_Reverse(Node *list)
{
    if (list == NULL || list->next == NULL || list->next->next == NULL)
    {
        return;
    }

    Node *prev = NULL;
    Node *current = list->next;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->next = prev;
}

bool List_HasCycle(const Node *list)
{
    if (list == NULL || list->next == NULL)
    {
        return false;
    }

    const Node *slow = list->next;
    const Node *fast = list->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return true;
        }
    }

    return false;
}

Node* List_GetMiddle(const Node *list)
{
    if (list == NULL || list->next == NULL)
    {
        return NULL;
    }

    Node *slow = list->next;
    Node *fast = list->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

size_t List_ToArray(const Node *list, int *buffer, size_t max_len)
{
    if (list == NULL || buffer == NULL || max_len == 0)
    {
        return 0;
    }

    size_t count = 0;
    const Node *current = list->next;

    while (current != NULL && count < max_len)
    {
        buffer[count++] = current->data;
        current = current->next;
    }

    return count;
}

void List_Print(const Node *list)
{
    if (list == NULL)
    {
        printf("(null)\n");
        return;
    }

    if (List_IsEmpty(list))
    {
        printf("[Head] -> (empty)\n");
        return;
    }

    printf("[Head]");
    const Node *current = list->next;

    while (current != NULL)
    {
        printf(" -> [%d]", current->data);
        current = current->next;
    }

    printf(" -> NULL\n");
}
