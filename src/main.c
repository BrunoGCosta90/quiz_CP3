#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"
#define max_pergunta 10
#define max_jgdr 5

int main(){
	Pergunta perguntas[max_pergunta];
	int totalPerguntas = carregarPerguntas(perguntas, max_pergunta);
	
	Jogador jogadores[max_jgdr];
	int totalJogadores = carregarJogadores(jogadores, max_jgdr);
	//printf("%d", totalJogadores);
	
	int playerOne = -1;
	
	int continua = 1;
	
	while (continua == 1){
		
		imprimeMenu();
		int opcao = capturaOpcao();
		
		switch(opcao){
			case 1: 
				totalJogadores = cadastrarJogador(jogadores, totalJogadores, max_jgdr); 
				break;
			case 2:
				playerOne = escolherJogador(jogadores, totalJogadores);
				break;
			case 3:
				totalPerguntas = cadastrarPergunta(perguntas, totalPerguntas, max_pergunta);
				break;
			case 4:
				jogar(perguntas,jogadores, playerOne, totalJogadores, totalPerguntas);
				break;
			case 5:
			case 6:
			case 7: 
				continua = 0;
				printf("Saindo...\n");
				break;
			default: break; 
		}
		
	}
	
	
}
