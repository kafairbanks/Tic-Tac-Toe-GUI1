#ifndef UI_H
#define UI_H

using namespace std;

class Board;

class UI {
	
	void PrintWinningMoves(bool player_won, bool cheat_to_win);
	void ChooseToken();

	public:
	Board *board;
    string initials;
    
	vector<Score> scores;
	
	void StartUI();	// called by game engine to start UI
	void EndUI();	// called by game engine to end UI
	char HandlePlayerInput();
	void PrintToScreen(int row, int column, string message, bool clear_row = false);  // optional to clear entire row
	void CreateWindow(int height, int width, int starty, int startx);
	void ClearScreen();
	void PrintBlankRow(int row);
	void ClearRow(int row);
	bool MoveCursor(int move_x, int move_y);  // use move cursor
	void Refresh();	// used after everytime a move cursor or write to screen in order to display to window
	void DrawBoard();
	void SplashScreen();
	void PrintInstructions();
	void PrintHighScores();
	void IncrementScores();
	bool AskToRetry();
	
	// default constructor
	UI();

};

#endif

