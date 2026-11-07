#include <stdio.h>
#include <string.h>
#include "modulo.h"

int carregarPerguntas(Pergunta perguntas[], int maximo){
	FILE *arquivo = fopen("data/perguntas.txt", "r");
	
	if(arquivo == NULL) {
		return 0;
	}
	
	int i = 0;
	while (i < maximo && fscanf(arquivo, "%199[^;];%49[^;];%49[^;];%49[^;];%49[^;];%1s\n", 
			perguntas[i].enunciado,
			perguntas[i].altA,
			perguntas[i].altB,
			perguntas[i].altC,
			perguntas[i].altD,
			perguntas[i].correta) == 6) {
		i++;	
	}
	
	fclose(arquivo);
	return i;
}

void salvarPergunta(Pergunta perguntas[], int tamanho){
	FILE *arquivo = fopen("data/perguntas.txt", "w");
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	
	int i;
	for (i = 0; i < tamanho; i++) {
		fprintf(arquivo, "%s;%s;%s;%s;%s;%s\n",
				perguntas[i].enunciado,
				perguntas[i].altA,
				perguntas[i].altB,
				perguntas[i].altC,
				perguntas[i].altD,
				perguntas[i].correta); 
	}
	
	fclose(arquivo);
}

int carregarJogadores(Jogador jogadores[], int maximo){
	FILE *arquivo = fopen("data/historico.txt", "r");
	
	if(arquivo == NULL) {
		return 0;
	}
	
	int i = 0;
	while (i < maximo && fscanf(arquivo, "%49[^;];%d;%d;%lf\n",
			jogadores[i].nome,
			&jogadores[i].respondidas,
			&jogadores[i].acertos,
			&jogadores[i].percentual) == 4) {
		jogadores[i].nome[strcspn(jogadores[i].nome, "\r\n")] = '\0';
		i++;	
	}
	
	fclose(arquivo);
	return i;
}

void salvarJogador(Jogador jogadores[], int tamanho) {
	FILE *arquivo = fopen("data/historico.txt", "w");
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	
	int i;
	for (i = 0; i < tamanho; i++){
		jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
		
		fprintf(arquivo, "%s;%d;%d;%.2lf\n",
			jogadores[i].nome,
			jogadores[i].respondidas,
			jogadores[i].acertos,
			jogadores[i].percentual);
	}
	fclose(arquivo);
}
