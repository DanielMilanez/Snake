#include "../inc/snake.h"

/*------------- DEPENDENCES FUNCTIONS --------------*/

void GameInit(void){
    if(WINDOWS) system("cls");
    if(LINUX)   system("clear");

    X = SIZE_GAME / 2;
    Y = SIZE_GAME_LINES / 2;

    snake[0].x = X;
    snake[0].y = Y;

    srand(time(NULL));
    fruit.x = rand() % SIZE_GAME;
    fruit.y = rand() % SIZE_GAME_LINES;
    game = 0;
}

void ShowKey(char *key){
    if(headDir == K_UP)    sprintf(key, "vk_up   ");
    if(headDir == K_DOWN)  sprintf(key, "vk_down ");
    if(headDir == K_LEFT)  sprintf(key, "vk_left ");
    if(headDir == K_RIGHT) sprintf(key, "vk_right");
    
    printf("Press key: %s", key);
}

void ShowGame(void){
    char key[10] = "K_NONE";
    MOVE_CURSOR_FROM_START();

    printf("Best score: %d\n", bestScore);
    printf("Atual score: %d\n", score);

    printf(" ");
    for(int i = 0; i <= SIZE_GAME ; ++i) printf("_");
    putchar('\n');

    for(int i = 0; i < SIZE_GAME_LINES; ++i){
        printf("| ");
        for(int j = 0; j < SIZE_GAME; ++j){
            
            char *snakeColor = ANSI_GREEN;
            int colorStage = (score / 3) % 6;

            switch (colorStage) {
                case 0: snakeColor = ANSI_GREEN; break;
                case 1: snakeColor = ANSI_YELLOW; break;
                case 2: snakeColor = ANSI_BLUE; break;
                case 3: snakeColor = ANSI_MAGENTA; break;
                case 4: snakeColor = ANSI_CYAN; break;
                case 5: snakeColor = ANSI_WHITE; break;
            }

            switch(map[i][j]){
                case 0: putchar(' '); break;
                case 1: printf("%s@%s", ANSI_RED, ANSI_RESET); break;
                case 2: printf("%s#%s", snakeColor, ANSI_RESET); break;
                case 3: printf("%sO%s", snakeColor, ANSI_RESET); break;
                case 4: putchar('X'); break;
                case 5: putchar('|'); break;
                default: putchar('?'); break;
            }
        }
        printf("|\n");
    }

    for(int i = 2; i <= SIZE_GAME + 4; ++i) printf("-");
    printf("\n|   USE THE KEYS ARROWS FOR MOVE  |\n");
    for(int i = 2; i <= SIZE_GAME + 4; ++i) printf("-");
    putchar('\n');
    
    ShowKey(key);
    putchar('\n');
    putchar('\n');

    fflush(stdout);
    HIDE_CURSOR();
}

void PushScore(void){
    FILE *arq_w;
    arq_w = fopen("score.txt", "w");

    if (arq_w == NULL){
        puts("ERROR: Save score not responding...");
    }

    sprintf(scoreString, "%d", bestScore);
    fputs(scoreString, arq_w);
    
    fclose(arq_w);
}

void PullScore(void){
    FILE * arq_r;
    arq_r = fopen("score.txt", "r");
    if(arq_r == NULL) PushScore();

    fgets(scoreString, 10, arq_r);
    bestScore = atoi(scoreString);
}

void PlayerControl(void){
    lastDir = headDir;

    switch (headDir){
        case K_UP:    Y--; break;
        case K_DOWN:  Y++; break;
        case K_LEFT:  X--; break;
        case K_RIGHT: X++; break;
    }

    if (X < 0) X = 0;
    if (X >= SIZE_GAME) X = SIZE_GAME - 1;
    if (Y < 0) Y = 0;
    if (Y >= SIZE_GAME_LINES) Y = SIZE_GAME_LINES - 1;
}

void KeyboardCheck(void){
    if(_kbhit()){
        int ch = _getch();

        if (ch == 0 || ch == 224){
            ch = _getch();

           if ((ch == K_UP && lastDir != K_DOWN)    ||
               (ch == K_DOWN && lastDir != K_UP)    ||
               (ch == K_LEFT && lastDir != K_RIGHT) ||
               (ch == K_RIGHT && lastDir != K_LEFT)) {
                headDir = ch;
            }
        }
    }
}

void GameOverWindow(void){
    GameDelay(500);
    if (WINDOWS) system("cls");
    if (LINUX) system("clear");

    printf("\n========================================\n");
    printf("               FIM DE JOGO              \n");
    printf("========================================\n");

    printf("\n-> Score: %d", score);
    printf("\n-> Record: %d\n", bestScore);

    if (score >= bestScore){
        bestScore = score;
        PushScore();
    }

    printf("\n========================================\n");
    printf("         Obrigado por jogar!            \n");
    printf("========================================\n\n");
}

void GameDelay(int time_ms){
    struct timespec ts;
    ts.tv_sec = time_ms / 1000;
    ts.tv_nsec = (time_ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void InsertInto(int x, int y, int who) {
    map[y][x] = who;
}

int MoveControl(void) {
    int nextX = X, nextY = Y;

    switch (headDir) {
        case K_UP:    nextY--; break;
        case K_DOWN:  nextY++; break;
        case K_LEFT:  nextX--; break;
        case K_RIGHT: nextX++; break;
    }

    // Colisão com paredes
    if (nextX < 0 || nextX >= SIZE_GAME || nextY < 0 || nextY >= SIZE_GAME_LINES) {
        InsertInto(snake[0].x, snake[0].y, PDEAD);
        return 0;
    }

    int nextBlock = map[nextY][nextX];

    // Colisão com "objetos"
    if (nextBlock == PBODY || nextBlock == WALL) {
        InsertInto(snake[0].x, snake[0].y, PDEAD);
        return 0;
    }

    int comeu_fruta = (nextBlock == FRUIT);

    if (comeu_fruta) {
        score++;

        if (snakeSize < MAX_SIZE_SNAKE - 1) {
            snakeSize++;
            srand(time(NULL));
            fruit.x = rand() % SIZE_GAME;
            fruit.y = rand() % SIZE_GAME_LINES;
        }else return 0;
    }

    for (int i = snakeSize; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    PlayerControl();  
    snake[0].x = X;
    snake[0].y = Y;

    for (int i = 0; i < SIZE_GAME_LINES; i++) {
        for (int j = 0; j < SIZE_GAME; j++) {
            if (map[i][j] == PBODY || map[i][j] == PHEAD)
                map[i][j] = GND;
        }
    }

    for (int i = 1; i <= snakeSize; i++) {
        InsertInto(snake[i].x, snake[i].y, PBODY);
    }

    // Atualiza mapa com fruta e cabeça da cobra
    InsertInto(fruit.x, fruit.y, FRUIT);
    InsertInto(snake[0].x, snake[0].y, PHEAD);

    return 1; 
}
