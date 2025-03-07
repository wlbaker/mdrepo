package idea.persistmanager.sql;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

import lombok.Data;

/**
 * Database metadata reflective of the RpMetric
 */
@SuppressWarnings("serial")
@Entity
@Table(name = "AA_METAKV")
@Data
public class MetaKV implements java.io.Serializable {

	public MetaKV() {
		// empty constructor for hibernate
	}
	public MetaKV(long tallyOID, String key, String value) {
		this.tallyOID = tallyOID;
		this.key = key;
		this.value = value;
	}
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long oid;

	@Column(nullable = false)
	private long tallyOID;

	@Column(length = 16, nullable = false)
	private String key;
	@Column(length = 16, nullable = false)
	private String value;

}
