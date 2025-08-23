/**
 * @file maze_solver.c
 * @brief Maze solving implementation using depth-first search with backtracking
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This file implements maze solving functionality that finds a path from a given
 * entry point to an exit point using a randomized depth-first search approach
 * with backtracking when dead ends are encountered.
 */

#include "maze_solver.h"

/**
 * @brief Randomly selects a valid direction for maze solving
 * 
 * Similar to get_random_direction in maze generation, but this function only
 * considers paths where walls have been removed (value = 1) instead of checking
 * for unvisited cells during generation.
 * 
 * @param m The maze matrix to solve
 * @param row Current row position
 * @param col Current column position  
 * @param visited Array tracking visited cells during solving
 * 
 * @return int Direction constant (up, down, left, right) or -1 if no valid moves
 * 
 * @note This function ensures the solver only moves through open passages
 */
int get_random_solution_direction(maze_matrix m, int row, int col, int* visited)
{
    cell current_cell = *(m + MAZE_COLS * row + col);
    int directions[4];
    int count = 0;

    if (current_cell.up == 1 && *(visited + (row - 1) * MAZE_COLS + col) == 0) {
        directions[count] = up;
        count++;
    }
    if (current_cell.right == 1 && *(visited + row * MAZE_COLS + col + 1) == 0) {
        directions[count] = right;
        count++;
    }
    if (current_cell.down == 1 && *(visited + (row + 1) * MAZE_COLS + col) == 0) {
        directions[count] = down;
        count++;
    }
    if (current_cell.left == 1 && *(visited + row * MAZE_COLS + col - 1) == 0) {
        directions[count] = left;
        count++;
    }
    if (count == 0) return -1;
    else {
        return directions[rand() % count];
    }
}

/**
 * @brief Solves a maze by finding a path from entry to exit point
 * 
 * This function implements a randomized depth-first search with backtracking
 * to find a path through the maze. It uses a stack to keep track of the path
 * and backtracks when it reaches dead ends.
 * 
 * @param maze The maze matrix to solve
 * @param entry Array containing entry coordinates [row, col]
 * @param exit Array containing exit coordinates [row, col]
 * 
 * @return stack* A stack containing the solution path from entry to exit
 * 
 * @note The returned stack represents the path with the entry point at the bottom
 *       and exit point at the top
 * @note The caller is responsible for freeing the returned stack
 * @note Returns NULL if no solution exists
 */
stack* solve_maze(maze_matrix maze, int entry[2], int exit[2])
{
    stack* solution = NULL;
    int* visited = (int*)malloc(MAZE_ROWS * MAZE_COLS * sizeof(int));
    int direction;
    int i, j;

    // Initialize the visited cells matrix
    for (i = 0; i < MAZE_ROWS * MAZE_COLS; i++)
    {
        *(visited + i) = 0;
    }
    
    i = entry[0];
    j = entry[1];
    push(&solution, i, j); // add the starting cell to the stack
    while (i != exit[0] || j != exit[1]) 
    {
        direction = get_random_solution_direction(maze, i, j, visited); 
        *(visited + i * MAZE_COLS + j) = 1;
        switch (direction)
        {
            case up: 
                i--;
                push(&solution, i, j);
                break;
            case down:
                i++;
                push(&solution, i, j);
                break;
            case right:
                j++;
                push(&solution, i, j);
                break;
            case left:
                j--;
                push(&solution, i, j);
                break;
            case -1:
                pop(&solution);
                i = *top(solution);
                j = *(top(solution) + 1);
                break;
        }
    }
    free(visited);
    return solution;
}

