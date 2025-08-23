/**
 * @file maze_generator.h
 * @brief Header file for maze generation functionality
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This header defines the data structures and function prototypes for
 * maze generation using the Randomized Depth-First Search algorithm.
 */

#ifndef MAZE
#define MAZE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

/** @brief Global variable for maze height (number of rows) */
extern int MAZE_ROWS;

/** @brief Global variable for maze width (number of columns) */
extern int MAZE_COLS;

/**
 * @brief Enumeration for movement directions in the maze
 * 
 * Used to represent the four cardinal directions when navigating
 * or generating paths in the maze.
 */
enum direction {up, right, down, left};

/**
 * @brief Structure representing a single cell in the maze
 * 
 * Each cell contains information about its four walls:
 * - 0: Wall is present (no passage)
 * - 1: Wall is removed (passage exists)  
 * - -1: Boundary wall (permanent, cannot be removed)
 */
typedef struct _cell
{
    int right;  /**< Right wall status */
    int left;   /**< Left wall status */
    int up;     /**< Top wall status */
    int down;   /**< Bottom wall status */
    
} cell;

/** @brief Type definition for a maze matrix (array of cells) */
typedef cell* maze_matrix;

/* Function prototypes */
void initialize_maze(maze_matrix *m);
int get_random_direction(maze_matrix m, int row, int col, int* visited);
maze_matrix generate_maze();

#endif