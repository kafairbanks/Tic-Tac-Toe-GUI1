package gameover;

import board.Board;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.stage.Stage;
import rules.ConfirmBox;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import splash.ScoreManager;
import splash.Score;
import splash.Splash;
import javafx.scene.text.Font;

import board.Board;

import java.util.Vector;


public class GameOver{
    
    private static Stage window;
    private static Scene scene;
    
    public static void displayGameOver() throws IOException{
        window = new Stage();
        window.setMinWidth(850);
        window.setMinHeight(550);
        window.setTitle("GAME OVER");
        
        window.setOnCloseRequest(e -> {
            e.consume();
            if ( ConfirmBox.display("Confirmation", "Are you sure you want to exit?"))
                window.close();
        });
        
        GridPane grid = new GridPane();
        grid.getStyleClass().add("bg");
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(5, 5, 5, 5));
        
        Text scenetitle = new Text("GAME OVER");
        scenetitle.setId("welcome-text");
        grid.setHalignment(scenetitle, HPos.CENTER);
        grid.add(scenetitle, 0, 1, 8, 1);
        
        Label playAgain = new Label("Would you like to play again?");
        grid.setHalignment(playAgain, HPos.CENTER);
        grid.add(playAgain, 0, 30);
        
        Button yes = new Button("YES");
        HBox hbBtn = new HBox(10);
        hbBtn.setAlignment(Pos.CENTER);
        hbBtn.getChildren().add(yes);
        grid.add(hbBtn, 2, 30);
        
        final Text actiontarget = new Text();
        actiontarget.setId("actiontarget");
        grid.add(actiontarget, 0, 8);
        
        Button no = new Button("NO");
        HBox hbBtn1 = new HBox(10);
        hbBtn1.setAlignment(Pos.CENTER);
        hbBtn1.getChildren().add(no);
        grid.add(hbBtn1, 3, 30);
        
        final Text actiontarget1 = new Text();
        actiontarget1.setId("actiontarget");
        grid.add(actiontarget1, 0, 8);
        
        Label topScores = new Label("TOP SCORES");
        topScores.setId("");
        grid.setHalignment(topScores, HPos.RIGHT);
        grid.add(topScores, 0, 7);
        
        
        ScoreManager scoreManager = new ScoreManager();
        Vector<Score> scores = new Vector<Score>();
        try {
            scores = scoreManager.load("Highscores.txt");   // loads in Highscores.txt
        } catch (IOException e) {
            e.printStackTrace();
        }
        int index = 0;
        String initials = Splash.currPlayer;                // gets initials of current player
        for(int i = 0; i < scores.size(); ++i){
            if (scores.get(i).getInitials().equals(initials)) {
                index = i;                                 // gets index of current player
                break;
            }
        }
        Board board = new Board();
        boolean playerWin = board.won;
        if(playerWin)
            scores.get(index).setScore((scores.get(index).getScore() + 1));  // NEEDS TO BE SET SCORE
        else
            scores.get(index).setScore((scores.get(index).getScore()));
        
        scores = scoreManager.sort(scores);
        scoreManager.save(scores, "Highscores.txt");
        
        /***** Print TXT onto screen ******/
        try{
            FileReader fr = new FileReader("Highscores.txt");
            BufferedReader br = new BufferedReader(fr);
            
            String str;
            int i = 0;
            
            while((str = br.readLine()) != null){
                
                Label score = new Label(str);
                grid.setHalignment(score, HPos.RIGHT);
                grid.add(score, 0, 8+i);
                i++;
                if(i > 4)
                    break;
            }
            
            br.close();
        } catch (IOException e){
            e.printStackTrace();
        }
        /***** Print TXT onto screen ******/
        
        if(playerWin){
            Text outcome = new Text("YOU WON");
            outcome.setId("won");
            grid.setHalignment(outcome, HPos.CENTER);
            grid.add(outcome, 0, 20, 8, 1);
        } else {
            Text outcome = new Text("YOU LOST");
            outcome.setId("lost");
            grid.setHalignment(outcome, HPos.CENTER);
            grid.add(outcome, 0, 20, 8, 1);
        }
        
        scene = new Scene(grid, 600, 550);
        
        // Create handlers for buttons
        yes.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                window.close();
                Board.displayBoard();
            }
        });
        
        no.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                window.close();
                try {
                    Splash.displaySplash();
                } catch (IOException ex){
                    System.out.println("Ripperoni");
                }
            }
        });
        
        
        window.setScene(scene);
        scene.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        window.show();
    }
}
