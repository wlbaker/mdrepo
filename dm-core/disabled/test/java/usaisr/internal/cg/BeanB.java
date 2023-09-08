/*
 * Created on May 15, 2006
 *
 */
package idea.internal.cg;

/**
 *
 * @author  baliuka
 */
public class BeanB implements java.io.Serializable{

    String sampleProperty;
    String name;

  //abstract public void addPropertyChangeListener(PropertyChangeListener listener);
  //abstract public void removePropertyChangeListener(PropertyChangeListener listener);

   public String getSampleProperty(){
      return sampleProperty;
   }

   public void setSampleProperty(String value){
      this.sampleProperty = value;
   }
   
   public String getName() {
       return name;
   }
   
   public void setName( String value ) {
       name = value;
       System.out.println( "set string value: " + value );
   }

   public String toString(){
     return "sampleProperty is " + sampleProperty;
   }

}