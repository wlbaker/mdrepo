package idea.tween;

import java.awt.Point;

import javax.swing.JComponent;

import aurelienribon.tweenengine.TweenAccessor;

public class JComponentAccessor implements TweenAccessor<JComponent> {
	// The following lines define the different possible tween types.
	// It's up to you to define what you need :-)
	public static final int POSITION_X = 1;
	public static final int POSITION_Y = 2;
	public static final int POSITION_XY = 3; // TweenAccessor implementation

	@Override
	public int getValues(JComponent target, int tweenType, float[] returnValues) {
		switch (tweenType) {
		case POSITION_X:
			returnValues[0] = target.getX();
			return 1;
		case POSITION_Y:
			returnValues[0] = target.getY();
			return 1;
		case POSITION_XY:
			returnValues[0] = target.getX();
			returnValues[1] = target.getY();
			return 2;
		default:
			assert false;
			return -1;
		}
	}

	@Override
	public void setValues(JComponent target, int tweenType, float[] newValues) {

		switch (tweenType) {
		case POSITION_X: {
			Point pt = target.getLocation(null);
			pt.setLocation(newValues[0], pt.getY());
			target.setLocation(pt);
		}
			break;
		case POSITION_Y: {
			Point pt = target.getLocation(null);
			pt.setLocation( pt.getX(), newValues[0]);
			target.setLocation(pt);
		}
			break;
		case POSITION_XY:
			target.setLocation((int) newValues[0], (int) newValues[1]);
			break;
		default:
			assert false;
			break;
		}
	}
}
