package idea.display.editor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.HierarchyBoundsListener;
import java.awt.event.HierarchyEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.SwingUtilities;
import javax.swing.plaf.basic.BasicButtonUI;

import lombok.extern.slf4j.Slf4j;
import idea.display.gl.GLInstrumentDisplay;
import idea.gui.VerticalButtonUI;
import idea.tween.JComponentAccessor;
import idea.tween.TheManager;
import aurelienribon.tweenengine.BaseTween;
import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenCallback;
import aurelienribon.tweenengine.TweenManager;

/* 
 * LayeredPaneDemo.java requires
 * images/dukeWaveRed.gif. 
 */
@SuppressWarnings("serial")
@Slf4j
public class DisplayEditorManager extends JLayeredPane implements TweenCallback {
	private static final int BANDSETUP_WIDTH = 340;
	private static final int PARAMSETUP_WIDTH = 640;

	private GLInstrumentDisplay form;
	private BandEditorPanel bandEditor;
	private ParamEditorPanel paramEditor;

	private JButton showBandSetup;
	private JButton ptrendsSetup;
	private JButton hideBandSetup;
	private JButton showParamSetup;
	private JButton hideParamSetup;
	private boolean open_be = false;
	private boolean open_pe = false;

	public DisplayEditorManager(Component gl_form) {
		this.form = (GLInstrumentDisplay) gl_form;

		setLayout(new BorderLayout());

		bandEditor = new BandEditorPanel(form);
		paramEditor = new ParamEditorPanel(form);

		// Create and set up the layered pane.
		setPreferredSize(new Dimension(720, 480));

		// Add several overlapping, colored labels to the layered pane
		// using absolute positioning/sizing.
		VerticalButtonUI rotate90 = new VerticalButtonUI(90);

		showBandSetup = createLabelButton("Band Setup", new Point(0, 0), rotate90);
		ptrendsSetup = createLabelButton("Trends", new Point(0, 91), rotate90);
		hideBandSetup = createLabelButton("Hide", new Point(BANDSETUP_WIDTH - 1, 0), rotate90);
		// showParamSetup = createLabelButton("Param Setup", new Point(20, 0), null);
		showParamSetup = createLabelButton("Param Setup", new Point(0, 182), rotate90);
		hideParamSetup = createLabelButton("Hide", new Point(20, form.getHeight() - 1), null);

		ptrendsSetup.setEnabled( false );
		
		add(showBandSetup, 0);
		add(ptrendsSetup, 0);
		add(hideBandSetup, 1);
		add(showParamSetup, 2);
		add(hideParamSetup, 3);

		hideBandSetup.setVisible(false);
		hideParamSetup.setVisible(false);

		this.setMinimumSize( new Dimension(600,400));
		this.setPreferredSize( new Dimension(700,400));
		form.setBounds(0, 0, 700, 340);

		bandEditor.setOpaque(true);
		bandEditor.setBorder(BorderFactory.createLineBorder(Color.black));

		paramEditor.setSize(PARAMSETUP_WIDTH, form.getHeight() - form.getHParamAreaHeight() - 20);

		add(bandEditor, 0);
		add(paramEditor, 0);

		add(form, BorderLayout.CENTER);
		add(new DisplayButtonBar(this.form), BorderLayout.SOUTH);

		
		form.addHierarchyBoundsListener(new HierarchyBoundsListener() {

			@Override
			public void ancestorMoved(HierarchyEvent e) {
				// TODO Auto-generated method stub

			}

			@Override
			public void ancestorResized(HierarchyEvent e) {
				Dimension parent_sz = e.getComponent().getSize();
				Point me_pos = bandEditor.getLocation();
				Dimension me_dim = bandEditor.getSize();

				if (me_pos.x == parent_sz.width && me_dim.height == parent_sz.height) {
					// ignore...dont propagate redraws
					return;
				}

				// this routine called way too often
				bandEditor.setLocation(-BANDSETUP_WIDTH, 0);
				bandEditor.setSize(BANDSETUP_WIDTH, parent_sz.height);

				paramEditor.setSize(PARAMSETUP_WIDTH, parent_sz.height - form.getHParamAreaHeight() - 20);
				paramEditor.setLocation(0, -paramEditor.getHeight());
				paramEditor.clear();
				
				open_be = false;
				open_pe = false;

				showBandSetup.setVisible(true);
				ptrendsSetup.setVisible(true);
				hideBandSetup.setVisible(false);
				showParamSetup.setVisible(true);
				hideParamSetup.setVisible(false);
			}
		});

		// after adding the controls, tell the parent to check out the sizes again
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

				if (btn == showBandSetup) {
					showParamSetup.setVisible(false);
					showBandSetup.setVisible(false);
					ptrendsSetup.setVisible(false);

					open_be = true;
					bandEditor.setBounds(-bandEditor.getWidth(), 0, BANDSETUP_WIDTH, form.getHeight());
					bandEditor.setOpaque(false);
					bandEditor.setVisible(true);
					bandEditor.refresh();

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll(); // clear out any pending actions
					TheManager shim = new TheManager();
					form.setDisplayShim(shim);
					Tween.to(bandEditor, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(0, 0) //
							.setCallback(DisplayEditorManager.this) //
							.start(myManager);

				} else if (btn == hideBandSetup) {
					btn.setVisible(false);
					open_be = false;
					bandEditor.setOpaque(false);
					bandEditor.setVisible(true);

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll(); // clear out any pending actions
					TheManager shim = new TheManager();
					form.setDisplayShim(shim);
					Tween.to(bandEditor, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(-bandEditor.getWidth(), 0) //
							.setCallback(DisplayEditorManager.this) //
							.start(myManager);

				} else if (btn == showParamSetup) {
					showParamSetup.setVisible(false);
					showBandSetup.setVisible(false);
					ptrendsSetup.setVisible(false);

					open_pe = true;
					paramEditor.setBounds(0, -paramEditor.getHeight(), PARAMSETUP_WIDTH,
							form.getHeight() - form.getHParamAreaHeight() - 20);
					paramEditor.setOpaque(false);
					paramEditor.setVisible(true);

					hideParamSetup.setLocation(0, paramEditor.getHeight());

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll();
					TheManager shim = new TheManager();
					form.setDisplayShim(shim);
					Tween.to(paramEditor, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(0, 0) //
							.setCallback(DisplayEditorManager.this) //
							.start(myManager);
				} else if (btn == hideParamSetup) {
					btn.setVisible(false);
					open_pe = false;
					paramEditor.setOpaque(false);
					paramEditor.setVisible(true);
					paramEditor.clear();

					TweenManager myManager = TheManager.getTweenManager();
					myManager.killAll(); // clear out any pending actions
					TheManager shim = new TheManager();
					form.setDisplayShim(shim);
					Tween.to(paramEditor, JComponentAccessor.POSITION_XY, 1.0f) //
							.target(0, -paramEditor.getHeight()) //
							.setCallback(DisplayEditorManager.this) //
							.start(myManager);
				} else if (btn == ptrendsSetup) {
				} else {
					log.error("UNEXPECTED BUTTON TXT: " + txt);
					bandEditor.setVisible(false);
				}
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
			form.setDisplayShim(null);
			form.repaint(); // !! 
		}

		showBandSetup.setVisible(!(open_be || open_pe));
		ptrendsSetup.setVisible(!(open_be || open_pe));
		hideBandSetup.setVisible(open_be);
		showParamSetup.setVisible(!(open_be || open_pe));
		hideParamSetup.setVisible(open_pe);
		
		if( open_pe) {
			form.addPropertyChangeListener( GLInstrumentDisplay.PROPERTY_SELECTED_PARAM, paramEditor );
		} else {
			form.clearSelection();
			form.removePropertyChangeListener( GLInstrumentDisplay.PROPERTY_SELECTED_PARAM, paramEditor );
		}
		
		// this is subtile becasue of the way our repaints work on the timer
		SwingUtilities.invokeLater( new Runnable() {

			@Override
			public void run() {
				form.repaint();
			} } );
	}
}
