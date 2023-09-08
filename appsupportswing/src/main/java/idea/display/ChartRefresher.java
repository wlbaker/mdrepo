package idea.display;

import java.util.Calendar;
import java.util.LinkedList;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ChartRefresher implements Runnable {

	private static boolean globalPause = false;

	private int sr = -1;
	private long timeDeltaInMillis;

	private volatile LinkedList<CardioStrip> strips;
	private boolean refreshing;

	private Thread t;

	private Thread tid;

	private boolean is_running;

	private static ChartRefresher refresher;

	public static ChartRefresher getInstance() {
		if (refresher == null) {
			refresher = new ChartRefresher(25);
		}

		return refresher;
	}

	private ChartRefresher(int hz) {
		// this.sr = 1000 / hz;
		this.strips = new LinkedList<CardioStrip>();
		this.sr = 20;
	}

	public void setTimeDeltaInMillis_DELETE_ME_OBSOLETE(long ms) {
		this.timeDeltaInMillis = ms;

		for (CardioStrip chart : strips) {
			// chart.setEndTimeInMillis(0); // this is a trigger of some
			// kind...not really what you want.
		}
	}

	public void addChart(CardioStrip strip) {
		synchronized (strips) {
			strips.add(strip);

			if (t == null) {
				t = new Thread(this);
				t.start();
			}
		}

	}

	@Override
	public void run() {
		if( is_running == true ) {
			log.error("refresher already running!");
			return;
		}
		is_running = true;
		try {
			_run();
		} catch (Exception e) {
			log.error("Refresher Error", e);
		} finally {
			is_running = false;
		}
		log.error("********************REFRESHER FINISHED");
	}

	public void _run() {
		refreshing = true;
		while (refreshing) {
			if (globalPause) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					log.error("shutdown request?");
					break;
				}
				continue;
			}
			Calendar cal = Calendar.getInstance();
			long msNow = cal.getTimeInMillis() - timeDeltaInMillis;


			synchronized (strips) {
				for (CardioStrip strip : strips) {
					strip.refresh(msNow);
				}
			}

			try {
				Thread.sleep(sr);
			} catch (InterruptedException e) {
				log.error("Refresher -- interrupted");
				break;  // breaks the while loop
			}
		}

	}

	public void stop() {
		refreshing = false;
	}

	public static void setGlobalPause(boolean pause) {
		globalPause = pause;
	}

	public void reset() {

		// help the garbage collector a little
		refreshing = false;

		if (t != null) {
			t.interrupt();
		}

		synchronized (strips) {
			while (strips.size() > 0) {
				strips.remove();
			}
		}
	}

	public void start() {
		if (tid == null) {
			tid = new Thread(this);
			tid.start();
		}
	}

}
