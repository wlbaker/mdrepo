package idea.meddaq;

import java.awt.AWTException;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.concurrent.TimeUnit;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.TargetDataLine;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import org.bytedeco.javacv.FFmpegFrameRecorder;

import idea.GuiUtil;

import com.xuggle.mediatool.IMediaWriter;
import com.xuggle.mediatool.ToolFactory;
import com.xuggle.xuggler.ICodec;
import com.xuggle.xuggler.IRational;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CaptureXugglerUtil {


	// ERROR: frame rate not set
	private static IRational FRAME_RATE = IRational.make(10, 1);

	private static IMediaWriter writer;
	private static Thread vidiocapture_thread;
	private static boolean vidiocap_running;

	private static JPanel panel;
	private static File videoOutputFile;

	private static Thread audiocapture_thread;
	private static boolean audiocap_running;

	protected static IMediaWriter audio_out;

	private static File audioFileOut;

	private static AudioFormat audioFormatOut;

	private static TargetDataLine line;

	public static void beginMovieCapture(File outFile, JPanel mp) throws AWTException {
		// create a swing timer
		if (vidiocap_running) {
			GuiUtil.showMessage("Capture already running!");
			return;
		}

		panel = mp;
		videoOutputFile = outFile;
		// Now, we're going to loop

		Runnable r = new Runnable() {

			@Override
			public void run() {
				try {
					runVideoCaptureLoop();
				} catch (AWTException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		};

		vidiocapture_thread = new Thread(r);
		vidiocapture_thread.start();
	}

	protected static void runVideoCaptureLoop() throws AWTException {
		Robot robot = new Robot();
		Rectangle screenBounds;
		final Toolkit toolkit = Toolkit.getDefaultToolkit();

		if (panel == null) {

			screenBounds = new Rectangle(toolkit.getScreenSize());
		} else {
			Dimension sz = panel.getSize();
			Point zero = new Point(0, 0);

			SwingUtilities.convertPointToScreen(zero, panel);

			zero.x = round(zero.x, 4);
			zero.y = round(zero.y, 4);
			Point r = new Point((int) sz.getWidth(), (int) sz.getHeight());
			r.x = round(r.x, 4);
			r.y = round(r.y, 4);

			screenBounds = new Rectangle(zero.x, zero.y, r.x, r.y);
			panel = null;
		}

		// First, let's make a IMediaWriter to write the file.
		writer = ToolFactory.makeWriter(videoOutputFile.getPath());

		// We tell it we're going to add one video stream, with id 0,
		// at position 0, and that it will have a fixed frame rate of
		// FRAME_RATE.
		// ICodec.ID.CODEC_ID_AVS?
		writer.addVideoStream(0, 0, FRAME_RATE, screenBounds.width, screenBounds.height);
		// writer.addAudioStream(arg0, arg1, arg2, arg3)

		long startTime = System.nanoTime();
		vidiocap_running = true;
		for (int index = 0; vidiocap_running; index++) {
			// take the screen shot
			BufferedImage screen;
			if (panel == null) {
				screen = robot.createScreenCapture(screenBounds);
			} else {
				int w = panel.getWidth();
				int h = panel.getHeight();
				screen = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
				Graphics2D g = screen.createGraphics();
				panel.paint(g);
			}

			// convert to the right image type
			BufferedImage bgrScreen = convertToType(screen, BufferedImage.TYPE_3BYTE_BGR);

			// encode the image to stream #0
			writer.encodeVideo(0, bgrScreen, System.nanoTime() - startTime, TimeUnit.NANOSECONDS);

			if (index % 30 == 0) {
				writer.flush();
			}

			// sleep for framerate milliseconds
			try {
				Thread.sleep((long) (1000 / FRAME_RATE.getDouble()));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		// Finally we tell the writer to close and write the trailer if
		// needed
		writer.close();

	}

	private static int round(int v, int mult) {
		v = mult * ((v + mult - 1) / mult);
		return v;
	}

	public static void endMovieCapture() {
		vidiocap_running = false;
		interrupt_and_join(vidiocapture_thread);
		vidiocapture_thread = null;
	}

	private static void interrupt_and_join(Thread thread) {
		if (thread != null) {
			thread.interrupt();
			try {
				thread.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	/**
	 * Convert a {@link BufferedImage} of any type, to {@link BufferedImage} of
	 * a specified type. If the source image is the same type as the target
	 * type, then original image is returned, otherwise new image of the correct
	 * type is created and the content of the source image is copied into the
	 * new image.
	 * 
	 * @param sourceImage
	 *            the image to be converted
	 * @param targetType
	 *            the desired BufferedImage type
	 * 
	 * @return a BufferedImage of the specifed target type.
	 * 
	 * @see BufferedImage
	 */

	public static BufferedImage convertToType(BufferedImage sourceImage, int targetType) {
		BufferedImage image;

		// if the source image is already the target type, return the source
		// image

		if (sourceImage.getType() == targetType)
			image = sourceImage;

		// otherwise create a new image of the target type and draw the new
		// image

		else {
			image = new BufferedImage(sourceImage.getWidth(), sourceImage.getHeight(), targetType);
			Graphics g = image.getGraphics();
			g.drawImage(sourceImage, 0, 0, null);
			g.dispose();
		}

		return image;
	}

	public static void captureScreenShot(File file, Component panel) throws AWTException, IOException {
		BufferedImage screenShot;

		Rectangle r = new Rectangle(Toolkit.getDefaultToolkit().getScreenSize());
		if (panel == null) {
			Robot robot = new Robot();
			screenShot = robot.createScreenCapture(r);
		} else {
			int w = panel.getWidth();
			int h = panel.getHeight();
			screenShot = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
			Graphics2D g = screenShot.createGraphics();
			panel.paint(g);
		}
		ImageIO.write(screenShot, "JPG", file);

	}

	private static AudioFormat getDefaultAudioFormat() {
		float sampleRate = 8000;
		int sampleSizeInBits = 8;
		int channels = 1;
		boolean signed = true;
		boolean bigEndian = true;
		return new AudioFormat(sampleRate, sampleSizeInBits, channels, signed, bigEndian);
	}

	public static void beginAudioCapture(File audioFile) {
		AudioFormat audioFormat = getDefaultAudioFormat();
		beginAudioCapture(audioFile, audioFormat);
	}

	public static void beginAudioCapture(final File audioFile, final AudioFormat format) {
		audioFormatOut = format;
		audioFileOut = audioFile;
		try {
			DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
			line = (TargetDataLine) AudioSystem.getLine(info);
			line.open(format);
			line.start();
			Runnable runner = new Runnable() {

				public void run() {
					audiocap_running = true;
					try {
						runAudioCaptureLoop();
					} finally {
						audiocap_running = false;
					}
				}
			};
			audiocapture_thread = new Thread(runner);
			audiocapture_thread.start();
		} catch (LineUnavailableException e) {
			System.err.println("Line unavailable: " + e);
			System.exit(-2);
		}
	}

	protected static void runAudioCaptureLoop() {
		int bufferSize = (int) audioFormatOut.getSampleRate() * audioFormatOut.getFrameSize();
		byte buffer[] = new byte[bufferSize];
		short sbuffer[] = new short[bufferSize];
		audio_out = ToolFactory.makeWriter(audioFileOut.getPath());
		int sampleRate = (int) audioFormatOut.getSampleRate();
		int channels = 1;
		audio_out.addAudioStream(0, 0, ICodec.ID.CODEC_ID_MP3, channels, sampleRate);

		// audio_out = new ByteArrayOutputStream();
		while (audiocap_running) {
			System.out.println("pkg: " + buffer.length);
			int count = line.read(buffer, 0, buffer.length);
			if (count > 0) {
				for( int i = 0; i < bufferSize; i++ ) {
					sbuffer[i] = (short) (128*buffer[i]);
				}
				// audio_out.write(buffer, 0, count);
				audio_out.encodeAudio(0, sbuffer);
			}
		}
		audio_out.close();
		log.info("audio capture is done.");

	}

	public static void endAudioCapture() {
		audiocap_running = false;
		interrupt_and_join(audiocapture_thread);
		audiocapture_thread = null;
	}

}
