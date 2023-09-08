/*
 * Created by JFormDesigner on Thu Nov 03 13:26:31 CDT 2016
 */

package idea.tsoffline.video;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.Timer;

import com.github.hoary.javaav.CodecID;
import com.github.hoary.javaav.Encoder;
import com.github.hoary.javaav.MediaPacket;
import com.github.hoary.javaav.Options;
import com.github.hoary.javaav.PixelFormat;
import com.github.hoary.javaav.VideoFrame;

//import org.jcodec.api.awt.SequenceEncoder;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import heatMap.Gradient;
import heatMap.HeatMap;
import idea.gui.WizardPanelInterface;
import idea.schema.rp.RpMetric;

/***
 * 
 * Options options = new Options();
options.put("tune", "zerolatency");
options.put("preset", "ultrafast");

Encoder encoder = new Encoder(CodecID.H264);
encoder.setPixelFormat(PixelFormat.YUV420P);
encoder.setImageWidth(1280);
encoder.setImageHeight(720);
encoder.setGOPSize(25);
encoder.setBitrate(2000000);
encoder.setFramerate(25);
encoder.open(options);

BufferedImage image = ...;
VideoFrame frame = VideoFrame.create(image);

MediaPacket packet = encoder.encodeVideo(frame);

... send packet over a network, write it to a file or whatever

encoder.close();
 */
/**
 * @author User #1
 */
public class TsPhaseControlPanel extends JPanel implements ActionListener, WizardPanelInterface {
	TsPhaseCanvas canvas;
	Timer swingTimer;
	private long tm0;

	ImageIcon[] icons;
	String[] names = { "GRADIENT_BLACK_TO_WHITE", "GRADIENT_BLUE_TO_RED", "GRADIENT_GREEN_YELLOW_ORANGE_RED",
			"GRADIENT_HEAT", "GRADIENT_HOT", "GRADIENT_MAROON_TO_GOLD", "GRADIENT_RAINBOW", "GRADIENT_RED_TO_GREEN",
			"GRADIENT_ROY" };
	Color[][] gradients = { Gradient.GRADIENT_BLACK_TO_WHITE, Gradient.GRADIENT_BLUE_TO_RED,
			Gradient.GRADIENT_GREEN_YELLOW_ORANGE_RED, Gradient.GRADIENT_HEAT, Gradient.GRADIENT_HOT,
			Gradient.GRADIENT_MAROON_TO_GOLD, Gradient.GRADIENT_RAINBOW, Gradient.GRADIENT_RED_TO_GREEN,
			Gradient.GRADIENT_ROY };
	private double speed_mult;
	// SequenceEncoder enc;
	Encoder enc;
	private File outputFile;

	public TsPhaseControlPanel() {
		initComponents();
		canvas = new TsPhaseCanvas();

		contentPanel.add(canvas, BorderLayout.CENTER);

		swingTimer = new Timer(30, this);
		swingTimer.setRepeats(true);

		canvas.updateGradient(gradients[0]);
		speed_mult = 1.0;
		speed.setSelectedItem("1X");
		outputName.setText("");
	}

	/** Returns an ImageIcon, or null if the path was invalid. */
	protected static ImageIcon createImageIcon(String path) {
		java.net.URL imgURL = HeatMap.class.getResource(path);
		if (imgURL != null) {
			return new ImageIcon(imgURL);
		} else {
			System.err.println("Couldn't find file: " + path);
			return null;
		}
	}

	class ComboBoxRenderer extends JLabel implements ListCellRenderer {
		public ComboBoxRenderer() {
			setOpaque(true);
			setHorizontalAlignment(LEFT);
			setVerticalAlignment(CENTER);
		}

		public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
				boolean cellHasFocus) {
			int selectedIndex = ((Integer) value).intValue();
			if (isSelected) {
				setBackground(list.getSelectionBackground());
				setForeground(list.getSelectionForeground());
			} else {
				setBackground(list.getBackground());
				setForeground(list.getForeground());
			}

			ImageIcon icon = icons[selectedIndex];
			setIcon(icon);
			setText(names[selectedIndex].substring(9));
			return this;
		}
	}

	private JComboBox createGradientCombo() {
		icons = new ImageIcon[names.length];
		Integer[] intArray = new Integer[names.length];
		for (int i = 0; i < names.length; i++) {
			intArray[i] = new Integer(i);
			icons[i] = createImageIcon("images/" + names[i] + ".gif");
		}

		JComboBox cb = new JComboBox(intArray);
		ComboBoxRenderer renderer = new ComboBoxRenderer();
		cb.setRenderer(renderer);

		return cb;
	}

	private void resumeActionPerformed(ActionEvent e) {

		tm0 = System.currentTimeMillis();
		swingTimer.start();

	}

	private void pauseActionPerformed(ActionEvent e) {
		swingTimer.stop();
	}

	private void rewindActionPerformed(ActionEvent e) {
		tm_ms = 0;
		canvas.clear();
		if (enc != null) {
			try {
				enc.close();
				//JCODEC enc.finish();
				outputName.setText("[Rewind: " + outputFile.getPath() + "]");
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			enc = null;
		}
	}

	private void gradientComboBoxItemStateChanged(ItemEvent e) {
		// must be from the combo box
		Integer ix = (Integer) e.getItem();
		if (e.getStateChange() == ItemEvent.SELECTED) {
			canvas.updateGradient(gradients[ix]);
		}
	}

	private void speedItemStateChanged(ItemEvent e) {
		String selectedItem = (String) e.getItem();
		if (selectedItem != null) {
			selectedItem = selectedItem.replace("X", "");
			speed_mult = Double.parseDouble(selectedItem);
		}
	}

	private void exportAsMovieActionPerformed(ActionEvent e) {
		String suffix = "";
		int idx = 0;
		do {
			outputFile = new File("c:/tmp/movie" + suffix + ".mp4");
			suffix = "" + (--idx);
		} while	( outputFile.exists() );
		
		outputName.setText(outputFile.getPath());

		if (enc != null) {
			try {
				enc.close();
				//JCODEC enc.finish();
			} catch (Exception e1) {
				// ignore
			}
			enc = null;
		}

		try {
			//JCODEC enc = new SequenceEncoder(outputFile);
			Options options = new Options();
			options.put("tune", "zerolatency");
			options.put("preset", "ultrafast");

			enc = new Encoder(CodecID.H264);
			enc.setPixelFormat(PixelFormat.YUV420P);
			enc.setImageWidth(1280);
			enc.setImageHeight(720);
			enc.setGOPSize(25);
			enc.setBitrate(2000000);
			enc.setFramerate(25);
			enc.open(options);
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		contentPanel = new JPanel();
		panel1 = new JPanel();
		gradientComboBox = createGradientCombo();
		outputName = new JLabel();
		exportAsMovie = new JButton();
		rewind = new JButton();
		pause = new JButton();
		speed = new JComboBox<>();
		resume = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[350dlu,default]:grow",
			"default, $lgap, fill:[200dlu,default]:grow, $lgap, default"));

		//======== contentPanel ========
		{
			contentPanel.setLayout(new BorderLayout());
		}
		add(contentPanel, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[150dlu,default], $lcgap, default:grow, 5*($lcgap, default)",
				"default"));

			//---- gradientComboBox ----
			gradientComboBox.addItemListener(e -> gradientComboBoxItemStateChanged(e));
			panel1.add(gradientComboBox, CC.xy(1, 1));

			//---- outputName ----
			outputName.setText("text");
			panel1.add(outputName, CC.xy(3, 1));

			//---- exportAsMovie ----
			exportAsMovie.setText("Export As Movie");
			exportAsMovie.addActionListener(e -> exportAsMovieActionPerformed(e));
			panel1.add(exportAsMovie, CC.xy(5, 1));

			//---- rewind ----
			rewind.setIcon(new ImageIcon(getClass().getResource("/idea/image/rewind-hot-icon.png")));
			rewind.addActionListener(e -> rewindActionPerformed(e));
			panel1.add(rewind, CC.xy(7, 1));

			//---- pause ----
			pause.setIcon(new ImageIcon(getClass().getResource("/idea/image/Pause-Normal-icon.png")));
			pause.setToolTipText("Pause");
			pause.setMaximumSize(new Dimension(23, 23));
			pause.setMinimumSize(new Dimension(23, 23));
			pause.setPreferredSize(new Dimension(23, 23));
			pause.addActionListener(e -> pauseActionPerformed(e));
			panel1.add(pause, CC.xy(9, 1));

			//---- speed ----
			speed.setModel(new DefaultComboBoxModel<>(new String[] {
				"10X",
				"1X",
				"0.5X",
				"0.25X",
				"0.1X",
				"0.01X"
			}));
			speed.setSelectedIndex(1);
			speed.addItemListener(e -> speedItemStateChanged(e));
			panel1.add(speed, CC.xy(11, 1));

			//---- resume ----
			resume.setIcon(new ImageIcon(getClass().getResource("/idea/image/Play-1-Hot-icon.png")));
			resume.setToolTipText("Resume");
			resume.setMaximumSize(new Dimension(23, 23));
			resume.setMinimumSize(new Dimension(23, 23));
			resume.setPreferredSize(new Dimension(23, 23));
			resume.addActionListener(e -> resumeActionPerformed(e));
			panel1.add(resume, CC.xy(13, 1));
		}
		add(panel1, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel contentPanel;
	private JPanel panel1;
	private JComboBox gradientComboBox;
	private JLabel outputName;
	private JButton exportAsMovie;
	private JButton rewind;
	private JButton pause;
	private JComboBox<String> speed;
	private JButton resume;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void setDataPackets( double[][] xx, double[][] yy) {
		canvas.setDataPackets( xx, yy);
	}

	public void setDataArray( double[] xx, double[] yy) {
		canvas.setDataArray( xx, yy);
	}

	public void setSignalInfo(RpMetric sigInfo) {
		canvas.setSignalInfo(sigInfo);
	}

	long tm_ms;

	@Override
	public void actionPerformed(ActionEvent e) {
		long additional_ms = System.currentTimeMillis() - tm0;
		tm0 = System.currentTimeMillis();

		if (additional_ms > 1000) {
			return; // ignore unrealistic delay
		}

		int loop_counter = (int) speed_mult;

		int dt = (int) (33 * speed_mult);
		if( dt <= 0 ) {
			dt = 1;
		}
		if( dt > 33 ) {
			dt = 33;
		}
		
		do {
			tm_ms += dt;

			if (canvas.update(tm_ms) == false) {
				swingTimer.stop();
				if (enc != null) {
					try {
						enc.close();
						//JCODEC enc.finish();
						outputName.setText("[Complete: " + outputFile.getPath() + "]");
					} catch (Exception e1) {
						outputName.setText(e1.getMessage());
					}
					enc = null;
				}
			} else {
				if (enc != null) {
					BufferedImage image = createScreenshot();
					try {
						VideoFrame frame = VideoFrame.create(image);

						MediaPacket packet = enc.encodeVideo(frame);

						//JCODEC enc.encodeImage(image);
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			}
		} while ((loop_counter--) > 0);

	}

	private BufferedImage createScreenshot() {
		JComponent p = canvas;
		int w = p.getWidth();
		int h = p.getHeight();
		int type = BufferedImage.TYPE_INT_RGB;
		BufferedImage out = new BufferedImage(w, h, type);
		Graphics2D g2 = out.createGraphics();
		p.paint(g2);
		g2.dispose();

		return out;
	}

	@Override
	public void refresh() {
		// ignore
	}

	@Override
	public void previous() {
		// ?
	}

	@Override
	public boolean next() {
		return false;
	}

	@Override
	public boolean finish() {
		return true; // finish pass-through...let the canvas be displayed!
	}

}
