#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <maze_generator.h>
#include <display.h>
#include "maze_solver.h"

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define ESCAPE -1

int SDL_main();
SDL_Surface* create_maze_surface(maze_matrix maze);
void draw_solution(maze_matrix m, SDL_Surface* maze, int entry[2], int exit[2]);
int handle_interaction(SDL_Surface *screen, SDL_Surface *original_maze, maze_matrix labyrinth, int entry[2], int exit[2]);
void play_game(SDL_Surface* screen);
int show_main_menu(SDL_Surface* screen);
int show_difficulty_menu(SDL_Surface *screen);
void show_controls(SDL_Surface *screen);

#endif