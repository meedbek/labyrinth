/**
 * @file maze_generator.c
 * @brief Maze generation implementation using Randomized Depth-First Search algorithm
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This file contains the implementation of maze generation using the Randomized DFS
 * algorithm. The maze is represented as a matrix of cells, where each cell has
 * information about its walls (up, down, left, right).
 */

#include "maze_generator.h"

/**
 * @brief Generates a maze using the Randomized Depth-First Search algorithm
 * 
 * This function creates a maze by starting from the top-left corner and randomly
 * choosing paths while maintaining a stack of visited cells. When it hits a dead end,
 * it backtracks using the stack until it finds a cell with unvisited neighbors.
 * 
 * @return maze_matrix A dynamically allocated matrix representing the generated maze
 * 
 * @note The returned maze must be freed by the caller
 * @note Uses global variables MAZE_ROWS and MAZE_COLS for dimensions
 */
maze_matrix generate_maze()
{
    stack* maze_stack = NULL;
    maze_matrix maze = (cell*)malloc(MAZE_ROWS * MAZE_COLS * sizeof(cell));
    int* visited = (int*)malloc(MAZE_ROWS * MAZE_COLS * sizeof(int));
    int direction;
    int i, j, count = 1;

    initialize_maze(&maze);

    // Initialize the visited cells matrix
    for (i = 0; i < MAZE_ROWS * MAZE_COLS; i++)
    {
        *(visited + i) = 0;
    }

    // Below is the "Randomized DFS" algorithm 
    i = 0;
    j = 0;
    while (count < MAZE_ROWS * MAZE_COLS) // while we haven't visited all cells
    {
        direction = get_random_direction(maze, i, j, visited); // randomly choose the cell we'll visit (up, right, etc.) 
        *(visited + i * MAZE_COLS + j) = 1;
        // we assign 1 to the side of the cell where we passed to indicate there's no wall on that side
        switch (direction)
        {
            case up: 
                (maze + i * MAZE_COLS + j)->up = 1;
                (maze + (i - 1) * MAZE_COLS + j)->down = 1;
                push(&maze_stack, i, j);
                count++;
                i--;
                break;
            case down:
                (maze + i * MAZE_COLS + j)->down = 1;
                (maze + (i + 1) * MAZE_COLS + j)->up = 1;
                push(&maze_stack, i, j);
                count++;
                i++;
                break;
            case right:
                (maze + i * MAZE_COLS + j)->right = 1;
                (maze + i * MAZE_COLS + (j + 1))->left = 1;
                push(&maze_stack, i, j);
                count++;
                j++;
                break;
            case left:
                (maze + i * MAZE_COLS + j)->left = 1;
                (maze + i * MAZE_COLS + (j - 1))->right = 1;
                push(&maze_stack, i, j);
                count++;
                j--;
                break;
            case -1:
                pop(&maze_stack);
                i = *top(maze_stack);
                j = *(top(maze_stack) + 1);
                break;
        }
    }
    free_stack(maze_stack);
    free(visited);
    return maze;
}


/**
 * @brief Initializes all cells in the maze with default wall configurations
 * 
 * This function sets up the initial state of the maze by:
 * - Setting all internal walls to 0 (no passage)
 * - Setting border walls to -1 (permanent walls)
 * - Ensuring the maze is properly bounded
 * 
 * @param m Pointer to the maze matrix to initialize
 * 
 * @note The maze matrix must be pre-allocated before calling this function
 */
void initialize_maze(maze_matrix *m)
{
    int i = 0;
    for (i = 0; i < MAZE_ROWS * MAZE_COLS; i++) {
        (*m + i)->up = 0;
        (*m + i)->down = 0;
        (*m + i)->left = 0;
        (*m + i)->right = 0;
    }
    for (i = 0; i < MAZE_COLS; i++) {
        (*m + i)->up = -1;
        (*m + i + MAZE_ROWS * MAZE_COLS - MAZE_COLS)->down = -1;
    }
    for (i = 0; i < MAZE_ROWS; i++) {
        (*m + i * MAZE_COLS)->left = -1;
        (*m + MAZE_COLS - 1 + i * MAZE_COLS)->right = -1;
    }
}

/**
 * @brief Randomly selects a valid direction for maze generation
 * 
 * This function examines the current cell and determines which neighboring cells
 * can be visited (haven't been visited yet and are within maze bounds). It then
 * randomly selects one of these valid directions.
 * 
 * @param m The maze matrix
 * @param row Current row position
 * @param col Current column position
 * @param visited Array tracking which cells have been visited
 * 
 * @return int Direction constant (up, down, left, right) or -1 if no valid moves
 * 
 * @note Returns -1 when the current cell has no unvisited neighbors (dead end)
 */
int get_random_direction(maze_matrix m, int row, int col, int* visited)
{
    cell current_cell = *(m + MAZE_COLS * row + col);
    int directions[4];
    int count = 0;
    if (current_cell.up == 0 && *(visited + (row - 1) * MAZE_COLS + col) == 0) {
        directions[count] = up;
        count++;
    }
    if (current_cell.right == 0 && *(visited + row * MAZE_COLS + col + 1) == 0) {
        directions[count] = right;
        count++;
    }
    if (current_cell.down == 0 && *(visited + (row + 1) * MAZE_COLS + col) == 0) {
        directions[count] = down;
        count++;
    }
    if (current_cell.left == 0 && *(visited + row * MAZE_COLS + col - 1) == 0) {
        directions[count] = left;
        count++;
    }
    if (count == 0) return -1;
    else {
        return directions[rand() % count];
    }
}



