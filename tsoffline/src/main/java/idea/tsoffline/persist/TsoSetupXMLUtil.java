package idea.tsoffline.persist;

import java.io.File;
import java.util.List;

import javax.xml.bind.JAXBContext;

import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.Marshaller;
import jakarta.xml.bind.Unmarshaller;

import lombok.extern.slf4j.Slf4j;
import idea.ts.ObjectFactory;
import idea.ts.TsCode;
import idea.ts.TsFilter;
import idea.ts.TsoAttributeType;
import idea.ts.TsoPrefs;

@Slf4j
public class TsoSetupXMLUtil {

	// keys
	static ObjectFactory factory;
	static JAXBContext jaxbContext;
	
	static {
		try {
			factory = ObjectFactory.class.newInstance();
			jaxbContext = JAXBContext.newInstance("idea.ts");

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static TsoPrefs getSetup(File f) throws Exception {
		TsoPrefs setup = null;

		if (f.isDirectory()) {
			f = new File(f, "setup.xml");
		}

		Unmarshaller marshaller = jaxbContext.createUnmarshaller();

		if (f.canRead()) {
			JAXBElement<TsoPrefs> env = (JAXBElement<TsoPrefs>) marshaller.unmarshal(f);
			setup = env.getValue();
		} else {
			log.warn("cannot read setup file: {}", f);
		}
		
		List<TsFilter> filters = setup.getFilters();
		if( filters != null ) {
			for( TsFilter filter : filters ) {
				filter.setGlobal( true );
			}
		}

		return setup;
	}

	public static void saveSetup(File f, TsoPrefs setup ) throws Exception {
		
		File parent = f.getParentFile();
		parent.mkdirs();

		Marshaller marshaller = jaxbContext.createMarshaller();

		marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);

		JAXBElement<TsoPrefs> out = factory.createTsoprefsImpl(setup);

		marshaller.marshal(out, f);
	}

	public static TsoPrefs getDefaultSetup() {
		TsoPrefs setup = new TsoPrefs();
		TsCode code = new TsCode();
		code.setCode("R");
		code.setDescription("R Indicator");
		code.setColor("red");
		
		setup.getCodes().add( code );
		
		TsoAttributeType attrib = new TsoAttributeType();
		attrib.setKey("indicatorColorIndex");
		attrib.setValue("3");
		setup.getAttributes().add( attrib );
		return setup;
	}
}
