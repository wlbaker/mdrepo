package idea.model;

import idea.message.StreamID;
import idea.model.dev.SimuSine_Measurement;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "ANNOTAT")
@Data
@EqualsAndHashCode(callSuper=false)
public class Annotation extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(Annotation.class);
	}
	@Override
	public RpMetric [] getMetrics() {
		return metrics;
	}

	public Annotation() {
		this( 0, null );
	}
	
	public Annotation( long time, String message) {
		super( StreamID.ANNOTATION );
		
		setTm( new Date(time) );
		this.setMessage(message);
	}

	@Text(loc = "message", code = "message", length=128)
	private String message;

}
