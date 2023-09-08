/*
 * Created by JFormDesigner on Wed Mar 30 11:00:53 CDT 2016
 */

package idea.tsoffline.prefs;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.piccolo2d.PLayer;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.intf.DataTyp;
import idea.message.StreamID;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardPanelInterface;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.SignalImporter;
import idea.tsoffline.canvas.DisplayLayout;
import idea.tsoffline.canvas.LabelType;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.OfflineSignal;

/**
 * @author User #1
 */
@Slf4j
public class ClassicLayoutPanel extends JPanel implements WizardPanelInterface {

	TsPSwingCanvas canvas;

	final static RpMetric emptyMetric;
	final static OfflineSignal emptySig;

	private OfflineSignal[] demoSig;

	private PLayer[] layers;

	static {
		emptyMetric = new RpMetric("", null, null, RpLinearUnit.unit, DataTyp.FLOAT_ARR_TYP);
		emptyMetric.setSampleRate(20);
		emptySig = new OfflineSignal(emptyMetric);
	}

	public ClassicLayoutPanel() {
		initComponents();

		canvas = new TsPSwingCanvas(false, false);
		canvas.setName("classic");

		canvas.showGraphTimeline(false);
		canvas.showGraphScale(false);
		canvas.showCursorValue(false);
		canvas.showGraphLegend(false);
		canvas.setSubtitleVisible(false);

		canvas.setGraphLabelFormat(LabelType.LABEL_REL_MMSS);
		// canvas.setXLabelType(LabelType.NONE);

		canvas.zoomToWidthInMillis(1000);
		canvas.setViewDomainInMillis(0, 1000);
		// canvas.setViewRange(0, 0, 500); // initially there is just one camera...or band

		content.add(canvas, BorderLayout.CENTER);

		DefaultComboBoxModel<DisplayLayout> model = new DefaultComboBoxModel<DisplayLayout>();
		for (DisplayLayout d : DisplayLayout.values()) {
			model.addElement(d);
		}
		layoutCombo.setModel(model);

		buildDemoLayers();
		//buildButtons();

		refresh();
	}

	private void buildDemoLayers() {

		int y_offset = 0;
		layers = new PLayer[16];
		demoSig = new OfflineSignal[16];
		for (int layer_id = 0; layer_id < 16; layer_id++) {
			String name = "**" + layer_id;
			RpMetric demoMetric = new RpMetric(name, name, null, RpLinearUnit.unit, DataTyp.FLOAT_ARR_TYP);
			demoSig[layer_id] = new OfflineSignal(demoMetric);
			demoSig[layer_id].setColor(Color.YELLOW);
			demoSig[layer_id].setDefaultColor(Color.BLUE);
			demoSig[layer_id].setLayerSeq(layer_id);

			PLayer layer = createDemoSignal(layer_id, demoSig[layer_id], y_offset);
			layers[layer_id] = layer;

			y_offset += 50;
		}
	}


	private PLayer createDemoSignal(int method, OfflineSignal demoSig, int y_offset) {
		PLayer layer = new HPPathLayer(demoSig, StreamID.WAVEFORM, "demo");
		demoSig.setColor(Color.CYAN);
		demoSig.setDefaultColor(Color.CYAN);

		double[] data = new double[1024];

		int mult = method / 4 + 1;
		method = method % 4;
		switch (method) {
		default:
		case 0: // sin wave
			for (int i = 0; i < 1024; i++) {
				data[i] = y_offset + 40.0 * Math.sin(mult * 3.1414 * i / 100.0);
			}
			break;
		case 1: // triag wave
			for (int i = 0; i < 1024; i++) {
				data[i] = y_offset + (i % (mult * 50)) / mult;
			}
			break;
		case 2: // square wave
			for (int i = 0; i < 1024; i++) {
				data[i] = y_offset;
				if ((mult * i) % 200 > 100)
					data[i] += 60;
			}
			break;
		case 3: // saw wave
			for (int i = 0; i < 1024; i++) {
				int ridge = (mult * i) % 200;
				if (ridge > 100)
					ridge = 200 - ridge;
				data[i] = y_offset + ridge;
			}
			break;
		}
		SignalImporter.addWaveformData(demoSig, 0, data);

		return layer;
	}

	private void layoutComboActionPerformed(ActionEvent e) {
		DisplayLayout dlayout = (DisplayLayout) layoutCombo.getSelectedItem();
		canvas.setDisplayLayout(dlayout);

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		content = new JPanel();
		panel1 = new JPanel();
		label1 = new JLabel();
		layoutCombo = new JComboBox<>();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, default"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"fill:default:grow"));

			//======== content ========
			{
				content.setLayout(new BorderLayout());

				//======== panel1 ========
				{
					panel1.setLayout(new FormLayout(
						"default, $lcgap, [80dlu,default], $lcgap, default:grow, 3*($lcgap, default)",
						"default"));

					//---- label1 ----
					label1.setText("Layout:");
					panel1.add(label1, CC.xy(1, 1));

					//---- layoutCombo ----
					layoutCombo.addActionListener(e -> layoutComboActionPerformed(e));
					panel1.add(layoutCombo, CC.xy(3, 1));
				}
				content.add(panel1, BorderLayout.NORTH);
			}
			panel2.add(content, CC.xy(1, 1));
		}
		add(panel2, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JPanel content;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox<DisplayLayout> layoutCombo;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void refresh() {
		canvas.zoomToWidthInMillis(1000);
		canvas.setViewDomainInMillis(0, 1000);
		// canvas.setViewRange(0, -100, 1000);

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		return true;
	}

	public DisplayLayout getDisplayLayout() {
		return (DisplayLayout) layoutCombo.getSelectedItem();
	}

	public TsPSwingCanvas getCanvas() {
		return canvas;
	}
}
