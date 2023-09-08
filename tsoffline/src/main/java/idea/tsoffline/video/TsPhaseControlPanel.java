/*
 * Created by JFormDesigner on Thu Nov 03 13:26:31 CDT 2016
 */

package idea.tsoffline.video;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.imageio.ImageIO;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JToggleButton;
import javax.swing.ListCellRenderer;
import javax.swing.Timer;
import javax.swing.filechooser.FileFilter;

import org.bytedeco.javacpp.avcodec;
import org.bytedeco.javacpp.avutil;
import org.bytedeco.javacv.FFmpegFrameRecorder;
import org.bytedeco.javacv.Frame;
import org.bytedeco.javacv.Java2DFrameConverter;
import org.bytedeco.javacv.OpenCVFrameConverter.ToIplImage;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.event.PInputEventListener;
import org.piccolo2d.nodes.PPath;

//import com.github.hoary.javaav.CodecID;
//import com.github.hoary.javaav.Encoder;
//import com.github.hoary.javaav.MediaPacket;
//import com.github.hoary.javaav.Options;
//import com.github.hoary.javaav.PixelFormat;
//import com.github.hoary.javaav.VideoFrame;

//import org.jcodec.api.awt.SequenceEncoder;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import heatMap.Gradient;
import heatMap.HeatMap;
import idea.display.ImageSelection;
import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppFrame;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.util.OpenFileFilter;

//http://www.programcreek.com/java-api-examples/index.php?api=org.bytedeco.javacv.FFmpegFrameRecorder

@SuppressWarnings("serial")
/**
 * @author User #1
 */
@Slf4j
public class TsPhaseControlPanel extends JPanel implements ActionListener, WizardPanelInterface {
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

	private static final int SWING_TIMER_MS = 50;

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

	long tm0;

	@Getter
	TsPhaseSpaceCanvas canvas;
	Timer swingTimer;

	DateFormat snapshot_dateformat = new SimpleDateFormat("yyyy-MM-dd_HHmmss");
	int snapshot_interval = 300; // sec
	int snapshot_time_sod = 0; // time for the next snapshot...secs of the
								// current day
	int current_time_sod = 0; // time for the next snapshot...secs of the
								// current day

	int recorder_fps = 20;
	int display_dt = 0;
	ImageIcon[] icons;
	String[] names = { "GRADIENT_BLACK_TO_WHITE", "GRADIENT_BLUE_TO_RED", "GRADIENT_GREEN_YELLOW_ORANGE_RED",
			"GRADIENT_HEAT", "GRADIENT_HOT", "GRADIENT_MAROON_TO_GOLD", "GRADIENT_RAINBOW", "GRADIENT_RED_TO_GREEN",
			"GRADIENT_ROY" };
	Color[][] gradients = { Gradient.GRADIENT_BLACK_TO_WHITE, Gradient.GRADIENT_BLUE_TO_RED,
			Gradient.GRADIENT_GREEN_YELLOW_ORANGE_RED, Gradient.GRADIENT_HEAT, Gradient.GRADIENT_HOT,
			Gradient.GRADIENT_MAROON_TO_GOLD, Gradient.GRADIENT_RAINBOW, Gradient.GRADIENT_RED_TO_GREEN,
			Gradient.GRADIENT_ROY };
	private double speed_mult;

	// JCODEC SequenceEncoder enc;
	// JAVAAV Encoder enc;
	// FrameRecorder enc;
	Java2DFrameConverter paintConverter;
	ToIplImage iplConverter;

	private File outputFile;

	private FFmpegFrameRecorder enc;

	long tm_ms;
	DecimalFormat df0 = new DecimalFormat("0");

	public TsPhaseControlPanel() {
		initComponents();
		canvas = new TsPhaseSpaceCanvas();
		// canvas.setInverse(true);

		Dimension sz = new Dimension(800, 600);
		contentPanel.setMaximumSize(sz);
		contentPanel.setMinimumSize(sz);
		contentPanel.setPreferredSize(sz);

		contentPanel.add(canvas, CC.xy(1, 1));

		swingTimer = new Timer(SWING_TIMER_MS, this);
		swingTimer.setRepeats(true);

		gradientComboBox.setSelectedIndex(3); // combo box contains an array of
												// integers!
		canvas.updateGradient(gradients[3]); // matches selection in line before

		speed_mult = 1.0;
		speed.setSelectedItem("1X");
		message.setText("");

		PInputEventListener centroidEventListener = new PInputEventListener() {

			@Override
			public void processEvent(PInputEvent event, int type) {
				PPath node = (PPath) event.getPickedNode();
				PNode rwave = null;
				if (node != null) {
					rwave = (PNode) node.getAttribute("source");
				}
				if (rwave != null) {
					Double Ix = (Double) rwave.getAttribute("moment_x");
					Double Iy = (Double) rwave.getAttribute("moment_y");
					Double Cx = (Double) rwave.getAttribute("centroid_x");
					Double Cy = (Double) rwave.getAttribute("centroid_y");

					long dt_ms = (long) (rwave.getX() * 1000);
					int mins = (int) (dt_ms / 60000);
					int secs = (int) ((dt_ms % 60000) / 1000);
					int millis = (int) (dt_ms % 1000);
					String tm_str = String.format("%d:%02d.%03d", mins, secs, millis);

					message.setText("Beat tm: " + tm_str + " (" + df0.format(Cx) + "," + df0.format(Cy) + ") Ix="
							+ df0.format(Ix) + " Iy=" + df0.format(Iy));
				}
			}
		};

		canvas.setCentroidEventListener(centroidEventListener);
	}

	/*
	 * a real doosey of a function to help R with longs!
	 */
	public void setDataArray(TsBaseCanvas canv, double[] tm, double[] xx, double[] yy) {
		setDataArray(canv.getStartTime(), tm, xx, yy);
	}

	public void setDataArray(long tm0, double[] tm, double[] xx, double[] yy) {
		canvas.setDataArray(tm0, tm, xx, yy);
	}

	public void setPhasespaceSize(double x0, double x1, double y0, double y1) {
		canvas.setPhasespaceSize(x0, x1, y0, y1);
	}

	public void setDataPackets(long tm0, double[][] tm, double[][] xx, double[][] yy) {
		canvas.setDataPackets(tm0, tm, xx, yy);
	}

	public void setDisplaySignal(RpMetric sigInfo) {
		canvas.setDisplaySignal(sigInfo);
	}

	public void setCentroidSignal(OfflineSignal sigInfo) {
		canvas.setCentroidSignal(sigInfo);
	}

	public void setSubject(String subject) {
		canvas.setSubject(subject);
	}

	private void speedItemStateChanged(ItemEvent e) {
		String selectedItem = (String) e.getItem();
		if (selectedItem != null) {
			selectedItem = selectedItem.replace("X", "");
			speed_mult = Double.parseDouble(selectedItem);
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		long additional_ms = System.currentTimeMillis() - tm0;
		tm0 = System.currentTimeMillis();

		if (additional_ms > 1000) {
			return; // ignore unrealistic delay
		}

		int dt = (int) 1000 / recorder_fps;
		if (dt < 1) {
			dt = 1;
		}

		display_dt += speed_mult * additional_ms;
		while (display_dt >= dt) {
			display_dt -= dt;
			tm_ms += dt;

			if (canvas.update(tm_ms) == false) {
				swingTimer.stop();

				record.setSelected(false);
				recordActionPerformed(null);
				message.setText("[Complete]");
			} else {
				if (record.isSelected()) {
					BufferedImage image = createScreenshot();
					try {
						if (enc == null) {
							initRecorder(outputFile, image.getWidth(), image.getHeight(), recorder_fps);
							enc.start();

							snapshot_time_sod = 0;
						}

						Frame frame = paintConverter.convert(image);
						if (frame != null) {
							// SEE:
							// https://github.com/bytedeco/javacv/issues/181
							enc.record(frame, avutil.AV_PIX_FMT_ARGB);
						}

						Date ddt = canvas.getCurrentDate();
						Calendar cal = Calendar.getInstance();
						cal.setTime(ddt);
						int hr = cal.get(Calendar.HOUR_OF_DAY);
						int min = cal.get(Calendar.MINUTE);
						int sec = cal.get(Calendar.SECOND);

						current_time_sod = hr * 3600 + min * 60 + sec;
						if (current_time_sod >= snapshot_time_sod) {
							// set trigger time for next snapshot
							while (snapshot_time_sod <= current_time_sod) {
								snapshot_time_sod += snapshot_interval;
							}
							// save snapshot
							String snapshotName = outputFile.getName();
							int pos = snapshotName.lastIndexOf(".");
							if (pos > 0) {
								snapshotName = snapshotName.substring(0, pos);
							}
							// snapshotName += "-";
							// snapshotName += canvas.getSigName();
							snapshotName += "-";
							snapshotName += snapshot_dateformat.format(ddt) + ".png";
							File file = new File(outputFile.getParentFile(), snapshotName);
							try {
								ImageIO.write(image, "png", file);
							} catch (IOException e1) {
								throw new RuntimeException(e1); // let the
																// global error
																// handler
																// catch it
							}
						}

					} catch (Exception e1) {
						// TODO Auto-generated catch block
						record.setSelected(false);
						message.setText(e1.getMessage());
						e1.printStackTrace();
					}
				}
			}
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

	private void gradientComboBoxItemStateChanged(ItemEvent e) {
		// must be from the combo box
		Integer ix = (Integer) e.getItem();
		if (e.getStateChange() == ItemEvent.SELECTED) {
			canvas.updateGradient(gradients[ix]);
		}
	}

	private void pauseActionPerformed(ActionEvent e) {
		swingTimer.stop();
	}

	private void recordActionPerformed(ActionEvent e) {
		if (!record.isSelected()) {
			if (enc != null) {
				FFmpegFrameRecorder safe_enc = enc;
				enc = null; // tell other threads not to write more images
				try {
					safe_enc.stop();
					safe_enc.release();
					// JAVACV enc.stop();
					// JAVAAV enc.close();
					// JCODEC enc.finish();
				} catch (Exception e1) {
					// ignore
					System.out.println("could not release?");
				}
			}
			message.setText("Recording stopped");
			return;
		}

		String root = canvas.getSubject();
		String suffix = "";
		int idx = 0;
		do {
			outputFile = new File("/tmp/" + root + "-" + canvas.getSigName() + suffix + ".mp4");
			suffix = "" + (--idx);
		} while (outputFile.exists());

		message.setText(outputFile.getPath());

		if (paintConverter == null) {
			iplConverter = new ToIplImage();
			paintConverter = new Java2DFrameConverter();
		}

	}

	private void resumeActionPerformed(ActionEvent e) {

		display_dt = 0;
		swingTimer.start();

	}

	private void rewindActionPerformed(ActionEvent e) {
		swingTimer.stop();
		tm_ms = 0;
		canvas.clear();
		if (enc != null) {
			record.setSelected(false);
			recordActionPerformed(null);
		}
	}

	private void copyImageActionPerformed(ActionEvent e) {
		BufferedImage out = createScreenshot();
		ImageSelection.copyImageToClipboard(out);
	}

	private void saveImageActionPerformed(ActionEvent e) {
		BufferedImage out = createScreenshot();

		JFileChooser fc = new JFileChooser();
		FileFilter[] filters = fc.getChoosableFileFilters();
		for (FileFilter ff : filters) {
			fc.removeChoosableFileFilter(ff);
		}
		fc.addChoosableFileFilter(new OpenFileFilter("png", "PNG Image"));

		int returnVal = fc.showSaveDialog(AppFrame.getInstance());

		if (returnVal == JFileChooser.APPROVE_OPTION) {
			File file = fc.getSelectedFile(); // new File(f);
			try {
				ImageIO.write(out, "png", file);
			} catch (IOException e1) {
				throw new RuntimeException(e1); // let the global error handler
												// catch it
			}
		}
	}

	private void copyDataActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		contentPanel = new JPanel();
		panel1 = new JPanel();
		gradientComboBox = createGradientCombo();
		message = new JLabel();
		record = new JToggleButton();
		rewind = new JButton();
		pause = new JButton();
		speed = new JComboBox<>();
		resume = new JButton();
		optionsPopupMenu = new JPopupMenu();
		copyImage = new JMenuItem();
		saveImage = new JMenuItem();
		copyData = new JMenuItem();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[350dlu,default]:grow",
			"fill:[200dlu,default]:grow, $lgap, default:grow, $lgap, default"));

		//======== contentPanel ========
		{
			contentPanel.setLayout(new FormLayout(
				"pref:grow",
				"fill:pref:grow"));
		}
		add(contentPanel, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[150dlu,default], $lcgap, default:grow, 5*($lcgap, default)",
				"default"));

			//---- gradientComboBox ----
			gradientComboBox.addItemListener(e -> gradientComboBoxItemStateChanged(e));
			panel1.add(gradientComboBox, CC.xy(1, 1));

			//---- message ----
			message.setText("text");
			panel1.add(message, CC.xy(3, 1));

			//---- record ----
			record.setText("Record");
			record.setToolTipText("Record");
			record.addActionListener(e -> recordActionPerformed(e));
			panel1.add(record, CC.xy(5, 1));

			//---- rewind ----
			rewind.setIcon(new ImageIcon(getClass().getResource("/idea/image/rewind-hot-icon.png")));
			rewind.setToolTipText("Rewind");
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

		//======== optionsPopupMenu ========
		{

			//---- copyImage ----
			copyImage.setText("Save Screenshot to Clipboard");
			copyImage.addActionListener(e -> copyImageActionPerformed(e));
			optionsPopupMenu.add(copyImage);

			//---- saveImage ----
			saveImage.setText("Save Screenshot to File");
			saveImage.addActionListener(e -> saveImageActionPerformed(e));
			optionsPopupMenu.add(saveImage);

			//---- copyData ----
			copyData.setText("Copy Data to Clipboard");
			copyData.setEnabled(false);
			copyData.addActionListener(e -> copyDataActionPerformed(e));
			optionsPopupMenu.add(copyData);
			optionsPopupMenu.addSeparator();
		}
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel contentPanel;
	private JPanel panel1;
	private JComboBox gradientComboBox;
	private JLabel message;
	private JToggleButton record;
	private JButton rewind;
	private JButton pause;
	private JComboBox<String> speed;
	private JButton resume;
	private JPopupMenu optionsPopupMenu;
	private JMenuItem copyImage;
	private JMenuItem saveImage;
	private JMenuItem copyData;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	void initRecorder(File file, int imageWidth, int imageHeight, int frameRate) {

		try {
			log.info(String.format("initRecorder {}", file));

			if (imageHeight % 2 == 1) {
				imageHeight--;
			}
			enc = new FFmpegFrameRecorder(file, imageWidth, imageHeight);

			// enc.setFormat("mp4");

			// recorder.setSampleRate(sampleAudioRateInHz);
			enc.setImageWidth(imageWidth);
			enc.setImageHeight(imageHeight);

			// re-set in the surface changed method as well
			enc.setVideoCodec(avcodec.AV_CODEC_ID_H264);
			enc.setFrameRate(frameRate);
			enc.setVideoBitrate(200000);
			// enc.setVideoQuality(0.8);

			// Create audio recording thread
			// audioRecordRunnable = new AudioRecordRunnable();
			// audioThread = new Thread(audioRecordRunnable);

		} catch (Exception e) {
			log.error("init ffmpeg", e);
		}
	}

	@Override
	public boolean finish() {
		return true; // finish pass-through...let the canvas be displayed!
	}

	@Override
	public boolean next() {
		return false;
	}

	@Override
	public void previous() {
		rewindActionPerformed(null); // stop the recording
	}

	@Override
	public void refresh() {
		// ignore
	}

	public JPopupMenu getPopupMenu() {
		return optionsPopupMenu;
	}

}
