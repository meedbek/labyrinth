/**
 * @file main.c
 * @brief Main entry point for the Labyrinth maze game
 * @author HamzaBenyazid
 * @date August 23, 2025
 * 
 * This file contains the main function that initializes the random number
 * generator and starts the SDL-based graphical interface for the maze game.
 */

#include "maze_generator.h"
#include "stack.h"
#include "display.h"
#include "maze_solver.h"
#include "sdl_display.h"

/**
 * @brief Main entry point of the application
 * 
 * Initializes the random number generator with current time as seed
 * and launches the SDL-based graphical maze game interface.
 * 
 * @return int Exit status (0 for success)
 */
int main()
{
    srand(time(0)); 
    SDL_main();
    return 0;
}