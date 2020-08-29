/**
*   ====================
*     GAME: MOUSE TRAP
*   ====================
*
*   ================
*    FUNCOES USADAS
*   ================
*   main()
*       funcao principal do programa
*       responsavel por chamar as funcoes auxiliares
*   ----------------
*   _getch()
*       espera teclado ser acionado e guarda o char acionado
*       nao avanca para a proxima instrucao enquanto
*       o teclado nao for acionado
*   ----------------
*   fopen()
*       abre um arquivo em um endereco por um ponteiro
*       ponteiro passado como parametro da funcao
*   ----------------
*   fclose()
*       fecha o arquivo aberto
*       ponteiro passado como parametro para localizar e
*       fechar arquivo
*   ----------------
*   cria_matriz_mapa()
*       recebe como parametro uma matriz bidimensional
*       le um arquivo e guarda os caracteres nessa matriz
*       caracteres lidos 1-a-1
*   ----------------
*   print_mapa()
*       print na tela dos caracteres presentes na
*       matriz mapa passada como parametro
*   ----------------
*   acha_rato()
*       encontra a posicao inicial do rato na matriz
*       a matriz deve ser passada como parametro juntamente com
*       os ponteiros de posicao inicial do rato para receberem os dados
*   ----------------
*   acha_gatos()
*       encontra as posicoes iniciais dos gatos na matriz
*       recebe como parametros a matriz contendo os caracteres do mapa e
*       um array do tipo GATOS contendo as posicoes dos gatos
*   ----------------
*   acha_portas()
*       recebe como parametros a matriz com os caracteres do mapa e o tipo PORTA
*       procura e guarda as posicoes das portas no mapa
*   ----------------
*   move_rato()
*       recebe como parametros ponteiros de caractere acionado pelo teclado,
*       posicao do rato eixo x, posicao do rato eixo y, matriz do mapa e placar a ser atualizado
*       faz as devidas verificacoes para mover ou nao o rato. Atualiza o placar se colidir com 'Q'
*       envia por parametro a futura posicao do rato para a funcao colisao()
*   ----------------
*   move_gato()
*       recebe como parametros o vetor tipo GATOS, matriz do mapa e ponteiro
*       numero de vidas que representa a quantidade de vidas do rato.
*       faz as devidas verificacoes para mover ou nao os gatos. Atualiza numero de vidas do rato.
*       envia por parametro a futura posicao dos gatos para a funcao colisao_gato().
*   ----------------
*   colisao()
*       recebe como parametros a posicao y do rato, a posicao x do rato, matriz mapa e ponteiro placar.
*       verifica a futura posicao do rato e se for parede(X na matriz mapa) nao move o rato.
*       se for queijo(Q na matriz mapa) atualiza o placar.
*       retorna para a funcao move_rato().
*   ----------------
*   colisao_gato()
*       recebe como parametros a posicao y do gato, a posicao x do gato, matriz mapa e ponteiro rato_vidas.
*       verifica a futura posicao do gato e se for parede(X na matriz mapa) nao move o gato.
*       se for rato(M na matriz mapa) decrementa o numero de vidas do rato.
*       se for gato(G na mariz mapa) nao move o gato.
*       retorna para a funcao move_gato().
*   ----------------
*   move_xy()
*       recebe como parametros coordenadas x e y, dois inteiros.
*       move caracteres na tela.
*   ----------------
*   muda_portas()
*       recebe por parametros matriz mapa, tipo PORTA com posicoes atuais
*       tipo PORTA com posicoes futuras, tipo PORTA auxiliar e ponteiro com caractere do teclado (b/B)
*       Altera as posicoes das portas e prepara as novas posicoes(posicoes antigas) quando
*       funcao for chamada novamente
*   ----------------
*   gera_numero_aleatorio()
*       recebe por parametro dois inteiros, um numero minimo e um numero maximo
*       funcao retorna o numero gerado. Utilizada na move_gato()
*   ----------------
*   menu()
*       print na tela do menu principal do jogo com as opcoes:
*       novo jogo, leaderboard e sair
*   ----------------
*   mostra_leaderboard()
*       print na tela do leaderboard. Melhores pontuacoes atingidas.
*   ----------------
*   atualiza_leaderboard()
*       cria/edita o arquivo leaderoard que contem as melhores pontuacoes.
*       recebe por parametro inteiro pontuacao que armazena a
*       pontuacao adquirida no jogo
*   ----------------
*   print_osso()
*       recebe por parametro um inteiro osso. Verifica se osso eh maior que 0
*       se for, modo cachorro esta ativo e printa na tela mensagem informando isso
*   ----------------
*   ================
*     LIBS USADAS
*   ================
*   <stdio.h> standard input/output
*       biblioteca com as funcoes basicas de entrada e saida
*   ----------------
*   <conio.h> console input/output
*       biblioteca para input e output no console
*   ----------------
*   <windows.h>
*       biblioteca com funcionalidades do Windows
*   ================
*    CORES NO CMD
*   ================
*   0 = BLACK;  1 = BLUE;       2 = GREEN;  3 = AQUA;
*   4 = RED;    5 = PURPLE;     6 = YELLOW; 7 = WHITE;
*   8 = GRAY;   9 = LIGHT BLUE;
**/

#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define LIN 12
#define COL 28

/** ====================
*    ESTRUTURAS CRIADAS
*   ====================
**/

// estrutura para guardar as posicoes das portas e o estado delas
typedef struct tipo_porta
{
    int posicao_x;
    int posicao_y;
    int estado;
} PORTA;

// estrutura para guardar as posicoes dos gatos
typedef struct tipo_gato
{
    int posicao_x;
    int posicao_y;
} GATOS;

// estrutura para guardar o tipo jogador antes de gravar/ler arquivo
typedef struct tipo_jogador
{
    char nome[12];
    int pontos;
} JOGADOR;

/** ===========
*     FUNCOES
*   ===========
**/
// funcao responsavel por criar a matriz do mapa
void cria_matriz_mapa(char matriz_mapa[LIN][COL], char matriz_bonita[LIN][COL])
{
    // variaveis
    FILE *arquivo_mapa; // cria um ponteiro do tipo arquivo
    int i, j; // contadores usados no for

    // endereço de onde esta o mapa. "r" de Read
    arquivo_mapa = fopen("mapas/5.txt", "r");

    // verifica se o arquivo existe(foi encontrado)
    if(arquivo_mapa)
    {
        // for para as linhas do mapa
        for(i = 0; i < LIN; i++)
        {
            // for para as colunas do mapa
            for(j = 0; j < COL; j++)
            {
                matriz_mapa[i][j] = getc(arquivo_mapa);
                matriz_bonita[i][j] = matriz_mapa[i][j];
            }
        }
        fclose(arquivo_mapa); // fecha o arquivo
    }
    else
    {
        // se arquivo nao foi encontrado informa o usuario
        printf("ARQUIVO NAO ENCONTRADO !\n");
    }
}

// funcao para a impressao do mapa inicial na tela
void print_mapa(char matriz_mapa[LIN][COL])
{
    // contadores para o for
    int i, j;
    // for para as linhas do mapa
    for(i = 0; i < LIN; i++)
    {
        // for para as colunas do mapa
        for(j = 0; j < COL; j++)
        {
            // switch para verificacao do caractere e poder alterar a cor
            switch(matriz_mapa[i][j])
            {
            case 'X':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                matriz_mapa[i][j] = 178;
                break;

            case 'Q':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                matriz_mapa[i][j] = '.';
                break;

            case 'O':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                break;

            case 'M':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                break;

            case 'G':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                break;

            case 'T':
                // altera a cor do caractere
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                matriz_mapa[i][j] = 176;
                break;
            }
            // print na tela de cada caractere
            printf("%c", matriz_mapa[i][j]);
        }
    }
}

// funcao responsavel por encontrar a posicao inicial do rato na tela
void acha_rato(char matriz_mapa[LIN][COL], int *posicao_rato_linha, int *posicao_rato_coluna)
{
    // variaveis
    int i, j; // contadores para o for
    // for para as linhas do mapa
    for(i = 0; i < LIN; i++)
    {
        // for para as colunas do mapa
        for(j = 0; j < COL; j++)
        {
            // verifica se o caractere atual eh o correspondente ao do rato M
            if(matriz_mapa[i][j] == 'M')
            {
                *posicao_rato_linha = i;
                *posicao_rato_coluna = j;
            }
        }
    }
}

// funcao para encontrar as posicoes dos gatos na matriz
void acha_gatos(char matriz_mapa[LIN][COL], GATOS gatos[])
{
    // variaveis locais
    int i, j, k = 0;
    // for para as linhas do mapa
    for(i = 0; i < LIN; i++)
    {
        // for para as colunas do mapa
        for(j = 0; j < COL; j++)
        {
            // verifica se o caractere atual eh o correspondente ao do gato G
            if(matriz_mapa[i][j] == 'G')
            {
                gatos[k].posicao_x = i; // guarda a linha em que esta o gato
                gatos[k].posicao_y = j; // guarda a coluna em que esta o gato
                k++; // incrementa k para guardar o proximo gato no array
            }
        }
    }
}

// funcao para encontrar todas as portas do mapa
void acha_portas(char matriz_mapa[LIN][COL], PORTA portas[])
{
    // variaveis
    int i, j, k = 0; // contadores para o for
    // for para as linhas do mapa
    for(i = 0; i < LIN; i++)
    {
        // for para as colunas do mapa
        for(j = 0; j < COL; j++)
        {
            // verifica se o caractere atual eh o correspondente ao da porta T
            if(matriz_mapa[i][j] == 'T')
            {
                portas[k].posicao_x = i;
                portas[k].posicao_y = j;
                portas[k].estado = 1;
                k++;
            }
        }
    }
}

// funcao que permite o movimento do rato
void move_rato(char *le_teclado, int *posicao_rato_x, int *posicao_rato_y, char matriz_mapa[LIN][COL], int *placar, int * osso)
{
    // variaveis
    int check_colisao = 0; // flag para saber se o rato bateu em algo

    // os numeros correspondem as setas do teclado. 72 cima. 75 esquerda. 80 baixo. 77 direita.
    switch(*le_teclado)
    {
    case 'w':
    case 'W':
    case 72:
        // verifica se houve colisao
        check_colisao = colisao(*posicao_rato_y, *posicao_rato_x - 1, matriz_mapa, placar, osso);

        // se nao houve colisao move rato, senao faz nada
        if(check_colisao == 0)
        {
            *posicao_rato_x = *posicao_rato_x - 1; // move o rato
            matriz_mapa[*posicao_rato_x][*posicao_rato_y] = 'M';
            matriz_mapa[*posicao_rato_x + 1][*posicao_rato_y] = ' ';  // limpa a posicao onde o rato estava
        }
        // coloca espaco em branco para nao ficar andando pra sempre
        *le_teclado = ' ';
        break;

    case 'a':
    case 'A':
    case 75:
        // verifica se houve colisao
        check_colisao = colisao(*posicao_rato_y - 1, *posicao_rato_x, matriz_mapa, placar, osso);

        // se nao houve colisao move rato, senao faz nada
        if(check_colisao == 0)
        {
            *posicao_rato_y = *posicao_rato_y - 1; // altera a posicao do rato
            matriz_mapa[*posicao_rato_x][*posicao_rato_y] = 'M';
            matriz_mapa[*posicao_rato_x][*posicao_rato_y + 1] = ' '; // limpa a posicao por onde o rato passou
        }
        // coloca espaco em branco para nao ficar andando pra sempre
        *le_teclado = ' ';
        break;

    case 's':
    case 'S':
    case 80:
        // verifica se houve colisao
        check_colisao = colisao(*posicao_rato_y, *posicao_rato_x + 1, matriz_mapa, placar, osso);

        // se nao houve colisao move rato, senao faz nada
        if(check_colisao == 0)
        {
            *posicao_rato_x = *posicao_rato_x + 1; // altera a posicao do rato
            matriz_mapa[*posicao_rato_x][*posicao_rato_y] = 'M';
            matriz_mapa[*posicao_rato_x - 1][*posicao_rato_y] = ' '; // limpa a posicao por onde o rato passou
        }
        // coloca espaco em branco para nao ficar andando pra sempre
        *le_teclado = ' ';
        break;

    case 'd':
    case 'D':
    case 77:
        // verifica se houve colisao
        check_colisao = colisao(*posicao_rato_y + 1, *posicao_rato_x, matriz_mapa, placar, osso);

        // se nao houve colisao move rato, senao faz nada
        if(check_colisao == 0)
        {
            *posicao_rato_y = *posicao_rato_y + 1; // altera a posicao do rato
            matriz_mapa[*posicao_rato_x][*posicao_rato_y] = 'M';
            matriz_mapa[*posicao_rato_x][*posicao_rato_y - 1] = ' ';
        }
        // coloca espaco em branco para nao ficar andando pra sempre
        *le_teclado = ' ';
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}

// funcao para movimentar os gato
void move_gato(GATOS gatos[], char matriz_mapa[LIN][COL], int *rato_vidas, int *placar, int *osso)
{
    // variaveis locais
    int i, j; // usado como contador
    int num_aleatorio; // guarda um numero gerado aleatoriamente
    int check_colisao; // flag para saber se houve colisao
    char auxiliar = ' '; // usado para guardar o que estiver a frente do gato(queijo ou osso)

    // for para cada gato
    for(i = 0; i < 4; i++)
    {
        // gera um numero aleatorio
        num_aleatorio = gera_numero_aleatorio(1, 4);

        // de acordo com o numero gerado move o gato para alguma direcao
        switch(num_aleatorio)
        {
        // move para cima
        case 1:
            // verifica se houve colisao
            check_colisao = colisao_gato(gatos[i].posicao_y, ((gatos[i].posicao_x) - 1), matriz_mapa, rato_vidas, placar, osso);

            // se nao houver colisao move o gato
            if(check_colisao == 0)
            {
                // verifica se existe um queijo ou osso a frente do gato para nao apagar ele
                if (matriz_mapa[((gatos[i].posicao_x) - 1)][(gatos[i].posicao_y)] == 'Q'
                        || matriz_mapa[((gatos[i].posicao_x) - 1)][(gatos[i].posicao_y)] == 'O')
                {
                    // se for Q ou O guarda o caractere para repor depois
                    auxiliar = matriz_mapa[((gatos[i].posicao_x) - 1)][(gatos[i].posicao_y)];
                }
                else
                {
                    auxiliar = ' ';
                }
                // atualiza a posicao do gato
                gatos[i].posicao_x = (gatos[i].posicao_x) - 1; // altera a posicao do gato especifico
                matriz_mapa[((gatos[i].posicao_x) + 1)][(gatos[i].posicao_y)] = auxiliar; // atualiza a antiga posicao
                matriz_mapa[(gatos[i].posicao_x)][(gatos[i].posicao_y)] = 'G'; // coloca a nova posicao

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // coloca a cor no caractere

                // Verifica se auxiliar eh igual a Q e substitui por ponto
                if(auxiliar == 'Q')
                    auxiliar = '.';

                // altera visualmente a posicao do gato na tela
                move_xy((gatos[i].posicao_x) + 1, gatos[i].posicao_y); // pega a antiga posicao visual do gato
                printf("%c", auxiliar); // atualiza espaco na tela

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // coloca a cor no caractere

                move_xy(gatos[i].posicao_x, gatos[i].posicao_y); // pega a posicao visual atual do gato
                printf("G"); // coloca G na tela
            }
            break;
        // move para baixo
        case 2:
            // verifica se houve colisao
            check_colisao = colisao_gato(gatos[i].posicao_y, ((gatos[i].posicao_x) + 1), matriz_mapa, rato_vidas, placar, osso);

            if(check_colisao == 0)
            {
                // verifica se existe um queijo ou osso a frente do gato para nao apagar ele
                if(matriz_mapa[((gatos[i].posicao_x) + 1)][(gatos[i].posicao_y)] == 'Q'
                        || matriz_mapa[((gatos[i].posicao_x) + 1)][(gatos[i].posicao_y)] == 'O')
                {
                    // se for igual a Q ou O guarda o caractere na posicao para repor depois
                    auxiliar = matriz_mapa[((gatos[i].posicao_x) + 1)][(gatos[i].posicao_y)];
                }
                else
                {
                    auxiliar = ' ';
                }
                // atualiza a posicao do gato
                gatos[i].posicao_x = (gatos[i].posicao_x) + 1; // altera a posicao do gato especifico
                matriz_mapa[((gatos[i].posicao_x) - 1)][(gatos[i].posicao_y)] = auxiliar; // atualiza a antiga posicao
                matriz_mapa[(gatos[i].posicao_x)][(gatos[i].posicao_y)] = 'G'; // coloca a nova posicao

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // coloca a cor no caractere

                // Verifica se auxiliar eh igual a Q e substitui por ponto
                if(auxiliar == 'Q')
                    auxiliar = '.';

                // altera visualmente a posicao do gato na tela
                move_xy((gatos[i].posicao_x) - 1, gatos[i].posicao_y); // pega a antiga posicao visual do gato
                printf("%c", auxiliar); // atualiza espaco na tela

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // coloca a cor no caractere

                move_xy(gatos[i].posicao_x, gatos[i].posicao_y); // pega a posicao visual atual do gato
                printf("G"); // coloca G na tela
            }
            break;
        // mmove para esquerda
        case 3:
            // verifica se houve colisao
            check_colisao = colisao_gato(((gatos[i].posicao_y) - 1), gatos[i].posicao_x, matriz_mapa, rato_vidas, placar, osso);

            // se nao houver colisao move o gato
            if(check_colisao == 0)
            {
                // verifica se existe um queijo ou osso a frente do gato para nao apagar ele
                if(matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) - 1)] == 'Q'
                        || matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) - 1)] == 'O')
                {
                    // se for Q ou O guarda o caractere para repor depois
                    auxiliar = matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) - 1)];
                }
                else
                {
                    auxiliar = ' ';
                }

                // atualiza a posicao do gato
                gatos[i].posicao_y = (gatos[i].posicao_y) - 1; // altera a posicao do gato especifico
                matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) + 1)] = auxiliar; // atualiza a antiga posicao
                matriz_mapa[(gatos[i].posicao_x)][(gatos[i].posicao_y)] = 'G'; // coloca a nova posicao

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // coloca a cor no caractere

                // Verifica se auxiliar eh igual a Q e substitui por ponto
                if(auxiliar == 'Q')
                    auxiliar = '.';

                // altera visualmente a posicao do gato na tela
                move_xy(gatos[i].posicao_x, (gatos[i].posicao_y) + 1); // pega a antiga posicao visual do gato
                printf("%c", auxiliar); // atualiza espaco na tela

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // coloca a cor no caractere

                move_xy(gatos[i].posicao_x, gatos[i].posicao_y); // pega a posicao visual atual do gato
                printf("G"); // coloca G na tela
            }
            break;
        // move para direita
        case 4:
            // verifica se houve colisao
            check_colisao = colisao_gato((gatos[i].posicao_y) + 1, gatos[i].posicao_x, matriz_mapa, rato_vidas, placar, osso);

            // se nao houver colisao move o gato
            if(check_colisao == 0)
            {
                // verifica se existe um queijo ou osso a frente do gato para nao apagar ele
                if (matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) + 1)] == 'Q'
                        || matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) + 1)] == 'O')
                {
                    // se for Q ou O guarda o caractere para repor depois
                    auxiliar = matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) + 1)];
                }
                else
                {
                    auxiliar = ' ';
                }
                // atualiza a posicao do gato
                gatos[i].posicao_y = (gatos[i].posicao_y) + 1; // altera a posicao do gato especifico
                matriz_mapa[(gatos[i].posicao_x)][((gatos[i].posicao_y) - 1)] = auxiliar; // atualiza a antiga posicao
                matriz_mapa[(gatos[i].posicao_x)][(gatos[i].posicao_y)] = 'G'; // coloca a nova posicao

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // coloca a cor no caractere

                // Verifica se auxiliar eh igual a Q e substitui por ponto
                if(auxiliar == 'Q')
                    auxiliar = '.';

                // altera visualmente a posicao do gato na tela
                move_xy(gatos[i].posicao_x, (gatos[i].posicao_y) - 1); // pega a antiga posicao visual do gato
                printf("%c", auxiliar); // atualiza espaco na tela

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // coloca a cor no caractere

                move_xy(gatos[i].posicao_x, gatos[i].posicao_y); // pega a posicao visual atual do gato
                printf("G"); // coloca G na tela
            }
            break;
        }
    }
}

// funcao para verificar se houve colisao
int colisao(int posicao_rato_y, int posicao_rato_x, char matriz_mapa[LIN][COL], int *placar, int *osso)
{
    // variaveis
    int colisao = 0; // retorno para saber se houve colisao

    // verifica o caractere no mapa e indica colisao se houver
    if(matriz_mapa[posicao_rato_x][posicao_rato_y] == 'X' || matriz_mapa[posicao_rato_x][posicao_rato_y] == 'T' || matriz_mapa[posicao_rato_x][posicao_rato_y] == 'G')
        colisao = 1;

    // atualiza a contagem de pontos
    if(matriz_mapa[posicao_rato_x][posicao_rato_y] == 'Q')
        *placar = *placar + 10; // altera os pontos direto no main

    if(matriz_mapa[posicao_rato_x][posicao_rato_y] == 'O')
        *osso = 120; // Altera o estado do rato para invulneravel

    return colisao;
}

// funcao para verificar se houve colisao do gato com alguma coisa
int colisao_gato(int posicao_gato_y, int posicao_gato_x, char matriz_mapa[LIN][COL], int *rato_vidas, int *placar, int *osso)
{
    // variaveis locais
    int colisao = 0; // retorno para saber se houve colisao

    // verifica o caractere no mapa e indica se  houve colisao
    if(matriz_mapa[posicao_gato_x][posicao_gato_y] == 'X' || matriz_mapa[posicao_gato_x][posicao_gato_y] == 'T' || matriz_mapa[posicao_gato_x][posicao_gato_y] == 'G')
        colisao = 1;

    // verifica se colidiu com o rato para descontar uma vida
    if(matriz_mapa[posicao_gato_x][posicao_gato_y] == 'M')
    {
        if(*osso > 0)
        {
            *placar = *placar + 100;
        }
        else
        {
            *rato_vidas = *rato_vidas - 1;
        }
    }
    return colisao;
}

// funcao responsavel por mover caracteres na tela
void move_xy(int move_y, int move_x)
{
    COORD coordenada;
    coordenada.X = move_x;
    coordenada.Y = move_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);
}

// funcao para mudar as portas de lugar no mapa
void muda_portas(char matriz_mapa[LIN][COL], PORTA porta[], char *teclado)
{
    // variaveis locais
    int cont; // contador
    int auxiliar = 176; // caractere usado como porta na tabela ascii

    // altera cor das portas para nao ficarem brancas
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

    // altera as portas de posicao em laco
    for(cont = 0; cont < 7; cont++)
    {
        // limpa a posicao da porta na tela e na matriz
        move_xy(porta[cont].posicao_x, porta[cont].posicao_y); // posiciona cursor
        printf(" "); // printf espaco em branco
        matriz_mapa[(porta[cont].posicao_x)][(porta[cont].posicao_y)] = ' '; // limpa matriz

        // verifica estado da porta para saber se abre ou fecha
        if(porta[cont].estado == 1)
        {
            porta[cont].posicao_x = porta[cont].posicao_x + 1;
            porta[cont].posicao_y = porta[cont].posicao_y + 1;
            porta[cont].estado = 0;
        }
        else
        {
            porta[cont].posicao_x = porta[cont].posicao_x - 1;
            porta[cont].posicao_y = porta[cont].posicao_y - 1;
            porta[cont].estado = 1;
        }
        // atualiza a posicao da porta na tela e na matriz
        move_xy(porta[cont].posicao_x, porta[cont].posicao_y); // posiciona cursor
        printf("%c", auxiliar); // printf do caractere da porta
        matriz_mapa[(porta[cont].posicao_x)][(porta[cont].posicao_y)] = 'T'; // atualiza matriz
    }
    *teclado = ' '; // limpa o le teclado da funcao main para nao ficar repetindo
    // a letra 'b' infinitamente
}

// funcao que gera um numero aleatorio entre minimo e maximo
int gera_numero_aleatorio(int minimo, int maximo)
{
    return rand() % (maximo - minimo + 1) + minimo;
}

// funcao que mostra o menu inicial do jogo
int menu()
{
    // variaveis locais
    int escolha = 0;
    // coloca a cor nos caracteres1
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    // Enquanto nao for uma opcao valida continua pedindo uma opcao
    while(escolha != 1 && escolha != 2 && escolha != 3)
    {
        move_xy(1, 6);
        printf("-------------------------------");
        move_xy(2, 6);
        printf("|                             |");
        move_xy(3, 6);
        printf("|        MOUSE    TRAP        |");
        move_xy(4, 6);
        printf("|                             |");
        move_xy(5, 6);
        printf("-------------------------------");

        move_xy(7, 14);
        printf("1. Novo Jogo");
        move_xy(9, 14);
        printf("2. Leaderboard");
        move_xy(11, 14);
        printf("3. Sair");
        printf("\n");

        scanf("%d", &escolha);
    }
    return escolha;
}

// funcao que mostra o scoreboard na tela (opcao 2 do menu)
void mostra_leaderboard()
{
    // variaveis locais
    FILE *ponteiro_arquivo; // ponteiro para abrir o arquivo
    JOGADOR jogador[4]; // guarda os dados de jogador
    int i = 0; // contador

    // guarda endereco do arquivo a ser aberto
    ponteiro_arquivo = fopen("leaderboard/leaderboard_table.bin", "rb");

    // se ponteiro pro arquivo estiver ok printa as melhores pontuacoes
    if(ponteiro_arquivo)
    {
        // cabecalho
        printf("==== LEADERBOARD ====\n\n");
        printf("JOGADOR       PONTOS\n");

        // enquanto nao for final do arquivo printa as melhores pontuacoes
        for(i = 0; i < 4; i++)
        {
            // teste se leu com exito e printa caso sim
            if(fread(&jogador[i], sizeof(JOGADOR), 1, ponteiro_arquivo))
            {
                // print dos dados lidos
                printf("%-13s %d\n", jogador[i].nome, jogador[i].pontos);
            }
        }
    }
    else
    {
        printf("AINDA NAO HA MELHORES PONTUACOES.");
    }
    // mensagem para sair da tela
    printf("\n\nPressione qualquer tecla para sair.\n\n");

    // fecha o arquivo
    fclose(ponteiro_arquivo);
}

// funcao que cria/atualiza o arquivo texto com as 5 melhores pontuacoes
void atualiza_leaderboard(int pontuacao)
{
    // variaveis locais
    FILE *ponteiro_arquivo; // ponteiro para abrir o arquivo
    JOGADOR jogador; // Guarda os dados do jogador para gravar no arquivo
    JOGADOR compara_jog[4]; // Guarda os jogadores que ja existem no arquivo para comparacao de pontuacao
    int cont = 0; // contador para while
    int achou = 0; // flag para while. Indica que jogador entra para leaderboard

    // guarda o endereco do arquivo a ser criado/atualizado*/
    ponteiro_arquivo = fopen("leaderboard/leaderboard_table.bin", "a+b");

    // se tudo certo com arquivo, opera. senao informa o erro
    if(ponteiro_arquivo)
    {
        // limpa a tela
        system("cls");

        // verifica se atual pontuacao eh maior que a pontuacao dos demais jogadores do leaderboard
        while(cont < 4 && achou != 1)
        {
            // verifica se houve retorno correto na leitura do arquivo(se encontrou jogador)
            if(fread(&compara_jog[cont], sizeof(JOGADOR), 1, ponteiro_arquivo))
            {
                // compara as pontuacoes. grava se for maior
                if(pontuacao > compara_jog[cont].pontos)
                {
                    // se for maior grava a nova pontuacao no arquivo
                    // prepara as variaveis
                    setbuf(stdin, NULL);
                    printf("Informe seu nome: ");
                    scanf("%s", &jogador.nome);
                    jogador.pontos = pontuacao;
                    // prepara o ponteiro e grava no arquivo
                    fseek(ponteiro_arquivo, - sizeof(JOGADOR), SEEK_CUR);
                    fwrite(&jogador, sizeof(JOGADOR), 1, ponteiro_arquivo);
                    // ativa flag para sair do while
                    achou = 1;
                }
            }
            // se deu erro na leitura o ponteiro ja vai estar posicionado
            // e entao faz a insercao na posicao
            else {
                printf("Informe seu nome: ");
                scanf("%s", &jogador.nome);
                jogador.pontos = pontuacao;
                // grava no arquivo
                fwrite(&jogador, sizeof(JOGADOR), 1, ponteiro_arquivo);
                // ativa a flag
                achou = 1;
            }
            // incrementa contador
            cont++;
        }
    }
    // se nao conseguir abrir/criar arquivo informa o erro
    else
    {
        // limpa a tela e informa o erro
        system("cls");
        printf("Erro: falha na criacao/atualizacao do arquivo leaderboard.txt");
    }
    // fecha o arquivo
    fclose(ponteiro_arquivo);
}

// print na tela do tempo do modo cachorro se estiver ativo
int print_osso(int osso)
{
    // verifica se osso ainda esta ativo
    if(osso > 0)
    {
        // ajusta cursor e printa na tela
        move_xy(12,19);
        printf("MODO CACHORRO ATIVADO");
        osso--; // decrementa osso para a proxima chamada da funcao
    }
    return osso;
}

// funcao principal do sistema
int main()
{
    PORTA portas[7]; // portas presentes no jogo, que sao 7
    GATOS gatos[4]; // gatos presentes no jogo, que sao 4

    char matriz_mapa[LIN][COL]; // matriz que sera o mapa do jogo
    char matriz_bonita[LIN][COL]; // matriz para efeitos especiais
    char le_teclado = ' '; // valor que sera lido do teclado. WASD e/ou seta

    int posicao_rato_x; // linha atual do rato
    int posicao_rato_y; // coluna atual do rato
    int antiga_rato_x = posicao_rato_x; // antiga linha onde estava o rato
    int antiga_rato_y = posicao_rato_y; // antiga coluna onde estava o rato

    int num_vidas = 3; // numero de vidas que o jogador possui
    int placar = 0; // autoexplicativo
    int escolha = 0; // numero do menu
    int osso = 0; // variavel que transforma o player em invulneravel

    // while externo que mantem o jogo rodando a todo custo
    while (escolha != 3)
    {
        // chama a funcao menu
        escolha = menu();
        // De acordo com a opcao selecionada...
        placar = 0;
        switch(escolha)
        {
        // NOVO JOGO -> inicia o nivel do jogo
        case 1:
        {
            system("cls"); // limpa a tela para colocar o nivel do jogo
            cria_matriz_mapa(matriz_mapa, matriz_bonita); // chama a funcao que cria a matriz do mapa

            acha_rato(matriz_mapa, &posicao_rato_x, &posicao_rato_y); // procura a posicao inicial do rato
            acha_portas(matriz_mapa, portas); // procura a posicao das portas na matriz_mapa e salva
            acha_gatos(matriz_mapa, gatos); // procura as posicoes dos gatos na matriz_mapa

            print_mapa(matriz_bonita); // print do mapa na tela
            // Enquanto houverem vidas continua rodando o nivel
            while(num_vidas != 0)
            {
                // se teclado foi acionado, salva o que foi digitado
                if(_kbhit())
                {
                    le_teclado = _getch(); // salva o que foi digitado
                }
                // verifica se o jogador pressionou b/B para mudar a orientacao das portas
                if(le_teclado == 'b' || le_teclado == 'B')
                {
                    muda_portas(matriz_mapa, portas, &le_teclado);
                }
                // salva a posicao antiga do rato para deixar um espaco
                // em branco por onde ele passou
                // quando ele come o queijo
                antiga_rato_x = posicao_rato_x;
                antiga_rato_y = posicao_rato_y;

                // atualiza as coordenadas do rato nas variaveis abaixo
                move_rato(&le_teclado, &posicao_rato_x, &posicao_rato_y, matriz_mapa, &placar, &osso);
                // pega a posicao antiga do rato na tela
                move_xy(antiga_rato_x, antiga_rato_y);
                // coloca um espaco em branco quando ele sair de cima
                printf(" ");
                // pega a nova posicao do rato
                move_xy(posicao_rato_x, posicao_rato_y);
                // printa o M na nova posicao
                printf("M");

                // print do titulo do jogo in game para ficar bonito
                move_xy(0, 30);
                printf("=================");
                move_xy(1, 30);
                printf("=               =");
                move_xy(2, 30);
                printf("=  MOUSE  TRAP  =");
                move_xy(3, 30);
                printf("=               =");
                move_xy(4, 30);
                printf("=================");
                move_xy(5, 30);
                printf("=               =");

                // seleciona o local do contador de vidas
                move_xy(6, 30);
                // print na tela das vidas atualizadas
                printf("=   Vidas:  %d   =", num_vidas);
                move_xy(7, 30);
                printf("=================");
                move_xy(8, 30);
                printf("=               =");
                // seleciona o local do placar
                move_xy(9,30);
                // print na tela da pontuacao atualizada
                printf("= Placar: %5d =", placar);
                move_xy(10, 30);
                printf("=================");

                // função que printa o aviso para o player
                print_osso(osso);

                if (osso < 0) // apaga o print do modo cachorro ativado da tela
                {
                    move_xy(12,19);
                    printf("                                         ");
                }

                // funcao para movimentar os gatos
                move_gato(gatos, matriz_mapa, &num_vidas, &placar, &osso);

                // decrementa o osso para contar os 6 segundos
                osso--;

                // sleep para nao ficar super rapido
                Sleep(50);
            }
            // restaura as vidas
            num_vidas = 3;

            // Limpa a tela
            system("cls");

            // Limpa a variavel escolha
            escolha = 0;

            // Mensagem informando que morreu
            move_xy(5, 6);
            printf("GAME OVER");
            Sleep(2000);

            // chama a funcao que atualiza o scoreboard
            atualiza_leaderboard(placar);

            // Limpa a tela novamente
            system("cls");
            break;
        }
        // LEADERBOARD -> Placar das melhores pontuacoes no jogo
        case 2:
            // limpa a tela
            system("cls");

            // abre arquivo do tipo texto com as pontuacoes
            mostra_leaderboard();

            // espera o usuario teclar para sair
            _getch();
            // Limpa a tela
            system("cls");
            // Limpa a variavel escolha
            escolha = 0;
            break;
        // SAIR -> Encerra o jogo
        case 3:
            system("cls");
            move_xy(5, 18);
            printf("Ate a proxima!\n");
            break;
        }
    }
    return 0;
}
