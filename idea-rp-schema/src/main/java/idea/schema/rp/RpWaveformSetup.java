//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.2.8-b130911.1802 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2019.07.12 at 08:57:32 AM CDT 
//


package idea.schema.rp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for rp-waveformSetup complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="rp-waveformSetup">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="sweepSpeed" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sampleRate" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="rangeMin" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="rangeMax" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="signalGroup" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="signalId" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="waveColor" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="loc" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "rp-waveformSetup", propOrder = {
    "sweepSpeed",
    "sampleRate",
    "rangeMin",
    "rangeMax",
    "signalGroup",
    "signalId",
    "waveColor",
    "loc"
})
public class RpWaveformSetup {

    protected int sweepSpeed;
    protected int sampleRate;
    protected int rangeMin;
    protected int rangeMax;
    @XmlElement(required = true)
    protected String signalGroup;
    @XmlElement(required = true)
    protected String signalId;
    @XmlElement(required = true)
    protected String waveColor;
    @XmlElement(required = true)
    protected String loc;

    /**
     * Gets the value of the sweepSpeed property.
     * 
     */
    public int getSweepSpeed() {
        return sweepSpeed;
    }

    /**
     * Sets the value of the sweepSpeed property.
     * 
     */
    public void setSweepSpeed(int value) {
        this.sweepSpeed = value;
    }

    /**
     * Gets the value of the sampleRate property.
     * 
     */
    public int getSampleRate() {
        return sampleRate;
    }

    /**
     * Sets the value of the sampleRate property.
     * 
     */
    public void setSampleRate(int value) {
        this.sampleRate = value;
    }

    /**
     * Gets the value of the rangeMin property.
     * 
     */
    public int getRangeMin() {
        return rangeMin;
    }

    /**
     * Sets the value of the rangeMin property.
     * 
     */
    public void setRangeMin(int value) {
        this.rangeMin = value;
    }

    /**
     * Gets the value of the rangeMax property.
     * 
     */
    public int getRangeMax() {
        return rangeMax;
    }

    /**
     * Sets the value of the rangeMax property.
     * 
     */
    public void setRangeMax(int value) {
        this.rangeMax = value;
    }

    /**
     * Gets the value of the signalGroup property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSignalGroup() {
        return signalGroup;
    }

    /**
     * Sets the value of the signalGroup property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSignalGroup(String value) {
        this.signalGroup = value;
    }

    /**
     * Gets the value of the signalId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSignalId() {
        return signalId;
    }

    /**
     * Sets the value of the signalId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSignalId(String value) {
        this.signalId = value;
    }

    /**
     * Gets the value of the waveColor property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getWaveColor() {
        return waveColor;
    }

    /**
     * Sets the value of the waveColor property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setWaveColor(String value) {
        this.waveColor = value;
    }

    /**
     * Gets the value of the loc property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getLoc() {
        return loc;
    }

    /**
     * Sets the value of the loc property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setLoc(String value) {
        this.loc = value;
    }

}