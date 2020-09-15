/*
 * Progaram para testar o componente checkbox
 * 
 * build: gcc -o box_test -Wall box_test.c components.c -lpg -lm
 */
 

#include <pg/graphics.h>
#include <stdbool.h>

#include "components.h"



Button bt_check;
CheckBox bx;
bool to_show = false;

int size = SMALL_FONT;


void timer_handler() {
	if (to_show ) {
		to_show = false;
		cbox_draw(bx);
	 
	}
	else {
		to_show = true;
		cbox_hide(bx);
		
	}
	
}


void next_size() {
	if (size == SMALL_FONT) size = MEDIUM_FONT;
	else if (size == MEDIUM_FONT) size = LARGE_FONT;
	else size = SMALL_FONT;
}

void mouse_handler(MouseEvent me) {
 
	if (bt_selected(bt_check, me.x, me.y)) {
		if (me.state == BUTTON_RELEASED) {
			next_size();
			cbox_hide(bx);
			bx = cbox_create(100,100, "Teste", size, c_blue, c_black, c_white);
		}
		bt_draw(bt_check, me.state);
		return;
		
	}
					
	if (me.type == MOUSE_BUTTON_EVENT && 
		me.state == BUTTON_PRESSED &&
		me.button == BUTTON_LEFT) {
		
		if (cbox_selected(bx, me.x, me.y)) {
			bx = cbox_toggle(bx);
			cbox_draw(bx);
			
			if (cbox_is_checked(bx))
				bt_check = bt_set_enable(bt_check, true);
			else
				bt_check = bt_set_enable(bt_check, false);
		}
		
			
	}
}

int main() {
	graph_init();
	
	bx = cbox_create(100,100, "Teste", SMALL_FONT, c_blue, c_black, c_white);
	
	bt_check = bt_create(400,100, "Size", c_red);
	bx.checked = true;			
	cbox_draw(bx);
	bt_draw(bt_check, BUTTON_RELEASED);
	graph_regist_timer_handler(timer_handler, 500);
	graph_regist_mouse_handler(mouse_handler);
	graph_start();
	return 0;
}
