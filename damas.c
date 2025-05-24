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

char grid[8][8];
void resetar_grid(char arr[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3){
                    arr[i][j] = 'b';
                }
                else if (i > 4){
                    arr[i][j] = 'p'; 
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
    int peca1=-1;
    int peca2=-1;
    int characteres_digitados = 0;
    printf("\n");
    while (1) {
        characteres_digitados = 0;
        printf("Digite a coordenada da peça (coluna linha): ");
        while ((letra = getchar())!='\n') {
            characteres_digitados++;
            if (characteres_digitados==1){
                peca1=toupper(letra)-'A';
            }
            if (characteres_digitados==2){
                peca2=letra-'1';
            }
        }
        printf("\n\nx: '%d'  |  y: '%d'   grid: '%c'        characteres inputados '%d'\n", peca1, peca2,grid[peca2][peca1], characteres_digitados);
        if (characteres_digitados > 2){
            continue;
        }
        else if (peca1 >= 8 || peca1 < 0) {
            continue;
        }
        else if (peca2 >= 8 || peca2 < 0) {
            continue;
        }
        else {
            break;
        }
    }
    
    arr[0] = peca1; // coluna
    arr[1] = peca2; // linha
}

// entraria a coordenada que fica no array "peca_selecionada"
void mover_peca(int arr[2]){

}


int main(){
    
    int jogador_atual = jogador_preto;
    int peca_selecionada[2];
    resetar_grid(grid);
    int ganhou_jogo = 0; 
    while(!ganhou_jogo){
        print_grid(grid);
        selecionar_peca(peca_selecionada);
        getchar();
        system("clear");
    }
    return 0;
}
