package idea.tsoffline.model;

import lombok.Data;

@Data
public class DerivedParamsBase {

	private OfflineDevice device;
	private OfflineSignal signal1;
	private OfflineSignal signal2;
}
