package idea.model;

import lombok.Data;

@Data
public class Triplet {
	public Triplet() {
		
	}
	
	public Triplet(Integer sys, Integer dia, Integer map) {
		P_SYS = sys;
		P_DIA = dia;
		P_MAP = map;
	}
	private Integer P_SYS;
	private Integer P_DIA;
	private Integer P_MAP;
}
