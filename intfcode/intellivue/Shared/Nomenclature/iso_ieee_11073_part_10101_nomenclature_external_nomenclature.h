/**
 * @file iso_ieee_11073_part_10101_nomenclature_external_nomenclature.h
 * 
 * @brief Defines the set of nomenclature from 11073 part 10101. This header
 * includes external nomenclatures. This header is intended to be shared by
 * software which uses 11073 nomenclature.
 * 
 * @see ISO/IEEE 11073-10101:2004(E) HEALTH INFORMATICS —
 * POINT-OF-CARE MEDICAL DEVICE COMMUNICATION
 * 
 * @author Robert England
 * 
 */
//=============================================================================

#ifndef ISO_IEEE_11073_PART_10101_NOMENCLATURE_EXTERNAL_NOMENCLATURE_H_
#define ISO_IEEE_11073_PART_10101_NOMENCLATURE_EXTERNAL_NOMENCLATURE_H_

/**
 * @see ISO/IEEE 11073-10101:2004(E) HEALTH INFORMATICS —
 * POINT-OF-CARE MEDICAL DEVICE COMMUNICATION
 * B.10 External Nomenclature
 */

/**
 * Partition:	EXTnom
 * Description	External Nomenclature
 */
#define MDC_EXT_NOM_SNOMED	1	/*	SNOMED			*/
#define MDC_EXT_NOM_UMLS	64	/*	UMLS			*/
#define MDC_EXT_NOM_MeSH	128	/*	MeSH			*/
#define MDC_EXT_NOM_LOINC	192	/*	LOINC			*/
#define MDC_EXT_NOM_HL7	256	/*	HL7			*/
#define MDC_EXT_NOM_READ	320	/*	READ			*/
#define MDC_EXT_NOM_ICD_9	384	/*	ICD-9-CM			*/
#define MDC_EXT_NOM_ICD_10	385	/*	ICD-10			*/
#define MDC_EXT_NOM_NNN	448	/*	NNN-Code			*/
#define MDC_EXT_NOM_MC	512	/*	MC			*/
#define MDC_EXT_NOM_SCP	576	/*	SCP			*/
#define MDC_EXT_NOM_NIC	640	/*	NIC			*/
#define MDC_EXT_NOM_NOC	704	/*	NOC			*/
#define MDC_EXT_NOM_ICPM	768	/*	ICPM			*/
#define MDC_EXT_NOM_ICPM_GE	832	/*	ICPM-GE			*/
#define MDC_EXT_NOM_VESKA	896	/*	VESKA			*/
#define MDC_EXT_NOM_ASTM_E1394_91	960	/*	ASTM E1394-91			*/
#define MDC_EXT_NOM_ASTM_E1238	1024	/*	ASTM E1238			*/
#define MDC_EXT_NOM_DSM_IIIR	1088	/*	DSM-IIIR			*/
#define MDC_EXT_NOM_DRG	1152	/*	DRG			*/
#define MDC_EXT_NOM_NANDA	1216	/*	NANDA			*/
#define MDC_EXT_NOM_GALEN	1280	/*	GALEN			*/
#define MDC_EXT_NOM_GRAIL	1344	/*	GRAIL			*/
#define MDC_EXT_NOM_ASTM_E1467_94	1408	/*	ASTM E1467-94			*/
#define MDC_EXT_NOM_CPT	1472	/*	CPT			*/
#define MDC_EXT_NOM_OPCS_4	1536	/*	OPCS-4			*/
#define MDC_EXT_NOM_ASTM_E1460_92	1600	/*	ASTM E1460-92			*/

#endif