#include <stdlib.h>
#include <time.h>
#include  "utils.h"

void irandom_init() {	
	srand(time(NULL));
}


int irandom(int li, int ls) {
	return rand() % (ls -li +1) + li;
}
