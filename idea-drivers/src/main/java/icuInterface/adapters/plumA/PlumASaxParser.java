package icuInterface.adapters.plumA;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/*
 * Sample data
 * 

<EVT><LEN Category="0"><LgID>10800</LgID><CNTT>03/21/11 05:09:33 Alarms silenced.</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10801</LgID><CNTT>03/21/11 05:09:42 Line: A, Delivery Restarted , Callback: No, Mode: N/A, Therapy: Dose Calculation, Max D.P.:6 PS
I</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10802</LgID><CNTT>03/21/11 05:09:42 Line: A, Delayed Start: 00:00 hr:min, Patient Wt: 110 Kg</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10803</LgID><CNTT>03/21/11 05:09:42 Line: A, Step: 1, Duration: 01:07 hr:min, Dose: 1.500 mcg/kg/hr</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10804</LgID><CNTT>03/21/11 05:09:42 Line: A, Step: 1, Rate: 41.3 mL/hr, VTBI: 45.6 mL</CNTT></LEN></EVT>
<EVT><LEN Category="1"><LgID>10805</LgID><CNTT>03/21/11 05:09:44 N186 Distal Occlusion</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10806</LgID><CNTT>03/21/11 05:09:46 Line: A, Delivery Restarted , Callback: No, Mode: N/A, Therapy: Dose Calculation, Max D.P.:6 PS
I</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10807</LgID><CNTT>03/21/11 05:09:46 Line: A, Delayed Start: 00:00 hr:min, Patient Wt: 110 Kg</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10808</LgID><CNTT>03/21/11 05:09:46 Line: A, Step: 1, Duration: 01:07 hr:min, Dose: 1.500 mcg/kg/hr</CNTT></LEN></EVT>
<EVT><LEN Category="0"><LgID>10809</LgID><CNTT>03/21/11 05:09:46 Line: A, Step: 1, Rate: 41.3 mL/hr, VTBI: 45.6 mL</CNTT></LEN></EVT>
 */
public class PlumASaxParser extends DefaultHandler {

	LinkedList<String> stack = new LinkedList<String>();
	String element;
	
	List<PumpLineEvent> eventList;
	PumpLineEvent levent;
	private String category;

	String cntt;
	
	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {

		element = qName;

		if (qName.equalsIgnoreCase("wrapper")) {
			eventList = new LinkedList<PumpLineEvent>();
		} else if (qName.equalsIgnoreCase("EVT")) {
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("LEN")) {
			stack.push(qName);
			element = null;
			levent = new PumpLineEvent();
			eventList.add( levent );
			category = "??";
			
			int nattrs = attributes.getLength();
			for( int i = 0; i < nattrs; i++ ) {
				String attrName = attributes.getQName(0);
				if( "Category".equals(attrName)) {
					category = attributes.getValue(i);
				} else {
					System.err.println( "unknown attribute: " + attrName );
				}
			}
		} else if (qName.equalsIgnoreCase("LgID")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("CNTT")) {
			cntt = "";
			// valid...ignore
		} else {
			System.out.println("unknown qname: " + qName);
		}
		// }

	}

	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {

		if (qName.equalsIgnoreCase("EVT")) {
			stack.pop();
			element = null;
		} else if (qName.equalsIgnoreCase("LEN")) {
			stack.pop();
			element = null;
		} else if (qName.equalsIgnoreCase("LgID")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("CNTT")) {
			// valid...ignore
		} else {
			System.out.println("plumA end element ignored:" + qName);
		}

	}

	@Override
	public void characters(char ch[], int start, int length) {
		try {
			_characters( ch, start, length );
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void _characters(char ch[], int start, int length)
			throws SAXException, ParseException {

		String path = stack.peek();

		String val = new String(ch, start, length);
		val = val.trim();
		if( val.length() == 0 ) {
			return;
		}
//		System.out.println("chars:" + path + "=" + val );

		if (element == null) {
			// this is ok...just means no data in current element
		} else if ("EVT".equals(path)) {
				System.out.println("unknown evt chars: " + element);
		} else if ("LEN".equals(path)) {
			if ("CNTT".equals(element)) {
				cntt += val;
				if( "0".equals(category)) {
					System.out.println( "cntt0: " + val );
					parseCNTT0( levent, val );
				} else {
					parseCTTN1( levent, val );
				}
			} else if ("LgID".equals(element)) {
				levent.setLgID( Integer.parseInt(val) );
			} else {
				System.out.println("unknown metric element: " + element);
			}
		} else {
			System.out.println("(chars) ignoring element: " + element + " at "
					+ path + " val: " + val);
		}

	}

	private void parseCTTN1(PumpLineEvent levent2, String val) {
		// TODO Auto-generated method stub
		
	}

	private static void parseCNTT0(PumpLineEvent levent, String val) throws ParseException {

		if( val.length() < 18 ) {
			System.err.println("no date? CNTT=" + val );
			return;
		}
		DateFormat dt_fmt = new SimpleDateFormat("MM/dd/yy HH:mm:ss");
		String s_tm = val.substring( 0, 17 );
		val = val.substring(18);
		
		Date dt = dt_fmt.parse(s_tm);
		levent.setTm( dt.getTime() );
		
		String [] ar = val.split(",");
		for( String seg : ar ) {
			seg = seg.trim();
			if( seg.length() == 0 ) {
				continue;  // ignore
			}
			int idx = seg.indexOf( ":" );
			if( idx > 0 ) {
				String func = seg.substring(0,idx);
				String farg = seg.substring(idx+1).trim();
				parse_func( levent, func, farg );
			} else if ("Alarms silenced.".equals(seg)) {
				// hmm
			} else if ("Delivery Restarted".equals(seg)) {
				// hmm
			} else if ("Delivery Started".equals(seg)) {
				// hmm
			} else {
				System.err.println("unknown CNTT segment: " + seg );
			}
		}
	}

	private static void parse_func(PumpLineEvent levent, String func, String farg) {
		if( "Line".equals(func)) {
			System.out.println("got line id: " + farg );
			levent.setLine( farg );
		} else if( "Mode".equals(func)) {
		} else if( "Therapy".equals(func)) {
		} else if( "Rate".equals(func)) {
			String [] s_rate = farg.split(" ");
			System.out.println("got RATE: " + farg );
			assert( s_rate[1].equals("mL/hr") ) : "PLUM-A UNKNOWN RATE UNIT: " + s_rate[1];
			levent.setRate( Double.parseDouble(s_rate[0]) );
		} else if( "VTBI".equals(func)) {
			String [] s_vtbi = farg.split(" ");
			System.out.println("got VTBI: " + farg );
			assert( s_vtbi[1].equals("mL/hr") ) : "PLUM-A UNKNOWN VTBI UNIT: " + s_vtbi[1];
			levent.setVTBI( Double.parseDouble(s_vtbi[0]) );
		} else if( "Step".equals(func)) {
			// arg is "1"
		} else if( "Delayed Start".equals(func)) {
			// arg is 00:00 hr:min
		} else if( "Duration".equals(func)) {
			// arg is 01:07 hr:min
		} else if( "Dose".equals(func)) {
			// arg is 1.500 mcg/kg/hr
		} else if( "Patient Wt".equals(func)) {
			// arg is 110 Kg
		} else if( "Max D.P.".equals(func)) {
			// arg is "6 PSI"
		} else if( "Callback".equals(func)) {
			// arg is No?
		} else if( "Power switched".equals(func)) {
			// arg is AC or Battery
		} else {
			System.out.println("!!! " + func + " arg=" + farg );
		}
	}

}

