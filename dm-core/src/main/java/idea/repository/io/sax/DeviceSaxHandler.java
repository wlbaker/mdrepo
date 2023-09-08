package idea.repository.io.sax;

import java.util.LinkedList;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;


@Slf4j
public class DeviceSaxHandler extends DefaultHandler {

		public RpStudy study;
		LinkedList<String> stack = new LinkedList<String>();
		String element;
		RpHardware hw;
		RpDevice device;
		
		String name;

		@Override
		public void startElement(String uri, String localName, String qName,
				Attributes attributes) throws SAXException {

			element = qName;

			if (qName.equalsIgnoreCase("title")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("name")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("connectionType")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("connectionValue")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("hardware")) {
				study = new RpStudy();
				study.setTitle("--?--");
				hw = new RpHardware();
				study.getHardware().add(hw);
				stack.push(qName);
				element = null;
			} else if (qName.equalsIgnoreCase("device")) {
				device = new RpDevice();
				hw.getDevices().add(device);
				stack.push(qName);
				element = null;
			} else if (qName.equalsIgnoreCase("protocol")) {
				// ignoring
			} else if (qName.equalsIgnoreCase("key")) {
				// ignoring
			} else if (qName.equalsIgnoreCase("param")) {
				// ignoring
				log.warn("ignoreing key/param");
			} else {
				log.warn("unknown qname: " + qName);
			}
			// }

		}

		@Override
		public void endElement(String uri, String localName, String qName)
				throws SAXException {

			if (qName.equalsIgnoreCase("title")) {
				// valid...ignore/"u
			} else if (qName.equalsIgnoreCase("pi")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("name")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("deviceClass")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("connectionType")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("connectionValue")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("protocol")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("rp-repository")) {
				// valid...ignore
			} else if (qName.equalsIgnoreCase("hardware")) {
				stack.pop();
				hw = null;
				element = null;
			} else if (qName.equalsIgnoreCase("device")) {
				stack.pop();
				device = null;
				element = null;
			} else {
				System.out.println("device-sax end element ignored:" + qName);
			}

		}

		@Override
		public void characters(char ch[], int start, int length)
				throws SAXException {

			String path = stack.peek();

			String val = new String(ch, start, length);
			val = val.trim();
			if( val.length() == 0 ) {
				return;
			}

			if (element == null) {
				// this is ok...just means no data in current element
			} else if ("device".equals(path)) {
				if ("name".equals(element)) {
					device.setName(val);
				} else if ("deviceClass".equals(element)) {
					device.setDeviceClass(val);
				} else if ("connectionType".equals(element)) {
					RpConnType typ = null;
					if ("RS_232".equals(val)) {
						typ = RpConnType.RS_232;
					} else if ("Ethernet".equalsIgnoreCase(val)) {
						typ = RpConnType.ETHERNET;
					} else {
						System.out.println("unknown connection type for device: "
								+ val);
					}
					device.setConnectionType(typ);
				} else if ("connectionValue".equals(element)) {
					device.setConnectionValue(val);
				} else if ("protocol".equalsIgnoreCase(element)) {
					// ignoring
				} else {
					System.out.println("unknown device element: " + element);
				}
			} else if ("name".equals(element)) {
				// study.setTitle(val);
				// hw.setName( val );
				name = val;
			} else {
				System.out.println("(chars) ignoring element: " + element + " at "
						+ path + " val: " + val);
			}

		}

		private RpUnit getUnit(RpMetric metric) {
			RpLinearUnit unit = (RpLinearUnit) metric.getUnit();
			if( unit == null ) {
				unit = new RpLinearUnit();
				unit.setM( 1 );
				unit.setB( 0 );
				unit.setUnitName( "<?>");
				metric.setUnit(unit);
			}
			
			return unit;
		}
	}
