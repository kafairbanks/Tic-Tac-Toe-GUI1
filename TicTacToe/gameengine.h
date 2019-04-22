#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "score.h"
#include "board.h"
#include "ui.h"
#include "Computer.h"

const string SCOREFILE = "TopScores.txt"; // name of .txt file that stores high scores

static WINDOW* win;
static UI* ui;
static Computer* computer;

class GameEngine {

	bool quit = false;
  	bool won = false;	
	void EndGame();
	void GameLoop();

	public:
	void StartGame();

	GameEngine();
};

#endif
