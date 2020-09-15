#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "mmind.h"

/*
 * Descrição:
 * 		Inicializa um código com valores aleatórios
 * Parâmetros
 * 		"code": o código a preencher com valores aleatórios
 * Retorna:
 * 		Nada
 * 
 */
void  code_random(Code code, int modo) {
	if (modo == 1) {
		for(int i = 0; i < NPLACES; ++i) {
			code[i] = (rand() % MAX_CLR) + MIN_CLR;
		}
	}
	else {
		int x = 0;
		while (x != 1) {
			bool rep = false;
			for(int i = 0; i < NPLACES; ++i) {
				code[i] = (rand() % MAX_CLR) + MIN_CLR;
			}
			
			for(int i = 0; i < NPLACES; ++i) {		//verificação de repetição de cores
				for(int j = 0; j < NPLACES; ++j) {
					if (code[i] == code[j] && i != j) {
						rep = true;
						break;
					}
				}
			}
			if (!rep)
				++x;
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
	int nblacks = 0;
	for(int i = 0; i < NPLACES; ++i) {
		if (try[i] == secret[i]) {
			nblacks++;
		}	
	}
	return nblacks;
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
	int nwhites = 0;
	int nblacks = 0;
	
	bool used[NPLACES] = { false, false, false, false };

	for(int i = 0; i < NPLACES; ++i)
		if (try[i] == secret[i]) {
			nblacks++;
			secret[i] = 0;
			used[i] = true;
		}

	for(int i = 0; i < NPLACES; ++i) {
		for(int j = 0; j < NPLACES; ++j) {
			if (used[j])
				continue;
			if (try[i] == secret[j]) {
				nwhites++;
				secret[j] = 0;
				used[j] = true;
				break;    
			}	
		}
	}
	
	return nwhites;
}


