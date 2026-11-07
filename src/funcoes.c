#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "modulo.h"

void limpaBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void voltarMenu(){
	printf("Pressione ENTER para voltar ao menu...");
	getchar();
	limparTela();
}

void limparTela(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void imprimeMenu(){
	printf("================= Quiz =================\n");
	printf("1. Cadastrar jogador\n");
	printf("2. Escolher jogador\n");
	printf("3. Cadastrar pergunta\n");
	printf("4. Jogar\n");
	printf("5. Estatisticas do jogador\n");
	printf("6. Ranking geral\n");
	printf("7. Sair\n");
}

int capturaOpcao(){
	printf("Escolha uma opcao entre 1 e 7: ");
	int opcao;
	scanf("%d", &opcao);
	while (opcao < 1 || opcao > 7){
		printf("Opcao invalida! Escolha uma opcao entre 1 e 7: ");
		scanf("%d", &opcao);
	}
	limpaBuffer();
	return opcao;
}

int cadastrarJogador(Jogador jogadores[], int totalJogadores, int maximo){
	limparTela();
	printf("=========== Cadastro de jogador ===========\n");
	if (totalJogadores >= maximo) {
		printf("Numero maximo de jogadores atingido.\n");
		voltarMenu();
		return totalJogadores;
	}
	int i = totalJogadores;
	printf("Digite o nome do jogador: ");
	fgets(jogadores[i].nome, sizeof(jogadores[i].nome), stdin);
	jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
	jogadores[i].respondidas = 0;
	jogadores[i].acertos = 0;
	jogadores[i].percentual = 0;
	
	totalJogadores++;
	salvarJogador(jogadores, totalJogadores);
	printf("Jogador salvo com sucesso!\n");
	voltarMenu();
	return totalJogadores;
}

int escolherJogador(Jogador jogadores[], int tamanho){
	limparTela();
	printf("=============== Escolha quem ira jogar =================\n");
	if (tamanho < 1){
		printf("Nao ha jogadores cadastrados ainda.\n");
		voltarMenu();
		return;
	}
	printf("========================================================\n");
	int i;
	for (i = 0; i < tamanho; i++){
		printf("|%d. %-50s |\n", i+1, jogadores[i].nome);
	}
	printf("========================================================\n");
	printf("Escolha o jogador com o numero correspondente: ");
	int escolha;
	scanf("%d", &escolha);
	limpaBuffer();
	while (escolha < 1 || escolha > tamanho){
		printf("Nenhum jogador correspondente, digite um valor de 1 ate %d: ", tamanho);
		scanf("%d", &escolha);
		limpaBuffer();
	}
	printf("\nJogador escolhido: %s\n\n", jogadores[escolha-1].nome);
	voltarMenu();
	return escolha - 1;
}
