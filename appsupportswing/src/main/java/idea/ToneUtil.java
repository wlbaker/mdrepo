package idea;

import java.io.ByteArrayInputStream;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;

public class ToneUtil {

	public static void playTone(final int duration, final int intSR, final int intFPW) {
		
		Runnable r = new Runnable() {
			Clip clip;
			
			@Override
			public void run() {
				try {
					_run( 1 );
					_run( 2 );
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} finally {
					clip.stop();
				}
			}
			
			public void _run(int mult) throws LineUnavailableException, InterruptedException {
				clip = generateTone(true, mult * intSR, intFPW);
				clip.setFramePosition(0);
				clip.loop(Clip.LOOP_CONTINUOUSLY);
				
				Thread.sleep( duration );
				clip.stop();
			}
		};
		
		Thread t = new Thread(r);
		t.start();
		
	}

	private static Clip generateTone(boolean addHarmonic, int intSR, int intFPW) throws LineUnavailableException {
		//		if (clip != null) {
		//			clip.stop();
		//			clip.close();
		//		} else {
		Clip clip = AudioSystem.getClip();
		//		}

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

		return clip;
	}

	private static byte getByteValue(double angle) {
		int maxVol = 127;
		return (new Integer((int) Math.round(Math.sin(angle) * maxVol))).byteValue();
	}


}
