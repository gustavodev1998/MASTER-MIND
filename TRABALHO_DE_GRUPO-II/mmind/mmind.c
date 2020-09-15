/*----------------------------------------------------------------------------
 * Jogo do master mind em modo consola
 * ISEL, outubro de 2019
 * 
 * Build: gcc -o mmind -Wall -std=c99 mmind.c model.c utils.c
 * Execute: mmind
 * 
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>


#include "mmind.h"
#include "utils.h"


// início das funções auxiliares
 
/*
 * Apresenta um código na consola.
 * Usada sobretudo para depuração de erros (debug).
 */
void code_show(const char msg[], Code code) {
	printf("%s: ", msg);
	for(int i=0; i < NPLACES; ++i) {
		printf("%d", code[i]);
	}
	printf("\n");
}
 
/*
 * descarta todos os caracteres lidos do input até à mudança de linha
 * Usada como auxiliar na função de leitura e validação de código 
 * (função "code_read").
 */
void line_flush() {
	int c;
	do  c=getchar(); while(c != '\n');
}


/*
 * Cópia o código existente no parâmetro "src"
 * para o código "dst"
 * Usada como função auxliar na função que concretiza uma jogada (função "play")
 */
void code_copy(Code dst, Code src) {
	for(int i=0; i < NPLACES; ++i) {
		dst[i] = src[i];
	}
}


// fim das funções auxiliares


/*
 * Lê e valida um código do input standard 
 */
void code_read(const char msg[], Code code) {
 
	int i, num;
	
	do {
		printf("%s", msg);
		
		if (scanf("%d", &num) == 0) continue;
		i= NPLACES -1;
		while(num > 0 && i >= 0) {
			int dig = num % 10;
			if (dig < MIN_CLR || dig > MAX_CLR) {
				line_flush();
				break;
			}
			code[i--] = dig;
			num /= 10;
		}
	}
	while(i >= 0 || num > 0);
}


/*
 * Processa uma jogada do jogador humano.
 * Retorna "true" se o código foi descoberto, "false" caso contrário
 */
 bool play(Code secret, int nplay) {
	Code secret_aux, try;
	char msg[16];
		
	
	code_copy(secret_aux, secret);
	

	sprintf(msg, "Jogada %2d: ", nplay);
	code_read(msg, try);
	int nblacks= blacks(try, secret_aux);
	int nwhites = whites(try, secret_aux);
	
	printf("\tbrancas: %d\n", nwhites);
	printf("\tpretas : %d\n", nblacks);
	
	return nblacks == NPLACES;
}



int main() {
	Code secret;
	int nplay = 1;
	int modo;
	
	printf("selecione o modo em que pretende jogar:\n 1 --> com a possibilidade de cores repetidas\n 2 --> sem a possibilidade de cores repetidas\n");
	scanf("%d", &modo);
	
	while (modo != 1 && modo != 2 ) {
		printf("selecione o modo em que pretende jogar:\n 1 --> com a possibilidade de cores repetidas\n 2 --> sem a possibilidade de cores repetidas\n");
		scanf("%d", &modo);
	}
	
	irandom_init();			// inicia a semente do gerador aleatório
	code_random(secret, modo);	// gera o código a descobrir
	
	while(!play(secret, nplay)) 
		++nplay;
	
	
	printf("O código foi descoberto em %d jogadas!\n", nplay);
	return 0;
}
		 



