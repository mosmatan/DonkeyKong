#include "Game.h"


int main() {
	bool end =false;
	do{
		::donkeykong::Game game;
		end  = game.run();
	}while (end == true);

	return 0;
}