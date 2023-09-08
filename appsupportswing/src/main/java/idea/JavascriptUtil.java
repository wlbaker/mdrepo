package idea;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;

import idea.message.StreamID;

public class JavascriptUtil {

	public static ScriptEngine initEngine() {
		ScriptEngineManager manager = new ScriptEngineManager();
		 ScriptEngine engine = manager.getEngineByName("JavaScript");
		
		engine.put("stdout", System.out );
		engine.put("ConnectionEvent", StreamID.CONNECTION);
		engine.put("NumericsEvent", StreamID.CONNECTION);
		engine.put("AlarmEvent", StreamID.ALARM);

		engine.put("study", "study name goes here");
		engine.put("study_dir", "study_dir_goes_here");

		return engine;
	}
}
