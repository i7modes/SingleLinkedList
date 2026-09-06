/**
 * @file single_linked_list.h
 * @brief Header file for a Singly Linked List with a Sentinel (Dummy) Header Node in C.
 * @author i7modes
 * @license MIT
 */

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a single node in the linked list.
 */
typedef struct Node {
    int data;               /**< Node payload data */
    struct Node *next;      /**< Pointer to the next node */
} Node;

typedef Node* List;
typedef Node* Position;

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocates and initializes a new, empty linked list with a sentinel header.
 * @return Pointer to the sentinel header node, or NULL if allocation fails.
 */
Node* List_Create(void);

/**
 * @brief Clears an existing list or allocates a new empty list.
 * @param list Pointer to an existing list (or NULL to allocate fresh).
 * @return Pointer to the sentinel header of the cleared or newly created list.
 */
Node* List_MakeEmpty(Node *list);

/**
 * @brief Deletes all payload nodes in the list, preserving the sentinel header.
 * @param list Pointer to the list's sentinel header.
 */
void List_Clear(Node *list);

/**
 * @brief Completely deallocates the entire list, including all nodes and the sentinel header.
 * Sets the caller's pointer to NULL to prevent dangling references.
 * @param list_ptr Pointer to the list variable (Node**).
 */
void List_Destroy(Node **list_ptr);

/* -------------------------------------------------------------------------- */
/*                              Query / Observers                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Checks if the list contains any elements (excluding the sentinel header).
 * @param list Pointer to the list's sentinel header.
 * @return true if empty or list is NULL, false otherwise.
 */
bool List_IsEmpty(const Node *list);

/**
 * @brief Checks if a given position is the last node in the list.
 * @param pos Pointer to the node position being tested.
 * @param list Pointer to the list's sentinel header (unused, kept for consistency).
 * @return true if pos is the last node, false otherwise.
 */
bool List_IsLast(const Node *pos, const Node *list);

/**
 * @brief Returns the number of elements in the list (excluding the sentinel header).
 * @param list Pointer to the list's sentinel header.
 * @return Number of nodes in the list.
 */
size_t List_Size(const Node *list);

/**
 * @brief Searches for the first node containing the specified value.
 * @param value The value to search for.
 * @param list Pointer to the list's sentinel header.
 * @return Pointer to the matching node, or NULL if not found.
 */
Node* List_Find(int value, const Node *list);

/**
 * @brief Searches for the node immediately preceding the first node with the specified value.
 * @param value The value to search for.
 * @param list Pointer to the list's sentinel header.
 * @return Pointer to the predecessor node, or the tail node if value is not found.
 */
Node* List_FindPrevious(int value, const Node *list);

/**
 * @brief Retrieves the node at a given 0-based index.
 * @param index 0-based index of the node to retrieve.
 * @param list Pointer to the list's sentinel header.
 * @return Pointer to the node at the specified index, or NULL if out of bounds.
 */
Node* List_GetAt(size_t index, const Node *list);

/* -------------------------------------------------------------------------- */
/*                              Insertion & Deletion                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Inserts a new value immediately following a specified position node.
 * @param value The value to insert.
 * @param list Pointer to the list's sentinel header.
 * @param pos Pointer to the node after which the new element will be placed.
 * @return true on success, false if memory allocation failed or pos is NULL.
 */
bool List_Insert(int value, Node *list, Node *pos);

/**
 * @brief Inserts a new value at the beginning of the list (right after the header).
 * @param value The value to insert.
 * @param list Pointer to the list's sentinel header.
 * @return true on success, false on failure.
 */
bool List_InsertFront(int value, Node *list);

/**
 * @brief Inserts a new value at the end of the list.
 * @param value The value to insert.
 * @param list Pointer to the list's sentinel header.
 * @return true on success, false on failure.
 */
bool List_InsertLast(int value, Node *list);

/**
 * @brief Deletes the first node containing the specified value.
 * @param value The value to remove.
 * @param list Pointer to the list's sentinel header.
 * @return true if the node was found and deleted, false otherwise.
 */
bool List_Delete(int value, Node *list);

/**
 * @brief Deletes the node at a given 0-based index.
 * @param index 0-based index of the node to remove.
 * @param list Pointer to the list's sentinel header.
 * @return true if successfully deleted, false if index is out of bounds.
 */
bool List_DeleteAt(size_t index, Node *list);

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Reverses the linked list in-place (O(n) time, O(1) space).
 * @param list Pointer to the list's sentinel header.
 */
void List_Reverse(Node *list);

/**
 * @brief Detects if the linked list contains a cycle using Floyd's Tortoise and Hare algorithm.
 * @param list Pointer to the list's sentinel header.
 * @return true if a cycle exists, false otherwise.
 */
bool List_HasCycle(const Node *list);

/**
 * @brief Finds the middle node using slow and fast pointers.
 * For even length lists, returns the second middle node.
 * @param list Pointer to the list's sentinel header.
 * @return Pointer to middle node, or NULL if list is empty.
 */
Node* List_GetMiddle(const Node *list);

/**
 * @brief Copies list element data into a provided integer array.
 * @param list Pointer to the list's sentinel header.
 * @param buffer Output array.
 * @param max_len Maximum number of elements that fit in buffer.
 * @return Number of elements copied.
 */
size_t List_ToArray(const Node *list, int *buffer, size_t max_len);

/**
 * @brief Prints the list visually in formatted ASCII:
 *        [Head] -> [10] -> [20] -> [30] -> NULL
 * @param list Pointer to the list's sentinel header.
 */
void List_Print(const Node *list);

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */
#define struct_node Node

static inline Node* MakeEmpty(Node *L) { return List_MakeEmpty(L); }
static inline int IsEmpty(Node *L) { return List_IsEmpty(L) ? 1 : 0; }
static inline int IsLast(Node *P, Node *L) { return List_IsLast(P, L) ? 1 : 0; }
static inline Node* Find(int X, Node *L) { return List_Find(X, L); }
static inline Node* FindPrevious(int X, Node *L) { return List_FindPrevious(X, L); }
static inline void Delete(int X, Node *L) { (void)List_Delete(X, L); }
static inline void Insert(int X, Node *L, Node *P) { (void)List_Insert(X, L, P); }
static inline void InsertLast(int X, Node *L) { (void)List_InsertLast(X, L); }
static inline void PrintList(Node *L) { List_Print(L); }
static inline void DeleteList(Node *L) { List_Clear(L); }
static inline int size(Node *L) { return (int)List_Size(L); }

#ifdef __cplusplus
}
#endif

#endif /* SINGLE_LINKED_LIST_H */
