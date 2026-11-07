#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"
#define max_pergunta 10
#define max_jogador 5

int main(){
	Pergunta perguntas[max_pergunta];
	int totalPerguntas = carregarPerguntas(perguntas, max_pergunta);
	
	Jogador jogadores[max_jogador];
	int totalJogadores = carregarJogadores(jogadores, max_jogador);
	
	int playerOne = -1;
	
	int continua = 1;
	
	while (continua == 1){
		
		imprimeMenu();
		int opcao = capturaOpcao();
		
		switch(opcao){
			case 1: 
				totalJogadores = cadastrarJogador(jogadores, totalJogadores, max_jogador); 
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
				estatisticas(jogadores, totalJogadores);
				break;
			case 6:
				rankingGeral(jogadores, totalJogadores);
				break;
			case 7: 
				continua = 0;
				printf("Saindo...\n");
				break;
			default: break; 
		}
		
	}
	
	
}
