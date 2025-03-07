package idea.schema.rp;

import java.util.HashMap;
import java.util.Map;

import jakarta.xml.bind.annotation.adapters.XmlAdapter;

public class StringStringMapAdapter extends XmlAdapter<StringStringMapModeller, HashMap<String, String>> {

    @Override
    public HashMap<String, String> unmarshal(StringStringMapModeller v)
            throws Exception {

        HashMap<String, String> map = new HashMap<String, String>();
        for(StringStringMapModeller.Entry e : v.getEntry())
        {
            map.put(e.getKey(), e.getValue());
        }

        return map;
    }

    @Override
    public StringStringMapModeller marshal(HashMap<String, String> v)
            throws Exception {

        StringStringMapModeller modeller = new StringStringMapModeller();
        for(Map.Entry<String, String> entry : v.entrySet())
        {
            StringStringMapModeller.Entry e = new StringStringMapModeller.Entry();
            e.setKey(entry.getKey());
            e.setValue(entry.getValue());
            modeller.getEntry().add(e);
        }
        return modeller;
    }
}