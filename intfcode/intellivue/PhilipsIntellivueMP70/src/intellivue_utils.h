/**
 * @file intellivue_utils.h
 *
 * Reference:
 * 	Data Export Interface Programming Guide
 * 	IntelliVue Patient Monitor
 * 	MP70
 *
 * 	Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_UTILS_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_UTILS_H_

#include <cstdint>
#include <cstring>
#include <string>
#include "intellivue.h"
#include "common.h"
#include "metric.h"
#include "mds.h"
#include "patdemo.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueUtils
{
 public:

  static DicesRcPhilipsIntellivueMP70 IsValidSetResultAttribute(
    const intellivue::OIDType attribute_id,
    bool* is_valid);

  static DicesRcPhilipsIntellivueMP70 IsValidMDSCreateEventReportAttribute(
    const intellivue::OIDType attribute_id,
    bool* is_valid);

  static DicesRcPhilipsIntellivueMP70 IsValidAssociationResponseAttribute(
    const intellivue::OIDType attribute_id,
    bool* is_valid);

  static DicesRcPhilipsIntellivueMP70 IsValidConnectIndicationAttribute(
    const intellivue::OIDType attribute_id,
    bool* is_valid);

  static DicesRcPhilipsIntellivueMP70 IsValidAttribute(
    const intellivue::OIDType code,
    const intellivue::OIDType attribute_id,
    bool* is_valid);

  static DicesRcPhilipsIntellivueMP70 ParseAttribute(
    intellivue::AVAType* ava,
    uint8_t* buffer,
    int iindex);

  static DicesRcPhilipsIntellivueMP70 DeleteAttribute(
    intellivue::AVAType* ava);

  static DicesRcPhilipsIntellivueMP70 Convert16BitUnicodeToAscii(
    uint16_t in_16bit,
    uint8_t* out_8bit);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueColorToDicesColor(
    ice::SimpleColor* dices_color,
    const intellivue::SimpleColour intellivue_color);

  static DicesRcPhilipsIntellivueMP70
  ConvertIntellivueMetricCategoryToDicesMetricCategory(
    ice::MetricCategory* dices_category,
    const intellivue::MetricCategory intellivue_category);

  static DicesRcPhilipsIntellivueMP70
  ConvertIntellivueMetricAccessToDicesMetricAccess(
    ice::MetricAccess* dices_access,
    const intellivue::MetricAccess intellivue_access);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueAbsoluteTimeToDicesTimespec(
    ice::Timespec* dices_abs_time,
    const intellivue::AbsoluteTime& intellivue_abs_time);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueRelativeTimeToDicesDuration(
    ice::Duration* dices_rel_time,
    const intellivue::RelativeTime intellivue_rel_time);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueNomPartitionToDicesNomPartition(
    ice::NomPartition* dices_nom_partition,
    const intellivue::NomPartition intellivue_nom_partition);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
    ice::MeasurementStatus* dices_meas_status,
    const intellivue::MeasurementState intellivue_meas_status);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueMDSStatusToDicesMDSStatus(
    ice::MDSStatus* dices_mds_status,
    const intellivue::MDSStatus intellivue_mds_status);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueProdSpecTypeToDicesProdSpecType(
    ice::ProdSpecType* dices_prod_spec_type,
    const uint16_t intellivue_prod_spec_type);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueLineFrequencyToDicesLineFrequency(
    ice::LineFrequency* dices_line_frequency,
    const intellivue::LineFrequency intellivue_line_frequency);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueFloatTypeToDicesFloatType(
    ice::FLOATType* dices_float_type,
    const intellivue::FLOATType intellivue_float_type);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueFloatTypeToDicesFloatType(
    ice::FLOATType* dices_float_type,
    const intellivue::FLOATType intellivue_float_type,
    bool* is_invalid);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivuePatDemoStateToDicesPatAdmitState(
    ice::PatAdmitState* dices_pat_admit_state,
    const intellivue::PatDemoState intellivue_pat_demo_state);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivuePatientTypeToDicesPatientType(
    ice::PatientType* dices_pat_type,
    const intellivue::PatientType intellivue_pat_type);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivuePatientSexToDicesPatientSex(
    ice::PatientSex* dices_pat_sex,
    const intellivue::PatientSex intellivue_pat_sex);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueTextIdToVMOLabelString(
      std::string* dices_vmo_label_string,
      const intellivue::TextId intellivue_textid);

  static DicesRcPhilipsIntellivueMP70 ConvertIntellivueTextIdStringToTextId(
      intellivue::TextId* intellivue_textid,
      const std::string& dices_vmo_label_string);

  static DicesRcPhilipsIntellivueMP70 TranslateIntellivePhysioIdToDicesMetricId(
      const std::string& dices_vmo_label_string,
      const intellivue::OIDType intellivue_physio_id,
      intellivue::OIDType* dices_metric_id);

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueUtils(const IntellivueUtils& src);
  IntellivueUtils &operator=(const IntellivueUtils& rhs);

  IntellivueUtils();
  ~IntellivueUtils();
};


#endif
