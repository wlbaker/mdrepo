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

import java.awt.Color;

import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class HistogramPanel extends JPanel implements StreamConsumer {
	
	private YAxisPanel yAxisPanel;
	//? private JPanel xAxisPanel;

	public HistogramPanel( ) {
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
		// this.scrollRate = scrollRate;
		chart.setTimeScalesInMillis(widthMs, bufferMs );
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		chart = new HistogramChart();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"25dlu, default:grow",
			"fill:default:grow, 5dlu, fill:default"));

		//---- chart ----
		chart.setBorder(LineBorder.createBlackLineBorder());
		chart.setBackground(new Color(51, 51, 51));
		add(chart, cc.xy(2, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private HistogramChart chart;
	// JFormDesigner - End of variables declaration  //GEN-END:variables


	public HistogramChart getChart() {
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
		chart.streamEvent( jobID, source, sid, item);
	}

	@Override
	public void setName(String name) {
		super.setName(name);
		chart.setName( name );
	}

}
