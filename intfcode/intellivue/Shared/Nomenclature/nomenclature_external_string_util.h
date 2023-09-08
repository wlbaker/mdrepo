/**
 * @file nomenclature_external_string_util.h
 * 
 * @brief String converter for nomenclature from 11073 part 10101. This header
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

#ifndef NOMENCLATURE_EXTERNAL_STRING_UTIL_H_
#define NOMENCLATURE_EXTERNAL_STRING_UTIL_H_

#include "iso_ieee_11073_part_10101_nomenclature_external_nomenclature.h"

class NomenclatureExternalStringUtil
{
public:
  const static std::string ExternalNomenclatureIDToString(const long id)
  {
    std::string str;
    switch(id)
    {
      case MDC_EXT_NOM_SNOMED: str = "MDC_EXT_NOM_SNOMED"; break;
      case MDC_EXT_NOM_UMLS: str = "MDC_EXT_NOM_UMLS"; break;
      case MDC_EXT_NOM_MeSH: str = "MDC_EXT_NOM_MeSH"; break;
      case MDC_EXT_NOM_LOINC: str = "MDC_EXT_NOM_LOINC"; break;
      case MDC_EXT_NOM_HL7: str = "MDC_EXT_NOM_HL7"; break;
      case MDC_EXT_NOM_READ: str = "MDC_EXT_NOM_READ"; break;
      case MDC_EXT_NOM_ICD_9: str = "MDC_EXT_NOM_ICD_9"; break;
      case MDC_EXT_NOM_ICD_10: str = "MDC_EXT_NOM_ICD_10"; break;
      case MDC_EXT_NOM_NNN: str = "MDC_EXT_NOM_NNN"; break;
      case MDC_EXT_NOM_MC: str = "MDC_EXT_NOM_MC"; break;
      case MDC_EXT_NOM_SCP: str = "MDC_EXT_NOM_SCP"; break;
      case MDC_EXT_NOM_NIC: str = "MDC_EXT_NOM_NIC"; break;
      case MDC_EXT_NOM_NOC: str = "MDC_EXT_NOM_NOC"; break;
      case MDC_EXT_NOM_ICPM: str = "MDC_EXT_NOM_ICPM"; break;
      case MDC_EXT_NOM_ICPM_GE: str = "MDC_EXT_NOM_ICPM_GE"; break;
      case MDC_EXT_NOM_VESKA: str = "MDC_EXT_NOM_VESKA"; break;
      case MDC_EXT_NOM_ASTM_E1394_91: str = "MDC_EXT_NOM_ASTM_E1394_91"; break;
      case MDC_EXT_NOM_ASTM_E1238: str = "MDC_EXT_NOM_ASTM_E1238"; break;
      case MDC_EXT_NOM_DSM_IIIR: str = "MDC_EXT_NOM_DSM_IIIR"; break;
      case MDC_EXT_NOM_DRG: str = "MDC_EXT_NOM_DRG"; break;
      case MDC_EXT_NOM_NANDA: str = "MDC_EXT_NOM_NANDA"; break;
      case MDC_EXT_NOM_GALEN: str = "MDC_EXT_NOM_GALEN"; break;
      case MDC_EXT_NOM_GRAIL: str = "MDC_EXT_NOM_GRAIL"; break;
      case MDC_EXT_NOM_ASTM_E1467_94: str = "MDC_EXT_NOM_ASTM_E1467_94"; break;
      case MDC_EXT_NOM_CPT: str = "MDC_EXT_NOM_CPT"; break;
      case MDC_EXT_NOM_OPCS_4: str = "MDC_EXT_NOM_OPCS_4"; break;
      case MDC_EXT_NOM_ASTM_E1460_92: str = "MDC_EXT_NOM_ASTM_E1460_92"; break;
      default: break;
    }
    return str;
  }

private:
  // Disallow use of implicitly generated member functions:
  NomenclatureExternalStringUtil(const NomenclatureExternalStringUtil &src);
  NomenclatureExternalStringUtil &operator=(const NomenclatureExternalStringUtil &rhs);
  
  NomenclatureExternalStringUtil(){}
  ~NomenclatureExternalStringUtil(){}
};

#endif