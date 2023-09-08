package idea.jasper;

import java.awt.Component;
import java.awt.Container;
import java.awt.Cursor;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.DecimalFormat;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.jar.Attributes;
import java.util.jar.Manifest;

import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JFormattedTextField.AbstractFormatterFactory;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.JTextComponent;
import javax.swing.text.NumberFormatter;

import com.toedter.calendar.JDateChooser;

class SelectAllTextRunLater implements Runnable {

	private JFormattedTextField f;

	public SelectAllTextRunLater(JFormattedTextField f) {
		this.f = f;
	}

	public void run() {
		f.selectAll();
	}

}

class TitledModelChangeListener implements PropertyChangeListener {
	String virginTitle;
	JComponent p;

	public TitledModelChangeListener(JComponent p, String title) {
		this.p = p;
		this.virginTitle = title;
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		if ("changed".equals(evt.getPropertyName())) {
			Boolean changed = (Boolean) evt.getNewValue();
			String title = (changed) ? "* " + virginTitle : virginTitle;
			p.putClientProperty("title", title);
		}
	}
}

public class DDD {


	private static FocusListener selectAllTextFocusListener;

	private static FocusListener selectLaterTextFocusListener;

	private static String reportRoot = null;


	private static int fontHeight = 11;

    private DDD() {
        // Override default constructor; prevents instantiation.
    }

	// private static boolean focusManagerInstalled = false;
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
	}

	private static void initSelectAllOnFocus(JComponent container) {

		Component[] compArray = container.getComponents();

		for (Component comp : compArray) {
			if (comp instanceof JDateChooser) {
				// set the standard date format
				JDateChooser dateChooser = (JDateChooser) comp;
				dateChooser.setDateFormatString("MM/dd/yyyy");
			}

			if (comp instanceof JPanel) {
				initSelectAllOnFocus((JPanel) comp);
			} else if (comp instanceof JTabbedPane) {
				initSelectAllOnFocus((JTabbedPane) comp);
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

	public static void setReportRoot(String reportRoot) {
		if (reportRoot != null && !reportRoot.endsWith("/")) {
			reportRoot = reportRoot + "/";
		}
		DDD.reportRoot = reportRoot;
	}

	/**
	 * @return
	 */
	public static String getJasperRoot(boolean versionExtension) {

		Map env = System.getenv();

		String szReportRoot = reportRoot;

		// Map.Entry = entry =
		if (szReportRoot == null) {
			szReportRoot = (String) env.get("RTEX_JASPER_ROOT");
		}

		if (szReportRoot == null) {

			if (!versionExtension) {
				szReportRoot = "c:/opt/workspace/caddo/cardioTool/bin/idea/labels";
			}
			if (versionExtension) {
				szReportRoot = "c:/opt/workspace/caddo/cardioTool/bin/idea/labels";

				String pathToGlazedLists = System.class.getResource("/net/sf/jasperreports/engine/JasperReport.class")
						.toString();
				String manifestPath = pathToGlazedLists.substring(0, pathToGlazedLists.lastIndexOf("!") + 1)
						+ "/META-INF/MANIFEST.MF";
				try {
					Manifest manifest = new Manifest(new URL(manifestPath).openStream());
					Set s = manifest.getEntries().keySet();
					Iterator ii = s.iterator();
					while (ii.hasNext()) {
						System.out.println(ii.next());
					}

					Attributes atts = manifest.getAttributes("net/sf/jasperreports/engine/");

					String rev = atts.getValue("Implementation-Version");

					if (rev != null) {
						szReportRoot += "-" + rev + "/";
					}
				} catch (MalformedURLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

		}

		return szReportRoot;
	}

	/**
	 * 
	 * Performs custom df-security checking only
	 */
	public static Object buildPage(JFrame owner, Class paneClass) throws SecurityException, NoSuchMethodException,
			IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {

		// boolean bAuthorized = true;

		// allow component to check security
		// bAuthorized = DFSecurity.checkCustomAuthentication(paneClass);
		// if (bAuthorized == false)
		// return null;

		// some constructors can take a while
		if (owner != null)
			owner.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

		Object o = null;

		try {
			Method paneBuilder = paneClass.getMethod("createInstance", new Class[] { Container.class });

			Object[] args = { owner };
			o = paneBuilder.invoke(null, args);
			if (owner != null)
				owner.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

		} catch (NoSuchMethodException e) {
			// no error here
		}

		if (o == null) {
			try {
				Constructor paneConstructor = paneClass.getConstructor(new Class[] {});
				o = paneConstructor.newInstance(new Object[] {});

				if (owner != null)
					owner.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
			} catch (NoSuchMethodException e) {
				System.err.println("no such method: " + e.getMessage());
			} catch (Exception e) {
				e.printStackTrace();

				if (owner != null)
					owner.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
				JOptionPane.showMessageDialog(owner, "Error loading page: " + paneClass.getCanonicalName()
						+ "\nMessage: " + e.getMessage());
			}
		}

		return o;
	}

	public static PrompterInterface buildPrompterInterface(Class cl, Object o) {

		PrompterInterface pi = null;

		try {
			Method getter = cl.getMethod("getPrompterInterface", new Class[] { Object.class });

			try {
				Object[] args = { o };
				pi = (PrompterInterface) getter.invoke(null, args);
			} catch (IllegalArgumentException e1) {
				e1.printStackTrace();
			} catch (IllegalAccessException e1) {
				e1.printStackTrace();
			} catch (InvocationTargetException e1) {
				e1.printStackTrace();
			}

		} catch (NoSuchMethodException e) {
			// no error here
		}

		return pi;
	}

	// not sure this is the best place for it, but it needs to be somewhere
	private static DefaultFormatterFactory currencyFactory;

	private static DefaultFormatterFactory numberFactory;

	private static DefaultFormatterFactory integerFactory;

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


	public static void initTable(JTable table) {

		// Defaults are exactly that: original defaults. There must be another
		// way to get
		// the installed values created by initApp();
		//
		// UIDefaults defs = UIManager.getLookAndFeelDefaults();

		// diagnostics output
		if (fontHeight > 0) {
			int hei = fontHeight + 6;
			// System.out.println( "Setting font size: " + hei );
			table.setRowHeight(hei);
		}

		KeyStroke f2 = KeyStroke.getKeyStroke("F2");
		int typ = JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT;
		Object act = table.getInputMap(typ).get(f2);

		if (act != null) {
			System.out.println("?? hel pme act=" + act.toString() + act.hashCode());
			// table.getInputMap( typ ).remove( f2 );
			table.getInputMap(typ).put(f2, null);
			// table.getInputMap(typ).put(f2, DefaultActions.startTableEditsNullAction);
		}

	}

	public static void initTree(JTree tree) {
		if (fontHeight > 0) {
			int hei = fontHeight + 6;
			System.out.println("Setting font size: " + hei);
			tree.setRowHeight(hei);
		}
	}

	public static int getDefaultFontHeight() {
		return fontHeight;
	}


}
