#include "gameengine.h"



using namespace std;

int main(){

	// playing game
	GameEngine *game = new GameEngine();
	game->StartGame();
	delete(game);
	return 0;
}


