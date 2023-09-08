package idea.display.elegant;

import java.awt.Color;

import idea.display.DisplayUtil;

public class ValueFactory {
	public static ValuePanelInterface createPanel(byte format_id,
			byte foreground) {
		ValuePanelInterface panel = null;

		Color color = DisplayUtil.getColorFromDrager(foreground);
		switch (format_id) {
		case 5:
			panel = new Format5();
			panel.setColor(color);
			break;
		case 9:
			panel = new Format9();
			panel.setColor(color);
			break;
		case 10:
			panel = new Format10();
			panel.setColor(color);
			break;
		case 15:
			panel = new Format15();
			panel.setColor(color);
			break;
		case 19:
			panel = new Format19();
			panel.setColor(color);
			break;

		case 80:
			panel = new Format80();
			panel.setColor(color);
			break;
		case 81:
			panel = new Format81();
			panel.setColor(color);

			break;
		case 82:
			panel = new Format82();
			panel.setColor(color);

			break;
		case 70:
			panel = new Format70Philips3();
			panel.setColor(color);

			break;
		default:
			panel = new ValuePanel(format_id, foreground);
		}

		return panel;
	}
}
