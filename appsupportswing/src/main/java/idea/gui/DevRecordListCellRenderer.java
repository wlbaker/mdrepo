package idea.gui;

import java.awt.Color;
import java.awt.Component;
import java.util.List;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.border.CompoundBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.MatteBorder;

import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryIntf;

@SuppressWarnings("serial")
public class DevRecordListCellRenderer extends JPanel implements ListCellRenderer<DeviceRecord> {
	private CompoundBorder activeBorder;
	private CompoundBorder inactiveBorder;
	private JLabel label = new JLabel();

	public DevRecordListCellRenderer() {
		super();

		activeBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.white), new LineBorder(Color.black));
		inactiveBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.DARK_GRAY), new LineBorder(Color.black));

		setBorder(activeBorder);
	}

	@Override
	public void setEnabled( boolean b ) {
		super.setEnabled( b );;
		setBorder( b ? activeBorder : inactiveBorder );
	}

	@Override
	public Component getListCellRendererComponent(JList<? extends DeviceRecord> list, DeviceRecord value, int index,
			boolean isSelected, boolean cellHasFocus) {
		if( value == null ) {
			label.setText("[NONE]");
		} else {
			String name = null;
			List<DiscoveryIntf> intfs = value.getIntfs();
			if( intfs != null ) {
				for( DiscoveryIntf intf : intfs ) {
					name = intf.getName();
				}
			}
			if( name == null ) {
				name = value.getUniqueID();
			}
			label.setText( name );
		}
		return label;
	}

}
