package idea.meddaq;

import java.awt.Component;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JToggleButton;
import javax.swing.text.JTextComponent;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

import idea.GuiUtil;

import com.toedter.calendar.JDateChooser;

public class QuestionAnswerUtils {

	static DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public static Map<String, String> readNamedPairs(File detailFile)
			throws ParserConfigurationException, SAXException, IOException {

		File f = detailFile;

		HashMap<String, String> map = new HashMap<String, String>();

		if (f != null && f.exists()) {

			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

			// Using factory get an instance of document builder
			DocumentBuilder db = dbf.newDocumentBuilder();

			// parse using builder to get DOM representation of the XML file
			Document dom = db.parse(detailFile);

			Element docEle = dom.getDocumentElement();

			NodeList nl = docEle.getChildNodes();
			if (nl != null && nl.getLength() > 0) {
				for (int i = 0; i < nl.getLength(); i++) {
					Object o = nl.item(i);
					if (o instanceof Text) {
						Text tt = (Text) o;
						// map.put( key, value);
					} else if (o instanceof Element) {
						Element el = (Element) o;
						// Node child = el.getFirstChild();
						// if( child != null ) {
						String key = el.getNodeName();
						String textVal = el.getNodeValue(); // TextContent();
						System.err.println("FIXME: in QuestionAnsswer, changed getTextContent() to getNodeValue(), is this right??");
						if (key != null && textVal != null) {
							map.put(key, textVal);
						}
						// }
					} else {
						System.err.println("woah...can't parse this q/a data");
					}
				}
			}
		}

		return map;
	}

	public static void writeNamedPairs(File detailFile, Map<String, String> map)
			throws IOException, ParserConfigurationException {
		// get an instance of factory
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

		// get an instance of builder
		DocumentBuilder db = dbf.newDocumentBuilder();

		// create an instance of DOM
		Document dom = db.newDocument();

		// create the root element
		Element rootEle = dom.createElement("detail");

		for (String key : map.keySet()) {
			String val = map.get(key);
			Node ele = createTextElement(dom, key, val);
			rootEle.appendChild(ele);
		}

		dom.appendChild(rootEle);

		FileOutputStream fout = new FileOutputStream(detailFile);

		// output DOM XML to file
		try {
			Transformer transformer = TransformerFactory.newInstance().newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			DOMSource source = new DOMSource(dom);
			StreamResult console = new StreamResult(fout);
			transformer.transform(source, console);
		} catch (TransformerException e) {
			throw new IOException(e);
		} finally {

			fout.close();
		}
	}

	private static Node createTextElement(Document dom, String key, String val) {

		Element keyEle = dom.createElement(key);
		Text valEle = dom.createTextNode(val);
		keyEle.appendChild(valEle);

		return keyEle;

	}

	public static void populateNamedPairs(JPanel p, Map<String, String> map) {
		for (Component comp : p.getComponents()) {
			try {
				_populateComponent(comp, map);
			} catch (Exception e) {
				GuiUtil.showError("Parsing Questions", e);
			}
		}
	}

	private static void _populateComponent(Component comp, Map<String, String> map) throws ParseException {
		if (comp instanceof JScrollPane) {
			JScrollPane sp = (JScrollPane) comp;
			comp = sp.getViewport().getView();
		}
		String name = comp.getName();

		if (comp instanceof JDateChooser && name != null) {
			// must come before
			// jpanel recursion
			JDateChooser dc = (JDateChooser) comp;
			String value = map.get(name);
			if (value != null && value.length() > 0) {
				Date dt = df.parse(value);
				dc.setDate(dt);
			}
		} else if (comp instanceof JPanel) { // panels might not have a name
			populateNamedPairs((JPanel) comp, map);
		} else if (name == null) {
			// ignore
		} else if (comp instanceof JTextComponent) {
			JTextComponent jt = (JTextComponent) comp;
			String value = map.get(name);
			if (value == null) {
				value = "";
			}
			jt.setText(value);
		} else if (comp instanceof JToggleButton) {
			JToggleButton cb = (JToggleButton) comp;
			String value = map.get(name);
			if (value == null) {
				value = "";
			}
			cb.setSelected(value.equals("1"));
		} else {
			System.err.println("unknown component: " + name + " type=" + comp.getClass());
		}
	}

	public static void getNamedPairs(JPanel p, Map<String, String> map) {

		for (Component comp : p.getComponents()) {
			try {
				_getComponent(comp, map);
			} catch (Exception e) {
				GuiUtil.showError("Parsing Questions", e);
			}
		}

	}

	private static void _getComponent(Component comp, Map<String, String> map) {
		if (comp instanceof JScrollPane) {
			JScrollPane sp = (JScrollPane) comp;
			comp = sp.getViewport().getView();
		}

		String name = comp.getName();

		if (comp instanceof JDateChooser && name != null) {
			// must come first
			// since datechooser is a jpanel
			JDateChooser dc = (JDateChooser) comp;
			Date dt = dc.getDate();
			if (dt != null) {
				String value = df.format(dt);
				map.put(name, value);
			}
		} else if (comp instanceof JPanel) { // panels might not have a name
			getNamedPairs((JPanel) comp, map);
		} else if (name == null) {
			// ignore
		} else if (comp instanceof JTextComponent) {
			JTextComponent jt = (JTextComponent) comp;
			String value = jt.getText();
			map.put(name, value);
		} else if (comp instanceof JToggleButton) {
			JToggleButton cb = (JToggleButton) comp;
			String value = (cb.isSelected()) ? "1" : "0";
			map.put(name, value);
		} else {
			System.err.println("unknown component: " + name + " type=" + comp.getClass());
		}
	}

}
