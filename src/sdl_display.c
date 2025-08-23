#include"sdl_display.h"

// Define global variables MAZE_ROWS and MAZE_COLS
int MAZE_ROWS;
int MAZE_COLS;

int cell_sizes[3]={32,16,8}; // cell size of a maze cell
char* floor_textures[3]={"images/sol32.bmp","images/sol16.bmp","images/sol08.bmp"};
char* ball_textures[3]={"images/yellowball32.png","images/yellowball16.png","images/yellowball08.png"};
char* trophy_textures[3]={"images/Trophy32.png","images/Trophy16.png","images/Trophy08.png"};
int difficulty_choice; // this variable indicates the chosen difficulty
int continue_game = 1; // this variable indicates whether the program stops or continues

int SDL_main()
{
    SDL_Surface *screen;
    SDL_Rect position = {0,0};
    SDL_Surface *background = IMG_Load("images/background.png");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("images/icon.jpg"), NULL);
    screen = SDL_SetVideoMode(1200, 701, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Labyrinthe", NULL);
    SDL_BlitSurface(background,NULL,screen,&position);
    
    while (continue_game){
        switch(show_main_menu(screen)){ // menu 1 is displayed and the function returns an int according to the button the user clicked
            case 1: switch(difficulty_choice=show_difficulty_menu(screen)) // menu 2 is displayed which contains the difficulties
                {
                    case EASY :
                        MAZE_ROWS=5;
                        MAZE_COLS=10;
                        play_game(screen);
                        break;
                    case MEDIUM :
                        MAZE_ROWS=14;
                        MAZE_COLS=24;
                        play_game(screen);
                        break;
                    case HARD :
                        MAZE_ROWS=25;
                        MAZE_COLS=40;
                        play_game(screen);
                        break;
                    break;
                }
                break;
        }
    }
    SDL_FreeSurface(background);
    SDL_Quit();

    return EXIT_SUCCESS;
}

// This function returns the surface containing the drawn maze
SDL_Surface* create_maze_surface(maze_matrix maze)
{
    int row_size=MAZE_ROWS*2+(MAZE_ROWS+1); 
    int column_size=MAZE_COLS*2+(MAZE_COLS+1);

    char* display_matrix=maze_to_display_matrix(maze);

    SDL_Surface *maze_surface=NULL,*wall=NULL;

    SDL_Rect position;

    int cell_size=cell_sizes[difficulty_choice]; // this variable indicates the number of pixels we'll work with (one cell contains (2*cell_size * 2*cell_size) pixels)

    maze_surface = SDL_CreateRGBSurface(SDL_HWSURFACE,column_size*cell_size,row_size*cell_size, 32, 0, 0, 0, 0);

    SDL_FillRect(maze_surface, NULL, SDL_MapRGB(maze_surface->format, 255, 255, 255));

    wall=IMG_Load(floor_textures[difficulty_choice]);

    for(int i=0;i<row_size;i++){
        for(int j=0;j<column_size;j++){
            if (*(display_matrix+i*column_size+j)=='#'){
                position.x=cell_size*j;
                position.y=cell_size*i;
                SDL_BlitSurface(wall,NULL,maze_surface,&position);
            }
        }
    }
    SDL_FreeSurface(wall);
    free(display_matrix);
    
    return maze_surface;
}

// This function colors the solution path on the maze surface 
void draw_solution(maze_matrix m, SDL_Surface* maze,int entry[2], int exit[2])
{
    SDL_Surface* cell_rect = NULL; // this variable colors each cell that belongs to the solution path
    SDL_Surface* horizontal_rect = NULL; // this variable and the next one are useful for coloring the space between two cells which is normally a wall or empty space 
    SDL_Surface* vertical_rect = NULL;
    SDL_Rect position, rectangle_position;
    int cell_size=cell_sizes[difficulty_choice];
    stack* path = solve_maze(m, entry, exit);
    
    
    cell_rect = SDL_CreateRGBSurface(SDL_HWSURFACE, cell_size*2, cell_size*2, 32, 0, 0, 0, 0);
    horizontal_rect = SDL_CreateRGBSurface(SDL_HWSURFACE, cell_size*2, cell_size, 32, 0, 0, 0, 0);
    vertical_rect = SDL_CreateRGBSurface(SDL_HWSURFACE, cell_size, cell_size*2, 32, 0, 0, 0, 0);

    SDL_FillRect(cell_rect, NULL, SDL_MapRGB(cell_rect->format, 0, 255, 0)); 
    SDL_FillRect(vertical_rect, NULL, SDL_MapRGB(vertical_rect->format, 0, 255, 0)); 
    SDL_FillRect(horizontal_rect, NULL, SDL_MapRGB(horizontal_rect->format, 0, 255, 0)); 


    while( path != NULL ) // while we haven't colored all cells from entry to exit
    {
        position.x = (path->column)*2*cell_size + (path->column+1)*cell_size;
        position.y = (path->row)*2*cell_size + (path->row+1)*cell_size;
        if(path->next != NULL)
        {
            if(path->next->row == path->row)
            {    
                rectangle_position.y = position.y ;
                if(path->next->column > path->column)
                    rectangle_position.x = position.x + cell_size*2 ;
                else 
                    rectangle_position.x = position.x - cell_size ;
                SDL_BlitSurface(vertical_rect,NULL,maze,&rectangle_position); 
            }
            else 
            {    
                rectangle_position.x = position.x ;
                if(path->next->row > path->row)
                    rectangle_position.y = position.y + cell_size*2 ;
                else 
                    rectangle_position.y = position.y - cell_size ;
                SDL_BlitSurface(horizontal_rect,NULL,maze,&rectangle_position);
            }
        }
        SDL_BlitSurface(cell_rect,NULL,maze,&position);
        path = path->next ;

    }
    
    SDL_FreeSurface(cell_rect);
    SDL_FreeSurface(horizontal_rect);
    SDL_FreeSurface(vertical_rect);
    free_stack(path);

}

// This function displays the maze and gives us the ability to move the object until we reach the exit 
int handle_interaction(SDL_Surface *screen,SDL_Surface *original_maze,maze_matrix labyrinth ,int entry[2],int exit[2])
{

    int column_size=MAZE_COLS*2+(MAZE_COLS+1);
    
    // The surfaces used
    SDL_Surface *maze = original_maze;
    SDL_Surface *maze_copy= NULL;
    SDL_Surface *ball=IMG_Load(ball_textures[difficulty_choice]);
    SDL_Surface *trophy=IMG_Load(trophy_textures[difficulty_choice]);
    int cell_size=cell_sizes[difficulty_choice];

    // Variables used
    int is_solved = 0;
    int row=(3*entry[0])+1,column=(3*entry[1])+1;
    int current_position[2]={entry[0],entry[1]};
    char *display_matrix=maze_to_display_matrix(labyrinth);

    // Positions used
    SDL_Rect ball_position={ column*cell_size , row*cell_size };
    SDL_Rect maze_position={ (screen->w-maze->w)/2 , (screen->h-maze->h)/2  }; // center of the screen
    SDL_Rect trophy_position={ (3*exit[1]+1)*cell_size , (3*exit[0]+1)*cell_size };

    // Event 
    SDL_Event event;
    
    // Display the maze with the ball and trophy at the exit
    SDL_EnableKeyRepeat(30, 30);
    maze_copy=SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
    SDL_BlitSurface(ball,NULL,maze_copy,&ball_position);
    SDL_BlitSurface(trophy,NULL,maze_copy,&trophy_position);
    SDL_BlitSurface(maze_copy,NULL,screen,&maze_position);
    SDL_Flip(screen);
    
    
    while (continue_game)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continue_game = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        SDL_FreeSurface(maze_copy);
                        SDL_FreeSurface(ball);
                        SDL_FreeSurface(trophy);
                        free(display_matrix);
                        return 0;
                    case SDLK_UP:
                        if (*(display_matrix+(row-1)*column_size+column)!='#'&&*(display_matrix+(row-1)*column_size+column+1)!='#'){
                            ball_position.y-=cell_size;
                            row--;
                        }break;
                    case SDLK_DOWN:
                        if (*(display_matrix+(row+2)*column_size+column)!='#'&&*(display_matrix+(row+2)*column_size+column+1)!='#'){
                            ball_position.y+=cell_size;
                            row++;
                        }break;
                    case SDLK_RIGHT:
                        if (*(display_matrix+row*column_size+column+2)!='#'&& *(display_matrix+(row+1)*column_size+column+2)!='#'){
                            ball_position.x+=cell_size;
                            column++;
                        }break;
                    case SDLK_LEFT:
                        if (*(display_matrix+row*column_size+column-1)!='#'&&*(display_matrix+(row+1)*column_size+column-1)!='#'){
                            ball_position.x-=cell_size;
                            column--;
                        }break;
                    case SDLK_SPACE: // if the user clicks space, the displayed maze should be solved; if clicked once, return to original maze
                        SDL_EnableKeyRepeat(0, 30);
                        if(is_solved == 0)
                            is_solved = 1;
                        else
                            is_solved = 0;
                        SDL_EnableKeyRepeat(30, 30);
                }
                
                current_position[0]= ball_position.y/cell_size/3 ;
                current_position[1]= ball_position.x/cell_size/3 ;
                
                SDL_FreeSurface(maze_copy);
                maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);

                // if is_solved = 1 then we update the maze with the solution according to the current position of the ball
                if(is_solved)
                    draw_solution(labyrinth,maze_copy,current_position,exit);
                
                SDL_BlitSurface(ball,NULL,maze_copy,&ball_position);
                SDL_BlitSurface(trophy,NULL,maze_copy,&trophy_position);
                SDL_BlitSurface(maze_copy,NULL,screen,&maze_position);
                SDL_Flip(screen);
                break;
        }

        // here if we reach the exit position we exit the function
        if(trophy_position.x == ball_position.x && trophy_position.y == ball_position.y)
        {
            SDL_FreeSurface(maze_copy);
            SDL_FreeSurface(ball);
            SDL_FreeSurface(trophy);
            free(display_matrix);
            return 1;
        }
    }
}

// This function displays the game after the user clicks the "play" button
void play_game(SDL_Surface *screen)
{
    SDL_Surface *maze_surface ;
    stack* solved_maze = NULL;
    maze_matrix labyrinth;

    int i;
    int entry[2] ;
    int exit[2][2] ;

    while(continue_game)
    {
        // we generate a new maze each time 
        labyrinth = generate_maze();
        maze_surface=create_maze_surface(labyrinth);

        // entry positions are generated randomly
        entry[0] = rand()%MAZE_ROWS; 
        entry[1] = rand()%MAZE_COLS;
        
        // this loop will display a maze and to exit you must solve it with the first exit and the second exit
        i = 0;
        while(i < 2)
        { 
            /* here we ensure that the second exit position is different from the first and that the maze to solve is not 
               obvious, which is why we put the condition length(solve_maze < (N+M)) */
            do
            {
                free_stack(solved_maze);
                exit[i][0] = rand()%MAZE_ROWS;
                exit[i][1] = rand()%MAZE_COLS;
                solved_maze = solve_maze(labyrinth,entry,exit[i]);

            } while ( length(solved_maze) < MAZE_ROWS+MAZE_COLS || i*(exit[0][0] == exit[1][0] && exit[0][1] == exit[1][1]) );
            
            // handle_interaction returns 0 when we click ESCAPE, in this case we exit the play_game function and return to the main menu
            if (handle_interaction(screen,maze_surface,labyrinth,entry,exit[i])==0){
                SDL_FreeSurface(maze_surface);
                free(labyrinth);
                return;
            }
            i++;
        }
        SDL_FreeSurface(maze_surface);
        free(labyrinth);
    }
}

// This function displays the main menu that appears at the beginning
int show_main_menu(SDL_Surface *screen)
{
    SDL_Surface* menu = NULL;
    SDL_Surface* start = NULL;
    SDL_Surface* quit = NULL;
    SDL_Surface* title = NULL;
    SDL_Surface *background = IMG_Load("images/background.png");
    SDL_Event event;
    SDL_Rect start_position, quit_position, title_position;
    SDL_Rect menu_position = {0,0};

    menu = SDL_CreateRGBSurface(SDL_HWSURFACE,screen->w,screen->h,32,0,0,0,0);

    title = IMG_Load("images/labyrinthe.png");

    start = IMG_Load("images/start.png");

    quit = IMG_Load("images/quit.png");

    SDL_BlitSurface(background,NULL,menu,&menu_position);

    title_position.x = ( screen->w - title->w )/2;
    title_position.y = ( screen->h - title->h )/8;
    SDL_BlitSurface(title,NULL,menu,&title_position);

    
    start_position.x = ( screen->w - start->w )/2;
    start_position.y = 4*( screen->h - start->h )/8;
    SDL_BlitSurface(start,NULL,menu,&start_position);


    quit_position.x = ( screen->w - quit->w )/2;
    quit_position.y = 6*( screen->h - quit->h )/8;
    SDL_BlitSurface(quit,NULL,menu,&quit_position);
    
    
    SDL_BlitSurface(menu,NULL,screen,&menu_position);
    SDL_Flip(screen);

    while(continue_game)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                    continue_game = 0;
                    break; 
            case SDL_MOUSEBUTTONUP :
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if( event.button.x >= start_position.x && event.button.x <= start_position.x + start->w && event.button.y >= start_position.y && event.button.y <= start_position.y + start->h  )
                    {
                        SDL_BlitSurface(background,NULL,screen,&menu_position);
                        return 1;
                    }
                    else if( event.button.x >= quit_position.x && event.button.x <= quit_position.x + quit->w && event.button.y >= quit_position.y && event.button.y <= quit_position.y + quit->h  )
                    {
                        continue_game = 0;
                    }
                    break;
                }
                break;
        }
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(start);
    SDL_FreeSurface(background);
    
    return 0;
}

// This function displays the menu that gives the user the ability to choose a difficulty level
int show_difficulty_menu(SDL_Surface *screen)
{
    SDL_Surface* menu = NULL;
    SDL_Surface* easy = NULL;
    SDL_Surface* medium = NULL;
    SDL_Surface* hard = NULL;
    SDL_Surface *background = NULL;
    SDL_Event event;
    SDL_Rect easy_position, medium_position, hard_position;
    SDL_Rect menu_position = {0,0};

    menu = SDL_CreateRGBSurface(SDL_HWSURFACE,screen->w,screen->h,32,0,0,0,0);

    background = IMG_Load("images/background.png");

    easy = IMG_Load("images/facile.png");
    
    medium = IMG_Load("images/moyen.png"); 

    hard = IMG_Load("images/difficile.png");

    SDL_BlitSurface(background,NULL,menu,&menu_position);

    easy_position.x = ( screen->w - easy->w )/2;
    easy_position.y = 2*( screen->h - easy->h )/8;
    SDL_BlitSurface(easy,NULL,menu,&easy_position);

    medium_position.x = ( screen->w - medium->w )/2;
    medium_position.y = 4*( screen->h - medium->h )/8;
    SDL_BlitSurface(medium,NULL,menu,&medium_position);

    hard_position.x = ( screen->w - hard->w )/2;
    hard_position.y = 6*( screen->h - hard->h )/8;
    SDL_BlitSurface(hard,NULL,menu,&hard_position);

    SDL_BlitSurface(menu,NULL,screen,&menu_position);
    SDL_Flip(screen);

    while(continue_game)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                    continue_game = 0;
                    break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    return ESCAPE;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP :
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if( event.button.x >= easy_position.x && event.button.x <= easy_position.x + easy->w && event.button.y >= easy_position.y && event.button.y <= easy_position.y + easy->h  )
                    {
                        SDL_BlitSurface(background,NULL,screen,&menu_position);
                        return EASY;
                    }
                    else if( event.button.x >= medium_position.x && event.button.x <= medium_position.x + medium->w && event.button.y >= medium_position.y && event.button.y <= medium_position.y + medium->h  )
                    {
                        SDL_BlitSurface(background,NULL,screen,&menu_position);
                        return MEDIUM;
                    }
                    else if( event.button.x >= hard_position.x && event.button.x <= hard_position.x + hard->w && event.button.y >= hard_position.y && event.button.y <= hard_position.y + hard->h  )
                    {
                        SDL_BlitSurface(background,NULL,screen,&menu_position);
                        return HARD;
                    }
                    break;
                }
                break;
                
        }
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(easy);
    SDL_FreeSurface(medium);
    SDL_FreeSurface(hard);
    SDL_FreeSurface(background);
    return 0;

}
