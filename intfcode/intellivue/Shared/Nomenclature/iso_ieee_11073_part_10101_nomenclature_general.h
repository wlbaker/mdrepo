/**
 * @file iso_ieee_11073_part_10101_nomenclature_general.h
 * 
 * @brief Defines code blocks and general fields from 11073 part 10101 nomenclature.
 * This header is intended to be shared by software which uses 11073
 * nomenclature.
 * 
 * @see ISO/IEEE 11073-10101:2004(E) HEALTH INFORMATICS —
 * POINT-OF-CARE MEDICAL DEVICE COMMUNICATION
 * 
 * @author Robert England
 * 
 */
//=============================================================================

#ifndef ISO_IEEE_11073_PART_10101_NOMENCLATURE_GENERAL_H_
#define ISO_IEEE_11073_PART_10101_NOMENCLATURE_GENERAL_H_

/**
 * @see ISO/IEEE 11073-10101:2004(E) HEALTH INFORMATICS —
 * POINT-OF-CARE MEDICAL DEVICE COMMUNICATION
 * Section B.1.2-Partition codes
 */

/**
 * CodeBlock Definitions
 */

#define MDC_PART_UNSPEC 0 /* Unspecified */
#define MDC_PART_OBJ 1 /* Object Infrastr. */
#define MDC_PART_SCADA 2 /* SCADA(Physio IDs) */
#define MDC_PART_EVT 3 /* Event */
#define MDC_PART_DIM 4 /* Dimension */
#define MDC_PART_VATTR 5 /* Virtual Attribute */
#define MDC_PART_PGRP 6 /* Parameter Group */
#define MDC_PART_SITES 7 /* [Body] Site */
#define MDC_PART_INFRA 8 /* Infrastructure */
#define MDC_PART_FEF 9 /* File Exchange Format */
#define MDC_PART_EXT_NOM 256 /* Ext. Nomenclature */
#define MDC_PART_PVT 1024 /* Private */

/**
 * Discriminator_Range_ Definitions
 */

/**
 * Sup'y Control and Data Acq'n (SCADA) CodeBlock: 2
 */

/* ECG Lead Discrim Offset: 256 */
#define MDC_DRANGE_ECG_LEAD_START 0
#define MDC_DRANGE_ECG_LEAD_END 16127
/* ECG Patterns Discrim Offset: 8 */
#define MDC_DRANGE_ECG_PATT_START 16448
#define MDC_DRANGE_ECG_PATT_END 17999
/* Pulsatile - Hemo Discrim Offset: 4 */
#define MDC_DRANGE_PULS_HEMO_START 18944
#define MDC_DRANGE_PULS_HEMO_END 19219
/* Pulsatile - Neuro Discrim Offset: 4 */
#define MDC_DRANGE_PULS_NEURO_START 22532
#define MDC_DRANGE_PULS_NEURO_END 22655

#endif
