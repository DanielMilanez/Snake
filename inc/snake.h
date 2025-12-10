#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "dependences.h"

/*------------- TYPEDEFS ------------*/

typedef struct{
    int x, y;
}setPoint;

/*--------- START FUNCTIONS ---------*/

void GameInit(void);
void ShowGame(void);
void PullScore(void);
void PushScore(void);
void PlayerControl(void);
void KeyboardCheck(void);
void GameOverWindow(void);

void ShowKey(char *key);
void GameDelay(int time_ms);
void InsertInto(int x, int y, int who);

int MoveControl(void);

/*--------- GLOBAL VARIABLES --------*/

int X, Y;
int game;

int score = 0;
int bestScore = 0;
char scoreString[5];

setPoint fruit;
setPoint snake[MAX_SIZE_SNAKE];

int headDir = 0;
int lastDir = 0;

int headPos[2] = {0};

int snakeSize = MIN_SIZE_SNAKE;
int map[SIZE_GAME_LINES][SIZE_GAME] = {{0}};

/*-----------------------------------*/
