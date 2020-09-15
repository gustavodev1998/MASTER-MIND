

#define MAX_NAME_SIZE 128


/*
 * Descrição:
 * 		Conta as palavras (nomes próprios e apelidos) do nome recebido por parâmetro.	
 * Parâmetros:
 * 		"name": nome a contabilizar
 * Retorno:
 * 		Total de palavras do nome
 */
 
int count_words(char name[]);

/*
 * Descrição:
 * 		produz o nome que resulta da conversão para maíuscula dos carateres do nome
 * 		recebido por parâmetro
 * Parâmetros:
 * 		"orig": nome a converter
 * 		"result": nome com as letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Não tem
 */
void name_all_upper(char orig[], char result[]);

/*
 * Descrição:
 *		Gera o nome que resulta da conversão para maíuscula do primeiro carater
 * 		de cada nome próprio e apelido do nome recebido. Todas as outros carateres de cada
 * 		nome deverão estar em minuscula
 * Parâmetros:
 * 		"orig": nome a converter
 * 		"result": nome com as primeiras letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Não tem
 */
void name_first_upper(char orig[], char result[]);

/*
 * Descrição:
 * 		Remove os espaços iniciais e finais e mais do que 
 * 		um espaço entre as palavras de um nome
 * Parâmetros:
 * 		"orig": nome a converter
 * 		"result": nome com as letras do nome original convertidas para maíuscula
 * Retorno:
 * 		Dimensão da string "result"
 */
 
int name_trimmed(char orig[], char result[]);
	 
/*
 * Descrição:
 *		Gera o formato do nome que corresponde ao último apelido (primeira letra em maíuscula) 
 * 		seguido da primeira Letra (em maíuscula) do primeiro nome seguido de ponto.
 * 		Espaços iniciais e finais e espaços intermédios a mais devem ser eliminados
 * 		Ex: se o nome for "  Carlos    Santos " ou resultado é "Santos C."
 * Parâmetros:
 * 		"orig": nome a converter
 * 		"result": o nome no formato requerido
 * Retorno:
 * 		"true" se o nome for passível de conversão (tem de ter pelo menos um nome proprio e um apelido)
 * 		"false" caso contrário.
 */
 
bool name_compressed(char orig[], char result[]);

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
  *	 	 "false" caso contrário.  
  */
	
bool name_middle_compressed(char orig[], char result[]);
	 
  


	 

	 




 




