#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"




void define_dificuldade(char d, int *tamanhotabuleiro, int *quantidademinas) {
    *tamanhotabuleiro = 0;
    switch(d) { // Se o caractere corresponder a um dos casos a dificuldade é definida
        case 'F': 
        case 'f': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 10;
            *quantidademinas = 15;
            printf("DIFICULDADE FÁCIL SELECIONADA\n");
            break;
        case 'M':
        case 'm': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 20;
            *quantidademinas = 60; 
            printf("DIFICULDADE MÉDIA SELECIONADA\n");
            break;
        case 'D':
        case 'd': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 30;
            *quantidademinas = 135;
            printf("DIFICULDADE DIFÍCIL SELECIONADA\n");
            break;
        default: // Caso o caractere lido não corresponda a nenhum caso
            printf("Entrada inválida\nInsira 'F', 'M' OU 'D' para definir a dificuldade\n");
            break;
    }
}

int **criador_matriz(int tamanhotabuleiro) { // Função para criar uma matriz alocada
    int **tempmatriz = malloc(tamanhotabuleiro * sizeof(int *)); // Alocação dinâmica de memória de uma matriz de ponteiros
    for(int cont = 0; cont < tamanhotabuleiro; cont++) { //Alocação dinâmica de memória para cada linha da matriz
        tempmatriz[cont] = malloc(tamanhotabuleiro * sizeof(int));
       if(tempmatriz == NULL){
        printf("ERRO AO CRIAR MATRIZ\n");
        exit(1);
    }
    }
    if(tempmatriz == NULL){
        printf("ERRO AO CRIAR MATRIZ\n");
        exit(1);
    }
    return tempmatriz; // Retorna a matriz gerada
}

void preenche_matriz_usuario(int **tabuleiro, int tamanho) { // Função para preencher a matriz visível ao usuário com 'X'
    for(int i = 0; i < tamanho; i++) { // Percorre as linhas
        for(int j = 0; j < tamanho; j++) { //Percorre as colunas
            tabuleiro[i][j] = 'X'; // Preenche a cada coordenada i e j da matriz com X
        }
    }
}

void preenche_matriz_coringa(int **tabuleiro, int tamanho) { // Função para preencher a matriz coringa inicialmente com 0
    for(int i = 0; i < tamanho; i++) { // Percorre as linhas
        for(int j = 0; j < tamanho; j++) { // Percorre as colunas
            tabuleiro[i][j] = 0; // Preenche a cada coordenada i e j da matriz com 0
        }
    }
}

void coloca_mina(int **tabuleiro, int tamanhotabuleiro, int quantidademinas) {
    int contminas = 0; // Contador de minas
    srand(time(NULL)); // Gerador de números aleatórios
    while(contminas < quantidademinas) {
        int i = rand() % tamanhotabuleiro; // Gera um índice aleatório de linha
        int j = rand() % tamanhotabuleiro; // Gera um índice aleatório de coluna
        if(tabuleiro[i][j] != -1) { // Verifica se já não há uma mina na coordenada i e j da matriz
            tabuleiro[i][j] = -1; // -1 representa uma mina
            contminas++; // Incrementa o contador de minas
        }
    }
}

void conta_minas_adjacentes(int **tabuleiro, int tamanhotabuleiro) {
    for (int i = 0; i < tamanhotabuleiro; i++) { // Percorre linha da matriz
        for (int j = 0; j < tamanhotabuleiro; j++) { // Percorre coluna da matriz
            if (tabuleiro[i][j] != -1) { // Se a coordenada atual i e j não possuem mina
                int quantidade_minas_adjacentes = 0; // Contador de minas adjacentes
                // Percorre as posições adjacentes a coordenada atual i e j
                for (int coluna = -1; coluna <= 1; coluna++) { // Percorre as colunas adjacentes
                    for (int linha = -1; linha <= 1; linha++) { // Percorre as linhas adjacentes 
                        if (coluna != 0 || linha != 0) { // If para ignorar caso a coordenada adjacente seja igual a coordenada atual
                            int templinha = i + coluna; // Calcula a linha adjacente
                            int tempcoluna = j + linha; // Calcula a coluna adjacente
                            if (templinha >= 0 && templinha < tamanhotabuleiro && tempcoluna >= 0 && tempcoluna < tamanhotabuleiro) { // Se as coordenadas estão dentro do tabuleiro
                                if (tabuleiro[templinha][tempcoluna] == -1) { // Se coordenada adjacente possui uma mina
                                    quantidade_minas_adjacentes++; // Quantidade de minas + 1
                                }
                            }
                        }
                    }
                }
                tabuleiro[i][j] = quantidade_minas_adjacentes; // Atualiza a coordenada atual i e j com a quantidade de minas adjacentes
            }
        }
    }
}

void imprime_tabuleiro(int **matrizvisivel, int tamanhotabuleiro) {
    printf("COLUNA"); // Imprimir marcadores de coluna para o usuário
    for(int cont = 0; cont < tamanhotabuleiro; cont++){ //Percorre cada coluna do tabuleiro
        if(cont < 9)printf("|%d| ", cont+1); // Se o número tiver menos que dois caracteres imprimir ex: |1|
        else printf("|%d ", cont+1); // Caso contrário, imprimir ex: |10
    }
    printf("\n\n"); // Pular linha para ficar mais intuitivo e menos embaralhado com os valores do tabuleiro
    for (int i = 0; i < tamanhotabuleiro; i++) { //Percorre linha da matriz
        if(i < 9){
            printf("%dºl.  ", i+1); // imprimir marcadores de linha
        }else{
            printf("%dºl. ", i+1); // imprimir marcadores de linha
        }
        for (int j = 0; j < tamanhotabuleiro; j++) { //Percorre coluna da matriz
            if (matrizvisivel[i][j] == 'X') { // Se a coordenada não foi revelada
                printf("|%c| ", matrizvisivel[i][j]); // Mostra 'X' se não revelado
            } else if (matrizvisivel[i][j] == -1) { // Se a coordenada tem uma mina
                printf("-1| "); // Exibe mina
            } else { // Caso a coordenada tenha número de minas adjacentes
                printf("|%d| ", matrizvisivel[i][j]); // Exibe número de minas adjacentes
            }
        }
        printf("\n"); // Quebra de impressão da linha da matriz
    }
}

void revela_minas(int **matrizvisivel, int **matrizcoringa, int tamanhotabuleiro) {
    for (int i = 0; i < tamanhotabuleiro; i++) { // Percorre linha da matriz
        for (int j = 0; j < tamanhotabuleiro; j++) { // Percorre coluna da matriz
            if (matrizcoringa[i][j] == -1) { // Se a coordenada for uma mina
                matrizvisivel[i][j] = -1; // Revela a mina
            } else {
                matrizvisivel[i][j] = matrizcoringa[i][j]; // Revela número de minas adjacentes
            }
        }
    }
}

void checa_coordenada(int **matrizvisivel, int **matrizcoringa, int i, int j, int *flagfimdejogo, int tamanhotabuleiro) {
    if(matrizcoringa[i][j] == -1) { // Se a coordenada escolhida for uma mina
        printf("game over\n"); // Imprimir game over
        revela_minas(matrizvisivel, matrizcoringa, tamanhotabuleiro); // Revela todas as minas
        *flagfimdejogo = 1; // Atualiza a flag de fim de jogo
    }else if(matrizcoringa[i][j] == 0){ // Se não, se a coordenada escolhida for igual a 0
        flood_fill(matrizvisivel, matrizcoringa, i, j, tamanhotabuleiro); //Verificar as coordenadas adjacentes
    }

    else {
        matrizvisivel[i][j] = matrizcoringa[i][j]; // Atualiza a matriz visível com o valor da matriz coringa
    }
}

int verifica_vitoria(int **matrizvisivel, int **matrizcoringa, int tamanhotabuleiro, int quantidademinas) {
    int cont = 0; // Contador para as coordenadas reveladas
    for (int i = 0; i < tamanhotabuleiro; i++) { //Percorre linha da matriz
        for (int j = 0; j < tamanhotabuleiro; j++) { // Percorre coluna da matriz
            if (matrizvisivel[i][j] != 'X') { // Se não for mina
                cont++; // Incrementa contador de coordenadas reveladas
            }
        }
    }
    // Se o número de coordenadas reveladas for igual ao total de coordenada (total - minas) = jogador ganhou
    return (cont == (tamanhotabuleiro * tamanhotabuleiro - quantidademinas));
}

void libera_memoria_matriz(int **tabuleiro, int tamanhotabuleiro) {
    for(int cont = 0; cont < tamanhotabuleiro; cont++) { // Percorre cada linha da matriz
        free(tabuleiro[cont]); // Liberada a memória alocada da linha cont da matriz
    }
    free(tabuleiro); // Libera a memória alocada para o ponteiro da matriz
}

int check_dentro_limites(int linha, int coluna, int tamanhotabuleiro) { // 
    return linha >= 0 && linha < tamanhotabuleiro && coluna >= 0 && coluna < tamanhotabuleiro; // Verifica se a coordenada está dentro do tabuleiro
}

void flood_fill(int **matrizvisivel, int **matrizcoringa, int linha, int coluna, int tamanhotabuleiro) {

    if (!check_dentro_limites(linha, coluna, tamanhotabuleiro)) { // Verifica se a coordenada está dentro do tabuleiro
        return; //encerra
    }
    if (matrizvisivel[linha][coluna] != 'X'){   // Verifica se a coordenada já foi revelada ou contém uma mina
        return; // encerra
    }

    matrizvisivel[linha][coluna] = matrizcoringa[linha][coluna]; //Revela a coordenada

    if (matrizcoringa[linha][coluna] > 0) { // Se a coordenada não for vazia, isto é, tiver um número maior que 0
        return; // encerra
    }
    
    // Se não ativar nenhum caso de parada
    for (int i = -1; i <= 1; i++) { // Chama a função nas coordenadas adjacentes
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) { // Evita recursão na coordenada atual
                flood_fill(matrizvisivel, matrizcoringa, linha + i, coluna + j, tamanhotabuleiro); // + i e + j para ser a coordenada adjacente
            }
        }
    }
}





