package idea.tsoffline.canvas;

import java.io.IOException;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.util.PAffineTransform;

import idea.intf.AbstractStreamProducer;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.HPAnnotationLayer;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.model.DerivedUtil;

@Slf4j
public class PLayerStream extends AbstractStreamProducer implements PiDatastreamImporter {
	private static int model_idx = 1;

	private int me = this.hashCode();

	private List<HPSplitableLayer> layers;
	private PLayer[] layer_par; // current layer segment
	private Iterator<PLayer>[] itts_par; // iterator over the layer
											// segments...may be null
	private Iterator<PNode>[] itts_sub; // iterator over the HPPath elements

	private Class<? extends PersistentItem> modelClass;

	private long start_tm;

	boolean initted = false;

	private int anno_seq;

	PNode m_node[]; // indexed by layer
	int[] m_pos; // indexed by layer

	private long start_millis;

	private int sid_code;
	List<RpMetric> metrics = new LinkedList<RpMetric>();

	/*
	 * Layer times are offset from 0, being starting time of the entire dataset. To
	 * get real-world time, you must add the startTime back to it. This is an
	 * intentional design decision to deal with precision of floating point numbers.
	 */

	public PLayerStream(HPSplitableLayer layer, long start_tm, int sid_code) {
		this.start_tm = start_tm;
		this.sid_code = sid_code;

		layers = new LinkedList<HPSplitableLayer>();
		me = model_idx;
		model_idx += 1;
		this.add( layer );
	}

	private void initDataModel() {
		if (layers.size() == 0) {
			return;
		}

		metrics = new LinkedList<RpMetric>();

		for (HPSplitableLayer layer : layers) {
			RpMetric sig = layer.getMetric();
			RpMetric xmetric = new RpMetric(sig.getLocation(), sig.getCode(), sig.getName(), sig.getUnit(),
					sig.getSubtyp());
			xmetric.setSampleRate(sig.getSampleRate());
			xmetric.setSamplesPerPacket(sig.getSamplesPerPacket());

			xmetric.setter = null; // these must be re-linked anytime you create a new data structure, below
			xmetric.getter = null;
			metrics.add(xmetric);
		}

		try {

			/*
			 * We scale everything according to the layer transform before sending, which
			 * means the data type will change from int[] to double[].
			 */
			for (RpMetric m : metrics) {
				if (m.getSubtyp() == DataTyp.INT_ARR_TYP || m.getSubtyp() == DataTyp.FLOAT_ARR_TYP) {
					m.setSubtyp(DataTyp.DOUBLE_ARR_TYP);
				}
			}
			modelClass = ModelUtil.findCachedModel(metrics);
			if (modelClass == null) {
				String modelName = "idea.model.auto.AutoPLayer" + me;
				modelClass = ModelUtil.createDynamicModel(modelName, metrics);

				log.debug("ME={} Created dynamic modelClass {} for dataset {} count=" + layers.size(), me, modelName,
						layers.get(0).getName());
			}

		} catch (Exception e) {
			log.error("could not creating dynamic model me={}", me, e);
		}

	}

	@Override
	public RpDevice getConfiguration() {
		RpDevice dev = new RpDevice();
		dev.setName(getName());
		// dev.add
		return dev;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PersistentItem next() throws IOException {
		if (layers == null || layers.size() == 0) {
			// no layers == no data, so don't try to create data objects
			return null;
		}

		if (initted == false) {
			initDataModel(); // create data objects
			initted = true;
		}
		log.debug("next for me={} class={} layer count={}", me, modelClass, layers.size());

		PersistentItem item = ModelUtil.getModelFromDataClass(modelClass);
		item.setSource(this);
		item.setStreamID(sid_code); // only using one stream per
									// layerdevice...this must be
									// the one!
		long tm0 = 0;
		long tm1 = 0;
		boolean has_dat = false;

		double min_tm = Double.MAX_VALUE;

		// fill in any missing m_nodes...and find the earliest time
		outer: for (int lidx = 0; lidx < layers.size(); lidx++) {
			PLayer layer = layer_par[lidx];
			if (layer == null) {
				log.warn("Null layer?  Where is my info! {}", lidx);
				continue outer;
			}
			PAffineTransform tran = layer.getTransformReference(false);
			double tx = (tran == null) ? 0 : tran.getTranslateX();

			Iterator<PLayer> it_par = itts_par[lidx];
			Iterator<PNode> it_sub = itts_sub[lidx];

			long millis = 0;
			PNode node = m_node[lidx];
			do { // a loop to handle the initial seek
				if (node == null) {
					if (it_sub.hasNext() == true) {
						// ignore
					} else {
						if (it_par != null && it_par.hasNext()) {
							layer = it_par.next();
							it_sub = layer.getChildrenIterator();

							tran = layer.getTransformReference(false);
							tx = (tran == null) ? 0 : tran.getTranslateX();

							layer_par[lidx] = layer;
							itts_sub[lidx] = it_sub;
						}
						if (it_sub.hasNext() == false) {
							continue outer;
						}
					}

					node = it_sub.next();

				}
				double width = node.getWidth();
				millis = (long) ((node.getX() + tx) * 1000.0 + 0.6); // round up
				millis += 1000; // we don't really know where this node
								// ends...only where it starts
				millis += start_tm;
				if (millis < start_millis) {
					node = null;
				}
			} while (node == null);

			if (node != null) {
				double node_tm = node.getX() + tx;
				min_tm = Math.min(min_tm, node_tm);
				has_dat = true;
			}
			m_node[lidx] = node;
		}

		if (has_dat == false) {
			return null;
		}

		// build a data structure to send
		for (int lidx = 0; lidx < layers.size(); lidx++) {

			PNode node = m_node[lidx];
			if (node == null) {
				continue; // end of the stream
			}
			PLayer layer = (PLayer) node.getParent();
			PAffineTransform tran = layer.getTransformReference(false);
			double tx = (tran == null) ? 0 : tran.getTranslateX();

			double x = m_node[lidx].getX() + tx;
			if (x != min_tm) {
				continue;
			}

			RpMetric xmetric = metrics.get(lidx);

			if (xmetric.getSubtyp() == DataTyp.DOUBLE_ARR_TYP //
					|| xmetric.getSubtyp() == DataTyp.FLOAT_ARR_TYP //
					|| xmetric.getSubtyp() == DataTyp.INT_ARR_TYP //
			) {

				// WARNING here: output is double[] but original data structure
				// could be int[] or float[]

				m_node[lidx] = null; // trigger next read
				double[][] pts = DerivedUtil.getValuesFromNode(tran, node);
				if (pts == null) {
					log.error("Could not get points from node: {}", node);
					continue;
				}

				IntfUtil.setValue(item, xmetric, pts[1]);
			} else if (xmetric.getSubtyp() == DataTyp.STRING_TYP) { // sids ==
				// StreamID.ANNOTATION)
				// {
				String txt = (String) node.getAttribute("txt");
				IntfUtil.setValue(item, xmetric, txt);

				m_node[lidx] = null; // trigger next read
			} else {
				// FIXME: deriving the values from the node for each iteration...not pretty.
				int pos = m_pos[lidx];
				double[][] pts = DerivedUtil.getValuesFromNode(tran, node);
				double[] xx = pts[0];
				double[] yy = pts[1];
				double val = yy[pos];
				x = xx[pos];
				if (xmetric.getSubtyp() == DataTyp.INT_TYP) {
					int ival = xmetric.getUnit().inverse(val);
					IntfUtil.setValue(item, xmetric, ival);
				} else if (xmetric.getSubtyp() == DataTyp.DOUBLE_TYP) {
					double dval = val; // xmetric.getUnit().inverse(val);
					IntfUtil.setValue(item, xmetric, dval);
				} else {
					IntfUtil.setValue(item, xmetric, val); // hope for the best
				}

				pos++;
				if (pos >= xx.length) {
					m_node[lidx] = null; // trigger next read
					m_pos[lidx] = 0;
				} else {
					m_pos[lidx] = pos;
				}
			}

			tm1 = start_tm + (long) (1000.0 * x + 0.6); // round up
			if (tm0 == 0) {
				tm0 = tm1;
				item.setTime(tm0);
			}

			if (tm0 != tm1) {
				// all times should match the first layer...maybe.
				// calibration might throw this off
				log.error("unequal signals timestamps: {} != {} layeridx={} layer name=" + layer.getName(), tm0, tm1,
						lidx);
			}
		}

		return item;
	}

	@Override
	public void rewind() throws IOException {

		anno_seq = 0; // when exporting, keep track of the annotation sequence
						// number
		int count = layers.size();
		layer_par = new PLayer[count];
		itts_par = new Iterator[count];
		itts_sub = new Iterator[count];

		m_node = new PNode[count]; // discard the old pointers and
									// allocate new null ones
		m_pos = new int[count];

		for (int i = 0; i < layers.size(); i++) {
			PLayer layer = layers.get(i);
			Collection nodes = layer.getChildrenReference();
			if (nodes.isEmpty()) {
				continue;
			}
			if (layer instanceof HPPathLayer) {
				itts_par[i] = null;
				layer_par[i] = layer;
			} else if (layer instanceof HPAnnotationLayer) {
				itts_par[i] = null;
				layer_par[i] = layer;
			} else {
				// this handles HPSplitableLayer, which is probably the expected layer type
				itts_par[i] = nodes.iterator();
				layer_par[i] = (PLayer) itts_par[i].next();
			}
			itts_sub[i] = layer_par[i].getChildrenIterator();
		}

		start_millis = 0;
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void seek(long seekTime) throws IOException {
		rewind();

		start_millis = seekTime;
	}

	@Override
	public void connect() throws IOException {
		rewind();
	}

	@Override
	public void disconnect() {
		// TODO Auto-generated method stub

	}

	@Override
	public String getName() {
		return "S" + sid_code + "_" + layers.size();
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {

		// the layer only has one stream...so it must be this one!

		return modelClass;
	}

	@Override
	public StreamID[] getStreams() {

		return new StreamID[] { StreamID.fromCode(sid_code) };
	}

	public void add(HPSplitableLayer layer) {
		log.debug("Adding layer: {} to stream: {}", layer.getName(), me);

		layers.add(layer);
	}

	public Collection getMetrics() {
		return metrics;
	}

}
