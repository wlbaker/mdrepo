package idea.discovery;

import java.io.File;

import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.JAXBException;
import jakarta.xml.bind.Unmarshaller;

import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpStudy;

public class Util {
	static JAXBContext jaxbContext;
	static {
		try {
			ObjectFactory factory = ObjectFactory.class.newInstance();
			jaxbContext = JAXBContext.newInstance("idea.schema.rp");

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static RpStudy createStudyFromFile(File f) throws JAXBException {

		RpStudy study = null;
		if (f.canRead()) {
			Unmarshaller marshaller = jaxbContext.createUnmarshaller();

			JAXBElement<RpStudy> env = (JAXBElement<RpStudy>) marshaller.unmarshal(f);
			study = env.getValue();

		}

		return study;

	}


}
