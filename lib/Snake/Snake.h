#pragma once

#define EMPTY 0
#define APPLE -1

#define ROWS 15
#define COLS 22
#define SIZE 4

#define UP -1
#define DOWN 1
#define LEFT -2
#define RIGHT 2

using namespace std;

// STRUCTS
struct pos
{
    int x;
    int y;

    pos(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
typedef struct pos *Pos;

struct game
{
    bool gameOver;
    int dir;
    int length;

    int **grid;
    Pos headPos;
    Pos applePos;
};
typedef struct game *Game;

Game newGame();
void deleteGame(Game game);
void tick(char inChar, Game game);
