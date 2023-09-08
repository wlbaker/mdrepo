/*
 * Created by JFormDesigner on Fri Sep 16 16:38:28 CDT 2016
 */

package idea.tsoffline.tspico;

import java.awt.event.ActionEvent;
import java.util.List;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

import lombok.extern.slf4j.Slf4j;
import idea.ts.TsFilter;
import idea.ts.TsoPrefs;
import idea.tsoffline.AppFrame;
import idea.tsoffline.filter.FilterUtil;

/**
 * @author User #1
 */
@Slf4j
class LegendPopupMenu extends JPopupMenu {
	private LegendTool tool;

	public LegendPopupMenu(LegendTool tool) {
		initComponents();

		this.tool = tool;
	}

	/**
	 * Create the list of filters from application preferences for display in the menu.
	 * This routine should be called before displaying (show()) the menu.
	 */
	public void refresh() {
		filterMenu.removeAll();

		TsoPrefs prefs = AppFrame.getInstance().getPrefs();
		if( prefs == null ) {
			log.warn("Preferences not (yet) available.");
			return;
		}
		List<TsFilter> filters = prefs.getFilters();

		for (TsFilter filter : filters) {

			JMenuItem mi = new JMenuItem();
			mi.setText(filter.getName());
			mi.setActionCommand(filter.getName());
			mi.addActionListener(e -> applyFilterActionPerformed(e));
			filterMenu.add(mi);
		}

		// ---- resetFilter ----
		filterMenu.addSeparator();
		resetFilter.setText("Reset");
		resetFilter.addActionListener(e -> resetFilterActionPerformed(e));
		filterMenu.add(resetFilter);

	}

	private void propertiesItemActionPerformed(ActionEvent e) {
		tool.firePropertiesNotificiation();
	}

	private void hideItemActionPerformed(ActionEvent e) {
		tool.fireHideNotificiation();
	}

	private void deleteItemActionPerformed(ActionEvent e) {
		tool.fireDeleteNotificiation();
	}

	private void applyFilterActionPerformed(ActionEvent e) {
		String action = e.getActionCommand();
		
		TsFilter filter = FilterUtil.findFilterFromName(action); 
		tool.fireFilterNotificiation(filter);

	}

	private void applyFilter3ActionPerformed(ActionEvent e) {
		//tool.fireFilterNotificiation("3");
	}

	private void applyFilter5ActionPerformed(ActionEvent e) {
		//tool.fireFilterNotificiation("5");
	}

	private void resetFilterActionPerformed(ActionEvent e) {
		tool.fireFilterNotificiation(null);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		filterMenu = new JMenu();
		applyFilter3 = new JMenuItem();
		applyFilter5 = new JMenuItem();
		resetFilter = new JMenuItem();
		hideItem = new JMenuItem();
		deleteItem = new JMenuItem();
		propertiesItem = new JMenuItem();

		//======== this ========

		//======== filterMenu ========
		{
			filterMenu.setText("Filter...");

			//---- applyFilter3 ----
			applyFilter3.setText("3pt");
			applyFilter3.addActionListener(e -> applyFilter3ActionPerformed(e));
			filterMenu.add(applyFilter3);

			//---- applyFilter5 ----
			applyFilter5.setText("5pt");
			applyFilter5.addActionListener(e -> applyFilter5ActionPerformed(e));
			filterMenu.add(applyFilter5);
			filterMenu.addSeparator();

			//---- resetFilter ----
			resetFilter.setText("Reset");
			resetFilter.addActionListener(e -> resetFilterActionPerformed(e));
			filterMenu.add(resetFilter);
		}
		add(filterMenu);

		//---- hideItem ----
		hideItem.setText("Hide");
		hideItem.addActionListener(e -> hideItemActionPerformed(e));
		add(hideItem);

		//---- deleteItem ----
		deleteItem.setText("Delete");
		deleteItem.addActionListener(e -> deleteItemActionPerformed(e));
		add(deleteItem);
		addSeparator();

		//---- propertiesItem ----
		propertiesItem.setText("Properties");
		propertiesItem.addActionListener(e -> propertiesItemActionPerformed(e));
		add(propertiesItem);
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JMenu filterMenu;
	private JMenuItem applyFilter3;
	private JMenuItem applyFilter5;
	private JMenuItem resetFilter;
	private JMenuItem hideItem;
	private JMenuItem deleteItem;
	private JMenuItem propertiesItem;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
