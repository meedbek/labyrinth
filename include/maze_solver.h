/**
 * @file maze_solver.h
 * @brief Header file for maze solving functionality
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This header defines functions for solving mazes using depth-first
 * search with backtracking algorithms.
 */

#ifndef MAZE_SOLVER
#define MAZE_SOLVER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze_generator.h"
#include "stack.h"

/* Function prototypes */
int get_random_solution_direction(maze_matrix m, int row, int col, int* visited);
stack* solve_maze(maze_matrix m, int entry[2], int exit[2]);

#endif