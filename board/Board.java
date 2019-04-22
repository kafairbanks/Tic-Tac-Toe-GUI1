package board;
 
import java.util.Arrays;
import java.io.IOException;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Separator;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.stage.Stage;
import jcomputer.ComputerJNI;
import rules.ConfirmBox;
import splash.Splash;
import gameover.GameOver;

public class Board {

	public static char[] moves = new char[64];

    public static boolean won = false; 
    
	private static Stage gameStage;
	private static Scene scene;
	
	private static int buttonSize = 20;
	private static Button[][][] gameButtons = new Button[4][4][4];
	private static Separator[] gameSep = new Separator [24];
	private static GridPane grid = new GridPane();
	
    public static void main(String[] args) {
    	displayBoard();
    }
	
	public static void displayBoard() {
		gameStage = new Stage();

        gameStage.setOnCloseRequest(e -> {
            e.consume();
            if ( ConfirmBox.display("Confirmation", "Are you sure you want to exit?"))
                gameStage.close();
        });
		
		
		Arrays.fill(moves, ' ');
		
		gameStage.setTitle("Board");
	        
        grid.getStyleClass().add("bg");
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(9);
		grid.setVgap(9);

		grid.setPadding(new Insets(5, 5, 5, 5));	//margins around whole grid

		Text scenetitle = new Text("Tic-Tac-Quatro");
		scenetitle.setId("welcome-text");
		//scenetitle.(Pos.CENTER);
        createButtons(grid, gameButtons);	//creates and add buttons to the grid
        createLines(grid);
        
        BorderPane pane = new BorderPane();
        pane.setCenter(grid);
        pane.setTop(scenetitle);
        BorderPane.setMargin(scenetitle, new Insets(20, 20, 20, 20));
        BorderPane.setAlignment(scenetitle, Pos.CENTER);
        
		scene = new Scene(pane, 850, 550);
		
		gameStage.setScene(scene);
		scene.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
		gameStage.show();
	    }
	
    //create the buttons for the board with own identifier and calls the AI code when pressed, also checks if game is won
	public static void createButtons(GridPane grid, Button[][][] gameButtons) {
		
        for(int board=0; board<4; board++) {

            for(int row=0; row<4; row++) {
            	
            	for (int column=0; column<4; column++) {

	                gameButtons[board][row][column] = new Button();
	                
	                Button currentButton = gameButtons[board][row][column];
	                
	                int currentIndex = (board*16) + (row*4) + column;
	                String currentButtonText = Character.toString(moves[currentIndex]);
	                
	                currentButton.setText(currentButtonText);
	                currentButton.setMinSize(buttonSize, buttonSize);
					currentButton.setMaxSize(buttonSize*2, 2*buttonSize);
					currentButton.setPrefSize(buttonSize, buttonSize);
					currentButton.setStyle(String.format("-fx-font-size: %dpx;", (int)(0.45 * buttonSize)));

	                //sets what this button does when pressed
                	currentButton.setOnAction((ActionEvent event) -> {
                		if (" ".equals(currentButton.getText())) {
                        	currentButton.setText("X");
                        	moves[currentIndex] = 'X';
                            
                            //this calls a java wrapper for JNI that in turn calls C++ wrapper that calls all AI functions
                            //returns an int[], int[0] is the computer's move (-1 if the player has already won with their move)
                            //int[1-4] returns what moves make up the winning four in a row, if any
                            //int[5] return 1 if the game is won, 0 otherwise 
                            int[] computerReturned = ComputerJNI.javaComputer(currentIndex);

                            int boardLoc = computerReturned[0] / 16;
                            int rowLoc = (computerReturned[0]  - (boardLoc * 16)) / 4;
                            int colLoc = (computerReturned[0] - (boardLoc*16) - (rowLoc*4)) % 4;

                            //player won
                            if ((computerReturned[5] == 1)){
                                //player won 
                                if ((computerReturned[0] == -1)){
                                    won = true;
                                }
                                //computer won
                                else {
                                    gameButtons[boardLoc][rowLoc][colLoc].setText("O");
                                    moves[computerReturned[0]] = 'O';
                                }
                                //now need to do end of game operations
                                try{
                                    //need to pass into the minmax 64 to reset itself for play agains
                                    ComputerJNI.javaComputer(64);
                                    gameStage.close();
                                    GameOver.displayGameOver();
                                }
                                catch (IOException ex) {
                                    System.out.println(ex);
                                }
                            }
                            else{                         
                                gameButtons[boardLoc][rowLoc][colLoc].setText("O");
                                moves[computerReturned[0]] = 'O';
                            }
  	                    } 
                    });
                	//every other column/row, with spacing of 2 between boards
                	grid.add(currentButton, (((column + (board*6)) * 2)+2), row*2 + 2);
            	}
            }
        } 
	}
	
	//24 lines, 6 per board
	public static void createLines(GridPane grid) {
		for (int board=0; board<4; board++) {
			for (int i=0; i<3; i++) {					
					Separator currentSep = new Separator(Orientation.HORIZONTAL);
					gameSep[((board * 6) + i)] = currentSep;
			        GridPane.setColumnSpan(currentSep, 11);
			        grid.add(currentSep,(board*12), i*2+3);
			        
			        Separator vertSep =new Separator(Orientation.VERTICAL);
			        gameSep[((board * 6) + i + 3)] = vertSep;
			        //vertSep.setValignment(VPos.CENTER);
			        GridPane.setRowSpan(vertSep, 11);
			        grid.add(vertSep, (board*12)+i*2+3, 0);
			}
		}
	
	}

	public static int[] toIndice(int move) {
        int board = (move / 16);
        int row = (move - (board*16)) /4;
        int col = (move - (board*16) - (row*4)) % 4;
        int[] movePos = new int[3];
        movePos[0] = board;
        movePos[1] = row;
        movePos[2] = col;

        return movePos;
    }

    public static void setButton(int move, Button[][][] gameButtons) {
        int[] position = toIndice(move);
        Button curr = gameButtons[position[0]][position[1]][position[2]];
        curr.setText("X");
        return;
    }


}




