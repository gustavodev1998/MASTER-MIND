

#define MIN_CLR 1
#define MAX_CLR 6

#define MAX_COLORS (MAX_CLR-MIN_CLR+1)
#define NPLACES 4

typedef int Code[NPLACES];



/*
 * Descrição:
 * 		Inicializa um código com valores aleatórios
 * Parâmetros
 * 		"code": o código a preencher com valores aleatórios
 * Retorna:
 * 		Nada
 * 
 */
void  code_random(Code code);

/*
 * Descrição:
 * 		Inicializa um código com valores aleatórios
 * Parâmetros
 * 		"code": o código a preencher com valores aleatórios sem repetições
 * Retorna:
 * 		Nada
 * 
 */
void  code_random_no_rep(Code code);


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
int blacks(Code try, Code secret);
	 

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
int whites(Code try, Code secret);
 

