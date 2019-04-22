package splash;

import java.util.Vector;
import java.io.IOException;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Font;
import javafx.scene.effect.DropShadow;
import javafx.scene.paint.Color;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.stage.Stage;
import rules.ConfirmBox;
import rules.Rules;


public class Splash {

    private static Stage window;
    private static Scene firstScene;
    
    public static String currPlayer;

    public static void displaySplash() throws IOException {
        window = new Stage();
        window.setMinWidth(600);
        window.setMinHeight(550);
        window.setTitle("Tic-Tac-Quatro");

        window.setOnCloseRequest(e -> {
            e.consume();
            if ( ConfirmBox.display("Confirmation", "Are you sure you want to exit?"))
                window.close();
        });
        
        // Scene 1 for game menu
        GridPane grid = new GridPane();
        grid.getStyleClass().add("bg");
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(5, 5, 5, 5));
		
		Text scenetitle = new Text("Tic-Tac-Quatro");
		scenetitle.setId("welcome-text");
		grid.add(scenetitle, 0, 0, 1, 1);
		
		// Create play button
		Button btn = new Button("Play");
		HBox hbBtn = new HBox(10);
		hbBtn.setAlignment(Pos.CENTER);
		hbBtn.getChildren().add(btn);
		grid.add(hbBtn, 0, 3);
		
		final Text actiontarget = new Text();
		actiontarget.setId("actiontarget");
        grid.add(actiontarget, 0, 8);

		final Text actiontarget2 = new Text();
		actiontarget2.setId("actiontarget");
        grid.add(actiontarget2, 0, 8);
        
        // Create high scores button
        Button btn3 = new Button("High Scores");
		HBox hbBtn3 = new HBox(10);
		hbBtn3.setAlignment(Pos.CENTER);
		hbBtn3.getChildren().add(btn3);
		grid.add(hbBtn3, 0, 4);
		
		final Text actiontarget3 = new Text();
		actiontarget3.setId("actiontarget");
        grid.add(actiontarget3, 0, 8);
        
        // Create quit button
        Button btn4 = new Button("Quit Game");
		HBox hbBtn4 = new HBox(10);
		hbBtn4.setAlignment(Pos.CENTER);
		hbBtn4.getChildren().add(btn4);
		grid.add(hbBtn4, 0, 5);
		
		final Text actiontarget4 = new Text();
		actiontarget4.setId("actiontarget");
        grid.add(actiontarget4, 0, 8);
        
		Label madeBy = new Label("Made by Team 13:");
		HBox box1 = new HBox(10);
		box1.setAlignment(Pos.CENTER);
		box1.getChildren().add(madeBy);
		grid.add(box1, 0, 10);
        
		Label name1 = new Label("Ryan Bilek");
		HBox box2 = new HBox(10);
		box2.setAlignment(Pos.CENTER);
		box2.getChildren().add(name1);
		grid.add(box2, 0, 11);
		
		Label name2 = new Label("Kathryn Fairbanks");
		HBox box3 = new HBox(10);
		box3.setAlignment(Pos.CENTER);
		box3.getChildren().add(name2);
		grid.add(box3, 0, 12);
		
		Label name3 = new Label("Karsen Keith");
		HBox box4 = new HBox(10);
		box4.setAlignment(Pos.CENTER);
		box4.getChildren().add(name3);
		grid.add(box4, 0, 13);
		
		Label name4 = new Label("Shawn Simon");
		HBox box5 = new HBox(10);
		box5.setAlignment(Pos.CENTER);
		box5.getChildren().add(name4);
		grid.add(box5, 0, 14);

		Scene scene = new Scene(grid, 850, 550);
		firstScene = scene;
		
		// Scene 2 to get initials for high score
		GridPane grid2 = new GridPane();
		grid2.getStyleClass().add("bg");
		grid2.setAlignment(Pos.CENTER);
		grid2.setHgap(10);
		grid2.setVgap(10);
		grid2.setPadding(new Insets(5, 5, 5, 5));

		Label initials = new Label("Initials:");
		grid2.add(initials, 0, 0);

		TextField userTextField = new TextField();
		grid2.add(userTextField, 1, 0);
		
		// Create enter button
        Button btn5 = new Button("Enter");
		HBox hbBtn5 = new HBox(10);
		hbBtn5.setAlignment(Pos.BOTTOM_CENTER);
		hbBtn5.getChildren().add(btn5);
		grid2.add(hbBtn5, 1, 4);
		
		final Text actiontarget5 = new Text();
		actiontarget5.setId("actiontarget");
        grid2.add(actiontarget5, 0, 8, 2, 1);
        
        // Create back button
        Button btn6 = new Button("Main Menu");
		HBox hbBtn6 = new HBox(10);
		hbBtn6.setAlignment(Pos.BOTTOM_LEFT);
		hbBtn6.getChildren().add(btn6);
		grid2.add(hbBtn6, 0, 4);
		
		final Text actiontarget6 = new Text();
		actiontarget6.setId("actiontarget");
        grid2.add(actiontarget6, 0, 8);
        
        Scene scene2 = new Scene(grid2, 850, 550);
        
    	// Scene 3 to show high scores
		GridPane grid3 = new GridPane();
		grid3.getStyleClass().add("bg");
		grid3.setAlignment(Pos.CENTER);
		grid3.setHgap(10);
		grid3.setVgap(10);
		grid3.setPadding(new Insets(5, 5, 5, 5));
		
		Text scene3title = new Text("High Scores");
		scene3title.setId("welcome-text");
		grid3.add(scene3title, 0, 0, 3, 1);
		
		Label l = new Label("Player: ");
		l.setAlignment(Pos.CENTER);
		l.getStyleClass().add("label");
		grid3.add(l, 0, 9);
		
		Label In = new Label("");
		In.setAlignment(Pos.CENTER);
		In.getStyleClass().add("label");
		grid3.add(In, 1, 9);
		
		Label Sc = new Label("");
		Sc.setAlignment(Pos.CENTER);
		Sc.getStyleClass().add("label");
		grid3.add(Sc, 2, 9);
		
		// Create Instructions button
		Button btn7 = new Button("Instructions");
		HBox hbBtn7 = new HBox(10);
		hbBtn7.setAlignment(Pos.BOTTOM_RIGHT);
		hbBtn7.getChildren().add(btn7);
		grid3.add(hbBtn7, 2, 10);

		final Text actiontarget7 = new Text();
		actiontarget7.setId("actiontarget");
		grid3.add(actiontarget7, 0, 12, 2, 2);

		// Create back button
		Button btn8 = new Button("Main Menu");
		HBox hbBtn8 = new HBox(10);
		hbBtn8.setAlignment(Pos.BOTTOM_LEFT);
		hbBtn8.getChildren().add(btn8);
		grid3.add(hbBtn8, 0, 10, 2, 1);
		
		ScoreManager scoreManager = new ScoreManager();
		Vector<Score> scores = scoreManager.load("Highscores.txt");
		
		Scene scene3 = new Scene(grid3, 850, 550);
        
        // Create handlers for buttons
        btn.setOnAction(new EventHandler<ActionEvent>() { // Play game button
			@Override
			public void handle(ActionEvent e) {
				actiontarget2.setText("");
				actiontarget3.setText("");
				window.setScene(scene2);
			}
		});
		
		btn3.setOnAction(new EventHandler<ActionEvent>() { // High scores button
			@Override
			public void handle(ActionEvent e) {
                window.setScene(scene3);
			}
		});
		
		btn4.setOnAction(new EventHandler<ActionEvent>() { // Exit button
			@Override
			public void handle(ActionEvent e) {
				window.close();
			}
		});
        
        btn5.setOnAction(new EventHandler<ActionEvent>() { // Enter initials button
			@Override
			public void handle(ActionEvent e) {
				String input = userTextField.getText().toUpperCase();
				currPlayer = input;
				if ((input != null && !input.isEmpty()) && 
						input.length() == 3) {
					Score player = scoreManager.findScore(scores, input);
					if(player == null) {
						player = new Score(input);
						scores.add(player);
					}
						
					for(int i=0; i<scores.size(); i++) {
						if(i > 4) {
							break;
						}
						Label tempL = new Label(Integer.toString(i+1));
						tempL.setAlignment(Pos.CENTER);
						tempL.getStyleClass().add("label");
						grid3.add(tempL, 0, i+2);
						
						Label tempIn = new Label(scores.get(i).getInitials());
						tempIn.setAlignment(Pos.CENTER);
						tempIn.getStyleClass().add("label");
						grid3.add(tempIn, 1, i+2);

						Label tempScore = new Label(Integer.toString(scores.get(i).getScore()));
						tempScore.setAlignment(Pos.CENTER);
						tempScore.getStyleClass().add("label");
						grid3.add(tempScore, 2, i+2);
					}
					
					In.setText(player.getInitials());
					Sc.setText(Integer.toString(player.getScore()));
					try {
						scoreManager.save(scores, "Highscores.txt");
					} catch (IOException ex){
						System.out.println("Ripperoni");
					}

					window.setScene(scene3);
				} else {
					actiontarget5.setText("Please enter your 3 letter initials");
				}
			}
		});
		
		btn6.setOnAction(new EventHandler<ActionEvent>() { // Back to main menu from enter initials button
			@Override
			public void handle(ActionEvent e) {
				window.setScene(scene);
			}
		});

		btn7.setOnAction(new EventHandler<ActionEvent>() { // Instructions button from initials screen
			@Override
			public void handle(ActionEvent e) {
                window.close();
                Rules.displayRules();
			}
		});
		
		btn8.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) { // Back to main menu button
				In.setText("");
				Sc.setText("");
				window.setScene(scene);
			}
		});
		
		window.setScene(scene);
		scene.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
		scene2.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
		scene3.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        window.show();
    }
} 
