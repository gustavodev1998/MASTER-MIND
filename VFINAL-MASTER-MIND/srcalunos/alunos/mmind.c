/*-----------------------------------------------------------------
 * Programa que permite jogar ao master mind com interface gráfica
 * usando ablioteca gráfica de pg1
 * 
 * Isel, novembro de 2019
 * 
 * Build: gcc -o mmind -Wall -std=c99 mmind.c view.c model.c utils.c components.c -lpg -lm
 *-----------------------------------------------------------------*/
 
#include <pg/graphics.h>

#include "config.h"

#include "model.h"

#include "utils.h"
#include "components.h"
#include "view.h"


typedef struct try {
	CodeView code; 	// código de tentativa
	Result res;		// apresenta  os resultados  
} Try;


// variáveis globais

Clock game_time;		// relógio com o tempo total de jogo
Clock play_time; 		// relógio com o tempo de jogada

MsgView final_msg;		// para afixação de mensagem de vitória ou derrota

Try tries[NTRIES];		// representa a zona de tentativas de acerto
int currTry;			// tentativa corrente

CodeView secret;		// vista do código secreto
Code secretCode;		// código secreto


CheckBox rep_colors;	// selecciona jogo com cores repetidas

Button bt_check;		// botão para verificar a jogada

bool game_over;			// indica que se chegou ao final do jogo


void show_secret() {
	for(int i=0; i < NPLACES; ++i) {
		secret = cv_change_place(secret, i, secretCode[i]);
	}
	cv_draw(secret);
}

/*
 * Criação do código secreto  
 */
void create_secret() {
	if (cbox_is_checked(rep_colors))
		code_random(secretCode);
	else 
		code_random_no_rep(secretCode);
	//show_secret();
	cv_hide(secret);
}

/*
 * Construção dos componentes gráficos no tabuleiro de jogo
 */
void board_init() {
	int x = BOARD_BORDER, y = BOARD_Y + BOARD_HEIGHT - TRY_HEIGHT - TRY_BORDER;
	
	
	
	// criação da palette de cores
	pal_create(x + 2*TRY_WIDTH, y - (NTRIES * TRY_HEIGHT)/4);
	
	// criação dos elementos de tentativa e resultado
	for(int i=0; i < NTRIES; ++i) {
		 tries[i].code = cv_create(x, y); 
		 tries[i].res = res_create(x + TRY_WIDTH + TRY_BORDER, y);
		 y = y -TRY_HEIGHT - TRY_BORDER;
	}

	x = BOARD_BORDER;
    y = BOARD_BORDER ;
    
    // elemento de visualização do código secreto
	secret = cv_create(x,y);
	
	
	// criação do relógio de tempo total 
	int clock_label_x = x + 2*TRY_WIDTH;
	int clock_label_y = y;
	char ct_label[] = "Tempo total:  ";

	Size sz = get_text_size(ct_label, MEDIUM_FONT);
	RGB label_color = c_gray;
	
	graph_text(clock_label_x, clock_label_y + sz.height + 20, label_color, ct_label, MEDIUM_FONT); 
	
	game_time = clk_create(clock_label_x + sz.width, y, LARGE_CLOCK, CLOCK_COLOR_TOTAL, CLOCK_BACK_COLOR);

	
	
	// criação do relógio de tempo parcial 
	char cp_label[] = "Tempo Jogada: ";
	graph_text(clock_label_x, clock_label_y + sz.height + 90, label_color, cp_label, MEDIUM_FONT); 
	play_time = clk_create(clock_label_x + sz.width, y+ 70, LARGE_CLOCK, CLOCK_COLOR_PARTIAL, CLOCK_BACK_COLOR);

    // checkbox para a seleccão do tipo de jogo
    
    rep_colors = cbox_create(
						clock_label_x, clock_label_y + 150, 
						"Cores repetidas: ", 
						MEDIUM_FONT,
						c_gray, c_orange, c_dgray);
	rep_colors = cbox_toggle(rep_colors);				


	// botão para verificar a jogada
	bt_check = bt_create(clock_label_x, clock_label_y + 220, "CHECK", c_red);
	bt_check = bt_set_enable(bt_check, false);
	
	// caixa de texto para apresentação do resulytado final
	final_msg = mv_create(MSG_X,MSG_Y,36, MSG_MARGIN, 2*MSG_MARGIN, MEDIUM_FONT, c_black, c_gray);
	
	// ainda não há nenhuma tentativa
	currTry=0;

}

/*
 * prenche o fundo do ecrâ com a cor de background
 */
void draw_background() {
	graph_rect( BOARD_X, BOARD_Y , BOARD_WIDTH, BOARD_HEIGHT, c_dgray, true);
}

/*
 * Afixação no ecrâ gráfico dos elementos do tabuleiro de jogo
 */
void board_draw() {
	// draw board area
	printf("Start board draw!\n");
	for(int i=0; i < NTRIES; ++i) {
		cv_draw(tries[i].code); 
		res_draw(tries[i].res);
	}
	pal_draw();
	clk_show(game_time);
	clk_show(play_time);
	
	cbox_draw(rep_colors);
	
	bt_draw(bt_check, BUTTON_RELEASED);
	printf("end board draw!\n");
}

/*
 * Usada para afixar a mensagem final de vitória
 */
void show_winner_msg() {
	char msg[128];
	
	show_secret();
	sprintf(msg, "Parabens! Venceu em %d tentativa(s)!", currTry);
	mv_show_text(final_msg, msg, ALIGN_CENTER);
	game_over = true;
}

/*
 * Usada para afixar a mensagem final de derrota
 */				 
void show_looser_msg() {
	char msg[128];
	
	show_secret();
	sprintf(msg, "Perdeu! Esgotou as tentativas!");
	mv_show_text(final_msg, msg, ALIGN_CENTER);
	game_over = true;
}

/*
 * Copia o código existente no parâmetro "src"
 * para o código "dst"
 * Usada como função auxliar na função que concretiza uma jogada (função "check_play")
 */
void code_copy(Code dst, Code src) {
	for(int i=0; i < NPLACES; ++i) {
		dst[i] = src[i];
	}
}

#define WIN 1
#define LOOSE 2
#define NONE 0

/*
 * Para afixar o tempo da jogada e reiniciar o relógio
 * parcial
 */
void process_play_time() {
	char str_time[8];
	
	int m = play_time.m;
	int s = play_time.s;
	sprintf(str_time, "%02d:%02d", m, s);
	
	// afixar o tempo da jogada
	graph_text(tries[currTry].code.start.x + TRY_WIDTH+ RESULT_WIDTH + TRY_BORDER + RESULT_BORDER, 
		   tries[currTry].code.start.y + 10 , c_orange,	str_time, MEDIUM_FONT);
				
	
	// para a contagem de jogada
	play_time = clk_reset(play_time);
	clk_show(play_time);
}

/*
 * Avaliação de uma tentativa de descoberta do código
 * Retorna:
 * 		WIN (1) - se a jogada descobriu o código
 * 		LOOSE (2) - se as tentativas esgotaram
 * 		NONE (0) - se o jogo não terminou
 */
int check_play() {
	// A completar
	return 0;
}

/*
 * Função que trata os eventos de rato
 */
void mouse_handler(MouseEvent me) {
	if (game_over) return;
	 
	
	// verificar se o botão de verificação de jogada está premido 
	if (bt_selected(bt_check, me.x, me.y)) {
		
		if 	((me.state == BUTTON_RELEASED ) &&
		    cv_is_filled(tries[currTry].code)) { // processa a jogada  caso esteja completa

			check_play();	// é preciso processar o resultado retornado pela função
			
			// A completar...
				 
		}
		bt_draw(bt_check, me.state);
		return; // evento processado!
	}
		
	if (me.type == MOUSE_BUTTON_EVENT && 
		me.button == BUTTON_LEFT 	  && 
		me.state == BUTTON_PRESSED) {
		
			
		
		// A completar
				
		 
	}
}

void timer_handler() {
	// A implementar
}


int main() {
	irandom_init();
	
	graph_init();
	
	draw_background();
	
	board_init();

	board_draw();
	 		
	graph_regist_mouse_handler(mouse_handler);
	graph_regist_timer_handler(timer_handler, 1000);
	graph_start();
}
