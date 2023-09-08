package idea.tween;

import javax.swing.JComponent;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenManager;

public class TheManager {

	private static TweenManager tmanager;

	public static TweenManager getTweenManager() {
		
		if( tmanager == null ) {
			Tween.registerAccessor( JComponent.class, new JComponentAccessor() );
			tmanager = new TweenManager();
		}
		
		return tmanager;
	}

}
