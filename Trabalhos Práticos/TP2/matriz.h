#ifndef matriz
#define matriz

void define_dificuldade(char d, int *tamanhotabuleiro, int *quantidademinas); /* Recebe um caractere 'd' que definirá a dificuldade, 
um ponteiro de inteiro para definir o valor da dificuldade do tabuleiro e um ponteiro de inteiros para o valor de quantidade de minas */

int **criador_matriz(int tamanhotabuleiro); /*Recebe um inteiro que irá definir o tamanho da matriz tamanhotabuleiro * tamanhotabuleiro e retornará
um ponteiro de um ponteiro desta matriz criada*/

void preenche_matriz_usuario(int **matriz, int tamanho); /*Recebe um ponteiro de um ponteiro da matriz criada pela função criador matriz e seu tamanho
para percorrer seus valores e preencher inicialmente com X*/

void preenche_matriz_coringa(int **matriz, int tamanho); /*Recebe um ponteiro de um ponteiro da matriz criada pela função criador matriz e seu tamanho
para percorrer seus valores e preencher inicialmente com 0*/

void coloca_mina(int **matriz, int tamanhotabuleiro, int quantidademinas); /*Recebe um ponteiro de um ponteiro da matriz criada pela função criador matriz
, seu tamanho para percorremos cada coordenada e recebe a quantidade de minas para colocar aleatoriamente em um determinado numero de coordenadas */

void conta_minas_adjacentes(int **matriz, int tamanhotabuleiro); /*Recebe um ponteiro de um ponteiro da matriz criada pela função criador matriz
, seu tamanho para percorremos cada coordenada e conta a quantidade de minas adjacentes na coordenda percorrida, modificando aquela coordenada para
o valor da quantidade de minas*/

void imprime_tabuleiro(int **matrizvisivel, int tamanhotabuleiro); /*Recebe um ponteiro de um ponteiro da matriz criada pela função criador matriz que atribuimos ao tabuleiro
visivel ao usuario, recebemos um inteiro do tamanho da matriz para percorremos e imprimimos o tabuleiro ao usuario*/



void revela_minas(int **matrizvisivel, int **matrizcoringa, int tamanhotabuleiro); /*Recebe um ponteiro de um ponteiro da matriz visivel ao usuario e matriz coringa, ambas
criadas na função criador matriz, recebe o tamanho do tabuleiro para percorremos as matrizes e a matriz visivel ao usuario obtem os valores da mesma coordenada da matriz coringa*/

void checa_coordenada(int **matrizvisivel, int **matrizcoringa, int i, int j, int *flagfimdejogo, int tamanhotabuleiro); /*Recebe um ponteiro de um ponteiro da matriz visivel e coringa,
recebe i e j como coordenadas, uma flag para definir se o jogo acabou ou não, e o tamanho do tabuleiro*/

int verifica_vitoria(int **matrizvisivel, int **matrizcoringa, int tamanhotabuleiro, int quantidademinas); /*Recebe um ponteiro de um ponteiro da matriz visivel ao usuario e da matriz coringa
, um int do tamanho do tabuleiro e a quantidade de minas, e retorna se o jogador venceu*/

void libera_memoria_matriz(int **matriz, int tamanhotabuleiro); /*Recebe um ponteiro de um ponteiro da matriz, um inteiro do tamanho do tabuleiro/matriz
e libera a memória alocada da matriz*/

int check_dentro_limites(int linha, int coluna, int tamanhotabuleiro); /*Recebe as coordenadas e o tamanho do tabuleiro para verificar se as
coordenadas são válidas e dentro do tabuleiro, e retorna se for verdade*/

void flood_fill(int **matrizvisivel, int **matrizcoringa, int linha, int coluna, int tamanhotabuleiro); /*Recebe um ponteiro de ponteiro da matriz visivel e coringa, as coordenadas e o tamanho do tabuleiro
e revela as coordenadas adjacentes da **matrizvisivel*/



#endif