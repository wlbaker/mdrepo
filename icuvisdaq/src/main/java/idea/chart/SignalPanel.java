/*
 * Created by JFormDesigner on Thu Sep 03 14:00:53 CDT 2009
 */

package idea.chart;

import idea.display.ScaleChangeListener;
import idea.display.YAxisPanel;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.LinkedList;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SignalPanel extends JPanel implements StreamConsumer {
	
	private YAxisPanel yAxisPanel;

	public SignalPanel( ) {
		this( null );
	}
	
	public SignalPanel( RpMetric desc ) {		
		initComponents();

		ui = javax.swing.plaf.basic.BasicPanelUI.createUI(this);

		CellConstraints cc = new CellConstraints();

		yAxisPanel = new YAxisPanel();
		add( yAxisPanel, cc.xy(1, 1));

		addScaleChangeListener( yAxisPanel );
	}

	public void setYLabelRotation(boolean b) {
		yAxisPanel.setLabelRotation(b);
	}

	public void addScaleChangeListener(ScaleChangeListener l) {
		chart.addScaleChangeListener( l );
	}
	
	public void setTimeScalesInMillis( int widthMs, int bufferMs ) {
		chart.setTimeScalesInMillis(widthMs, bufferMs );
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		chart = new SignalChart();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"25dlu, default:grow, default",
			"fill:default:grow, 5dlu, fill:default"));

		//---- chart ----
		chart.setBorder(LineBorder.createBlackLineBorder());
		chart.setBackground(new Color(51, 51, 51));
		add(chart, cc.xy(2, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private SignalChart chart;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	private JPanel legendPanel;


	public SignalChart getChart() {
		return chart;
	}

	public void autoScale() {
		chart.autoScale();
	}

	public void setYAxisLabel(String label) {
		yAxisPanel.setAxisLabel(label);
	}

	public String getYAxisLabel( ) {
		return yAxisPanel.getAxisLabel();
	}
	
	public void clear() {
		chart.clear();
	}

	public boolean isScrolling() {
		return chart.isScrolling();
	}

	public void setScrolling(boolean scrolling) {
		chart.setScrolling( scrolling );
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		
//		Object debug = getClientProperty("debug");
//		if( debug != null ) {
//			System.out.println( "debug goes here");
//		} else {
//			System.out.println( "no-debug");
//		}
		chart.streamEvent( jobID, source, sid, item );
	}

	@Override
	public void setName(String name) {
		super.setName(name);
		chart.setName( name );
	}

	public void setScaleMinY(Double y) {
		chart.setScaleMinY( y );
	}
	
	public Double getScaleMinY() {
		return chart.getScaleMinY( );
	}

	public void setScaleMaxY(Double y) {
		chart.setScaleMaxY( y );
	}
	
	public Double getScaleMaxY() {
		return chart.getScaleMaxY( );
	}

	public void setScaleMinRange(Double y) {
		chart.setScaleMinRange( y );
	}
	
	public Double getScaleMinRange() {
		return chart.getScaleMinRange( );
	}

	public void setDisplayDataPoints(Integer pts) {
		chart.setDisplayDataPoints( pts );
	}
	
	public Integer getDisplayDataPoints() {
		return chart.getDisplayDataPoints( );
	}

	public void showLegend(boolean b) {
		if( legendPanel != null ) {
			remove( legendPanel );
		}
		
		if( b ) {
			LinkedList<WaveformData> signals = chart.getSignals();
			CellConstraints cc = new CellConstraints();

			legendPanel = new JPanel();
			legendPanel.setLayout( new GridLayout(4,  1));
			for( WaveformData signal : signals ) {
				JLabel label = new JLabel( );
				String txt = signal.getCode();
				label.setText( txt );
				label.setForeground( signal.getColor() );
				legendPanel.add( label );
			}
			add( legendPanel, cc.xy(3, 1));

		}
		
	}
}
