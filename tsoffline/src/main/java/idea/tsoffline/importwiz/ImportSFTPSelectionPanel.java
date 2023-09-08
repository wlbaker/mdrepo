/*
 * Created by JFormDesigner on Wed Oct 07 11:47:58 CDT 2009
 */

package idea.tsoffline.importwiz;

import java.awt.event.ActionEvent;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Vector;
import java.util.prefs.BackingStoreException;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.SwingWorker;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.ChannelSftp.LsEntry;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.Session;
import com.jcraft.jsch.SftpATTRS;
import com.jcraft.jsch.UserInfo;
import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.TsOfflineSetup;

/*
*         MyUserInfo shared with bernard...maybe roll it into appsupportswing
*/

class MyUserInfo implements UserInfo {

	@Override
	public String getPassphrase() {
		// TODO Auto-generated method stub
		return "passphrase: ";
	}

	@Override
	public String getPassword() {
		// TODO Auto-generated method stub
		return "madmax123";
	}

	@Override
	public boolean promptPassword(String message) {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean promptPassphrase(String message) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean promptYesNo(String message) {
		return true;
	}

	@Override
	public void showMessage(String message) {
		// TODO Auto-generated method stub
		System.out.println("message: " + message);
	}

}

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ImportSFTPSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int REMOTE_FILE_COL = 1;

	private WizardMasterInterface wizard;

	// RpSubject header;
	RpStudy profile;
	private SwingWorker<Integer, Void> worker;

	boolean success;

	private FileOutputStream output;

	private InputStream input;

	public ImportSFTPSelectionPanel(WizardMasterInterface wizard) {
		initComponents();

		hostField.setText(TsOfflineSetup.getSFTPHost());
		this.wizard = wizard;
		retrieve.setEnabled(false);

		statusLabel.setText("");
		DefaultTableModel model = (DefaultTableModel) selectedFile.getModel();
		model.setRowCount(0);
		destFile.setText("/opt/study/idea/dest0.h5");
		
		selectedFile.getSelectionModel().addListSelectionListener(this);
	}

	private void panelToModel(File file) {
		log.error("FIXME: need function PiImporterUtil.getStudyFromFile(file)");
		profile = null; // PiImporterUtil.getStudyFromFile(file);
		return;
	}

	public void startSFTPDownloadWorker(File dest) {

		wizard.enableNext(false);
		wizard.enableFinish(false);
		statusLabel.setText("--");

		worker = new SwingWorker<Integer, Void>() {

			@Override
			protected Integer doInBackground() throws Exception {

				connect.setEnabled(false);
				try {
					boolean complete = ImportSFTPSelectionPanel.this.doInBackground(true, false);
					if( complete ) {
						wizard.enableNext(true);
					}
				} catch (Exception e) {
					statusLabel.setText(e.getMessage());
					throw (e);
				}
				connect.setEnabled(true);

				return 1;
			}

			@Override
			protected void done() {
				if (this.isCancelled()) {
					System.out.println("cleanup partial Files();");
					success = false;
				}
				super.done();
				if (success) {
					wizard.enableNext(true);
					wizard.enableFinish(true);
				} else {
					statusLabel.setVisible(true);
				}
			}

		};

		// worker.addPropertyChangeListener(this);
		worker.execute();

	}

	protected boolean doInBackground(boolean getDevices, boolean getFile) throws Exception {

		success = false;
		String device = (String) deviceSelection.getSelectedItem();
		int selected_file_row = -1;
		if (device != null && selectedFile.getRowCount() > 0) {
			selected_file_row = selectedFile.getSelectedRow();
			if (selected_file_row <= 0) {
				statusLabel.setText("No File Selected");
				return false;
			}
		}

		JSch jsch = new JSch();

		String knownHostsFilename = "/opt/bernard/etc/known_hosts";
		jsch.setKnownHosts(knownHostsFilename);

		Session session = jsch.getSession("bbaker", hostField.getText());
		{
			// "interactive" version
			// can selectively update specified known_hosts file
			// need to implement UserInfo interface
			// MyUserInfo is a swing implementation provided in
			// examples/Sftp.java in the JSch dist

			// UserInfo ui = new MyUserInfo();
			// session.setUserInfo(ui);

			// OR non-interactive version. Relies in host key being in
			// known-hosts file
			session.setPassword("madmax123");
		}

		ChannelSftp sftpChannel = null;
		String remote_file = null;
		try {
			session.connect();

			Channel channel = session.openChannel("sftp");
			channel.connect();
			sftpChannel = (ChannelSftp) channel;

			String me = "idea-erc";
			try {
				sftpChannel.cd(me); // ok to fail
			} catch (Exception e) {
				statusLabel.setText("Host has no ERC data.");
				sftpChannel.disconnect();
				return false;
			}

			if (device == null) {

				Vector ls = sftpChannel.ls(".");
				if (ls == null || ls.size() <= 2) { // should have "." and ".."
					statusLabel.setText("No Device Data");
					sftpChannel.disconnect();
					return false;
				}

				statusLabel.setText("Select Device");
				deviceSelection.setModel(listToComboModel(ls));
				deviceSelection.setEnabled(true);
				sftpChannel.disconnect();
				return false;
			}

			try {
				sftpChannel.cd(device); // ok to fail
			} catch (Exception e) {
				statusLabel.setText("Host has no ERC data.");
				sftpChannel.disconnect();
				return false;
			}

			if (selected_file_row < 0) {
				Vector ls = sftpChannel.ls(".");
				if (ls == null || ls.size() <= 2) { // should have "." and ".."
					statusLabel.setText("No files for device.");
					sftpChannel.disconnect();
					return false;
				}

				listToTableModel(ls, (DefaultTableModel) selectedFile.getModel());

				statusLabel.setText("Select a file to retrieve.");
				sftpChannel.disconnect();
				return false;
			}

			long totSize = 0;
			remote_file = (String) selectedFile.getValueAt(selected_file_row, REMOTE_FILE_COL);
			SftpATTRS lstat = sftpChannel.lstat(remote_file);
			totSize = lstat.getSize();
			// sftpChannel.get("remote-file", "local-file" );
			// OR

			statusLabel.setText(me + "/" + remote_file);

			String local_file = destFile.getText();
			output = new FileOutputStream(local_file);
			input = sftpChannel.get(remote_file);

			copyStreams(totSize);

			success = true;
			statusLabel.setText("Complete");
		} catch (Exception e) {
			e.printStackTrace();
			statusLabel.setText("ERROR: " + e.getMessage());
		} finally {
			if (input != null)
				input.close();
			if (output != null)
				output.close();

			if (success == false && remote_file != null) {
				sftpChannel.rm(remote_file);
			}

			if (sftpChannel != null)
				sftpChannel.exit();
			session.disconnect();
		}

		return success;
	}

	private ComboBoxModel<String> listToComboModel(Vector ls) {
		DefaultComboBoxModel<String> model = new DefaultComboBoxModel<String>();
		int len = ls.size();
		System.out.println("size=" + len);
		for (int idx = 0; idx < len; idx++) {
			ChannelSftp.LsEntry entry = (LsEntry) ls.get(idx);
			if (entry != null) { // this happens
				String fileName = entry.getFilename();
				if (fileName.startsWith(".")) {
					// ignore
				} else {
					model.addElement(entry.getFilename());
				}
			}
		}
		return model;
	}

	private void listToTableModel(Vector ls, DefaultTableModel model) {
		model.setRowCount(0);
		int len = ls.size();
		System.out.println("size=" + len);
		for (int idx = 0; idx < len; idx++) {
			ChannelSftp.LsEntry entry = (LsEntry) ls.get(idx);
			if (entry != null) { // this happens
				String fileName = entry.getFilename();
				if (fileName.startsWith(".")) {
					// ignore
				} else {
					model.addRow(new Object[] { entry, fileName });
				}
			}
		}

		return;
	}

	private void copyStreams(long totSize) throws IOException {
		byte[] buf = new byte[16 * 1024];

		int bytesRead;
		long totRead = 0;

		while ((bytesRead = input.read(buf)) > 0) {
			output.write(buf, 0, bytesRead);
			// if you don't flush, everything is buffered until the end,
			// rendering the pct complete meaningless
			output.flush();

			totRead += bytesRead;
			statusLabel.setText("" + (100 * totRead) / totSize + "%");
		}
		statusLabel.setText("Finalizing...");
	}

	private void saveSFTPHost(String hostName) {
		try {
			TsOfflineSetup.saveSFTPHost(hostName);
		} catch (BackingStoreException e) {
			log.error("saveSFTPHost()", e);
		}
	}

	private void connectActionPerformed(ActionEvent e) {
		startSFTPDownloadWorker(null);
	}

	public File getSelectedFile() {

		File local_file = new File(destFile.getText());
		return local_file;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if( e.getValueIsAdjusting() ) {
			return; // ignore
		}
		if( e.getFirstIndex() >= 0 ) {
			retrieve.setEnabled(true);
		}
	}

	private void retrieveActionPerformed(ActionEvent e) {
		startSFTPDownloadWorker(null);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		label1 = new JLabel();
		hostField = new JTextField();
		connect = new JButton();
		label2 = new JLabel();
		deviceSelection = new JComboBox();
		label3 = new JLabel();
		scrollPane1 = new JScrollPane();
		selectedFile = new JTable();
		panel1 = new JPanel();
		label4 = new JLabel();
		destFile = new JTextField();
		retrieve = new JButton();
		statusLabel = new JLabel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default, $lcgap, right:default, $lcgap, default:grow, $lcgap, [50dlu,default]",
			"default, $lgap, default, $rgap, default, $lgap, fill:default:grow, 2*($lgap, default)"));

		//---- label1 ----
		label1.setText("Host:");
		add(label1, CC.xy(3, 3));
		add(hostField, CC.xy(5, 3));

		//---- connect ----
		connect.setText("Connect");
		connect.addActionListener(e -> connectActionPerformed(e));
		add(connect, CC.xy(7, 3));

		//---- label2 ----
		label2.setText("Device:");
		add(label2, CC.xy(3, 5));

		//---- deviceSelection ----
		deviceSelection.setEnabled(false);
		add(deviceSelection, CC.xy(5, 5));

		//---- label3 ----
		label3.setText("Input File:");
		label3.setVerticalAlignment(SwingConstants.TOP);
		add(label3, CC.xy(3, 7));

		//======== scrollPane1 ========
		{

			//---- selectedFile ----
			selectedFile.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null},
					{null, null},
				},
				new String[] {
					null, null
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = selectedFile.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
			}
			scrollPane1.setViewportView(selectedFile);
		}
		add(scrollPane1, CC.xy(5, 7));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow",
				"default:grow, 2*($lgap, default)"));
		}
		add(panel1, CC.xy(7, 7));

		//---- label4 ----
		label4.setText("Destination:");
		add(label4, CC.xy(3, 9));
		add(destFile, CC.xy(5, 9));

		//---- retrieve ----
		retrieve.setText("Retrieve");
		retrieve.addActionListener(e -> retrieveActionPerformed(e));
		add(retrieve, CC.xy(7, 9));

		//---- statusLabel ----
		statusLabel.setText("text");
		add(statusLabel, CC.xywh(1, 11, 7, 1));
		// //GEN-END:initComponents
	}

	@Override
	public boolean finish() {
		return next();
	}

	@Override
	public boolean next() {

		saveSFTPHost(hostField.getText());

		panelToModel(null); // FIXME: here as a reminder

		return true;
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public RpStudy getSelectedStudy() {
		return profile;
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel label1;
	private JTextField hostField;
	private JButton connect;
	private JLabel label2;
	private JComboBox deviceSelection;
	private JLabel label3;
	private JScrollPane scrollPane1;
	private JTable selectedFile;
	private JPanel panel1;
	private JLabel label4;
	private JTextField destFile;
	private JButton retrieve;
	private JLabel statusLabel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
