//
//  main.cpp
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/23/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#include <iostream>
#include <vector>
#include "ComputerWrapper.h"
#include "Computer.h"
using namespace std;

vector<vector<vector<char>>> ComputerWrapper::board(4, vector<vector<char> >(4, vector<char>(4, ' ')));
Computer* ComputerWrapper::computer = new Computer(board);  

void ComputerWrapper::resetComputer(){
    board = vector<vector<vector<char>>>(4, vector<vector<char> >(4, vector<char>(4, ' ')));
    delete computer;
    computer = new Computer(board); 
}

vector<int> ComputerWrapper::indexToPoint(int p) {
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

int ComputerWrapper::pointToIndex(vector<int> v) {
    int x = v.at(0);
    int y = v.at(1);
    int z = v.at(2);
    
    return x + 4*y + 16*z;
}

vector<vector<int>> ComputerWrapper::checkWin(vector<vector<vector<char>>> board, int index) {    
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

vector<int> ComputerWrapper::playComputer(int humanMove) {
    //int humanMove = 0;
    vector<vector<int> > winningMove;
    
    vector<int> returnMoves (6);
    
    //while(true) {
        //cout << "Enter index: ";
        //cin >> humanMove;
        vector<int> move = indexToPoint(humanMove);
        board[move.at(0)][move.at(1)][move.at(2)] = 'X';
        
        //cout << "(" << move.at(0) << ", " << move.at(1) << ", " << move.at(2) << ")" << endl;
        //cout << humanMove << endl;
        
        winningMove = checkWin(board, humanMove);
        //if player won
        if (winningMove.size() == 4) {
            returnMoves[0]= -1;
            returnMoves[5]= 1;          //game is won
            for (int i = 0; i < 4; i++){
                returnMoves[i+1] = pointToIndex(winningMove[i]);
            }
            return returnMoves;
        }
        
        computer->update(move);
        int computerMove = computer->computerMove();
        move = indexToPoint(computerMove);
        board[move.at(0)][move.at(1)][move.at(2)] = 'O';
        
        /*
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
        */
        winningMove = checkWin(board, computerMove);
        
        returnMoves[0] = computerMove;
        if (winningMove.size() == 4){
            returnMoves[5]= 1; 
            for (int i = 0; i < 4; i++){
                returnMoves[i+1] = pointToIndex(winningMove[i]);
            }
            return returnMoves;
        }
        return returnMoves;   
    //}
}

int ComputerWrapper::computerCall( int (&returnMoves)[6], int playerMove ){
    vector<int> moves{6, 0}; 
    moves = playComputer(playerMove);
    copy(moves.begin(), moves.end(), returnMoves);
    
    return 0;
}
