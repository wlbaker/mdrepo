/*
 * Created on Dec 7, 2004
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package idea.gui;

import java.awt.Color;
import java.awt.Component;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;

import javax.swing.JTable;
import javax.swing.RowSorter;
import javax.swing.Timer;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;

/**
 * 
 */

@SuppressWarnings("serial")
// public class ColorRenderer extends DefaultTableCellRenderer implements ActionListener
public class ColorRenderer implements TableCellRenderer, ActionListener {
	protected JTable table;
	protected Map<Point, Color> colors;
	protected boolean isBlinking = true;
	private Timer timer;
	private Point location;
	private boolean isTimer = false;

	TableCellRenderer defaultRenderer = new DefaultTableCellRenderer();

	LinkedList<TableCellRenderer> rendererList = new LinkedList<TableCellRenderer>();
	LinkedList<Class<?>> rendererType = new LinkedList<Class<?>>();
	private TableSorter sorter;
	private boolean editableHighlight;

	public ColorRenderer(JTable table) {
		this(table, new DefaultTableCellRenderer());
	}

	public ColorRenderer(JTable table, TableCellRenderer defaultRenderer) {
		this(table, defaultRenderer, null);
	}

	public ColorRenderer(JTable table, TableCellRenderer defaultRenderer, TableSorter sorter) {
		this.table = table;
		colors = new HashMap<Point, Color>();
		location = new Point();

		if (defaultRenderer != null) {
			rendererList.add(defaultRenderer);
			rendererType.add(Object.class);
		}

		this.sorter = sorter;
	}

	public void addRenderer(Class<?> cl, TableCellRenderer r) {
		if (r != null) {
			//??
			rendererList.addFirst(r);
			rendererType.addFirst(cl);
		}
	}

	@SuppressWarnings("unchecked")
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
		Class cl = null;
		TableCellRenderer rn = null;

		if (value != null) {
			Iterator<TableCellRenderer> rnii = rendererList.iterator();
			Iterator<Class<?>> clii = rendererType.iterator();
			while (clii.hasNext()) {
				cl = clii.next();
				rn = rnii.next();

				if (cl.isAssignableFrom(value.getClass())) {
					break;
				}
			}
		}

		if (rn == null) {
			rn = defaultRenderer;
		}
		Component result = rn.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);

		boolean editable = table.isCellEditable(row, column); // need this value from table, not model

		RowSorter<? extends TableModel> systemRowSorter = table.getRowSorter();
		if (systemRowSorter != null) {
			row = systemRowSorter.convertRowIndexToModel(row);
		}

		if (isSelected || !isBlinking) {
			Color c = getCellColor(row, column);
			if (c != null) {
				c = c.darker();
				c = c.darker();
				if (editableHighlight && !editable) {
					c = c.darker();
				}
				result.setBackground(c);
			}
			// result.setBackground( table.getBackground() );
		} else {
			Color c = getCellColor(row, column);

			if (c == null) {
				c = table.getBackground();
			}

			if (c == null) {
				c = Color.WHITE;
			}

			if (!table.isEnabled()) { // when taking control of the color, tell the user if tables is disabled
				c = c.darker();
			} else if (editableHighlight && !editable) {
				c = c.darker();
			}

			result.setBackground(c);
		}

		return result;
	}

	public Color getCellColor(int row, int column) {
		column = table.convertColumnIndexToModel(column);
		// row = table.convertRowIndexToModel(  );
		if (sorter != null) {
			row = sorter.modelIndex(row);
		}

		//  Get cell color

		Object key = getKey(row, column);
		Object o = colors.get(key);

		if (o != null)
			return (Color) o;

		//  Get row color

		key = getKey(row, -1);
		o = colors.get(key);

		if (o != null)
			return (Color) o;

		//  Get column color

		key = getKey(-1, column);
		o = colors.get(key);

		if (o != null)
			return (Color) o;

		//  Use default
		return null;
	}

	public void setCellColor(int row, int column, Color color) {
		Point key = new Point(row, column);
		colors.put(key, color);
	}

	public void setColumnColor(int column, Color color) {
		setCellColor(-1, column, color);
	}

	public Color getRowColor(int row) {
		return getCellColor(row, -1);
	}

	public void setRowColor(int row, Color color) {
		setCellColor(row, -1, color);
	}

	private Object getKey(int row, int column) {
		location.x = row;
		location.y = column;
		return location;
	}

	public void startBlinking(int interval) {
		timer = new Timer(interval, this);
		timer.start();
		isTimer = true;
	}

	public void stopBlinking() {
		if (isTimer) {
			timer.stop();
			isTimer = false;
		}
		;
	}

	public void actionPerformed(ActionEvent e) {
		isBlinking = !isBlinking;

		AbstractTableModel model = (AbstractTableModel) table.getModel();

		for (Point key : colors.keySet()) {
			// Point key = (Point)it.next();
			int row = key.x;
			int column = key.y;

			if (column == -1) {
				model.fireTableRowsUpdated(row, row);
			} else if (row == -1) {
				int rows = table.getRowCount();

				for (int i = 0; i < rows; i++) {
					model.fireTableCellUpdated(i, column);
				}
			} else {
				model.fireTableCellUpdated(row, column);
			}
		}
	}

	/**
	 * 
	 */
	public void clear() {
		colors.clear();
	}

	public void setEditableHighlight(boolean editableHighlight) {
		this.editableHighlight = editableHighlight;
	}

	public void removeRow(int row) {

		Iterator<Point> ii;

		LinkedList<Point> adjustable = new LinkedList<Point>();
		LinkedList<Point> removable = new LinkedList<Point>();
		for (Point pt : colors.keySet()) {
			if (pt.x == row) {
				// to avoid ConcurrentModificationException, we have to keep a list and 
				// delete it after the iteration is complete.
				removable.add(pt);
			} else if (pt.x > row) {
				adjustable.add(pt);
			}
		}

		ii = removable.iterator();
		while (ii.hasNext()) {
			Point pt = ii.next();
			colors.remove(pt);
		}

		// you have to sort them, otherwise you end up replacing colors that have
		// not been adjusted.

		Collections.sort(adjustable, new Comparator<Point>() {

			@Override
			public int compare(Point o1, Point o2) {
				int value = o1.x - o2.x;
				if (value == 0)
					value = o1.y - o2.y;
				return value;
			}
		});

		ii = adjustable.iterator();
		while (ii.hasNext()) {
			Point pt = ii.next();
			Color color = colors.remove(pt);

			pt.x--;
			colors.put(pt, color);
		}

	}

	private void dump() {
		for (Point pt : colors.keySet()) {
			System.out.println("pt: " + pt + " color: " + colors.get(pt));
		}
	}

	public void insertRow(int row) {
		Iterator<Point> ii;

		LinkedList<Point> adjustable = new LinkedList<Point>();
		for (Point pt : colors.keySet()) {
			if (pt.x >= row) {
				adjustable.add(pt);
			}
		}

		// you have to sort them, otherwise you end up replacing colors that have
		// not been adjusted.

		Collections.sort(adjustable, new Comparator<Point>() {

			@Override
			public int compare(Point o1, Point o2) {
				int value = o2.x - o1.x;
				if (value == 0)
					value = o2.y - o1.y;
				return value;
			}
		});

		ii = adjustable.iterator();
		while (ii.hasNext()) {
			Point pt = ii.next();
			Color color = colors.remove(pt);

			pt.x++;
			colors.put(pt, color);
		}
	}
}
