package idea.datamanager.sql;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

@Data
@AllArgsConstructor
public class SimpleData {

	public SimpleData( int saveme, int ssugar, String nosug) {
		sugar = -ssugar;
		spice = nosug;
	}
	@Getter private int sugar;
	@Getter @Setter private String spice;
	
	
	
}
