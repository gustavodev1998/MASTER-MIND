
// iniciar o gerador de números pseudo-aleatórios
void irandom_init();

// obter um número aleatório dentro do intervalo (fechado) especificado
int irandom(int li, int ls);
	 

// tipo para representar uma área rectangular
typedef struct {
	int width, height;
} Size;


// tipo para representar uma posição no écrâ
typedef struct {
	int x;
	int y;
} Point;

/*
 *  Calcular a distância entre dois pontos
 */
double point_distance(Point p1, Point p2);

// tipo que representa uma área rectangular
typedef struct {
	Point p;
	Size sz;
} Rect;


/* 
 * Verificar se um ponto está contido no rectângulo dado
 */
bool rect_contains(Rect r, Point p);

