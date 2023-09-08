package idea.analysis;

import idea.schema.rp.RpDevice;

public class DevWrapper {

	private RpDevice dev;

	public DevWrapper(RpDevice dev) {
		this.dev = dev;
	}

	public RpDevice getDevice() {
		return dev;
	}

	@Override
	public String toString() {
		return "[dev=" + dev.getName() + "]";
	}
}

