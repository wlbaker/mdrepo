package idea.persistmanager.sql;

// Generated Jun 7, 2008 8:07:08 PM by Hibernate Tools 3.2.0.b9

import java.util.Date;

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
@Table(name = "AA_METATALLY")
@Data
public class MetaTally implements java.io.Serializable {

	public MetaTally() {
		// empty constructor for hibernate
	}
	public MetaTally(String category, String subject, Date start_dt, double weight) {
		this.category = category;
		this.subject = subject;
		this.start_dt = start_dt;
		this.weight = weight;
	}
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long oid;

	@Column(length = 16)
	private String category;
	@Column(length = 16, nullable = false)
	private String subject;
	@Column( nullable = false)
	private Date start_dt;
	
	@Column( )
	private Date stop_dt;

	@Column(nullable = false)
	private double weight;
	
	@Column( length = 16 )
	private String disposition;
	
	@Column( columnDefinition="text" )
	private String note;
}
