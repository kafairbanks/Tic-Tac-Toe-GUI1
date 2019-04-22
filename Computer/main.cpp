//
//  main.cpp
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/23/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Computer.h"
using namespace std;

vector<int> indexToPoint(int p) {
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

vector<vector<int>> checkWin(vector<vector<vector<char>>> board, int index) {
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
    
    //FIXME: Check Diagonals
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

int main(int argc, const char * argv[]) {
    vector<vector<vector<char> > > board(4, vector<vector<char> >(4, vector<char>(4, ' ')));
    Computer* computer = new Computer(board);
    int humanMove = 0;
    vector<vector<int> > winningMove;
    
    while(true) {
        cout << "Enter index: ";
        cin >> humanMove;
        vector<int> move = indexToPoint(humanMove);
        board[move.at(0)][move.at(1)][move.at(2)] = 'X';
        
        cout << "(" << move.at(0) << ", " << move.at(1) << ", " << move.at(2) << ")" << endl;
        cout << humanMove << endl;
        
        winningMove = checkWin(board, humanMove);
        if (winningMove.size() == 4) break;
        
        computer->update(move);
        int computerMove = computer->computerMove();
        move = indexToPoint(computerMove);
        board[move.at(0)][move.at(1)][move.at(2)] = 'O';
        
        for(int k=0; k<4; k++) {
            for(int j=0; j<4; j++) {
                for(int i=0; i<4; i++) {
                    if(board[i][j][k] == ' ') {
                        cout << "- ";
                    }
                    else {
                        cout << board[i][j][k] << " ";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
        
        cout << "(" << move.at(0) << ", " << move.at(1) << ", " << move.at(2) << ")" << endl;
        cout << computerMove << endl;
        
        winningMove = checkWin(board, computerMove);
        if (winningMove.size() == 4) break;
    }
    
	printf("Winning Points:\n     (%d, %d, %d), (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n",
	   winningMove[0][0], winningMove[0][1], winningMove[0][2],
	   winningMove[1][0], winningMove[1][1], winningMove[1][2], winningMove[2][0],
	   winningMove[2][1], winningMove[2][2], winningMove[3][0], winningMove[3][1], winningMove[3][2]);
    
    return 0;
}
