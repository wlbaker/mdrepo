//
// This file was generated by the Eclipse Implementation of JAXB, v4.0.5 
// See https://eclipse-ee4j.github.io/jaxb-ri 
// Any modifications to this file will be lost upon recompilation of the source schema. 
//


package idea.ts;

import jakarta.xml.bind.annotation.XmlAccessType;
import jakarta.xml.bind.annotation.XmlAccessorType;
import jakarta.xml.bind.annotation.XmlElement;
import jakarta.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ts-filter complex type</p>.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.</p>
 * 
 * <pre>{@code
 * <complexType name="ts-filter">
 *   <complexContent>
 *     <restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       <sequence>
 *         <element name="name" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         <element name="description" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         <element name="bidirectional" type="{http://www.w3.org/2001/XMLSchema}boolean" minOccurs="0"/>
 *       </sequence>
 *     </restriction>
 *   </complexContent>
 * </complexType>
 * }</pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ts-filter", propOrder = {
    "name",
    "description",
    "bidirectional"
})
public class TsFilter {

    @XmlElement(required = true)
    protected String name;
    @XmlElement(required = true)
    protected String description;
    protected Boolean bidirectional;

    /**
     * Gets the value of the name property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getName() {
        return name;
    }

    /**
     * Sets the value of the name property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setName(String value) {
        this.name = value;
    }

    /**
     * Gets the value of the description property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getDescription() {
        return description;
    }

    /**
     * Sets the value of the description property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setDescription(String value) {
        this.description = value;
    }

    /**
     * Gets the value of the bidirectional property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isBidirectional() {
        return bidirectional;
    }

    /**
     * Sets the value of the bidirectional property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setBidirectional(Boolean value) {
        this.bidirectional = value;
    }
    
        
        
        
    /**
     * Filters can be either global to the user or local to the session.  Global filters
     * are saved in the user preferences.  Local filters exist only in the session file.
     * Filters in the session file may exist both locally and globally.
     * 
     * This is a transient flag to indicate if this value should be saved as part of the
     * user preferences.
     */
    @jakarta.xml.bind.annotation.XmlTransient
    protected boolean global;
    
    public boolean isGlobal() {
    	return global;
    }
    public void setGlobal( boolean global) {
    	this.global = global;
    }
    

        /**
	 * Convert TsFilter to a meaningful string
	 * 
	 * <p>
	 * This accessor method returns a the string value of the filter that could be used to recreate the filter.  This is the same as the filter description except when the description is null.
	 * 
	 */
	public String toString() {
	
		if( description == null ) {
			return "{}";
		}
		return description;  // should never return null
	}

        
}
