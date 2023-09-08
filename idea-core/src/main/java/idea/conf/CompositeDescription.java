package idea.conf;

import java.util.Arrays;

import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@Data
@EqualsAndHashCode(callSuper=true) 
public class CompositeDescription extends RpMetric {

	private RpMetric[] metrics;
	private Class<?> model;

	public CompositeDescription(String location, String code, String name, RpMetric... descs ) {
		setLocation(location);
		setCode(code);
		setName(name);
		setUnit(RpLinearUnit.unit );
		
		this.metrics = descs;
	}

	public int getCount() {
		if( metrics == null ) {
			log.error("no descriptions for composite: {}", this );
		}
		return (metrics == null) ? 1 : metrics.length;
	}

	public void add(RpMetric comp_item) {
		RpMetric [] new_descs;
	
		if( metrics == null ) {
			new_descs = new RpMetric[1];
			new_descs[0] = comp_item;
		} else {
			new_descs = Arrays.copyOf(metrics, metrics.length + 1);
			new_descs[ metrics.length ] = comp_item;
		}
		metrics = new_descs;
	}
	
	@Override
	public String toString() {
		return "Composite: " + super.toString() + " metrics=" + metrics;
	}

}
