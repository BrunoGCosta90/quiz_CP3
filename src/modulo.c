#include <stdio.h>
#include <string.h>
#include "modulo.h"

int carregarPerguntas(Pergunta perguntas[], int maximo){
	FILE *arquivo = fopen("data/perguntas.txt", "r");
	
	if(arquivo == NULL) {
		return 0;
	}
	
	int i = 0;
	while (i < maximo && fscanf(arquivo, "%199[^;];%49[^;];%49[^;];%49[^;];%49[^;];%c", 
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
		fprintf(arquivo, "%s;%s;%s;%s;%s;%c\n",
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

//int carregarJogadores(Jogador jogadores[], int maximo){
//	FILE *arquivo = fopen("data/historico.txt", "r");
//	
//	if(arquivo == NULL) {
//		return 0;
//	}
//	
//	char linha[256];
//	int i = 0;
//	
//	// Lê o arquivo linha por linha com segurança
//	while (i < maximo && fgets(linha, sizeof(linha), arquivo) != NULL) {
//		// Remove a quebra de linha do final da linha lida
//		linha[strcspn(linha, "\r\n")] = '\0';
//		
//		// Se a linha estiver vazia, pula para a próxima
//		if (strlen(linha) == 0) continue;
//		
//		// Extrai os campos separados por ponto e vírgula
//		if (sscanf(linha, "%49[^;];%d;%d;%lf",
//				jogadores[i].nome,
//				&jogadores[i].respondidas,
//				&jogadores[i].acertos,
//				&jogadores[i].percentual) == 4) {
//			i++;
//		}
//	}
//	
//	fclose(arquivo);
//	return i;
//}

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
