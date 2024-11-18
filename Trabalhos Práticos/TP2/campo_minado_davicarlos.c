#include <stdio.h>
#include "matriz.h"
#include "log.h" 


int main() {

    criar_log();
    char dificuldade; // Caractere para definir e armazenar a dificuldade do jogo
    int tamanhotabuleiro = 0; // Tamanho do tabuleiro
    int quantidademinas = 0; // Quantidade de minas a serem inseridas no tabuleiro

    printf("Bem-vindo ao jogo de Campo Minado\nDigite a dificuldade de jogo:\n[F] = Fácil\n[M] = Médio\n[D] = Difícil\n");

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


        log_registrar_cabecalho();

        int numjogadas = 0; // variavel para guardar o numero de jogadas realizadas para o historico do jogo
        int flagfimdejogo = 0; // Controle do fim do jogo
        while(!flagfimdejogo) { // Loop do jogo até que o jogo termine
            int i, j; // Variáveis que serão lidas pelo jogador para as coordenadas
            printf("Digite uma coordenada X e Y no formato\n[linha],[coluna]\n");
            scanf("%d%*[,.]%d", &i, &j); //ignorar a , e .

            // Garante que a coordenada comece em 1 e vá até o tamanho do tabuleiro
            if((i >= 1 && i <= tamanhotabuleiro) && (j >= 1 && j <= tamanhotabuleiro)) {
                

                if(matrizvisivel[i - 1][j - 1] != 'X'){ // Se a coordenada já tiver sido revelada
                    printf("Coordenada já relevada!\n");
                }else{ // Se não, o jogo segue normalmente
                    checa_coordenada(matrizvisivel, matrizcoringa, i - 1, j - 1, &flagfimdejogo, tamanhotabuleiro); //Verifica a coordenada atual e atualiza a matriz do usuário
                    log_registrar_matriz(matrizvisivel, tamanhotabuleiro, tamanhotabuleiro, ++numjogadas, i, j);
                    imprime_tabuleiro(matrizvisivel, tamanhotabuleiro); 

                    if (verifica_vitoria(matrizvisivel, matrizcoringa, tamanhotabuleiro, quantidademinas)) { // Se o jogador venceu
                        printf("parabéns, vc eh fera\n");
                        flagfimdejogo = 1; // Finaliza o jogo
                    }
                
                }

            }
            else {
                printf("Entrada Inválida\nO valor deve estar entre 1 e %d e a entrada deve ser no formato [linha],[coluna\n", tamanhotabuleiro); // Mensagem de valor fora do tamanho do tabuleiro
            }
        }
        // Salvar e fechar o log
        log_salvar();
        log_fechar();

        // Libera a memória alocada das matrizes
        libera_memoria_matriz(matrizvisivel, tamanhotabuleiro);
        libera_memoria_matriz(matrizcoringa, tamanhotabuleiro);
    }

    return 0;
}

