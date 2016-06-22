#include <stdio.h>
#include "game.h"
#include "SDL.h"

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

int main(int, char**) {
	Game game;
	return 0;
}
