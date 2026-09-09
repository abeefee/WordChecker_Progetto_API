# 🔍 WordChecker - Lexical Filtering - API Project 2021/22

*You can read this also in [Italiano](readme.it.md)*

> **Academic Note:** This project was developed as the Final Project for the *Algoritmi e Principi dell'Informatica* course at Politecnico di Milano (Academic Year 2021/22), achieving a final grade of **30/30 cum laude**. The code was evaluated by an automated grader strictly enforcing execution time and memory usage limits.

### Project Description
WordChecker is a C (C11) software for checking, validating, and filtering dictionaries of words, utilizing logic similar to the popular game *Wordle*. 

The system receives a base dictionary and compares attempt words against a reference target word. Based on the outcome of the comparison, the engine **dynamically learns constraints** (presence, absence, exact position, or minimum/exact quantity of specific characters) and filters the dictionary, printing in lexicographical order only the words still compatible with the learned constraints.

### Technical Features & Challenges
As an algorithm-focused project, the implementation required careful data structure design to minimize search time and memory footprint:

* **Hybrid Data Structure:** Implemented a Binary Search Tree (BST) integrated with a Linked List. This hybrid approach guarantees optimal time complexity for word lookups while allowing sequential, ordered iterations for filtering and printing.
* **Smart Filtering (Logical Deletion):** Instead of heavily modifying the tree structure and freeing memory during filtering, nodes utilize an `inPartita` (in-game) boolean flag. Words are logically removed by toggling this flag, bypassing the need for expensive tree rebalancing and memory reallocation between games.
* **Custom String Operations:** Developed a custom `faststrcmp` function to squeeze out maximum performance over the standard string library during the millions of tree traversals required.
* **Constraint Tracking:** Implemented a secondary Linked List to dynamically track learned constraints (`node_v`), allowing newly inserted words at runtime to be immediately evaluated against the current game state.

### Technologies & Profiling
* **Language:** C (Standard C11, VLA supported)
* **Compiler (recommended):** GCC
* **Testing & Profiling (Valgrind Suite):** 
  * **Memcheck:** Used to guarantee strict dynamic memory management with zero memory leaks.
  * **Callgrind:** Used to profile code execution, identify bottlenecks, and optimize the custom string comparison functions.
  * **Massif:** Used to monitor and minimize heap memory footprint, ensuring the data structures stayed within the strict automated grader limits.

### Compilation & Execution
No external dependencies are required. To compile:

```bash
gcc -Wall -Werror -O2 -g3 src/wordchecker.c -o wordchecker
```

To run tests:

```bash
./wordchecker < tests/test1.txt > my_output.txt