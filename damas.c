#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


#define WHITE "\033[37m"


#define VAZIO ' '
#define PRETO 'p'
#define BRANCO 'b'

#define jogador_branco 0
#define jogador_preto 1

#define morto 0
#define vivo 1

typedef struct{
    int coordenada_x;
    int coordenada_y;
    int status_vida;
} Pecas_jogador;

int contador_pecas_b = 0;
int contador_pecas_p = 0;

int jogador_atual = jogador_branco;

char grid[8][8];

void resetar_grid(char arr[8][8],Pecas_jogador **branco,Pecas_jogador **preto) {
    contador_pecas_b = 0;
    contador_pecas_p = 0;
    *branco = NULL;
    *preto = NULL;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3){
                    arr[i][j] = 'b';
                    contador_pecas_b++;
                    (*branco) = (Pecas_jogador*)realloc(*branco,contador_pecas_b*sizeof(Pecas_jogador));
                    (*branco)[contador_pecas_b-1].coordenada_x =j; 
                    (*branco)[contador_pecas_b-1].coordenada_y =i;
                }
                else if (i > 4){
                    arr[i][j] = 'p';
                    contador_pecas_p++;
                    (*preto) = (Pecas_jogador*)realloc(*preto,contador_pecas_p*sizeof(Pecas_jogador));
                    (*preto)[contador_pecas_p-1].coordenada_x =j; 
                    (*preto)[contador_pecas_p-1].coordenada_y =i;
                }
                else{
                    arr[i][j] = ' '; 
                }
            }
            else {
                arr[i][j] = ' '; 
            }
        }
    }
    return;
}

// fazer função para testar as structs criadas
void printar_structs_branco_e_preto(Pecas_jogador *branco,Pecas_jogador *preto){
    printf("\n");
    printf("\n");
    for(int i =0; i<contador_pecas_b;i++){
        if (i%4==0 && i !=0){
            printf(" |\n");
        }
        printf(" | (%d,%d) - (%c,%d)",branco[i].coordenada_x,branco[i].coordenada_y,branco[i].coordenada_x+'A',branco[i].coordenada_y+1);
    }
    printf(" |\n");
    printf("\n");
    printf("\n");
    for(int i =0; i<contador_pecas_p;i++){
        if (i%4==0 && i!=0){
            printf(" |\n");
        }
        printf(" | (%d,%d) - (%c,%d)",preto[i].coordenada_x,preto[i].coordenada_y,preto[i].coordenada_x+'A',preto[i].coordenada_y+1);
    }
    printf(" |\n\n");
    return;
}

void print_grid(char arr[8][8]){
    int contador =1;
    printf(" A B C D E F G H\n");
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            printf("|%c",arr[i][j]);
            
        }
        printf("| %d\n",contador++);
    }
    return;
}

void selecionar_peca(int arr[2],char grid[8][8],int jogador){
    char letra;
    char *jogadores_str[2] = {"Jogador Branco","Jogador Preto"};
    int coordenada_y=-1;
    int coordenada_x=-1;
    int characteres_digitados = 0;
    printf("\n");
    while (1) {
        characteres_digitados = 0;
        printf("Jogador atual: %s\nDigite a coordenada da peça (coluna linha): ",jogadores_str[jogador]);
        while ((letra = getchar())!='\n') {
            characteres_digitados++;
            if (characteres_digitados==1){
                coordenada_x=toupper(letra)-'A';
            }
            if (characteres_digitados==2){
                coordenada_y=letra-'1';
            }
        }
        printf("\n\nX: '%c' -> %d\nY: '%d' -> %d      \ngrid: '%c'\ncharacteres inputados '%d'\nJogador: %d", coordenada_x+'A',coordenada_x, coordenada_y+1,coordenada_y,grid[coordenada_y][coordenada_x], characteres_digitados,jogador);
        if (characteres_digitados > 2){
            printf("\nDigite apenas duas coordenadas!\n");
            continue;
        }
        else if (coordenada_y >= 8 || coordenada_y < 0) {
            printf("\nDigite uma coordenada dentro dos limites!\n");
            continue;
        }
        else if (coordenada_x >= 8 || coordenada_x < 0) {
            printf("\nDigite uma coordenada dentro dos limites!\n");
            continue;
        }
        else if (coordenada_x >= 8 || coordenada_x < 0) {
            printf("\nDigite uma coordenada dentro dos limites!\n");
            continue;
        }
        else if ((grid[coordenada_y][coordenada_x] == 'b' || grid[coordenada_y][coordenada_x] == 'B') && jogador == jogador_branco){
            arr[0] = coordenada_y; // coluna
            arr[1] = coordenada_x; // linha
            printf("\n\n(%d,%d) -> %c",arr[0],arr[1],grid[coordenada_y][coordenada_x]);
            break;
        }
        else if ((grid[coordenada_y][coordenada_x] == 'p' || grid[coordenada_y][coordenada_x] == 'P') && jogador == jogador_preto) {
            arr[0] = coordenada_y; // coluna
            arr[1] = coordenada_x; // linha
            printf("\n\n(%d,%d) -> %c",coordenada_x,coordenada_y,grid[coordenada_y][coordenada_x]);
            break;
        }
        else {
            printf("\nDigite a coordenada de uma peca correspondente a sua cor!\n");
            continue;
        }
    }
}

// entraria a coordenada que fica no array "peca_selecionada"
void mover_peca(int coordenada_peca[2],int jogador){
    
}

int main(){
    Pecas_jogador *jogador_b = NULL;
    Pecas_jogador *jogador_p = NULL;
    int peca_selecionada[2];
    resetar_grid(grid,&jogador_b,&jogador_p);
    int ganhou_jogo = 0; 
    while(!ganhou_jogo){
        print_grid(grid);
        printar_structs_branco_e_preto(jogador_b, jogador_p);
        selecionar_peca(peca_selecionada,grid,jogador_atual);
        getchar();
        system("clear");
        jogador_atual++;
        jogador_atual%=2;
    }
    return 0;
}
