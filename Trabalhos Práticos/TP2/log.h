#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

// Funções para gerenciamento do log
void criar_log();  // Cria o arquivo de log
void log_registrar_cabecalho();  // Registra o cabeçalho do log
void log_registrar_matriz(int **matriz, int linhas, int colunas, int jogadas, int x, int y);  // Registra o estado da matriz
void log_salvar();  // Garante que os dados sejam salvos no arquivo
void log_fechar();  // Fecha o arquivo de log

#endif
