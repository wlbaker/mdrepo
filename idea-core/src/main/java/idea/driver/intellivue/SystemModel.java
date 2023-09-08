package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class SystemModel implements Reportable {

	private String manufacturer;
	private String model_number;

	private SystemModel() {
	}

	public static SystemModel parse(ByteBuffer bb) {

		SystemModel model = new SystemModel();

		short len = bb.getShort();
		if (len > 0) {
			byte[] value = new byte[len];
			bb.get(value);
			model.manufacturer = new String(value).trim();
		}

		len = bb.getShort();
		if (len > 0) {
			byte[] value = new byte[len];
			bb.get(value);
			model.model_number = new String(value).trim();
		}

		return model;
	}

	@Override
	public void dump() {
		System.out.println("SystemModel");
		System.out.println("   MFG/MODEL=" + manufacturer + "/" + model_number);
	}

}
