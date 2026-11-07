#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "modulo.h"

void limpaBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void imprimeMenu(){
	printf("======= Quiz =======\n");
	printf("1. Cadastrar jogador\n");
	printf("2. Escolher jogador\n");
	printf("3. Cadastrar pergunta\n");
	printf("4. Jogar\n");
	printf("5. Estatisticas do jogador\n");
	printf("6. Ranking geral\n");
	printf("7. Sair\n");
	
}

int capturaOpcao(){
	int opcao;
	scanf("%d", &opcao);
	while (opcao < 1 || opcao > 7){
		printf("Opcao invalida! Escolha uma opcao entre 1 e 7: ");
		scanf("%d", &opcao);
	}
	limpaBuffer();
	return opcao;
}

void cadastrarJogador(Jogador jogadores[], int *tamanho, int maximo){
	if (*tamanho >= maximo) {
		printf("Numero maximo de jogadores atingido.\n");
		return;
	}
	
	
	printf("Digite o nome do jogador: ");
	fgets(jogadores[*tamanho].nome, sizeof(jogadores[*tamanho].nome), stdin);
	jogadores[*tamanho].nome[strcspn(jogadores[*tamanho].nome, "\n")] = '\0';
	jogadores[*tamanho].respondidas = 0;
	jogadores[*tamanho].acertos = 0;
	jogadores[*tamanho].percentual = 0;
	(*tamanho)++;
	int i = *tamanho;
	salvarJogador(jogadores, i);
	return;
}
