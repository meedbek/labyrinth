/**
 * @file display.h
 * @brief Header file for console-based maze display functionality
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This header defines functions for converting maze data structures
 * into displayable ASCII art for console output.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "maze_generator.h"

/* Function prototypes */
char* maze_to_display_matrix(maze_matrix m);
void display_maze(char* display_matrix);
void fill_cell(cell* m, int i, int j, int up, int right, int down, int left);

#endif