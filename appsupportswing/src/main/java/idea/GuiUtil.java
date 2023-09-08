package idea;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.KeyboardFocusManager;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.net.URL;
import java.net.URLClassLoader;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Properties;

import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.DefaultCellEditor;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JEditorPane;
import javax.swing.JFileChooser;
import javax.swing.JFormattedTextField;
import javax.swing.JFormattedTextField.AbstractFormatterFactory;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.ListSelectionModel;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableColumn;
import javax.swing.text.DateFormatter;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.Document;
import javax.swing.text.JTextComponent;
import javax.swing.text.NumberFormatter;
import javax.swing.text.html.HTMLEditorKit;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.jtattoo.plaf.graphite.GraphiteLookAndFeel;
import com.toedter.calendar.IDateEditor;
import com.toedter.calendar.JDateChooser;
import com.toedter.calendar.JTextFieldDateEditor;

import lombok.extern.slf4j.Slf4j;
import idea.gui.ColorListCellRenderer;
import idea.gui.ColorTableCellRenderer;
import idea.gui.DefaultOkCancelPanel;
import idea.gui.DialogActionListener;
import idea.gui.ExcelAdapter;
import idea.gui.ExceptionDialogPanel;
import idea.gui.UndecoratedFilechooser;
import idea.gui.action.DefaultActions;
import idea.gui.action.NextFocusAction;

@Slf4j
public class GuiUtil {

	private static boolean isFullScreen;
	private static FocusListener selectAllTextFocusListener;
	private static FocusListener selectLaterTextFocusListener;
	private static PropertyChangeListener datechooser_colorfixer;
	private static FocusListener datechooser_focusListener;

	private static final String ENTER_ACTION_NAME = "ddd_enter_action";

	private static DefaultFormatterFactory currencyFactory;

	private static DefaultFormatterFactory numberFactory;

	private static DefaultFormatterFactory integerFactory;
	private static Window root_window;

	static {
		selectAllTextFocusListener = new FocusListener() {

			public void focusGained(FocusEvent e) {
				JTextField f = (JTextField) e.getSource();
				f.selectAll();
			}

			public void focusLost(FocusEvent e) {
				// TODO Auto-generated method stub

			}
		};

		selectLaterTextFocusListener = new FocusListener() {

			public void focusGained(FocusEvent e) {
				Runnable selectLaterRunnable = new SelectAllTextRunLater((JFormattedTextField) e.getSource());
				SwingUtilities.invokeLater(selectLaterRunnable);
			}

			public void focusLost(FocusEvent e) {
				// TODO Auto-generated method stub

			}

		};

		/*
		 * WARNING: I made one little change in JDateChooser. There are two places in
		 * this file where foreground color is set to black. The one where the check for
		 * text is empty is not needed!
		 * 
		 * There is a feature defect in JDateChooser. It should use the look and feel
		 * resources, but it interacts poorly with jformattedtextfield because it
		 * doesnt.
		 */

		datechooser_colorfixer = new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				// 060319 Object src = evt.getSource();
				// 060319 JComponent comp = (JComponent) src;
				// 060319 if (comp.getForeground().equals(Color.BLACK)) {
				// 060319 	comp.setForeground(Color.WHITE);
				// 060319 }

				// if (comp instanceof JDateChooser) {
				// JDateChooser chooser = (JDateChooser) comp;
				// IDateEditor editor = chooser.getDateEditor();
				// JTextFieldDateEditor sub_comp = (JTextFieldDateEditor)
				// editor.getUiComponent();
				// if ( sub_comp.getForeground().equals(Color.BLACK)) {
				// sub_comp.setForeground(Color.WHITE);
				// }
				// }

			};
		};

		datechooser_focusListener = new FocusListener() {

			public void focusGained(FocusEvent e) {
			}

			public void focusLost(FocusEvent e) {
				// 060319 Object src = e.getSource();
				// 060319 JComponent comp = (JComponent) src;
				// 060319 Color f = comp.getForeground();
				// 060319 if (f.equals(Color.BLACK)) {
				// 060319	comp.setForeground(Color.WHITE);
				// 060319 	System.out.println("reset color to white");
				// 060319 } else {
				// 060319 	System.out.println("color is: " + f);
				// 060319 }
			}

		};

	}

	// private static GraphicsDevice device;

	public static void initApplication(String appName, String appVersion, String[] args)
			throws UnsupportedLookAndFeelException {
		initApplication(appName, appVersion, args, true);
	}

	public static void initApplication(String appName, String appVersion, String[] args, boolean lookAndFeel)
			throws UnsupportedLookAndFeelException {
		PrefUtil.setAppName(appName);
		PrefUtil.setAppVersion(appVersion);
		if (lookAndFeel) {
			setLookAndFeel();
		}

		initGlobalHotkeys();

	}

	public static Action getEnterAction(JComponent c) {
		return (Action) c.getClientProperty(ENTER_ACTION_NAME);
	}

	/**
	 * Redirect an application's System.out and Sytem.err to a log file
	 * 
	 * @param applicationName
	 * @param location
	 */
	public static void redirectStdOutAndErr(String applicationName, String location) {
		try {
			Date date = Calendar.getInstance().getTime();

			String outName = location;

			File f = new File(location);
			if (f.isDirectory()) {
				Format formatter = new SimpleDateFormat("yyyyMMdd");
				String now = "_" + formatter.format(date);
				formatter = new SimpleDateFormat("HHmmss");
				now += "_" + formatter.format(date);
				outName = location + applicationName + now + ".log";
			}

			try {
				File p = f.getParentFile();
				if (p.exists() == false) {
					p.mkdirs();
				}
			} catch (Exception e) {
				// ignore
			}

			System.setOut(new PrintStream(new FileOutputStream(outName)));
			System.setErr(System.out);
		} catch (FileNotFoundException fnfe) {
			System.out.println(fnfe.getMessage());
		}
	}

	private static void initGlobalHotkeys() {

		String nfaKey = "dfNextFocus";
		Action nextFocusAction = new NextFocusAction("dfNextFocus");
		KeyStroke enter = KeyStroke.getKeyStroke('\n'); // java.awt.event.KeyEvent.VK_ENTER,
		// java.awt.event.KeyEvent.KEY_TYPED );

		GlobalHotkeyManager hotkeyManager = GlobalHotkeyManager.getInstance();
		hotkeyManager.getInputMap().put(enter, nfaKey);
		hotkeyManager.getActionMap().put(nfaKey, nextFocusAction);

		String link = "dfDebugFocus";
		Action debugAction = new AbstractAction(link) {

			@Override
			public void actionPerformed(ActionEvent e) {
				KeyboardFocusManager focusManager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
				Component source = focusManager.getFocusOwner();
				System.out.println("focus owner is: " + source);
			}

		};

		KeyStroke debugKey = KeyStroke.getKeyStroke("F11"); // java.awt.event.KeyEvent.VK_ENTER,
		// java.awt.event.KeyEvent.KEY_TYPED );
		hotkeyManager.getInputMap().put(debugKey, link);
		hotkeyManager.getActionMap().put(link, debugAction);

	}

	public static void initScreen(GraphicsDevice device, JFrame f, boolean fullScreen) {

		if (device == null) {
			GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
			GraphicsDevice[] devices = env.getScreenDevices();

			device = devices[0];
		}

		isFullScreen = false;
		if (device != null && fullScreen) {
			isFullScreen = device.isFullScreenSupported();
		}

		if (f.isDisplayable()) {
			// release all the native resources before setting undecorated
			f.dispose();
		}

		// substance has an issue with setUndecorated...?
		//
		// f.getT
		// if( decorateFrame ) {
		// f.setUndecorated(isFullScreen);
		// }
		// f.setResizable(!isFullScreen);

		if (isFullScreen) {
			f.setVisible(false);
			// Full-screen mode
			device.setFullScreenWindow(f);
			f.validate();
		} else {
			// Windowed mode
			f.pack();
			f.setVisible(true);
		}

		root_window = f;

	}

	/**
	 * 
	 * Best reference on L&F
	 * https://stackoverflow.com/questions/3954616/java-look-and-feel-lf/28753722#28753722
	 */

	private static void setLookAndFeel() throws UnsupportedLookAndFeelException {

		JFrame.setDefaultLookAndFeelDecorated(true);
		JDialog.setDefaultLookAndFeelDecorated(true);

		try {
			// UIManager.setLookAndFeel("de.javasoft.plaf.synthetica.SyntheticaStandardLookAndFeel");
			// UIManager.setLookAndFeel("de.javasoft.plaf.synthetica.SyntheticaBlackEyeLookAndFeel");
			// UIManager.setLookAndFeel("de.javasoft.plaf.synthetica.SyntheticaClassyLookAndFeel");

			// UIManager.setLookAndFeel("com.jtattoo.plaf.texture.TextureLookAndFeel");
			// GraphiteLookAndFeel.setTheme("Graphite", "", "");
			Properties props = new Properties();
			props.put("logoString", "");
			GraphiteLookAndFeel.setCurrentTheme(props);
			UIManager.setLookAndFeel("com.jtattoo.plaf.graphite.GraphiteLookAndFeel");
			return;
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		/*
		 * -- begin substance L&F //Another way is to use the #setLookAndFeel method of
		 * the SyntheticaLookAndFeel class //SyntheticaLookAndFeel.setLookAndFeel(String
		 * className, boolean antiAlias, boolean useScreenMenuOnMac);
		 * UIManager.setLookAndFeel(new SubstanceRavenLookAndFeel() ); boolean ok =
		 * SubstanceLookAndFeel.setSkin(new
		 * org.pushingpixels.substance.api.skin.RavenSkin()); //
		 * SubstanceCortex.GlobalScope.setSkin(new
		 * org.pushingpixels.substance.api.skin.RavenSkin());
		 * 
		 * if( !ok ) { // throw new
		 * UnsupportedLookAndFeelException("could not load RavenSkin"); log.
		 * error("throw new UnsupportedLookAndFeelException(\"could not load RavenSkin ??\");"
		 * ); } if (!SubstanceLookAndFeel.isCurrentLookAndFeel()) { log.
		 * error("throw new UnsupportedLookAndFeelException(\"could not install Substance L&F\");"
		 * ); } -- end substancd L&F
		 */
		// SubstanceLookAndFeel.setSkin(new
		// org.pushingpixels.substance.api.skin.CremeCoffeeSkin() );
		// UIManager.put("ComboBox.background", Color.RED );
		// UIManager.put("ComboBox.foreground", Color.WHITE );
		// UIManager.put("ComboBox.buttonBackground", Color.YELLOW );
		// UIManager.put("ComboBox.buttonDarkShadow", Color.WHITE );
		// UIManager.put("ComboBox.buttonHighlight", Color.YELLOW );
		// UIManager.put("ComboBox.buttonShadow", Color.YELLOW );
		// UIManager.put("ComboBox.control", Color.YELLOW );
		// UIManager.put("ComboBox.controlForeground", Color.CYAN );
		// UIManager.put("ComboBox.controlBackground", Color.MAGENTA );
		// UIManager.put("ComboBox.disabledForeground", Color.WHITE );
		// UIManager.put("ComboBox.selectionBackground", Color.RED );
		// UIManager.put("ComboBox.selectionForeground", Color.WHITE );

		/*
		 * NimRODLookAndFeel laf = new com.nilo.plaf.nimrod.NimRODLookAndFeel();
		 * 
		 * String themeName = "/nimrod/darkgrey.theme"; try { java.net.URL url =
		 * GuiUtil.class.getResource(themeName); NimRODTheme theme = new
		 * NimRODTheme(url); NimRODLookAndFeel.setCurrentTheme(theme); } catch
		 * (Exception e) { System.err.println("could not load default theme: " +
		 * themeName); }
		 * 
		 * UIManager.setLookAndFeel(laf);
		 */

		/*
		 * tattoo try { UIManager.setLookAndFeel(
		 * "com.jtattoo.plaf.graphite.GraphiteLookAndFeel"); } catch
		 * (ClassNotFoundException e) { // TODO Auto-generated catch block
		 * e.printStackTrace(); } catch (InstantiationException e) { // TODO
		 * Auto-generated catch block e.printStackTrace(); } catch
		 * (IllegalAccessException e) { // TODO Auto-generated catch block
		 * e.printStackTrace(); }
		 */
		// // UIManager.setLookAndFeel("com.jtattoo.plaf.hifi.HiFiLookAndFeel");
		// //
		// UIManager.setLookAndFeel("com.jtattoo.plaf.noire.NoireLookAndFeel");
		// // UIManager.setLookAndFeel("com.jtattoo.plaf.aero.AeroLookAndFeel");
		// //
		// UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

	}

	public static void closeDialog(JPanel panel) {

		Container parent = panel.getParent();
		DialogActionListener listener = null;

		while (parent != null) {
			DialogActionListener l = (DialogActionListener) panel.getClientProperty("DialogActionListener");
			if (l != null) {
				listener = l;
			}

			if (parent instanceof DisabledGlassPane)
				break;
			if (parent instanceof JDialog)
				break;

			parent = parent.getParent();
		}

		if (parent instanceof DisabledGlassPane) {
			DisabledGlassPane p0 = (DisabledGlassPane) parent;
			p0.deactivate();

			if (listener != null) {
				listener.closeDialogAction(panel);
			}
		} else if (parent instanceof JDialog) {
			JDialog p0 = (JDialog) parent;
			p0.setVisible(false);

			// ERROR: This is not the right thing to do here...the dialog must
			// have
			// a window listener for close events...consider the X in the
			// corner.
			if (listener != null) {
				listener.closeDialogAction(panel);
			}
		}

	}

	public static void doDialog(String title, Component parent, JPanel panel, DialogActionListener listener) {
		doDialog(title, parent, panel, listener, isFullScreen);
	}

	public static void doDialog(String title, Component parent, JPanel panel, DialogActionListener listener,
			boolean inOverlay) {

		panel.putClientProperty("DialogActionListener", listener);
		if (inOverlay) {
			initModalDialog(null, panel); // installs the ESC handler
			DisabledGlassPane glassPane = new DisabledGlassPane(panel);
			JRootPane rootPane = SwingUtilities.getRootPane(parent);
			rootPane.setGlassPane(glassPane);

			panel.requestFocusInWindow();
			glassPane.activate();

			glassPane.repaint();
		} else {

			Object[] options = new Object[] {};

			JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);

			JDialog dlg = op.createDialog(parent, title);
			GuiUtil.initModalDialog(dlg, panel);
			// dlg.setModalityType( Dialog.ModalityType.APPLICATION_MODAL );
			// //dlg.setUndecorated( true );
			dlg.setResizable(true);

			Window prev_root = root_window;
			try {
				root_window = dlg;
				dlg.setVisible(true);
			} finally {
				root_window = prev_root;
			}

		}
	}

	public static void doNonModalDialog(String title, Component parent, JPanel panel, DialogActionListener listener) {

		panel.putClientProperty("DialogActionListener", listener);
		if (isFullScreen) {
			DisabledGlassPane glassPane = new DisabledGlassPane(panel);
			JRootPane rootPane = SwingUtilities.getRootPane(parent);
			rootPane.setGlassPane(glassPane);

			glassPane.activate();

		} else {

			Object[] options = new Object[] {};

			JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);

			JDialog dlg = op.createDialog(parent, title);
			GuiUtil.initModalDialog(dlg, panel);
			// dlg.setModalityType( Dialog.ModalityType.APPLICATION_MODAL );
			dlg.setModal(false);
			// //dlg.setUndecorated( true );
			dlg.setResizable(true);

			dlg.setVisible(true);

		}
	}

	private static File chosen = null;
	private static DefaultFormatterFactory datetimeFactory;
	private static DefaultFormatterFactory hhmmssFactory;

	public static File doOpenFileChooser(int mode, String title, Component frame, File parent,
			final ActionListener ll) {
		return _doFileChooser(false, mode, title, frame, parent, ll);
	}

	public static File doSaveFileChooser(int mode, String title, Component frame, File parent,
			final ActionListener ll) {
		return _doFileChooser(true, mode, title, frame, parent, ll);
	}

	private static File _doFileChooser(boolean save, int mode, String title, Component frame, File parent,
			final ActionListener ll) {

		if (isFullScreen) {
			final UndecoratedFilechooser fc = new UndecoratedFilechooser();
			if (parent != null) {
				if (parent.isFile()) {
					fc.setSelectedFile(parent);
				} else if (parent.isDirectory()) {
					fc.setCurrentDirectory(parent);
				}
			}
			fc.setFileSelectionMode(mode);

			if (title != null && title.startsWith("New")) {
				// OK, maybe not the cleanest idea, but it should work
				fc.setApproveButtonText("New File");
				fc.setApproveButtonMnemonic('N');
			}

			JDialog d = fc.createDialog(frame);

			JPanel panel = (JPanel) d.getContentPane();
			d.remove(panel);
			d.setContentPane(new JPanel());

			fc.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					UndecoratedFilechooser fc = (UndecoratedFilechooser) e.getSource();
					GuiUtil.closeDialog(fc.nakedPanel);
				}
			});

			// panel.setOw

			GuiUtil.doDialog(title, frame, panel, new DialogActionListener() {

				@Override
				public void closeDialogAction(JPanel p) {
					ActionEvent ae = new ActionEvent(fc.getSelectedFile(), 0, "file");
					ll.actionPerformed(ae);
				}
			});
		} else {

			JFileChooser fc = new JFileChooser();
			fc.setFileSelectionMode(mode); // this needs to be called before
											// setting the selected file
			fc.setDialogTitle(title);
			if (parent != null) {

				if (parent.isDirectory()) {
					fc.setCurrentDirectory(parent);
				} else {
					fc.setSelectedFile(parent);
				}
			}

			if (title != null && title.startsWith("New")) {
				// OK, maybe not the cleanest idea, but it should work
				fc.setApproveButtonText("New File");
				fc.setApproveButtonMnemonic('N');
			}

			int rc;
			if (save) {
				rc = fc.showSaveDialog(frame);
			} else {
				rc = fc.showOpenDialog(frame);
			}

			if (rc == JFileChooser.APPROVE_OPTION) {
				chosen = fc.getSelectedFile();

				if (ll != null) {
					ActionEvent ae = new ActionEvent(fc.getSelectedFile(), 0, "file");
					ll.actionPerformed(ae);
				}
			}
		}
		/*
		 * SimulationParametersPanel content = new SimulationParametersPanel();
		 * ParametersMasterPanel panel = new ParametersMasterPanel(content);
		 * GuiUtil.doDialog(this, panel, new DialogActionListener() {
		 * 
		 * @Override public void closeDialogAction(JPanel p) { doSimulatorAction(); }
		 * });
		 */
		return chosen;
	}

	/**
	 * Initialize common functions for a JTable user interface: single selection and
	 * an Excel enabled menu for right-click options. Enables a table to be copied
	 * to another document such as a spreadsheet.
	 * 
	 * @param table
	 * @param with_menu
	 * @return
	 */
	public static ExcelAdapter initTable(JTable table, boolean with_menu) {
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		ExcelAdapter menuAdapter = null;
		if (with_menu) {
			menuAdapter = new ExcelAdapter(table);
		}
		return menuAdapter;
	}

	public static void showError(final String prefix, final Throwable e1) {
		showError(root_window, prefix, e1);
	}

	public static void showError(final Component parent, final String prefix, final Throwable e1) {
		e1.printStackTrace();

		if ("Setting shape for full-screen window is not supported.".equals(e1.getMessage())) {
			// let the user ignore...
			return;
		}

		Runnable r = new Runnable() {

			@Override
			public void run() {

				String app_info = "Application: " + PrefUtil.getAppName();
				app_info += "\n";
				app_info += "Version: " + PrefUtil.getAppVersion();
				app_info += "\n";

				if (PrefUtil.getAppFile() != null) {
					app_info += "File: " + PrefUtil.getAppFile();
					app_info += "\n";
				}
				// String location =
				// getClass().getClassLoader().getResource("TitanWaterworks.class").getPath();
				// // Gets the path of the class or jar.

				String message = e1.getMessage();
				if (message == null) {
					message = e1.getClass().getName();
				}
				String seperator = "\n\n#\n# ********************************\n#\n\n";
				String summary = app_info + seperator + getSystemPropsAsTxt() + seperator + getEnvironmentAsText()
						+ seperator + prefix + ": " + message;

				ExceptionDialogPanel ld = new ExceptionDialogPanel(summary, e1);
				if (isFullScreen) {
					ld.setSize(600, 300);
					ld.setMinimumSize(new Dimension(600, 300));
					ld.setPreferredSize(new Dimension(600, 300));
					ld.doLayout();
				}

				GuiUtil.doDialog("Application Error", parent, ld, null);
			}

		};

		if (SwingUtilities.isEventDispatchThread())

		{
			r.run();
		} else

		{
			try {
				SwingUtilities.invokeAndWait(r);
			} catch (Exception e) {
				// Not really much to do except give up if you can't tell the
				// user there is a problem.
				e.printStackTrace();
			}
		}

	}

	private static String getSystemPropsAsTxt() {
		Properties props = System.getProperties();

		String txt = "";
		Enumeration<Object> keys = props.keys();
		ArrayList<Object> list = Collections.list(keys);
		Collections.sort(list, new Comparator<Object>() {

			@Override
			public int compare(Object arg0, Object arg1) {
				String s1 = (String) arg0;
				String s2 = (String) arg1;
				return s1.compareTo(s2);
			}
		});

		for (Object key : list) {
			txt = txt + key + "=" + props.getProperty((String) key) + "\n";
		}
		return txt;
	}

	private static String getEnvironmentAsText() {
		Map<String, String> env_map = System.getenv();

		LinkedList<String> keys = new LinkedList<String>(env_map.keySet());
		Collections.sort(keys);
		String txt = "";
		for (String key : keys) {
			txt = txt + key + "=" + env_map.get(key) + "\n";
		}
		return txt;
	}

	public static void showErrorInGuiThread(final String prefix, final Throwable e) {
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				showError(prefix, e);

			}
		});
	}

	public static void initModalDialog(JDialog dummy, JComponent p) {

		Action act = DefaultActions.exitDialogAction;
		Object oName = act.getValue(Action.NAME);

		p.getActionMap().put(oName, act);
		p.getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0),
				oName);
		// p.getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(KeyStroke.getKeyStroke(KeyEvent.VK_ENTER,
		// 0),
		// oName);

		return;
	}

	/*
	 * This routine provides application level setup of a user panel. All JPanel
	 * constructors should call this routine to provide consistent look-n-feel kinds
	 * of setup on the panel.
	 */

	public static void initPanel(JComponent p) {

		// if (clearForm != null)
		// bindPanelClearAction(p, clearForm);
		// if (saveForm != null)
		// bindPanelSaveAction(p, saveForm);

		initUIFixes(p, true);
		return;
	}

	public static String getDateTimeFormatString() {
		return "MM/dd/yyyy HH:mm:ss";
	}

	public static DateFormat getDateTimeFormat() {
		DateFormat datef = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		return datef;
	}

	public static DateFormat getDateFormat() {
		DateFormat datef = new SimpleDateFormat("MM/dd/yyyy");
		return datef;
	}

	public static DateFormat getTimeFormat() {
		DateFormat datef = new SimpleDateFormat("HH:mm:ss");
		return datef;
	}

	public static void initUIFixes(JComponent container, boolean fixDateFormat) {

		Component[] compArray = container.getComponents();

		for (Component comp : compArray) {
			if (comp instanceof JDateChooser) {
				// set the standard date format

				JDateChooser dateChooser = (JDateChooser) comp;
				if (fixDateFormat) {
					dateChooser.setDateFormatString("MM/dd/yyyy");
				}

				// fix the date for dark backgrounds
				IDateEditor editor = dateChooser.getDateEditor();
				JTextFieldDateEditor sub_comp = (JTextFieldDateEditor) editor.getUiComponent();

				comp.addPropertyChangeListener("date", datechooser_colorfixer);
				comp.addFocusListener(datechooser_focusListener);
				sub_comp.addPropertyChangeListener("date", datechooser_colorfixer);
				sub_comp.addFocusListener(datechooser_focusListener);
			}

			if (comp instanceof JPanel) {
				initUIFixes((JPanel) comp, fixDateFormat);
			} else if (comp instanceof JTabbedPane) {
				initUIFixes((JTabbedPane) comp, fixDateFormat);
			} else if (comp instanceof JFormattedTextField) {
				comp.addFocusListener(selectLaterTextFocusListener);
			} else if (comp instanceof JTextComponent) {
				comp.addFocusListener(selectAllTextFocusListener);
			} else if (comp instanceof JSpinner) {
				JSpinner s = (JSpinner) comp;
				s.getEditor().addFocusListener(selectAllTextFocusListener);
			}
		}
	}

	public static void showMessage(final String message) {
		showMessage(message, true);
	}

	public static void showMessage(final String message, final boolean modal) {

		Runnable r = new Runnable() {

			@Override
			public void run() {
				String m = message;
				if (m.startsWith("<!DOCTYPE html")) {
					int beginIndex = m.indexOf("<html", 10);
					if (beginIndex > 0) {
						m = m.substring(beginIndex);
					}
					// clip the DOCTYP&DTD
				}
				if (m.startsWith("<html ")) {
					int beginIndex = m.indexOf(">", 5);
					if (beginIndex > 0) {
						m = "<html>" + m.substring(beginIndex);
					}
					// cut out namespace stuff
				}
				Object o = m;
				// special handling for html?
				if (m.startsWith("<!DOCTYPE html") || m.startsWith("<html")) {
					HTMLEditorKit kit = new HTMLEditorKit();

					// add some styles to the html
//					StyleSheet styleSheet = kit.getStyleSheet();
//					styleSheet.addRule("body {color:#000; font-family:times; margin: 4px; }");
//					styleSheet.addRule("h1 {color: blue;}");
//					styleSheet.addRule("h2 {color: #ff0000;}");
//					styleSheet.addRule("pre {font : 10px monaco; color : black; background-color : #fafafa; }");

					Document doc = kit.createDefaultDocument();

					JEditorPane ed1 = new JEditorPane();
					ed1.setEditorKit(kit);
					ed1.setDocument(doc);
					ed1.setText(m);

					ed1.setEditable(false);
					// JLabel label = new JLabel(m);
					JScrollPane sp = new JScrollPane(ed1);

					sp.setPreferredSize(new Dimension(400, 300));

					JPanel p = new JPanel();

					// ======== this ========
					p.setLayout(new FormLayout("[400dlu,default,600dlu]:grow",
							"fill:[200dlu,default,300dlu]:grow, $lgap, default"));
					p.add(sp, CC.xy(1, 1));

					o = p;
					JOptionPane op = new JOptionPane(p, JOptionPane.PLAIN_MESSAGE, JOptionPane.OK_OPTION);
					JDialog d = op.createDialog(root_window, "Message");
					GuiUtil.initModalDialog(d, op); // makes the escape key work
					d.setModal(modal);
					d.setResizable(true);
					d.pack();
					d.setVisible(true);
				} else {
					JOptionPane.showMessageDialog(root_window, o);
				}
			}

		};

		if (SwingUtilities.isEventDispatchThread()) {
			r.run();
		} else {
			try {
				SwingUtilities.invokeAndWait(r);
			} catch (Exception e) {
				// Not really much to do except give up if you can't tell the
				// user there is a problem.
				e.printStackTrace();
			}
		}

	}

	public static int showConfirmDialog(Object message, String title, int option) {
		return JOptionPane.showConfirmDialog(null, message, title, option);
	}

	public static void initPrinters(JComboBox printerList, String TASK) {
		Object[] ar = ConfigurationInfo.getPrinterList();

		DefaultComboBoxModel m = new DefaultComboBoxModel(ar);
		printerList.setModel(m);

		String namedPrinter = ConfigurationInfo.getSelectedPrinter(TASK);
		PrintService printer = null;
		if (namedPrinter != null) {
			for (int idx = 0; idx < m.getSize(); idx++) {
				String serviceName = m.getElementAt(idx).toString();
				if (namedPrinter.equals(serviceName)) {
					printer = (PrintService) m.getElementAt(idx);
					break;
				}
			}
		}
		if (printer == null) {
			printer = PrintServiceLookup.lookupDefaultPrintService();
		}
		printerList.setSelectedItem(printer); // printer.getName() );
	}

	public static void selectComboString(JComboBox printerList, String value) {
		for (int idx = 0; idx < printerList.getItemCount(); idx++) {
			Object o = printerList.getItemAt(idx);
			if (value.equals(o.toString())) {
				printerList.setSelectedIndex(idx);
				break;
			}
		}

	}

	public static AbstractFormatterFactory getDateTimeFormatterFactory() {
		if (datetimeFactory == null) {
			DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			DateFormatter df = new DateFormatter(dateFormat);

			df.setAllowsInvalid(false);

			datetimeFactory = new DefaultFormatterFactory(df, // default
					df, // display
					df // edit
			);
		}
		return datetimeFactory;
	}

	public static AbstractFormatterFactory getHHMMSSFormatterFactory() {
		if (hhmmssFactory == null) {
			DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
			DateFormatter df = new DateFormatter(dateFormat);

			df.setAllowsInvalid(false);

			hhmmssFactory = new DefaultFormatterFactory(df, // default
					df, // display
					df // edit
			);
		}
		return hhmmssFactory;
	}

	// not sure this is the best place for it, but it needs to be somewhere

	public static AbstractFormatterFactory getCurrencyFormatterFactory() {
		if (currencyFactory == null) {
			DecimalFormat currencyFormat = (DecimalFormat) DecimalFormat.getCurrencyInstance();

			NumberFormatter currencyDisplayFormatter = new NumberFormatter(currencyFormat);

			DecimalFormat currencyEditFormat = new DecimalFormat("#0.00");
			currencyEditFormat.setParseBigDecimal(true);

			NumberFormatter currencyEditFormatter = new NumberFormatter(currencyEditFormat);

			currencyEditFormatter.setAllowsInvalid(true);

			currencyFactory = new DefaultFormatterFactory(currencyDisplayFormatter, // default
					currencyDisplayFormatter, // display
					currencyEditFormatter // edit
			);
		}

		return currencyFactory;
	}

	public static AbstractFormatterFactory getNumberFormatterFactory() {
		if (numberFactory == null) {
			DecimalFormat numFormat = new DecimalFormat("###,##0.0###");
			NumberFormatter num1 = new NumberFormatter(numFormat);
			numFormat.setParseBigDecimal(true);

			DecimalFormat numEditFormat = new DecimalFormat("#0.0###");
			numEditFormat.setParseBigDecimal(true);

			NumberFormatter numEdit = new NumberFormatter(numEditFormat);

			num1.setAllowsInvalid(false);
			// ?numEdit.setMaximum(new Double(30.0));
			numEdit.setAllowsInvalid(true);

			numberFactory = new DefaultFormatterFactory(num1, // default
					num1, // display
					numEdit // edit
			);
		}

		return numberFactory;
	}

	public static AbstractFormatterFactory getIntegerFormatterFactory() {
		if (integerFactory == null) {
			DecimalFormat numFormat = new DecimalFormat("#,##0");
			NumberFormatter num1 = new NumberFormatter(numFormat);
			numFormat.setParseIntegerOnly(true);

			DecimalFormat numEditFormat = new DecimalFormat("#0");
			numEditFormat.setParseIntegerOnly(true);

			NumberFormatter numEdit = new NumberFormatter(numEditFormat);
			numEdit.setValueClass(Integer.class);

			num1.setAllowsInvalid(false);
			numEdit.setAllowsInvalid(true);

			integerFactory = new DefaultFormatterFactory(num1, // default
					num1, // display
					numEdit // edit
			);
		}

		return integerFactory;
	}

	public static boolean doOkDialog(JFrame parent, String title, Component comp) {

		DefaultOkCancelPanel panel = new DefaultOkCancelPanel(comp);
		Object[] options = new Object[] {};
		JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);
		JDialog dlg = op.createDialog(parent, title);
		GuiUtil.initModalDialog(dlg, panel);
		dlg.setResizable(true);
		dlg.pack();
		dlg.setVisible(true);

		return panel.isOk();
	}

	/*
	 * used as an object for scripts
	 */

	public static GuiUtil getInstance() {
		return new GuiUtil();
	}

	public static Color getColorFromName(String color) {
		Color ccolor = Color.MAGENTA;
		if ("red".equalsIgnoreCase(color)) {
			ccolor = Color.RED;
		} else if ("green".equalsIgnoreCase(color)) {
			ccolor = Color.GREEN;
		} else if ("blue".equalsIgnoreCase(color)) {
			ccolor = Color.BLUE;
		} else if ("black".equalsIgnoreCase(color)) {
			ccolor = Color.BLACK;
		} else if ("gray".equalsIgnoreCase(color)) {
			ccolor = Color.GRAY;
		} else if ("orange".equalsIgnoreCase(color)) {
			ccolor = Color.ORANGE;
		}
		return ccolor;
	}

	public static void initColorColumn(TableColumn col, Color[] colors) {
		JComboBox<Color> comboBox = new JComboBox<Color>(colors);
		col.setCellEditor(new DefaultCellEditor(comboBox));
		comboBox.setRenderer(new ColorListCellRenderer());

		// Set up tool tips for the sport cells.
		DefaultTableCellRenderer renderer = new ColorTableCellRenderer();
		renderer.setToolTipText("Click for color list");
		col.setCellRenderer(renderer);
	}

	public static String[] parseArgs(String[] args) {

		List<String> remaining = new LinkedList<String>();

		LogManager.getRootLogger().setLevel((Level) Level.ERROR);
		for (int i = 0; i < args.length; i++) {

			if ("-log".equals(args[i]) || "--log".equals(args[i])) {
				i++;
				String fileName = args[i];
				DateFormat df = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
				Date now = new Date();
				String str = df.format(now);

				if (fileName.indexOf("{Date}") > 0) {
					fileName = fileName.replaceAll("\\{Date\\}", str);
				}
				if (fileName.indexOf("{DATE}") > 0) {
					fileName = fileName.replaceAll("\\{DATE\\}", str);
				}
				GuiUtil.redirectStdOutAndErr("mgDaq", fileName);
				System.out.println("Logging started at " + str);
			} else if ("-d".equals(args[i])) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for DEBUG: {}", loggerName);
				} else {
					System.out.println("setting log level: " + loggerName + " to ALL");
					logger.setLevel(Level.ALL);
				}
			} else if ("-w".equals(args[i])) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for DEBUG: {}", loggerName);
				} else {
					System.out.println("setting log level: " + loggerName + " to WARN");
					logger.setLevel(Level.WARN);
				}
			} else if ("-i".equals(args[i])) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for DEBUG: {}", loggerName);
				} else {
					System.out.println("setting log level: " + loggerName + " to INFO");
					logger.setLevel(Level.INFO);
				}
			} else if ("-ii".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.INFO);
			} else if ("-ww".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.WARN);
			} else if ("-dd".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.DEBUG);
			} else if ("-cap".equals(args[i])) {
				System.setProperty("devicelog_dir", args[++i]);
			} else if ("-jars".equals(args[i])) {
				ClassLoader cl = ClassLoader.getSystemClassLoader();

				if (cl instanceof URLClassLoader) {
					URL[] urls = ((URLClassLoader) cl).getURLs();

					for (URL url : urls) {
						System.out.println(url.getFile());
					}
				} else {
					System.out.println("JARS not available in this classloader: " + cl.getClass().getCanonicalName());
				}
			} else {
				remaining.add(args[i]);
			}
		}

		Thread.setDefaultUncaughtExceptionHandler(new GuiUncaughtExceptionHandler());

		args = new String[remaining.size()];
		remaining.toArray(args);
		return args;
	}

	public static void setRootWindow(Window f) {
		root_window = f;
	}

}
