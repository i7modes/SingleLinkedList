# Singly Linked List in C (Sentinel Header Architecture)

[![CI](https://github.com/i7modes/SingleLinkedList/actions/workflows/ci.yml/badge.svg)](https://github.com/i7modes/SingleLinkedList/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C Standard](https://img.shields.io/badge/C-C99-blue.svg)
![Memory Status](https://img.shields.io/badge/Valgrind-0%20Leaks-brightgreen.svg)

A clean, robust, and production-ready implementation of a **Singly Linked List** in C99 using a **Sentinel (Dummy) Header Node** architecture. Includes classic interview algorithms (in-place reversal, Floyd's cycle detection, middle node finder), an automated unit testing suite, and zero memory leaks.

---

## Architecture: The Sentinel Head Pattern

This implementation employs a **dummy/sentinel head node**. The head node itself never stores application data; rather, it serves as a persistent anchor for the first element.

```text
+-------------------+      +-------------------+      +-------------------+
| Sentinel (Dummy)  | ---> |   Payload Node    | ---> |   Payload Node    | ---> NULL
| [data: 0 | next]  |      | [data: 10 | next] |      | [data: 20 | next] |
+-------------------+      +-------------------+      +-------------------+
```

### Why use a Sentinel Node?
1. **Eliminates Edge-Case Branching**: Inserting or deleting the very first element does not require updating the caller's head pointer.
2. **Simplified Invariants**: Operations never need to handle a `NULL` head during mutations.
3. **Clean Code**: Greatly reduces pointer-to-pointer (`Node**`) complexity across traversal algorithms.

---

## Features

- **Core Operations**: `InsertFront`, `InsertLast`, `Insert`, `Delete`, `DeleteAt`, `Find`, `FindPrevious`, `GetAt`.
- **Advanced Algorithms**:
  - **In-Place Reversal**: Iterative $O(n)$ time, $O(1)$ auxiliary space reversal.
  - **Floyd's Cycle Detection**: Fast & slow pointer algorithm (Tortoise and Hare).
  - **Middle Element Lookup**: One-pass middle node detection.
  - **Buffer Serialization**: `List_ToArray` for easy data export.
- **Memory Safety**: Every allocation is checked; `List_Destroy` frees all nodes + sentinel header and nullifies the caller's pointer.
- **Backward Compatibility**: Includes inline aliases for legacy academic signatures (`MakeEmpty`, `InsertLast`, `DeleteList`, etc.).
- **Automated Tests & CI**: 39+ assertions tested across Ubuntu and Windows with Valgrind & AddressSanitizer.

---

## Complexity Analysis

| Operation | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
| :--- | :---: | :---: | :---: |
| `List_InsertFront` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `List_Insert` (after known node) | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `List_InsertLast` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_Delete` (by value) | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_DeleteAt` (by index) | $\mathcal{O}(k)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_Find` / `List_FindPrevious` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_Reverse` (in-place) | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_HasCycle` (Floyd's) | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_GetMiddle` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `List_Destroy` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |

---

## Project Structure

```text
SingleLinkedList/
├── include/
│   └── single_linked_list.h     # Public API, types, and documentation
├── src/
│   └── single_linked_list.c     # Implementation
├── examples/
│   └── demo.c                   # Visual terminal demonstration
├── tests/
│   └── test_list.c              # Automated unit test suite (39 assertions)
├── .github/
│   └── workflows/
│       └── ci.yml               # GitHub Actions CI matrix (GCC, Clang ASan, Valgrind)
├── Makefile                     # Cross-platform build script
├── LICENSE                      # MIT License
├── .gitignore                   # Ignore binaries and temporary files
└── README.md                    # Project documentation
```

---

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/i7modes/SingleLinkedList.git
cd SingleLinkedList
```

### 2. Build and Run Demo
Using GNU Make (Linux, macOS, or Windows with MinGW):
```bash
make demo
make run-demo
```

Or compile directly with GCC:
```bash
gcc -Wall -Wextra -std=c99 -Iinclude src/single_linked_list.c examples/demo.c -o demo
./demo
```

### 3. Run Automated Tests
```bash
make check
```

Output:
```text
========================================
  Single Linked List Automated Tests
========================================

--- Test: Initialization & Empty Check ---
  [PASS] List_Create returns non-NULL sentinel header
  [PASS] New list is empty
  [PASS] New list size is 0
  [PASS] List_Destroy nullifies list pointer
...
========================================
  Results: 39/39 assertions passed
========================================
```

### 4. Memory Leak Check (Linux / WSL)
```bash
make test
valgrind --leak-check=full --show-leak-kinds=all ./bin/test_runner
```

---

## Code Example

```c
#include "single_linked_list.h"
#include <stdio.h>

int main(void) {
    // 1. Create list with sentinel header
    Node *list = List_Create();

    // 2. Insert values
    List_InsertLast(10, list);
    List_InsertLast(20, list);
    List_InsertFront(5, list); // [Head] -> [5] -> [10] -> [20] -> NULL

    // 3. Print formatted list
    List_Print(list);

    // 4. In-place reversal
    List_Reverse(list);        // [Head] -> [20] -> [10] -> [5] -> NULL
    List_Print(list);

    // 5. Clean up memory
    List_Destroy(&list);       // list is now NULL, 0 memory leaks!
    return 0;
}
```

---

## License

Distributed under the [MIT License](file:///c:/Users/i7mod/OneDrive/GitHub/SingleLinkedList/LICENSE). Created by [i7modes](https://github.com/i7modes).
