#include <pg/graphics.h>
#include <stdbool.h>

/*
 * Definições para a criação e apresentação de um elemento de um código
 */

typedef struct hole {
	bool empty;
	Point center;
	int radius;
	int clr_number;
	RGB back_color;
	RGB border_color;
} Hole;

/*
 * Criar um "buraco" na posição dada,
 * com o tamanho e cor dados
 */
Hole hole_create(int x, int y, int radius, RGB back_color);

/*
 * Determinar se um ponto está contido no "buraco" dado
 */
bool hole_selected(Hole h, Point p);

/*
 * "desenhar" um "buraco"
 */
void hole_draw(Hole h);

/*
 * obter a cor (código) da peça no "Buraco"
 */
int hole_get_color(Hole h);


/*
 * modificar a cor (código) da peça no "buraco"
 */
Hole hole_set_color(Hole h, int clr_number);

	 
/*
 * Definições para a criação e apresentação de um código
 */

typedef struct cv {
	Point start;
	Hole holes[NPLACES];
} CodeView;


/*
 * criar a representação de um código na posição (x,y) dada
 */
CodeView cv_create(int x, int y);


/*
 * "desenhar" o código dado
 */
void cv_draw(CodeView t);

/*
 * popular o código "c" com 
 * a sequência de cores presente em "t"
 */
void cv_get_code(CodeView t, Code c);

/*
 *  devolve o índice do "buraco" de "t" que contém o ponto "p"
 *  ou -1 caso o ponto não esteja contido em nenhum "buraco"
 */
int cv_get_selected_hole(CodeView t, Point p);

/*
 * Altera a cor da peça presenta no  buraco de posição "place"
 * na "vista" "t"
 */
CodeView cv_change_place(CodeView t, int place, int number);

/*
 * Devolve true se todos os buracos têm peça
 */
bool cv_is_filled(CodeView t);

/*
 * Esconde a vista "t" 
 * (Simulando uma tampa por cima)
 */
void cv_hide(CodeView t);

/*
 * Definições para a palete de cores
 */

#define C_WHITE 1
#define C_BLACK 2

typedef struct pallete {
	Point start; 				// canto superior esquerdo da palete
	Hole colors[MAX_COLORS];	// array de buracos que representam as cores
	Hole selected;				// apresenta a cor da palete seleccionada
} Palette;


/*
 * Para criar a palete na posição dada
 */
void pal_create(int x, int y);

/*
 * Devolve o índice do "buraco" que contém na palete o ponto "p"
 * ou -1 se não existir nenhum
 */ 
int pal_get_selected(Point p);

/*
 * "desenha" a palete
 */	 
void pal_draw();

/*
 * Devolve o código da cor seleccionada na palete "p"
 */ 
int pal_get_selected_color();

/*
 * Devolve a cor correspondente ao código dado
 */
RGB pal_color_from_number(int number);


/*
 * Modifica a cor do "buraco" que representa a cor seleccionada
 * com a cor de índice "index"
 */
void pal_select(int color_index); 


/*
 * Definições para apresentar o resultado de uma jogada
 */

typedef struct result {
	int whites, blacks;	// quantidade de "brancas" e "pretas" no resultado
	Point start;		// canto superior esquerdo do resultado
	// A completar
} Result;


/*
 * Cria um resultado na posição (x,y)
 */
Result res_create(int x, int y);

 
/*
 * modifica e retorna o resultado com o número
 * de "brancas" e "pretas" recebido
 */
Result res_set(Result r, int whites, int blacks);

/*
 * "desenha o resultado no écran gráfico
 */
void   res_draw(Result r);
