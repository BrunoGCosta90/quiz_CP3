#ifndef FUNCOES_H
#define FUNCOES_H
#include "modulo.h"

void limpaBuffer();

void voltarMenu();

void limparTela();

void imprimeMenu();

int capturaOpcao();

void cadastrarJogador(Jogador jogadores[], int *tamanho, int maximo);

int escolherJogador(Jogador jogadores[], int tamanho);

#endif
