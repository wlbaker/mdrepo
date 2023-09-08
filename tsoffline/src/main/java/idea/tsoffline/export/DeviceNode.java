package idea.tsoffline.export;

import lombok.Data;

@Data
public class DeviceNode {
	public DeviceNode(String name) {
		this.name = name;
	}

	private String name;

	@Override
	public String toString() {
		return name;
	}
}
