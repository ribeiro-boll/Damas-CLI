#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define WHITE "\033[37m"

// --- Constantes do Jogo ---
#define VAZIO ' '
#define PRETO 'p'
#define BRANCO 'b'

// --- Identificadores de Jogador ---
#define jogador_branco 0
#define jogador_preto 1

// --- Status da Peça (não utilizado no código atual) ---
#define morto 0
#define vivo 1

// --- Variáveis Globais ---
int contador_pecas_b = 0;
int contador_pecas_p = 0;
int jogador_atual = jogador_branco;

// --- Tabuleiro Inicial de Teste ---
char grid[8][8] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', 'b', ' ', ' ', ' ', 'b', ' ', ' '},
    {'p', ' ', ' ', ' ', ' ', ' ', 'p', ' '},
    {' ', 'b', ' ', ' ', ' ', 'b', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'b', ' ', 'b', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ' , ' ', ' ', ' '}
};

/*
void resetar_grid(char arr[8][8]) {
    contador_pecas_b = 0;
    contador_pecas_p = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3) {
                    arr[i][j] = 'b';
                    contador_pecas_b++;
                } else if (i > 4) {
                    arr[i][j] = 'p';
                    contador_pecas_p++;
                } else {
                    arr[i][j] = ' ';
                }
            } else {
                arr[i][j] = ' ';
            }
        }
    }
    return;
}
*/

/*
// fazer função para testar as structs criadas
void printar_structs_branco_e_preto(Pecas_jogador *branco, Pecas_jogador *preto) {
    printf("\n\n");
    for (int i = 0; i < contador_pecas_b; i++) {
        if (i % 4 == 0 && i != 0) {
            printf(" |\n");
        }
        printf(" | (%d,%d) - (%c,%d)", branco[i].coordenada_x, branco[i].coordenada_y, branco[i].coordenada_x + 'A', branco[i].coordenada_y + 1);
    }
    printf(" |\n");
    printf("\n\n");
    for (int i = 0; i < contador_pecas_p; i++) {
        if (i % 4 == 0 && i != 0) {
            printf(" |\n");
        }
        printf(" | (%d,%d) - (%c,%d)", preto[i].coordenada_x, preto[i].coordenada_y, preto[i].coordenada_x + 'A', preto[i].coordenada_y + 1);
    }
    printf(" |\n\n");
    return;
}
*/

void print_grid(char arr[8][8], int pontos_branco, int pontos_preto) {
    system("clear");
    int contador = 1;
    printf("  A B C D E F G H\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("|%c", arr[i][j]);
        }
        printf("| %d\n", contador++);
    }
    printf("\nPontos jogador branco: %d\nPontos jogador preto: %d\n\n", pontos_branco, pontos_preto);
    return;
}

void verificar_captura_mais_pecas(char grid[8][8], int jogador, int coordenada_peca[2], int *pontos_preto, int *pontos_branco) {
    int x = coordenada_peca[0];
    int y = coordenada_peca[1];
    int capturas_possiveis = 0;
    char peca_jogador;
    char peca_adversario;

    if (jogador == jogador_preto) {
        peca_jogador = 'p';
        peca_adversario = 'b';
    } else {
        // Lógica incorreta aqui: deveria ser 'b' e 'p' para o jogador branco
        peca_jogador = 'p';
        peca_adversario = 'b';
    }

    if (grid[y][x] != peca_jogador) {
        return;
    }

    print_grid(grid, *pontos_branco, *pontos_preto);
    printf("\nVerificando mais capturas para a peça em (%c, %d):\n", x + 'A', y + 1);

    // Lógica de verificação de captura (com printf incorreto)
    if (jogador == jogador_branco) {
        if (x - 2 >= 0 && y + 2 < 8 && grid[y + 1][x - 1] == peca_adversario && grid[y + 2][x - 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x - 2) + 'A', (y + 2) + 1);
        }
        if (x + 2 < 8 && y + 2 < 8 && grid[y + 1][x + 1] == peca_adversario && grid[y + 2][x + 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x + 2) + 'A', (y + 2) + 1);
        }
        if (x - 2 >= 0 && y - 2 >= 0 && grid[y - 1][x - 1] == peca_adversario && grid[y - 2][x - 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x - 2) + 'A', (y - 2) + 1);
        }
        if (x + 2 < 8 && y - 2 >= 0 && grid[y - 1][x + 1] == peca_adversario && grid[y - 2][x + 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x + 2) + 'A', (y - 2) + 1);
        }
    }

    if (jogador == jogador_preto) {
        if (x - 2 >= 0 && y - 2 >= 0 && grid[y - 1][x - 1] == peca_adversario && grid[y - 2][x - 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x - 2) + 'A', (y - 2) + 1);
        }
        if (x + 2 < 8 && y - 2 >= 0 && grid[y - 1][x + 1] == peca_adversario && grid[y - 2][x + 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x + 2) + 'A', (y - 2) + 1);
        }
        if (x - 2 >= 0 && y + 2 < 8 && grid[y + 1][x - 1] == peca_adversario && grid[y + 2][x - 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x - 2) + 'A', (y + 2) + 1);
        }
        if (x + 2 < 8 && y + 2 < 8 && grid[y + 1][x + 1] == peca_adversario && grid[y + 2][x + 2] == ' ') {
            capturas_possiveis++;
            printf("%d) Captura possível para (%c, %d)\n", capturas_possiveis, (x + 2) + 'A', (y + 2) + 1);
        }
    }

    if (capturas_possiveis >= 1) {
        printf("\n\nDigite a coordenada do proximo movimento: ");
        char letra;
        char *jogadores_str[2] = {"Jogador Branco", "Jogador Preto"};
        int coordenada_y = -1;
        int coordenada_x = -1;
        int characteres_digitados = 0;
        int cond_comeu_peca = 0;
        
        print_grid(grid, *pontos_branco, *pontos_preto);
        
        while (1) {
            characteres_digitados = 0;
            printf("\n%s, capture novamente com a peça em (%c, %d): ", jogadores_str[jogador], coordenada_peca[0] + 'A', coordenada_peca[1] + 1);
            
            while ((letra = getchar()) != '\n') {
                characteres_digitados++;
                if (characteres_digitados == 1) {
                    coordenada_x = toupper(letra) - 'A';
                }
                if (characteres_digitados == 2) {
                    coordenada_y = letra - '1';
                }
            }

            if (characteres_digitados > 2) {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite apenas duas coordenadas!\n");
                continue;
            } else if (coordenada_y >= 8 || coordenada_y < 0) {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite uma coordenada dentro dos limites!\n");
                continue;
            } else if (coordenada_x >= 8 || coordenada_x < 0) {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite uma coordenada dentro dos limites!\n");
                continue;
            }
            // Lógica de captura (com bugs na remoção da peça)
            else if (jogador == jogador_branco && grid[coordenada_y][coordenada_x] == ' ') {
                 if ((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) && grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' '; // Peça capturada
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    cond_comeu_peca = 1;
                    break;
                }
                 // ... outras verificações de captura para o branco
            } else if (jogador == jogador_preto && grid[coordenada_y][coordenada_x] == ' ') {
                if ((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) && grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' '; // Peça capturada
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    cond_comeu_peca = 1;
                    break;
                }
                // ... outras verificações de captura para o preto
            } else {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite apenas coordenadas válidas para captura!\n");
                continue;
            }
        }
        
        if (cond_comeu_peca) {
            int arr_nova_coordenada[2] = {coordenada_x, coordenada_y};
            verificar_captura_mais_pecas(grid, jogador, arr_nova_coordenada, pontos_branco, pontos_preto);
        }
    }
    return;
}

void mover_peca_normal(char grid[8][8], int coordenada_peca[2], int jogador, int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Jogador Branco", "Jogador Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    int cond_comeu_peca = 0;
    
    print_grid(grid, *pontos_branco, *pontos_preto);
    
    while (1) {
        characteres_digitados = 0;
        printf("\nPara onde %s deseja mover a peça de (%c, %d)? ", jogadores_str[jogador], coordenada_peca[0] + 'A', coordenada_peca[1] + 1);
        
        while ((letra = getchar()) != '\n') {
            characteres_digitados++;
            if (characteres_digitados == 1) {
                coordenada_x = toupper(letra) - 'A';
            }
            if (characteres_digitados == 2) {
                coordenada_y = letra - '1';
            }
        }

        if (characteres_digitados > 2) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Digite apenas duas coordenadas (ex: A3).\n");
            continue;
        } else if (coordenada_y >= 8 || coordenada_y < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Coordenada da linha fora do tabuleiro.\n");
            continue;
        } else if (coordenada_x >= 8 || coordenada_x < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Coordenada da coluna fora do tabuleiro.\n");
            continue;
        }
        // --- Movimento Simples ---
        else if (jogador == jogador_branco && grid[coordenada_y][coordenada_x] == ' ' &&
            ((coordenada_peca[0] + 1 == coordenada_x && coordenada_peca[1] + 1 == coordenada_y) ||
             (coordenada_peca[0] - 1 == coordenada_x && coordenada_peca[1] + 1 == coordenada_y))) {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'b';
            break;
        } else if (jogador == jogador_preto && grid[coordenada_y][coordenada_x] == ' ' &&
            ((coordenada_peca[0] + 1 == coordenada_x && coordenada_peca[1] - 1 == coordenada_y) ||
             (coordenada_peca[0] - 1 == coordenada_x && coordenada_peca[1] - 1 == coordenada_y))) {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'p';
            break;
        }
        // --- Lógica de Captura (com bugs na remoção da peça) ---
        else if (jogador == jogador_branco && grid[coordenada_y][coordenada_x] == ' ') {
            if ((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) && grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'p') {
                (*pontos_branco)++;
                grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'b';
                cond_comeu_peca = 1;
                break;
            } // ... outras condições de captura do branco
        } 
        else if (jogador == jogador_preto && grid[coordenada_y][coordenada_x] == ' ') {
            if ((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) && grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] == 'b') {
                (*pontos_preto)++;
                grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'p';
                cond_comeu_peca = 1;
                break;
            } // ... outras condições de captura do preto
        } 
        else {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Movimento inválido para (%c, %d).\n", coordenada_x + 'A', coordenada_y + 1);
            continue;
        }
    }

    if (cond_comeu_peca) {
        int arr_nova_coordenada[2] = {coordenada_x, coordenada_y};
        verificar_captura_mais_pecas(grid, jogador, arr_nova_coordenada, pontos_branco, pontos_preto);
    }
    return;
}

void selecionar_peca(int arr[2], char grid[8][8], int jogador, int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Jogador Branco", "Jogador Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    
    while (1) {
        characteres_digitados = 0;
        printf("Vez do %s.\nDigite a coordenada da peça (ex: B2): ", jogadores_str[jogador]);
        
        while ((letra = getchar()) != '\n') {
            characteres_digitados++;
            if (characteres_digitados == 1) {
                coordenada_x = toupper(letra) - 'A';
            }
            if (characteres_digitados == 2) {
                coordenada_y = letra - '1';
            }
        }

        if (characteres_digitados > 2 || characteres_digitados < 2) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Digite apenas duas coordenadas (coluna e linha).\n");
            continue;
        }
        else if (coordenada_y >= 8 || coordenada_y < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Coordenada da linha fora do tabuleiro.\n");
            continue;
        } 
        else if (coordenada_x >= 8 || coordenada_x < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Coordenada da coluna fora do tabuleiro.\n");
            continue;
        } 
        else if (grid[coordenada_y][coordenada_x] == 'b' && jogador == jogador_branco) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            mover_peca_normal(grid, arr, jogador, pontos_branco, pontos_preto);
            break;
        } 
        else if (grid[coordenada_y][coordenada_x] == 'p' && jogador == jogador_preto) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            mover_peca_normal(grid, arr, jogador, pontos_branco, pontos_preto);
            break;
        } 
        else if (grid[coordenada_y][coordenada_x] == 'B' && jogador == jogador_branco) {
            // Lógica para Dama Branca (não implementada)
        } 
        else if (grid[coordenada_y][coordenada_x] == 'P' && jogador == jogador_preto) {
            // Lógica para Dama Preta (não implementada)
        } 
        else {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nErro: Selecione uma peça válida da sua cor.\n");
            continue;
        }
    }
    return;
}

int main() {
    while (1) {
        int pontos_preto = 0;
        int pontos_branco = 0;
        char resposta;
        int coordenada_peca[2];
        jogador_atual = jogador_preto; // Reinicia para o jogador branco
        
        // resetar_grid(grid); // Se quiser usar um tabuleiro padrão no início

        while (pontos_branco < 12 && pontos_preto < 12) {
            print_grid(grid, pontos_branco, pontos_preto);
            selecionar_peca(coordenada_peca, grid, jogador_atual, &pontos_branco, &pontos_preto);
            
            // Alterna o jogador
            jogador_atual++;
            jogador_atual %= 2;
        }

        system("clear");
        printf("\n\n--- FIM DE JOGO ---\n\n");
        if (pontos_branco == 12) {
            printf("Parabéns, Jogador Branco, você ganhou!!!\n");
        } else if (pontos_preto == 12) {
            printf("Parabéns, Jogador Preto, você ganhou!!!\n");
        }

        printf("\nDeseja jogar novamente (S/N)? ");
        resposta = getchar();
        // Limpa o buffer de entrada para a próxima leitura
        while (getchar() != '\n'); 

        if (toupper(resposta) == 'N') {
            printf("\nObrigado por jogar!\n\n");
            break;
        }
        // Se a resposta não for 'N', o loop principal continua e o jogo recomeça
    }
    return 0;
}
//b3 - c4
//e6 - d5
//c4 - e6