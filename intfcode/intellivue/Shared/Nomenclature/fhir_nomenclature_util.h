/**
 * file fhir_nomenclature_util.h
 * 
 */
//=============================================================================

#ifndef FHIR_NOMENCLATURE_UTIL_H_
#define FHIR_NOMENCLATURE_UTIL_H_

enum class DiagnosticReportStatus
{
  registered = 0,
  partial,
  preliminary,
  final,
  amended,
  corrected,
  appended,
  cancelled,
  entered_in_error,
  unknown
};

namespace loinccodes
{
    static const std::string kLoincCodeSystem = "http://loinc.org";
    static const std::string kLoincCodeVersion = "2.61";
    static const std::string kSampleType = "66746-9";
    static const std::string kpH = "11558-4";
    static const std::string kpCO2 = "11557-6";
    static const std::string kpO2 = "11556-8";
    static const std::string kHemoglobin = "718-7";
    static const std::string kWBC = "26464-8";
    static const std::string kHematocrit = "20570-8";
    static const std::string kO2saturation = "20564-1";
    static const std::string kPotassium = "2823-3";
    static const std::string kLactate = "32693-4";
    static const std::string kSodium = "2951-2";
    static const std::string kBaseExcess = "11555-0";
    static const std::string kAnionGap = "10466-1";
    static const std::string kAnionGapKPlus = "1863-0";
    static const std::string kChloride = "2075-0";
    static const std::string kCalcium = "17863-2";
    static const std::string kCalciumpHnormalized = "19072-8";
    static const std::string kTemperature = "60834-9";
    static const std::string kGlucose = "2339-0";
    static const std::string kTotalCO2 = "11211-0";
    static const std::string kbloodsugar = "2339-0";
    static const std::string kACT = "3184-9";
    static const std::string ktotalleukocytecount = "26464-8";
    static const std::string kdifferentialleukocytecountN = "26499-4";
    static const std::string kdifferentialleukocytecountL = "26474-7";
    static const std::string kdifferentialleukocytecountM = "26484-6";
    static const std::string kdifferentialleukocytecountB = "26444-0";
    static const std::string kdifferentialleukocytecountE = "26449-9";
    static const std::string kplatelets = "13056-7";
    static const std::string kAPTTTC = "57763-5";
    static const std::string kProthrombinTime = "5902-2";
    static const std::string kProthrombinTimeINR = "34714-6";
    static const std::string kUrea = "3091-6";
    static const std::string kCreatinine = "2160-0";
    static const std::string kMagnesium = "19123-9";
    static const std::string kPCT = "33959-8";
    static const std::string kBilirubinT = "14631-6";
    static const std::string kBilirubinD = "14629-0";
    static const std::string kTotalprotein = "2885-2";
    static const std::string kalbumin = "1751-7";
    static const std::string kGlobulin = "10834-0";
    static const std::string kSerumglutamicoxaloacetictransaminase = "1920-8";
    static const std::string kserumglutamicpyruvictransaminase = "1742-6";
    static const std::string kalkalinephosphatase = "6768-6";
    static const std::string kgammaglutamyltranspeptidase = "2324-2";
    static const std::string kuricacid = "3084-1";
    static const std::string kChemistryStudies = "18719-5";
    static const std::string kBloodBankStudies = "18717-9";
    static const std::string kCytologyStudies = "26438-2";
    static const std::string kHematologyStudies = "18723-7";
    static const std::string kSurgicalPathologyStudies = "26439-0";
    static const std::string kInfection = "28124-6";
    static const std::string kSerologyStudies = "18727-8";
    static const std::string kMicrobiologyStudies = "18725-2";
    static const std::string kLaboratoryStudies = "26436-6";
    static const std::string kClot = "41293-2";
    static const std::string kSampleHemolyzed = "20393-5";
    static const std::string kDataEntryError = "58202-3";
    static const std::string kReasonProcedureNotPerformed = "72112-6";
    static const std::string kIncorrectAction = "74071-2";
}

namespace snomedcodes
{
  static const std::string kSnomedCodeSystem = "http://snomed.info/sct/900000000000207008";
  static const std::string kSnomedCodeVersion = "International 2017 (v1.36.1)";
  static const std::string kAboveReferenceRangeQualifierRange = "281302008";
  static const std::string kBelowReferenceRangeQualifierRange = "281300000";
  static const std::string kWithinReferenceRangeQualifierRange = "281301001";
  static const std::string k24HourUrineSampleSpecimen = "276833005";
  static const std::string kAsciticFluidSampleSpecimen = "309201001";
  static const std::string kBiopsySampleSpecimen = "258415003";
  static const std::string kBloodSpecimenSpecimen = "119297000";
  static const std::string kBloodSpecimenWithEdeticAcidSpecimen = "445295009";
  static const std::string kBodyFluidSampleSpecimen = "309051001";
  static const std::string kBoneMarrowSpecimenSpecimen = "119359002";
  static const std::string kCerebroospinalFluidSampleSpecimen = "258450006";
  static const std::string kDeoxyribonucleicAcidSampleSpecimen = "258566005";
  static const std::string kDrainageFluidSampleSpecimen = "258455001";
  static const std::string kEthylenediamineTetraAcetateSubstance = "69519002";
  static const std::string kPlasmaSpecimenWithEthylenediaminTetraaceticAcidSpecimen = "708049000";
  static const std::string kTissueSpecimenFromEndometriumSpecimen = "128163008";
  static const std::string kSpecimenFromEyeSpecimen = "119399004";
  static const std::string kSpecimenFromGallbladderSpecimen = "449446003";
  static const std::string kSpecimenFromLungObtainedByLobectomySpecimen = "122606006";
  static const std::string kSpecimenFromLungSpecimen = "127458004";
  static const std::string kNasalPolypSampleSpecimen = "309179009";
  static const std::string kSwabFromNasalSinusSpecimen = "472901003";
  static const std::string kOmentumTissueSampleSpecimen = "309495002";
  static const std::string kSpecimenSpecimen = "123038009";
  static const std::string kPapanicolaouSmearSampleSpecimen = "16224251000119106";
  static const std::string kRectalSwabSpecimen = "258528007";
  static const std::string kSerumSpecimenSpecimen = "119364003";
  static const std::string kMeasurementOfAlbuminGradientBetweenSerumSpecimenAndAsciticFluidSpecimenProcedure = "442039000";
  static const std::string kSkinTissueSpecimenSpecimen = "119325001";
  static const std::string kSpecimenFromSmallIntestineSpecimen = "119380008";
  static const std::string kSputumSpecimenSpecimen = "1193340036";
  static const std::string kStoolSpecimenSpecimen = "119339001";
  static const std::string kThroatSwabSpecimen = "258529004";
  static const std::string kKidneyBiopsySampleSpecimen = "309269002";
  static const std::string kSpecimenFromUrinaryBladderSpecimen = "450872001";
  static const std::string kUrineSpecimenSpecimen = "122575003";
}

class FHIRNomenclatureStringUtil
{
public:
  const static std::string DiagnosticReportStatusToString(const DiagnosticReportStatus status)
  {
    std::string str;
    switch(status)
    {
      case DiagnosticReportStatus::registered: str = "registered"; break;
      case DiagnosticReportStatus::partial: str = "partial"; break;
      case DiagnosticReportStatus::preliminary: str = "preliminary"; break;
      case DiagnosticReportStatus::final: str = "final"; break;
      case DiagnosticReportStatus::amended: str = "amended"; break;
      case DiagnosticReportStatus::corrected: str = "corrected"; break;
      case DiagnosticReportStatus::appended: str = "appended"; break;
      case DiagnosticReportStatus::cancelled: str = "cancelled"; break;
      case DiagnosticReportStatus::entered_in_error: str = "entered-in-error"; break;
      case DiagnosticReportStatus::unknown: str = "unknown"; break;
      default: str = "unknown"; break;
    }
    return str;
  }

  void static LoincCodeToString(
          const std::string loinc_code,
          std::string* system,
          std::string* version,
          std::string* component,
          std::string* long_description)
  {
      if (!system) return;
      if (!version) return;
      if (!component) return;
      if (!long_description) return;

      *system = loinccodes::kLoincCodeSystem;
      *version = loinccodes::kLoincCodeVersion;

      if (loinc_code.compare(loinccodes::kSampleType) == 0)
      {
          *component = "Specimen type";
          *long_description = "Specimen type";
      }
      else if (loinc_code.compare(loinccodes::kpH) == 0)
      {
          *component = "pH";
          *long_description = "pH of Blood";
      }
      else if (loinc_code.compare(loinccodes::kpCO2) == 0)
      {
          *component = "Carbon dioxide";
          *long_description = "Carbon dioxide [Partial pressure] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kpO2) == 0)
      {
          *component = "Oxygen";
          *long_description = "Oxygen [Partial pressure] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kHemoglobin) == 0)
      {
          *component = "Hemoglobin";
          *long_description = "Hemoglobin [Mass/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kWBC) == 0)
      {
          *component = "Leukocytes";
          *long_description = "Leukocytes [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kHematocrit) == 0)
      {
          *component = "Hematocrit";
          *long_description = "Hematocrit [Volume Fraction] of Blood";
      }
      else if (loinc_code.compare(loinccodes::kO2saturation) == 0)
      {
          *component = "Oxygen saturation";
          *long_description = "Oxygen saturation in Blood";
      }
      else if (loinc_code.compare(loinccodes::kPotassium) == 0)
      {
          *component = "Potassium";
          *long_description = "Potassium [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kLactate) == 0)
      {
          *component = "Lactate";
          *long_description = "Lactate [Moles/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kSodium) == 0)
      {
          *component = "Sodium";
          *long_description = "Sodium [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kBaseExcess) == 0)
      {
          *component = "Base excess";
          *long_description = "Base excess in Blood by calculation";
      }
      else if (loinc_code.compare(loinccodes::kAnionGap) == 0)
      {
          *component = "Anion gap 3";
          *long_description = "Anion gap 3 in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kAnionGapKPlus) == 0)
      {
          *component = "Anion gap 4";
          *long_description = "Anion gap 4 in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kChloride) == 0)
      {
          *component = "Chloride";
          *long_description = "Chloride [Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kCalcium) == 0)
      {
          *component = "Calcium.ionized";
          *long_description = "Calcium.ionized [Mass/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kCalciumpHnormalized) == 0)
      {
          *component = "Calcium.ionized^^adjusted to pH 7.4";
          *long_description = "Calcium.ionized [Moles/volume] adjusted to pH 7.4 in Blood";
      }
      else if (loinc_code.compare(loinccodes::kTemperature) == 0)
      {
          *component = "Body temperature";
          *long_description = "Blood temperature";
      }
      else if (loinc_code.compare(loinccodes::kGlucose) == 0)
      {
          *component = "Glucose";
          *long_description = "Glucose [Mass/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kTotalCO2) == 0)
      {
          *component = "Carbon dioxide";
          *long_description = "Carbon dioxide";
      }
      else if (loinc_code.compare(loinccodes::kbloodsugar) == 0)
      {
          *component = "Glucose";
          *long_description = "Glucose [Mass/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kACT) == 0)
      {
          *component = "Activated clotting time";
          *long_description = "Activated clotting time (ACT) of Blood by Coagulation assay";
      }
      else if (loinc_code.compare(loinccodes::ktotalleukocytecount) == 0)
      {
          *component = "Leukocytes";
          *long_description = "Leukocytes [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kdifferentialleukocytecountN) == 0)
      {
          *component = "Neutrophils";
          *long_description = "Neutrophils [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kdifferentialleukocytecountL) == 0)
      {
          *component = "Lymphocytes";
          *long_description = "Lymphocytes [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kdifferentialleukocytecountM) == 0)
      {
          *component = "Monocytes";
          *long_description = "Monocytes [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kdifferentialleukocytecountB) == 0)
      {
          *component = "Basophils";
          *long_description = "Basophils [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kdifferentialleukocytecountE) == 0)
      {
          *component = "Eosinophils";
          *long_description = "Eosinophils [#/volume] in Blood";
      }
      else if (loinc_code.compare(loinccodes::kplatelets) == 0)
      {
          *component = "Platelets";
          *long_description = "Platelets [#/volume] in Plasma by Automated count";
      }
      else if (loinc_code.compare(loinccodes::kAPTTTC) == 0)
      {
          *component = "Coagulation surface induced.factor "
                       "substitution^immediately after addition of normal "
                       "plasma/Coagulation surface induced";
          *long_description = "Activated partial thromboplastin time "
                              "(aPTT).factor substitution in Platelet poor plasma by Coagulation "
                              "assay --immediately after addition of normal plasma/pre addition "
                              "of normal plasma";
      }
      else if (loinc_code.compare(loinccodes::kProthrombinTime) == 0)
      {
          *component = "Coagulation tissue factor induced";
          *long_description = "Prothrombin time (PT)";
      }
      else if (loinc_code.compare(loinccodes::kProthrombinTimeINR) == 0)
      {
          *component = "Coagulation tissue factor induced.INR";
          *long_description = "INR in Blood by Coagulation assay";
      }
      else if (loinc_code.compare(loinccodes::kUrea) == 0)
      {
          *component = "Urea";
          *long_description = "Urea [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kCreatinine) == 0)
      {
          *component = "Creatinine";
          *long_description = "Creatinine [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kMagnesium) == 0)
      {
          *component = "Magnesium";
          *long_description = "Magnesium [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kPCT) == 0)
      {
          *component = "Procalcitonin";
          *long_description = "Procalcitonin [Mass/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kBilirubinT) == 0)
      {
          *component = "Bilirubin";
          *long_description = "Bilirubin.total [Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kBilirubinD) == 0)
      {
          *component = "Bilirubin.glucuronidated+Bilirubin.albumin bound";
          *long_description = "Bilirubin.direct [Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kTotalprotein) == 0)
      {
          *component = "Protein";
          *long_description = "Protein [Mass/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kalbumin) == 0)
      {
          *component = "Albumin";
          *long_description = "Albumin [Mass/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kGlobulin) == 0)
      {
          *component = "Globulin";
          *long_description = "Globulin [Mass/volume] in Serum by calculation";
      }
      else if (loinc_code.compare(loinccodes::kSerumglutamicoxaloacetictransaminase) == 0)
      {
          *component = "Aspartate aminotransferase";
          *long_description = "Aspartate aminotransferase [Enzymatic activity/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kserumglutamicpyruvictransaminase) == 0)
      {
          *component = "Alanine aminotransferase";
          *long_description = "Alanine aminotransferase [Enzymatic activity/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kalkalinephosphatase) == 0)
      {
          *component = "Alkaline phosphatase";
          *long_description = "Alkaline phosphatase [Enzymatic activity/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kgammaglutamyltranspeptidase) == 0)
      {
          *component = "Gamma glutamyl transferase";
          *long_description = "Gamma glutamyl transferase [Enzymatic activity/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kuricacid) == 0)
      {
          *component = "Urate";
          *long_description = "Urate [Mass or Moles/volume] in Serum or Plasma";
      }
      else if (loinc_code.compare(loinccodes::kChemistryStudies) == 0)
      {
          *component = "Chemistry studies";
          *long_description = "Chemistry studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kBloodBankStudies) == 0)
      {
          *component = "Blood bank studies";
          *long_description = "Blood bank studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kCytologyStudies) == 0)
      {
          *component = "Cytology studies";
          *long_description = "Cytology studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kHematologyStudies) == 0)
      {
          *component = "Hematology studies";
          *long_description = "Hematology studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kSurgicalPathologyStudies) == 0)
      {
          *component = "Surgical pathology studies";
          *long_description = "Surgical pathology studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kInfection) == 0)
      {
          *component = "Infection";
          *long_description = "Infection [CCC]";
      }
      else if (loinc_code.compare(loinccodes::kSerologyStudies) == 0)
      {
          *component = "Serology studies";
          *long_description = "Serology studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kMicrobiologyStudies) == 0)
      {
          *component = "Microbiology studies";
          *long_description = "Microbiology studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kLaboratoryStudies) == 0)
      {
          *component = "Laboratory studies";
          *long_description = "Laboratory studies (set)";
      }
      else if (loinc_code.compare(loinccodes::kClot) == 0)
      {
          *component = "Clot";
          *long_description = "Clotted specimen";
      }
      else if (loinc_code.compare(loinccodes::kSampleHemolyzed) == 0)
      {
          *component = "Sample hemolyzed";
          *long_description = "Sample hemolyzed [Presence] of Serum or Plasma Qualitative";
      }
      else if (loinc_code.compare(loinccodes::kDataEntryError) == 0)
      {
          *component = "Data entry error";
          *long_description = "Data entry error [MDSv3]";
      }
      else if (loinc_code.compare(loinccodes::kReasonProcedureNotPerformed) == 0)
      {
          *component = "Reason procedure not performed";
          *long_description = "Reason procedure not performed [NEMSIS]";
      }
      else if (loinc_code.compare(loinccodes::kIncorrectAction) == 0)
      {
          *component = "Incorrect action";
          *long_description = "Incorrect action [AHRQ]";
      }
      else
      {
          *system = "";
          *version = "";
          *component = "";
          *long_description = "";
      }
  }

  void static SnomedCodeToString(
          const std::string snomed_code,
          std::string* system,
          std::string* version,
          std::string* component,
          std::string* long_description)
  {
      if (!system) return;
      if (!version) return;
      if (!component) return;
      if (!long_description) return;

      *system = snomedcodes::kSnomedCodeSystem;
      *version = snomedcodes::kSnomedCodeVersion;

      if (snomed_code.compare(snomedcodes::kAboveReferenceRangeQualifierRange) == 0)
      {
          *component = "Above reference range (qualifier range)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBelowReferenceRangeQualifierRange) == 0)
      {
          *component = "Below reference range (qualifier range)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kWithinReferenceRangeQualifierRange) == 0)
      {
          *component = "Within reference range (qualifier range)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::k24HourUrineSampleSpecimen) == 0)
      {
          *component = "24 hour urine sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kAsciticFluidSampleSpecimen) == 0)
      {
          *component = "Ascitic fluid sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBiopsySampleSpecimen) == 0)
      {
          *component = "Biopsy sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBloodSpecimenSpecimen) == 0)
      {
          *component = "Blood specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBloodSpecimenWithEdeticAcidSpecimen) == 0)
      {
          *component = "Blood specimen with edetic acid (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBodyFluidSampleSpecimen) == 0)
      {
          *component = "Body fluid sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kBoneMarrowSpecimenSpecimen) == 0)
      {
          *component = "Bone marrow specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kCerebroospinalFluidSampleSpecimen) == 0)
      {
          *component = "Cerebroospinal fluid sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kDeoxyribonucleicAcidSampleSpecimen) == 0)
      {
          *component = "Deoxyribonucleic acid sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kDrainageFluidSampleSpecimen) == 0)
      {
          *component = "Drainage fluid sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kEthylenediamineTetraAcetateSubstance) == 0)
      {
          *component = "Ethylenediamine tetra-acetate (substance)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kPlasmaSpecimenWithEthylenediaminTetraaceticAcidSpecimen) == 0)
      {
          *component = "Plasma specimen with ethylenediamine tetraacetic acid (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kTissueSpecimenFromEndometriumSpecimen) == 0)
      {
          *component = "Tissue specimen from endometrium (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromEyeSpecimen) == 0)
      {
          *component = "Specimen from eye (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromGallbladderSpecimen) == 0)
      {
          *component = "Specimen from gallbladder (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromLungObtainedByLobectomySpecimen) == 0)
      {
          *component = "Specimen from lung obtained by lobectomy (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromLungSpecimen) == 0)
      {
          *component = "Specimen from lung (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kNasalPolypSampleSpecimen) == 0)
      {
          *component = "Nasal polyp sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSwabFromNasalSinusSpecimen) == 0)
      {
          *component = "Swab from nasal sinus (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kOmentumTissueSampleSpecimen) == 0)
      {
          *component = "Omentum tissue sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenSpecimen) == 0)
      {
          *component = "Specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kPapanicolaouSmearSampleSpecimen) == 0)
      {
          *component = "Papanicolaou smear sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kRectalSwabSpecimen) == 0)
      {
          *component = "Rectal swab (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSerumSpecimenSpecimen) == 0)
      {
          *component = "Serum specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kMeasurementOfAlbuminGradientBetweenSerumSpecimenAndAsciticFluidSpecimenProcedure) == 0)
      {
          *component = "Measurement of albumin gradient between serum specimen and ascitic fluid specimen (procedure)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSkinTissueSpecimenSpecimen) == 0)
      {
          *component = "Skin (tissue) specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromSmallIntestineSpecimen) == 0)
      {
          *component = "Specimen from small intestine (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSputumSpecimenSpecimen) == 0)
      {
          *component = "Sputum specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kStoolSpecimenSpecimen) == 0)
      {
          *component = "Stool specimen (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kThroatSwabSpecimen) == 0)
      {
          *component = "Throat swab (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kKidneyBiopsySampleSpecimen) == 0)
      {
          *component = "Kidney biopsy sample (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kSpecimenFromUrinaryBladderSpecimen) == 0)
      {
          *component = "Specimen from urinary bladder (specimen)";
          *long_description = "";
      }
      else if (snomed_code.compare(snomedcodes::kUrineSpecimenSpecimen) == 0)
      {
          *component = "Urine specimen (specimen)";
          *long_description = "";
      }
      else
      {
          *system = "";
          *version = "";
          *component = "";
          *long_description = "";
      }
  }

private:
  // Disallow use of implicitly generated member functions:
  FHIRNomenclatureStringUtil(const FHIRNomenclatureStringUtil &src);
  FHIRNomenclatureStringUtil &operator=(const FHIRNomenclatureStringUtil &rhs);
  
  FHIRNomenclatureStringUtil(){}
  ~FHIRNomenclatureStringUtil(){}
};

#endif
