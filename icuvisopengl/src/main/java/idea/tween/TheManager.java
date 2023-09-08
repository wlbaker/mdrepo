package idea.tween;

import javax.swing.JComponent;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenManager;
import idea.display.gl.GLDisplayShim;

public class TheManager implements GLDisplayShim {

	private static TweenManager tmanager;
	public static TweenManager getTweenManager() {
		
		if( tmanager == null ) {
			Tween.registerAccessor( JComponent.class, new JComponentAccessor() );
			tmanager = new TweenManager();
		}
		return tmanager;
	}

	private static long last_tm;
	
	private int ii = 0;
	@Override
	public void microTick() {
		ii++;
		if( ii % 100 == 0 ) {
			System.out.print("m");
		}
		if( ii > 10000 ) {
			System.out.println(": TheManager");
			ii = 0;
		}
		long tm = System.currentTimeMillis();
		long delta = (tm - last_tm);
		if( delta > 1000 ) {
			delta = 20;
			last_tm = tm - delta;
		}
		float dt = delta/(float)1000;
		
		tmanager.update(dt);
		last_tm = tm;
	}
}
