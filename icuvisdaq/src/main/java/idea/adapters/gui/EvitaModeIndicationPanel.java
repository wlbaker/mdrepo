package idea.adapters.gui;

import java.awt.BorderLayout;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JLabel;
import javax.swing.JPanel;

import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@SuppressWarnings("serial")
@Slf4j
public class EvitaModeIndicationPanel extends JPanel implements StreamConsumer {

	String[] txtFields = { "txt0", "txt1", "txt2", "txt3", "txt4", "txt5" };

	Map<Integer, String> map = new HashMap<Integer, String>();

	JLabel label;

	public EvitaModeIndicationPanel() {
		setLayout(new BorderLayout());

		label = new JLabel("---");
		add(label, BorderLayout.EAST);

		map.put(0x01, "IPPV");
		map.put(0x02, "IPPV/ASSIST");
		map.put(0x06, "SIMV");
		map.put(0x07, "SIMV/ASB");
		map.put(0x0e, "BIPAP");
		map.put(0x2d, "BIPAP/ASB");
		map.put(0x2e, "SIMV/AutoFlow");
		map.put(0x2f, "SIMV/ASB/AutoFlow");
		map.put(0x30, "IPP/AutoFlow");
		map.put(0x31, "IPP/ASSIST/AutoFlow");
		map.put(0x1a, "APRV");
		map.put(0x0c, "MMV");
		map.put(0x0d, "MMV/ASB");
		map.put(0x32, "MMV/Autoflow");
		map.put(0x33, "MMV/ASB/AutoFlow");
		map.put(0x0a, "CPAP");
		map.put(0x0b, "CPAP/ASB");
		map.put(0x11, "APNEA VENT");
		map.put(0x35, "CPAP/PPS");
		map.put(0x0f, "SYNCHRON MASTER");
		map.put(0x10, "SYNCHRON SLAVE");
		map.put(0x47, "BIPAP/ASSIST");
		map.put(0x20, "Adult");
		map.put(0x3a, "Pediatrics");
		map.put(0x21, "Neonames");
		map.put(0x48, "Invasive Ventilation");
		map.put(0x49, "Non-Invasive Ventilation");
		map.put(0x1e, "STANDBY");
		map.put(0x22, "mmHg");
		map.put(0x23, "kPa");
		map.put(0x24, "%");

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid,
			PersistentItem block) {
		if (sid == StreamID.SETTINGS) {

			boolean first = true;
			StringBuffer out = new StringBuffer();
			for (String field : txtFields) {
				RpMetric metric = IntfUtil.getMetricByLoc(block, field);
				if (metric == null) {
					log.error("no such field for Evita: {}", field);
					continue;
				}
				Object vi = IntfUtil.getRawValue(block, metric);

				if (vi != null) {
					if (vi instanceof Number) {
						Number val = (Number) vi;

						String txt = map.get(val.intValue());
						if (txt != null) {
							if (!first) {
								out.append("/");
							}
							out.append("" + txt);
						}
					} else if (vi instanceof String) {
						String val = (String) vi;

						if (!first) {
							out.append("/");
						}
						out.append("" + val);
					}
				}
				first = false;
			}
			if (out.length() > 0) {
				label.setText(out.toString());
			}
		}
	}

}
