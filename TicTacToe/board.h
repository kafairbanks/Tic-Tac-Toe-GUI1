#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {		

	public:
	vector<char> moves;
	vector< vector<int> > winningMove;

	char player_one_token = 'X';
	char player_two_token = 'O';

	bool playerTurn = true;

	pair<int,int> board_pos;

	void DrawBoard();		// draw entire board
	void DrawSingleGrid(int pos_r, int pos_c, int num_grid);  // draw one of four grids

	string GetRow(int num_grid, int num_row);  // use the map 'moves' to populate board
	string GetDivider();	// function to draw divider within the grid
	
	bool ValidMove(int row, int col);
	int TranslateToIndex(int row, int col);

	vector<int> indexToPoint(int p);
	vector<vector<int>> checkWin(vector<vector<vector<char>>> board, int index);
	vector<int> GetAbsolutePoint(vector<int> point);

	void ClearBoard();

	Board();

};

#endif


