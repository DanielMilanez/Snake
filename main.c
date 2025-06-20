#include "main.h"

int main(void){
    
    PULL_SCORE();
    
    // CLEAR TERMINAL
    if (WINDOWS) system("cls");
    if (LINUX) system("clear");
    
    X = SIZE_GAME / 2;
    Y = SIZE_GAME_LINES / 2;
    
    snake[0].x = X;
    snake[0].y = Y;

    // Gerando a posição da fruta inicial 
    srand(time(NULL));
    fruit.x = rand() % 32;
    fruit.y = rand() % 16;
    int game = 0;

    // GAME START UP
    do {
        KEYBOARD_CHECK();
        game = MOVMENT_CONTROL();
        SHOW_GAME();
        DELAY(50);
    } while (game != 0);

    GAME_OVER_SCREEN();
    
    system("PAUSE");
    return 0;
}