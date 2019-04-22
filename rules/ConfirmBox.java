package rules;

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import splash.Splash;


public class ConfirmBox {

    private static Boolean answer;

    public static Boolean display (String title, String message){
        Stage alertWin = new Stage();
        alertWin.initModality(Modality.APPLICATION_MODAL);
        alertWin.setTitle(title);
        alertWin.setMinWidth(300);
        alertWin.setMinHeight(300);

        Label userLabel = new Label(message);
        Button yesButton = new Button("Yes");
        Button noButton = new Button("No");
        yesButton.setOnAction(e -> {
            answer = true;
            alertWin.close();
        });
        noButton.setOnAction(e -> {
            answer = false;
            alertWin.close();
        });

        VBox layout = new VBox(10);
        layout.getChildren().addAll(userLabel, yesButton, noButton);
        layout.setAlignment(Pos.CENTER);

        Scene scene = new Scene(layout);
        scene.getStylesheets().add(Splash.class.getResource("Splash.css").toExternalForm());
        alertWin.setScene(scene);
        alertWin.showAndWait();

        return answer;
    }
}
