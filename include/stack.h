/**
 * @file stack.h
 * @brief Header file for stack data structure implementation
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This header defines a stack data structure specifically designed for
 * storing coordinate pairs used in maze generation and solving algorithms.
 */

#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>

/** @brief Macro for type-safe dynamic memory allocation */
#define Malloc(type) (type*)malloc(sizeof(type))

/**
 * @brief Stack node structure for storing coordinate pairs
 * 
 * Each node contains a coordinate pair (row, column) and a pointer
 * to the next node in the stack. Implements a linked list structure.
 */
typedef struct _stack
{
    int column; /**< Column coordinate */
    int row;    /**< Row coordinate */
    struct _stack *next; /**< Pointer to next node in stack */
    
} stack;

/* Function prototypes */
void push(stack **s, int i, int j);
void print_stack(stack *s);
void pop(stack **s);
int* top(stack *s);
int is_empty(stack *s);
int length(stack *s);
void free_stack(stack *s);

#endif