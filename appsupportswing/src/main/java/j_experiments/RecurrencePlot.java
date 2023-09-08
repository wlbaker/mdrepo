package j_experiments;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.DataBuffer;
import java.awt.image.DataBufferByte;
import java.awt.image.Raster;
import java.awt.image.SampleModel;
import java.awt.image.SinglePixelPackedSampleModel;
import java.awt.image.WritableRaster;

import heatMap.Gradient;

public class RecurrencePlot {

	public Color[] colors;
	double[] series;
	int[] w;

	Image image;
	private Graphics g;
	private int m;
	private int d;
	private int eps;
	private int nt;
	private int end_time;
	private Color bg = Color.BLACK;
	private int width;
	private int height;

	public RecurrencePlot(int width, int height, int m, int d, int eps, int nt, int end_time) {
		this.m = m;
		this.d = d;
		this.eps =eps;
		this.nt = nt;
		this.end_time = end_time;
		this.width = width;
		this.height = height;
		// colors = generateColors(20);

        Color[] gradientColors = new Color[]{Color.blue,Color.red};
        colors = Gradient.createMultiGradient(gradientColors, 50);

		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);// new
																				// java.util.Hashtable());

		w = new int[m];
		for (int i = 0; i < m; i++) {
			w[i] = i * d;
		}
		// .checkEmbParms(series, m, d)
		assert (eps > 0) : "eps must be positive";

		if (nt <= 0)
			nt = 1;

	}

	public Color[] generateColors(int n) {
		Color[] cols = new Color[n];
		for (int i = 0; i < n; i++) {
			cols[i] = Color.getHSBColor((float) i / (float) n, 0.85f, 1.0f);
		}
		return cols;
	}

	private void generateElaborateImage(int width, int height, int loc) {
		ColorModel colorModel = generateColorModel();

		// Generate the pixel data; this method is defined in
		// Creating an Image from an Array of Color-Indexed Pixel Values
		byte[] pixels = generatePixels(width, height, loc);

		// Create a data buffer using the byte buffer of pixel data.
		// The pixel data is not copied; the data buffer uses the byte buffer
		// array.
		DataBuffer dbuf = new DataBufferByte(pixels, width * height, 0);

		// The number of banks should be 1
		int numBanks = dbuf.getNumBanks(); // 1

		// Prepare a sample model that specifies a storage 4-bits of
		// pixel datavd in an 8-bit data element
		int bitMasks[] = new int[] { (byte) 0xf };
		SampleModel sampleModel = new SinglePixelPackedSampleModel(DataBuffer.TYPE_BYTE, width, height, bitMasks);

		// Create a raster using the sample model and data buffer
		WritableRaster raster = Raster.createWritableRaster(sampleModel, dbuf, null);

		// Combine the color model and raster into a buffered image
		image = new BufferedImage(colorModel, raster, false, null);// new
																	// java.util.Hashtable());

	}

	private byte[] generatePixels(int width, int height, int loc) {
		// TODO Auto-generated method stub
		return null;
	}

	private ColorModel generateColorModel() {
		// TODO Auto-generated method stub
		return null;
	}

	private double dist(int i, int j) {
		double dsq = 0;
		for (int ii = 0; ii < w.length; ii++) {
			double d0 = (series[i + w[ii]] - series[j + w[ii]]);
			dsq += (d0 * d0);
		}
		return dsq;
	}

	public void isr_recurrencePlot(double[] x ) {
		series = x;


		
		int n = series.length - (m - 1) * d;
		if (end_time > n)
			end_time = n;
		int eps_sq = eps * eps;

		// REMOVE FROM R CODE....
		// xyz = .embeddPSR(series, m = m, d = d)[1:end_time, ]

		g = image.getGraphics();
		clear( g, bg );
		
		// System.out.println( "nt=" + nt + " end_time=" + end_time + " x.length=" + x.length);
		
		for (int i = 1; i < end_time; i += nt) {
			for (int j = i; j < end_time; j += nt) {
				double dd = dist(i, j);
				if (dd < eps_sq) {
					int q = (int) (dd / 2);
					if (q >= colors.length) {
						q = colors.length - 1;
					}
					q = colors.length - q - 1;

					g.setColor(colors[q]);
					
					g.drawRect(i/nt, j/nt, 1, 1);
					g.drawRect(j/nt, i/nt, 1, 1);
				}
			}
		}
		g.dispose();
	}

	public Image getImage() {
		return image;
	}

	public void setImageBackground( Color color) {
		bg = color;
	}

	public void clear( Graphics g, Color color) {

		g.setColor(color);
		g.fillRect(0, 0, width, height);
	}

}
