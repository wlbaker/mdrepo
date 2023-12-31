//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.2.8-b130911.1802 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2019.07.12 at 08:57:32 AM CDT 
//


package idea.schema.rp;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the idea.schema.rp package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _RpDisplayImpl_QNAME = new QName("http://idea.mil/rp", "rp-display-impl");
    private final static QName _RpStudyImpl_QNAME = new QName("http://idea.mil/rp", "rp-study-impl");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: idea.schema.rp
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link RpStudy }
     * 
     */
    public RpStudy createRpStudy() {
        return new RpStudy();
    }

    /**
     * Create an instance of {@link RpDisplay }
     * 
     */
    public RpDisplay createRpDisplay() {
        return new RpDisplay();
    }

    /**
     * Create an instance of {@link RpPrecisionUnit }
     * 
     */
    public RpPrecisionUnit createRpPrecisionUnit() {
        return new RpPrecisionUnit();
    }

    /**
     * Create an instance of {@link RpLinearUnit }
     * 
     */
    public RpLinearUnit createRpLinearUnit() {
        return new RpLinearUnit();
    }

    /**
     * Create an instance of {@link RpMetric }
     * 
     */
    public RpMetric createRpMetric() {
        return new RpMetric();
    }

    /**
     * Create an instance of {@link RpFile }
     * 
     */
    public RpFile createRpFile() {
        return new RpFile();
    }

    /**
     * Create an instance of {@link RpConnection }
     * 
     */
    public RpConnection createRpConnection() {
        return new RpConnection();
    }

    /**
     * Create an instance of {@link RpDevice }
     * 
     */
    public RpDevice createRpDevice() {
        return new RpDevice();
    }

    /**
     * Create an instance of {@link RpStream }
     * 
     */
    public RpStream createRpStream() {
        return new RpStream();
    }

    /**
     * Create an instance of {@link RpBandData }
     * 
     */
    public RpBandData createRpBandData() {
        return new RpBandData();
    }

    /**
     * Create an instance of {@link RpWaveformSetup }
     * 
     */
    public RpWaveformSetup createRpWaveformSetup() {
        return new RpWaveformSetup();
    }

    /**
     * Create an instance of {@link RpHardware }
     * 
     */
    public RpHardware createRpHardware() {
        return new RpHardware();
    }

    /**
     * Create an instance of {@link RpResource }
     * 
     */
    public RpResource createRpResource() {
        return new RpResource();
    }

    /**
     * Create an instance of {@link RpPboxData }
     * 
     */
    public RpPboxData createRpPboxData() {
        return new RpPboxData();
    }

    /**
     * Create an instance of {@link RpSubject }
     * 
     */
    public RpSubject createRpSubject() {
        return new RpSubject();
    }

    /**
     * Create an instance of {@link RpAnalysis }
     * 
     */
    public RpAnalysis createRpAnalysis() {
        return new RpAnalysis();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link RpDisplay }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://idea.mil/rp", name = "rp-display-impl")
    public JAXBElement<RpDisplay> createRpDisplayImpl(RpDisplay value) {
        return new JAXBElement<RpDisplay>(_RpDisplayImpl_QNAME, RpDisplay.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link RpStudy }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://idea.mil/rp", name = "rp-study-impl")
    public JAXBElement<RpStudy> createRpStudyImpl(RpStudy value) {
        return new JAXBElement<RpStudy>(_RpStudyImpl_QNAME, RpStudy.class, null, value);
    }

}
