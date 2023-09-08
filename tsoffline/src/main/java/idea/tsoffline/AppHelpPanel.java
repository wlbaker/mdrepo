package idea.tsoffline;

import javax.swing.JEditorPane;
import javax.swing.text.Document;
import javax.swing.text.html.HTMLEditorKit;
import javax.swing.text.html.StyleSheet;

/**
 * A complete Java class that demonstrates how to create an HTML viewer with
 * styles, using the JEditorPane, HTMLEditorKit, StyleSheet, and JFrame.
 * 
 * @author alvin alexander, devdaily.com.
 *
 */
public class AppHelpPanel extends JEditorPane {

	public AppHelpPanel() {

		this.setName("Help");
		// make it read-only
		this.setEditable(false);

		// add an html editor kit
		HTMLEditorKit kit = new HTMLEditorKit();
		this.setEditorKit(kit);

		// add some styles to the html
		StyleSheet styleSheet = kit.getStyleSheet();
		styleSheet.addRule("body {color:#000; font-family:times; margin: 4px; }");
		styleSheet.addRule("h1 {color: blue;}");
		styleSheet.addRule("h2 {color: #ff0000;}");
		styleSheet.addRule("pre {font : 10px monaco; color : black; background-color : #fafafa; }");

		Document doc = kit.createDefaultDocument();
		this.setDocument(doc);
		

	}

	public void setLoadHelp(String tag) {
		// create some simple html as a string
		String htmlString = AppUtil.getScript(tag);

		// create a document, set it on the jeditorpane, then add the html
		this.setText(htmlString);
	}
}
