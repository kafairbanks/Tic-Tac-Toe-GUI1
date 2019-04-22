package rules;

import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.*;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;
import javafx.scene.text.Text;
import javafx.scene.transform.Rotate;
import javafx.stage.Stage;
import javafx.util.Duration;
import splash.Splash;
import board.Board;

import java.io.IOException;

public class Rules {

    private static Stage window;
    private static Scene rule1;
    private static Scene rule2;
    private static Scene rule3;
    private static Scene rule4;


    public static void displayRules() {
        window = new Stage();
        window.setMinWidth(600);
        window.setMinHeight(550);

        // set up scenes
        rule1 = createOne();
        rule2 = createTwo();
        rule3 = createThree();
        rule4 = createFour();
        rule1.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        rule2.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        rule3.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        rule4.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());


        window.setOnCloseRequest(e -> {
            e.consume();
            if ( ConfirmBox.display("Confirmation", "Are you sure you want to exit?"))
                window.close();
        });


        window.setTitle("Rules");
        window.setScene(rule1);
        window.show();
    }

    // X or O
    private static Scene createOne()  {
        // set overall layout to embed into
        BorderPane layout = new BorderPane();
        layout.setPadding(new Insets(25,25,25,25));

        // set top box
        VBox top = new VBox();
        top.setAlignment(Pos.CENTER);

        // create the rule and words for screen
        Label title = new Label("Rule 1:");
        title.setId("actiontarget");
        Label ruleLabel = new Label("Select to either be X's or O's . If you select X, you");
        Label ruleLabel2 = new Label("will go first. If you select O you will go second.");
        top.getChildren().addAll(title, ruleLabel, ruleLabel2);

        // set bot box
        HBox bot = new HBox(180);
        bot.setAlignment(Pos.CENTER);

        // set left box
        VBox left = new VBox(10);
        left.setAlignment(Pos.CENTER);

        // create the 'O' animations
        Circle outerCircle = new Circle();
        outerCircle.setRadius(90);
        Circle innerCircle = new Circle();
        innerCircle.setRadius(70);
        Shape oShape = Shape.subtract(outerCircle,innerCircle);
        oShape.setId("actiontarget");

        // create the 'X' animations
        Rectangle rect1 = new Rectangle(200,20);
        rect1.setX(-110); rect1.setY(-10);
        Rectangle rect2 = new Rectangle(200,20);
        rect2.setX(-100);
        Rotate neg45 = new Rotate(-45); Rotate pos45 = new Rotate(45);
        rect1.getTransforms().add(neg45); rect2.getTransforms().add(pos45);
        Shape xShape = Shape.union(rect1, rect2);
        xShape.setId("actiontarget");

        HBox center = new HBox(80);
        center.setAlignment(Pos.CENTER);
        center.getChildren().addAll(xShape,oShape);




        // create all buttons
        Button nextButton, mainButton, skipButton;

        nextButton = new Button("Next");
        mainButton = new Button("Main Menu");
        skipButton = new Button("Skip Rules");

        nextButton.setOnAction(e -> window.setScene(rule2));
        skipButton.setOnAction(e -> window.setScene(rule4));
        mainButton.setOnAction(e -> {
            window.close();
            try {
                Splash.displaySplash();
            }
            catch (IOException excp) { System.out.println("Error: IOException caught in Rules.java.");}
        });

        bot.getChildren().addAll(mainButton, skipButton, nextButton);

        layout.setTop(top);
        layout.setBottom(bot);
        layout.setCenter(center);

        Scene scene = new Scene(layout, 850, 550);
        return scene;

    }

    // board layout
    private static Scene createTwo() {
        // set overall layout to embed into
        BorderPane layout = new BorderPane();
        layout.setPadding(new Insets(25,25,25,25));

        // set top box
        VBox top = new VBox();
        top.setAlignment(Pos.CENTER);

        // create the rule and words for screen
        Label title = new Label("Rule 2:");
        title.setId("actiontarget");
        Label ruleLabel = new Label("The game is (4x4x4) Tic-Tac-Toe... aka 3-D Tic-Tac-Toe. The boards");
        Label ruleLabel2 = new Label("are oriented with the left most layer being the top and the right most");
        Label ruleLabel3 = new Label("layer being the bottom. In other words, the planes lined up left to right");
        Label ruleLabel4 = new Label("on the screen go top to bottom on the game board.");
        top.getChildren().addAll(title, ruleLabel, ruleLabel2, ruleLabel3, ruleLabel4);

        // set bot box
        HBox bot = new HBox();
        bot.setAlignment(Pos.CENTER);
        bot.setSpacing(180);

        // set center

        // first the game board
        Button[][][] gameButtons = new Button[4][4][4];
        GridPane gameGrid = new GridPane();
        gameGrid.setHgap(9); gameGrid.setVgap(9);
        Board.createButtons(gameGrid, gameButtons);
        Board.createLines(gameGrid);
        gameGrid.setAlignment(Pos.CENTER);

        // labels for the panes will go in a GridPane()
        GridPane planeNames = new GridPane(); planeNames.setAlignment(Pos.CENTER); planeNames.setHgap(5);
        Label plane1 = new Label("Top Layer"); plane1.setId("actiontarget");
        Label plane2 = new Label("Top Middle Layer"); plane2.setId("actiontarget");
        Label plane3 = new Label("Bottom Middle Layer"); plane3.setId("actiontarget");
        Label plane4 = new Label("Bottom Layer"); plane4.setId("actiontarget");
        planeNames.add(plane1, 0, 0);
        planeNames.add(plane2, 23, 0);
        planeNames.add(plane3, 36, 0);
        planeNames.add(plane4, 51, 0);


        // overall structure is VBox()
        VBox center = new VBox(20); center.setAlignment(Pos.CENTER);
        center.getChildren().addAll(gameGrid, planeNames);

        // create all buttons
        Button nextButton, prevButton, skipButton;

        nextButton = new Button("Next");
        prevButton = new Button("Back");
        skipButton = new Button("Skip Rules");

        prevButton.setOnAction(e -> window.setScene(rule1));
        nextButton.setOnAction(e -> window.setScene(rule3));
        skipButton.setOnAction(e -> window.setScene(rule4));
        bot.getChildren().addAll(prevButton, skipButton, nextButton);

        layout.setTop(top);
        layout.setBottom(bot);
        layout.setCenter(center);

        Scene scene = new Scene(layout, 850, 550);
        return scene;
    }

    // get four in a row
    private static Scene createThree() {
        // set overall layout to embed into
        BorderPane layout = new BorderPane();
        layout.setPadding(new Insets(25,25,25,25));

        // set top box
        VBox top = new VBox();
        top.setAlignment(Pos.CENTER);

        // create the rule and words for screen
        Label title = new Label("Rule 3:");
        title.setId("actiontarget");
        Label ruleLabel = new Label("Try to get four either X's or O's in a row. Remember that this");
        Label ruleLabel2 = new Label("game is a (4x4x4) game of Tic-Tac-Toe. This means the game is 3-D.");
        Label ruleLabel3 = new Label("So you can get 4 in a row going through the different planes.");
        top.getChildren().addAll(title, ruleLabel, ruleLabel2, ruleLabel3);

        // set bot box
        HBox bot = new HBox();
        bot.setAlignment(Pos.CENTER);
        bot.setSpacing(180);

        // create all buttons
        Button nextButton, prevButton, skipButton;

        // set center

        // first the game board
        Button[][][] gameButtons = new Button[4][4][4];
        GridPane gameGrid = new GridPane();
        gameGrid.setHgap(9); gameGrid.setVgap(9);
        Board.createButtons(gameGrid, gameButtons);
        Board.createLines(gameGrid);
        gameGrid.setAlignment(Pos.CENTER);

        Board.setButton(0, gameButtons); Board.setButton(16, gameButtons);
        Board.setButton(32, gameButtons); Board.setButton(48, gameButtons);

        FadeTransition fadeOut = new FadeTransition(Duration.seconds(2.0),gameGrid);
        fadeOut.setFromValue(1.0); fadeOut.setToValue(0); fadeOut.setAutoReverse(true); fadeOut.setDelay(Duration.seconds(5.0));
        fadeOut.play();


        GridPane gameGrid2 = new GridPane();
        Button[][][] gameButtons2 = new Button[4][4][4];
        gameGrid2.setHgap(9); gameGrid2.setVgap(9); gameGrid2.setAlignment(Pos.CENTER);
        Board.createButtons(gameGrid2, gameButtons2);
        Board.createLines(gameGrid2);
        Board.setButton(0, gameButtons2); Board.setButton(21, gameButtons2);
        Board.setButton(42, gameButtons2); Board.setButton(63, gameButtons2);
        gameGrid2.setOpacity(0.0);


        FadeTransition fadeIn = new FadeTransition(Duration.seconds(2.0),gameGrid2);
        fadeIn.setFromValue(0); fadeIn.setToValue(1.0); fadeIn.setDelay(Duration.seconds(6.5));
        fadeIn.play();

        VBox center = new VBox(0);
        center.getChildren().addAll(gameGrid, gameGrid2);


        nextButton = new Button("Next");
        prevButton = new Button("Back");
        skipButton = new Button("Skip Rules");

        prevButton.setOnAction(e -> window.setScene(rule2));
        nextButton.setOnAction(e -> window.setScene(rule4));
        skipButton.setOnAction(e -> window.setScene(rule4));
        bot.getChildren().addAll(prevButton, skipButton, nextButton);

        layout.setTop(top);
        layout.setBottom(bot);
        layout.setCenter(center);



        Scene scene = new Scene(layout, 850, 550);
        return scene;
    }

    // have fun!
    private static Scene createFour() {
        // set overall layout to embed into
        BorderPane layout = new BorderPane();
        layout.setPadding(new Insets(25,25,25,25));

        // set top box
        VBox top = new VBox();
        top.setAlignment(Pos.CENTER);

        // create the rule and words for screen
        Label title = new Label("Rule 4:");
        title.setId("actiontarget");
        Label ruleLabel = new Label("Try to beat the computer before it beats you!");
        top.getChildren().addAll(title, ruleLabel);

        // set bot box
        HBox bot = new HBox();
        bot.setAlignment(Pos.CENTER);
        bot.setSpacing(180);

        // create all buttons
        Button mainButton, prevButton;

        // create center message
        Label endMsg = new Label("Have fun!!!");
        endMsg.setId("msg");
        VBox center = new VBox(20);
        center.setAlignment(Pos.CENTER);
        center.getChildren().add(endMsg);


        Button toGameButton = new Button("Go To Game!");

        mainButton = new Button("Main Menu");
        prevButton = new Button("Back");

        prevButton.setOnAction(e -> window.setScene(rule3));
        toGameButton.setOnAction(e -> {
            window.close();
            Board.displayBoard();
        });

        mainButton.setOnAction(e -> {
            window.close();
            try {
                Splash.displaySplash();
            }
            catch (IOException excp) { System.out.println("Error: IOException caught in Rules.java.");}
        });

        bot.getChildren().addAll(prevButton, toGameButton, mainButton);

        layout.setTop(top);
        layout.setBottom(bot);
        layout.setCenter(center);

        Scene scene = new Scene(layout, 850, 550);
        return scene;
    }


}
