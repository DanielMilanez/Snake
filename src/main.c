#include "snake.c"

int main(void){
    PullScore();
    GameInit();

    InsertInto(5, 10, GND);
    do {
        KeyboardCheck();
        game = MoveControl();
        ShowGame();
        GameDelay(100);
    } while(game != 0);

    GameOverWindow();
    system("PAUSE");
    return 0;
}