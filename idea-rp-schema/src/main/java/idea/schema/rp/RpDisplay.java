//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.2.8-b130911.1802 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2019.07.12 at 08:57:32 AM CDT 
//


package idea.schema.rp;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for rp-display complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="rp-display">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="numBands" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="numPBoxes" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="horizPBoxes" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="vertPBoxes" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="opmode" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="bandData" type="{http://idea.mil/rp}rp-bandData" maxOccurs="unbounded" minOccurs="0"/>
 *         &lt;element name="pboxData" type="{http://idea.mil/rp}rp-pboxData" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "rp-display", propOrder = {
    "numBands",
    "numPBoxes",
    "horizPBoxes",
    "vertPBoxes",
    "opmode",
    "bandData",
    "pboxData"
})
public class RpDisplay {

    protected int numBands;
    protected int numPBoxes;
    protected int horizPBoxes;
    protected int vertPBoxes;
    protected int opmode;
    protected List<RpBandData> bandData;
    protected List<RpPboxData> pboxData;

    /**
     * Gets the value of the numBands property.
     * 
     */
    public int getNumBands() {
        return numBands;
    }

    /**
     * Sets the value of the numBands property.
     * 
     */
    public void setNumBands(int value) {
        this.numBands = value;
    }

    /**
     * Gets the value of the numPBoxes property.
     * 
     */
    public int getNumPBoxes() {
        return numPBoxes;
    }

    /**
     * Sets the value of the numPBoxes property.
     * 
     */
    public void setNumPBoxes(int value) {
        this.numPBoxes = value;
    }

    /**
     * Gets the value of the horizPBoxes property.
     * 
     */
    public int getHorizPBoxes() {
        return horizPBoxes;
    }

    /**
     * Sets the value of the horizPBoxes property.
     * 
     */
    public void setHorizPBoxes(int value) {
        this.horizPBoxes = value;
    }

    /**
     * Gets the value of the vertPBoxes property.
     * 
     */
    public int getVertPBoxes() {
        return vertPBoxes;
    }

    /**
     * Sets the value of the vertPBoxes property.
     * 
     */
    public void setVertPBoxes(int value) {
        this.vertPBoxes = value;
    }

    /**
     * Gets the value of the opmode property.
     * 
     */
    public int getOpmode() {
        return opmode;
    }

    /**
     * Sets the value of the opmode property.
     * 
     */
    public void setOpmode(int value) {
        this.opmode = value;
    }

    /**
     * Gets the value of the bandData property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the bandData property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getBandData().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link RpBandData }
     * 
     * 
     */
    public List<RpBandData> getBandData() {
        if (bandData == null) {
            bandData = new ArrayList<RpBandData>();
        }
        return this.bandData;
    }

    /**
     * Gets the value of the pboxData property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the pboxData property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getPboxData().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link RpPboxData }
     * 
     * 
     */
    public List<RpPboxData> getPboxData() {
        if (pboxData == null) {
            pboxData = new ArrayList<RpPboxData>();
        }
        return this.pboxData;
    }

}