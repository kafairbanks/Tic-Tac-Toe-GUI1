import javafx.application.Application;
import javafx.stage.Stage;
import splash.Splash;

import java.io.IOException;


public class Main extends Application {

    public static void main(String[] args) { launch(args); }

    @Override
    public void start(Stage primaryStage) {
        try {
            Splash.displaySplash();
        }
        catch (IOException e) {
            System.out.println("Error: IOException caught in Main.java.");
        }
    }
}