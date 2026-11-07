#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

void imprimeJogadores(Jogador jogadores[], int totalJogadores){
	printf("========================================================\n");
	int i;
	for (i = 0; i < totalJogadores; i++){
		printf("|%d. %-50s |\n", i+1, jogadores[i].nome);
	}
	printf("========================================================\n");
}

int escolherJogador(Jogador jogadores[], int tamanho){
	limparTela();
	printf("=============== Escolha quem ira jogar =================\n");
	if (tamanho < 1){
		printf("Nao ha jogadores cadastrados ainda.\n");
		voltarMenu();
		return;
	}
	imprimeJogadores(jogadores, tamanho);
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

char alternativa(){
	char alternativa;
	scanf(" %c", &alternativa);
	alternativa = toupper(alternativa);
	limpaBuffer();
	while (alternativa != 'A' && alternativa != 'B' && alternativa != 'C' && alternativa != 'D') {
		printf("Alternativa invalida, digite A, B, C ou D): ");
		scanf(" %c", &alternativa);
		alternativa = toupper(alternativa);
		limpaBuffer();
	}
	
	return alternativa;
}

int cadastrarPergunta(Pergunta perguntas[], int totalPerguntas, int maximo){
	limparTela();
	printf("=============== Cadastro de perguntas ===============\n");
	if (totalPerguntas > maximo){
		printf("Total de perguntas permitido ja atingido.\n");
		voltarMenu();
		return totalPerguntas;
	}
	
	int i = totalPerguntas;
	printf("Digite a %da. pergunta:\n", i + 1);
	fgets(perguntas[i].enunciado, sizeof(perguntas[i].enunciado), stdin);
	perguntas[i].enunciado[strcspn(perguntas[i].enunciado, "\n")] = '\0';
	printf("Alternativa A:\nA.");
	fgets(perguntas[i].altA, sizeof(perguntas[i].altA), stdin);
	perguntas[i].altA[strcspn(perguntas[i].altA, "\n")] = '\0';
	printf("Alternativa B:\nB.");
	fgets(perguntas[i].altB, sizeof(perguntas[i].altB), stdin);
	perguntas[i].altB[strcspn(perguntas[i].altB, "\n")] = '\0';
	printf("Alternativa C:\nC.");
	fgets(perguntas[i].altC, sizeof(perguntas[i].altC), stdin);
	perguntas[i].altC[strcspn(perguntas[i].altC, "\n")] = '\0';
	printf("Alternativa D:\nD.");
	fgets(perguntas[i].altD, sizeof(perguntas[i].altD), stdin);
	perguntas[i].altD[strcspn(perguntas[i].altD, "\n")] = '\0';
	printf("Alternativa correta (A, B, C, ou D): ");
	char alt = alternativa();

	perguntas[i].correta[0] = alt;
	perguntas[i].correta[1] = '\0';
	
	totalPerguntas++;
	salvarPergunta(perguntas, totalPerguntas);
	printf("Pergunta salva com sucesso!\n\n");
	voltarMenu();
	return totalPerguntas;
}

void jogar(Pergunta perguntas[], Jogador jogadores[], int jogador, int totalJogadores, int totalPerguntas) {
	limparTela();
	printf("================ Jogar ===============\n");
	if (totalJogadores < 1 && totalPerguntas < 1){
		printf("Nao ha jogadores ou perguntas cadastradas!\n");
		voltarMenu();
		return;
	} else if (totalJogadores < 1) {
		printf("Nao ha jogadores cadastrados!\n");
		voltarMenu();
		return;
	} else if (totalPerguntas < 1) {
		printf("Nao ha perguntas cadastradas!\n");
		voltarMenu();
		return;
	} else if (jogador == -1){
		printf("Nenhum jogador foi escolhido!\n");
		voltarMenu();
		return;
	}
	
	int i = jogador;
	int j, corretas = 0;
	double percentual;
	
	for (j = 0; j < totalPerguntas; j++){
		printf("==============================================================\n");
		printf("%d. %s\n", j+1, perguntas[j].enunciado);
		printf("A. %s\n", perguntas[j].altA);
		printf("B. %s\n", perguntas[j].altB);
		printf("C. %s\n", perguntas[j].altC);
		printf("D. %s\n", perguntas[j].altD);
		printf("Escolha uma alternativa: ");
		char alt = alternativa();
		jogadores[i].respondidas++;
		if (alt == perguntas[j].correta[0]){
			printf("Correto!\n");
			jogadores[i].acertos++;
			corretas++;
		} else {
			printf("Errado!\n");
		}
		percentual = 100.0 * ((double) corretas / (double) totalPerguntas);
		printf("Nesta partida: %d/%d (%.2lf%%)\n", corretas, totalPerguntas, percentual);
		printf("==============================================================\n");
	}
	jogadores[i].percentual = 100.0 * ((double) jogadores[i].acertos / (double) jogadores[i].respondidas);
	
	printf("===================== Placar do jogador ======================\n");
	printf("Nome: %s\n", jogadores[i].nome);
	printf("Total desta partida:\n");
	printf("Acertos: %d\n", corretas);
	printf("Erros: %d\n", totalPerguntas - corretas);
	printf("Percentual: %.2lf%%\n", percentual);
	printf("Total de todas as partidas:\n");
	printf("Acertos: %d\n", jogadores[i].acertos);
	printf("Erros: %d\n", jogadores[i].respondidas - jogadores[i].acertos);
	printf("Percentual total %.2lf%%\n", jogadores[i].percentual);
	printf("==============================================================\n");
	
	salvarJogador(jogadores, totalJogadores);
	voltarMenu();
}

void estatisticas(Jogador jogadores[], int totalJogadores){
	limparTela();
	printf("============== Estatisticas do jogador =================\n");
	int continua = 1;
	int jogador;
	
	while (continua == 1){
		
		
		imprimeJogadores(jogadores, totalJogadores);
		printf("Escolha um jogador digitando o numero corresponde para exibir estatisticas ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &jogador);
		limpaBuffer();
		limparTela();
		if (jogador == 0){
			limparTela();
			return;
		}
		printf("============== Estatisticas do jogador =================\n");
		if(jogador > 0 && jogador <= totalJogadores){
			printf("\n========================================================\n");
			printf("Nome: %s\n", jogadores[jogador-1].nome);
			printf("Respondidas: %d\n", jogadores[jogador-1].respondidas);
			printf("Acertos: %d\n", jogadores[jogador-1].acertos);
			printf("Erros: %d\n", jogadores[jogador-1].respondidas - jogadores[jogador-1].acertos);
			printf("Percentual: %.2lf%%\n", jogadores[jogador-1].percentual);
			printf("========================================================\n\n");
		}
	}
}

void rankingGeral(Jogador jogadores[], int totalJogadores){
	limparTela();
	int i, j;
	for (i = 0; i < totalJogadores; i++){
		for (j = 0; j < totalJogadores - 1; j++){
			if (jogadores[j].percentual < jogadores[j+1].percentual){
				Jogador temp = jogadores[j];
				jogadores[j] = jogadores[j+1];
				jogadores[j+1] = temp;
			}
		}
	}
	
	printf("========================= Ranking geral ===========================\n");
	for (i = 0; i < totalJogadores; i++){
		printf("| %d. %-50s | %6.2lf%% |\n", i+1, jogadores[i].nome, jogadores[i].percentual);
		printf("|-----------------------------------------------------------------|\n");
	}
	printf("===================================================================\n");
	voltarMenu();
	return;
}
