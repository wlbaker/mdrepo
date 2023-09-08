/*
 * Created by JFormDesigner on Thu Sep 23 14:00:32 CDT 2010
 */

package idea.tsoffline.script;

import java.awt.Color;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.LinkedList;

import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;
import javax.swing.text.BadLocationException;

import org.fife.ui.rsyntaxtextarea.RSyntaxTextArea;
import org.fife.ui.rsyntaxtextarea.SyntaxConstants;
import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPList;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineCallbacks;
import org.rosuda.REngine.REngineException;
import org.rosuda.REngine.REngineOutputInterface;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GlobalHotkeyManager;
import idea.GuiUtil;
import idea.r.RCue;
import idea.r.RUtil;
import idea.tsoffline.AppUtil;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class ConsolePanel extends JPanel implements REngineCallbacks, REngineOutputInterface {

	private static final int MAX_CONSOLE_BUFFER = 500000;
	LinkedList<String> history = new LinkedList<String>();
	int histIdx = 0;

	RSyntaxTextArea command;

	public ConsolePanel() {
		initComponents();

		command = textArea;

		setStyle(textArea);
		setStyle(command);

		GuiUtil.initPanel(this);
		command.putClientProperty(GlobalHotkeyManager.IGNORE_HOTKEY, true);

		command.addKeyListener(new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				KeyStroke ks = KeyStroke.getKeyStrokeForEvent(e);

				if (ks.getKeyCode() == KeyEvent.VK_ENTER && !e.isControlDown()) {
					if( runActionPerformed(null) ) {
						e.consume();
					}
				} else if (ks.getKeyCode() == KeyEvent.VK_ENTER && e.isControlDown()) {
					command.append("\n");
					e.consume();
				} else if (ks.getKeyCode() == KeyEvent.VK_TAB) {
					showCompletion();
					e.consume();
				} else if (ks.getKeyCode() == KeyEvent.VK_UP) {
					prevHistory();
					e.consume();
				} else if (ks.getKeyCode() == KeyEvent.VK_DOWN) {
					nextHistory();
					e.consume();
				}
			}

			private void showCompletion() {
				log.error("FIXME: show completion for command");
			}

			@Override
			public void keyReleased(KeyEvent e) {
				// KeyStroke ks = KeyStroke.getKeyStrokeForEvent(e);
				// log.debug("RELEASE {}", ks.getKeyChar() );
				// ks.getKeyCode());
			}

			@Override
			public void keyTyped(KeyEvent e) {
				// KeyStroke ks = KeyStroke.getKeyStrokeForEvent(e);
				// System.out.println("TYPED {}" + ks.getKeyChar() );
				// ks.getKeyCode());
			}
		});

		textArea.setComponentPopupMenu(popup);
		command.requestFocus();
	}

	private void setStyle(RSyntaxTextArea a) {
		a.setSyntaxEditingStyle(SyntaxConstants.SYNTAX_STYLE_PYTHON);
		a.setHighlightCurrentLine(false);
		a.setMarginLineEnabled(false);
		a.setCodeFoldingEnabled(true);
		a.setCaretColor(Color.DARK_GRAY);
	}

	private boolean runActionPerformed(ActionEvent e) {

		boolean executed = false;
		try {
			executed = _runActionPerformed(e);
		} catch (REngineException | REXPMismatchException e1) {
			textArea.append("Error: ");
			textArea.append(e1.getMessage());
			textArea.append("\n");
			// e1.printStackTrace();
		} catch (Exception e2) {
			// e2.printStackTrace();
		}

		// add new prompt
		if (executed) {
			textArea.append("> ");
			command_start = textArea.getDocument().getLength();
			textArea.setCaretPosition(command_start);
		}
		return executed;
	}

	private boolean _runActionPerformed(ActionEvent e)
			throws REngineException, REXPMismatchException, BadLocationException {

		RCue.parent = null;

		int command_end = textArea.getDocument().getLength();

		String currCmd = textArea.getDocument().getText(command_start, command_end - command_start);
		/*
		 * count paranthese and brackets to see if we should execute
		 */
		int n_open = 0;
		int n_close = 0;
		for (int idx = 0; idx < currCmd.length(); idx++) {
			char ch = currCmd.charAt(idx);
			if (ch == '(' || ch == '{' || ch == '[') {
				n_open++;
			} else if (ch == ')' || ch == '}' || ch == ']') {
				n_close++;
			}
		}
		
		if( n_open > n_close ) {
			/*
			 * not ready for next prompt...continue entry
			 */
			return false;
		}
		
		log.debug("currCmd: {}", currCmd);
		if (currCmd.startsWith("> ")) {
			if (currCmd.length() == 2) {
				currCmd = "";
			} else {
				currCmd = currCmd.substring(2);
			}
		}

		// only store the command if it is unique
		String lastCmd = "";
		if (history.size() > 0) {
			lastCmd = history.getLast();
		}

		if (!currCmd.equals(lastCmd)) {
			history.add(currCmd);
		}

		// set the history index pointer to one past last
		histIdx = history.size();

		boolean executed = false;
		if (currCmd.trim().length() == 0) {
			textArea.append("> ");
			textArea.append(currCmd);
			textArea.append("\n");

		} else {
			try {
				textArea.append("\n");
				executed = true;
				AppUtil.runScript("print( { " + currCmd + "} )", false);
			} catch (RuntimeException re) {
				String message = re.getMessage();
				textArea.append(message);

				Throwable cause = re.getCause();
				if (cause != null) {
					StringWriter errors = new StringWriter();
					cause.printStackTrace(new PrintWriter(errors));
					textArea.append(errors.toString());
				}
			}
		}

		return executed;
	}

	public static String explain(REXP ok) throws REXPMismatchException {
		String message = null;
		REXP cl = ok.getAttribute("class");
		if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {

			// RUtil.getNativeException()
			REXPList attr = ok._attr();
			Throwable t = null;
			if (attr != null && attr.length() > 0) {
				t = AppUtil.drillForNativeException(attr.asList());
			}

			message = RUtil.describe(null, 5, ok).toString();
		}

		return message;
	}

	private void prevHistory() {

		do_history(-1);
	}

	private void nextHistory() {
		do_history(1);
	}

	private void do_history(int dir) {
		if ((dir < 0 && histIdx <= 0) || (dir > 0 && histIdx >= history.size() - 1)) {
			// beep!
			Toolkit.getDefaultToolkit().beep();
			return;
		}

		histIdx += dir;

		String cmd = history.get(histIdx);

		int command_end = textArea.getDocument().getLength();
		textArea.replaceRange(cmd, command_start, command_end);
		command_end = textArea.getDocument().getLength();
	}

	private void pasteActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void copyActionPerformed(ActionEvent e) {
		textArea.copy();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		textArea = new RSyntaxTextArea();
		popup = new JPopupMenu();
		copy = new JMenuItem();
		paste = new JMenuItem();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $rgap, fill:default"));

		//======== scrollPane1 ========
		{
			scrollPane1.setViewportView(textArea);
		}
		add(scrollPane1, CC.xy(1, 1));

		//======== popup ========
		{

			//---- copy ----
			copy.setText("Copy");
			copy.addActionListener(e -> copyActionPerformed(e));
			popup.add(copy);

			//---- paste ----
			paste.setText("Paste");
			paste.setEnabled(false);
			paste.addActionListener(e -> pasteActionPerformed(e));
			popup.add(paste);
		}
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private RSyntaxTextArea textArea;
	private JPopupMenu popup;
	private JMenuItem copy;
	private JMenuItem paste;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	private int sz;
	private int command_start;

	@Override
	public void RFlushConsole(REngine arg0) {
		// TODO Auto-generated method stub

		log.debug("**flushing: {}", arg0);
	}

	@Override
	public void RShowMessage(REngine arg0, String arg1) {
		textArea.append(arg1);
		log.debug("**showinging: {}", arg1);
	}

	@Override
	public void RWriteConsole(REngine arg0, String arg1, int arg2) {
		textArea.append(arg1);

		sz += arg1.length();
		if (sz > MAX_CONSOLE_BUFFER) {
			String txt = textArea.getText();
			String rev = txt.substring(txt.length() - MAX_CONSOLE_BUFFER + 1000);
			textArea.setText(rev);
			sz = rev.length();
		}

		command_start = textArea.getDocument().getLength();
		textArea.setCaretPosition(command_start);
		log.debug("**command_start: {}", command_start);
	}

	/*
	 * @Override public void rBusy(Rengine arg0, int arg1) { // TODO Auto-generated
	 * method stub
	 * 
	 * }
	 * 
	 * @Override public String rChooseFile(Rengine arg0, int arg1) { // TODO
	 * Auto-generated method stub return null; }
	 * 
	 * @Override public void rFlushConsole(Rengine arg0) { // TODO Auto-generated
	 * method stub
	 * 
	 * }
	 * 
	 * @Override public void rLoadHistory(Rengine arg0, String arg1) { // TODO
	 * Auto-generated method stub
	 * 
	 * }
	 * 
	 * @Override public String rReadConsole(Rengine arg0, String arg1, int arg2) {
	 * // TODO Auto-generated method stub return null; }
	 * 
	 * @Override public void rSaveHistory(Rengine arg0, String arg1) { // TODO
	 * Auto-generated method stub
	 * 
	 * }
	 * 
	 * @Override public void rShowMessage(Rengine arg0, String arg1) {
	 * textArea.append(arg1); }
	 * 
	 * @Override public void rWriteConsole(Rengine arg0, String arg1, int arg2) {
	 * textArea.append(arg1); }
	 */
}
