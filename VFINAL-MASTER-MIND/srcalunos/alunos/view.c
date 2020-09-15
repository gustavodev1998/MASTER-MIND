#include <pg/graphics.h>

#include "config.h"

#include "model.h"

#include "utils.h"
#include "components.h"
#include "view.h"


void panic(char msg[]) {
	printf("Fatal error: %s\n", msg);
	graph_exit();
}


/*------------------------------------------------------
 * Hole - representa o sítio onde se pode colocar uma peça
 *----------------------------------------------------------*/
 


/*
 * Cria uma estrutura "Hole"
 * 		
 */
Hole hole_create(int x, int y, int radius, RGB back_color) {
	Point center = { x, y };
	Hole h = {
		.center = center,
		.border_color = HOLE_BORDER_COLOR,
		.back_color = back_color,
		.radius = radius,
		.clr_number = 0,
		.empty = true
	};
	
	return h;

}

/*
 * Desenha a estrutura "Hole" recebida por parâmetro
 */
void hole_draw(Hole h) {
	RGB color = (h.empty) ? h.back_color : pal_color_from_number(h.clr_number);
	int radius = (h.empty) ? h.radius/2 : h.radius;
	// draw border
	if (h.empty)
		graph_circle(h.center.x, h.center.y, h.radius, HOLE_BORDER_COLOR, true);
	// draw hole
	
	graph_circle(h.center.x, h.center.y, radius, color, true);
}

/*
 * Colocar uma peça no buraco, apresentando o resultado
 * Retorna:
 * 		A estrutura com a peça colocada
 */
Hole hole_set_color(Hole hole, int clr_number)  {
	hole.empty = false;
	hole.clr_number = clr_number;
	hole_draw(hole);
	return hole;
}



/*
 * Verifica se o ponto "p" está dentro da área
 * definida pelo buraco "h"
 */
bool hole_selected(Hole h, Point p) {
	return point_distance(h.center, p) < h.radius;
}

/*
 * obter a cor (código) da peça no "Buraco"
 */
int hole_get_color(Hole h) {
	return h.empty ? 0 : h.clr_number;
}

/*------------------------------------------------------
 * CodeView - Usado para a  apresentação um código de cores
 *----------------------------------------------------------*/

/*
 * criar a representação de um código na posiçao (x,y) dada
 */
CodeView cv_create(int x, int y) {
	Point p = { x, y };
	CodeView t;
	
	t.start = p;
	 
	x = x + TRY_BORDER + HOLE_RADIUS;
    y = y + TRY_BORDER  + HOLE_RADIUS;
	for(int i= 0; i < NPLACES; ++i) {
		t.holes[i] = hole_create(x, y, HOLE_RADIUS, HOLE_BACK_COLOR);
		x+= TRY_BORDER + 2*HOLE_RADIUS;
	}
	
	return t;
		
}

/*
 * "desenhar" o código dado
 */
void cv_draw(CodeView t) {
	graph_rect(t.start.x, t.start.y, TRY_WIDTH, TRY_HEIGHT, TRY_COLOR, true);
	for(int i= 0; i < NPLACES; ++i) {
		hole_draw(t.holes[i]);
	}
}

/*
 *  devolve o índice do "buraco" de "t" que contém o ponto "p"
 *  ou -1 caso o ponto não esteja contido em nenhum "buraco"
 */
int cv_get_selected_hole(CodeView t, Point p) {
	for(int i=0; i < NPLACES; ++i) {
		if (hole_selected(t.holes[i], p)) {
			return i;
		}
	}
	return -1;
}

/*
 * Altera a cor da peça presente no  buraco de posição "place"
 * na "vista" "t"
 */
CodeView cv_change_place(CodeView t, int place, int number) {
	if (hole_get_color(t.holes[place]) == number) {
		//t.holes[place] = hole_remove_piece(t.holes[place]);
	}
	else {
		t.holes[place] = hole_set_color(t.holes[place], number);
	}
	return t;
}

/*
 * Devolve true se todos os buracos têm peça
 */
bool cv_is_filled(CodeView t) {
	printf("is filled ? \n");
	for(int i=0; i < NPLACES; ++i) {
		if (hole_get_color(t.holes[i]) == 0) {
			printf("No!\n");
			return false;
		}
	}
	printf("Yes!\n");
	return true;
}


/*
 * popular o código "c" com 
 * a sequência de cores presente em "t"
 */
void cv_get_code(CodeView t, Code c) {
	for(int i=0; i < NPLACES; ++i) {
		c[i] = hole_get_color(t.holes[i]);
	}
}


/*
 * Esconde a vista "t" 
 * (Simulando uma tampa por cima)
 */
void cv_hide(CodeView t) {
	graph_rect(t.start.x, t.start.y, TRY_WIDTH, TRY_HEIGHT, TRY_COLOR_HIDE, true);
}

/*------------------------------------------------------
 * Palette  -Usado para disponibilizar as peças (cores) do jogo
 *----------------------------------------------------------*/

// tabela de cores
RGB colors[MAX_COLORS]; 

// a palette de peças
// como existe uma única platte na aplicação
// as funções que a manipulam usam diretamente esta variável
// não a recebendo por parametro
Palette pal; 


/*
 * Inicia a palete de cores
 * Os códigos correspondem ao índice (+ 1) da respectiva cor
 */
void pal_init_colors() {
	colors[0] = c_white;
	colors[1] = c_black;
	colors[2] = c_orange;
	colors[3] = c_blue;
	colors[4] = c_red;
	colors[5] = c_green;
}

/*
 * Para criar a palete na posição dada
 */
void pal_create(int x, int y) {
	Point start = {x, y};
	
	pal_init_colors();
	pal.start = start;
	x = x + TRY_BORDER + HOLE_RADIUS;
	y = y + TRY_BORDER  + HOLE_RADIUS;
	for(int i= 0; i < MAX_COLORS; ++i) {
		pal.colors[i] = hole_create(x, y, HOLE_RADIUS, colors[i]);
		
		x+= TRY_BORDER + 2*HOLE_RADIUS;
	}
	pal.selected = hole_create(x+ PALETTE_BORDER, y, HOLE_RADIUS, HOLE_BACK_COLOR);
	pal.selected = hole_set_color(pal.selected, 1);
}

/*
 * "desenha" a palete
 */	 
void pal_draw() {
	graph_rect(pal.start.x, pal.start.y, PALETTE_WIDTH, PALETTE_HEIGHT, TRY_COLOR, true);
	for(int i= 0; i < MAX_COLORS; ++i) {
		hole_draw(pal.colors[i]);
	}
	
	hole_draw(pal.selected);
}


/*
 * Devolve o índice do "buraco" que contem, na palete,  o ponto "p",
 * ou -1 se não existir nenhum
 */ 
int pal_get_selected( Point p) {
	for(int i=0; i < MAX_COLORS; ++i) {
		if (hole_selected(pal.colors[i], p)) {
			return i+1;
		}
	}
	return -1;
}

/*
 * Modifica a cor do "buraco" que representa a cor seleccionada
 * com a cor de índice "index"
 */
void  pal_select( int clr_number) {
	pal.selected = hole_set_color(pal.selected, clr_number);
}

/*
 * Devolve o código da cor seleccionada na palete "p"
 */ 
int pal_get_selected_color() {
	return hole_get_color(pal.selected);
}

 
/*
 * Devolve a cor correspondente ao código dado
 */
RGB pal_color_from_number(int number) {
	if (number < MIN_CLR || number > MAX_CLR) 
		panic("Invalid color number!\n");
	return colors[number -1];
}

/*------------------------------------------------------
 * Result - Usado para apresentar o resultado de uma jogada  
 *----------------------------------------------------------*/

/*
 * Cria um resultado na posição (x,y)
 */
Result res_create(int x, int y) {
	Result r = {0};
	
	// A implementar
	return r;
}

/*
 * modifica e retorna o resultado com o número
 * de "brancas" e "pretas" recebido
 */
Result res_set(Result r, int whites, int blacks) {
	// A implementar
	return r;
}

/*
 * "desenha o resultado no écran gráfico
 */
void   res_draw(Result r) {
	// A implementar
}
