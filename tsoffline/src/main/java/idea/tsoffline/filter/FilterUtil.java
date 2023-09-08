package idea.tsoffline.filter;

import java.util.List;

import com.google.gson.Gson;
import com.softhorizons.firj.MovingAverage;

import lombok.extern.slf4j.Slf4j;
import uk.me.berndporr.api.Cascade;
import uk.me.berndporr.api.FilterInterface;
import uk.me.berndporr.iirj.Bessel;
import uk.me.berndporr.iirj.Butterworth;
import uk.me.berndporr.iirj.ChebyshevI;
import uk.me.berndporr.iirj.ChebyshevII;
import idea.ts.TsFilter;
import idea.ts.TsoPrefs;
import idea.tsoffline.AppFrame;

/**
 * This class provides application wide static methods for creating filters from
 * textual descriptions stored in the session or site configuration files.
 * 
 * @author william.l.baker2
 *
 */
@Slf4j
public class FilterUtil {

	private static FilterUtil inst;

	/**
	 * The LocalDesc class is a bucket holder for the JSON description. All valid
	 * JSON terms are fields in this class.
	 * 
	 * @author william.l.baker2
	 *
	 */
	static class LocalDesc {
		String name;
		String type;
		int order;
		double fs;
		double cutoff;
		double center;
		double width;
		double rippleDb;
	}

	/*
	 * Used by R interface
	 */
	public static FilterUtil getInstance() {
		if (inst == null) {
			inst = new FilterUtil();
		}
		return inst;
	}


	public static double mean(double[] sig, int off, int step) {
		double tot = 0.0f;

		int len = sig.length;
		for (int i = off; i < len; i += step) {
			tot += sig[i];
		}

		return (tot * step) / len;
	}

	public static String getSourceFromSpec(String location) {
		System.err.println("FIXME: parse loc=" + location);
		String[] arr = location.split("\\$");
		return arr[0];
	}

	/**
	 * Create a filter from the JSON description created by in 
	 * filterdesigner.DesignPanel.notifyFilterListeners.
	 * 
	 *  @param json the json encoded filter description
	 */
	public static FilterInterface createFilterFromJSON(String json) {
		
		Gson gson = new Gson();
		LocalDesc desc = gson.fromJson(json, LocalDesc.class );
		
		FilterInterface cascade;
		switch( desc.name ) {
		case "Chebyshev I":
			cascade = createChebyshevI( desc );
			break;
		case "Chebyshev II":
			cascade = createChebyshevII( desc );
			break;
		case "Bessel":
			cascade = createBessel( desc );
			break;
		case "Butterworth":
			cascade = createButterworth( desc );
			break;
		case "Equiripple":
			cascade = createEquiripple( desc );
			break;
		case "Elliptic":
			cascade = createElliptic( desc );
			break;
		case "Moving Average":
			cascade = createMovingAverage( desc );
			break;
		default:
			log.error("Unidentified filter: {}", desc.name );
			cascade = null;  // let it throw a null pointer
		}
		cascade.setSample_rate( desc.fs );
		cascade.setName( desc.name );

		return cascade;
	}

	private static Cascade createEquiripple(LocalDesc desc) {
		log.error("TODO: implementation of createEquiripple()"); 
		return null;
	}


	private static Cascade createElliptic(LocalDesc desc) {
		log.error("TODO: implementation of createElliptic()"); 
		return null;
	}


	private static FilterInterface createMovingAverage(LocalDesc desc) {
		MovingAverage ma = new MovingAverage( desc.order );
		return ma;
	}


	private static Cascade createBessel(LocalDesc desc) {
		Bessel bessel = new Bessel();

		switch (desc.type) {
		case "lowpass":
			bessel.lowPass(desc.order, desc.fs, desc.cutoff);
			break;
		case "highpass":
			bessel.highPass(desc.order, desc.fs, desc.cutoff);
			break;
		case "bandpass":
			bessel.bandPass(desc.order, desc.fs, desc.center, desc.width);
			break;
		case "bandstop":
			bessel.bandStop(desc.order, desc.fs, desc.center, desc.width);
			break;
		default:
			log.error("Cannot parse filter type: {}", desc.type);
		}
		return bessel;
	}

	private static Cascade createButterworth(LocalDesc desc) {
		Butterworth butterworth = new Butterworth();

		switch (desc.type) {
		case "lowpass":
			butterworth.lowPass(desc.order, desc.fs, desc.cutoff);
			break;
		case "highpass":
			butterworth.highPass(desc.order, desc.fs, desc.cutoff);
			break;
		case "bandpass":
			butterworth.bandPass(desc.order, desc.fs, desc.center, desc.width);
			break;
		case "bandstop":
			butterworth.bandStop(desc.order, desc.fs, desc.center, desc.width);
			break;
		default:
			log.error("Cannot parse filter type: {}", desc.type);
		}
		return butterworth;
	}

	private static Cascade createChebyshevI(LocalDesc desc) {
		ChebyshevI filter = new ChebyshevI();

		switch (desc.type) {
		case "lowpass":
			filter.lowPass(desc.order, desc.fs, desc.cutoff, desc.rippleDb);
			break;
		case "highpass":
			filter.highPass(desc.order, desc.fs, desc.cutoff, desc.rippleDb);
			break;
		case "bandpass":
			filter.bandPass(desc.order, desc.fs, desc.center, desc.width, desc.rippleDb);
			break;
		case "bandstop":
			filter.bandStop(desc.order, desc.fs, desc.center, desc.width, desc.rippleDb);
			break;
		default:
			log.error("Cannot parse filter type: {}", desc.type);
		}
		return filter;
	}
	
	private static Cascade createChebyshevII(LocalDesc desc) {
		ChebyshevII filter = new ChebyshevII();

		switch (desc.type) {
		case "lowpass":
			filter.lowPass(desc.order, desc.fs, desc.cutoff, desc.rippleDb);
			break;
		case "highpass":
			filter.highPass(desc.order, desc.fs, desc.cutoff, desc.rippleDb);
			break;
		case "bandpass":
			filter.bandPass(desc.order, desc.fs, desc.center, desc.width, desc.rippleDb);
			break;
		case "bandstop":
			filter.bandStop(desc.order, desc.fs, desc.center, desc.width, desc.rippleDb);
			break;
		default:
			log.error("Cannot parse filter type: {}", desc.type);
		}
		return filter;
	}

	public static TsFilter findFilterFromName(String action) {
		TsoPrefs prefs = AppFrame.getInstance().getPrefs();
		List<TsFilter> filters = prefs.getFilters();
		if( filters == null ) {
			return null;
		}
		for( TsFilter filter : filters ) {
			String filterName = filter.getName();
			if( filterName == null ) {
				log.error("Filter has no name: {}", filter );
				 continue;
			}
			if( filterName.equals(action) ) {
				return filter;
			}
		}
		
		return null;
	}

}
