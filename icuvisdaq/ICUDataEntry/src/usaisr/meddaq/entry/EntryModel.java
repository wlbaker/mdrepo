package idea.meddaq.entry;

import java.util.LinkedList;

public class EntryModel {

	public LinkedList<ExecutableAction> exes;
	public LinkedList<EntryTimePoint> timepoints;
	private LinkedList<EntrySheet> sheets;
	
	public EntryModel(LinkedList<EntryTimePoint> timepoints, LinkedList<ExecutableAction> exes, LinkedList<EntrySheet> esheets) {
		this.timepoints = timepoints;
		this.exes = exes;
		this.sheets = esheets;
	}

	public LinkedList<EntrySheet> getSheets() {
		return sheets;
	}

	public LinkedList<EntryTimePoint> getTimepoints() {
		
		return timepoints;
	}

	public ExecutableAction [] getExecutableActions(String name) {

		if( exes == null ) {
			return null;
		}

		LinkedList<ExecutableAction> found = new LinkedList<ExecutableAction>();
		
		for( ExecutableAction exe : exes ) {
			if( name.equals(exe.getName()) ) {
				found.add(exe);
			}
		}
		
		if( found.size() == 0 ) {
			return null;
		}
		
		ExecutableAction [] ar = new ExecutableAction[found.size()];
		return found.toArray( ar );
	}

}
