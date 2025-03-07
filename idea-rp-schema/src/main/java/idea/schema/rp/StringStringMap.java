package idea.schema.rp;

import java.util.HashMap;

import jakarta.xml.bind.annotation.adapters.XmlJavaTypeAdapter;

@XmlJavaTypeAdapter(StringStringMapAdapter.class)
public class StringStringMap extends HashMap<String, String> {

}
