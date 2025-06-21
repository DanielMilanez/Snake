#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <conio.h>

// ALTERE CASO SEU SISTEMA FOR LINUX
#define WINDOWS_SYSTEM // para windows
// #define LINUX_SYSTEM   // para linux 

#define WINDOWS 0
#define LINUX   0

#ifdef WINDOWS_SYSTEM
    #undef WINDOWS
    #define WINDOWS 1
#endif

#ifdef LINUX_SYSTEM
    #undef LINUX
    #define LINUX 1
#endif

#define vk_left 75
#define vk_right 77
#define vk_up 72
#define vk_down 80

#define SIZE_GAME 32
#define SIZE_GAME_LINES 16

#define GROUND 0
#define FRUIT  1
#define PLAYER_BODDY 2
#define PLAYER_HEAD 3
#define PLAYER_DEAD 4
#define WALL 5

#define MIN_SNAKE_SIZE 3
#define MAX_SNAKE_SIZE 515
#define WIN_SCORE (MAX_SNAKE_SIZE - 3)
#define HIDE_CURSOR(void) printf("\033[?25l")

/*----------------------------------------*/

typedef struct {
    int x, y;
}POINT;

/*---------------------------------------*/
void GAME_INIT(void);
void SHOW_GAME(void);
void SAVE_SCORE(void);
void PULL_SCORE(void);
void DELAY(int time_ms);
void PALYER_CONTROL(void);
int MOVMENT_CONTROL(void);
void KEYBOARD_CHECK(void);
void GAME_OVER_SCREEN(void);
void INSETR_INTO(int x, int y, int who);
/*---------------------------------------*/
int X, Y;
int game;
POINT fruit;
int score = 0;
char score_string[5];
int dir_head = 0;
int last_dir = 0;
int best_score = 2;
int had_pos[2] = {0};
int size  = MIN_SNAKE_SIZE;
POINT snake[MAX_SNAKE_SIZE];
int map[SIZE_GAME_LINES][SIZE_GAME] = {{0}};

/*---------------------------------------*/

void GAME_INIT(void){    
    // LIMPA TERMINAL
    if (WINDOWS) system("cls");
    if (LINUX) system("clear");
    
    // POSICIONA A SNAKE NO MEIO
    X = SIZE_GAME / 2;
    Y = SIZE_GAME_LINES / 2;
    
    // POSICIONA O CORPO NO MEIO
    snake[0].x = X;
    snake[0].y = Y;

    // GERANDO FRUTA
    srand(time(NULL));
    fruit.x = rand() % 32;
    fruit.y = rand() % 16;
    game = 0;
}

void SHOW_GAME(void) {
    char tecla[10] = "k_NONE";

    printf("\033[H"); // Movendo cursor para o inicio 

    printf("MELHOR %d pts\n", best_score);
    printf("PONTOS %d pts\n", score);
    printf(" ");

    for(int i = 2; i <= SIZE_GAME + 2; ++i)  printf("_");
    putchar('\n');

    for (int i = 0; i < SIZE_GAME_LINES; ++i) {
        printf("| ");
        for (int j = 0; j < SIZE_GAME; ++j) {
            switch (map[i][j]) {
                case 0:
                    putchar(' '); // Espaço vazio
                    break;
                case 1:
                    putchar('@'); // Fruta
                    break;
                case 2:
                    putchar('#'); // Corpo Jogador
                    break;
                case 3:
                    putchar('O'); // Cabeça Jogador
                    break;
                case 4:
                    putchar('X'); // Morto
                    break;
                case 5:
                    putchar('|'); // Parede
                    break;
                default:
                    putchar('?'); // Desconhecido
            }
        }
        printf("|\n");
    }

    for(int i = 2; i <= SIZE_GAME + 4; ++i)  printf("-");
    printf("\n|   USE AS SETAS PARA MOVER-SE    |\n");
    for(int i = 2; i <= SIZE_GAME + 4; ++i)  printf("_");

    if (dir_head == vk_up) sprintf(tecla, "k_up     ");
    if (dir_head == vk_down) sprintf(tecla, "k_down ");
    if (dir_head == vk_left) sprintf(tecla, "k_left ");
    if (dir_head == vk_right) sprintf(tecla, "k_right");

    // Mostrador tecla precionada
    // printf("TECLA PRECIONADA: %s", tecla);

    fflush(stdout);  // Força a impressão no terminal imediatamente
    HIDE_CURSOR();   // Desabilitando visualização do cursor.
}

void KEYBOARD_CHECK(void) {
    if (_kbhit()) {
        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();
            
            if ((ch == vk_up && last_dir != vk_down) ||
                (ch == vk_down && last_dir != vk_up) ||
                (ch == vk_left && last_dir != vk_right) ||
                (ch == vk_right && last_dir != vk_left)) {
                    dir_head = ch;
            }
        }
    }
}

void DELAY(int time_ms){
    struct timespec ts;
    ts.tv_sec = time_ms / 1000;
    ts.tv_nsec = (time_ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
 
void INSETR_INTO(int x, int y, int who){
    map[y][x] = who;
}

int MOVMENT_CONTROL(void) {
    int nextX = X, nextY = Y;

    switch (dir_head) {
        case vk_up:    nextY--; break;
        case vk_down:  nextY++; break;
        case vk_left:  nextX--; break;
        case vk_right: nextX++; break;
    }

    // Colisão com paredes
    if (nextX < 0 || nextX >= SIZE_GAME || nextY < 0 || nextY >= SIZE_GAME_LINES) {
        INSETR_INTO(snake[0].x, snake[0].y, PLAYER_DEAD);
        return 0;
    }

    int nextBlock = map[nextY][nextX];

    // Colisão com "objetos"
    if (nextBlock == PLAYER_BODDY || nextBlock == WALL) {
        INSETR_INTO(snake[0].x, snake[0].y, PLAYER_DEAD);
        return 0;
    }

    int comeu_fruta = (nextBlock == FRUIT);

    if (comeu_fruta) {
        score++;

        if (size < MAX_SNAKE_SIZE - 1) {
            size++;
            srand(time(NULL));
            fruit.x = rand() % SIZE_GAME;
            fruit.y = rand() % SIZE_GAME_LINES;
        }else return 0;
    }

    for (int i = size; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    PALYER_CONTROL();  
    snake[0].x = X;
    snake[0].y = Y;

    for (int i = 0; i < SIZE_GAME_LINES; i++) {
        for (int j = 0; j < SIZE_GAME; j++) {
            if (map[i][j] == PLAYER_BODDY || map[i][j] == PLAYER_HEAD)
                map[i][j] = GROUND;
        }
    }

    for (int i = 1; i <= size; i++) {
        INSETR_INTO(snake[i].x, snake[i].y, PLAYER_BODDY);
    }

    // Atualiza mapa com fruta e cabeça da cobra
    INSETR_INTO(fruit.x, fruit.y, FRUIT);
    INSETR_INTO(snake[0].x, snake[0].y, PLAYER_HEAD);

    return 1; 
}

void PALYER_CONTROL(void){
    last_dir = dir_head;

    switch (dir_head){
        case vk_up:    Y--; break;
        case vk_down:  Y++; break;
        case vk_left:  X--; break;
        case vk_right: X++; break;
    }

    if (X < 0) X = 0;
    if (X >= SIZE_GAME) X = SIZE_GAME - 1;
    if (Y < 0) Y = 0;
    if (Y >= SIZE_GAME_LINES) Y = SIZE_GAME_LINES - 1;
}

void GAME_OVER_SCREEN(void){
    DELAY(500);
    if (WINDOWS) system("cls");
    if (LINUX) system("clear");

    printf("\n========================================\n");
    printf("               FIM DE JOGO              \n");
    printf("========================================\n");

    printf("\n-> Score: %d", score);
    printf("\n-> Record: %d\n", best_score);

    if (score >= best_score){
        best_score = score;
        SAVE_SCORE();
    }

    printf("\n========================================\n");
    printf("         Obrigado por jogar!            \n");
    printf("========================================\n\n");
}

void SAVE_SCORE(void){
    FILE *arq_w;
    arq_w = fopen("score.txt", "w");

    if (arq_w == NULL){
        puts("ERROR: Save score not responding...");
    }

    sprintf(score_string, "%d", best_score);
    fputs(score_string, arq_w);
    
    fclose(arq_w);
}

void PULL_SCORE(void){
    FILE *arq_r;
    arq_r = fopen("score.txt", "r");
    
    if(arq_r == NULL){
        SAVE_SCORE();
    }

    fgets(score_string, 10, arq_r);
    best_score = atoi(score_string);

}
