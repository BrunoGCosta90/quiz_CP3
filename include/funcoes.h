#ifndef FUNCOES_H
#define FUNCOES_H
#include "modulo.h"

void limpaBuffer();

void voltarMenu();

void limparTela();

void imprimeMenu();

int capturaOpcao();

int cadastrarJogador(Jogador jogadores[], int totalJogadores, int maximo);

void imprimeJogadores(Jogador jogadores[], int totalJogadores);

int escolherJogador(Jogador jogadores[], int tamanho);

char alternativa();

int cadastrarPergunta(Pergunta perguntas[], int totalPerguntas, int maximo);

void jogar(Pergunta perguntas[], Jogador jogadores[], int jogador, int totalJogadores, int totalPerguntas);

void estatisticas(Jogador jogadores[], int totalJogadores);

void rankingGeral(Jogador jogadores[], int totalJogadores);

#endif
