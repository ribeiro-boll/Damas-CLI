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
    int jogador;
    int status_vida;
} Pecas_jogador;

int contador_pecas_b = 0;
int contador_pecas_p = 0;

char grid[8][8];
void resetar_grid(char arr[8][8],Pecas_jogador *branco,Pecas_jogador *preto) {
    contador_pecas_b = 0;
    contador_pecas_p = 0;
    branco = NULL;
    preto = NULL;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3){
                    arr[i][j] = 'b';
                    contador_pecas_b++;
                    branco = (Pecas_jogador*)realloc(branco,contador_pecas_b*sizeof(Pecas_jogador));
                    branco[contador_pecas_b-1].coordenada_x =i; 
                    branco[contador_pecas_b-1].coordenada_y =j;
                }
                else if (i > 4){
                    arr[i][j] = 'p';
                    contador_pecas_p++;
                    preto = (Pecas_jogador*)realloc(preto,contador_pecas_p*sizeof(Pecas_jogador));
                    preto[contador_pecas_p-1].coordenada_x =i; 
                    preto[contador_pecas_p-1].coordenada_y =j;
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
void printar_structs_branco_e_preto(Pecas_jogador branco,Pecas_jogador preto){

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


void selecionar_peca(int arr[2]){
    char letra;
    int coordenada_y=-1;
    int coordenada_x=-1;
    int characteres_digitados = 0;
    printf("\n");
    while (1) {
        characteres_digitados = 0;
        printf("Digite a coordenada da peça (coluna linha): ");
        while ((letra = getchar())!='\n') {
            characteres_digitados++;
            if (characteres_digitados==1){
                coordenada_y=toupper(letra)-'A';
            }
            if (characteres_digitados==2){
                coordenada_x=letra-'1';
            }
        }
        printf("\n\nX: '%c'\nY: '%d'       \ngrid: '%c'\ncharacteres inputados '%d'\n", coordenada_x+'A', coordenada_y,grid[coordenada_x][coordenada_y], characteres_digitados);
        if (characteres_digitados > 2){
            continue;
        }
        else if (coordenada_y >= 8 || coordenada_y < 0) {
            continue;
        }
        else if (coordenada_x >= 8 || coordenada_x < 0) {
            continue;
        }
        else {
            break;\
        }
    }
    
    arr[0] = coordenada_y; // coluna
    arr[1] = coordenada_x; // linha
}

// entraria a coordenada que fica no array "peca_selecionada"
void mover_peca(int arr[2]){

}


int main(){
    Pecas_jogador *jogador_b = NULL;
    Pecas_jogador *jogador_p = NULL;
    int jogador_atual = jogador_preto;
    int peca_selecionada[2];
    resetar_grid(grid,jogador_b,jogador_p);
    int ganhou_jogo = 0; 
    while(!ganhou_jogo){
        print_grid(grid);
        selecionar_peca(peca_selecionada);
        getchar();
        system("clear");
    }
    return 0;
}
