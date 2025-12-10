## Sobre o Projeto

>⚠️ Este projeto foi testado em ambiente Windows. Em outros sistemas, pode ser necessário adaptar algumas bibliotecas.

Este sem dúvidas é um clássico atemporal que, além de divertido, representa uma excelente introdução ao desenvolvimento de jogos para iniciantes. Ele foi o primeiro jogo que desenvolvi na vida! Então por isso, resolvi realizar esse projeto, em forma de comemoração aos meus 10 anos como desenvolvedor de jogos (faço jogos desde os 10 anos). Neste projeto, implementamos o `Snake` inteiramente em linguagem C, proporcionando uma oportunidade prática de aprender conceitos fundamentais como manipulação de tempo, controle de fluxo, leitura de entradas do teclado e persistência de dados.

Lembrando que o desenvolvimento completo deste jogo foi documentado passo a passo em uma série de vídeos no meu canal do YouTube, tornando o aprendizado ainda mais acessível e didático.

O Snake consiste em controlar uma cobra que se movimenta pelo terminal, com o objetivo de coletar alimentos gerados aleatoriamente na tela. A cada alimento consumido, a cobra cresce em tamanho, aumentando também a dificuldade do jogo. A partida termina quando a cobra colide com as bordas do mapa ou com seu próprio corpo.

## Funcionalidades e Implementações

Para tornar o jogo funcional e mais interativo, foram utilizadas as seguintes bibliotecas.
```C
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <conio.h>
``` 
Além disso, foram desenvolvidas algumas funcionalidades específicas:

- Função de Delay: Criação de um mecanismo para pausar a execução em milissegundos, simulando fluidez no movimento da cobra.

- Sistema de Salvamento de Pontuação: A pontuação é armazenada, permitindo que o jogador acompanhe seus recordes.

- Leitura de Teclas (Setas): Implementado controle via teclado, utilizando as setas direcionais para movimentar a cobra em tempo real.


## Tecnologias Utilizadas

- Linguagem C: O projeto foi desenvolvido 100% em C, utilizando o editor Visual Studio Code, sem dependência de bibliotecas externas ou frameworks adicionais.

## Como Baixar e Rodar o Projeto

1. Abra o `prompt de comando` em sua maquina

2. Clone este repositório na sua máquina:
```bash
    git clone https://github.com/DanielMilanez/Snake.git
```

2. Navegue até o diretório do projeto. Caso esteja usando o terminal acesse o diretório com o código:
```bash
    cd Snake
```

3. Execute o jogo clicando sobre o aplicativo `SnakeGame.exe`, ou então execute-o em linha de código:
```bash
    snake.exe
```

4. Tente superar meu recorde!


## Confira a história em primeira mão!!!

Em meu canal no youtube eu conto como foi o desenvolvimento desse projeto e ainda menciono sobre odesenvolvimento de projetos futuros. Confira a série completa de vídeos no meu canal do YouTube `terminal quest`. [🎥 MiTcH - YouTube](https://www.youtube.com/@mitchzito).


<p align="center">
  <img src="https://readme-typing-svg.demolab.com/?lines=Mas+lembre-se;O+mundo+e+pequeno+demais+para+aquels+que+sonham!;Por+isso+a+necessidade+de+criar+novos!&font=Fira%20Code&center=true&color=64F58E&width=1000&height=50&duration=4000&pause=1000" alt="Example Usage - README Typing SVG">
</p>
