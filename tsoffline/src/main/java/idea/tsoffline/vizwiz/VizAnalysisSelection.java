/*
 * Created by JFormDesigner on Tue Jan 11 14:36:21 CST 2011
 */

package idea.tsoffline.vizwiz;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpAnalysis;
import lombok.extern.slf4j.Slf4j;
import idea.analysis.AnalysisFactory;
// import idea.analysis.SBSegmentFilter;
import idea.gui.TableSorter;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class VizAnalysisSelection extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int OBJECT_COL = 0;
	private static final int NAME_COL = 1;
	
	private WizardMasterInterface wiz;
	private RpAnalysis anal;

	private static boolean init_plugins = true;

	public VizAnalysisSelection(WizardMasterInterface wiz) {
		initComponents();

		if (init_plugins) {
			initPlugins();
			init_plugins = false;
		}
		this.wiz = wiz;
		
		initTable();
		refresh();
	}

	private void initTable() {
			TableSorter sorter = new TableSorter(table.getModel());

			table.setAutoCreateColumnsFromModel(false);
			table.setModel(sorter);
			sorter.setTableHeader(table.getTableHeader());
			sorter.setSortingStatus(NAME_COL, TableSorter.ASCENDING);

			table.getSelectionModel().addListSelectionListener(this);
	}

	private void initPlugins() {
		// dummy reference to tell the class loader to find this package...needed by AnalysisFactory()
		// System.err.println(SBSegmentFilter.class);
		System.err.println("SBSegmentFilter.class");
		List<RpAnalysis> analyses = AnalysisFactory.getAnalyses();
		
		ArrayList<String> rfiles = null;
		try {
			rfiles = getPluginFileList("idea.tsoffline.r");
		} catch (Exception e) {
			log.error("plug init error", e);
		}
		
		if( rfiles != null ) {
			for( String f : rfiles ) {
				File ff = new File(f);
				RpAnalysis analysis = new RAnalysisWrapper( ff.getName(), f );
				analyses.add(analysis);
			}
		}
	}

	private ArrayList<String> getPluginFileList(String pkgname) throws IOException {

		ArrayList<String> rfiles = new ArrayList<String>();

		File directory = null;
		String fullPath;
		String relPath = pkgname.replace('.', '/');

		Enumeration<URL> resources = ClassLoader.getSystemClassLoader().getResources(relPath);
		while (resources.hasMoreElements()) {
			URL resource = resources.nextElement();
			log.info("ClassDiscovery: Resource = {}", resource);
			if (resource == null) {
				throw new RuntimeException("No resource for " + relPath);
			}
			fullPath = resource.getFile();

			try {
				directory = new File(resource.toURI());
			} catch (URISyntaxException e) {
				throw new RuntimeException(pkgname + " (" + resource
						+ ") does not appear to be a valid URL / URI.  Strange, since we got it from the system...", e);
			} catch (IllegalArgumentException e) {
				directory = null;
			}
			log.info("ClassDiscovery: Directory = {}", directory);

			if (directory != null && directory.exists()) {
				// Get the list of the files contained in the package
				File[] files = directory.listFiles();
				for (int i = 0; i < files.length; i++) {
					// we are only interested in .r files
					String path = files[i].getPath();
					if (path.endsWith(".r")) {
						rfiles.add(path);
					}
				}
			} else {
				String jarPath = fullPath.replaceFirst("[.]jar[!].*", ".jar").replaceFirst("file:", "");
				jarPath = jarPath.replace("%20", " ");
				JarFile jarFile = new JarFile(jarPath);
				Enumeration<JarEntry> entries = jarFile.entries();
				while (entries.hasMoreElements()) {
					JarEntry entry = entries.nextElement();
					String entryName = entry.getName();
					if (entryName.startsWith(relPath) && entryName.length() > (relPath.length() + "/".length())) {
						log.info("ClassDiscovery: JarEntry: {}", entryName);
						if (entryName.endsWith(".r")) {
							log.info("R FILE FOUND in CP: {}", entryName);
							rfiles.add(entryName);
						}
					}
				}
				jarFile.close();
			}
		}

		return rfiles;

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Analysis");
		scrollPane1 = new JScrollPane();
		table = new JTable();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[350dlu,default]:grow",
			"default, $lgap, fill:default:grow"));
		add(separator2, CC.xy(1, 1));

		//======== scrollPane1 ========
		{

			//---- table ----
			table.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null},
				},
				new String[] {
					"O", "Description", "Detail"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false, false
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(200);
				cm.getColumn(2).setPreferredWidth(400);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, CC.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator2;
	private JScrollPane scrollPane1;
	private JTable table;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		//		TreePath path = tree.getSelectionPath();
		//		Object userobj = path.getLastPathComponent();

		return true;
	}

	@Override
	public void refresh() {
		TableSorter sorter = (TableSorter)table.getModel();
		DefaultTableModel model = (DefaultTableModel)sorter.getTableModel();
		model.setRowCount(0);


		List<RpAnalysis> analyses = AnalysisFactory.getAnalyses();
		if (analyses != null) {
			for (RpAnalysis analysis : analyses) {
				model.addRow(new Object[] { analysis, analysis.getName(), analysis.getAnalysisClass() });
			}
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public RpAnalysis getAnalysis() {
		return anal;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		boolean hasNext = false;
		int idx = table.getSelectedRow();

		if (e.getValueIsAdjusting() || idx < 0) {
			// ignore path removed
		} else {
			Object userobj = table.getValueAt(idx, OBJECT_COL);
			if (userobj instanceof RpAnalysis) {
				anal = ((RpAnalysis) userobj);
				hasNext = true;
			}

		}

		wiz.enableNext(hasNext);
		wiz.enableFinish(false);
	}
}
