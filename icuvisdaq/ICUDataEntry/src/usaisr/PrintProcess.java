package idea;

import java.util.HashMap;

import javax.print.PrintService;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExpression;
import net.sf.jasperreports.engine.JRParameter;
import net.sf.jasperreports.engine.JasperReport;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.StringStringMap;

public class PrintProcess { // implements AnalysisPanelInterface {

	private String fileName;
	PrintService service;
	
	public PrintProcess(RpAnalysis anal) {
		StringStringMap params = anal.getParam();
		fileName = params.get( "report");
		service = ConfigurationInfo.getNamedPrinter( params.get("printer") );
	}

//	@Override
//	public void clear() {
//		// TODO Auto-generated method stub
//		
//	}
//
//
//	@Override
//	public Component getConfigurationComponent(RpStudy study, RpHardware hw, RpAnalysis analysis) {
//		PrintProcessSetupForm form = new PrintProcessSetupForm( null, hw, analysis );
//		return form;
//	}
//
	public void print() throws JRException {
		JasperReport report = PrintUtil.loadReport( fileName );
		HashMap<String,Object> map = new HashMap<String,Object>();
		
		JRParameter[] params = report.getParameters();
		for( JRParameter param : params ) {
			String name = param.getName();
			JRExpression expr = param.getDefaultValueExpression();
			if( expr == null ) {
				System.out.println( "expr is null for: " + param );
			} else {
				System.out.println( " " + name + " --> " + expr.getText() );
				
				valueFromDevice( map, name, expr.getText() );
			}
		}
		
		PrintUtil.print(service, map, report);
	}

	private void valueFromDevice(HashMap<String, Object> map, String name, String val) {
		map.put( name, val );
	}
}
