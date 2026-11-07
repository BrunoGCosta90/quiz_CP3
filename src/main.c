#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"
#define max_prgt 10
#define max_jgdr 5

int main(){
	Pergunta perguntas[max_prgt];
	int totalPerguntas = carregarPerguntas(perguntas, max_prgt);
	
	Jogador jogadores[max_jgdr];
	int totalJogadores = carregarJogadores(jogadores, max_jgdr);
	//printf("%d", totalJogadores);
	
	int playerOne;
	
	int continua = 1;
	
	while (continua == 1){
		
		imprimeMenu();
		int opcao = capturaOpcao();
		
		switch(opcao){
			case 1: 
				cadastrarJogador(jogadores, &totalJogadores, max_jgdr); 
				break;
			case 2:
				playerOne = escolherJogador(jogadores, totalJogadores);
				break;
			case 3:
			case 4:
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
