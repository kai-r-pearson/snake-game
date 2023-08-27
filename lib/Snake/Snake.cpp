#include <Arduino.h>
#include <stdlib.h>
#include "Snake.h"

// FUNCTION DECLARATIONS
Game newGame();
int ** newGrid();
void deleteGrid(int **grid);
void deleteGame(Game game);
struct pos getDeltaPos(char inChar, Game game);
int correctCoord(int z, int max);
void changePos(Pos pos, Pos deltaPos);
bool samePos(Pos pos1, Pos pos2);
void randomisePos(Pos pos, Game game);
void decrement(Game game);
void tick(char inChar, Game game);

// FUNCTIONS DEFINITIONS
Game newGame() {
    Game game = new struct game;

    game->gameOver = false;
    game->dir = LEFT;  
    game->length = 1;

    // Declare memory block of size ROWS
    int** grid = newGrid();

    int startHeadX = ROWS/2;
    int startHeadY = COLS/2;
    int startAppleX = 1;
    int startAppleY = 1;

    game->headPos = new struct pos(startHeadX, startHeadY);
    game->applePos = new struct pos(startAppleX, startAppleY);
    
    game->grid = grid;
    game->grid[startHeadY][startHeadX] = game->length;
    game->grid[startAppleY][startAppleX] = APPLE;

    return game;
}

int ** newGrid() {

    // Declare memory block of size M
    int** grid = new int*[ROWS];
 
    for (int i = 0; i < ROWS; i++) {
        grid[i] = new int[COLS];
    }
 
    // Traverse the 2D array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    return grid;

}

void deleteGrid(int **grid) {
    // Delete the array created
    for (int i = 0; i < ROWS; i++) // To delete the inner arrays
        delete[] grid[i];
    delete[] grid;
}

void deleteGame(Game game) {
    deleteGrid(game->grid);
    delete game->headPos;
    delete game->applePos;
    delete game;
}

// POSITION FUNCTIONS

struct pos getDeltaPos(char inChar, Game game)
{
    int dir = game->dir;
    switch (inChar)
    {
    case 'w':
        game->dir = UP;
        return {0, -1};
    case 'd':
        game->dir = RIGHT;
        return {1, 0};
    case 's':
        game->dir = DOWN;
        return {0, 1};
    case 'a':
        game->dir = LEFT;
        return {-1, 0};
    case 'q':
        game->gameOver = 1;
        return {0, 0};
    default:
        if (dir == UP)
        {
            return {0, -1};
        }
        else if (dir == RIGHT)
        {
            return {1, 0};
        }
        else if (dir == DOWN)
        {
            return {0, 1};
        }
        else
        {
            return {-1, 0};
        }
    }
}


int correctCoord(int z, int max)
{
    if (z < 0)
    {
        return max + z;
    }
    else if (z >= max)
    {
        return z % max;
    }
    return z;
}

void changePos(Pos pos, Pos deltaPos)
{
    pos->x = correctCoord(pos->x + deltaPos->x, COLS);
    pos->y = correctCoord(pos->y + deltaPos->y, ROWS);
}

bool samePos(Pos pos1, Pos pos2)
{
    if (pos1->x == pos2->x &&
        pos1->y == pos2->y)
    {
        return true;
    }
    return false;
}

// GAME FUNCTIONS

void randomisePos(Pos pos, Game game)
{
    char x = rand() % COLS;
    char y = rand() % ROWS;

    if (game->grid[y][x] != 0)
    {
        randomisePos(pos, game);
    }

    pos->x = x;
    pos->y = y;
}

void decrement(Game game) {
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            if(game->grid[i][j] > 0) game->grid[i][j]--; 
        }
    }
}

void tick(char inChar, Game game)
{
    // get change in position
    struct pos deltaPos = getDeltaPos(inChar, game);

    // update head position
    changePos(game->headPos, &deltaPos);

    // new head position
    int headX = game->headPos->x;
    int headY = game->headPos->y;

    // value of the square head is moving into
    int inSquare = game->grid[headY][headX];

    if (inSquare > 0) {
        // Game over
        game->gameOver = true;
    } else if (inSquare == APPLE) {
        // apple collected don't remove tail
        game->length++;
        game->grid[headY][headX] = game->length;

        // Rerandomise apple position
        randomisePos(game->applePos, game);

        // Update apple in grid
        game->grid[game->applePos->y][game->applePos->x] = APPLE;

    } else {
        // no apple collected, make current tail square EMPTY
        game->grid[headY][headX] = game->length+1;

        // decrement all positive grid values
        decrement(game);
    }

}

