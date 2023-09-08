package idea.r;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;
import org.rosuda.javaGD.GDInterface;
import org.rosuda.javaGD.JGDBufferedPanel;
import org.rosuda.javaGD.JGDPanel;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class RCue extends GDInterface {

	public static JPanel parent;
	public static JGDBufferedPanel plotter;

	private JPanel _parent;
	JFrame f = null;

	// private Stack history = new Stack();

	public RCue() {
		this._parent = parent;
		this.c = plotter;
		
		log.info("M1 Created new RCue parent={}", _parent );
	}

	public JGDBufferedPanel getPlotter() {
		return (JGDBufferedPanel) c;
	}

	public RCue(JPanel parent) {
		_parent = parent;
		log.info("M2 Created new RCue parent={}", _parent );
	}

	@Override
	public void gdOpen(double w, double h) {
		
		// super.gdOpen( w , h);
		
		log.info("gdOpen {}, {}", w, h);
		plotter = new JGDBufferedPanel(w, h);
		c = plotter;

		try {
			plotter.putClientProperty("rcue", this);

			if (_parent == null || _parent.getLayout().getClass() != BorderLayout.class) {
				f = new JFrame("Default Plotter");
				 InternalPlotterPanel pp = new InternalPlotterPanel();
				 f.add( pp, BorderLayout.CENTER );
				 _parent = pp;
// 				_parent = (JPanel) f.getContentPane();
				log.info("CREATING a default plotter, assigning parent=hash/{}, cl={}", _parent.hashCode(), _parent.getClass() );
				
				// missing fundamental things here...such as gdClose() when frame closes...
				// FIXME: pull in better frame from tsoffline

			} else {
				log.info("NO NEED for a default plotter parent=hash/{}, cl={}" , _parent.hashCode(), _parent.getClass() );
				log.info("parent name=" + _parent.getName() );
				log.info("parent cue=" + _parent.getClientProperty("rcue"));
				dump();
				log.info("parent layout=" + _parent.getLayout() );
				
			}
			_parent.putClientProperty("rcue", this);
			_parent.add((Component) c, BorderLayout.CENTER);
			// _parent.add(devLabel = new JLabel("Dev: ?"), BorderLayout.SOUTH);

			if (f != null) {
				f.setSize(800, 600);
				f.pack();
				f.setVisible(true);
			}
			parent = null;
		} catch (Exception e) {
			log.error("error: " + _parent.getClass());
			log.error("parent layout: " + _parent.getLayout());
			log.error("RCue::got an error in gdOpen? ", e);
		}
		
		super.gdOpen(w, h);
//		log.info("newpage on gdopen");
//		super.gdNewPage();
	}

	@Override
	public void gdClose() {
		log.info("gdClose id={}", plotter.getDeviceNumber() );
		super.gdClose();
		c = null;
		
		if( f != null ) {
			f.setVisible(false);
			f.dispose();
			f = null;
		}
	}

	@Override
	public void executeDevOff() {
		super.executeDevOff();
		// System.out.println("RCue::executeDevOff");
		Container curr_parent = plotter.getParent();
		if (curr_parent != null) {
			curr_parent.remove(plotter);
		}
	}

	@Override
	public void gdActivate() {
		super.gdActivate();
		updateTitle();
		dump();
	}

	private void dump() {
		if( _parent == null ) {
			log.info( "DUMP: NO PARENT? this=", this );
			return;
		}
		log.info( "dump: hash/{}", _parent.hashCode() );
		for( int i = 0; i < _parent.getComponentCount() ; i++ ) {
			log.info("parent comp=" + _parent.getComponent(i));
		}
	}

	@Override
	public void gdFlush(boolean arg0) {
		super.gdFlush(arg0);
		log.info("RCue::gdFlush  arg0={}", arg0 );
	}

	@Override
	public void gdMode(int arg0) {
		super.gdMode(arg0);
		log.debug("gdMode {}", arg0);
	}

	@Override
	public void gdNewPage() {
		super.gdNewPage();
		log.info("gdNewPage");
		updateTitle();
	}

	@Override
	public void gdNewPage(int arg0) {
		super.gdNewPage(arg0);
		// Vector list = plotter.getGDOList();
		// history.push(list);
		log.info("gdNewPage {}", arg0);
		// plotter.set
		updateTitle();
	}

	private void updateTitle() {
		int num = plotter.getDeviceNumber();
		if (num > 0) {
			// devLabel.setText("Dev: " + num);
			log.info("plotter device number {}", num);
		}
		if( f != null ) {
			f.setTitle( "Default Printer: " + num );
		}
	}

	public void setFrame(JFrame f) {
		this.f = f;
	}

}
