package idea.tsoffline;

import java.awt.BasicStroke;
import java.awt.Stroke;

import lombok.Getter;

public class AppConstants {
	@Getter static Stroke defaultSignalStroke = new BasicStroke((float) 0.001, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
	@Getter static Stroke emphasisSignalStroke = new BasicStroke((float) 0.001, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

}
