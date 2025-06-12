#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



#define branco  "\033[0;36m"
#define preto   "\033[0;31m"

#define jogador_branco 0
#define jogador_preto 1

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

int contador_pecas_b = 0;
int contador_pecas_p = 0;
void mover_peca_dama(char grid[8][8], int coordenada_peca[2], int *jogador,int *pontos_branco, int *pontos_preto);
int verifiar_se_vira_dama(char grid[8][8],int jogador,int cordenada_x,int coordenada_y);
int quick_verificar_dama(char grid[8][8], int jogador, int peca_selecionada[2]);
char grid[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', 'p', ' ', 'p', ' ', ' ', ' '},
                   {' ', ' ', ' ', 'b', ' ', ' ', ' ', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
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


void resetar_grid(char arr[8][8],int modo_debug) {
    if (modo_debug){
        return;
    }
    contador_pecas_b = 0;
    contador_pecas_p = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3) {
                    arr[i][j] = 'p';
                    contador_pecas_b++;
                } else if (i > 4) {
                    arr[i][j] = 'b';
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
    system(CLEAR_SCREEN);
    
    int contador = 1;
    printf("\n\033[0;33m A  B  C  D  E  F  G  H \033[0m \n\n");
    for (int i = 0; i < 8; i++) {
        
        for (int j = 0; j < 8; j++) {
            
            if (arr[i][j] == 'b' || arr[i][j] == 'B') {
                printf("\033[0;36m %c \033[0m", arr[i][j]);  
            }
            else if (arr[i][j] == 'p' || arr[i][j] == 'P') {
                printf("\033[0;31m %c \033[0m", arr[i][j]); 
            }
            else if ((i + j) % 2 == 0){
                printf("\033[47;31m ");
                printf("  \033[0m");
            }
            else {
                printf(" ");
                printf("  ");
            }
        }
        printf("\033[0;33m   %d\033[0m\n", contador++);
    }
    printf("\nPontos jogador branco: %d\nPontos jogador preto: %d\n\n",
           pontos_branco, pontos_preto);
    return;
}
void verificar_captura_mais_pecas_dama(char grid[8][8], int *jogador,int coordenada_peca[2], int *pontos_preto,int *pontos_branco);
void verificar_captura_mais_pecas(char grid[8][8], int jogador,int coordenada_peca[2], int *pontos_preto,int *pontos_branco) {
    int x = coordenada_peca[0];
    int y = coordenada_peca[1];
    int coordenada_y = -1;
    int coordenada_x = -1;
    int capturas_possiveis = 0;
    char peca_preto     = 'p';
    char peca_branco    = 'b';
    int cond_comeu_peca = 0;
    print_grid(grid, *pontos_branco, *pontos_preto);
    if (jogador == jogador_branco) {
        if (x - 2 >= 0 && y + 2 < 8) {
            if (tolower(grid[y + 1][x - 1]) == peca_preto && grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (tolower(grid[y + 1][x + 1]) == peca_preto && grid[y + 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x - 2 >= 0 && y - 2 >= 0) {
            if (tolower(grid[y - 1][x - 1]) == peca_preto && grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (tolower(grid[y - 1][x + 1]) == peca_preto && grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        
    }
    if (jogador == jogador_preto) {
        if (x - 2 >= 0 && y - 2 >= 0) {
            if (tolower(grid[y - 1][x - 1]) == peca_branco && grid[y - 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y - 2 >= 0) {
            if (tolower(grid[y - 1][x + 1]) == peca_branco && grid[y - 2][x + 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x - 2 >= 0 && y + 2 < 8) {
            if (tolower(grid[y + 1][x - 1]) == peca_branco && grid[y + 2][x - 2] == ' ') {
                capturas_possiveis++;
            }
        }
        if (x + 2 < 8 && y + 2 < 8) {
            if (tolower(grid[y + 1][x + 1]) == peca_branco && grid[y + 2][x + 2] == ' ') {
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
                    if (tolower(grid[y + 1][x - 1]) == peca_preto && grid[y + 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }

                if (x + 2 < 8 && y + 2 < 8) {
                    if (tolower(grid[y + 1][x + 1]) == peca_preto && grid[y + 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
                if (x - 2 >= 0 && y - 2 >= 0) {
                    if (tolower(grid[y - 1][x - 1]) == peca_preto && grid[y - 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
                if (x + 2 < 8 && y - 2 >= 0) {
                    if (tolower(grid[y - 1][x + 1]) == peca_preto && grid[y - 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
            }
            if (jogador == jogador_preto) {
                if (x - 2 >= 0 && y - 2 >= 0) {
                    if (tolower(grid[y - 1][x - 1]) == peca_branco && grid[y - 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
                if (x + 2 < 8 && y - 2 >= 0) {
                    if (tolower(grid[y - 1][x + 1]) == peca_branco && grid[y - 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
                if (x - 2 >= 0 && y + 2 < 8) {
                    if (tolower(grid[y + 1][x - 1]) == peca_branco && grid[y + 2][x - 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
                if (x + 2 < 8 && y + 2 < 8) {
                    if (tolower(grid[y + 1][x + 1]) == peca_branco && grid[y + 2][x + 2] == ' ') {
                        capturas_possiveis++;
                        
                               
                    }
                }
            }
            characteres_digitados = 0;
            printf("\nCaptura possivel!\nDigite a onde o jogador: %s\nDeseja mover a peca de "
                   "coordenada: (%c, %d), para capturar uma peca: ",
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
            
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) ||
                      (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y)) &&
                     jogador == jogador_branco &&
                     grid[coordenada_y][coordenada_x] == ' ') {
                if (0){}
                else if (tolower(grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1]) == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                } 
                else if (tolower(grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1]) == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                }
                continue;
            } 
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y)) &&
                       jogador == jogador_branco &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                if (0){}
                else if (tolower(grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1]) ==
                    'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                } else if (tolower(grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1]) == 'p') {
                    (*pontos_branco)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'b';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                }
                continue;
            } 
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] - 2 == coordenada_y)) &&
                       jogador == jogador_preto &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                if (0) {}
                else if (tolower(grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1]) == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                } else if (tolower(grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1]) == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] - 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                }
            }
            else if (((coordenada_peca[0] + 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y) ||
                        (coordenada_peca[0] - 2 == coordenada_x && coordenada_peca[1] + 2 == coordenada_y)) &&
                       jogador == jogador_preto &&
                       grid[coordenada_y][coordenada_x] == ' ') {
                if (0){}
                else if (tolower(grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1]) == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                } else if (tolower(grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1]) == 'b') {
                    (*pontos_preto)++;
                    grid[coordenada_peca[1] + 1][coordenada_peca[0] - 1] = ' ';
                    grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
                    grid[coordenada_y][coordenada_x] = 'p';
                    if (verifiar_se_vira_dama(grid,jogador,coordenada_x,coordenada_y)){
                        cond_comeu_peca=-1;
                    }
                    cond_comeu_peca += 1;
                    break;
                }

                else {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nDigite apenas coordenadas validas!\n");
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
}



void mover_peca_normal(char grid[8][8], int coordenada_peca[2], int *jogador, int *pontos_branco, int *pontos_preto) {
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
               "coordenada: (%c, %d)\nCaso queira escolher outra peca, apenas aperte 'enter' sem caracteres digitados: ",
               jogadores_str[*jogador], coordenada_peca[0] + 'A',
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
        if (characteres_digitados == 0){
            (*jogador)++;
            break;
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
                   coordenada_peca[1] - 1 == coordenada_y) ||
                  (coordenada_peca[0] - 1 == coordenada_x &&
                   coordenada_peca[1] - 1 == coordenada_y)) &&
                 *jogador == jogador_branco &&
                 grid[coordenada_y][coordenada_x] == ' ') {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'b', 
            verifiar_se_vira_dama(grid,*jogador,coordenada_x,coordenada_y);
            break;
        } else if (((coordenada_peca[0] + 1 == coordenada_x &&
                     coordenada_peca[1] + 1 == coordenada_y) ||
                    (coordenada_peca[0] - 1 == coordenada_x &&
                     coordenada_peca[1] + 1 == coordenada_y)) &&
                   *jogador == jogador_preto &&
                   grid[coordenada_y][coordenada_x] == ' ') {
            grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
            grid[coordenada_y][coordenada_x] = 'p';
            verifiar_se_vira_dama(grid,*jogador,coordenada_x,coordenada_y);
            break;
        }
        else {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf(
                "\nDigite apenas coordenadas validas!\n");
            
            continue;
        }
    }
    return;
}

void selecionar_peca(int arr[2], char grid[8][8], int *jogador, int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Branco", "Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    printf("\n");
    while (1) {
        characteres_digitados = 0;
        print_grid(grid, *pontos_branco, *pontos_preto);
        printf(
            "Jogador atual: %s\n\nPara desistir da partida, digite 'ff'\n\nDigite a coordenada da peca (ex: a2): ",
            jogadores_str[*jogador]);
        while ((letra = getchar()) != '\n') {
            characteres_digitados++;
            if (characteres_digitados == 1) {
                coordenada_x = toupper(letra) - 'A';
            }

            if (characteres_digitados == 2) {
                coordenada_y = letra - '1';
            }
        }
        if (coordenada_x+'A' == 'F' && coordenada_y+17 == 'F'){
            if (*jogador == jogador_branco){
                *pontos_preto = 12;
                break;
            }
            else {
                *pontos_branco = 12;
                break;
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
                 (*jogador) == jogador_branco) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            if (quick_verificar(grid, *jogador, arr)) {
                verificar_captura_mais_pecas(grid, *jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_normal(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }
            break;
        }

        else if (grid[coordenada_y][coordenada_x] == 'p' &&
                 (*jogador) == jogador_preto) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            if (quick_verificar(grid, *jogador, arr)) {
                verificar_captura_mais_pecas(grid, *jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_normal(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }
            break;
        }

        else if (grid[coordenada_y][coordenada_x] == 'B' &&
                 *jogador == jogador_branco) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            if (quick_verificar_dama(grid, *jogador, arr)) {
                verificar_captura_mais_pecas_dama(grid, jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_dama(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }
        }

        else if (grid[coordenada_y][coordenada_x] == 'P' &&
                *jogador == jogador_preto) {
            arr[1] = coordenada_y;
            arr[0] = coordenada_x;
            if (quick_verificar_dama(grid, *jogador, arr)) {
                verificar_captura_mais_pecas_dama(grid,jogador, arr, pontos_preto,
                                             pontos_branco);
            } else {
                mover_peca_dama(grid, arr, jogador, pontos_branco,
                                  pontos_preto);
            }

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

int verifiar_se_vira_dama(char grid[8][8],int jogador,int cordenada_x,int coordenada_y){
    if (jogador == jogador_branco){
        if (coordenada_y == 7){
            grid[coordenada_y][cordenada_x] = 'B';
            return 1;
        }
    }
    else if (jogador == jogador_preto) {
        if (coordenada_y == 0){
            grid[coordenada_y][cordenada_x] = 'P';
            return 1;
        }
    }
    return 0;
}

int quick_verificar_dama(char grid[8][8], int jogador, int peca_selecionada[2]) {
    int x = peca_selecionada[0];
    int y = peca_selecionada[1];
    int capturas_possiveis = 0;

    char peca_adversario = (jogador == jogador_branco) ? 'p' : 'b';
    char peca_adversario_dama = (jogador == jogador_branco) ? 'P' : 'B';

    
    
    for (int i = 1; i < 8; i++) {
        int novo_x = x - i;
        int novo_y = y - i;
        
        if (novo_x < 0 || novo_y < 0) break;
        
        if (grid[novo_y][novo_x] == peca_adversario || grid[novo_y][novo_x] == peca_adversario_dama) {
            
            if (novo_x - 1 >= 0 && novo_y - 1 >= 0 && grid[novo_y - 1][novo_x - 1] == ' ') {
                capturas_possiveis++;
            }
            break;
        } else if (grid[novo_y][novo_x] != ' ') {
            break; 
        }
    }

    
    for (int i = 1; i < 8; i++) {
        int novo_x = x + i;
        int novo_y = y - i;
        
        if (novo_x >= 8 || novo_y < 0) break;
        
        if (grid[novo_y][novo_x] == peca_adversario || grid[novo_y][novo_x] == peca_adversario_dama) {
            if (novo_x + 1 < 8 && novo_y - 1 >= 0 && grid[novo_y - 1][novo_x + 1] == ' ') {
                capturas_possiveis++;
            }
            break;
        } else if (grid[novo_y][novo_x] != ' ') {
            break;
        }
    }

    
    for (int i = 1; i < 8; i++) {
        int novo_x = x - i;
        int novo_y = y + i;
        
        if (novo_x < 0 || novo_y >= 8) break;
        
        if (grid[novo_y][novo_x] == peca_adversario || grid[novo_y][novo_x] == peca_adversario_dama) {
            if (novo_x - 1 >= 0 && novo_y + 1 < 8 && grid[novo_y + 1][novo_x - 1] == ' ') {
                capturas_possiveis++;
            }
            break;
        } else if (grid[novo_y][novo_x] != ' ') {
            break;
        }
    }

    
    for (int i = 1; i < 8; i++) {
        int novo_x = x + i;
        int novo_y = y + i;
        
        if (novo_x >= 8 || novo_y >= 8) break;
        
        if (grid[novo_y][novo_x] == peca_adversario || grid[novo_y][novo_x] == peca_adversario_dama) {
            if (novo_x + 1 < 8 && novo_y + 1 < 8 && grid[novo_y + 1][novo_x + 1] == ' ') {
                capturas_possiveis++;
            }
            break;
        } else if (grid[novo_y][novo_x] != ' ') {
            break;
        }
    }

    return capturas_possiveis;
}


void mover_peca_dama(char grid[8][8], int coordenada_peca[2], int *jogador, int *pontos_branco, int *pontos_preto) {
    char letra;
    char *jogadores_str[2] = {"Branco", "Preto"};
    int coordenada_y = -1;
    int coordenada_x = -1;
    int characteres_digitados = 0;
    
    char peca_dama = (*jogador == jogador_branco) ? 'B' : 'P';
    
    printf("\n");
    print_grid(grid, *pontos_branco, *pontos_preto);
    while (1) {
        characteres_digitados = 0;
        printf("\nJogador %s (DAMA), digite onde deseja mover a peça de coordenada: (%c, %d)\nCaso queira escolher outra peça, aperte 'enter' sem caracteres digitados: ",
               jogadores_str[*jogador], coordenada_peca[0] + 'A',
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
        
        if (characteres_digitados == 0) {
            *jogador++;
            break;
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

        
        int dx = coordenada_x - coordenada_peca[0];
        int dy = coordenada_y - coordenada_peca[1];
        
        
        if (abs(dx) != abs(dy) || dx == 0) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nDama só pode se mover na diagonal!\n");
            continue;
        }
        
        
        if (grid[coordenada_y][coordenada_x] != ' ') {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nPosição de destino ocupada!\n");
            continue;
        }
        
        
        int step_x = (dx > 0) ? 1 : -1;
        int step_y = (dy > 0) ? 1 : -1;
        int caminho_livre = 1;
        
        for (int i = 1; i < abs(dx); i++) {
            int check_x = coordenada_peca[0] + (i * step_x);
            int check_y = coordenada_peca[1] + (i * step_y);
            
            if (grid[check_y][check_x] != ' ') {
                caminho_livre = 0;
                break;
            }
        }
        
        if (!caminho_livre) {
            print_grid(grid, *pontos_branco, *pontos_preto);
            printf("\nCaminho bloqueado!\n");
            continue;
        }
        
        
        grid[coordenada_peca[1]][coordenada_peca[0]] = ' ';
        grid[coordenada_y][coordenada_x] = peca_dama;
        break;
    }
}


void verificar_captura_mais_pecas_dama(char grid[8][8], int *jogador, int coordenada_peca[2], int *pontos_preto, int *pontos_branco) {
    int x = coordenada_peca[0];
    int y = coordenada_peca[1];
    int coordenada_y = -1;
    int coordenada_x = -1;
    int capturas_possiveis = 0;
    char peca_adversario = (*jogador == jogador_branco) ? 'p' : 'b';
    char peca_adversario_dama = (*jogador == jogador_branco) ? 'P' : 'B';
    char peca_dama = (*jogador == jogador_branco) ? 'B' : 'P';
    int cond_comeu_peca = 0;
    
    print_grid(grid, *pontos_branco, *pontos_preto);
    
    
    capturas_possiveis = quick_verificar_dama(grid, *jogador, coordenada_peca);
    
    if (capturas_possiveis >= 1) {
        printf("\n\nA dama pode capturar peças!\n");
        char letra;
        char *jogadores_str[2] = {"Jogador Branco", "Jogador Preto"};
        int characteres_digitados = 0;

        printf("\n");
        print_grid(grid, *pontos_branco, *pontos_preto);
        
        while (1) {
            printf("\nMovimentos de captura possíveis:\n");
            int opcao = 1;
            
            
            for (int i = 1; i < 8; i++) {
                int check_x = x - i;
                int check_y = y - i;
                
                if (check_x < 0 || check_y < 0) break;
                
                if (grid[check_y][check_x] == peca_adversario || grid[check_y][check_x] == peca_adversario_dama) {
                    
                    for (int j = i + 1; j < 8; j++) {
                        int dest_x = x - j;
                        int dest_y = y - j;
                        if (dest_x < 0 || dest_y < 0) break;
                        if (grid[dest_y][dest_x] != ' ') break;
                    }
                    break;
                } else if (grid[check_y][check_x] != ' ') {
                    break;
                }
            }
            characteres_digitados = 0;
            printf("\n\nA dama pode capturar peças!\n");
            printf("\nDigite onde o jogador: %s\nDeseja mover a dama de "
                   "coordenada: (%c, %d): ",
                   jogadores_str[*jogador], coordenada_peca[0] + 'A',
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

            
            int dx = coordenada_x - x;
            int dy = coordenada_y - y;
            
            if (abs(dx) != abs(dy) || dx == 0) {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nMovimento deve ser diagonal!\n");
                continue;
            }
            
            if (grid[coordenada_y][coordenada_x] != ' ') {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nPosição de destino ocupada!\n");
                continue;
            }
            
            
            int step_x = (dx > 0) ? 1 : -1;
            int step_y = (dy > 0) ? 1 : -1;
            int capturou = 0;
            int pos_captura_x = -1, pos_captura_y = -1;
            
            for (int i = 1; i < abs(dx); i++) {
                int check_x = x + (i * step_x);
                int check_y = y + (i * step_y);
                
                if (grid[check_y][check_x] == peca_adversario || grid[check_y][check_x] == peca_adversario_dama) {
                    if (capturou) {
                        
                        capturou = 0;
                        break;
                    }
                    capturou = 1;
                    pos_captura_x = check_x;
                    pos_captura_y = check_y;
                } else if (grid[check_y][check_x] != ' ' && !capturou) {
                    
                    break;
                }
            }
            
            if (capturou) {
                
                grid[pos_captura_y][pos_captura_x] = ' ';
                grid[y][x] = ' ';
                grid[coordenada_y][coordenada_x] = peca_dama;
                
                if (*jogador == jogador_branco) {
                    (*pontos_branco)++;
                } else {
                    (*pontos_preto)++;
                }
                
                cond_comeu_peca = 1;
                break;
            } else {
                print_grid(grid, *pontos_branco, *pontos_preto);
                printf("\nMovimento de captura inválido!\n");
                continue;
            }
        }
    }
    
    if (cond_comeu_peca) {
        int arr_nova_coordenada[2] = {coordenada_x, coordenada_y};
        verificar_captura_mais_pecas_dama(grid, jogador, arr_nova_coordenada,
                                         pontos_preto, pontos_branco);
    }
    else {
        (*jogador)++;
        return;
    }
}
/*

grid[coordenada_peca[1] - 1][coordenada_peca[0] + 1]
grid[coordenada_peca[1] + 1][coordenada_peca[0] + 1]

*/
int main() {
    int modo_debug = 1;
    while (1) {
        system(CLEAR_SCREEN);
        
        int pontos_preto;
        int pontos_branco;
        char resposta;
        int coordenada_peca[2];
        resetar_grid(grid,modo_debug);
        int ganhou_jogo = 0;
        pontos_branco = 0;
        pontos_preto = 0;
        int jogador_atual = jogador_branco;
        while (pontos_branco < 12 && pontos_preto < 12) {
            print_grid(grid, pontos_branco, pontos_preto);
            selecionar_peca(coordenada_peca, grid, &jogador_atual,&pontos_branco, &pontos_preto);
            system(CLEAR_SCREEN);
            jogador_atual++;
            jogador_atual %= 2;
        }
        system(CLEAR_SCREEN);
        
        printf("\n\n\n");
        if (pontos_branco == 12) {
            printf("parabens jogador branco, voce ganhou!!!\n\n");
        } else if (pontos_preto == 12) {
            printf("parabens jogador preto, voce ganhou!!!\n\n");
        }
        printf("deseja jogar novamente (s/n)? Default: s\n\nresposta: ");
        if (toupper(resposta = getchar()) == 'N') {
            printf("\n\nobrigado por jogar!!!");
            break;
        }
    }
    return 0;
}