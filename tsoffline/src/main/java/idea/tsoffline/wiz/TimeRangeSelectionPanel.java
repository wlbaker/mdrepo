/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.tsoffline.wiz;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.io.IOException;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.swing.ButtonGroup;
import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.ListCellRenderer;

import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.BindingGroup;
import org.jdesktop.beansbinding.Bindings;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.persistence.PiSubjectImporter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.AppUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimelineModel;
import idea.tsoffline.canvas.LinkedNode;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
class TimerangeComboBoxRenderer implements ListCellRenderer {

	private DecimalFormat df3 = new DecimalFormat("0.000");
	protected ListCellRenderer defaultRenderer = null;
	private JComboBox combo;

	// JLabel label = new JLabel();
	// JTextField label = new JTextField(); // ((JTextField)
	// myJComboBox.getEditor().getEditorComponent())
	public TimerangeComboBoxRenderer(JComboBox combo) {
		this.combo = combo;
		defaultRenderer = combo.getRenderer();
	}

	@Override
	public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
			boolean cellHasFocus) {

		PNode node = (PNode) value;
		JLabel label = (JLabel) defaultRenderer.getListCellRendererComponent(list, value, index, isSelected,
				cellHasFocus);
		if (node == null) {
			// null node in list cell -- happens where there is no data
			label.setText("");
		} else {
			double tm = node.getX();
			double y = node.getY(); // we really dont care about y here.
									// it only reflects the node-to-node
									// distance
			Object o = node.getAttribute("item");
			if (o instanceof TsoAnnotationEntryType) {
				TsoAnnotationEntryType item = (TsoAnnotationEntryType) o;
				int seqNo = item.getTempSeq();
				String message = (String) node.getAttribute("txt");
				if (message == null) {
					message = "??";
				}
				String option = (seqNo > 0) ? ": " + seqNo : "";
				label.setText("[ " + df3.format(tm) + " sec] " + message + option);
			} else {
				log.warn("Expecting object of type TsoAnnotationEntryType, but found: {}", o.getClass());
			}
		}

		return label;
	}
};

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class TimeRangeSelectionPanel extends JPanel implements WizardPanelInterface {

	private Date metaStartTime;
	private Date metaEndTime;
	private WizardMasterInterface wizard;

	Date displayStart;
	Date displayEnd;

	private long tm0;

	public TimeRangeSelectionPanel(WizardMasterInterface wiz, TsPSwingCanvas canvas) {
		this(wiz);

		tm0 = 0;
		long startMs = 0;
		long endMs = 0;
		if (canvas != null) {
			tm0 = canvas.getStartTime();
			startMs = canvas.getViewStartTimeMs();
			endMs = canvas.getViewEndTimeMs();
		}
		displayStart = new Date(tm0 + startMs);
		displayEnd = new Date(tm0 + endMs);

		DateFormat df = GuiUtil.getDateTimeFormat();
		DateFormat millidf = new SimpleDateFormat(".SSS");
		displayTimeRange.setText( //
				"From: " + df.format(displayStart) + millidf.format(displayStart) + //
						"  To: " + df.format(displayEnd) + millidf.format(displayEnd) //
		);

		displayRadioButton.setSelected(true);
		setPref(displayRadioButton, AppUtil.getParam("TIMERANGE", "TR_DISPLAY"));
		setPref(eventMarkersRadioButton, AppUtil.getParam("TIMERANGE", "TR_EVENT"));
		setPref(timeRangeRadioButton, AppUtil.getParam("TIMERANGE", "TR_TIMERANGE"));

		enableRealtime(false);
	}

	public void enableRealtime(boolean b) {
		realtimeRadioButton.setEnabled(b);
		rtPanel1.setVisible(b);
		rtPanel2.setVisible(b);
		// this.doLayout();
	}

	private void setPref(JRadioButton rb, Object b) {
		if (b != null) {
			if (b instanceof Boolean) {
				rb.setSelected((Boolean) b);
			} else {
				boolean bb = ((String) b).equals("TRUE");
				rb.setSelected(bb);
			}
		}
	}

	public TimeRangeSelectionPanel(WizardMasterInterface wiz) {
		initComponents();
		setName("Time Range");

		this.wizard = wiz;
		// GuiUtil.initPanel(this);

		AppFrame app = AppFrame.getInstance();
		TsPSwingCanvas canv = app.getCanvas();

		startTimeChooser.setDateFormatString(GuiUtil.getDateTimeFormatString());
		endTimeChooser.setDateFormatString(GuiUtil.getDateTimeFormatString());

		TimelineModel tm = AppModel.getTimelineModel();
		startTimeChooser.setMinSelectableDate(tm.getStartTime());
		endTimeChooser.setMinSelectableDate(tm.getStartTime());
		startTimeChooser.setMaxSelectableDate(tm.getEndTime());
		endTimeChooser.setMaxSelectableDate(tm.getEndTime());
		startTimeChooser.setDate(tm.getStartTime());
		endTimeChooser.setDate(tm.getEndTime());

		startTimeChooser.setForeground(Color.BLACK);
		endTimeChooser.setForeground(Color.BLACK);

		metaStartTime = tm.getStartTime();
		metaEndTime = tm.getEndTime();

		// addStartTime( tm.getStartTime().getTime() );
		// addEndTime( tm.getEndTime().getTime() );

		List<HPSplitableLayer> list = canv.getAnnotationModel();
		if (list == null || list.size() == 0) {
			eventMarkersRadioButton.setEnabled(false);
			startEventLayer.setEnabled(false);
			stopEventLayer.setEnabled(false);
			startEvent.setEnabled(false);
			stopEvent.setEnabled(false);
		} else {
			HPSplitableLayer[] arr = new HPSplitableLayer[list.size()];
			list.toArray(arr);

			startEventLayer.setModel(new DefaultComboBoxModel(arr));
			stopEventLayer.setModel(new DefaultComboBoxModel(arr));
		}

		// need to call this even if there are not layers
		// ...reset model from whatever gui builder left
		startEventLayerActionPerformed(null);
		stopEventLayerActionPerformed(null);

		startEvent.setRenderer(new TimerangeComboBoxRenderer(startEvent));
		stopEvent.setRenderer(new TimerangeComboBoxRenderer(stopEvent));

		timeRangeRadioButton.setSelected(true);
	}

	public void refresh(PiSubjectImporter importer) throws IOException {

		startTimeChooser.setDate(metaStartTime);
		endTimeChooser.setDate(metaEndTime);

	}

	public Date getClipStart() {
		Date tm = null;
		if (timeRangeRadioButton.isSelected()) {
			tm = startTimeChooser.getDate();
			;
		} else if (eventMarkersRadioButton.isSelected()) {
			TimelineModel tmod = AppModel.getTimelineModel();

			PNode node = (PNode) startEvent.getSelectedItem();
			long ms = (long) (node.getX() * 1000.0);
			tm = new Date(tmod.getStartTime().getTime() + ms);
		} else if (displayRadioButton.isSelected()) {
			tm = displayStart;
		} else if (realtimeRadioButton.isSelected()) {
			long ms = displayEnd.getTime();
			tm = new Date(ms - AppUtil.asMilliseconds((String) timeWidth.getSelectedItem()));
		} else {
			log.error("FIXME: no timeframe selected");
		}
		return tm;
	}

	public Date getClipEnd() {
		Date tm = null;
		if (timeRangeRadioButton.isSelected()) {
			tm = endTimeChooser.getDate();
			;
		} else if (eventMarkersRadioButton.isSelected()) {
			TimelineModel tmod = AppModel.getTimelineModel();

			PNode node = (PNode) stopEvent.getSelectedItem();
			long ms = (long) (node.getX() * 1000.0);
			tm = new Date(tmod.getStartTime().getTime() + ms);
		} else if (displayRadioButton.isSelected() || realtimeRadioButton.isSelected()) {
			tm = displayEnd;
		} else {
			log.error("FIXME: no timeframe selected");
		}
		return tm;
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		Date dtStart = startTimeChooser.getDate();
		Date dtEnd = endTimeChooser.getDate();
		if (dtStart == null || dtEnd == null) {
			return;
		}

		if (dtStart.getTime() > dtEnd.getTime()) {
			endTimeChooser.setDate(dtStart);
		}
	}

	private void stopMinActionPerformed(ActionEvent e) {
		Date dt0a = metaStartTime;
		Date dt0b = startTimeChooser.getDate();
		if (dt0a == null || dt0b == null) {
			// keep going
		} else if (dt0b.getTime() < dt0a.getTime()) {
			// set startTime to beginning of data
			startTimeChooser.setDate(dt0a);
		}
		endTimeChooser.setDate(startTimeChooser.getDate());
	}

	private void stopMaxActionPerformed(ActionEvent e) {
		endTimeChooser.setDate(metaEndTime);
	}

	private void plus10MActionPerformed(ActionEvent e) {
		addEndTime(10 * 60 * 1000);
	}

	private void plus1HActionPerformed(ActionEvent e) {
		addEndTime(60 * 60 * 1000);
	}

	private void minus10MActionPerformed(ActionEvent e) {
		addStartTime(-10 * 60 * 1000);
	}

	private void minus1HActionPerformed(ActionEvent e) {
		addStartTime(-60 * 60 * 1000);
	}

	private void addEndTime(long ms) {
		Date dt0 = endTimeChooser.getDate();
		if (dt0 == null) {
			dt0 = startTimeChooser.getDate();
		}
		if (dt0 == null) {
			return;
		}

		dt0.setTime(dt0.getTime() + ms);

		Date metaEnd = metaEndTime;
		if (metaEnd != null) {
			if (dt0.getTime() > metaEnd.getTime()) {
				dt0 = metaEnd;
			}
		}

		endTimeChooser.setDate(dt0);
	}

	private void addStartTime(long ms) {
		Date dt0 = startTimeChooser.getDate();
		if (dt0 == null) {
			dt0 = endTimeChooser.getDate();
		}
		if (dt0 == null) {
			return;
		}

		dt0.setTime(dt0.getTime() + ms);

		Date metaEnd = metaEndTime;
		if (metaEnd != null) {
			if (dt0.getTime() > metaEnd.getTime()) {
				dt0 = metaEnd;
			}
		}

		Date metaStart = metaStartTime;
		if (metaStart != null) {
			if (dt0.getTime() < metaStart.getTime()) {
				dt0 = metaStart;
			}
		}

		startTimeChooser.setDate(dt0);
	}

	private void startMinActionPerformed(ActionEvent e) {
		startTimeChooser.setDate(metaStartTime);
	}

	private void startMaxActionPerformed(ActionEvent e) {
		startTimeChooser.setDate(metaEndTime);
	}

	private void startEventLayerActionPerformed(ActionEvent e) {

		PLayer annos = (PLayer) startEventLayer.getSelectedItem();
//		if (annos == null) {
//			return;
//		}
		PLayer layer = annos; // .getLayer();

		Object seqNo = null;
		if (layer != null) {
			seqNo = layer.getAttribute("@seqNo");
			if (layer.getName().indexOf("Segmentation") > 0) {
				seqNo = true;
			}
		}

		if (seqNo != null) {
			int idx = 0;
			List ll = layer.getChildrenReference();
			Iterator it = ll.iterator();
			while (it.hasNext()) {
				Object o = it.next();
				TsoAnnotationEntryType item = null;
				if (o instanceof LinkedNode) {
					LinkedNode node = (LinkedNode) o; // WLB 012519 it.next();
					item = (TsoAnnotationEntryType) node.getAttribute("item");
				} else if (o instanceof PNode) {
					PNode node = (PNode) o; // WLB 012519 it.next();
					item = (TsoAnnotationEntryType) node.getAttribute("item");
				}

				if (item == null) {
					log.error("Expected 'item' attrib and node type LinkedNode/PNode.  Got node type: {}",
							o.getClass());
				} else {
					item.setTempSeq(++idx);
				}
			}
		}
		startEvent.setModel(buildEventModel(annos));
	}

	private void stopEventLayerActionPerformed(ActionEvent e) {
		PLayer annos = (PLayer) stopEventLayer.getSelectedItem();
		stopEvent.setModel(buildEventModel(annos));
	}

	private ComboBoxModel<PNode> buildEventModel(PLayer annos) {
		DefaultComboBoxModel<PNode> model = new DefaultComboBoxModel();

		Collection<PNode> nodes = null;
		if (annos != null) {
			nodes = annos.getChildrenReference();
		}

		if (nodes != null) {
			for (PNode node : nodes) {
				model.addElement(node); //
			}
		}

		return model;
	}

	private void displayRadioButtonActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		title = compFactory.createSeparator("Time Range");
		panel7 = new JPanel();
		displayRadioButton = new JRadioButton();
		panel1 = new JPanel();
		displayTimeRange = new JLabel();
		panel6 = new JPanel();
		eventMarkersRadioButton = new JRadioButton();
		panel8 = new JPanel();
		label9 = new JLabel();
		startEventLayer = new JComboBox();
		startEvent = new JComboBox();
		label10 = new JLabel();
		stopEventLayer = new JComboBox();
		stopEvent = new JComboBox();
		panel2 = new JPanel();
		timeRangeRadioButton = new JRadioButton();
		panel3 = new JPanel();
		label7 = new JLabel();
		startTimeChooser = new JDateChooser();
		panel5 = new JPanel();
		startMin = new JButton();
		startMax = new JButton();
		minus10M = new JButton();
		minus1H = new JButton();
		label8 = new JLabel();
		endTimeChooser = new JDateChooser();
		panel4 = new JPanel();
		stopMin = new JButton();
		stopMax = new JButton();
		plus10M = new JButton();
		plus1H = new JButton();
		rtPanel1 = new JPanel();
		realtimeRadioButton = new JRadioButton();
		rtPanel2 = new JPanel();
		label1 = new JLabel();
		timeWidth = new JComboBox<>();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow",
				"3*(default, $lgap), default, $ugap, default, $lgap, default, $ugap, 3*(default, $lgap), default"));
		add(title, CC.xy(1, 1));

		// ======== panel7 ========
		{
			panel7.setLayout(new FormLayout("default, $lcgap, default", "default"));

			// ---- displayRadioButton ----
			displayRadioButton.setText("Display");
			displayRadioButton.addActionListener(e -> displayRadioButtonActionPerformed(e));
			panel7.add(displayRadioButton, CC.xy(3, 1));
		}
		add(panel7, CC.xy(1, 5));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("[60dlu,default], $lcgap, default:grow, $lcgap, default", "default"));

			// ---- displayTimeRange ----
			displayTimeRange.setText("From:");
			panel1.add(displayTimeRange, CC.xy(3, 1));
		}
		add(panel1, CC.xy(1, 7));

		// ======== panel6 ========
		{
			panel6.setLayout(new FormLayout("default, $lcgap, default", "default"));

			// ---- eventMarkersRadioButton ----
			eventMarkersRadioButton.setText("Event Markers");
			panel6.add(eventMarkersRadioButton, CC.xy(3, 1));
		}
		add(panel6, CC.xy(1, 9));

		// ======== panel8 ========
		{
			panel8.setLayout(new FormLayout(
					"right:[60dlu,default], $lcgap, [70dlu,default], $lcgap, [110dlu,default], $lcgap, default",
					"default, $lgap, default"));

			// ---- label9 ----
			label9.setText("Start:");
			panel8.add(label9, CC.xy(1, 1));

			// ---- startEventLayer ----
			startEventLayer.addActionListener(e -> startEventLayerActionPerformed(e));
			panel8.add(startEventLayer, CC.xy(3, 1));
			panel8.add(startEvent, CC.xy(5, 1));

			// ---- label10 ----
			label10.setText("Stop:");
			panel8.add(label10, CC.xy(1, 3));

			// ---- stopEventLayer ----
			stopEventLayer.addActionListener(e -> stopEventLayerActionPerformed(e));
			panel8.add(stopEventLayer, CC.xy(3, 3));
			panel8.add(stopEvent, CC.xy(5, 3));
		}
		add(panel8, CC.xy(1, 11));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default, $lcgap, default", "default"));

			// ---- timeRangeRadioButton ----
			timeRangeRadioButton.setText("Time Range");
			panel2.add(timeRangeRadioButton, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 13));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
					"right:60dlu, $lcgap, [80dlu,default], $lcgap, [80dlu,default]:grow, $lcgap, default, $lcgap, [50dlu,default]",
					"default, $lgap, default"));

			// ---- label7 ----
			label7.setText("Start:");
			panel3.add(label7, CC.xy(1, 1));

			// ---- startTimeChooser ----
			startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			startTimeChooser.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					startTimeChooserFocusLost(e);
				}
			});
			panel3.add(startTimeChooser, CC.xy(3, 1));

			// ======== panel5 ========
			{
				panel5.setLayout(new FormLayout(
						"2*(default), $lcgap, [50dlu,default], $lcgap, [50dlu,pref], $lcgap, default", "default"));

				// ---- startMin ----
				startMin.setIcon(
						new ImageIcon(getClass().getResource("/idea/tsoffline/images/left-solid-circle.PNG")));
				startMin.setPreferredSize(new Dimension(24, 21));
				startMin.setMinimumSize(new Dimension(20, 20));
				startMin.addActionListener(e -> startMinActionPerformed(e));
				panel5.add(startMin, CC.xy(1, 1));

				// ---- startMax ----
				startMax.setIcon(
						new ImageIcon(getClass().getResource("/idea/tsoffline/images/right-solid-circle.PNG")));
				startMax.setMinimumSize(new Dimension(24, 21));
				startMax.setPreferredSize(new Dimension(24, 21));
				startMax.addActionListener(e -> startMaxActionPerformed(e));
				panel5.add(startMax, CC.xy(2, 1));

				// ---- minus10M ----
				minus10M.setText("-10min");
				minus10M.addActionListener(e -> minus10MActionPerformed(e));
				panel5.add(minus10M, CC.xy(4, 1));

				// ---- minus1H ----
				minus1H.setText("-1hr");
				minus1H.setActionCommand("-1hr");
				minus1H.addActionListener(e -> minus1HActionPerformed(e));
				panel5.add(minus1H, CC.xy(6, 1));
			}
			panel3.add(panel5, CC.xywh(5, 1, 3, 1));

			// ---- label8 ----
			label8.setText("Stop:");
			panel3.add(label8, CC.xy(1, 3));

			// ---- endTimeChooser ----
			endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel3.add(endTimeChooser, CC.xy(3, 3));

			// ======== panel4 ========
			{
				panel4.setLayout(new FormLayout(
						"2*(default), $lcgap, [50dlu,default], $lcgap, [50dlu,pref], $lcgap, default", "default"));

				// ---- stopMin ----
				stopMin.setIcon(
						new ImageIcon(getClass().getResource("/idea/tsoffline/images/left-solid-circle.PNG")));
				stopMin.setPreferredSize(new Dimension(24, 21));
				stopMin.setMinimumSize(new Dimension(20, 20));
				stopMin.addActionListener(e -> stopMinActionPerformed(e));
				panel4.add(stopMin, CC.xy(1, 1));

				// ---- stopMax ----
				stopMax.setIcon(
						new ImageIcon(getClass().getResource("/idea/tsoffline/images/right-solid-circle.PNG")));
				stopMax.setMinimumSize(new Dimension(24, 21));
				stopMax.setPreferredSize(new Dimension(24, 21));
				stopMax.addActionListener(e -> stopMaxActionPerformed(e));
				panel4.add(stopMax, CC.xy(2, 1));

				// ---- plus10M ----
				plus10M.setText("+10min");
				plus10M.addActionListener(e -> plus10MActionPerformed(e));
				panel4.add(plus10M, CC.xy(4, 1));

				// ---- plus1H ----
				plus1H.setText("+1hr");
				plus1H.addActionListener(e -> plus1HActionPerformed(e));
				panel4.add(plus1H, CC.xy(6, 1));
			}
			panel3.add(panel4, CC.xywh(5, 3, 5, 1));
		}
		add(panel3, CC.xy(1, 15));

		// ======== rtPanel1 ========
		{
			rtPanel1.setLayout(new FormLayout("default, $lcgap, default:grow", "default"));

			// ---- realtimeRadioButton ----
			realtimeRadioButton.setText("Realtime");
			rtPanel1.add(realtimeRadioButton, CC.xy(3, 1));
		}
		add(rtPanel1, CC.xy(1, 17));

		// ======== rtPanel2 ========
		{
			rtPanel2.setLayout(new FormLayout("right:60dlu, $rgap, 80dlu", "default"));

			// ---- label1 ----
			label1.setText("Width:");
			rtPanel2.add(label1, CC.xy(1, 1));

			// ---- timeWidth ----
			timeWidth.setModel(new DefaultComboBoxModel<>(
					new String[] { "3 sec", "6 sec", "15 sec", "30 sec", "60 sec", "10 min", "30 min" }));
			timeWidth.addActionListener(e -> startEventLayerActionPerformed(e));
			rtPanel2.add(timeWidth, CC.xy(3, 1));
		}
		add(rtPanel2, CC.xy(1, 19));

		// ---- buttonGroup2 ----
		ButtonGroup buttonGroup2 = new ButtonGroup();
		buttonGroup2.add(displayRadioButton);
		buttonGroup2.add(eventMarkersRadioButton);
		buttonGroup2.add(timeRangeRadioButton);
		buttonGroup2.add(realtimeRadioButton);

		// ---- bindings ----
		bindingGroup = new BindingGroup();
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, eventMarkersRadioButton,
				BeanProperty.create("selected"), startEventLayer, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, eventMarkersRadioButton,
				BeanProperty.create("selected"), startEvent, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, displayRadioButton,
				BeanProperty.create("selected"), displayTimeRange, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), startTimeChooser, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), endTimeChooser, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, eventMarkersRadioButton,
				BeanProperty.create("selected"), stopEventLayer, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, eventMarkersRadioButton,
				BeanProperty.create("selected"), stopEvent, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), minus10M, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), minus1H, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), startMin, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), startMax, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), stopMin, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), stopMax, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), plus10M, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, timeRangeRadioButton,
				BeanProperty.create("selected"), plus1H, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, realtimeRadioButton,
				BeanProperty.create("selected"), timeWidth, BeanProperty.create("enabled")));
		bindingGroup.bind();
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent title;
	private JPanel panel7;
	private JRadioButton displayRadioButton;
	private JPanel panel1;
	private JLabel displayTimeRange;
	private JPanel panel6;
	private JRadioButton eventMarkersRadioButton;
	private JPanel panel8;
	private JLabel label9;
	private JComboBox startEventLayer;
	private JComboBox startEvent;
	private JLabel label10;
	private JComboBox stopEventLayer;
	private JComboBox stopEvent;
	private JPanel panel2;
	private JRadioButton timeRangeRadioButton;
	private JPanel panel3;
	private JLabel label7;
	private JDateChooser startTimeChooser;
	private JPanel panel5;
	private JButton startMin;
	private JButton startMax;
	private JButton minus10M;
	private JButton minus1H;
	private JLabel label8;
	private JDateChooser endTimeChooser;
	private JPanel panel4;
	private JButton stopMin;
	private JButton stopMax;
	private JButton plus10M;
	private JButton plus1H;
	private JPanel rtPanel1;
	private JRadioButton realtimeRadioButton;
	private JPanel rtPanel2;
	private JLabel label1;
	private JComboBox<String> timeWidth;
	private BindingGroup bindingGroup;

	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return next();
	}

	@Override
	public boolean next() {

		AppUtil.setParam("TIMERANGE", "TR_DISPLAY", displayRadioButton.isSelected());
		AppUtil.setParam("TIMERANGE", "TR_EVENT", eventMarkersRadioButton.isSelected());
		AppUtil.setParam("TIMERANGE", "TR_TIMERANGE", timeRangeRadioButton.isSelected());
		AppUtil.setParam("TIMERANGE", "startTime", getClipStart());
		AppUtil.setParam("TIMERANGE", "stopTime", getClipEnd());

		double startSecs = (getClipStart().getTime() - tm0) / 1000.0;
		double stopSecs = (getClipEnd().getTime() - tm0) / 1000.0;
		AppUtil.setParam("TIMERANGE", "startSecs", startSecs);
		AppUtil.setParam("TIMERANGE", "stopSecs", stopSecs);
		AppUtil.setParam("TIMERANGE", "realtime", realtimeRadioButton.isSelected());
		return true;
	}

	@Override
	public void refresh() {
		wizard.enableNext(true);
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
	}

	public void setTitle(String text) {
		JPanel p = (JPanel) title;
		JLabel label = (JLabel) p.getComponent(0);
		label.setText(text);
	}

	public boolean isRealtime() {
		return realtimeRadioButton.isSelected();
	}

}
