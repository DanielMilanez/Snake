#include "main.h"

int main(void){
    PULL_SCORE(); // Puxando informações do arquivo score.txt
    GAME_INIT(); 

    // WALL   - parede
    // GROUND - bloco vazio

    INSETR_INTO(5, 10, GROUND); // Comando para inserir paredes ou outras coisas

    // LOOP DO JOGO
    do {
        KEYBOARD_CHECK(); // Verifica teclas precionadas
        game = MOVMENT_CONTROL(); // Controla movimento
        SHOW_GAME(); // Exibe o jogo
        DELAY(50); // Atraso para que o jogo seja fluido
    } while (game != 0); // Verifica se o jogador perdeu

    GAME_OVER_SCREEN(); 

    system("PAUSE"); // Espera para não fechar o terminal.
    return 0;
}