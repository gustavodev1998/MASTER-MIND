 
// Constantes de configuração

#define BOARD_BACK_COLOR graph_rgb(100,75, 50)
#define NTRIES 8


#define BOARD_X 0
#define BOARD_Y 0
 
#define BOARD_BORDER 20
#define BOARD_WIDTH GRAPH_WIDTH
#define BOARD_HEIGHT GRAPH_HEIGHT


// buracos
#define HOLE_RADIUS 14
#define HOLE_BACK_COLOR graph_rgb(40, 15, 10) 
#define HOLE_BORDER_COLOR BOARD_BACK_COLOR

// área de tentativa

#define TRY_COLOR graph_rgb(128, 96, 65)
#define TRY_COLOR_HIDE graph_rgb(64, 48, 33)
#define TRY_BORDER 7
#define TRY_WIDTH  (TRY_BORDER + (TRY_BORDER + 2*HOLE_RADIUS)*NPLACES)
#define TRY_HEIGHT ((2*TRY_BORDER) + 2*HOLE_RADIUS)


// área de resposta

#define RESULT_BORDER  (TRY_BORDER/2)
#define RESULT_WIDTH (RESULT_BORDER + (RESULT_BORDER + 2*RESULT_HOLE_RADIUS)*NPLACES/2)
#define RESULT_HEIGHT (RESULT_BORDER + 4*(RESULT_BORDER+ RESULT_HOLE_RADIUS))
#define RESULT_HOLE_RADIUS (HOLE_RADIUS/2)

// palette de peças

#define PALETTE_BORDER TRY_BORDER
#define PALETTE_WIDTH (PALETTE_BORDER*2 + (PALETTE_BORDER + 2*HOLE_RADIUS)*(MAX_COLORS + 1))
#define PALETTE_HEIGHT TRY_HEIGHT


// relógios

#define CLOCK_COLOR_TOTAL c_green
#define CLOCK_COLOR_PARTIAL c_orange
#define CLOCK_BACK_COLOR c_dgray
#define CLOCK_HEIGHT 50

// mensagem

#define MSG_MARGIN 5
#define MSG_HEIGHT 25
#define MSG_X (BOARD_WIDTH/2 - 55)
#define MSG_Y  (BOARD_HEIGHT- 50)
