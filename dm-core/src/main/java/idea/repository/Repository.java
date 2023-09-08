package idea.repository;

import lombok.Data;

@Data
public class Repository {
	public Repository(String name, String loc) {
		this.name = name;
		this.loc = loc;
	}
	private String name;
	private String loc;
}
