package idea.tsoffline.r;

import org.rosuda.REngine.REngine;

import idea.r.RUtil;
import idea.tsoffline.AppUtil;

public class PluginController {

	public static void initPlugin() {
		REngine re = RUtil.getREngine();
		if (re != null) {
			AppUtil.runR( "idea/tsoffline/r/init.r", true);
			AppUtil.runR( "idea/tsoffline/r/B2B-init.r", true);
		}

	}
}
