/*
 * Created by JFormDesigner on Wed Oct 21 10:52:08 CDT 2009
 */

package idea.display.elegant;

import java.awt.Color;
import java.util.LinkedList;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.display.DisplayUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ValuePanel extends JPanel implements ValuePanelInterface {

	public static final byte CUSTOM_BOX_111 = 111;
	private byte format;
	private JLabel unit1;
	private JLabel alarm1;
	private JLabel value1;
	private JLabel paramCode1;
	private JLabel value3;
	private JLabel paramCode2;
	private JLabel label1;
	private JLabel label3;
	private JLabel value2;
	
	int nparams = 0;

	LinkedList<RpMetric> metrics = new LinkedList<RpMetric>();
	private int verbose = 0;
	private JLabel uomLabel1;
	private DisplayKnob knob1;

	public ValuePanel(byte format, byte foreground) {

		setBorder(new EmptyBorder(2, 4, 0, 4));
		// setBorder(new LineBorder(Color.CYAN, 2));
		Color color = DisplayUtil.getColorFromDrager(foreground);
		setForeground(color);
		setBackground(Color.BLACK);

		setFormat(format);
		setColor( color );

	}

	private void setFormat(byte format) {
		if (format == 17) {
			log.error("format = 17");
			return;
		}
		this.format = format;

		String colLayout = null;
		String rowLayout = null;

		log.debug("format={}", (int) format);
		removeAll();
		switch (format) {
		case 1:
			colLayout = "[20dlu,default],fill:default:grow";
			rowLayout = "fill:default, $nlgap, fill:max(default;20dlu):grow";
			// rowLayout = "default,$lgap,default:grow";
			break;

		case 4:
			colLayout = "[20dlu,default],fill:default:grow";
			rowLayout = "fill:default, $nlgap, fill:max(default;20dlu):grow";
			// rowLayout = "default,$lgap,default:grow";
			break;
		case 2: // spo2
		case 9: // tbasic
			colLayout = "[40dlu,default],fill:default:grow";
			rowLayout = "default,$nlgap,default:grow,$nlgap,default";
			break;
		case 91: // one parameter ventilator
			colLayout = "[80dlu,default]:grow, $lcgap, 50dlu";
			rowLayout = "default, $nlgap, fill:default:grow";
			break;
		case 92: // two parameter ventilator
			// colLayout =
			// "[40dlu,default],right:default:grow,$lgap,right:default:grow,$lgap";
			// rowLayout = "$lgap,default:grow,$lgap";
			colLayout = "[80dlu,default]:grow, $lcgap, default:grow";
			rowLayout = "default, $nlgap, fill:default:grow"; //04Apr16 ,$nlgap
			break;
		case CUSTOM_BOX_111: // CUSTOM used for waveform average value by VIT
								// Hemolung Summary Panel
		case 94: // vent thingie
			colLayout = "default:grow";
			rowLayout = "fill:default:grow, $nlgap, 15dlu";
			break;
		case 95: // circular vent knob thingie
			colLayout = "fill:default:grow";
			rowLayout = "fill:default:grow, $nlgap, 12dlu";
			break;
		case 96:
			colLayout = "right:[15dlu,default]:grow, $lcgap, default, $lcgap, [15dlu,default]:grow";
			rowLayout = "default:grow, $nlgap, default";
			break;
		case 0:
			log.error("FORMAT 0 -- NOT SPECIFIED!");
		default:
			colLayout = "fill:default:grow, $lcgap, fill:default:grow";
			rowLayout = "default:grow,$lgap,default:grow,$lgap,default:grow";
			break;
		}

		if (colLayout != null) {
			this.setLayout(new FormLayout(colLayout, rowLayout));
		}

		CellConstraints cc = new CellConstraints();
		switch (format) {
		case 1:
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(alarm1 = new JLabel(), cc.xy(1, 3));
			add(value1 = new ScaledLabel(), cc.xywh(2, 1, 1, 3));

			paramCode1.setText("HR");
			alarm1.setText("ARR");
			value1.setText("000");
			alarm1.setName("ecg.arr");

			paramCode1.setForeground(Color.red);

			break;
		case 91: // vent 1-field....FiO2
			add(uomLabel1 = new JLabel(), cc.xy(1, 1));
			add(paramCode1 = new JLabel(), cc.xywh(3, 1, 1, 3));
			// add(alarm1 = new JLabel(), cc.xy(1, 3));
			add(value1 = new ScaledLabel(3), cc.xywh(1, 1, 1, 3));
			value1.setHorizontalAlignment(SwingConstants.TRAILING);

			uomLabel1.setText("Vol %");
			paramCode1.setText("FiO2");
			// alarm1.setText("ARR");
			value1.setText("999");
			// alarm1.setName("ecg.arr");

			break;
		case 92: // vent 2-fields
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(value1 = new ScaledLabel(3), cc.xywh(1, 1, 1, 3));
			add(paramCode2 = new JLabel(), cc.xy(3, 1));
			add(value2 = new ScaledLabel(3), cc.xywh(3, 1, 1, 3));
			value1.setHorizontalAlignment(SwingConstants.TRAILING);
			value2.setHorizontalAlignment(SwingConstants.TRAILING);

			paramCode1.setText("v1");
			value1.setText("a92");
			paramCode2.setText("v2");
			value2.setText("b92");
			
			break;
		case 4:
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(value1 = new JLabel(), cc.xy(2, 1));
			add(value2 = new JLabel(), cc.xy(2, 3));
			add(value3 = new ScaledLabel(), cc.xy(1, 3));

			value1.setHorizontalAlignment(SwingConstants.RIGHT);
			value2.setHorizontalAlignment(SwingConstants.RIGHT);

			paramCode1.setText("?ART");
			value1.setText("000");
			value2.setText("000");
			value3.setText("000");
			break;
		case 2: // spo2
		case 9: // tbasic
			// ICP
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(value1 = new JLabel(), cc.xy(2, 1));
			add(paramCode2 = new JLabel(), cc.xy(1, 3));
			add(value2 = new JLabel(), cc.xy(2, 3));

			paramCode1.setText("fmt: " + format);
			value1.setText("000");
			paramCode2.setText("parm2");
			value2.setText("000");
			break;
		case 8: // RESP
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(value1 = new JLabel(), cc.xy(3, 1));
			paramCode1.setText("format: " + format);
			value1.setText("000");
			break;
		case 94:
			add(value1 = new ScaledLabel(), cc.xy(1, 1));
			add(paramCode1 = new JLabel(), cc.xy(1, 3));

			value1.setText("000");
			paramCode1.setText("gFiO2");
			break;
		case 95:
			add(knob1 = new DisplayKnob(), cc.xywh(1, 1, 1, 3));
			add(paramCode1 = new JLabel(), cc.xy(1, 3));

			knob1.setValue(Float.NaN);
			// paramCode1.setText("kFiO2");
			paramCode1.setHorizontalAlignment(SwingConstants.CENTER);
			break;
		case 96: // I:E panel on vent
			ScaledLabel colon;
			add(value1 = new ScaledLabel(), cc.xy(1, 1));
			add(colon = new ScaledLabel(), cc.xy(3, 1));
			add(value2 = new ScaledLabel(), cc.xy(5, 1));

			add(label1 = new JLabel(), cc.xywh(1, 3, 5, 1));

			colon.setText(":");
			label1.setText("I:E");
			label1.setHorizontalAlignment(SwingConstants.CENTER);
			break;
		case CUSTOM_BOX_111:
			add(value1 = new ScaledLabel(), cc.xy(1, 1));
			add(paramCode1 = new JLabel(), cc.xy(1, 3));

			value1.setText("?");
			paramCode1.setText("p");
			break;
		default:
			add(paramCode1 = new JLabel(), cc.xy(1, 1));
			add(value1 = new JLabel(), cc.xy(3, 1));
			add(paramCode2 = new JLabel(), cc.xy(1, 3));
			add(value2 = new JLabel(), cc.xy(3, 3));
			add(label3 = new JLabel(), cc.xy(1, 5));
			add(value3 = new JLabel(), cc.xy(3, 5));
			paramCode1.setText("format: " + format);
			value1.setText("-0.0");
			paramCode2.setText("paramCd2");
			label3.setText("LBL3");
			value3.setText("000");
			break;
		}
		
		// labels should never cover up values...dont know if this works!
		if( uomLabel1 != null ) uomLabel1.setOpaque( false );
		if( paramCode1 != null ) paramCode1.setOpaque( false );
		if( paramCode2 != null ) paramCode2.setOpaque( false );
	}

	@Override
	public void addParameter(RpMetric desc) { // ParamData param) {

		log.info("BETA2: DRAGER VALUE PANEL...needs more work here...next two lines!");
		// String groupCode =
		// InfinityDriver.getSignalGroup(param.getSignalGroup());
		// String paramCode = InfinityDriver.getParamCode(param.getParamID());

		String groupCode = desc.getCode();
		String paramCode = desc.getCode();

		int idx = groupCode.indexOf('.');
		if (idx > 0) {
			paramCode = groupCode.substring(idx + 1);
			groupCode = groupCode.substring(0, idx);
		}

		String loc = "??";

		metrics.add(desc);
		if (desc != null) {
			loc = desc.getLocation().toString();
		}

		switch (metrics.size()) {
		case 1:
			if (paramCode1 == null) {
				// ignore
			} else if (groupCode.equalsIgnoreCase("MGM_CO2")) {
				paramCode = "etCO2*";
				paramCode1.setText("etCO2*");
			} else {
				paramCode1.setText(groupCode);
			}

			if (value1 != null) {
				value1.setText(desc == null ? "??" : desc.getCode());
				value1.setName(loc);
			}

			if (uomLabel1 != null) {
				uomLabel1.setText(desc.getUnit().getUnitName());
			}
			setName(groupCode);
			break;
		case 2:
			if (groupCode.equals("tbasic") || groupCode.startsWith("temp")) {
				paramCode = "Tb";
				// } else if (groupCode.equals("ICO2")) {
				// paramCode = "RRc*";
			} else {
				// paramCode = paramCode.toUpperCase();
			}
			if (paramCode2 != null)
				paramCode2.setText(paramCode);
			if (value2 != null) {
				value2.setText(desc == null ? "??" : desc.getCode());
				value2.setName(loc);
			}

			break;
		case 3:
			if (label3 != null)
				label3.setText(paramCode.toUpperCase());
			if (value3 != null) {
				value3.setText(desc == null ? "??" : desc.getCode());
				value3.setName(loc);
			}
			break;
		case 4:
			if( paramCode1 != null && nparams == 0) {
				paramCode1.setText(desc == null ? "??" : desc.getCode());
			}
		}
		
		nparams++;
	}

	@Override
	public void clear() {
		if (value1 != null)
			value1.setText(" ");
		if (value2 != null)
			value2.setText(" ");
		if (value3 != null)
			value3.setText(" ");
		
	}

	@Override
	public void setValue(RpMetric desc, Object item ) {


		JLabel v = null;
		String itemName = desc.getLocation();

		if (knob1 != null ) {
			RpUnit unit = desc.getUnit();
			
			setKnobValue(desc, unit, itemName, (Number)item);
			return;
		}

		if( itemName == null ) {
			log.error("item loc code cannot be null value={}", value1);
			return;
		}

		if( value1 == null ) {
			log.error("value1 cannot be null item = {}", itemName );
			return;
		}
		if (itemName.equals(value1.getName())) {
			v = value1;
		} else if (value2 != null && itemName.equals(value2.getName())) {
			v = value2;
		} else if (value3 != null && itemName.equals(value3.getName())) {
			v = value3;
		} else if (alarm1 != null && itemName.equals(alarm1.getName())) {
			v = alarm1;
		}

		if (v == null) {
			if (verbose > 0) {
				log.error(" no field for item: " + itemName);
			}
			return;
		}
		String val = ValueHelper.format( format, desc, item );
		if (val != null) {
			v.setText(val);
		}
	}

	private void setKnobValue(RpMetric desc, RpUnit unit,
			String itemName, Number value) {

		if (value == null) {
			knob1.setValue(Float.NaN);
		} else {
			knob1.setValue(value.floatValue());
		}
	}

	@Override
	public boolean containsLoc(String loc) {
		for (RpMetric metric : metrics) {
			if (loc.equals(metric.getLocation())) {
				return true;
			}
		}
		return false;
	}

	@Override
	public void setColor(Color color) {
		JLabel[] labels = new JLabel[] { alarm1, label1, label3, value1,
				value2, value3, paramCode1, paramCode2 };

		for (JLabel v : labels) {
			if (v != null) {
				v.setForeground(color);
			}
		}
	}
}
