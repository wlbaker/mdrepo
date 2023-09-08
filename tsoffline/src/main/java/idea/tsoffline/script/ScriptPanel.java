/*
 * Created by JFormDesigner on Wed Mar 28 12:15:12 CDT 2012
 */

/**
 *  Sample script
 *  

  importPackage(java.awt);

  importClass( Packages.idea.cardiostrip.StudyEvent )
  
  fileName = "\\\\ameda7aisr0042\\2canciolab\\A-11-010 Smoke Inhalation and Burn Study\\data_icu\\115";
 
 app.open( fileName )
 ekg = app.getSignal("Drager", "EKG1")

 frame = app.createInternalFrame(ekg)
 ts = frame.getTimeseriesControl();

 gui.showMessage("waiting for ts load")
 rri_derived = ts.createDerivedSignal( ekg, "RRI PT1", "PT1" )

 gui.showMessage("waiting for rri calc")
 sampen_derived = ts.createDerivedSignal( rri_derived, "SE", "200,2,1,6ms,n" )
 gui.showMessage("waiting for sampen calc...will be shown in gui")

 lya_derived = ts.createDerivedSignal( rri_derived, "LYA", "200,2,1,6ms,n" )
 gui.showMessage("waiting for lya calc...will be shown in gui")


 events = app.getEventModel()
 
 var dt = new java.util.Date( 2010, 10, 30, 8, 15 )
 
 var event = new StudyEvent("BASELINE", "Baseline", dt, 0 )
 events.add( event ) 

 */

package idea.tsoffline.script;

import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;

import javax.script.ScriptEngine;
import javax.script.ScriptException;
import javax.swing.JButton;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.JavascriptUtil;
import idea.tsoffline.AppUtil;
import idea.tsoffline.model.DerivedUtil;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ScriptPanel extends JPanel implements ClipboardOwner {
	ScriptEngine engine;

	public ScriptPanel() {
		initComponents();
		initMenu();
	}

	private void initMenu() {
		scriptArea.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				checkForTriggerEvent(e);
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				checkForTriggerEvent(e);
			}

			private void checkForTriggerEvent(MouseEvent e) {
				if (e.isPopupTrigger())
					popup.show(e.getComponent(), e.getX(), e.getY());
			}
		});
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void runActionPerformed(ActionEvent e) {
		run.setEnabled( false );
		try {
			_run(null);
		} catch (Exception ex) {
			GuiUtil.showError("Script Processing", ex);
		} finally {
			run.setEnabled( true );
		}
	}

	private void _run(ActionEvent e) throws ScriptException {

		if (engine == null) {
			engine = JavascriptUtil.initEngine();
		}

		engine.put("app", AppUtil.getInstance());
		engine.put("gui", GuiUtil.getInstance());
		engine.put("util", DerivedUtil.getInstance() );

		String s = scriptArea.getText();
		if( s == null || s.length() == 0 ) {
			// nothing to run...could cause null pointer exception
		} else {
			engine.eval(s);
		}

	}

	private void copyActionPerformed(ActionEvent e) {

		String txt = scriptArea.getText();
		StringSelection stringSelection = new StringSelection(txt);
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		clipboard.setContents(stringSelection, this);
	}

	private void pasteActionPerformed(ActionEvent e) {
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		//odd: the Object param of getContents is not currently used
		Transferable contents = clipboard.getContents(null);
		boolean hasTransferableText = (contents != null) && contents.isDataFlavorSupported(DataFlavor.stringFlavor);
		if (hasTransferableText) {
			try {
				String result = (String) contents.getTransferData(DataFlavor.stringFlavor);
				scriptArea.setText(result);
			} catch (UnsupportedFlavorException ex) {
				//highly unlikely since we are using a standard DataFlavor
				System.out.println(ex);
				ex.printStackTrace();
			} catch (IOException ex) {
				System.out.println(ex);
				ex.printStackTrace();
			}
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		scriptArea = new JTextArea();
		panel1 = new JPanel();
		load = new JButton();
		textField1 = new JTextField();
		run = new JButton();
		save = new JButton();
		cancel = new JButton();
		popup = new JPopupMenu();
		copy = new JMenuItem();
		paste = new JMenuItem();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[400dlu,default]:grow",
			"default, $lgap, fill:[200dlu,default]:grow, 2*($lgap, default)"));

		//======== scrollPane1 ========
		{
			scrollPane1.setViewportView(scriptArea);
		}
		add(scrollPane1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 3*($lcgap, [50dlu,default])",
				"default"));

			//---- load ----
			load.setText("Load");
			panel1.add(load, cc.xy(1, 1));
			panel1.add(textField1, cc.xy(3, 1));

			//---- run ----
			run.setText("Run");
			run.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					runActionPerformed(e);
				}
			});
			panel1.add(run, cc.xy(5, 1));

			//---- save ----
			save.setText("Save");
			panel1.add(save, cc.xy(7, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(9, 1));
		}
		add(panel1, cc.xy(1, 7));

		//======== popup ========
		{

			//---- copy ----
			copy.setText("Copy");
			copy.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					copyActionPerformed(e);
				}
			});
			popup.add(copy);

			//---- paste ----
			paste.setText("Paste");
			paste.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					pasteActionPerformed(e);
				}
			});
			popup.add(paste);
		}
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTextArea scriptArea;
	private JPanel panel1;
	private JButton load;
	private JTextField textField1;
	private JButton run;
	private JButton save;
	private JButton cancel;
	private JPopupMenu popup;
	private JMenuItem copy;
	private JMenuItem paste;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public void lostOwnership(Clipboard clipboard, Transferable contents) {
		// TODO Auto-generated method stub

	}
}
