package idea.model.dev;

import static idea.driver.infinity.Constants.BED_LABEL_SIZE;
import static idea.driver.infinity.Constants.PATIENT_ID_EXTENDED_SIZE;
import static idea.driver.infinity.Constants.PATIENT_ID_SIZE;
import static idea.driver.infinity.Constants.PATIENT_INITIALS_SIZE;
import static idea.driver.infinity.Constants.PATIENT_NAME_SIZE;
import static idea.driver.infinity.Constants.PHYSICIAN_NAME_SIZE;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import java.util.Date;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;


@Entity
@Table(name = "Intellivue$Demographics")
@Data
public class Intellivue_Demographics extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(Intellivue_Demographics.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public Intellivue_Demographics() {
		this(0);
	}

	public Intellivue_Demographics(long time) {
		super(StreamID.ANNOTATION);

		setTm(new Date(time));
	}

	@Text(loc = "name", code = "name", desc = "Patient Name", length = PATIENT_NAME_SIZE)
	private String name;
	@Text(loc = "initials", code = "initials", desc = "Patient Initials", length = PATIENT_INITIALS_SIZE)
	private String initials;
	@Text(loc = "id", code = "id", desc = "Patient ID", length = PATIENT_ID_SIZE)
	private String id;
	@Text(loc = "physician", code = "physician", desc = "Physician Name", length = PHYSICIAN_NAME_SIZE)
	private String physician;
	@Text(loc = "bed", code = "bed", desc = "Bed Label", length = BED_LABEL_SIZE)
	private String bed;
	@Text(loc = "extid", code = "extid", desc = "Patient ID Extended", length = PATIENT_ID_EXTENDED_SIZE)
	private String extid;

}
