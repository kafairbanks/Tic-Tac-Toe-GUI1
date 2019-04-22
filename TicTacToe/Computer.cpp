//
//  Computer.cpp
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/30/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#include <vector>
#include <iostream>
#include "Computer.h"
#include "MinimaxTree.h"
using namespace std;

Computer::Computer() {
	vector<vector<vector<char> > > b(4, vector<vector<char> >(4, vector<char>(4, ' ')));
	board = b;
    tree = new MinimaxTree(b);
}

int Computer::pointToIndex(vector<int> v) {
    int x = v.at(0);
    int y = v.at(1);
    int z = v.at(2);
    
    return x + 4*y + 16*z;
}

// To update tree with human's move
void Computer::update(vector<int> move, char humanChar) {
	board[move.at(0)][move.at(1)][move.at(2)] = humanChar;
    tree->update(move, humanChar);
    return;
}

// returns the index of the position the computer wants to place its character on
int Computer::computerMove(char humanChar) {
    vector<int> move = tree->getMove(humanChar);
	
	if(humanChar == 'X') {
		board[move.at(0)][move.at(1)][move.at(2)] = 'O';
		tree->update(move, 'O');
	}
    else {
		board[move.at(0)][move.at(1)][move.at(2)] = 'X';
		tree->update(move, 'X');
	}
    
    return pointToIndex(move);
}
