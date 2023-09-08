package idea.tsoffline;

import java.awt.Color;

class NamedColor extends Color {
	public NamedColor(String name, Color c) {
		this(name, c.getRed(), c.getGreen(), c.getBlue(), 255);
	}

	public NamedColor(String name, int r, int g, int b, int a) {
		super(r, g, b);
		this.name = name;
	}

	String name;
}

public class ColorManager {

	// http://www.colorcombos.com/color-schemes/233/ColorCombo233.html
	// http://www.colorcombos.com/color-schemes/60/ColorCombo60.html
	// http://www.colorcombos.com/color-schemes/65/ColorCombo65.html
	// http://www.colorcombos.com/color-schemes/249/ColorCombo249.html

	// DI=http://www.digital-images.net/temp/Greyscales_ColorChart/RGB_Grey_equivs.jpg
	private static NamedColor[] colors = new NamedColor[] {
			// BLACK-ON-BLACK new NamedColor("Dark Gray", Color.DARK_GRAY),
			new NamedColor("Red", Color.RED), //
			new NamedColor("Green", Color.GREEN), //
			new NamedColor("Cyan", Color.CYAN), //
			new NamedColor("Blue", Color.BLUE), // Tape#4
			new NamedColor("DI.185", 77, 255, 153, 0), // Tape#5
			new NamedColor("Magenta", Color.MAGENTA), // Tape#6
			new NamedColor("152, 50, 101", 152, 50, 101, 0), // ?7
			new NamedColor("DI.90", 240, 77, 0, 0), // Tape#8
			new NamedColor("DI.166", 255, 204, 0, 0), // Tape#9
			new NamedColor("151, 151, 53", 151, 151, 53, 0), // ?10
			new NamedColor("0, 102, 153", 0, 102, 153, 0), // ?11
			new NamedColor("DI.185", 153, 255, 77, 0), // Tape#12
			new NamedColor("DI.172", 77, 204, 204, 0), // Tape#13
			new NamedColor("DI.109", 204, 77, 77, 0), // Tape#14
			new NamedColor("102, 153, 102", 102, 153, 102, 0), // ?15
			new NamedColor("White", 255, 255, 255, 0), //
			new NamedColor("Yellow", Color.YELLOW), //
			new NamedColor("153, 51, 102", 153, 51, 102, 0), //
			new NamedColor("111, 5, 100", 111, 5, 100, 0), //
			new NamedColor("140, 169, 62", 140, 169, 62, 0), //
			new NamedColor("140, 0, 26", 140, 0, 26, 0), // dark red
			new NamedColor("33, 182, 168", 33, 182, 168, 0), //
			new NamedColor("23, 127, 117", 23, 127, 117, 0), //
			new NamedColor("182, 33, 45", 182, 33, 45, 0), //
			// new NamedColor( "127, 23, 31", 127, 23, 31 , 0 ), .. too close to
			// previous dark red
			new NamedColor("182, 119, 33", 182, 119, 33, 0), //
			new NamedColor("127, 84, 23", 127, 84, 23, 0) };//

	public static Color getDefaultColor(int default_color_idx) {
		return colors[default_color_idx % colors.length];
	}

	public static Color[] getColors() {
		return colors;
	}

	public static byte[] asBytes(Color color) {
		byte [] tso_color = null;
		if (color != null) {
			tso_color = new byte[3];
			tso_color[0] = (byte) color.getRed();
			tso_color[1] = (byte) color.getGreen();
			tso_color[2] = (byte) color.getBlue();
		}
		return tso_color;
	}

	public static Color asColor(byte[] rgb) {
			int r = 256 + rgb[0];
			int g = 256 + rgb[1];
			int b = 256 + rgb[2];
			return new Color(r % 256, g % 256, b % 256);
	}

}
