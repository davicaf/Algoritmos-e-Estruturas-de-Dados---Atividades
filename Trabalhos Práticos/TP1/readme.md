CAMPO MINADO – TP1
Este programa é um trabalho prático da disciplina Algoritmos e Estruturas de Dados, ministrada pelo professor Juan Gabriel Colonna – ICOMP/UFAM. O objetivo era implementar o jogo do Campo Minado, utilizando conceitos de alocação dinâmica de memória com matrizes construídas como vetores de ponteiros.
O trabalho foi realizado com base nas instruções fornecidas e respeitando os requisitos especificados.
Como executar
Basta compilar o arquivo com “gcc campo_minado_davicarlos.c” e executar “./a.out campo_minado_davicarlos.c”
Ou compilar “gcc campo_minado_davicarlos.c -o campo_minado” e executar “./campo_minado”
Descrição do Jogo
O jogo segue as regras clássicas do Campo Minado. Ele começa solicitando ao usuário que escolha uma dificuldade, com as seguintes opções:
• Fácil: Tabuleiro 10x10 com 3 minas;
• Médio: Tabuleiro 20x20 com 6 minas;
• Difícil: Tabuleiro 30x30 com 9 minas.
Após a escolha, uma matriz é gerada com minas colocadas aleatoriamente e impresso ao jogador como uma matriz preenchida com 'X'. O jogador informa coordenadas para revelar as células, com as seguintes regras:
• Se a célula selecionada não tiver minas vizinhas, será exibido 0.
• Se a célula selecionada tiver minas vizinhas, será exibida a quantidade de minas ao redor.
• Se o jogador selecionar uma célula com uma mina, o jogo termina com "game over" e todas as minas são reveladas.
• Caso todas as células sem minas sejam reveladas, o jogador vence e o jogo exibe a mensagem "parabens, vc eh fera".
Técnicas
• Alocação dinâmica de matrizes com ponteiros.
• Geração aleatória de minas com base em time.h.
• Funções modulares para legibilidade e organização do código.
• Liberação de memória alocada com free() ao final da execução.
• Tratamento de bordas e coordenadas fora dos limites do tabuleiro.
