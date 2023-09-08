/*
 * Created by JFormDesigner on Wed Oct 21 10:52:08 CDT 2009
 */

package idea.display.simple;

import java.awt.Color;
import java.awt.Font;
import java.text.NumberFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class TwoValuePanel extends JPanel implements StreamConsumer {

	NumberFormat n_fmt = NumberFormat.getNumberInstance();
	String s_fmt = null;
	private String upperLoc;
	private String lowerLoc;

	public TwoValuePanel() {
		initComponents();
	}

	private void setValue(JLabel value, Number number) {
		String val = null;

		if (number != null) {
			if (number instanceof Integer) {
				int ii = (Integer) number;
				if (ii == Integer.MIN_VALUE) {
					val = "--";
				}
			}

			if (val == null) {
				val = _asFormattedString( number );
			}
		}

		if (val == null) {
			val = " ";
		}
		value.setText(val);
	}

	private String _asFormattedString(Number number) {
		String val;
		if( s_fmt != null ) {
			val = String.format(s_fmt, number);
		} else if( n_fmt != null ) {
			val = n_fmt.format(number);
		} else {
			val = "" + number;
		}
		return val;
	}

	public void setFormat( NumberFormat fmt ) {
		this.s_fmt = null;
		this.n_fmt = fmt;
	}
	
	public void setUpperTitle( String title ) {
		this.upperTitle.setText( title );
	}

	public String getUpperTitle() {
		return upperTitle.getText();
	}
	
	public void setLowerTitle( String title ) {
		this.lowerTitle.setText( title );
	}

	public String getLowerTitle() {
		return lowerTitle.getText();
	}
	
	public void setUpperValue(Number val) {
		setValue( upperValue, val );
	}

	public void setLowerValue(Number val) {
		setValue( lowerValue, val );
	}

	public Number getUpperValue() {
		Integer n = 0;
		return n;
	}

	public Number getLowerValue() {
		Integer n = 0;
		return n;
	}

	public void setUpperLoc(String loc) {
		upperLoc = loc;
	}
	public void setLowerLoc(String loc) {
		lowerLoc = loc;
	}
	public void clear() {
		setUpperValue((Number)null);
		setLowerValue((Number)null);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		upperTitle = new JLabel();
		upperValue = new JLabel();
		lowerTitle = new JLabel();
		lowerValue = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(new CompoundBorder(
			new LineBorder(Color.magenta, 2),
			new EmptyBorder(3, 3, 3, 3)));
		setLayout(new FormLayout(
			"[40dlu,default]:grow",
			"2*(default, fill:default:grow)"));

		//---- upperTitle ----
		upperTitle.setText("(upper label)");
		upperTitle.setFont(new Font("Tahoma", Font.PLAIN, 9));
		add(upperTitle, cc.xy(1, 1));

		//---- upperValue ----
		upperValue.setText("0");
		upperValue.setHorizontalAlignment(SwingConstants.TRAILING);
		upperValue.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 30));
		upperValue.setVerticalAlignment(SwingConstants.BOTTOM);
		add(upperValue, cc.xy(1, 2));

		//---- lowerTitle ----
		lowerTitle.setText("(lower label)");
		lowerTitle.setFont(new Font("Tahoma", Font.PLAIN, 9));
		add(lowerTitle, cc.xy(1, 3));

		//---- lowerValue ----
		lowerValue.setText("0");
		lowerValue.setHorizontalAlignment(SwingConstants.TRAILING);
		lowerValue.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 30));
		lowerValue.setVerticalAlignment(SwingConstants.BOTTOM);
		add(lowerValue, cc.xy(1, 4));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel upperTitle;
	private JLabel upperValue;
	private JLabel lowerTitle;
	private JLabel lowerValue;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if( sid == StreamID.MEASUREMENT ) {
			setItem( upperValue, item, upperLoc );
			setItem( lowerValue, item, lowerLoc );
		}
	}

	private void setItem(JLabel label, PersistentItem item2, String loc) {
		if( loc == null ) {
			// ignore?
		} else {
			RpMetric metric = IntfUtil.getMetricByLoc(item2, loc);
			Number value = null;
			if( metric != null ) {
				value = (Number) IntfUtil.getRawValue(item2, metric);;
			}
			if( value != null ) {
				String s_val = _asFormattedString( value );
				label.setText( s_val );
			}
		}
	}

	public void setFormat(String fmt) {
		// TODO Auto-generated method stub
		
	}

	public void setBorderColor(Color color) {
		setBorder(new CompoundBorder(
				new LineBorder(color, 2),
				new EmptyBorder(3, 3, 3, 3)));
	}

	public void setUpperValueString(String t) {
		upperValue.setText( t );
	}

	public void setLowerValueString(String t) {
		lowerValue.setText( t );
	}


}
