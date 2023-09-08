/*
 * Created by JFormDesigner on Tue Sep 29 08:41:30 CDT 2009
 */

package idea.meddaq;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.events.ConnectionItem;
import idea.display.InstrumentDisplayInterface;
import idea.display.RefreshablePanel;
import idea.display.elegant.ElegantDisplayForm;
import idea.display.simple.SingleDeviceForm;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.Annotation;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Stroke;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.SwingUtilities;
import javax.swing.border.BevelBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.AnalysisPanelInterface;
import idea.analysis.event.BeatBlock;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

enum RunMode {
	SIMULATION, RUN, STOP
};

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class MedDAQPanel extends JPanel implements StreamConsumer {

	public static final String EDITABLE_DISPLAY = "EditableDisplay";
	//13Apr16 private MedDAQSubpanelInterface subpanel;

	private MessagesPanel messagesPanel;

	private int nglobal_waves;
	private long lastUpdateTm;

	public MedDAQPanel() {

		initComponents();

		messagesPanel = new MessagesPanel();
		addPanel("Messages", messagesPanel, null);

		tabber.setVisible(false);

		tabber.getModel().addChangeListener(new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent e) {
				System.out.println("tabber changed: " + e);
				int idx = tabber.getSelectedIndex();
				boolean editable = false;
				if (idx >= 0) {
					Component o = tabber.getComponentAt(idx);
					if (o instanceof InstrumentDisplayInterface) {
						editable = true;
					}
				}
				putClientProperty(EDITABLE_DISPLAY, editable);
			}
		});
	}

	public void addPanel(String title, Component comp, ConnectionStatus status ) {
		int idx = tabber.getTabCount();
		tabber.add(title, comp);
		tabber.setBackgroundAt(idx, getColorForStatus( status ) );
	}

	public void scrapeScreenValues() {
		int count = tabber.getTabCount();
		for (int index = 0; index < count; index++) {
			Component comp = tabber.getTabComponentAt(index);
			if (comp instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) comp;
				// form.getValues();
			}
		}
	}

	public void setStroke(Stroke stroke) {
		int idx = tabber.getSelectedIndex();
		if (idx >= 0) {
			Component o = tabber.getComponentAt(idx);
			if (o instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) o;
				form.setStroke(stroke);
			} else if (o instanceof ElegantDisplayForm) {
				ElegantDisplayForm form = (ElegantDisplayForm) o;
				form.setStroke(stroke);
			} else {
				System.err.println("DONT KNOW HOW TO SET STROKE THIS FORM: " + o.getName());
			}
		}
	}

	public void autoScale(String loc) {

		int idx = tabber.getSelectedIndex();
		if (idx >= 0) {
			Component o = tabber.getComponentAt(idx);
			if (o instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) o;
				form.autoScale(loc);
			} else if (o instanceof ElegantDisplayForm) {
				ElegantDisplayForm form = (ElegantDisplayForm) o;
				form.autoScale(loc);
			} else {
				log.error("DONT KNOW HOW TO AUTOSCALE FORM: {}", o);
			}
		}
	}

	public SingleDeviceForm[] getDeviceForms() {
		// SingleDeviceForm [] ar =

		ArrayList<SingleDeviceForm> forms = new ArrayList<SingleDeviceForm>();
		for (int i = 0; i < tabber.getTabCount(); i++) {
			Object o = tabber.getComponentAt(i);
			if (o instanceof SingleDeviceForm) {
				forms.add((SingleDeviceForm) o);
			}
		}

		SingleDeviceForm[] ar = null;
		if (forms.size() > 0) {
			ar = new SingleDeviceForm[forms.size()];
			ar = forms.toArray(ar);
		}

		return ar;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		try {
			_signalEvent(jobID, source, sid, item);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	private void _signalEvent(int jobID, final StreamProducer source, StreamID sid, final PersistentItem item)
			throws IOException {

		if (item instanceof BeatBlock) {

			// RWaveEvent e = (RWaveEvent) event;

			// analysisPanel.rwaveDetect(rri, saEntLabel2, e.getPos(),
			// e.getInterval(), e.getAmplitude());

		} else if (sid == StreamID.WAVEFORM) {

		} else if (sid == StreamID.MEASUREMENT) {

		} else if (sid == StreamID.ANNOTATION) {
			// !

		} else if (sid == StreamID.CONNECTION) {
			Runnable r = new Runnable() {

				@Override
				public void run() {
					handleConnectionEvent(source, (ConnectionItem) item);
				}

			};

			if (SwingUtilities.isEventDispatchThread()) {
				r.run();
			} else {
				try {
					SwingUtilities.invokeAndWait(r);
				} catch (Exception e) {
					// Not really much to do except give up if you can't tell the user there is a problem.
					e.printStackTrace();
				}
			}

		} else if (sid == StreamID.ALARM) {
			log.info("ignoring alarm event...change tab colors?");
		} else {
			log.error("unrecognized event: {}", item);
		}

	}

	private void handleConnectionEvent(StreamProducer source, ConnectionItem e) {

		int severity = Alarm.INFO;
		ConnectionStatus status = e.getStatus();
		addMessage(new Date(), source, severity, e.getStatus().toString());

		updateTabColor(source, getColorForStatus( status ) );

	}

	private Color getColorForStatus(ConnectionStatus status) {
		Color color = Color.BLACK;
		if( status == null) {
			// leave it black
		} else if (status == ConnectionStatus.NOT_CONNECTED) {
			color = Color.RED;
		} else if (status == ConnectionStatus.NEGOTIATING) {
			color = Color.ORANGE;
		} else if (status == ConnectionStatus.DATA_AVAILABLE) {
			color = Color.CYAN;  // used by analysis panels
		} else {
			log.error("No color for status: {}", status );
		}

		return color;
	}

	protected void updateTabColor(StreamProducer source, Color color) {
		String sourceName = "Adapter?";
		if (source != null) {
			RpDevice conf = source.getConfiguration();
			if (conf != null) {
				sourceName = conf.getName();
			}
		}

		updateTabColor(sourceName, color);
	}

	public void updateTabColor(String sourceName, Color color) {

		int idx = -1;

		for (int tab = 0; tab < tabber.getComponentCount(); tab++) {
			String title = tabber.getTitleAt(tab);
			if (title == null) {
				log.error("tabber title == null");
				idx = tab;
				break;
			} else if (sourceName == null) {
				log.error("sourcename is NULL");
				idx = tab;
				break;
			} else if (sourceName.equals(title)) {
				idx = tab;
				break;
			}

			Component comp = tabber.getComponentAt(tab);
			if (comp instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) comp;
				StreamProducer driver = form.getDriver();
				if (sourceName.equals(driver.getConfiguration().getName())) {
					idx = tab;
					break;
				}
			}
		}

		if (idx < 0) {
			log.error("device not found: " + sourceName);
			for (int tab = 0; tab < tabber.getComponentCount(); tab++) {
				String title = tabber.getTitleAt(tab);
				System.err.println("checked: " + title);

				Component comp = tabber.getComponentAt(tab);
				if (comp instanceof SingleDeviceForm) {
					SingleDeviceForm form = (SingleDeviceForm) comp;
					StreamProducer driver = form.getDriver();
					System.err.println("   also: " + sourceName + "!=" + driver.getConfiguration().getName());
				}
			}
			return;
		}

		final int r_idx = idx;
		final Color r_color = color;

		Runnable r = new Runnable() {

			@Override
			public void run() {
				log.info("BETA2: WILL GET WRONG TAB IF DEVICES REMOVED"); // FIXME: for version 2
				tabber.setBackgroundAt(r_idx, r_color);

				// try to clear the waveforms when we disconnect
				if (r_color == Color.RED) {
					Component comp = tabber.getComponentAt(r_idx);
					if (comp instanceof RefreshablePanel) {
						((RefreshablePanel) comp).clear();
					}
				}
			}
		};

		SwingUtilities.invokeLater(r);
	}

	public void reset() {
		System.err.println("FIXME: DISCOVER SHOULD HAVE ZEROED THIS...excpet for the analysis panels");
		for (int idx = tabber.getTabCount() - 1; idx > 0; idx--) {
			Component comp = tabber.getComponentAt(idx);
			if (comp instanceof JScrollPane) {
				JScrollPane sp = (JScrollPane) comp;
				comp = sp.getViewport().getView();
			}
			if (comp instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) comp;
				form.getDriver().removeStreamListener(form);
				GuiUtil.showMessage("FIXME: not expecting single device form");
				// do I need a better method to remove stream listeners?
			} else if (comp instanceof ElegantDisplayForm) {
				ElegantDisplayForm form = (ElegantDisplayForm) comp;
				form.getDriver().removeStreamListener(form);
				// do I need a better method to remove stream listeners?
			} else if (comp instanceof AnalysisPanelInterface) {
				AnalysisPanelInterface form = (AnalysisPanelInterface) comp;
				for (StreamProducer producer : form.getSignalProducers()) {
					producer.removeAllStreamListeners();
				}
				// form.getDriver().removeStreamListener(form);
			} else if (comp instanceof MessagesPanel) {
				MessagesPanel form = (MessagesPanel) comp;
				// no special action?
			}
			tabber.removeTabAt(idx);
		}
	}

	public void clear() {

		for (int idx = 0; idx < tabber.getTabCount(); idx++) {
			Component comp = tabber.getComponentAt(idx);
			if (comp instanceof JScrollPane) {
				JScrollPane sp = (JScrollPane) comp;
				comp = sp.getViewport().getView();
			}
			if (comp instanceof SingleDeviceForm) {
				SingleDeviceForm form = (SingleDeviceForm) comp;
				form.clear();
			} else if (comp instanceof ElegantDisplayForm) {
				ElegantDisplayForm form = (ElegantDisplayForm) comp;
				form.clear();
			} else if (comp instanceof AnalysisPanelInterface) {
				AnalysisPanelInterface form = (AnalysisPanelInterface) comp;
				form.clear();
			} else if (comp instanceof MessagesPanel) {
				MessagesPanel form = (MessagesPanel) comp;
				form.clear();
			}
		}

	}

	public void addGlobalPanel(JPanel form) {
		GridBagConstraints c = new GridBagConstraints();
		c.gridx = 0;
		c.gridy = ++nglobal_waves;
		c.gridheight = 80;
		c.weightx = 1.0;
		c.fill = GridBagConstraints.HORIZONTAL;

		globalWavePanel.add(form, c);

		return;
	}

	public void loadAnnotations(PiDatastreamImporter annos) {
		if (annos == null) {
			return;
		}
		try {
			annos.rewind();
			_loadAnnotations(annos);
		} catch (IOException e) {
			// yes, I'm just going to ignore this for now
			e.printStackTrace();
		}
	}

	private void _loadAnnotations(PiDatastreamImporter annos) throws IOException {
		PersistentItem block;
		while ((block = annos.next()) != null) {
			Annotation anno = (Annotation) block;
			addMessage(block.getTm(), null, Alarm.INFO, anno.getMessage());
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		globalWavePanel = new JPanel();
		panel1 = new JPanel();
		tabber = new JTabbedPane();

		// ======== this ========
		setBorder(null);
		setMinimumSize(new Dimension(600, 246));
		setPreferredSize(new Dimension(600, 246));
		setLayout(new FormLayout("$lcgap, [440dlu,default]:grow, $lcgap", "pref, $lgap, fill:default:grow"));

		// ======== globalWavePanel ========
		{
			globalWavePanel.setLayout(new GridBagLayout());
			((GridBagLayout) globalWavePanel.getLayout()).columnWidths = new int[] { 0, 0 };
			((GridBagLayout) globalWavePanel.getLayout()).rowHeights = new int[] { 0, 0 };
			((GridBagLayout) globalWavePanel.getLayout()).columnWeights = new double[] { 1.0, 1.0E-4 };
			((GridBagLayout) globalWavePanel.getLayout()).rowWeights = new double[] { 0.0, 1.0E-4 };
		}
		add(globalWavePanel, CC.xy(2, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("[450dlu,default]:grow", "fill:default:grow"));
			panel1.add(tabber, CC.xy(1, 1));
		}
		add(panel1, CC.xy(2, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel globalWavePanel;
	private JPanel panel1;
	private JTabbedPane tabber;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void addMessage(Date date, Object source, int severity, String msg) {
		messagesPanel.addMessage(date, source, severity, msg);
	}

	public void setRunMode(RunMode runMode) {
		tabber.setVisible(runMode == RunMode.RUN || runMode == RunMode.SIMULATION);

		//13Apr16 if (subpanel != null) {
		//13Apr16	buttonPanel.remove((JPanel) subpanel);
		//13Apr16	subpanel = null;
		//13Apr16 }

		if (runMode == RunMode.STOP) {

		} else if (runMode == RunMode.RUN) {
			//13Apr16 buttonPanel.add((JPanel) (subpanel = new DataCaptureSubpanel()), BorderLayout.CENTER);
			messagesPanel.setSimulate(false);
		} else if (runMode == RunMode.SIMULATION) {
			log.error(
					"FIXME: stub buttonPanel.add((JPanel) (subpanel = new SimulatorControlSubpanel()), BorderLayout.CENTER);");
			tabber.setVisible(true);

			messagesPanel.setSimulate(true);
		}

	}

	public void updateSubPanel(Date dt) {
//13Apr16		if (subpanel != null) {
//13Apr16			subpanel.updateClock(dt);
//13Apr16		}

		// no matter how fast this is called, only update graphs every 10 secs
		long tm = PlatformUtil.currentTimeMillis();
		if (Math.abs(lastUpdateTm - tm) > 10000) {
			Component comp = tabber.getSelectedComponent();
			if (comp instanceof RefreshablePanel) {
				((RefreshablePanel) comp).update();
			}
			lastUpdateTm = tm;
		}

	}

	public void removePanel(String name) {
		int tot = tabber.getTabCount();
		for (int i = 0; i < tot; i++) {
			String title = tabber.getTitleAt(i);
			if (name.equals(title)) {
				tabber.removeTabAt(i);
				break;
			}
		}

	}

	public Component getSelectedPanel() {
		int idx = tabber.getSelectedIndex();
		return tabber.getComponentAt(idx);
	}

}
