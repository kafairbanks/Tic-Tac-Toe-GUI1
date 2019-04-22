#include "gameengine.h"

// Start game and returns the character for win or lose
void GameEngine::StartGame(){

	ui = new UI();
	ui->StartUI();
	
	GameLoop();
	EndGame();
}

void GameEngine::GameLoop(){	

	while (!quit) {
		ui->PrintHighScores();
		ui->DrawBoard();
		char winLose = ui->HandlePlayerInput();
		if(winLose == 'w') {
			won = true;
		}
		else {
		 	won = false;
		}
		
		// increments high score if player won
		if(won) {
			ui->IncrementScores();
        }
		
		// saves to output file to update high score
		Score::save(ui->scores, SCOREFILE);

		quit = ui->AskToRetry();
		
	}
}



// Delete the ui and end the game
void GameEngine::EndGame(){
	ui->EndUI();
	delete(ui);
}

// default constructor
GameEngine::GameEngine () {

}
