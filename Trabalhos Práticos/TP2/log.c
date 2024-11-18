#include "log.h"
#include <stdlib.h>
#include <string.h>

FILE *arquivo_log = NULL;  // Ponteiro para o arquivo de log global

void criar_log() { // Função para criar e abrir o arquivo de log
    
    time_t  horario = time(NULL); // Obtem o horário atual
    struct tm *info_tempo = localtime(&horario); //Converte o valor do horario para estrutura tm

   
    char nome_arquivo[100];    // Gerar o nome do arquivo como data e hora
    //Formata o nome da string do arquivo no formato log_dia_mes_ano_hora_minutos_segundos.txt
    snprintf(nome_arquivo, sizeof(nome_arquivo), "registro_%02d_%02d_%04d_%02d_%02d_%02d.txt", info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900, info_tempo->tm_hour, info_tempo->tm_min, info_tempo->tm_sec);
    
    arquivo_log = fopen(nome_arquivo, "w"); //Abre o arquivo gerado

    if (arquivo_log == NULL) { // Caso o arquivo não abra
        printf("Erro ao criar o log.\n");
        return;
    }


}

void log_registrar_cabecalho() { // Função para registrar o cabeçalho do log

    if (arquivo_log == NULL){
        return;
    } // Caso o arquivo possua algum erro de criar ou abrir

    time_t  horario = time(NULL); // Horario armazena o numero de segundos desde 1° de janeiro de 1970
    struct tm *info_tempo = localtime(& horario); //Converte o valor do horario para estrutura tm
    
    /*A função fprint é usada para escrever no arquivo
    A data e a hora são extraídas da estrutura tm apontada por info_tempo.
    tm_mday é o dia do mês.
    tm_mon é o mês, como começa em 0 somamos +1
    tm_year é o ano, contado a partir de 1900, e por isso é somado +1900
    tm_hour, tm_min, tm_sec são hora, minuto e segundo respectivamente
    Formatamos %02d para que tenha sempre dois dígitos e preencher com 0 a esquerda
    Formatamos %04d para que o ano tenha quatro dígitos
    */
    fprintf(arquivo_log, "Registro de Campo Minado - Log de Jogo\nData %02d/%02d/%04d\nHorario de Inicio: %02d:%02d:%02d\n\n", info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900, info_tempo->tm_hour, info_tempo->tm_min, info_tempo->tm_sec);
}


void log_registrar_matriz(int **matriz, int linhas, int colunas, int jogadas, int x, int y) { // Função para registrar o estado da matriz no log
    if (arquivo_log == NULL){
        return;
    } // Caso o arquivo possua algum erro de criar ou abrir

    // Escrevemos o numero de jogadas e as coordenadas escolhidas pelo jogador
    fprintf(arquivo_log, "Quantidade de Jogadas: %d\nCoordenada escolhida pelo jogador: (%d, %d)\nMatriz Visivel ao Usuário no momento:\n", jogadas, x, y);
    
    // Percorrer a matriz e imprimir as minas
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == -1) { // Se a coordenada for uma mina
                fprintf(arquivo_log, "X "); //Imprimir X
            } else { // Se não
                fprintf(arquivo_log, "%c ", matriz[i][j] + '0');
            }
        }
        fprintf(arquivo_log, "\n");
    }
    fprintf(arquivo_log, "\n");
}


void log_salvar() { // Função para salvar as alterações no registro
    if (arquivo_log == NULL){
        return;
    } // Caso o arquivo possua algum erro de criar ou abrir
    fflush(arquivo_log);  // Garante que os dados sejam salvos no registro
}


void log_fechar() { // Função para fechar o registro e liberar memória
    if (arquivo_log != NULL) {
        fclose(arquivo_log); // fecha o arquivo
        arquivo_log = NULL;  // libera o ponteiro
    }
}
