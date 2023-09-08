package idea.jasper;

import java.util.HashMap;

import net.sf.jasperreports.engine.JRParameter;

public interface PrompterInterface {

	void setParameters(JRParameter[] jrparamReport, HashMap hm);

	void getParameters(HashMap hm);
	
}
