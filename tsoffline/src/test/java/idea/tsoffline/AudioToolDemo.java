/*
 * Common microphone sample rates:
 * 
 * float sampleRate = 11025.0F;   //8000,11025,16000,22050,44100
 *
 */
package idea.tsoffline;

import java.io.ByteArrayInputStream;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.Control;
import javax.sound.sampled.Line;
import javax.sound.sampled.Line.Info;
import javax.sound.sampled.LineEvent;
import javax.sound.sampled.LineListener;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.Mixer;
import javax.sound.sampled.Port;

class AudioToolDemo implements LineListener {

	// od --address-radix=d -t x1 -w1 BAMC\ 2719.002.aud | grep '.*80$'

	private static byte getByteValue(double angle) {
		int maxVol = 127;
		return (new Integer((int) Math.round(Math.sin(angle) * maxVol))).byteValue();
	}

	private static Clip playTone(boolean addHarmonic, int intSR, int intFPW) throws LineUnavailableException {
		Clip clip = AudioSystem.getClip();

		float sampleRate = (float) intSR;

		// oddly, the sound does not loop well for less than
		// around 5 or so, wavelengths
		int wavelengths = 20;
		byte[] buf = new byte[2 * intFPW * wavelengths];
		AudioFormat af = new AudioFormat(sampleRate, 8, // sample size in bits
				2, // channels
				true, // signed
				false // bigendian
		);

		int maxVol = 127;
		for (int i = 0; i < intFPW * wavelengths; i++) {
			double angle = ((float) (i * 2) / ((float) intFPW)) * (Math.PI);
			buf[i * 2] = getByteValue(angle);
			if (addHarmonic) {
				buf[(i * 2) + 1] = getByteValue(2 * angle);
			} else {
				buf[(i * 2) + 1] = buf[i * 2];
			}
		}

		try {
			byte[] b = buf;
			AudioInputStream ais = new AudioInputStream(new ByteArrayInputStream(b), af, buf.length / 2);

			clip.open(ais);
		} catch (Exception e) {
			e.printStackTrace();
		}

		clip.setFramePosition(0);
		clip.loop(Clip.LOOP_CONTINUOUSLY);
		return clip;
	}

	@Override
	public void update(LineEvent event) {
		System.out.println("event: " + event.getFramePosition() + " --> " + event);
	
	}

	private void playSample(String fileName) throws Exception {
		// ToneUtil.playTone(2000, 4000, 10);

		// AudioTool.playTone(false, 4000, 10);
		// Thread.sleep(1000);

		// open the sound file as a Java input stream
		// String gongFile = "/Users/al/DevDaily/Projects/MeditationApp/resources/gong.au";
		InputStream in = new FileInputStream(fileName);
		byte[] header = new byte[71];
		in.read(header, 0, 71);

		AudioFormat f = new AudioFormat(11025, 16, 1, true, true);
		// create an audiostream from the inputstream
		AudioInputStream ais = new AudioInputStream(in, f, 11026 * 300);

		// play the audio clip with the audioplayer class
		// AudioPlayer.player.start(audioStream);

		Clip clip = AudioSystem.getClip();
		clip.open(ais);
		clip.addLineListener( this );
		clip.setFramePosition(0);
		clip.loop(1);

		Thread.sleep(300 * 1000);

	}

	private static void dump(byte[] header) {
		ByteBuffer bb = ByteBuffer.wrap(header);
		while (bb.hasRemaining()) {
			char ch = (char) bb.get();
			if (ch < 0) {
				ch += 256;
			}
			if (ch < 32) {
				System.out.print("[" + Integer.toHexString(ch) + "]");
			} else {
				System.out.print(ch);
			}
		}
		System.out.println();

	}

	private static void enum_lines() throws Exception {
		Port port = null;
		// line.
		// Line.Info refline = new Line.Info(lineClass)
		Info[] lineinfos = AudioSystem.getSourceLineInfo(Port.Info.MICROPHONE);
		for (Info info : lineinfos) {
			System.out.println(info);
		}

		if (AudioSystem.isLineSupported(Port.Info.MICROPHONE)) {
			port = (Port) AudioSystem.getLine(Port.Info.MICROPHONE);
			
			Line.Info info = port.getLineInfo();
			System.out.println("info=" + info );
			System.out.println();
			
			Control[] controls = port.getControls();
			System.out.println("controls=" + controls );
			if( controls != null ) {
				System.out.println("port controls.length=" + controls.length);
			}
			
			Line line = AudioSystem.getLine( info );
			Control[] mic_controls = line.getControls();
			System.out.println("line controls.length=" + mic_controls.length);
			for(Control control : mic_controls ) {
				System.out.println("control: " + control );
			}
		}

		Mixer.Info[] mixinfos = AudioSystem.getMixerInfo();
		for(Mixer.Info mixer : mixinfos ) {
			System.out.println("mixer: " + mixer );
		}
		System.out.println();

	}

	public static void main(String[] args) throws Exception {

		System.out.println("audio util");
		enum_lines();

		AudioToolDemo tool = new AudioToolDemo();
		String fileName = "c:/opt/study/rubal/BAMC 2719.002.aud";
		tool.playSample(fileName);

		System.exit(0);

		// od --address-radix=d -t d1 -w4 BAMC\ 2719.002.aud -v > four.txt
		// df1 <- read.table( "/opt/study/rubal/four.txt", colClasses=rep("numeric",5) )

		FileInputStream r = null;
		byte[] buf = new byte[2048];
		try {
			r = new FileInputStream(fileName);
			byte[] header = new byte[70];
			int sz = r.read(header);
			dump(header);

			do {
				sz = r.read(buf);
				if (sz <= 0)
					break;

				ByteBuffer bb = ByteBuffer.wrap(buf);
				bb.order(ByteOrder.LITTLE_ENDIAN);

				while (bb.position() < sz) {
					short data = bb.getShort();
					System.out.printf("" + data + "\n");
				}
			} while (true);
		} catch (EOFException ignore) {
		} catch (Exception ioe) {
			ioe.printStackTrace();
		} finally {
			if (r != null) {
				try {
					r.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		}
	}

}