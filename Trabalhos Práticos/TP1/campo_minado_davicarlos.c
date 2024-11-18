#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REVELADO 1
#define NAO_REVELADO 0

void define_dificuldade(char d, int *tamanhotabuleiro, int *quantidademinas) {
    *tamanhotabuleiro = 0;
    switch(d) { // Se o caractere corresponder a um dos casos a dificuldade é definida
        case 'F': 
        case 'f': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 10;
            *quantidademinas = 3;
            printf("DIFICULDADE FÁCIL SELECIONADA\n");
            break;
        case 'M':
        case 'm': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 20;
            *quantidademinas = 6; 
            printf("DIFICULDADE MÉDIA SELECIONADA\n");
            break;
        case 'D':
        case 'd': //caso o usuário escreva o caractere de dificuldade minúsculo
            *tamanhotabuleiro = 30;
            *quantidademinas = 9;
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
    }
    return tempmatriz; // Retorna a matriz gerada
}

void preenche_matriz_usuario(int **matriz, int tamanho) { // Função para preencher a matriz visível ao usuário com 'X'
    for(int i = 0; i < tamanho; i++) { // Percorre as linhas
        for(int j = 0; j < tamanho; j++) { //Percorre as colunas
            matriz[i][j] = 'X'; // Preenche a cada coordenada i e j da matriz com X
        }
    }
}

void preenche_matriz_coringa(int **matriz, int tamanho) { // Função para preencher a matriz coringa inicialmente com 0
    for(int i = 0; i < tamanho; i++) { // Percorre as linhas
        for(int j = 0; j < tamanho; j++) { // Percorre as colunas
            matriz[i][j] = 0; // Preenche a cada coordenada i e j da matriz com 0
        }
    }
}

void coloca_mina(int **matriz, int tamanhotabuleiro, int quantidademinas) {
    int contminas = 0; // Contador de minas
    srand(time(NULL)); // Gerador de números aleatórios
    while(contminas < quantidademinas) {
        int i = rand() % tamanhotabuleiro; // Gera um índice aleatório de linha
        int j = rand() % tamanhotabuleiro; // Gera um índice aleatório de coluna
        if(matriz[i][j] != -1) { // Verifica se já não há uma mina na coordenada i e j da matriz
            matriz[i][j] = -1; // -1 representa uma mina
            contminas++; // Incrementa o contador de minas
        }
    }
}

void conta_minas_adjacentes(int **matriz, int tamanhotabuleiro) {
    for (int i = 0; i < tamanhotabuleiro; i++) { // Percorre linha da matriz
        for (int j = 0; j < tamanhotabuleiro; j++) { // Percorre coluna da matriz
            if (matriz[i][j] != -1) { // Se a coordenada atual i e j não possuem mina
                int quantidade_minas_adjacentes = 0; // Contador de minas adjacentes
                // Percorre as posições adjacentes a coordenada atual i e j
                for (int coluna = -1; coluna <= 1; coluna++) { // Percorre as colunas adjacentes
                    for (int linha = -1; linha <= 1; linha++) { // Percorre as linhas adjacentes 
                        if (coluna != 0 || linha != 0) { // If para ignorar caso a coordenada adjacente seja igual a coordenada atual
                            int templinha = i + coluna; // Calcula a linha adjacente
                            int tempcoluna = j + linha; // Calcula a coluna adjacente
                            if (templinha >= 0 && templinha < tamanhotabuleiro && tempcoluna >= 0 && tempcoluna < tamanhotabuleiro) { // Se as coordenadas estão dentro do tabuleiro
                                if (matriz[templinha][tempcoluna] == -1) { // Se coordenada adjacente possui uma mina
                                    quantidade_minas_adjacentes++; // Quantidade de minas + 1
                                }
                            }
                        }
                    }
                }
                matriz[i][j] = quantidade_minas_adjacentes; // Atualiza a coordenada atual i e j com a quantidade de minas adjacentes
            }
        }
    }
}

void imprime_tabuleiro(int **matrizvisivel, int tamanhotabuleiro) {
    for (int i = 0; i < tamanhotabuleiro; i++) { //Percorre linha da matriz
        for (int j = 0; j < tamanhotabuleiro; j++) { //Percorre coluna da matriz
            if (matrizvisivel[i][j] == 'X') { // Se a coordenada não foi revelada
                printf("%c ", matrizvisivel[i][j]); // Mostra 'X' se não revelado
            } else if (matrizvisivel[i][j] == -1) { // Se a coordenada tem uma mina
                printf("-1 "); // Exibe mina
            } else { // Caso a coordenada tenha número de minas adjacentes
                printf("%d ", matrizvisivel[i][j]); // Exibe número de minas adjacentes
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
    // Se o número de coordenadas reveladas for igual ao total de células (total - minas) = jogador ganhou
    return (cont == (tamanhotabuleiro * tamanhotabuleiro - quantidademinas));
}

void libera_memoria_matriz(int **matriz, int tamanhotabuleiro) {
    for(int cont = 0; cont < tamanhotabuleiro; cont++) { // Percorre cada linha da matriz
        free(matriz[cont]); // Liberada a memória alocada da linha cont da matriz
    }
    free(matriz); // Libera a memória alocada para o ponteiro da matriz
}

int main() {
    char dificuldade; // Caractere para definir e armazenar a dificuldade do jogo
    int tamanhotabuleiro = 0; // Tamanho do tabuleiro
    int quantidademinas = 0; // Quantidade de minas a serem inseridas no tabuleiro

    printf("Digite a dificuldade\n[F] = Fácil\n[M] = Médio\n[D] = Difícil\n");

    while(tamanhotabuleiro == 0) { // Loop para garantir que o tabuleiro tenha um tamanho válido
        scanf(" %c", &dificuldade); // LÊ o caractere
        define_dificuldade(dificuldade, &tamanhotabuleiro, &quantidademinas); // Define o tamanho do tabuleiro
    }

    // Verifica se a dificuldade foi corretamente selecionada
    if (tamanhotabuleiro > 0) {
        // Cria e preenche a matriz visível ao jogador
        int **matrizvisivel = criador_matriz(tamanhotabuleiro); 
        preenche_matriz_usuario(matrizvisivel, tamanhotabuleiro);
        
        // Cria e preenche a matriz coringa que contém a posição das minas e os números de minas adjacentes
        int **matrizcoringa = criador_matriz(tamanhotabuleiro);
        preenche_matriz_coringa(matrizcoringa, tamanhotabuleiro);
        
        // Coloca as minas na matriz coringa
        coloca_mina(matrizcoringa, tamanhotabuleiro, quantidademinas);
        
        // Preenche os valores das coordenadas adjacentes a mina
        conta_minas_adjacentes(matrizcoringa, tamanhotabuleiro);
        
        // Imprime o tabuleiro visível ao jogador
        imprime_tabuleiro(matrizvisivel, tamanhotabuleiro);

        int flagfimdejogo = 0; // Controle do fim do jogo
        while(!flagfimdejogo) { // Loop do jogo até que o jogo termine
            int i, j; // Variáveis que serão lidas pelo jogador para as coordenadas
            printf("Digite uma coordenada X e Y\n[linha] [coluna]\n");
            scanf("%d %d", &i, &j); 

            // Garante que a coordenada comece em 1 e vá até o tamanho do tabuleiro
            if((i >= 1 && i <= tamanhotabuleiro) && (j >= 1 && j <= tamanhotabuleiro)) {
                checa_coordenada(matrizvisivel, matrizcoringa, i - 1, j - 1, &flagfimdejogo, tamanhotabuleiro); //Verifica a coordenada atual e atualiza a matriz do usuário
                imprime_tabuleiro(matrizvisivel, tamanhotabuleiro); 

                if (verifica_vitoria(matrizvisivel, matrizcoringa, tamanhotabuleiro, quantidademinas)) { // Se o jogador venceu
                    printf("parabéns, vc eh fera\n");
                    flagfimdejogo = 1; // Finaliza o jogo
                }

            }
            else {
                printf("Entrada Inválida\nO valor deve estar entre 1 e %d\n", tamanhotabuleiro); // Mensagem de valor fora do tamanho do tabuleiro
            }
        }
        // Libera a memória alocada das matrizes
        libera_memoria_matriz(matrizvisivel, tamanhotabuleiro);
        libera_memoria_matriz(matrizcoringa, tamanhotabuleiro);
    }

    return 0;
}

