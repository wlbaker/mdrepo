//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.2.8-b130911.1802 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2019.07.22 at 12:50:03 PM CDT 
//


package idea.ts;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tso-prefs complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tso-prefs">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="title" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="analysis" type="{http://idea.mil/ts}ts-analysis" maxOccurs="unbounded" minOccurs="0"/>
 *         &lt;element name="codes" type="{http://idea.mil/ts}ts-code" maxOccurs="unbounded" minOccurs="0"/>
 *         &lt;element name="filters" type="{http://idea.mil/ts}ts-filter" maxOccurs="unbounded" minOccurs="0"/>
 *         &lt;element name="attributes" type="{http://idea.mil/ts}tso-attributeType" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tso-prefs", propOrder = {
    "title",
    "analysis",
    "codes",
    "filters",
    "attributes"
})
public class TsoPrefs {

    @XmlElement(required = true)
    protected String title;
    protected List<TsAnalysis> analysis;
    protected List<TsCode> codes;
    protected List<TsFilter> filters;
    protected List<TsoAttributeType> attributes;

    /**
     * Gets the value of the title property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getTitle() {
        return title;
    }

    /**
     * Sets the value of the title property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setTitle(String value) {
        this.title = value;
    }

    /**
     * Gets the value of the analysis property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the analysis property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getAnalysis().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TsAnalysis }
     * 
     * 
     */
    public List<TsAnalysis> getAnalysis() {
        if (analysis == null) {
            analysis = new ArrayList<TsAnalysis>();
        }
        return this.analysis;
    }

    /**
     * Gets the value of the codes property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the codes property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getCodes().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TsCode }
     * 
     * 
     */
    public List<TsCode> getCodes() {
        if (codes == null) {
            codes = new ArrayList<TsCode>();
        }
        return this.codes;
    }

    /**
     * Gets the value of the filters property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the filters property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getFilters().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TsFilter }
     * 
     * 
     */
    public List<TsFilter> getFilters() {
        if (filters == null) {
            filters = new ArrayList<TsFilter>();
        }
        return this.filters;
    }

    /**
     * Gets the value of the attributes property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the attributes property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getAttributes().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TsoAttributeType }
     * 
     * 
     */
    public List<TsoAttributeType> getAttributes() {
        if (attributes == null) {
            attributes = new ArrayList<TsoAttributeType>();
        }
        return this.attributes;
    }
    
        
        
        
        /**
	 * Gets the value of a single named attribute.
	 * 
	 * @param key 
	 * 
	 * <p>
	 * This accessor method returns a the string value of the named attribute.  The typ field of the attribute is ignored.
	 * 
	 */
	public String getAttribute(String key) {
		if (attributes != null) {

			for (TsoAttributeType attrib : attributes) {
				if (key.equals(attrib.getKey())) {
					return attrib.value;
				}
			}
		}
		return null;
	}

        /**
	 * Sets the value of a single named attribute.
	 * 
	 * <p>
	 * This method sets the string value of the named attribute.  If the attribute is not found
	 * it will be created.  The typ field of the attribute is ignored.
	 * 
	 */
	public void putAttribute(String key, String value) {
		List<TsoAttributeType> attribs = getAttributes();

		for (TsoAttributeType attrib : attribs) {
			if (key.equals(attrib.getKey())) {
				attrib.setValue(value);
				return;
			}
		}

		TsoAttributeType attrib = new TsoAttributeType();
		attrib.setKey(key);
		attrib.setValue(value);
		attribs.add( attrib );
		return;
	}
        
}
