package idea.tsoffline.vizwiz;

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.StringStringMap;

public class RAnalysisWrapper extends RpAnalysis {

	public RAnalysisWrapper(String name, String f) {
		this.setName( name );
		this.setAnalysisClass( RAnalysisExecutor.class.getCanonicalName() );
		StringStringMap map = this.getParam();
		
		if( map == null ) {
			map = new StringStringMap();
		}
		
		map.put("name", name);
		map.put("script", f);
		this.setParam(map);
	}


}
