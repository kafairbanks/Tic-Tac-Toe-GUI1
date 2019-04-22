#include "gameengine.h"
#include <unistd.h>

using namespace std;

const int WINDOW_WIDTH = 80;
const int WINDOW_HEIGHT = 26;

const int BOARD_OFFSET_ROW = 4;
const int BOARD_OFFSET_COL = 5;



// default constructor
UI::UI(){
	initscr();			// start curses mode
	start_color(); // used for coloring text

	// define color pairs
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	
	if(win == NULL)
		CreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, 1, 1);
	cbreak();	
	keypad(win, TRUE);
	noecho();			// don't echo() while we do getch
	board = new Board();
	wmove(win, 1,2);
}

void UI::DrawBoard(){
	board->DrawBoard();
	Refresh(); // print it on screen
};

// Player input controller and return the character pressed
char UI::HandlePlayerInput(){
	ChooseToken();
	int ch;
	int break_ch = 1;
	wmove(win,BOARD_OFFSET_ROW,BOARD_OFFSET_COL);
	
	computer = new Computer();
	board->ClearBoard();
	board->DrawBoard();
	board->board_pos.second = 0;
	board->board_pos.first = 0;
	bool player_won = false;
	bool cheatToWin = false;
	bool cat = false;
	bool firstTurn = true;
	
	for(int i=0; i<board->winningMove.size(); i++) {
		board->winningMove.pop_back();
	}

	while(break_ch != 0)
	{	
		if(board->playerTurn){
			ch = wgetch(win);
			string msg = "Character pressed is ";
			switch(ch)
			{	
				case KEY_UP: // int 259
					msg += "up ";
					if(MoveCursor(-2,0))
						board->board_pos.second -= 1;
					break;
				case KEY_DOWN: // int 258
					if(MoveCursor(2,0))
						board->board_pos.second += 1;
					msg += "down ";
					break;
				case KEY_LEFT: // int 260
					if(MoveCursor(0,-4))
						board->board_pos.first -= 1;
					msg += "left ";
					break;
				case KEY_RIGHT: // int 261
					if(MoveCursor(0,4))
						board->board_pos.first += 1;
					msg += "right ";
					break;
				case 10: // enter
					msg += "enter";
					firstTurn = false;
					if(board->ValidMove(board->board_pos.second, board->board_pos.first)){
						wattron(win, A_BOLD | COLOR_PAIR(2));
						PrintToScreen(17,0, "Legal Move", true);
						wattroff(win, A_BOLD | COLOR_PAIR(2));
						board->playerTurn = false;

						cat = true;
						break_ch = 0;
						for(int i=0; i<64; i++) {
							if(board->moves[i] != 'X' && board->moves[i] != 'O') {
								break_ch = 1;
								cat = false;
							}
						}

						int playerIndex = board->TranslateToIndex(board->board_pos.second, board->board_pos.first);
						vector<int> move = board->indexToPoint(playerIndex);
						computer->update(move, board->player_one_token);
						
						board->winningMove = board->checkWin(computer->board, playerIndex);
						
						if (board->winningMove.size() == 4) {
							break_ch = 0;
							player_won = true;
							ch = 'w';
						}
					}
					else {
						wattron(win, A_BOLD | COLOR_PAIR(3));
						PrintToScreen(17,0, "Illegal Move", true);
						wattroff(win, A_BOLD | COLOR_PAIR(3));					
					}				
					break;
				case 119:				//press 'w' to win
					break_ch = 0;
					cheatToWin = true;
					break;
				case 99:				//press 'c' to cat
					break_ch = 0;
					cat = true;
					break;
				case 113: case 81: // ascii code for 'q', and 'Q'
					break_ch = 0;
					msg += "later...press any key to continue";
					break;			
				default:
					msg += ch;
					msg += " ";
					break;
			}
			// used for debugging controls
			//PrintToScreen(15,0,msg, true);

		} else {
			// computer turn
			/*
			if(!firstTurn){
				int playerIndex = board->TranslateToIndex(board->board_pos.second, board->board_pos.first);
				vector<int> move = board->indexToPoint(playerIndex);
			
				computer->update(move, board->player_one_token);
			}
			*/
			int computerMove = computer->computerMove(board->player_one_token);
			board->moves[computerMove] = board->player_two_token;
			DrawBoard();
			Refresh();
			
			//board[move.at(0)][move.at(1)][move.at(2)] = 'O';	
			
			cat = true;
			break_ch = 0;
			for(int i=0; i<64; i++) {
				if(board->moves[i] != 'X' && board->moves[i] != 'O') {
					break_ch = 1;
					cat = false;
				}
			}	

			board->winningMove = board->checkWin(computer->board, computerMove);
			if (board->winningMove.size() == 4) break_ch = 0;

			board->playerTurn = true;
			firstTurn = false;
		}
	}
	if(board->winningMove.size() == 4 || cheatToWin)
		PrintWinningMoves(player_won, cheatToWin);
		
	if(cat) {
		PrintToScreen(1, 30, "Cat Game!", true);
		
		wattron(win, A_BOLD | COLOR_PAIR(2));
		PrintToScreen(12, 20, "Press Enter to continue...");	
		wattroff(win, A_BOLD | COLOR_PAIR(2));
		Refresh();
		int ch2 = wgetch(win);
		while(ch2 != 10)
			ch2 = wgetch(win);
	}
	
	delete(computer);
	return ch;
}

void UI::PrintWinningMoves(bool playerWon, bool cheatToWin){
	
	if(cheatToWin)
		playerWon = true;
		
	vector< vector <int> > absolutePoints;
	if(!cheatToWin){
		for(int i = 0; i < 4; ++i){
			vector<int> winningPoint;
			winningPoint.push_back(board->winningMove[i][0]);
			winningPoint.push_back(board->winningMove[i][1]);
			winningPoint.push_back(board->winningMove[i][2]);
			vector<int> absPoint = board->GetAbsolutePoint(winningPoint);
			absolutePoints.push_back(absPoint);
			string str = to_string(winningPoint[0]) + ", " + to_string(winningPoint[1]) + ", " + to_string(winningPoint[2]);
			PrintToScreen(13,i* 12, str);
		}
	}	

	// choosing red; assuming player loss
	int color = 3;
	string msg = "YOU LOSE";
	char charToPrint = board->player_two_token;
	if(playerWon){
		color = 2;
		msg = "YOU WIN";
		if(cheatToWin)
			msg += " BUT CHEATED";
		charToPrint = board->player_one_token;
	}
	
	string s(1,charToPrint);

	wattron(win, A_BOLD | COLOR_PAIR(color));

	bool alt_color = false;
	// alternate between colors based on timer
	for(int j = 0; j < 8; ++j){
		if(!cheatToWin){
			for(int i = 0; i < 4; ++i)
				PrintToScreen(absolutePoints[i][0], absolutePoints[i][1] + 1, s);
		}		
		
		PrintToScreen(1, 30, msg, true);
		
		if(!alt_color)
			wattron(win, COLOR_PAIR(1));
		else
			wattron(win, COLOR_PAIR(color));
			
		alt_color = !alt_color;
		usleep(500 * 1000);
	}
	
	wattron(win, A_BOLD | COLOR_PAIR(2));
	PrintToScreen(12, 20, "Press Enter to continue...");	
	wattroff(win, A_BOLD | COLOR_PAIR(2));
	Refresh();
	int ch = wgetch(win);
	while(ch != 10)
		ch = wgetch(win);
	
}

// Create the window and assign gameengine's static window to this
void UI::CreateWindow(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	win = local_win;
	Refresh();
}

// replaces printw with some options
void UI::PrintToScreen(int row, int column, string message, bool clear_row){

	if(clear_row)
		ClearRow(row);
		
	int cur_x, cur_y;
	getyx(win, cur_y, cur_x);
	mvwprintw(win, row + 1, column + 2, message.c_str());
	wmove(win,cur_y, cur_x);
	Refresh();
}

void UI::PrintBlankRow(int row){
	PrintToScreen(row, 0, "", true);
}

// cleaner function
void UI::ClearScreen(){
	wclear(win);
}

// Clears to end of the row minus the box
void UI::ClearRow(int row){		
	int cur_x, cur_y;
	getyx(win, cur_y, cur_x);
	wmove(win,row + 1,0);
	wclrtoeol(win);
	wmove(win,cur_y, cur_x);
	Refresh();
}

// move the cursor around the screen based off of player input
bool UI::MoveCursor(int move_y, int move_x){
	int cur_x, cur_y;
	getyx(win, cur_y, cur_x);
	if(move_x > 0 && (cur_x % 17 == 0 || cur_x % 35 == 0 || cur_x % 53 == 0))
		move_x += 2;
	else if(move_x < 0 && (cur_x % 23 == 0 || cur_x % 41 == 0 || cur_x % 59 == 0))
		move_x -= 2;
	if(cur_x + move_x < 72 && cur_y + move_y < 11 && cur_x + move_x > 4 && cur_y + move_y > 3){
		wmove(win,cur_y + move_y, cur_x + move_x);
		Refresh();
		return true;
	}
	return false;
	
}

void UI::StartUI(){
	Refresh();
	SplashScreen();
	PrintInstructions();	
}

void UI::EndUI(){
	ClearScreen();
	Refresh();
	delete(board);
	endwin();	// end curses mode
}

void UI::Refresh(){		
		box(win, '|', '*');
		wrefresh(win);
}

void UI::SplashScreen(){
	
	// ifstream input("DaugherityASCII.txt");       // Open input file
    // string line = "";
   //prints DaugherityASCII.txt to screen
   // int row = 0;
    // while(!input.eof()) {
        // getline(input, line);
        // PrintToScreen(row, 0, line.c_str());
        // ++row;
    // }
    
	
	
    // outputs title, team number, team name, team member names, and press enter to start
   wattron(win, A_BOLD);
    PrintToScreen(11,25,"3D Tic-Tac-Quatro");
    wattroff(win, A_BOLD );
    
    PrintToScreen(12,30,"Team 15:");
    PrintToScreen(13,25,"The Shape of Walter");
    PrintToScreen(14,30,"Created by:");
    PrintToScreen(15,30,"Amy Hughes");
    PrintToScreen(16,30,"Brandon Anderson");
    PrintToScreen(17,30,"Kathryn Fairbanks");
    PrintToScreen(18,30,"Roby Nkwamo");
    
    wattron(win, A_BOLD | A_BLINK | A_STANDOUT | COLOR_PAIR(2));
    PrintToScreen(20,50,"PRESS ENTER TO START");
    wattroff(win, A_BOLD | A_BLINK | A_STANDOUT | COLOR_PAIR(2));

	Refresh();
	
	DrawBoard();

    int ch = wgetch(win);                           // Wait for user input
    
    while(ch != 10) {                           // Will not change screen until "ENTER" is pressed
        ch = wgetch(win);
    }
}
void UI::ChooseToken(){
	ClearScreen();
	
	PrintToScreen(1, 20, "Would you like to be X's or O's?");
	PrintToScreen(5, 20, "Please press X or O (X goes first, O goes second)");
	int ch = wgetch(win);
	while(ch != 'x' && ch != 'o' && ch != 'X' && ch != 'O'){
		PrintToScreen(8, 30, "Try Again", true);
		ch = wgetch(win);
	}
	
	if(ch == 'o' || ch == 'O'){
		board->playerTurn = false;
		board->player_one_token = 'O';
		board->player_two_token = 'X';
	} else{
		board->playerTurn = true;
		board->player_one_token = 'X';
		board->player_two_token = 'O';
	}
	
	string s(1,ch);
	s = "You chose: " + s;
	PrintToScreen(8, 30, s, true);
	
	PrintToScreen(9, 30, "Press Enter to continue...", true);
	ch = wgetch(win);
	while(ch != 10)
		ch = wgetch(win);
		
	ClearScreen();
}
void UI::PrintInstructions(){

	int ch;
	ClearScreen();
 	wattron(win, A_UNDERLINE);
    PrintToScreen(1, 28, "Game Instructions");
    wattroff(win, A_UNDERLINE);
    
    PrintToScreen(3, 5, "This is Tic-Tac-Quatro! A game of 3-D Tic-Tac-Toe where the players");
    PrintToScreen(4, 5, "must get four in a row across the four cross sections of a 3-D cube.");
    PrintToScreen(5, 5, "Winning rows include horizontal, vertical, diagonal and those made");
    PrintToScreen(6, 5, "in 3-D space.");
    PrintToScreen(7, 30, "Good luck!");
    PrintBlankRow(8);
    
    wattron(win, A_BOLD);
    PrintToScreen(9, 30, "Controls");
    wattroff(win, A_BOLD);
    PrintToScreen(10, 5, "Use the arrows keys to move the cursor across the board.");
    PrintToScreen(11, 5, "Press 'Enter' to place your token in the corresponding box. If the move is");
    PrintToScreen(12, 5, "valid, your token will appear on the board and your turn is over.");
    PrintToScreen(13, 5, "Next, the opponent will decide and place their token in a box.");
    PrintBlankRow(14);
    
    wattron(win, A_BOLD);
    PrintToScreen(15, 30, "Win/Lose Conditions");
    wattroff(win, A_BOLD);
    PrintToScreen(16, 5, "The game is over once a player completes their row. The first player");
    PrintToScreen(17, 5, "who does is deemed victor, while the opponent is a loser.");
    PrintToScreen(18, 5, "If you win the game, you score a point. Can you reach the high score???");
    PrintBlankRow(19);
    
	wattron(win, A_BOLD | COLOR_PAIR(2));
    PrintToScreen(20, 15, "Enter your initials (3 characters only): ");
    wattroff(win, A_BOLD | COLOR_PAIR(2));

    Refresh();                                  // Print it on to the real screen
      
    for(int i=0; i<3; i++) {   	
 
      ch = wgetch(win);
    	if(ch == 10) ch = ' ';
    	
    	initials.push_back(ch);
    	
    	PrintToScreen(21, 33, initials, true);
    	
    	Refresh();
    }
    PrintToScreen(22, 25, "Press enter to continue...");
    ch = wgetch(win);
    while(ch != 10)
    	ch = wgetch(win);
    ClearScreen();
}

void UI::PrintHighScores(){

 // load current input file to scores vector
    scores = Score::load(SCOREFILE);
        
		// if this is the first time this set of initials is playing, it will add it to the scores vector
    auto it = scores.begin();
    Score::find_score(it, scores.end(), initials);
    if (it == scores.end()) {
        // append new scores object
        scores.emplace_back(initials);
    }
		      
		// saves scores vector to file in case new player
    Score::save(scores, SCOREFILE);
    
    ClearScreen();
		
	// outputs high score list
	wattron(win, A_UNDERLINE);
	PrintToScreen(2, 30, "TOP SCORES");
	wattroff(win, A_UNDERLINE);
	
	for(int i=0; i<scores.size(); i++) {
		if(i < 5) {
			string score = scores.at(i).initials.c_str();
			int points = scores.at(i).score;
			score +=  " " + to_string(points);
			PrintToScreen(4+i, 30, score);
		}
	}
	
	it = scores.begin();
	Score::find_score(it, scores.end(), initials);

	string score = it->initials.c_str();
	int points = it->score;
	score +=  " " + to_string(points);
	PrintToScreen(4+scores.size()+1, 30, score);
	      
	PrintToScreen(22, 5, "Press Enter to continue...");  
	
	int ch;                           // Wait for user input
	while(ch != 10) {                       // Will not change screen until "ENTER" is pressed
		ch = wgetch(win);
	}
	
	ClearScreen();
	
}

void UI::IncrementScores(){

	auto it = scores.begin();
  Score::find_score(it, scores.end(), initials);
  it->score++;
  
}

bool UI::AskToRetry(){
		// Play again?
		ClearScreen();
        PrintToScreen(12, 20, "Would you like to play again? [Y/N]: ");
				Refresh();
        char answer = wgetch(win);
      
       while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') {
       PrintToScreen(14,20, "Please enter either Y or N: ");
       answer = wgetch(win);
       }
       
       if (answer == 'Y' || answer == 'y') {
            return false;
       } else {
       ClearScreen();
        	
		// outputs high scores again
    	wattron(win, A_BOLD | A_BLINK);
    	PrintToScreen(20, 25, "THANKS FOR PLAYING! (:");
    	wattroff(win, A_BOLD | A_BLINK);
    
    	wattron(win, A_UNDERLINE);
		PrintToScreen(2, 30, "TOP SCORES");
		wattroff(win, A_UNDERLINE);
    	for(int i=0; i < scores.size(); i++) {
			if(i < 5) {
				string score = scores.at(i).initials.c_str();
				int points = scores.at(i).score;
				score += " " + to_string(points);
				PrintToScreen(4+i, 30, score);
			}
    	}
    	
		PrintToScreen(22, 30, "Press any key to continue...");
    	Refresh();
    	
    	wgetch(win);	// exit at any input entered
		return true;
        }
}
