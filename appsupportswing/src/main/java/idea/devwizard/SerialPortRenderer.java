package idea.devwizard;

import java.awt.Component;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellRenderer;

import com.fazecast.jSerialComm.SerialPort;

import lombok.extern.slf4j.Slf4j;

/*
 * 
 * NOTE: this cell renderer is backwards...it should really subclass DefaultCellRenderer
 * this class should be depricated and replaced with a slightly different one
 * 
 */
@Slf4j
@SuppressWarnings("serial")
public class SerialPortRenderer extends DefaultTableCellRenderer {
	protected TableCellRenderer parent;
	JLabel label;
	Icon [] icon = new ImageIcon[8];

	protected static ImageIcon createImageIcon(String path) {
		java.net.URL imgURL = SerialPortRenderer.class.getResource(path);
		if (imgURL != null) {
			return new ImageIcon(imgURL);
		} else {
			System.err.println("Couldn't find file: " + path);
			return null;
		}
	}
	
	public SerialPortRenderer( TableCellRenderer parent ) {
		this.parent = parent;
		label = new JLabel();
		
		icon[0] = createImageIcon("images/000.gif");
		icon[1] = createImageIcon("images/001.gif");
		icon[2] = createImageIcon("images/010.gif");
		icon[3] = createImageIcon("images/011.gif");
		icon[4] = createImageIcon("images/100.gif");
		icon[5] = createImageIcon("images/101.gif");
		icon[6] = createImageIcon("images/110.gif");
		icon[7] = createImageIcon("images/111.gif");

	}
	
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
	
		System.out.println("r");
		
		JLabel l;
		if( parent == null ) {
			l = (JLabel)super.getTableCellRendererComponent( table, value, isSelected, hasFocus, row, column);
		} else {
			l = (JLabel)parent.getTableCellRendererComponent( table, value, isSelected, hasFocus, row, column);
		}

		label.setSize( l.getSize() );
		label.setBorder( l.getBorder() );
		label.setBackground( l.getBackground() );
		label.setForeground( l.getForeground() );
		label.setOpaque( l.isOpaque() );
		
		SerialPort port = (SerialPort)value;
		int idx = 0;
		log.error("FIXME: read CD, CTS, DSR in jSerialComm?");
//rxtx		idx += port.isCD() ? 4 : 0;
//rxtx		idx += port.isCTS() ? 2 : 0;
//rxtx		idx += port.isDSR() ? 1 : 0;
		label.setIcon( icon[idx] );
		
		if( value == null ) {
			label.setText(port.getDescriptivePortName());
		}
		
		return label;
	}

}
