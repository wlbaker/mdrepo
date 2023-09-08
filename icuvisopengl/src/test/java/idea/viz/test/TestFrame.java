package idea.viz.test;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.jogamp.opengl.GLProfile;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import idea.conf.DeviceConfiguration;
import idea.display.BandLayout;
import idea.display.WaveformData;
import idea.driver.SimuSineStreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.schema.rp.RpStream;
import idea.display.gl.GLInstrumentDisplay;

public class TestFrame {

	static GLInstrumentDisplay d;
	private static DeviceConfiguration caps;
	private static SimuSineStreamProducer sig;

	static {
		GLProfile.initSingleton();
		GLProfile pp = GLProfile.getGL2ES2();
	}

	private static GLInstrumentDisplay buildDisplay() {

		RpStream stream = caps.getStream(StreamID.WAVEFORM);

		DisplayConfig dc = new DisplayConfig();
		{
			WaveformData wf = new WaveformData();
			// wf.setLoc("ai0");
			wf.setLoc("wf0");
			wf.setWaveSampleRate((short) 50);
			wf.setRangeMin((short) -100);
			wf.setRangeMax((short) 100);
			wf.setWaveColor( (byte)1 );

			BandLayout band = new BandLayout((byte) 0, (byte) 0);
			band.addWaveform(wf);
			dc.addBand(band);
		}
		{
			WaveformData wf = new WaveformData();
			// wf.setLoc("ai0");
			wf.setLoc("wf1");
			wf.setWaveSampleRate((short) 50);
			wf.setRangeMin((short) -5);
			wf.setRangeMax((short) 25);
			wf.setWaveColor( (byte)2 );

			BandLayout band = new BandLayout((byte) 0, (byte) 0);
			band.addWaveform(wf);
			dc.addBand(band);
		}

		// dc.addParamBox( new PBoxSetupData( ));
		d = new GLInstrumentDisplay();
		d.setDisplay(dc, true, false);

		return d;
	}

	private static Component buildButtonBar() {
		JPanel p = new JPanel();

		final JLabel stat = new JLabel("status");
		JButton adv = new JButton("Adv");
		JButton retr = new JButton("Retr");
		JButton curr = new JButton("Curr");
		JButton data = new JButton("Data");
		JButton realt = new JButton("Toggle Realtime");

		adv.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int tm = d.getTTime();
				d.setTime(tm - 1000);
				stat.setText("tm=" + d.getTTime());
			}
		});

		retr.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int tm = d.getTTime();
				d.setTime(tm + 1000);
				stat.setText("tm=" + d.getTTime());
			}
		});

		curr.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int tm = (int) (System.currentTimeMillis() - d.getTime0());
				d.setTime(tm);
				stat.setText("tm=" + d.getTTime());
			}
		});

		realt.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				d.setRealtime( !d.isRealtime() );
				stat.setText("realtime=" + d.isRealtime() );
			}
		});

		data.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int tm = (int) (System.currentTimeMillis() - d.getTime0());
				// float [] arr = new float[100];
				float [] arr = null;  // special diagnostic case
				d.getDisplayData("wf0", arr);
//				System.out.println();
//				System.out.println( d.getTime0() );
//				for( float f : arr ) { 
//					System.out.print(" " + f);
//				}
//				System.out.println();
			}
		});
		p.setLayout(new FlowLayout());
		p.add(stat);
		p.add(adv);
		p.add(retr);
		p.add(curr);
		p.add(data);
		p.add(realt);

		return p;
	}

	private static Thread createSignalProducer() {
		DeviceConfiguration conf = SimuSineStreamProducer.createConfigInstance();
		sig = new SimuSineStreamProducer(conf);

		caps = sig.getStaticCapabilities();

		Thread t = new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					while (true) {
						Thread.sleep(500);
						sig.tick();
						System.out.print("t");
					}
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});

		return t;
	}

	public static void main(String[] argv) {

		Thread t = createSignalProducer();

		JFrame f = new JFrame("GLTest");

		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel p = new JPanel();
		p.setLayout(new BorderLayout());
		p.setPreferredSize(new Dimension(600, 300));
		p.add(buildDisplay());

		f.add(p, BorderLayout.CENTER);
		f.add(buildButtonBar(), BorderLayout.SOUTH);

		f.pack();

		sig.addStreamListener(StreamID.WAVEFORM, d);
		t.start();

		f.setVisible(true);
	}

}
