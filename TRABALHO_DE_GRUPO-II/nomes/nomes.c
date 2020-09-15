#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "nomes.h"



/*
 * Descrição:
 * 		produz o nome que resulta da conversão para maíuscula dos carateres do nome
 * 		recebido por parâmetro
 * Parâmetros:
 * 		"nome": nome a converter
 * 		"result": nome com as letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Não tem
 */
void name_all_upper(char orig[], char result[]) {
	 // A implementar
	  int i;
	 for ( i = 0; orig[i] != '\0'; i++) {
		if ( orig[i] >= 'a' &&  orig[i] <= 'z' ) {
			result[i] = orig[i] - ('a' - 'A');
			
		} else {
			result[i] = orig[i];
		}
	}
	result[i] = 0;
	 
}

/*
 * Descrição:
 * 		Conta as palavras (nomes próprios e apelidos) do nome recebido por parâmetro.	
 * Parâmetros:
 * 		"nome": nome a contabilizar
 * Retorno:
 * 		o total de palavras do nome
 */
int count_words(char name[]) {
	 // A implementar
	 
	 int flag = 0; 
	 int total = 0;
	 
	 for ( int i = 0; name[i] != '\0'; i++) {
		 
		 if ( !flag &&  ( name[i] != ' ' && name[i] != '\t' && name[i] != '\n')  ) {
			 flag = 1;
			 total++;
		}
		 
		 else if ( flag && ( name[i] == ' ') ) {	// Confirmar com o professor pq n necessito por tab e new line na condição else if, se por o contador fica == 1;
			 flag = 0;
		}
		 
		 
	
	}
	



	return total;
}

/*
 * Descrição:
 * 		remove os espaços iniciais e finais e mais do que 
 * 		um espaço entre as palavras de um nome
 * Parâmetros:
 * 		"nome": nome a converter
 * 		"result": nome com as letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Não tem
 */
int name_trimmed(char orig[], char result[]) {
	// A implementar
	int i = 0;
	int j = 0;
	
	while ( orig[i] == ' ') i++; // Saltando os espaços iniciais
	
	while ( orig[i] != '\0' ) { 
			while ( orig[i] != ' ' && orig[i] != '\0' ) { //COpiar palavra para o destino
				result[j] = orig[i];
				j++;
				i++;
			}
			while ( orig[i] == ' ' ) i++; //Saltar os espaços a seguir a palavra
			if ( orig[i] != '\0' ) {
				result[j] = ' ';
				j++;
			}
	}
	
	result[j] = 0;
	
	 return j;
	
}

/*
 * Descrição:
 *		Gera o nome que resulta da conversão para maíuscula do primeiro carater
 * 		de cada nome próprio e apelido do nome recebido. Todas as outros carateres de cada
 * 		nome deverão estar em minuscula
 * Parâmetros:
 * 		"nome": nome a converter
 * 		"result": nome com as primeiras letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Não tem
 */
void name_first_upper(char orig[], char result[]) {
	 // A implementar
	 int i = 0;
	int j = 0;
	
	while ( orig[i] == ' ') i++; // Saltando os espaços iniciais
	
	while ( orig[i] != '\0' ) { 
			while ( orig[i] != ' ' && orig[i] != '\0' ) { //COpiar palavra para o destino
				result[j] = orig[i];
				j++;
				i++;
			}
			while ( orig[i] == ' ' ) i++; //Saltar os espaços a seguir a palavra
			if ( orig[i] != '\0' ) {
				result[j] = ' ';
				j++;
			}
	}
	
	result[j] = 0;
	
	int k = j;
	
	int l = 0;
	result[l] = toupper(result[l]);
	for ( l = 1; l < k; l++) {
		result[l] = tolower(result[l]);
		
		if ( result[l-1] == ' ' && result [l] != ' ') {
				result[l] = toupper(result[l]);
		
	
		}
			
}
	
}

/*
 * Descrição:
 *		Gera o formato do nome que corresponde ao último apelido (primeira letra em maíuscula) 
 * 		seguido da primeira Letra (em maíuscula) do primeiro nome seguido de ponto.
 * 		Espaços iniciais e finais e espaços intermédios a mais devem ser eliminados
 * 		Ex: se o nome for "  Carlos    Santos " ou resultado é "Santos C."
 * Parâmetros:
 * 		"nome": nome a converter
 * 		"result": o nome no formato requerido
 * Retorno:
 * 		"true" se o nome for passível de conversão (tem de ter pelo menos um nome proprio e um apelido)
 * 		"false" caso contrário.
 */
bool name_compressed(char orig[], char result[]) {
	// A implementar
	
	if ( count_words(orig) < 2) return false;
	
	else {
		
		name_first_upper(orig, result);
		
		int tamanho = strlen(result)-1;
		int tamanho_definitivo = strlen(result)-1;
		int i = 0;
		
		while (result[tamanho] != ' ' ) tamanho--; // Anda para trás ate encontrar um espaço
		
		char Primeiro = result[0]; // Guarda primeira letra 
		
		while (tamanho != tamanho_definitivo) {
			
			result[i] = result[tamanho+1];
			tamanho++;
			i++;
			
		}
		result[i] = ' ';
		result[i + 1] = Primeiro;
		result[i + 2] = '.';
		result[i + 3] = 0;
	}
	
	return true;

	 
}


/* Descrição:   
  * 	Gera o formato alternativo para o nome recebido por parâmetro em que apenas   *    
  * 	o primeiro nome e o ultimo apelido são apresentados por extenso, estando os nomes   *    
  * 	intermédios apresentado na forma de abreviatura.  *    
  * 	Espaços iniciais e finais e espaços intermédios a mais devem ser eliminados  *    
  * 	Ex: se o nome original for:  "  pedro manuel  vieira   rodrigues  "  *        
  * 		o nome resultante da conversão é:  "Pedro M. V. Rodrigues".  
  * Parâmetros:  
  *	 	 "orig": nome a converter  
  *  	 "result": o nome no formato requerido  
  * Retorno:  
  *  	 "true" se o nome for passível de conversão   
  *  	 (tem de ter pelo menos um nome próprio e um apelido). 
  *	 	 "false" caso contrário.  */



bool name_middle_compressed(char orig[], char result[] ) {	
	
	char aux[MAX_NAME_SIZE];
	
	name_first_upper(orig, aux);
	
	int first_letter = 0;
	int words = 1;
	
	int j = 0;
	
	int x = count_words(aux);
	if ( x > 2 ) {
	
		for ( int i = 0; i < strlen(aux); i++) {
			if (words == 1 || words == x ) { 	//Tratamento do primeiro nome e Apelido
				result[j] = aux [i]; 
				j++;
					if ( aux[i] == ' ' ) {
						words++;
					 }
			} 
			else{								//Tratamento dos nomes do meio
					if ( first_letter == 0 ) { 	//Aproveitamento da primeira letra
						result[j] = aux[i];
						result[j+1] = '.';
						j += 2;
						 first_letter = 1;
						}
						else {					//Espera pelo próximo nome
								if ( aux[i] == ' ' ) {
									 result[j] = aux[i];
									 j++;
									 words++;
									 first_letter = 0;
								}
						}
					
					}
				
			}
		return true;
		}
	return false;
}

 
	









