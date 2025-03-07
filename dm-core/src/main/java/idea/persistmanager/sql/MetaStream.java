package idea.persistmanager.sql;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.NamedQueries;
import jakarta.persistence.NamedQuery;
import jakarta.persistence.Table;

import idea.schema.rp.RpStream;
import lombok.Data;

/**
 * Database metadata reflective of the RpStream
 */
@SuppressWarnings("serial")
@Entity
@NamedQueries({
//@NamedQuery(name = "metaByDevice", query = "from MetaLog t where t.device=:device order by t.seq"),
@NamedQuery(name = "metaByDevice", query = "from MetaStream t where t.dev=:device") // 
})
@Table(name = "AA_METASTREAM")
@Data
public class MetaStream implements java.io.Serializable {

	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long oid;

	@Column
	private long tallyOID;
	@Column(name = "DEV", length = 16, nullable = false)
	private String dev;
	@Column(name = "TABL", length = 16, nullable = false)
	private String table;
	@Column
	private int streamID;

	@Column(length = 32)
	private String name;
	@Column(length = 64)
	private String model;


	public MetaStream() {
	}

	public MetaStream(long tallyOID, String dev, String table, int streamID, RpStream str) {
		this.tallyOID = tallyOID;
		this.dev = dev;
		this.table = table;
		this.streamID = streamID;
		
		this.name = str.getName();
		this.model = str.getModel();
	}

}
