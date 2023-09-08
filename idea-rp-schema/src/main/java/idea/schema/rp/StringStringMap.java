package idea.schema.rp;

import java.util.HashMap;

import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapter;

@XmlJavaTypeAdapter(StringStringMapAdapter.class)
public class StringStringMap extends HashMap<String, String> {

}
