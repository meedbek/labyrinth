/**
 * @file display.c
 * @brief Console-based maze display functionality
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This file implements console display functions for rendering mazes as
 * ASCII art using '#' characters for walls and spaces for passages.
 */

#include "display.h"

/**
 * @brief Converts a maze matrix to a character matrix for display
 * 
 * This function transforms the internal maze representation into a visual
 * character matrix that can be displayed in the console. Walls are represented
 * by '#' characters and open passages by spaces.
 * 
 * @param m The maze matrix to convert
 * 
 * @return char* A dynamically allocated character matrix ready for display
 * 
 * @note The returned matrix must be freed by the caller
 * @note The display matrix is larger than the maze matrix to accommodate wall rendering
 */
char* maze_to_display_matrix(maze_matrix m)
{
    int row_size = MAZE_ROWS * 2 + (MAZE_ROWS + 1);
    int column_size = MAZE_COLS * 2 + (MAZE_COLS + 1);

    char* display_matrix = (char*)malloc(row_size * column_size);
    int i, j = 0, k, n = 0;


    for (i = 0; i < row_size * column_size; i++) {
        *(display_matrix + i) = ' ';
    }

    for (i = 0; i < column_size; i++) {
        *(display_matrix + i) = '#';                 // Initialize first row
        *(display_matrix + column_size * (row_size - 1) + i) = '#';   // Initialize last row
    }

    for (i = 0; i < row_size; i++) {
        *(display_matrix + column_size * i) = '#';            // Initialize first column
        *(display_matrix + column_size * i + column_size - 1) = '#';     // Initialize last column
    }

    for (k = 0, n = 3; k < MAZE_ROWS && n < row_size; k++, n += 3) {
        for (i = 0, j = 3; i < MAZE_COLS && j < column_size; i++, j += 3) {
            if ((m + i + k * MAZE_COLS)->right == 0) {
                *(display_matrix + (n - 3) * column_size + j) = '#';
                *(display_matrix + (n - 2) * column_size + j) = '#';
                *(display_matrix + (n - 1) * column_size + j) = '#';
                *(display_matrix + n * column_size + j) = '#';

            }
            if ((m + i + k * MAZE_COLS)->down == 0) {
                *(display_matrix + n * column_size + j - 3) = '#';
                *(display_matrix + n * column_size + j - 2) = '#';
                *(display_matrix + n * column_size + j - 1) = '#';
                *(display_matrix + n * column_size + j) = '#';

            }
        }
    }
    return display_matrix;
}

/**
 * @brief Displays the maze in the console
 * 
 * Takes a character matrix (typically from maze_to_display_matrix) and
 * prints it to the console with proper formatting.
 * 
 * @param display_matrix The character matrix to display
 * 
 * @note The display matrix should be properly formatted with walls and passages
 */
void display_maze(char* display_matrix)
{
    int row_size = MAZE_ROWS * 2 + (MAZE_ROWS + 1);
    int column_size = MAZE_COLS * 2 + (MAZE_COLS + 1);
    int i, j;
    for (i = 0; i < row_size; i++) {
        for (j = 0; j < column_size; j++) {
            printf("%c", *(display_matrix + i * column_size + j));
        }
        printf("\n");
    }
}