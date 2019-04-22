#include "gameengine.h"

using namespace std;

const int GRID_SPACE = 8;
const int GRID_WIDTH = 10;

const int BOARD_START_ROW = 3;
const int BOARD_START_COL = 2;

// default constructor
Board::Board(){

	moves.resize(64);
	board_pos = make_pair(0,0);
	
	moves[0]= 'X';
	DrawBoard();
	moves[5] = 'O';
	napms(1000);
	DrawBoard();
	moves[16] = 'X';
	napms(1000);
	DrawBoard();
	moves[63] = 'O';
	napms(1000);
	DrawBoard();
	moves[31] = 'X';
	napms(1000);
	DrawBoard();
	moves[25] = 'O';
	napms(1000);
	DrawBoard();
	moves[32] = 'X';
	napms(1000);
	DrawBoard();
	moves[33] = 'O';
	napms(1000);
	DrawBoard();
	moves[48] = 'X';
	
};

// draw board onscreen
void Board::DrawBoard(){
	ui->PrintToScreen(20, 0, "Please use the arrows to select your block");
	ui->PrintToScreen(21, 0, "Enter to select your block");
	ui->PrintToScreen(22, 0, "Press 'q' to quit anytime");
	for(int i = 0; i < 4; ++i){
		DrawSingleGrid(BOARD_START_ROW, BOARD_START_COL + i * GRID_WIDTH + i * GRID_SPACE, i);
	}

}

// draws a cross section of the board
void Board::DrawSingleGrid(int pos_r, int pos_c, int num_grid){
	
	int cur_x, cur_y;
	getyx(win, cur_y, cur_x);

	ui->PrintToScreen(pos_r,pos_c, GetRow(num_grid, 0).c_str());
	ui->PrintToScreen(pos_r+1,pos_c, GetDivider().c_str());
	ui->PrintToScreen(pos_r+2,pos_c, GetRow(num_grid, 1).c_str());
	ui->PrintToScreen(pos_r+3,pos_c, GetDivider().c_str());
	ui->PrintToScreen(pos_r+4,pos_c, GetRow(num_grid, 2).c_str());
	ui->PrintToScreen(pos_r+5,pos_c, GetDivider().c_str());
	ui->PrintToScreen(pos_r+6,pos_c, GetRow(num_grid, 3).c_str());
}

// Get a row and place the moves in the appropriate boxes
string Board::GetRow(int num_grid, int num_row){
	string row = " ";
	for(int i = 0; i < 4; ++i){
		if(moves[i + 4 * num_row + num_grid * 16] != '\0'){ 
			row = row + moves[i + 4 * num_row + num_grid * 16];
		} else {
			row = row + ' ';
		}
		if(i != 3)
			row = row + " | ";
	}

	return row;
}
void Board::ClearBoard(){
	for(int i = 0; i < 64; ++i)
		moves[i] = '\0';
}
// Draw a divider between each row
string Board::GetDivider(){
	string div = "";
	for(int i = 0; i < 15; ++i)
		div += '-';
	return div;
}

bool Board::ValidMove(int row, int col){

	int index = TranslateToIndex(row, col);
	if (moves[index] == '\0') {
		moves[index] = player_one_token;
		DrawBoard();
		return true;
	}
	else
		return false;
}

vector<int> Board::GetAbsolutePoint(vector<int> point){
	// BOARD_START_ROW, BOARD_START_COL + i * GRID_WIDTH + i * GRID_SPACE, i

	int r, c, z;
	r = BOARD_START_ROW + point[1] * 2;
	c = BOARD_START_COL + point[2] * GRID_WIDTH + point[2] * GRID_SPACE + 4 * point[0]	;
	z = point[2];

	vector<int> absolutePoint;
	absolutePoint.push_back(r);
	absolutePoint.push_back(c);
	return absolutePoint;
}

int Board::TranslateToIndex(int row, int col){
	int num_grid = col / 4;
	int index = row * 4 + num_grid * 16 + (col % 4);
	return index;
}

vector<int> Board::indexToPoint(int p) {
    vector<int> v = vector<int>(3);
    if (p >= 0 && p < 64) {
        v.at(2) = p/16;
        p = p % 16;
        v.at(1) = p/4;
        p = p % 4;
        v.at(0) = p;
        
        return v;
    }
    
    return vector<int>(0);
}

vector<vector<int>> Board::checkWin(vector<vector<vector<char>>> board, int index) {
	if (index < 0 || index > 63) {
        return { { } };
    }
    
    vector<int> point = indexToPoint(index);
    int x = point[0];
    int y = point[1];
    int z = point[2];
    char piece = board[x][y][z];
    if (piece == ' ') return { { } };
    
    int matches = 0;
    vector<vector<int>> v;
    //check row
    for (int i = 0; i < 4; i++) {
        if (board[i][y][z] == piece) matches++;
        if (matches == 4) {
            //return indices of entire row
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, y, z };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    //check column
    for (int i = 0; i < 4; i++) {
        if (board[x][i][z] == piece) matches++;
        if (matches == 4) {
            //return indices of entire column
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { x, j, z };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    //check down z
    for (int i = 0; i < 4; i++) {
        if (board[x][y][i] == piece) matches++;
        if (matches == 4) {
            //return indices of entire z
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { x, y, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    //Check XY Diagonals
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i][z] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, j, z };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][3 - i][z] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, 3 - j, z };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    //Check XZ Diagonals
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][y][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, y, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][y][3 - i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, y, 3 - j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    //Check YZ Diagonals
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[x][i][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { x, j, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[x][i][3 - i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { x, j, 3 - j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    //Check True Diagonals
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, j, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[3 - i][i][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { 3 - j, j, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][3 - i][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { j, 3 - j, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    matches = 0;
    for (int i = 0; i < 4; i++) {
        if (board[3 - i][3 - i][i] == piece) matches++;
        if (matches == 4) {
            //return indices
            for (int j = 0; j < 4; j++) {
                vector<int> winningPoint = { 3 - j, 3 - j, j };
                v.push_back(winningPoint);
            }
            return v;
        }
    }
    
    return { { } };
}

