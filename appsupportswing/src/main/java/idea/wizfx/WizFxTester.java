
package idea.wizfx;

import java.io.IOException;

// maybe a good idea...another day.
// import org.scenicview.ScenicView;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class WizFxTester extends Application {

	@Override
	public void start(Stage stage) {
		Parent root;
		try {
			FXMLLoader loader = new FXMLLoader(getClass().getResource("SetupWizard.fxml"));
			root = loader.load();
			// Object controller = loader.getController();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}

		Scene scene = new Scene(root, 300, 275);

		stage.setTitle("FXML Wizard Tester");
		stage.setScene(scene);
		stage.show();
		
		// ScenicView.show( scene );

	}

	public static void main(String[] args) {
		launch(args);
	}
}
