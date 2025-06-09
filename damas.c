#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WHITE "\033[37m"

#define VAZIO ' '
#define PRETO 'p'
#define BRANCO 'b'

#define jogador_branco 0
#define jogador_preto 1

#define morto 0
#define vivo 1

int contador_pecas_b = 0;
int contador_pecas_p = 0;

int jogador_atual = jogador_branco;

char grid[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', 'b', ' ', ' ', ' ', 'b', ' ', ' '},
                   {'b', ' ', ' ', ' ', ' ', ' ', 'p', ' '},
                   {' ', 'p', ' ', ' ', ' ', 'b', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', ' ', 'p', ' ', 'p', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
int quick_verificar(char grid[8][8], int jogador, int peca_selecionada[2]) {
    int x = peca_selecionada[0];
    int y = peca_selecionada[1];
    int capturas_possiveis = 0;

    char peca_jogador = (jogador == jogador_branco) ? 'b' : 'p';
    char peca_adversario = (jogador == jogador_branco) ? 'p' : 'b';

    if (grid[y][x] != peca_jogador) {
        return 0;
    }

    if (jogador == jogador_branco) {
        if (x - 2 >= 0 && y + 2 < 8) {
            if (grid[y + 1][x - 1] == peca_adversario &&
                grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (grid[y + 1][x + 1] == peca_adversario &&
                grid[y + 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }

        if (x - 2 >= 0 && y - 2 >= 0) {
            if (grid[y - 1][x - 1] == peca_adversario &&
                grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (grid[y - 1][x + 1] == peca_adversario &&
                grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
    }

    if (jogador == jogador_preto) {
        if (x - 2 >= 0 && y + 2 < 8) {
            if (grid[y + 1][x - 1] == peca_adversario &&
                grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (grid[y + 1][x + 1] == peca_adversario &&
                grid[y + 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x - 2 >= 0 && y - 2 >= 0) {
            if (grid[y - 1][x - 1] == peca_adversario &&
                grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (grid[y - 1][x + 1] == peca_adversario &&
                grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
    }

    return capturas_possiveis;
}


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



void print_grid(char arr[8][8], int pontos_branco, int pontos_preto) {
    system("clear");
    int contador = 1;
    printf(" A B C D E F G H\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("|%c", arr[i][j]);
        }
        printf("| %d\n", contador++);
    }
    printf("\nPontos jogador branco: %d\nPontos jogador preto: %d\n\n",
           pontos_branco, pontos_preto);
    return;
}

void verificar_captura_mais_pecas(char grid[8][8], int jogador,int coordenada_peca[2], int *pontos_preto,int *pontos_branco) {
    int x = coordenada_peca[0];
    int y = coordenada_peca[1];
    int coordenada_y = -1;
    int coordenada_x = -1;
    int capturas_possiveis = 0;
    char peca_jogador;
    char peca_adversario;
    int cond_comeu_peca = 0;
    print_grid(grid, *pontos_branco, *pontos_preto);
    if (jogador == jogador_branco) {
        if (x - 2 >= 0 && y + 2 < 8) {
            if (grid[y + 1][x - 1] == 'p' && grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (grid[y + 1][x + 1] == 'p' && grid[y + 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x - 2 >= 0 && y - 2 >= 0) {
            if (grid[y - 1][x - 1] == 'p' && grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (grid[y - 1][x + 1] == 'p' && grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
    }
    if (jogador == jogador_preto) {
        if (x - 2 >= 0 && y - 2 >= 0) {
            if (grid[y - 1][x - 1] == 'b' && grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (grid[y - 1][x + 1] == 'b' && grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x - 2 >= 0 && y + 2 < 8) {
            if (grid[y + 1][x - 1] == 'b' && grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (grid[y + 1][x + 1] == 'b' && grid[y + 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
    }

    if (capturas_possiveis >= 1) {
        printf("\n\nDigite a coordenada do proximo movimento: ");
        char letra;
        char *jogadores_str[2] = {"Jogador Branco", "Jogador Preto"};

        int characteres_digitados = 0;

        printf("\n");
        print_grid(grid, *pontos_branco, *pontos_preto);
        while (1) {
            capturas_possiveis = 0;
            if (jogador == jogador_branco) {
                if (x - 2 >= 0 && y + 2 < 8) {
                    if (grid[y + 1][x - 1] == 'p' &&
                        grid[y + 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x - 2) + 'A', (y + 2) + 1);
                    }
                }

                if (x + 2 < 8 && y + 2 < 8) {
                    if (grid[y + 1][x + 1] == 'p' &&
                        grid[y + 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x + 2) + 'A', (y + 2) + 1);
                    }
                }
                if (x - 2 >= 0 && y - 2 >= 0) {
                    if (grid[y - 1][x - 1] == 'p' &&
                        grid[y - 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x - 2) + 'A', (y - 2) + 1);
                    }
                }
                if (x + 2 < 8 && y - 2 >= 0) {
                    if (grid[y - 1][x + 1] == 'p' &&
                        grid[y - 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x + 2) + 'A', (y - 2) + 1);
                    }
                }
            }
            if (jogador == jogador_preto) {
                if (x - 2 >= 0 && y - 2 >= 0) {
                    if (grid[y - 1][x - 1] == 'b' &&
                        grid[y - 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x - 2) + 'A', (y - 2) + 1);
                    }
                }
                if (x + 2 < 8 && y - 2 >= 0) {
                    if (grid[y - 1][x + 1] == 'b' &&
                        grid[y - 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x + 2) + 'A', (y - 2) + 1);
                    }
                }
                if (x - 2 >= 0 && y + 2 < 8) {
                    if (grid[y + 1][x - 1] == 'b' &&
                        grid[y + 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x - 2) + 'A', (y + 2) + 1);
                    }
                }
                if (x + 2 < 8 && y + 2 < 8) {
                    if (grid[y + 1][x + 1] == 'b' &&
                        grid[y + 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        printf("%d)Captura possivel, na coordenada (%c, %d)\n", capturas_possiveis,
                               (x + 2) + 'A', (y + 2) + 1);
                    }
                }
            }
            characteres_digitados = 0;
            printf("\nDigite a onde o jogador: %s\nDeseja mover a peca de "
                   "coordenada: (%c, %d): ",
                   jogadores_str[jogador], coordenada_peca[0] + 'A',
                   coordenada_peca[1] + 1);
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
            //
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) ||
                      (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y)) &&
                     jogador == jogador_branco &&
                     grid[coordenada_y][coordenada_x] == ' ') {
                if (grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    cond_comeu_peca = 1;
                    break;
                } 
                else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    cond_comeu_peca = 1;
                    break;
                }
                continue;
            } else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y)) &&
                       jogador == jogador_branco &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                        
                if (grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] ==
                    'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    cond_comeu_peca = 1;
                    break;
                } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    cond_comeu_peca = 1;
                    break;
                }
                continue;
            } 
            
            
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y)) &&
                       jogador == jogador_preto &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                if (grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    cond_comeu_peca = 1;
                    break;
                } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    cond_comeu_peca = 1;
                    break;
                }
                continue;
            } 
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y)) &&
                       jogador == jogador_preto &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                if (grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    cond_comeu_peca = 1;
                    break;
                } else if (grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    cond_comeu_peca = 1;
                    break;
                }
                continue;
            }

            else {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite apenas coordenadas validas!\n(%d, %d) -> (%c, "
                       "%d)\n",
                       coordenada_x, coordenada_y, coordenada_x + 'A',
                       coordenada_y + 1);
                continue;
            }
        }
    }
    if (cond_comeu_peca) {
        int arr_nova_coordenada[2] = {coordenada_x, coordenada_y};
        verificar_captura_mais_pecas(grid, jogador, arr_nova_coordenada,
                                     pontos_preto, pontos_branco);
    }

    return;
}

void mover_peca_normal(char grid[8][8], int coordenada_peca[2], int jogador,
                       int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Branco", "Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    int cond_comeu_peca = 0;
    printf("\n");
    print_grid(grid, *pontos_branco, *pontos_preto);
    while (1) {
        characteres_digitados = 0;
        printf("\nJogador %s, digite a onde deseja mover a peca de "
               "coordenada: (%c, %d): ",
               jogadores_str[jogador], coordenada_peca[0] + 'A',
               coordenada_peca[1] + 1);
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

        else if (((coordenada_peca[0] + 1 == coordenada_x &&
                   coordenada_peca[1] + 1 == coordenada_y) ||
                  (coordenada_peca[0] - 1 == coordenada_x &&
                   coordenada_peca[1] + 1 == coordenada_y)) &&
                 jogador == jogador_branco &&
                 grid[coordenada_y][coordenada_x] == ' ') {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'b';
            break;
        } else if (((coordenada_peca[0] + 1 == coordenada_x &&
                     coordenada_peca[1] - 1 == coordenada_y) ||
                    (coordenada_peca[0] - 1 == coordenada_x &&
                     coordenada_peca[1] - 1 == coordenada_y)) &&
                   jogador == jogador_preto &&
                   grid[coordenada_y][coordenada_x] == ' ') {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'p';
            break;
        }
        //
        else if (((coordenada_peca[0] + 2 == coordenada_x &&
                   coordenada_peca[1] + 2 == coordenada_y) ||
                  (coordenada_peca[0] - 2 == coordenada_x &&
                   coordenada_peca[1] + 2 == coordenada_y)) &&
                 jogador == jogador_branco &&
                 grid[coordenada_y][coordenada_x] == ' ') {

            if (grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'p') {
                (*pontos_branco)++;
                grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'b';
                cond_comeu_peca = 1;
                break;
            } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] ==
                       'p') {
                (*pontos_branco)++;
                grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'b';
                cond_comeu_peca = 1;
                break;
            }
            continue;
        } else if (((coordenada_peca[0] + 2 == coordenada_x &&
                     coordenada_peca[1] - 2 == coordenada_y) ||
                    (coordenada_peca[0] - 2 == coordenada_x &&
                     coordenada_peca[1] - 2 == coordenada_y)) &&
                   jogador == jogador_branco &&
                   grid[coordenada_y][coordenada_x] == ' ') {
            if (grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] == 'p') {
                (*pontos_branco)++;
                grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'b';
                cond_comeu_peca = 1;
                break;
            } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] ==
                       'p') {
                (*pontos_branco)++;
                grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'b';
                cond_comeu_peca = 1;
                break;
            }
            continue;
        } else if (((coordenada_peca[0] + 2 == coordenada_x &&
                     coordenada_peca[1] - 2 == coordenada_y) ||
                    (coordenada_peca[0] - 2 == coordenada_x &&
                     coordenada_peca[1] - 2 == coordenada_y)) &&
                   jogador == jogador_preto &&
                   grid[coordenada_y][coordenada_x] == ' ') {
            if (grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] == 'b') {
                (*pontos_preto)++;
                grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'p';
                cond_comeu_peca = 1;
                break;
            } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] ==
                       'b') {
                (*pontos_preto)++;
                grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'p';
                cond_comeu_peca = 1;
                break;
            }
            continue;
        } else if (((coordenada_peca[0] + 2 == coordenada_x &&
                     coordenada_peca[1] + 2 == coordenada_y) ||
                    (coordenada_peca[0] - 2 == coordenada_x &&
                     coordenada_peca[1] + 2 == coordenada_y)) &&
                   jogador == jogador_preto &&
                   grid[coordenada_y][coordenada_x] == ' ') {
            if (grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] == 'b') {
                (*pontos_preto)++;
                grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'p';
                cond_comeu_peca = 1;
                break;
            } else if (grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] ==
                       'b') {
                (*pontos_preto)++;
                grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                grid[coordenada_y][coordenada_x] = 'p';
                cond_comeu_peca = 1;
                break;
            }
            continue;
        }

        else {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf(
                "\nDigite apenas coordenadas validas!\n(%d, %d) -> (%c, %d)\n",
                coordenada_x, coordenada_y, coordenada_x + 'A',
                coordenada_y + 1);
            continue;
        }
    }
    if (cond_comeu_peca) {
        int arr_nova_coordenada[2] = {coordenada_x, coordenada_y};
        verificar_captura_mais_pecas(grid, jogador, arr_nova_coordenada,
                                     pontos_preto, pontos_branco);
    }

    return;
}

void selecionar_peca(int arr[2], char grid[8][8], int jogador,
                     int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Branco", "Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    printf("\n");
    while (1) {
        characteres_digitados = 0;
        printf(
            "Jogador atual: %s\nDigite a coordenada da peca (ex: a2): ",
            jogadores_str[jogador]);
        while ((letra = getchar()) != '\n') {
            characteres_digitados++;
            if (characteres_digitados == 1) {
                coordenada_x = toupper(letra) - 'A';
            }

            if (characteres_digitados == 2) {
                coordenada_y = letra - '1';
            }
        }

        printf("\n\nX: '%c' -> %d\nY: '%d' -> %d      \ngrid: "
               "'%c'\ncharacteres inputados '%d'\n",
               coordenada_x + 'A', coordenada_x, coordenada_y + 1, coordenada_y,
               grid[coordenada_y][coordenada_x], characteres_digitados);
        if (characteres_digitados > 2) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nDigite apenas duas coordenadas!\n");
            continue;
        }

        else if (coordenada_y >= 8 || coordenada_y < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nDigite uma coordenada dentro dos limites!\n");
            continue;
        }

        else if (coordenada_x >= 8 || coordenada_x < 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nDigite uma coordenada dentro dos limites!\n");
            continue;
        }

        else if (grid[coordenada_y][coordenada_x] == 'b' &&
                 jogador == jogador_branco) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            printf("\n\n(%d,%d) -> %c\n", arr[0], arr[1],
                   grid[coordenada_y][coordenada_x]);
            if (quick_verificar(grid, jogador, arr)) {
                verificar_captura_mais_pecas(grid, jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_normal(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }
            break;
        }

        else if (grid[coordenada_y][coordenada_x] == 'p' &&
                 jogador == jogador_preto) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            printf("\n\n(%d,%d) -> %c\n", coordenada_x, coordenada_y,
                   grid[coordenada_y][coordenada_x]);
            if (quick_verificar(grid, jogador, arr)) {
                verificar_captura_mais_pecas(grid, jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_normal(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }
            break;
        }

        else if (grid[coordenada_y][coordenada_x] == 'B' &&
                 jogador == jogador_branco) {
        }

        else if (grid[coordenada_y][coordenada_x] == 'P' &&
                 jogador == jogador_preto) {
        }

        else {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nDigite a coordenada de uma peca correspondente a sua "
                   "cor!\n");
            continue;
        }
    }
    return;
}

int main() {
    while (1) {
        system("clear");
        int pontos_preto;
        int pontos_branco;
        char resposta;
        int coordenada_peca[2];
        resetar_grid(grid);
        int ganhou_jogo = 0;
        pontos_branco = 0;
        pontos_preto = 0;
        while (pontos_branco < 12 && pontos_preto < 12) {
            print_grid(grid, pontos_branco, pontos_preto);
            selecionar_peca(coordenada_peca, grid, jogador_atual,
                            &pontos_branco, &pontos_preto);
            system("clear");
            jogador_atual++;
            jogador_atual %= 2;
        }
        system("clear");
        printf("\n\n\n");
        if (pontos_branco == 12) {
            printf("parabens jogador branco, voce ganhou!!!");
        } else if (pontos_preto == 12) {
            printf("parabens jogador preto, voce ganhou!!!");
        }
        printf("deseja jogar novamente (s/n)? Default: s resposta: ");
        if (toupper(resposta = getchar()) == 'N') {
            printf("\n\nobrigado por jogar!!!");
            break;
        }
    }
    return 0;
}

// b3 - c4
// e6 - d5
// c4 - e6
