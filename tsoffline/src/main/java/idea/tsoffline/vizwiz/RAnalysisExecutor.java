package idea.tsoffline.vizwiz;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;

import icuInterface.ConnectionStatus;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.r.RUtil;

@Slf4j
public class RAnalysisExecutor implements StreamProducer, // all analysis classes have to produce an analysis, so they implement StreamProducer 
		StreamConsumer // and most of them also consume data
{

	private String f;

	public RAnalysisExecutor(RpAnalysis anal) {

		StringStringMap map = anal.getParam();
		this.f = map.get("script");
	}

	static String readFile(String path, Charset encoding) throws IOException {
		byte[] encoded = Files.readAllBytes(Paths.get(path));
		return new String(encoded, encoding);
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		try {
			REngine eng = RUtil.getREngine();
			for (RpMetric m : item.getMetrics()) {
				Object v = IntfUtil.getRawValue(item, m);
				if( v instanceof double[] ) {
					eng.assign(m.getLocation(), (double[]) v);
				} else if ( v instanceof String ) {
					eng.assign(m.getLocation(), (String) v);
				} else {
					log.error("Dont know how to handle assignment: {}", m.getLocation() );
				}
			}

			String script = readFile(f, Charset.defaultCharset());
			// String script = "load \"" + f + "\"";
			
			String r_tryable = "try( {" + script + "}, silent=TRUE)";
			r_tryable = r_tryable.replace("\r\n", "\n");
			System.out.println( r_tryable );
			
			REXP ok = eng.parseAndEval(r_tryable);
			explain(ok);

		} catch (Exception e) {
			log.error("Error processing stream event", e);
			throw (new RuntimeException(e));
		}
	}

	private static void explain(REXP ok) throws REXPMismatchException {
		REXP cl = ok.getAttribute("class");
		if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {
			System.err.println("R error: " + ok.asString());
			throw new RuntimeException(ok.asString());
		}
	}

	@Override
	public void addStreamListener(StreamID sid, StreamConsumer l) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeStreamListener(StreamConsumer l) {
		// TODO Auto-generated method stub

	}

	@Override
	public PersistentItem getEvent(StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void requestCapabilities() throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public RpDevice getConfiguration() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void removeAllStreamListeners() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public ConnectionStatus getStatus() {
		// TODO Auto-generated method stub
		return null;
	}

}
