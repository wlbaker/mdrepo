package idea.gui;

/*
 * Created on Jan 23, 2006
 *
 */

import java.awt.Container;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.StringTokenizer;

import javax.swing.JComponent;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.KeyStroke;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

/**
 * ExcelAdapter enables Copy-Paste Clipboard functionality on JTables. The clipboard data format used by the adapter is
 * compatible with the clipboard format used by Excel. This provides for clipboard interoperability between enabled
 * JTables and Excel.
 */
public class ExcelAdapter implements ActionListener {
	private String rowstring, value;

	JPopupMenu menu = new JPopupMenu();
	JTable table;
	JMenuItem itemPaste;
	JMenuItem itemCopy;
	JMenuItem itemCopyNoHeader;
	JMenuItem itemSelect;

	MouseAdapter mouseAdapter;

	private StringSelection stsel;

	/**
	 * The Excel Adapter is constructed with a JTable on which it enables Copy-Paste and acts as a Clipboard listener.
	 */
	public ExcelAdapter(JTable table) {
		this(table, null, false);
		Container parent = table.getParent();
		if (parent != null && parent instanceof JScrollPane) {
			JScrollPane sp = (JScrollPane) parent;
			sp.addMouseListener(mouseAdapter);
		}
	}

	public ExcelAdapter(JTable table, JScrollPane sp, boolean pasteable) {

		// ERROR: this is the wrong way to do this: if you want to paste, you need to supply
		// some kind of pasteable interface...needs at least a setValueAt and an addRow()

		this.table = table;

		KeyStroke copy = KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK, false);
		// Identifying the copy KeyStroke user can modify this
		// to copy on some other Key combination.
		KeyStroke paste = KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK, false);
		KeyStroke selectAll = KeyStroke.getKeyStroke(KeyEvent.VK_A, ActionEvent.CTRL_MASK, false);

		// Identifying the Paste KeyStroke user can modify this
		// to copy on some other Key combination.
		table.registerKeyboardAction(this, "Copy", copy, JComponent.WHEN_FOCUSED);
		table.registerKeyboardAction(this, "Paste", paste, JComponent.WHEN_FOCUSED);
		table.registerKeyboardAction(this, "SelectAll", selectAll, JComponent.WHEN_FOCUSED);

		// Create and add a menu item
		itemCopy = new JMenuItem("Copy");
		itemCopy.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				ActionEvent e2 = new ActionEvent(ExcelAdapter.this.table, 0, "Copy");
				ExcelAdapter.this.actionPerformed(e2);
			}

		});

		itemCopyNoHeader = new JMenuItem("Copy w/o Header");
		itemCopyNoHeader.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				ActionEvent e2 = new ActionEvent(ExcelAdapter.this.table, 0, "CopyNoHeader");
				ExcelAdapter.this.actionPerformed(e2);
			}

		});

		if (pasteable) {
			itemPaste = new JMenuItem("Paste");
			itemPaste.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent e) {
					ActionEvent e2 = new ActionEvent(ExcelAdapter.this.table, 0, "Paste");
					ExcelAdapter.this.actionPerformed(e2);
				}

			});
		}

		itemSelect = new JMenuItem("Select All");
		itemSelect.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				ActionEvent e2 = new ActionEvent(ExcelAdapter.this.table, 0, "SelectAll");
				ExcelAdapter.this.actionPerformed(e2);
			}

		});

		menu.add(itemCopy);
		menu.add(itemCopyNoHeader);
		if (pasteable)
			menu.add(itemPaste);
		menu.add(itemSelect);

		// Set the component to show the popup menu
		mouseAdapter = new MouseAdapter() {
			public void mousePressed(MouseEvent evt) {
				if (evt.isPopupTrigger()) {
					menu.show(evt.getComponent(), evt.getX(), evt.getY());
				}
			}

			public void mouseReleased(MouseEvent evt) {
				if (evt.isPopupTrigger()) {
					menu.show(evt.getComponent(), evt.getX(), evt.getY());
				}
			}
		};

		table.addMouseListener(mouseAdapter);
		if (sp != null) {
			sp.addMouseListener(mouseAdapter);
		}
	}

	/**
	 * This method is activated on the Keystrokes we are listening to in this implementation. Here it listens for Copy
	 * and Paste ActionCommands. Selections comprising non-adjacent cells result in invalid selection and then copy
	 * action cannot be performed. Paste is done by aligning the upper left corner of the selection with the 1st element
	 * in the current selection of the JTable.
	 */
	public void actionPerformed(ActionEvent e) {
		Clipboard system = Toolkit.getDefaultToolkit().getSystemClipboard();

		// this could be expanded by looking at the column and row selection values
		JTable table = (JTable) e.getSource();

		/*
		 * OK...this is an obsolete style of coding actions, but it's validated
		 */
		if (e.getActionCommand().startsWith("Copy")) {
			boolean noHeader = e.getActionCommand().compareTo("CopyNoHeader") == 0;
			boolean withHeader = !noHeader; // positive logice is so much nicer than negative logic

			StringBuffer sbf = new StringBuffer();
			// Check to ensure we have selected only a contiguous block of
			// cells
			int numcols = table.getColumnCount(); // jTable1.getSelectedColumnCount();
			int numrows = table.getSelectedRowCount();
			int[] rowsselected = table.getSelectedRows();

			// determine which columns to copy...only visible columns are copied
			boolean tab = false;
			LinkedList<Integer> ll = new LinkedList<Integer>();
			for (int i = 0; i < numcols; i++) {
				TableColumnModel m = table.getColumnModel();
				if (m != null) {
					TableColumn col = m.getColumn(i);
					if (col.getMaxWidth() > 1) {
						ll.add(i);
						if (withHeader) {
							if (tab)
								sbf.append('\t');
							sbf.append( _t(col.getHeaderValue()) );
							tab = true;
						}
					}
				}
			}
			if (withHeader) {
				sbf.append('\n');
			}

			for (int i = 0; i < numrows; i++) {
				Iterator<Integer> ii = ll.iterator();
				while (ii.hasNext()) {
					Object val = table.getValueAt(rowsselected[i], ii.next());
					if (val == null) {
						sbf.append(""); // empty string
						// } else if( val instanceof QtyWithUnit ) {
						// QtyWithUnit qu = (QtyWithUnit)val;
						// sbf.append( qu.getQty() );
						// sbf.append("\t");
						// sbf.append( qu.getUnit() );
					} else {
						sbf.append(val);
					}
					if (ii.hasNext())
						sbf.append('\t');
				}
				sbf.append('\n');
			}
			stsel = new StringSelection(sbf.toString());
			system.setContents(stsel, stsel);
		}
		if (e.getActionCommand().compareTo("Paste") == 0) {
			int startRow = table.getSelectedRow();
			int startCol = table.getSelectedColumn();
			if (startRow < 0) {
				startRow = 0;
			}
			if (startCol < 0) {
				startCol = 0;
			}

			TableModel model = table.getModel();
			TableModel insertable = model;
			if (model instanceof TableSorter) {
				insertable = ((TableSorter) model).getTableModel();
			}
			int columnCount = model.getColumnCount();

			System.err.println(
					"err -- we need to step through the TABLe column sequentially, mapping them to the MODEL columns");
			try {
				String trstring = (String) (system.getContents(this).getTransferData(DataFlavor.stringFlavor));
				System.out.println("String is:" + trstring);
				StringTokenizer st1 = new StringTokenizer(trstring, "\n");
				for (int currentRow = startRow; st1.hasMoreTokens(); currentRow++) {
					rowstring = st1.nextToken();
					StringTokenizer st2 = new StringTokenizer(rowstring, "\t");

					for (int currentColumn = startCol; st2.hasMoreTokens()
							&& currentColumn < columnCount; currentColumn++) {
						if (model.isCellEditable(currentRow, currentColumn) == false) {
							// only insert into editable columns
							continue;
						}
						value = (String) st2.nextToken();
						if (currentRow >= table.getRowCount()) {
							((DefaultTableModel) insertable).addRow(new Object[] { null, null, null });
						}
						model.setValueAt(value, currentRow, currentColumn);
						System.out.println("Putting " + value + "atrow=" + currentRow + "column=" + currentColumn);
					}
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
		if (e.getActionCommand().compareTo("SelectAll") == 0) {
			int tot = table.getRowCount();
			if (tot > 0)
				table.setRowSelectionInterval(0, tot - 1);
		}
	}

	private String _t(Object v) {
		// excel wants to use certain prefixes for formulas
		String headerValue = "" + v;
		if( headerValue.startsWith("+")) {
			headerValue = "'" + headerValue;
		} else if( headerValue.startsWith("-")) {
			headerValue = "'" + headerValue;
		} else if( headerValue.startsWith("=")) {
			headerValue = "'" + headerValue;
		}
		return headerValue;
	}

	public JPopupMenu getPopupMenu() {
		return menu;
	}

	public void enablePaste(boolean enabled) {
		itemPaste.setEnabled(enabled);
	}

	public void enableCopy(boolean enabled) {
		itemCopy.setEnabled(enabled);
	}

	public void enableSelect(boolean enabled) {
		itemSelect.setEnabled(enabled);
	}
}