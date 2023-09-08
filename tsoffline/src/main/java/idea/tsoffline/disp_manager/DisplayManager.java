package idea.tsoffline.disp_manager;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.HierarchyBoundsListener;
import java.awt.event.HierarchyEvent;
import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.plaf.basic.BasicButtonUI;

import aurelienribon.tweenengine.BaseTween;
import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenCallback;
import aurelienribon.tweenengine.TweenManager;
import lombok.extern.slf4j.Slf4j;
import idea.gui.VerticalButtonUI;
import idea.tsoffline.TsSignalTreeSelectionPanel;
import idea.tsoffline.canvas.TsControlPanel;
import idea.tween.JComponentAccessor;
import idea.tween.TheManager;

/* 
 * LayeredPaneDemo.java requires
 * images/dukeWaveRed.gif. 
 */

// FIXME: look for the number "300" to find out why it slides to where it does...
@SuppressWarnings("serial")
@Slf4j
public class DisplayManager extends JLayeredPane implements TweenCallback {
	private static final int BANDSETUP_WIDTH = 340;
	private static final int PARAMSETUP_WIDTH = 640;

	private TsControlPanel form;
	private TsSignalTreeSelectionPanel dataPanel;

	private JButton showDataSetup;
	private JButton ptrendsSetup;
	private JButton hideDataSetup;
	private JButton hideLayoutSetup;
	private boolean open_be = false;
	private boolean open_pe = false;
	private ReplayControlPanel replayController;

	private static Timer timer;

	public DisplayManager(TsControlPanel gl_form, TsSignalTreeSelectionPanel dataPanel) {
		this.form = gl_form;
		this.dataPanel = dataPanel;
		replayController = new ReplayControlPanel(this.form);

		// Create and set up the layered pane.
		setPreferredSize(new Dimension(720, 480));

		// Add several overlapping, colored labels to the layered pane
		// using absolute positioning/sizing.
		VerticalButtonUI rotate90 = new VerticalButtonUI(90);

		//showDataSetup = createLabelButton("Data", new Point(0, 6), rotate90);
		//ptrendsSetup = createLabelButton("Trends", new Point(0, 97), rotate90);
		hideDataSetup = createLabelButton("Hide", new Point(BANDSETUP_WIDTH - 1, 0), rotate90);
		hideLayoutSetup = createLabelButton("Hide", new Point(20, form.getHeight() - 1), null);

		//ptrendsSetup.setEnabled(false);

		hideDataSetup.setVisible(false);
		hideLayoutSetup.setVisible(false);

		this.setMinimumSize(new Dimension(600, 400));
		this.setPreferredSize(new Dimension(700, 400));
		form.setBounds(0, 0, 700, 340);
		if( dataPanel != null ) {
			dataPanel.setBounds(0, 0, 200, 700);
			dataPanel.setBorder(BorderFactory.createLineBorder(Color.black));
		}

		JPanel primary = new JPanel();
		primary.setLayout(new BorderLayout());
		primary.add(replayController, BorderLayout.SOUTH);
		// primary.add(createBlankPanel(), BorderLayout.WEST );
		primary.add(form, BorderLayout.CENTER);
		primary.setName("primary");

		prepareForm(form);

		timer = new Timer(1000 / 60, loop);

		JLayeredPane layers = new JLayeredPane();
		layers.setName("layers");
		layers.setPreferredSize(new Dimension(300, 310));
		layers.addComponentListener(new ComponentAdapter() {

			@Override
			public void componentResized(ComponentEvent e) {
				Component comp = e.getComponent();
				SwingUtilities.invokeLater(new Runnable() {

					@Override
					public void run() {
						// layers.setSize( comp.getSize() );
						primary.setSize(comp.getSize());
						// form.setSize( comp.getSize() );

						primary.doLayout();
						replayController.doLayout();
						// form.doLayout();
						// layers.doLayout();
					}
				});
			}
		});

		Integer pos = 0;
		layers.add(primary, pos++);
		// buttons
		if( showDataSetup != null) layers.add(showDataSetup, pos++);
		if( ptrendsSetup != null) layers.add(ptrendsSetup, pos++);
		layers.add(hideDataSetup, pos++);
		layers.add(hideLayoutSetup, pos++);

		if( dataPanel != null ) {
			layers.add(dataPanel, pos++);
			dataPanel.setVisible(true);
		}

		this.setLayout(new BorderLayout());
		this.add(layers, BorderLayout.CENTER);
	}

	private long last_tm;

	private int ii = 0;

	private final ActionListener loop = new ActionListener() {

		@Override
		public void actionPerformed(ActionEvent e) {
			microTick();
			repaint();
		}

	};

	public void microTick() {
		ii++;
		if (ii % 100 == 0) {
			System.out.print("m");
		}
		if (ii > 10000) {
			System.out.println(": TheManager");
			ii = 0;
		}
		long tm = System.currentTimeMillis();
		long delta = (tm - last_tm);
		if (delta > 1000) {
			delta = 20;
			last_tm = tm - delta;
		}
		float dt = delta / (float) 1000;

		TheManager.getTweenManager().update(dt);
		last_tm = tm;
	}

	private void prepareForm(JComponent form) {

		form.addHierarchyBoundsListener(new HierarchyBoundsListener() {

			@Override
			public void ancestorMoved(HierarchyEvent e) {
				// TODO Auto-generated method stub

			}

			@Override
			public void ancestorResized(HierarchyEvent e) {
				Dimension parent_sz = e.getComponent().getSize();
				
				if( dataPanel != null ) {
					Point me_pos = dataPanel.getLocation();
					Dimension me_dim = dataPanel.getSize();

					if (me_pos.x == parent_sz.width && me_dim.height == parent_sz.height) {
						// ignore request to set existing size...creates excess
						// 	redraws
						return;
					}

					// this routine called way too often
					dataPanel.setBounds(-BANDSETUP_WIDTH, 0, BANDSETUP_WIDTH, parent_sz.height);
				}

				// paramEditor.clear();

				open_be = false;
				open_pe = false;

				if( showDataSetup != null) showDataSetup.setVisible(true);
				if( ptrendsSetup != null) ptrendsSetup.setVisible(true);
				hideDataSetup.setVisible(false);
				hideLayoutSetup.setVisible(false);
			}
		});

		// after adding the controls, tell the parent to check out the sizes
		// again
		doLayout();
	}

	// Create and set up a colored label.
	private JButton createLabelButton(String text, Point origin, BasicButtonUI ui) {
		JButton label = new JButton(text);
		label.setVerticalAlignment(JLabel.TOP);
		label.setHorizontalAlignment(JLabel.CENTER);
		label.setOpaque(true);
		// label.setForeground(Color.black);
		label.setBorder(BorderFactory.createLineBorder(Color.black));
		if (ui == null) {
			label.setBounds(origin.x, origin.y, 90, 20);
		} else {
			label.setBounds(origin.x, origin.y, 20, 90);
			label.setUI(ui);
		}
		label.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JButton btn = (JButton) e.getSource();
				String txt = btn.getText();

				if (btn == showDataSetup) {
					if( showDataSetup != null ) showDataSetup.setVisible(false);
					if( ptrendsSetup != null ) ptrendsSetup.setVisible(false);

					open_be = true;
					dataPanel.setBounds(-dataPanel.getWidth(), 0, BANDSETUP_WIDTH, form.getHeight());
					// dataPanel.setOpaque(false);
					dataPanel.setVisible(true);
					dataPanel.refresh();

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll(); // clear out any pending actions
					Tween.to(dataPanel, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(0, 0) //
							.setCallback(DisplayManager.this) //
							.start(myManager);

				} else if (btn == hideDataSetup) {
					btn.setVisible(false);
					open_be = false;
					// dataPanel.setOpaque(false);
					dataPanel.setVisible(true);

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll(); // clear out any pending actions
					Tween.to(dataPanel, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(-dataPanel.getWidth(), 0) //
							.setCallback(DisplayManager.this) //
							.start(myManager);

				} else if (btn == ptrendsSetup) {
				} else {
					log.error("UNEXPECTED BUTTON TXT: " + txt);
					dataPanel.setVisible(false);
				}
				timer.start();
			}
		});
		return label;
	}

	public Component getForm() {
		return form;
	}

	@Override
	public void onEvent(int type, BaseTween<?> source) {

		if (type == TweenCallback.COMPLETE) {
			// form.setDisplayShim(null);
			form.repaint(); // !!
			timer.stop();
		}

		if( showDataSetup != null) showDataSetup.setVisible(!(open_be || open_pe));
		if( ptrendsSetup != null) ptrendsSetup.setVisible(!(open_be || open_pe));
		hideDataSetup.setVisible(open_be);
		hideLayoutSetup.setVisible(open_pe);

		// this is subtile becasue of the way our repaints work on the timer
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				form.repaint();
			}
		});
	}

	public void clear() {
		if( dataPanel != null ) {
			dataPanel.clear();
		}
		form.clear();
		replayController.clear();
	}

	public void refresh() {
		if( dataPanel != null ) {
			dataPanel.clear();
		}
	}

	public void setAudiofile(File audioFile) {
		replayController.setAudioFile(audioFile);
		if (audioFile == null) {
			enableQuietReplay();
		}

	}

	public void setMessage(String txt) {
		replayController.setMessage(txt);
	}

	public void enableQuietReplay() {
		replayController.enableQuietReplay();
	}

	public void disableReplay() {
		replayController.disableReplay();
	}

	public void setAudiofile(String audioFileName) {
		setAudiofile( (audioFileName == null) ? null : new File(audioFileName));
	}
}
