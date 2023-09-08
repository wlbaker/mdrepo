package idea.tsoffline;

import com.softhorizons.filterdesigner.GuiUtil;

public class B2BUtil {

	private static double lead_lag = -0.03;
	
	public static HPSplitableLayer getBeatSegmentationLayer() {
		GuiUtil.showMessage("FIXME: This will not work...annos.get(0)? List<HPSplitableLayer> annos = AppModel.getAnnotationModel();");
		// return annos.get(0);
		return null;
	}

	public static double getBeatLeadLag() {
		return lead_lag;
	}
	
	public static void setBeatLeadLag( double d ) {
		lead_lag = d;
	}
}
