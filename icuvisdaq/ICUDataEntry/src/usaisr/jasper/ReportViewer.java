package idea.jasper;

/*
 * Created on Jul 10, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

import java.awt.Component;
import java.awt.Container;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.sql.Connection;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JViewport;
import javax.swing.filechooser.FileFilter;
import javax.swing.text.DateFormatter;

import net.sf.jasperreports.engine.JRDataSource;
import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExpression;
import net.sf.jasperreports.engine.JRHyperlink;
import net.sf.jasperreports.engine.JRParameter;
import net.sf.jasperreports.engine.JRPrintAnchorIndex;
import net.sf.jasperreports.engine.JRPrintElement;
import net.sf.jasperreports.engine.JRPrintHyperlink;
import net.sf.jasperreports.engine.JRPrintPage;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JasperPrintManager;
import net.sf.jasperreports.engine.JasperReport;
import net.sf.jasperreports.engine.fill.JRBaseFiller;
import net.sf.jasperreports.engine.fill.JRFillDataset;
import net.sf.jasperreports.engine.fill.JRFiller;
import net.sf.jasperreports.engine.util.JRClassLoader;
import net.sf.jasperreports.engine.util.JRLoader;
import net.sf.jasperreports.engine.xml.JRPrintXmlLoader;
import net.sf.jasperreports.view.JRHyperlinkListener;
import net.sf.jasperreports.view.JRSaveContributor;
import net.sf.jasperreports.view.save.JRPrintSaveContributor;
import idea.ConfigurationInfo;
import idea.GuiUtil;

/**
 * 
 */
@SuppressWarnings("serial")
public class ReportViewer extends javax.swing.JPanel implements // FileSaveInterface, 
		JRHyperlinkListener {
	/*
	 * Begin Section added by wlb
	 */
	private ImageIcon[] iconWait = new ImageIcon[2];

	private boolean enablePrompting = true;

	protected Thread thReport = null;

	protected HashMap hmParameters;

	DateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");

	DateFormatter df = new DateFormatter(sdf);

	private JFrame parent;

	private ReportViewer() {
		setName("$Id: ReportViewer.java,v 1.20 2008/07/25 23:41:21 bbaker Exp $");
		initResources(null, null);
		 
		setZooms();

		initComponents();
		initSaveContributors();

		float zoom = 1.0f;
		try {
			Float f = (Float) ConfigurationInfo.getObject("ReportViewer.zoom");
			if (f != null && f > 0.0f) {
				zoom = f;
			}
		} catch (Exception e) {
			// ignore
		}

		setZoomRatio(zoom);

		addHyperlinkListener(this);
	}

	/** Creates new form JRViewer */
	public ReportViewer(HashMap<String,?> hmParameters, String fileName, boolean promptable) throws JRException {
		this();

		this.hmParameters = hmParameters;
		this.enablePrompting = promptable;

		File f = new File(fileName);
		initParameters(f);

		loadReport(fileName, isXML);
		setPageIndex(0);
		refreshPage();

	}

	/** Creates new form JRViewer */
	public ReportViewer(JasperPrint jrPrint) throws JRException {
		this();

		loadReport(jrPrint);
		setPageIndex(0);
		refreshPage();
	}

	/** Creates new form JRViewer */
	public ReportViewer(JFrame parent, String szFileName, boolean enablePrompting) {
		this.parent = parent;
		this.enablePrompting = enablePrompting;

		type = TYPE_FILE_NAME;
		this.isXML = false; // isXML;
		reportFileName = szFileName;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFPrintInterface#Print()
	 */
	public JasperPrint getPrintable() {
		// btnPrintActionPerformed( null );
		// btnSendActionPerformed( null );
		return jasperPrint;
	}

	protected void reloadLinks() {
	} // wlb

	/**
	 */
	protected void startLoadReportThread(String szReport, boolean bXML) {
		class LRT implements Runnable {
			public String szReport;

			public boolean bXML;

			public void run() {
				try {
					Thread.sleep(300);
					lblProgress.setText("Processing...");
					loadReport(szReport, bXML);
					lblProgress.setText("Done...");
					Thread.sleep(1000);

					setPageIndex(0);
					zoom = 0;// force pageRefresh()
					setZoomRatio(1f);

					reloadLinks();
				} catch (Exception e) {
					e.printStackTrace();
					lblProgress.setText("ERROR!!!: " + e.getMessage());
				}
				btnReload.setEnabled(true);
				btnBreak.setEnabled(false);
				thReport = null;
			}
		}
		;

		btnBreak.setEnabled(true);
		btnReload.setEnabled(true);
		LRT r = new LRT();
		r.szReport = szReport;
		r.bXML = bXML;

		thReport = new Thread(r);
		thReport.start();
	}

	public void btnReloadActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnReloadActionPerformed
	{// GEN-HEADEREND:event_btnReloadActionPerformed
		if (hmParameters == null) {
			hmParameters = new HashMap();
		}

		System.out.println("reload action");
		if (type == TYPE_JASPER_PRINT)
			type = TYPE_FILE_NAME;

		if (type == TYPE_FILE_NAME) {
			jasperPrint = null;
			setPageIndex(0);
			zoom = 0;// force pageRefresh()
			setZoomRatio(1);

			try {
				startLoadReportThread(reportFileName, isXML);
			} catch (Exception e) {
				JOptionPane.showMessageDialog(this, "Could not locate report: " + reportFileName + "\n\n"
						+ e.getMessage());
			}

		}
	}// GEN-LAST:event_btnReloadActionPerformed

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFSaveInterface#HaveSave()
	 */

	public boolean HaveSave() {
		// TODO Auto-generated method stub
		return false;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFSaveInterface#HaveSaveAs()
	 */
	public boolean HaveSaveAs() {
		// TODO Auto-generated method stub
		return true;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFSaveInterface#Save()
	 */
	public void Save() {
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFSaveInterface#SaveAs(java.lang.String)
	 */
	public void SaveAs(String szFileName) {
		btnSaveActionPerformed(null);
	}

	/**
	 * @return
	 */
	protected Object getSelectionImage() {

		/*
		 * BufferedImage im = new BufferedImage( sel.getWidth(), sel.getHeight(), BufferedImage.TYPE_INT_RGB );
		 * System.out.println( "this sel w,h = " + sel.getWidth() + "," + sel.getHeight() ); Graphics2D g =
		 * im.createGraphics();
		 * 
		 * this.add( sel ); sel.printAll( g ); this.remove( sel );
		 * 
		 * return im;
		 */
		return null;
	}

	/*
	 * End Section added by wlb
	 */

	/**
	 * 
	 */
	protected static final int TYPE_FILE_NAME = 1;

	private static final int TYPE_INPUT_STREAM = 2;

	protected static final int TYPE_JASPER_PRINT = 3;

	protected float MIN_ZOOM = 0.5f;

	protected float MAX_ZOOM = 2.5f;

	protected int zooms[] = { 50, 75, 100, 125, 150, 175, 200, 250 };

	protected int type = TYPE_FILE_NAME;

	protected boolean isXML = false;

	protected String reportFileName = null;

	protected JasperPrint jasperPrint = null;

	protected int pageIndex = 0;

	protected float zoom = 1f;

	private DecimalFormat zoomDecimalFormat = new DecimalFormat("#.##");

	private int downX = 0;

	private int downY = 0;

	private java.util.List hyperlinkListeners = new ArrayList();

	private Map linksMap = new HashMap();
    protected List saveContributors = new ArrayList();
    protected File lastFolder = null;
    protected JRSaveContributor lastSaveContributor = null;

    private ResourceBundle resourceBundle = null;
    
	private MouseListener mouseListener = new java.awt.event.MouseAdapter() {
		public void mouseClicked(java.awt.event.MouseEvent evt) {
			hyperlinkClicked(evt);
		}
	};

	public void initParameters(File reportFile) {
		// parameters.put("ReportTitle", szCaption );
		if (hmParameters == null)
			hmParameters = new HashMap();
		if (reportFile != null)
			hmParameters.put("BaseDir", reportFile.getParentFile());

		String logoName = ConfigurationInfo.getLogoName();
		if (logoName != null) {
			hmParameters.put("LOGO_NAME", logoName);
		}

	}

	public void setReport(JasperPrint jrPrint) throws JRException {
		loadReport(jrPrint);
		setPageIndex(0);

		reloadLinks();
		refreshPage();
		btnReload.setEnabled(true);
	}

	/**
	 * 
	 */
	public void clear() {
		emptyContainer(this);
		jasperPrint = null;
	}

	/**
	 * 
	 */
	protected void setZooms() {
	}

	/**
	 * 
	 */
	public void addHyperlinkListener(JRHyperlinkListener listener) {
		hyperlinkListeners.add(listener);
	}

	/**
	 * 
	 */
	public void removeHyperlinkListener(JRHyperlinkListener listener) {
		hyperlinkListeners.remove(listener);
	}

	/**
	 * 
	 */
	public void gotoHyperlink(JRPrintHyperlink hyperlink) throws JRException {
		switch (hyperlink.getHyperlinkType()) {
		case JRHyperlink.HYPERLINK_TYPE_REFERENCE: {
			if (hyperlinkListeners != null && hyperlinkListeners.size() > 1) {
				System.out.println("Hyperlink reference : " + hyperlink.getHyperlinkReference());
				System.out.println("Implement your own JRHyperlinkListener to manage this type of event.");
			}
			break;
		}
		case JRHyperlink.HYPERLINK_TYPE_LOCAL_ANCHOR: {
			if (hyperlink.getHyperlinkAnchor() != null) {
				Map anchorIndexes = jasperPrint.getAnchorIndexes();
				JRPrintAnchorIndex anchorIndex = (JRPrintAnchorIndex) anchorIndexes.get(hyperlink.getHyperlinkAnchor());
				if (anchorIndex.getPageIndex() != pageIndex) {
					setPageIndex(anchorIndex.getPageIndex());
					refreshPage();
				}
				Container container = pnlInScroll.getParent();
				if (container instanceof JViewport) {
					JViewport viewport = (JViewport) container;

					int newX = (int) (anchorIndex.getElement().getX() * zoom);
					int newY = (int) (anchorIndex.getElement().getY() * zoom);

					int maxX = pnlInScroll.getWidth() - viewport.getWidth();
					int maxY = pnlInScroll.getHeight() - viewport.getHeight();

					if (newX < 0) {
						newX = 0;
					}
					if (newX > maxX) {
						newX = maxX;
					}
					if (newY < 0) {
						newY = 0;
					}
					if (newY > maxY) {
						newY = maxY;
					}

					viewport.setViewPosition(new Point(newX, newY));
				}
			}

			break;
		}
		case JRHyperlink.HYPERLINK_TYPE_LOCAL_PAGE: {
			int page = pageIndex + 1;
			if (hyperlink.getHyperlinkPage() != null) {
				page = hyperlink.getHyperlinkPage().intValue();
			}

			if (page >= 1 && page <= jasperPrint.getPages().size() && page != pageIndex + 1) {
				setPageIndex(page - 1);
				refreshPage();
				Container container = pnlInScroll.getParent();
				if (container instanceof JViewport) {
					JViewport viewport = (JViewport) container;
					viewport.setViewPosition(new Point(0, 0));
				}
			}

			break;
		}
		case JRHyperlink.HYPERLINK_TYPE_REMOTE_ANCHOR: {
			if (hyperlinkListeners != null && hyperlinkListeners.size() > 1) {
				System.out.println("Hyperlink reference : " + hyperlink.getHyperlinkReference());
				System.out.println("Hyperlink anchor    : " + hyperlink.getHyperlinkAnchor());
				System.out.println("Implement your own JRHyperlinkListener to manage this type of event.");
			}
			break;
		}
		case JRHyperlink.HYPERLINK_TYPE_REMOTE_PAGE: {
			if (hyperlinkListeners != null && hyperlinkListeners.size() > 1) {
				System.out.println("Hyperlink reference : " + hyperlink.getHyperlinkReference());
				System.out.println("Hyperlink page      : " + hyperlink.getHyperlinkPage());
				System.out.println("Implement your own JRHyperlinkListener to manage this type of event.");
			}
			break;
		}
		case JRHyperlink.HYPERLINK_TYPE_NONE:
		default: {
			break;
		}
		}
	}

	/**
	 * This method is called from within the constructor to initialize the form. WARNING: Do NOT modify this code. The
	 * content of this method is always regenerated by the Form Editor.
	 */
	private void initComponents() {// GEN-BEGIN:initComponents
		java.awt.GridBagConstraints gridBagConstraints;

		java.net.URL imageURL;

		imageURL = ReportViewer.class.getResource("com/ddd/images/polling.gif");
		if (imageURL != null) {
			iconWait[0] = new ImageIcon(imageURL);
		}

		imageURL = ReportViewer.class.getResource("com/ddd/images/nopoll.gif");
		if (imageURL != null) {
			iconWait[1] = new ImageIcon(imageURL);
		}

		tlbToolBar = new javax.swing.JPanel();
		btnSave = new javax.swing.JButton();
		btnPrint = new javax.swing.JButton();
		btnSend = new javax.swing.JButton();
		btnReload = new javax.swing.JButton();
		pnlSep01 = new javax.swing.JPanel();
		btnFirst = new javax.swing.JButton();
		btnPrevious = new javax.swing.JButton();
		btnNext = new javax.swing.JButton();
		btnLast = new javax.swing.JButton();
		pnlSep02 = new javax.swing.JPanel();
		btnActualSize = new javax.swing.JToggleButton();
		btnFitPage = new javax.swing.JToggleButton();
		btnFitWidth = new javax.swing.JToggleButton();
		pnlSep03 = new javax.swing.JPanel();
		btnZoomIn = new javax.swing.JButton();
		btnZoomOut = new javax.swing.JButton();
		cmbZoom = new javax.swing.JComboBox();
		DefaultComboBoxModel model = new DefaultComboBoxModel();
		for (int i = 0; i < zooms.length; i++) {
			model.addElement("" + zooms[i] + "%");
		}
		cmbZoom.setModel(model);

		pnlMain = new javax.swing.JPanel();
		scrollPane = new javax.swing.JScrollPane();
		scrollPane.getHorizontalScrollBar().setUnitIncrement(5);
		scrollPane.getVerticalScrollBar().setUnitIncrement(5);

		pnlInScroll = new javax.swing.JPanel();
		pnlPage = new javax.swing.JPanel();
		jPanel4 = new javax.swing.JPanel();
		pnlLinks = new javax.swing.JPanel();
		jPanel5 = new javax.swing.JPanel();
		jPanel6 = new javax.swing.JPanel();
		jPanel7 = new javax.swing.JPanel();
		jPanel8 = new javax.swing.JPanel();
		jLabel1 = new javax.swing.JLabel();
		jPanel9 = new javax.swing.JPanel();
		lblPage = new javax.swing.JLabel();
		pnlStatus = new javax.swing.JPanel();
		lblStatus = new javax.swing.JLabel();

		lblSpacer = new javax.swing.JPanel();
		lblProgress = new javax.swing.JLabel();
		btnBreak = new javax.swing.JButton();

		setLayout(new java.awt.BorderLayout());

		setMinimumSize(new java.awt.Dimension(450, 150));
		setPreferredSize(new java.awt.Dimension(450, 150));
		tlbToolBar.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 0, 2));

		btnSave
				.setIcon(new javax.swing.ImageIcon(getClass().getResource("/net/sf/jasperreports/view/images/save.GIF")));
		btnSave.setToolTipText("Save");
		btnSave.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnSave.setMaximumSize(new java.awt.Dimension(23, 23));
		btnSave.setMinimumSize(new java.awt.Dimension(23, 23));
		btnSave.setPreferredSize(new java.awt.Dimension(23, 23));
		btnSave.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnSaveActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnSave);

		btnPrint.setIcon(new javax.swing.ImageIcon(getClass()
				.getResource("/net/sf/jasperreports/view/images/print.GIF")));
		btnPrint.setToolTipText("Print");
		btnPrint.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnPrint.setMaximumSize(new java.awt.Dimension(23, 23));
		btnPrint.setMinimumSize(new java.awt.Dimension(23, 23));
		btnPrint.setPreferredSize(new java.awt.Dimension(23, 23));
		btnPrint.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnPrintActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnPrint);

		btnSend.setIcon(new javax.swing.ImageIcon(getClass().getResource("/com/ddd/images/send.GIF")));
		btnSend.setToolTipText("Send");
		btnSend.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnSend.setMaximumSize(new java.awt.Dimension(23, 23));
		btnSend.setMinimumSize(new java.awt.Dimension(23, 23));
		btnSend.setPreferredSize(new java.awt.Dimension(23, 23));
		btnSend.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnSendActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnSend);

		btnReload.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/reload.GIF")));
		btnReload.setToolTipText("Reload");
		btnReload.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnReload.setMaximumSize(new java.awt.Dimension(23, 23));
		btnReload.setMinimumSize(new java.awt.Dimension(23, 23));
		btnReload.setPreferredSize(new java.awt.Dimension(23, 23));
		btnReload.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnReloadActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnReload);

		// intended to stop report loading
		btnBreak.setIcon(new javax.swing.ImageIcon(getClass()
				.getResource("/net/sf/jasperreports/view/images/first.GIF")));
		btnBreak.setToolTipText("Break");
		btnBreak.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnBreak.setMaximumSize(new java.awt.Dimension(23, 23));
		btnBreak.setMinimumSize(new java.awt.Dimension(23, 23));
		btnBreak.setPreferredSize(new java.awt.Dimension(23, 23));
		btnBreak.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				if (thReport != null) {
					thReport.stop();
					thReport = null;
					btnReload.setEnabled(true);
					btnBreak.setEnabled(false);
				}
			}
		});
		btnBreak.setEnabled(false);

		tlbToolBar.add(btnBreak);

		pnlSep01.setMaximumSize(new java.awt.Dimension(10, 10));
		tlbToolBar.add(pnlSep01);

		btnFirst.setIcon(new javax.swing.ImageIcon(getClass()
				.getResource("/net/sf/jasperreports/view/images/first.GIF")));
		btnFirst.setToolTipText("First Page");
		btnFirst.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnFirst.setMaximumSize(new java.awt.Dimension(23, 23));
		btnFirst.setMinimumSize(new java.awt.Dimension(23, 23));
		btnFirst.setPreferredSize(new java.awt.Dimension(23, 23));
		btnFirst.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnFirstActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnFirst);

		btnPrevious.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/previous.GIF")));
		btnPrevious.setToolTipText("Previous Page");
		btnPrevious.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnPrevious.setMaximumSize(new java.awt.Dimension(23, 23));
		btnPrevious.setMinimumSize(new java.awt.Dimension(23, 23));
		btnPrevious.setPreferredSize(new java.awt.Dimension(23, 23));
		btnPrevious.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnPreviousActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnPrevious);

		btnNext
				.setIcon(new javax.swing.ImageIcon(getClass().getResource("/net/sf/jasperreports/view/images/next.GIF")));
		btnNext.setToolTipText("Next Page");
		btnNext.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnNext.setMaximumSize(new java.awt.Dimension(23, 23));
		btnNext.setMinimumSize(new java.awt.Dimension(23, 23));
		btnNext.setPreferredSize(new java.awt.Dimension(23, 23));
		btnNext.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnNextActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnNext);

		btnLast
				.setIcon(new javax.swing.ImageIcon(getClass().getResource("/net/sf/jasperreports/view/images/last.GIF")));
		btnLast.setToolTipText("Last Page");
		btnLast.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnLast.setMaximumSize(new java.awt.Dimension(23, 23));
		btnLast.setMinimumSize(new java.awt.Dimension(23, 23));
		btnLast.setPreferredSize(new java.awt.Dimension(23, 23));
		btnLast.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnLastActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnLast);

		pnlSep02.setMaximumSize(new java.awt.Dimension(10, 10));
		tlbToolBar.add(pnlSep02);

		btnActualSize.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/actualsize.GIF")));
		btnActualSize.setToolTipText("Actual Size");
		btnActualSize.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnActualSize.setMaximumSize(new java.awt.Dimension(23, 23));
		btnActualSize.setMinimumSize(new java.awt.Dimension(23, 23));
		btnActualSize.setPreferredSize(new java.awt.Dimension(23, 23));
		btnActualSize.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnActualSizeActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnActualSize);

		btnFitPage.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/fitpage.GIF")));
		btnFitPage.setToolTipText("Fit Page");
		btnFitPage.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnFitPage.setMaximumSize(new java.awt.Dimension(23, 23));
		btnFitPage.setMinimumSize(new java.awt.Dimension(23, 23));
		btnFitPage.setPreferredSize(new java.awt.Dimension(23, 23));
		btnFitPage.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnFitPageActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnFitPage);

		btnFitWidth.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/fitwidth.GIF")));
		btnFitWidth.setToolTipText("Fit Width");
		btnFitWidth.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnFitWidth.setMaximumSize(new java.awt.Dimension(23, 23));
		btnFitWidth.setMinimumSize(new java.awt.Dimension(23, 23));
		btnFitWidth.setPreferredSize(new java.awt.Dimension(23, 23));
		btnFitWidth.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnFitWidthActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnFitWidth);

		pnlSep03.setMaximumSize(new java.awt.Dimension(10, 10));
		tlbToolBar.add(pnlSep03);

		btnZoomIn.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/zoomin.GIF")));
		btnZoomIn.setToolTipText("Zoom In");
		btnZoomIn.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnZoomIn.setMaximumSize(new java.awt.Dimension(23, 23));
		btnZoomIn.setMinimumSize(new java.awt.Dimension(23, 23));
		btnZoomIn.setPreferredSize(new java.awt.Dimension(23, 23));
		btnZoomIn.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnZoomInActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnZoomIn);

		btnZoomOut.setIcon(new javax.swing.ImageIcon(getClass().getResource(
				"/net/sf/jasperreports/view/images/zoomout.GIF")));
		btnZoomOut.setToolTipText("Zoom Out");
		btnZoomOut.setMargin(new java.awt.Insets(2, 2, 2, 2));
		btnZoomOut.setMaximumSize(new java.awt.Dimension(23, 23));
		btnZoomOut.setMinimumSize(new java.awt.Dimension(23, 23));
		btnZoomOut.setPreferredSize(new java.awt.Dimension(23, 23));
		btnZoomOut.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				btnZoomOutActionPerformed(evt);
			}
		});

		tlbToolBar.add(btnZoomOut);

		cmbZoom.setEditable(true);
		cmbZoom.setToolTipText("Zoom Ratio");
		cmbZoom.setMaximumSize(new java.awt.Dimension(80, 23));
		cmbZoom.setMinimumSize(new java.awt.Dimension(80, 23));
		cmbZoom.setPreferredSize(new java.awt.Dimension(80, 23));
		cmbZoom.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				cmbZoomActionPerformed(evt);
			}
		});

		cmbZoom.addItemListener(new java.awt.event.ItemListener() {
			public void itemStateChanged(java.awt.event.ItemEvent evt) {
				cmbZoomItemStateChanged(evt);
			}
		});

		tlbToolBar.add(cmbZoom);

		lblSpacer.setMinimumSize(new java.awt.Dimension(10, 10));
		lblSpacer.setMaximumSize(new java.awt.Dimension(1000, 10));
		tlbToolBar.add(lblSpacer);

		lblProgress.setText("New Report");
		tlbToolBar.add(lblProgress);

		add(tlbToolBar, java.awt.BorderLayout.NORTH);

		pnlMain.setLayout(new java.awt.BorderLayout());

		pnlMain.addComponentListener(new java.awt.event.ComponentAdapter() {
			public void componentResized(java.awt.event.ComponentEvent evt) {
				pnlMainComponentResized(evt);
			}
		});

		scrollPane.setHorizontalScrollBarPolicy(javax.swing.JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		scrollPane.setVerticalScrollBarPolicy(javax.swing.JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		pnlInScroll.setLayout(new java.awt.GridBagLayout());

		pnlPage.setLayout(new java.awt.BorderLayout());

		pnlPage.setMinimumSize(new java.awt.Dimension(100, 100));
		pnlPage.setPreferredSize(new java.awt.Dimension(100, 100));
		jPanel4.setLayout(new java.awt.GridBagLayout());

		jPanel4.setMinimumSize(new java.awt.Dimension(100, 120));
		jPanel4.setPreferredSize(new java.awt.Dimension(100, 120));
		pnlLinks.setLayout(null);

		pnlLinks.setMinimumSize(new java.awt.Dimension(5, 5));
		pnlLinks.setPreferredSize(new java.awt.Dimension(5, 5));
		pnlLinks.setOpaque(false);
		pnlLinks.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mousePressed(java.awt.event.MouseEvent evt) {
				pnlLinksMousePressed(evt);
			}

			public void mouseReleased(java.awt.event.MouseEvent evt) {
				pnlLinksMouseReleased(evt);
			}
		});

		pnlLinks.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
			public void mouseDragged(java.awt.event.MouseEvent evt) {
				pnlLinksMouseDragged(evt);
			}
		});

		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 0;
		gridBagConstraints.gridy = 0;
		gridBagConstraints.gridwidth = 2;
		gridBagConstraints.gridheight = 2;
		gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
		jPanel4.add(pnlLinks, gridBagConstraints);

		jPanel5.setBackground(java.awt.Color.gray);
		jPanel5.setMinimumSize(new java.awt.Dimension(5, 5));
		jPanel5.setPreferredSize(new java.awt.Dimension(5, 5));
		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 2;
		gridBagConstraints.gridy = 1;
		gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
		jPanel4.add(jPanel5, gridBagConstraints);

		jPanel6.setMinimumSize(new java.awt.Dimension(5, 5));
		jPanel6.setPreferredSize(new java.awt.Dimension(5, 5));
		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 0;
		gridBagConstraints.gridy = 2;
		jPanel4.add(jPanel6, gridBagConstraints);

		jPanel7.setBackground(java.awt.Color.gray);
		jPanel7.setMinimumSize(new java.awt.Dimension(5, 5));
		jPanel7.setPreferredSize(new java.awt.Dimension(5, 5));
		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 1;
		gridBagConstraints.gridy = 2;
		gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
		jPanel4.add(jPanel7, gridBagConstraints);

		jPanel8.setBackground(java.awt.Color.gray);
		jPanel8.setMinimumSize(new java.awt.Dimension(5, 5));
		jPanel8.setPreferredSize(new java.awt.Dimension(5, 5));
		jLabel1.setText("jLabel1");
		jPanel8.add(jLabel1);

		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 2;
		gridBagConstraints.gridy = 2;
		jPanel4.add(jPanel8, gridBagConstraints);

		jPanel9.setMinimumSize(new java.awt.Dimension(5, 5));
		jPanel9.setPreferredSize(new java.awt.Dimension(5, 5));
		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 2;
		gridBagConstraints.gridy = 0;
		jPanel4.add(jPanel9, gridBagConstraints);

		lblPage.setBackground(java.awt.Color.white);
		lblPage.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0)));
		lblPage.setOpaque(true);
		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.gridx = 0;
		gridBagConstraints.gridy = 0;
		gridBagConstraints.gridwidth = 2;
		gridBagConstraints.gridheight = 2;
		gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
		gridBagConstraints.weightx = 1.0;
		gridBagConstraints.weighty = 1.0;
		jPanel4.add(lblPage, gridBagConstraints);

		pnlPage.add(jPanel4, java.awt.BorderLayout.CENTER);

		gridBagConstraints = new java.awt.GridBagConstraints();
		gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
		pnlInScroll.add(pnlPage, gridBagConstraints);

		scrollPane.setViewportView(pnlInScroll);

		pnlMain.add(scrollPane, java.awt.BorderLayout.CENTER);

		add(pnlMain, java.awt.BorderLayout.CENTER);

		pnlStatus.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.CENTER, 0, 0));

		lblStatus.setFont(new java.awt.Font("Dialog", 1, 10));
		lblStatus.setText("Page i of n");
		pnlStatus.add(lblStatus);

		add(pnlStatus, java.awt.BorderLayout.SOUTH);

		btnReload.setEnabled(true); // wlb

	}// GEN-END:initComponents

	private void cmbZoomItemStateChanged(java.awt.event.ItemEvent evt) {// GEN-FIRST:event_cmbZoomItemStateChanged
		// Add your handling code here:
		btnActualSize.setSelected(false);
		btnFitPage.setSelected(false);
		btnFitWidth.setSelected(false);
	}// GEN-LAST:event_cmbZoomItemStateChanged

	private void pnlMainComponentResized(java.awt.event.ComponentEvent evt) {// GEN-FIRST:event_pnlMainComponentResized
		// Add your handling code here:
		if (btnFitPage.isSelected()) {
			setZoomRatio(((float) pnlInScroll.getVisibleRect().getHeight() - 20f) / (float) jasperPrint.getPageHeight());
		} else if (btnFitWidth.isSelected()) {
			setZoomRatio(((float) pnlInScroll.getVisibleRect().getWidth() - 20f) / (float) jasperPrint.getPageWidth());
		}

	}// GEN-LAST:event_pnlMainComponentResized

	private void btnActualSizeActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_btnActualSizeActionPerformed
		// Add your handling code here:
		if (btnActualSize.isSelected()) {
			btnFitPage.setSelected(false);
			btnFitWidth.setSelected(false);

			setZoomRatio(1);
		}
	}// GEN-LAST:event_btnActualSizeActionPerformed

	private void btnFitWidthActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_btnFitWidthActionPerformed
		// Add your handling code here:
		if (btnFitWidth.isSelected()) {
			btnActualSize.setSelected(false);
			btnFitPage.setSelected(false);

			setZoomRatio(((float) pnlInScroll.getVisibleRect().getWidth() - 20f) / (float) jasperPrint.getPageWidth());
		}
	}// GEN-LAST:event_btnFitWidthActionPerformed

	private void btnFitPageActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_btnFitPageActionPerformed
		// Add your handling code here:
		if (btnFitPage.isSelected()) {
			btnActualSize.setSelected(false);
			btnFitWidth.setSelected(false);

			setZoomRatio(((float) pnlInScroll.getVisibleRect().getHeight() - 20f) / (float) jasperPrint.getPageHeight());
		}
	}// GEN-LAST:event_btnFitPageActionPerformed

    /**
    *
    */
   protected void initResources(Locale locale, ResourceBundle resBundle)
   {
           if (locale != null)
                   setLocale(locale);
           else
                   setLocale(Locale.getDefault());

           if (resBundle == null)
           {
                   this.resourceBundle = ResourceBundle.getBundle("net/sf/jasperreports/view/viewer", getLocale());
           }
           else
           {
                   this.resourceBundle = resBundle;
           }
   }


   /**
    *
    */
   protected String getBundleString(String key)
   {
           return resourceBundle.getString(key);
   }
    /**
    *
    */
   protected void initSaveContributors()
   {
           final String[] DEFAULT_CONTRIBUTORS =
                   {
                           // "net.sf.jasperreports.view.save.JRPrintSaveContributor",
                           "net.sf.jasperreports.view.save.JRPdfSaveContributor",
                           "net.sf.jasperreports.view.save.JRRtfSaveContributor",
                           // "net.sf.jasperreports.view.save.JROdtSaveContributor",
                           "net.sf.jasperreports.view.save.JRHtmlSaveContributor",
                           "net.sf.jasperreports.view.save.JRSingleSheetXlsSaveContributor",
                           "net.sf.jasperreports.view.save.JRMultipleSheetsXlsSaveContributor",
                           "net.sf.jasperreports.view.save.JRCsvSaveContributor",
                           // "net.sf.jasperreports.view.save.JRXmlSaveContributor",
                           // "net.sf.jasperreports.view.save.JREmbeddedImagesXmlSaveContributor"
                   };

           for(int i = 0; i < DEFAULT_CONTRIBUTORS.length; i++)
           {
                   try
                   {
                           Class saveContribClass = JRClassLoader.loadClassForName(DEFAULT_CONTRIBUTORS[i]);
                           Constructor constructor = saveContribClass.getConstructor(new Class[]{Locale.class, ResourceBundle.class});
                           JRSaveContributor saveContrib = (JRSaveContributor)constructor.newInstance(new Object[]{getLocale(), resourceBundle});
                           saveContributors.add(saveContrib);
                   }
                   catch (Exception e)
                   {
                   }
           }
   }
   
   void btnSaveActionPerformed(java.awt.event.ActionEvent evt) {
	                   // Add your handling code here:

	                   JFileChooser fileChooser = new JFileChooser();
	                   fileChooser.setLocale(this.getLocale());
	                   fileChooser.updateUI();
	                   for(int i = 0; i < saveContributors.size(); i++)
	                   {
	                           fileChooser.addChoosableFileFilter((JRSaveContributor)saveContributors.get(i));
	                   }

	                   if (saveContributors.contains(lastSaveContributor))
	                   {
	                           fileChooser.setFileFilter(lastSaveContributor);
	                   }
	                   else if (saveContributors.size() > 0)
	                   {
	                           fileChooser.setFileFilter((JRSaveContributor)saveContributors.get(0));
	                   }

	                   if (lastFolder != null)
	                   {
	                           fileChooser.setCurrentDirectory(lastFolder);
	                   }

	                   int retValue = fileChooser.showSaveDialog(this);
	                   if (retValue == JFileChooser.APPROVE_OPTION)
	                   {
	                           FileFilter fileFilter = fileChooser.getFileFilter();
	                           File file = fileChooser.getSelectedFile();

	                           lastFolder = file.getParentFile();

	                           JRSaveContributor contributor = null;

	                           if (fileFilter instanceof JRSaveContributor)
	                           {
	                                   contributor = (JRSaveContributor)fileFilter;
	                           }
	                           else
	                           {
	                                   int i = 0;
	                                   while(contributor == null && i < saveContributors.size())
	                                   {
	                                           contributor = (JRSaveContributor)saveContributors.get(i++);
	                                           if (!contributor.accept(file))
	                                           {
	                                                   contributor = null;
	                                           }
	                                   }

	                                   if (contributor == null)
	                                   {
	                                           contributor = new JRPrintSaveContributor(getLocale(), this.resourceBundle);
	                                   }
	                           }

	                           lastSaveContributor = contributor;

	                           try
	                           {
	                                   contributor.save(jasperPrint, file);
	                           }
	                           catch (JRException e)
	                           {
	                                   e.printStackTrace();
	                                   // JOptionPane.showMessageDialog(this, getBundleString("error.saving"));
	                   				JOptionPane.showMessageDialog(null, "Error saving document. See the console for details.");
	                           }
	                   }
	           }
   
//	private void btnSaveActionPerformed2(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_btnSaveActionPerformed
//		// Add your handling code here:
//
//		JFileChooser fileChooser = new JFileChooser();
//
//		FileFilter jrprintFileFilter = new FileFilter() {
//			public boolean accept(File file) {
//				if (file.isDirectory())
//					return true;
//				else
//					return file.getName().toLowerCase().endsWith(".jrprint");
//			}
//
//			public String getDescription() {
//				return "JasperReports (*.jrprint)";
//			}
//		};
//		fileChooser.addChoosableFileFilter(jrprintFileFilter);
//
//		// fileChooser.addChoosableFileFilter(xmlEmbeddedImagesSaver);
//
//		fileChooser.setFileFilter(jrprintFileFilter);
//
//		int retValue = fileChooser.showSaveDialog(this);
//		if (retValue == JFileChooser.APPROVE_OPTION) {
//			FileFilter fileFilter = fileChooser.getFileFilter();
//			File file = fileChooser.getSelectedFile();
//			String lowerCaseFileName = file.getName().toLowerCase();
//
//			try {
//				if (fileFilter == jrprintFileFilter) {
//					JRSaver.saveObject(jasperPrint, file);
//				} else if (fileFilter instanceof JRSaveContributor) {
//					((JRSaveContributor) fileFilter).save(jasperPrint, file);
//				} else {
//					if (lowerCaseFileName.endsWith(".jrprint")) {
//						JRSaver.saveObject(jasperPrint, file);
//					} else if (lowerCaseFileName.endsWith(".pdf") && pdfSaveContrib != null) {
//						pdfSaveContrib.save(jasperPrint, file);
//					} else if ((lowerCaseFileName.endsWith(".html") || lowerCaseFileName.endsWith(".htm"))
//							&& htmlSaver != null) {
//						htmlSaver.save(jasperPrint, file);
//					} else if (lowerCaseFileName.endsWith(".xls") && xlsSingleSheetSaver != null) {
//						xlsSingleSheetSaver.save(jasperPrint, file);
//					} else if (lowerCaseFileName.endsWith(".csv") && csvSaver != null) {
//						csvSaver.save(jasperPrint, file);
//					} else if (lowerCaseFileName.endsWith(".xml") || lowerCaseFileName.endsWith(".jrpxml")
//							&& xmlSaver != null) {
//						xmlSaver.save(jasperPrint, file);
//					} else {
//						JRSaver.saveObject(jasperPrint, fileChooser.getSelectedFile());
//					}
//				}
//			} catch (JRException e) {
//				e.printStackTrace();
//				JOptionPane.showMessageDialog(null, "Error saving document. See the console for details.");
//			}
//		}
//	}// GEN-LAST:event_btnSaveActionPerformed

	private void pnlLinksMouseDragged(java.awt.event.MouseEvent evt) {// GEN-FIRST:event_pnlLinksMouseDragged
		// Add your handling code here:

		Container container = pnlInScroll.getParent();
		if (container instanceof JViewport) {
			JViewport viewport = (JViewport) container;
			Point point = viewport.getViewPosition();
			int newX = point.x - (evt.getX() - downX);
			int newY = point.y - (evt.getY() - downY);

			int maxX = pnlInScroll.getWidth() - viewport.getWidth();
			int maxY = pnlInScroll.getHeight() - viewport.getHeight();

			if (newX < 0) {
				newX = 0;
			}
			if (newX > maxX) {
				newX = maxX;
			}
			if (newY < 0) {
				newY = 0;
			}
			if (newY > maxY) {
				newY = maxY;
			}

			viewport.setViewPosition(new Point(newX, newY));
		}
	}// GEN-LAST:event_pnlLinksMouseDragged

	private void pnlLinksMouseReleased(java.awt.event.MouseEvent evt) {// GEN-FIRST:event_pnlLinksMouseReleased
		// Add your handling code here:
		pnlLinks.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
	}// GEN-LAST:event_pnlLinksMouseReleased

	private void pnlLinksMousePressed(java.awt.event.MouseEvent evt) {// GEN-FIRST:event_pnlLinksMousePressed
		// Add your handling code here:
		pnlLinks.setCursor(new Cursor(Cursor.MOVE_CURSOR));

		downX = evt.getX();
		downY = evt.getY();
	}// GEN-LAST:event_pnlLinksMousePressed

	private void btnPrintActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnPrintActionPerformed
	{// GEN-HEADEREND:event_btnPrintActionPerformed
		// Add your handling code here:

		Thread thread = new Thread(new Runnable() {
			public void run() {
				try {
					JasperPrintManager.printReport(jasperPrint, true);
				} catch (Exception ex) {
					ex.printStackTrace();
					JOptionPane.showMessageDialog(null, "Error printing report. See the console for details.");
				}
			}
		});

		thread.start();

	}// GEN-LAST:event_btnPrintActionPerformed

	private void btnSendActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnSendActionPerformed
	{
//		Contact contact = null ;
//		
//		Long contactRecnum = (Long)getClientProperty("PFT_CONTACT");
//		if( contactRecnum != null ) {
//			EntityManager em = JpaUtil.getEntityManager();
//			try {
//				contact = em.find( Contact.class, contactRecnum );
//			} catch (Exception e) {
//				// ignore entity not found
//			}
//			em.close();
//		}
		Object contact = null;
		
		String subject = (String) hmParameters.get("PMC_MAIL_SUBJECT");
		String title = (String)getClientProperty("PFT_TITLE");
		GuiUtil.showMessage( "SEND not ready!");
		// SendPanel.send( subject, title, jasperPrint, contact );
	}

	private void btnLastActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnLastActionPerformed
	{// GEN-HEADEREND:event_btnLastActionPerformed
		// Add your handling code here:
		setPageIndex(jasperPrint.getPages().size() - 1);
		refreshPage();
	}// GEN-LAST:event_btnLastActionPerformed

	private void btnNextActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnNextActionPerformed
	{// GEN-HEADEREND:event_btnNextActionPerformed
		// Add your handling code here:
		setPageIndex(pageIndex + 1);
		refreshPage();
	}// GEN-LAST:event_btnNextActionPerformed

	private void btnPreviousActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnPreviousActionPerformed
	{// GEN-HEADEREND:event_btnPreviousActionPerformed
		// Add your handling code here:
		setPageIndex(pageIndex - 1);
		refreshPage();
	}// GEN-LAST:event_btnPreviousActionPerformed

	private void btnFirstActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnFirstActionPerformed
	{// GEN-HEADEREND:event_btnFirstActionPerformed
		// Add your handling code here:
		setPageIndex(0);
		refreshPage();
	}// GEN-LAST:event_btnFirstActionPerformed

	/*
	 * private void btnReloadActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_btnReloadActionPerformed
	 * {//GEN-HEADEREND:event_btnReloadActionPerformed // Add your handling code here: if (type == TYPE_FILE_NAME) { try {
	 * loadReport(reportFileName, isXML); } catch (JRException e) { e.printStackTrace();
	 * 
	 * jasperPrint = null; setPageIndex(0); refreshPage();
	 * 
	 * JOptionPane.showMessageDialog(this, "Error loading report. See the console for details."); }
	 * 
	 * setPageIndex(0); zoom = 0;//force pageRefresh() setZoomRatio(1); } }//GEN-LAST:event_btnReloadActionPerformed
	 */

	private void btnZoomInActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnZoomInActionPerformed
	{// GEN-HEADEREND:event_btnZoomInActionPerformed
		// Add your handling code here:
		btnActualSize.setSelected(false);
		btnFitPage.setSelected(false);
		btnFitWidth.setSelected(false);

		int newZoomInt = (int) (100 * getZoomRatio());
		int index = Arrays.binarySearch(zooms, newZoomInt);
		if (index < 0) {
			setZoomRatio((float) zooms[-index - 1] / 100f);
		} else if (index < cmbZoom.getModel().getSize() - 1) {
			setZoomRatio((float) zooms[index + 1] / 100f);
		}
	}// GEN-LAST:event_btnZoomInActionPerformed

	private void btnZoomOutActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_btnZoomOutActionPerformed
	{// GEN-HEADEREND:event_btnZoomOutActionPerformed
		// Add your handling code here:
		btnActualSize.setSelected(false);
		btnFitPage.setSelected(false);
		btnFitWidth.setSelected(false);

		int newZoomInt = (int) (100 * getZoomRatio());
		int index = Arrays.binarySearch(zooms, newZoomInt);
		if (index > 0) {
			setZoomRatio((float) zooms[index - 1] / 100f);
		} else if (index < -1) {
			setZoomRatio((float) zooms[-index - 2] / 100f);
		}
	}// GEN-LAST:event_btnZoomOutActionPerformed

	private void cmbZoomActionPerformed(java.awt.event.ActionEvent evt)// GEN-FIRST:event_cmbZoomActionPerformed
	{// GEN-HEADEREND:event_cmbZoomActionPerformed
		// Add your handling code here:
		float newZoom = getZoomRatio();

		if (newZoom < MIN_ZOOM) {
			newZoom = MIN_ZOOM;
		}

		if (newZoom > MAX_ZOOM) {
			newZoom = MAX_ZOOM;
		}

		setZoomRatio(newZoom);
	}// GEN-LAST:event_cmbZoomActionPerformed

	/**
	 */
	private void hyperlinkClicked(MouseEvent evt) {
		JPanel link = (JPanel) evt.getSource();
		JRPrintHyperlink element = (JRPrintHyperlink) linksMap.get(link);

		try {
			JRHyperlinkListener listener = null;
			for (int i = 0; i < hyperlinkListeners.size(); i++) {
				listener = (JRHyperlinkListener) hyperlinkListeners.get(i);
				listener.gotoHyperlink(element);
			}
		} catch (JRException e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(this,
					"Error encoutered when following hyperlink. See the console for details.");
		}
	}

	/**
	 */
	protected void setPageIndex(int index) {
		pageIndex = index;
		if (jasperPrint != null && jasperPrint.getPages() != null && jasperPrint.getPages().size() > 0) {
			btnFirst.setEnabled((pageIndex > 0));
			btnPrevious.setEnabled((pageIndex > 0));
			btnNext.setEnabled((pageIndex < jasperPrint.getPages().size() - 1));
			btnLast.setEnabled((pageIndex < jasperPrint.getPages().size() - 1));
			lblStatus.setText("Page " + (pageIndex + 1) + " of " + jasperPrint.getPages().size());
		} else {
			btnFirst.setEnabled(false);
			btnPrevious.setEnabled(false);
			btnNext.setEnabled(false);
			btnLast.setEnabled(false);
			lblStatus.setText("");
		}
	}

	public static JasperPrint fill(JFrame parent, JPanel owner, JasperReport jasperReport, HashMap hmParameters, boolean enablePrompting)
			throws JRException {

		String szDataSource = null;
		JRDataSource jrds = null;
		JasperPrint jasperPrint = null;

		JRParameter[] jrparamReport = jasperReport.getParameters();

		String prompter = null;

		for (int i = 0; i < jrparamReport.length; i++) {
			String szName = jrparamReport[i].getName();
			// String szValClass = jrparamReport[i].getValueClassName();
			if (szName.equals("REPORT_PARAMETERS_MAP"))
				continue;
			if (szName.equals("REPORT_CONNECTION"))
				continue;
			if (szName.equals("REPORT_DATA_SOURCE"))
				continue;
			if (szName.equals("REPORT_SCRIPTLET"))
				continue;
			if (szName.equals("PFT_OPERATOR"))
				continue;
			if (szName.equals("PFT_TODAY"))
				continue;

			// new in 1.0
			if (szName.equals("IS_IGNORE_PAGINATION"))
				continue;
			if (szName.equals("REPORT_VIRTUALIZER"))
				continue;
			if (szName.equals("REPORT_CLASS_LOADER"))
				continue;

			if (szName.equals(""))
				continue;

			if (szName.equals("PFT_PROMPTER")) {
				JRExpression exp = jrparamReport[i].getDefaultValueExpression();
				prompter = exp.getText();
				prompter = prompter.replaceAll("\"", "");
			}

			if (szName.equals("PFT_DATASOURCE")) {
				if (szDataSource == null) {
					JRExpression exp = jrparamReport[i].getDefaultValueExpression();
					szDataSource = exp.getText();
					continue;
				}
			}
		}

		if (szDataSource != null) {
			if (szDataSource.startsWith("\"")) {
				// some versions of JasperReports compile the quotes into the
				// parameter ?
				szDataSource = szDataSource.substring(1, szDataSource.length() - 1);
			}
		}

		if (enablePrompting) {
			ParameterManager.prompt(parent, jasperReport.getName(), prompter, hmParameters, jrparamReport);
			String title = (String) hmParameters.get("PFT_TITLE");
			if (title != null && owner != null ) {
				owner.putClientProperty("PFT_TITLE", title);
			}
		}

		Connection conn = null;
		if (hmParameters.containsKey("REPORT_CONNECTION")) {
			conn = (Connection) hmParameters.get("REPORT_CONNECTION");
		}

		if (szDataSource != null) {

			Class dsClass;
			Object o;
			try {
				dsClass = Class.forName(szDataSource);
				Constructor dsConstructor = dsClass.getConstructor(new Class[] { Connection.class, Map.class });
				o = dsConstructor.newInstance(new Object[] { conn, hmParameters });
				jrds = (JRDataSource) o; // new
				// com.priefert.reports.CustomerMonthlyHistory(
				// conn );
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		// note: sometimes you want BOTH the jrds and the REPORT_CONNECTION!
		if (jrds == null) {
			// one more try
			jrds = (JRDataSource) hmParameters.get("REPORT_DATA_SOURCE");
		}
		coerceDataTypes(jasperReport, hmParameters);

		JRBaseFiller filler = JRFiller.createFiller(jasperReport);
		
		// create a new copy of the parameters
		// ...the filler modifies the parameters in unacceptable ways!
		// ...in particular, he can remove the REPORT_CONNECTION and insert
		// ...a subreport data source 
		
		HashMap<Object,Object> xParameters = new HashMap<Object,Object>();
		Iterator ii = hmParameters.keySet().iterator();
		while (ii.hasNext()) {
			String key = (String) ii.next();
			xParameters.put(key, hmParameters.get(key));
		}
		
		if (jrds != null) {
			jasperPrint = filler.fill(xParameters, jrds);
		} else {
			jasperPrint = filler.fill(xParameters, conn);
		}

		String title = null;
		try {
			JRFillDataset mainDataset = filler.getMainDataset();
			title = (String) mainDataset.getVariableValue("PFT_TITLE");
			System.out.println("title=" + title);
		} catch (Exception ex) {
			// variable does not exist is OK;
		}

		Long contactRecnum = null;
		try {
			JRFillDataset mainDataset = filler.getMainDataset();
			contactRecnum = (Long) mainDataset.getVariableValue("PFT_CONTACT");
		} catch (Exception ex) {
			// variable does not exist is OK;
		}
		
		if( owner != null ) {
			owner.putClientProperty("PFT_CONTACT", contactRecnum );
		}
		if( contactRecnum != null ) {
			hmParameters.put("PFT_CONTACT", contactRecnum );
		}
		
		// for( int i=0; i < variables.length ; i++ ) {
		// JRVariable variable = variables[i];
		// if( "PFT_TITLE".equals(variable.getName()) ) {
		// title = variable.get
		if (title != null && owner != null ) {
			owner.putClientProperty("PFT_TITLE", title);
		}
		// }
		// }

		return jasperPrint;
	}

	private static void coerceDataTypes(JasperReport jasperReport, HashMap map) {
		JRParameter[] ar = jasperReport.getParameters();

		for (int idx = 0; idx < ar.length; idx++) {
			JRParameter param = ar[idx];
			String cn = param.getValueClassName();

			String key = param.getName();
			Object value = map.get(key);
			if (value != null) {
				if ("java.lang.String".equals(cn) && !(value instanceof String)) {
					map.put(key, value.toString());
				} else if ("java.lang.Short".equals(cn) && !(value instanceof Short)) {
					Short s = Short.parseShort(value.toString());
					map.put(key, s);
				} else if ("java.lang.Integer".equals(cn) && !(value instanceof Integer)) {
					Integer i = Integer.parseInt(value.toString());
					map.put(key, i);
				} else if ("java.lang.Long".equals(cn) && !(value instanceof Long)) {
					Long l = Long.parseLong(value.toString());
					map.put(key, l);
				}
			}
		}
	}

	/**
	 */
	protected void loadReport(String fileName, boolean isXML) throws JRException {
		System.out.println("loadReport for string: " + fileName);
		if (isXML) {
			jasperPrint = JRPrintXmlLoader.load(fileName);
		} else {
			// if( fileName.endsWith(".jasper")) {
			// fileName = fileName.substring( 0, fileName.length() - 7 );
			// }
			Object o = JRLoader.loadObject(fileName);
			if (o instanceof JasperPrint) {
				jasperPrint = (JasperPrint) o;
			} else {
				jasperPrint = fill(parent, this, (JasperReport) o, hmParameters, enablePrompting);
			}
		}

		type = TYPE_FILE_NAME;
		this.isXML = isXML;
		reportFileName = fileName;
		btnReload.setEnabled(true); // BAD BAD BAD

	}

	/**
	 */
	protected void loadReport(InputStream is, boolean isXML) throws JRException {
		System.out.println("loadReport for stream.");
		if (isXML) {
			jasperPrint = JRPrintXmlLoader.load(is);
		} else {
			jasperPrint = (JasperPrint) JRLoader.loadObject(is);
		}

		type = TYPE_INPUT_STREAM;
		this.isXML = isXML;
	}

	/**
	 */
	protected void loadReport(JasperPrint jrPrint) throws JRException {
		System.out.println("loadReport from printable.");

		jasperPrint = jrPrint;
		type = TYPE_JASPER_PRINT;
		isXML = false;
	}

	protected void refreshPage() {

		System.out.println("REFRESH");

		if (jasperPrint == null || jasperPrint.getPages() == null || jasperPrint.getPages().size() == 0) {
			pnlPage.setVisible(false);
			btnSave.setEnabled(false);
			btnPrint.setEnabled(false);
			btnSend.setEnabled(false);
			btnActualSize.setEnabled(false);
			btnFitPage.setEnabled(false);
			btnFitWidth.setEnabled(false);
			btnZoomIn.setEnabled(false);
			btnZoomOut.setEnabled(false);
			cmbZoom.setEnabled(false);

			if (jasperPrint != null) {
				JOptionPane.showMessageDialog(this, "The document has no pages.");
			}

			return;
		}

		pnlPage.setVisible(true);
		btnSave.setEnabled(true);
		btnPrint.setEnabled(true);
		btnSend.setEnabled(true);
		btnActualSize.setEnabled(true);
		btnFitPage.setEnabled(true);
		btnFitWidth.setEnabled(true);
		btnZoomIn.setEnabled(zoom < MAX_ZOOM);
		btnZoomOut.setEnabled(zoom > MIN_ZOOM);
		cmbZoom.setEnabled(true);

		Image image = null;
		ImageIcon imageIcon = null;

		Dimension dim = new Dimension((int) (jasperPrint.getPageWidth() * zoom) + 8, // 2
				// from
				// border,
				// 5
				// from
				// shadow
				// and
				// 1
				// extra
				// pixel
				// for
				// image
				(int) (jasperPrint.getPageHeight() * zoom) + 8);
		pnlPage.setMaximumSize(dim);
		pnlPage.setMinimumSize(dim);
		pnlPage.setPreferredSize(dim);

		try {
			image = JasperPrintManager.printPageToImage(jasperPrint, pageIndex, zoom);
			imageIcon = new ImageIcon(image);
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(this, "Error displaying report page. See the console for details.");
		}

		pnlLinks.removeAll();
		linksMap = new HashMap();

		java.util.List pages = jasperPrint.getPages();
		JRPrintPage page = (JRPrintPage) pages.get(pageIndex);
		Collection elements = page.getElements();
		if (elements != null && elements.size() > 0) {
			String toolTip = null;
			JPanel link = null;
			JRPrintElement element = null;
			JRPrintHyperlink hyperlink = null;

			int idx = 0;
			for (Iterator it = elements.iterator(); it.hasNext();) {
				lblProgress.setText(Integer.toString(idx++));

				element = (JRPrintElement) it.next();
				if (element instanceof JRPrintHyperlink
						&& ((JRPrintHyperlink) element).getHyperlinkType() != JRHyperlink.HYPERLINK_TYPE_NONE) {
					hyperlink = (JRPrintHyperlink) element;

					link = new JPanel();
					link.setCursor(new Cursor(Cursor.HAND_CURSOR));
					link.setLocation((int) (element.getX() * zoom), (int) (element.getY() * zoom));
					link.setSize((int) (element.getWidth() * zoom), (int) (element.getHeight() * zoom));
					link.setOpaque(false);

					toolTip = null;
					switch (hyperlink.getHyperlinkType()) {
					case JRHyperlink.HYPERLINK_TYPE_REFERENCE: {
						toolTip = hyperlink.getHyperlinkReference();
						break;
					}
					case JRHyperlink.HYPERLINK_TYPE_LOCAL_ANCHOR: {
						if (hyperlink.getHyperlinkAnchor() != null) {
							toolTip = "#" + hyperlink.getHyperlinkAnchor();
						}
						break;
					}
					case JRHyperlink.HYPERLINK_TYPE_LOCAL_PAGE: {
						if (hyperlink.getHyperlinkPage() != null) {
							toolTip = "#page " + hyperlink.getHyperlinkPage();
						}
						break;
					}
					case JRHyperlink.HYPERLINK_TYPE_REMOTE_ANCHOR: {
						toolTip = "";
						if (hyperlink.getHyperlinkReference() != null) {
							toolTip = toolTip + hyperlink.getHyperlinkReference();
						}
						if (hyperlink.getHyperlinkAnchor() != null) {
							toolTip = toolTip + "#" + hyperlink.getHyperlinkAnchor();
						}
						break;
					}
					case JRHyperlink.HYPERLINK_TYPE_REMOTE_PAGE: {
						toolTip = "";
						if (hyperlink.getHyperlinkReference() != null) {
							toolTip = toolTip + hyperlink.getHyperlinkReference();
						}
						if (hyperlink.getHyperlinkPage() != null) {
							toolTip = toolTip + "#page " + hyperlink.getHyperlinkPage();
						}
						break;
					}
					default: {
						break;
					}
					}

					link.setToolTipText(toolTip);
					link.addMouseListener(mouseListener);
					pnlLinks.add(link);
					linksMap.put(link, element);
				}
			}
		}

		lblPage.setIcon(imageIcon);
	}

	/**
	 */
	private void emptyContainer(Container container) {
		Component[] components = container.getComponents();

		if (components != null) {
			for (int i = 0; i < components.length; i++) {
				if (components[i] instanceof Container) {
					emptyContainer((Container) components[i]);
				}
			}
		}

		components = null;
		container.removeAll();
		container = null;
	}

	/**
	 */
	private float getZoomRatio() {
		float newZoom = zoom;

		try {
			newZoom = zoomDecimalFormat.parse(String.valueOf(cmbZoom.getEditor().getItem())).floatValue() / 100f;
		} catch (ParseException e) {
		}

		return newZoom;
	}

	/**
	 */
	protected void setZoomRatio(float newZoom) {
		if (newZoom > 0) {
			cmbZoom.getEditor().setItem(zoomDecimalFormat.format(newZoom * 100) + "%");

			if (zoom != newZoom) {
				zoom = newZoom;

				refreshPage();
				try {
					ConfigurationInfo.putObject("ReportViewer.zoom", zoom);
				} catch (Exception e) {
					// Spit out diagnostics, but don't bother the user
					e.printStackTrace();
				}
			}
		}
	}

	// Variables declaration - do not modify//GEN-BEGIN:variables
	protected javax.swing.JPanel tlbToolBar;

	protected javax.swing.JPanel pnlInScroll;

	private javax.swing.JPanel jPanel4;

	private javax.swing.JPanel pnlPage;

	private javax.swing.JLabel jLabel1;

	protected javax.swing.JPanel pnlStatus;

	private javax.swing.JScrollPane scrollPane;

	private javax.swing.JPanel pnlLinks;

	private javax.swing.JPanel pnlMain;

	protected javax.swing.JButton btnSave;

	protected javax.swing.JToggleButton btnActualSize;

	protected javax.swing.JPanel pnlSep02;

	protected javax.swing.JLabel lblStatus;

	protected javax.swing.JButton btnLast;

	protected javax.swing.JButton btnReload;

	private javax.swing.JPanel jPanel5;

	protected javax.swing.JButton btnPrevious;

	protected javax.swing.JButton btnZoomOut;

	protected javax.swing.JPanel pnlSep03;

	private javax.swing.JLabel lblPage;

	private javax.swing.JPanel jPanel8;

	protected javax.swing.JButton btnZoomIn;

	protected javax.swing.JToggleButton btnFitPage;

	private javax.swing.JPanel jPanel7;

	protected javax.swing.JButton btnNext;

	protected javax.swing.JPanel pnlSep01;

	protected javax.swing.JButton btnFirst;

	private javax.swing.JPanel jPanel6;

	protected javax.swing.JComboBox cmbZoom;

	private javax.swing.JPanel jPanel9;

	protected javax.swing.JToggleButton btnFitWidth;

	protected javax.swing.JButton btnPrint;

	protected javax.swing.JButton btnSend;

	protected javax.swing.JButton btnBreak;

	protected javax.swing.JLabel lblProgress;

	protected javax.swing.JPanel lblSpacer;

	// End of variables declaration//GEN-END:variables

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.dataflex.DFPrintInterface#updateProgress()
	 */
	public void progressUpdate(String szText) {
		lblProgress.setText(szText);
	}

	public void progressComplete() {
		btnReload.setEnabled(true);
	}

}
