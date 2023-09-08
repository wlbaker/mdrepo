package idea.test;

import idea.model.IntfUtil;
import idea.model.dev.DragerDelta_Measurements;
import idea.model.dev.DragerDelta_MibBIS;
import idea.model.dev.DragerDelta_MibMGM;
import idea.model.dev.DragerDelta_MibSVO2;
import idea.model.dev.DragerDelta_MibVent;
import idea.model.dev.DragerDelta_Sensors;

public class TestComplexStructure {

	public static void main(String[] args) {
		DragerDelta_Measurements measures = new DragerDelta_Measurements();
		DragerDelta_MibBIS mib_bis = new DragerDelta_MibBIS();
		DragerDelta_MibMGM mib_mgm = new DragerDelta_MibMGM();
		DragerDelta_MibSVO2 mib_svo2 = new DragerDelta_MibSVO2();
		DragerDelta_MibVent mib_vent = new DragerDelta_MibVent();
		DragerDelta_Sensors sensors = new DragerDelta_Sensors();
		
		IntfUtil.clear(measures);

		System.out.println("test completed successfully");
	}

}
