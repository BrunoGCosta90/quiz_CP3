#ifndef MODULO_H
#define MODULO_H

typedef struct {
	char enunciado[200];
	char altA[50];
	char altB[50];
	char altC[50];
	char altD[50];
	char correta[];
} Pergunta;

typedef struct {
	char nome[50];
	int respondidas;
	int acertos;
	double percentual;
} Jogador;

int carregarPerguntas(Pergunta perguntas[], int maximo);

void salvarPergunta(Pergunta perguntas[], int tamanho);

int carregarJogadores(Jogador jogadores[], int maximo);

void salvarJogador(Jogador jogadores[], int tamanho);

#endif
