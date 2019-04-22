#include <iostream>
#include <vector>
#include "Computer.h"
using namespace std;

//wrapper to abstract AI calling
class ComputerWrapper {
    public:
        //stores the state of the board
        static vector<vector<vector<char> > > board;
        //creates the 
        static Computer* computer;    

        //calls the computer to make a decision based on playerMove 
        int computerCall( int (&returnMoves)[6], int playerMove );  
        //the game is over, reset the board state and clear the computer/minimax tree
        void resetComputer();   
        
        ComputerWrapper() {}
        
    private:
        vector<int> indexToPoint(int p);

        int pointToIndex(vector<int> v);

        vector<vector<int>> checkWin(vector<vector<vector<char>>> board, int index);
        
        vector<int> playComputer(int humanMove);        
        
};