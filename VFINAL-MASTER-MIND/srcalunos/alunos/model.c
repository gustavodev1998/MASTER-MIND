#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "model.h"
#include "utils.h"


/*
 * Descrição:
 * 		Inicializa um código com valores aleatórios
 * Parâmetros
 * 		"code": o código a preencher com valores aleatórios
 * Retorna:
 * 		Nada
 * 
 */
void  code_random(Code code) {
	for(int i=0; i < NPLACES; ++i) {
		code[i] = irandom(MIN_CLR, MAX_CLR);
	}
}

/*
 * Descrição:
 * 		Inicializa um código com valores aleatórios
 * Parâmetros
 * 		"code": o código a preencher com valores aleatórios sem repetições
 * Retorna:
 * 		Nada
 * 
 */
void  code_random_no_rep(Code code) {
	for(int i=0; i < NPLACES; ++i) {
		while (true) {
			int ci = irandom(MIN_CLR, MAX_CLR);
			int j =0;
			while (j < i && code[j] != ci) j ++;
			if (j == i) {
				code[i] = ci;
				break;
			}
		} 
	}
}

/*
 * Descrição:
 * 		calcula o número de casas pretas (cores certas no lugar certo)
 * 		para o código secreto e de tentativa recebidos por parâmetro.
 * Parâmetros
 * 		"try": o código tentativa a avaliar.
 * 		"secret": o código secreto.
 * Retorna:
 * 		O número de cores certas no lugar certo
 */
int blacks(Code try, Code secret) {
	int nb = 0;
	for(int i=0; i < NPLACES; ++i) {
		if (try[i] == secret[i]) {
			nb++;
			try[i]=0;
			secret[i]=0;
		}
	}
	return nb;
}


/*
 * Descrição:
 * 		calcula o número de casas brancas (cores certas no lugar errado)
 * 		para o código secreto e de tentativa recebidos por parâmetro.
 * Parâmetros
 * 		"try": o código tentativa a avaliar.
 * 		"secret": o código secreto.
 * Retorna:
 * 		O número de cores certas no lugar errado
 */
int whites(Code try, Code secret) {
	int nw = 0;
	
	for(int i=0; i < NPLACES; ++i) {
		if (secret[i]==0) continue;
		//printf("process %d at pos %d\n", secret[i], i);
		for(int j=0; j < NPLACES; j++) {
			if (try[j] == secret[i]) {
				nw++;
				//printf("found %d at try pos %d\n", secret[i], j);
				try[j]=0;
				break;
			}
		}		
	}
	return nw;
}

  


