package idea.gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URLEncoder;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;

import lombok.extern.slf4j.Slf4j;
import idea.DisabledGlassPane;
import idea.GuiUtil;

/**
 * 
 * ExceptionDialog.
 * 
 * Displays an exception stack trace in a panel south of the main dialog area.
 * 
 * 
 * @author Oliver Watkins (c)
 */
@Slf4j
@SuppressWarnings("serial")
public class ExceptionDialogPanel extends JPanel { // 12Apr16 extends JDialog {

	private int dialogWidth = 600;
	private int dialogHeight = 160;

	private JLabel iconLabel = new JLabel();

	// is error panel opened up
	private boolean open = false;

	private JTextArea errorTextArea = new JTextArea("");

	private JTextArea exceptionTextArea = new JTextArea("");
	private JScrollPane exceptionTextAreaSP = new JScrollPane();

	private JButton okButton = new JButton("OK");
	private JButton viewButton = new JButton("View Error");
	private JButton emailButton = new JButton("Email Error");

	private JPanel topPanel = new JPanel(new BorderLayout());

	String reportableMessage;

	public ExceptionDialogPanel(String errorDescription, Throwable e) {

		// 12Apr16 super(root_frame);

		StringWriter errors = new StringWriter();
		PrintWriter pw = new PrintWriter(errors);
		
		pw.print( errorDescription );
		e.printStackTrace(pw);

		// 17Apr16 setSize(dialogWidth, dialogHeight);

		// this doesnt make sense with a panel...might make sense with a jdialog or glasspane if
		// the default layout is awkward.
		// 12Apr16 setLocationRelativeTo(root_frame);

		errorTextArea.setText(errorDescription);
		errorTextArea.setEditable(false);
		errorTextArea.setPreferredSize(new Dimension(dialogWidth - 86, 60));

		reportableMessage = errors.toString();
		exceptionTextArea.setText(reportableMessage);
		exceptionTextArea.setEditable(false);

		exceptionTextAreaSP = new JScrollPane(exceptionTextArea);
		exceptionTextAreaSP.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		exceptionTextAreaSP.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		// exceptionTextAreaSP.setPreferredSize(new Dimension(dialogWidth - 20, 300));

		iconLabel.setBorder(new EmptyBorder(new Insets(10, 10, 10, 10)));

		iconLabel.setIcon(UIManager.getIcon("OptionPane.errorIcon"));
		setupUI();

		setUpListeners();

		setDialogHeight(this.getParent(), dialogHeight );
		// 12Apr16 GuiUtil.initModalDialog(this, (JPanel) this.getContentPane());
	}

	// public ExceptionDialog(String errorLabelText, Throwable e) {
	// this(null, errorLabelText, null, e);
	// }

	public void setupUI() {

		// 12Apr16 this.setTitle("Application Error");

		errorTextArea.setLineWrap(true);
		errorTextArea.setWrapStyleWord(true);
		errorTextArea.setEditable(false);

		JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));

		buttonPanel.add(okButton);
		buttonPanel.add(emailButton);
		buttonPanel.add(viewButton);

		errorTextArea.setBackground(iconLabel.getBackground());

		JScrollPane textAreaSP = new JScrollPane(errorTextArea);

		textAreaSP.setBorder(new EmptyBorder(new Insets(5, 5, 5, 5)));

		// exceptionTextArea.setPreferredSize(new Dimension(100, 100));

		setLayout(new BorderLayout());
		topPanel.add(iconLabel, BorderLayout.WEST);

		JPanel p = new JPanel(new BorderLayout());
		// p.add(errorLabel, BorderLayout.NORTH);
		p.add(textAreaSP, BorderLayout.CENTER);

		topPanel.add(p, BorderLayout.CENTER);

		add(topPanel, BorderLayout.NORTH);
		// this.add(exceptionTextAreaSP, BorderLayout.CENTER);

		add(buttonPanel, BorderLayout.SOUTH);
	}

	private void setUpListeners() {

		okButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// ExceptionDialog.this.setVisible(false);
				GuiUtil.closeDialog(ExceptionDialogPanel.this);
			}
		});

		viewButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {

				int reqHeight = dialogHeight;
				if (open) {
					viewButton.setText("View Error");
					// 12Apr16 setResizable(false);

					ExceptionDialogPanel.this.remove(exceptionTextAreaSP);

					open = false;

				} else {

					viewButton.setText("Hide Error");
					// 12Apr16 setResizable(true);

					ExceptionDialogPanel.this.add(exceptionTextAreaSP, BorderLayout.CENTER);
					reqHeight += 300;

					open = true;
				}

				setDialogHeight(ExceptionDialogPanel.this.getParent(), reqHeight);
			}
		});

		emailButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					submitError();
				} catch (Exception ee) {
					log.error("Could not submit error.", ee);
				}
			}
		});
	}

	private void setDialogHeight(Container parent, int reqHeight ) {

		while (parent != null) {

			if (parent instanceof DisabledGlassPane) {
				JComponent dialog = (JComponent) parent;
				dialog.setSize(dialogWidth, reqHeight);
				break;
			}
			if (parent instanceof JDialog) {
				JDialog dialog = (JDialog) parent;
				dialog.setSize(dialogWidth, reqHeight);
				break;
			}

			parent = parent.getParent();
		}
	}

	protected void submitError() throws IOException, URISyntaxException {

		String to = "william.l.baker2.civ@mail.mil";
		String cc = "bbaker@softhorizons.com";
		String subject = "Application%20Error";

		// this encoding uses + insedad of %20...and maybe other issues
		String body = URLEncoder.encode(reportableMessage, "UTF-8");

		// poor man's encoding
		body = body.replaceAll("\\+", "%20").replaceAll("\\%21", "!").replaceAll("\\%27", "'").replaceAll("\\%28", "(")
				.replaceAll("\\%29", ")").replaceAll("\\%7E", "~");

		String mailURIStr = String.format("mailto:%s?subject=%s&cc=%s&body=%s", to, subject, cc, body);
		if( mailURIStr.length() > 32694) {
			// max length of uristr is 32700
			// this can fail if a dangling/partial % arg is present, so add a couple of 0's to be sure
			mailURIStr = mailURIStr.substring(0, 32694) + "0000";
		}

		URI uriMailTo = new URI(mailURIStr);

		Desktop desktop;
		if (Desktop.isDesktopSupported() && (desktop = Desktop.getDesktop()).isSupported(Desktop.Action.MAIL)) {
			desktop.mail(uriMailTo);
		} else {
			throw new RuntimeException("desktop doesn't support mailto; mail is dead anyway ;)");
		}

	}

}