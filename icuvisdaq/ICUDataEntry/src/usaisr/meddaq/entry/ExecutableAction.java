package idea.meddaq.entry;

public class ExecutableAction {
	private String name;
	private String cmd;
	private String arg1;
	private String arg2;

	public ExecutableAction( String name, String cmd, String arg1, String arg2 ) {
		this.name = name;
		this.cmd = cmd;
		this.arg1 = arg1;
		this.arg2 = arg2;
	}

	public String getName() {
		return name;
	}

	public String getCmd() {
		return cmd;
	}

	public String getArg1() {
		return arg1;
	}

	public String getArg2() {
		return arg2;
	}
	
}
