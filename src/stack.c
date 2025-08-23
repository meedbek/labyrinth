/**
 * @file stack.c
 * @brief Stack data structure implementation for coordinate pairs
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This file implements a stack data structure specifically designed to store
 * coordinate pairs (row, column) used in maze generation and solving algorithms.
 * The stack uses a linked list implementation for dynamic memory management.
 */

#include "stack.h"

/**
 * @brief Pushes a coordinate pair onto the stack
 * 
 * Creates a new stack node with the given coordinates and adds it to the top
 * of the stack. Uses dynamic memory allocation for each new node.
 * 
 * @param s Pointer to the stack pointer (double pointer for modification)
 * @param i Row coordinate to push
 * @param j Column coordinate to push
 * 
 * @note The stack grows dynamically and the caller doesn't need to worry about capacity
 */
void push(stack **s, int i, int j)
{
    stack *new_node = Malloc(stack);
    new_node->column = j;
    new_node->row = i;
    new_node->next = *(s);
    *(s) = new_node;
}

/**
 * @brief Prints all elements in the stack for debugging purposes
 * 
 * Traverses the entire stack from top to bottom and prints each coordinate pair.
 * Useful for debugging maze generation and solving algorithms.
 * 
 * @param s Pointer to the stack to print
 * 
 * @note This function is primarily for debugging and doesn't modify the stack
 * @note Output format: "row column" for each coordinate pair
 */
void print_stack(stack *s)
{
    printf("\n\n");
    while (s != NULL) {
        printf("%d %d\n", s->row, s->column);
        s = s->next;
    }
}

/**
 * @brief Removes the top element from the stack
 * 
 * Pops the topmost element from the stack and frees its memory.
 * Does nothing if the stack is empty.
 * 
 * @param s Pointer to the stack pointer (double pointer for modification)
 * 
 * @note The function safely handles empty stacks without errors
 * @note Memory is properly freed to prevent memory leaks
 */
void pop(stack **s)
{
    stack* previous;
    if (!is_empty(*s)) 
    {
        previous = *s;
        *s = (*s)->next;
        free(previous);
    }
}

/**
 * @brief Returns the coordinates of the top element without removing it
 * 
 * Provides access to the top element's coordinates without modifying the stack.
 * Returns a dynamically allocated array containing the coordinates.
 * 
 * @param s Pointer to the stack
 * 
 * @return int* Array of 2 integers [row, column] or [-1, -1] if stack is empty
 * 
 * @note The caller is responsible for freeing the returned array
 * @note Returns [-1, -1] for empty stacks as an error indicator
 */
int* top(stack *s) 
{
    int* coordinates = (int*)malloc(sizeof(int) * 2);
    if (is_empty(s)) {
        *coordinates = -1;
        *(coordinates + 1) = -1;
        return coordinates;
    }
    *coordinates = s->row;
    *(coordinates + 1) = s->column;
    return coordinates;
}

/**
 * @brief Checks if the stack is empty
 * 
 * @param s Pointer to the stack to check
 * 
 * @return int 1 (true) if stack is empty, 0 (false) otherwise
 */
int is_empty(stack *s)
{
    return (s == NULL);
}

/**
 * @brief Counts the number of elements in the stack
 * 
 * Traverses the entire stack to count elements. Useful for determining
 * path length in maze solving applications.
 * 
 * @param s Pointer to the stack to count
 * 
 * @return int Number of elements in the stack
 * 
 * @note This operation is O(n) where n is the number of elements
 */
int length(stack *s)
{
    int count = 0;
    
    while (s != NULL) {
        s = s->next;
        count++;
    }
    return count;
}

/**
 * @brief Frees all memory allocated for the stack
 * 
 * Traverses the entire stack and frees each node's memory to prevent
 * memory leaks. Should be called when the stack is no longer needed.
 * 
 * @param s Pointer to the stack to free
 * 
 * @note After calling this function, the stack pointer becomes invalid
 * @note This function handles NULL pointers safely
 */
void free_stack(stack *s)
{
    stack* previous;

    while (s != NULL)
    {
        previous = s;
        s = s->next;
        free(previous);
    }
}
