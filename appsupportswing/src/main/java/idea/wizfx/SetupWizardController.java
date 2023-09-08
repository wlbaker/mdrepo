package idea.wizfx;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javax.swing.JPanel;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.SubScene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardPanelInterface;
import idea.schema.rp.RpStudy;

public class SetupWizardController implements SetupWizardInterface {

	@FXML
	Button previous;
	
	@FXML
	Button next;
	
	@FXML
	Button finish;
	
	@FXML
	Button cancel;
	
	@FXML
	SubScene subscene;
	
	@FXML
	StackPane stackPane;
	
	@FXML
	public void initialize() {
		stackPane.setOpacity( 0.5);
		subscene.heightProperty().bind(stackPane.heightProperty());
		subscene.widthProperty().bind(stackPane.widthProperty());
		
		subscene.setManaged(false);
	}
	
	@Override
	public void setFinished(boolean b) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void pushPage(JPanel panel) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void popPageUntil(String string) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void enableNext(boolean b) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void enablePrevious(boolean b) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void enableFinish(boolean b) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Object getClientProperty(Object key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public RpStudy getStudy() {
		// TODO Auto-generated method stub
		return null;
	}

	public void onNext() {

		Parent root;
		try {
			FXMLLoader loader = new FXMLLoader(getClass().getResource("SiteSetupPanel.fxml"));
			// loader.se
			root = loader.load();
			Object controller = loader.getController();
			if( controller instanceof WizardPanelInterface ) {
				WizardPanelInterface sub = (WizardPanelInterface)controller;
				sub.setWizard( this );
				sub.dump();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}

		subscene.setRoot(root  );
		System.out.println("subscene visible=" + subscene.isVisible() );
		System.out.println("subscene width=" + subscene.getWidth() );
		System.out.println("subscene height=" + subscene.getHeight() );
		System.out.println("stackpane visible=" + stackPane.isVisible() );
		System.out.println("stackpane width=" + stackPane.getWidth() );
		System.out.println("stackpane height=" + stackPane.getHeight() );
		
	}

}
