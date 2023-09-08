/**
 * @file nomenclature_parameter_group_string_util.h
 * 
 * @brief String converter for nomenclature from 11073 part 10101. This header
 * includes parameter groups nomenclature. This header is intended to be
 * shared by software which uses 11073 nomenclature.
 * 
 * @see ISO/IEEE 11073-10101:2004(E) HEALTH INFORMATICS —
 * POINT-OF-CARE MEDICAL DEVICE COMMUNICATION
 * 
 * @author Robert England
 * 
 */
//=============================================================================

#ifndef NOMENCLATURE_PARAMETER_GROUP_STRING_UTIL_H_
#define NOMENCLATURE_PARAMETER_GROUP_STRING_UTIL_H_

#include "iso_ieee_11073_part_10101_nomenclature_parameter_groups.h"

class NomenclatureParameterGroupStringUtil
{
public:
  const static std::string GroupIDToString(const long id)
  {
    std::string str;
    switch(id)
    {
      case MDC_PGRP_HEMO: str = "MDC_PGRP_HEMO"; break;
      case MDC_PGRP_ECG: str = "MDC_PGRP_ECG"; break;
      case MDC_PGRP_RESP: str = "MDC_PGRP_RESP"; break;
      case MDC_PGRP_VENT: str = "MDC_PGRP_VENT"; break;
      case MDC_PGRP_NEURO: str = "MDC_PGRP_NEURO"; break;
      case MDC_PGRP_DRUG: str = "MDC_PGRP_DRUG"; break;
      case MDC_PGRP_FLUID: str = "MDC_PGRP_FLUID"; break;
      case MDC_PGRP_BLOOD_CHEM: str = "MDC_PGRP_BLOOD_CHEM"; break;
      case MDC_PGRP_MISC: str = "MDC_PGRP_MISC"; break;
      default: break;
    }
    return str;
  }

private:
  // Disallow use of implicitly generated member functions:
  NomenclatureParameterGroupStringUtil(const NomenclatureParameterGroupStringUtil &src);
  NomenclatureParameterGroupStringUtil &operator=(const NomenclatureParameterGroupStringUtil &rhs);
  
  NomenclatureParameterGroupStringUtil(){}
  ~NomenclatureParameterGroupStringUtil(){}
};

#endif