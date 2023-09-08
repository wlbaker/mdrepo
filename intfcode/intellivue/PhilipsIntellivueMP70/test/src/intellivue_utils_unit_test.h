/**
 * @file intellivue_utils_unit_test.h
 *
 * @brief Declares a unit test class for IntellivueUtils class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_UTILS_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_UTILS_UNIT_TEST_H_

enum class DicesRcUnitTest;

class IntellivueUtilsUnitTest
{
 public:
  IntellivueUtilsUnitTest();
  ~IntellivueUtilsUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueUtilsUnitTest(const IntellivueUtilsUnitTest &src);
  IntellivueUtilsUnitTest &operator=(const IntellivueUtilsUnitTest &rhs);

  DicesRcUnitTest IsValidSetResultAttribute();
  DicesRcUnitTest IsValidMDSCreateEventReportAttribute();
  DicesRcUnitTest IsValidAssociationResponseAttribute();
  DicesRcUnitTest IsValidConnectIndicationAttribute();
  DicesRcUnitTest IsValidAttribute();
  DicesRcUnitTest ParseAttribute();
  DicesRcUnitTest DeleteAttribute();
  DicesRcUnitTest Convert16BitUnicodeToAscii();
  DicesRcUnitTest ConvertIntellivueColorToDicesColor();
  DicesRcUnitTest ConvertIntellivueMetricCategoryToDicesMetricCategory();
  DicesRcUnitTest ConvertIntellivueMetricAccessToDicesMetricAccess();
  DicesRcUnitTest ConvertIntellivueAbsoluteTimeToDicesTimespec();
  DicesRcUnitTest ConvertIntellivueRelativeTimeToDicesDuration();
  DicesRcUnitTest ConvertIntellivueNomPartitionToDicesNomPartition();
  DicesRcUnitTest ConvertIntellivueMeasurementStatusToDicesMeasurementStatus();
  DicesRcUnitTest ConvertIntellivueMDSStatusToDicesMDSStatus();
  DicesRcUnitTest ConvertIntellivueProdSpecTypeToDicesProdSpecType();
  DicesRcUnitTest ConvertIntellivueLineFrequencyToDicesLineFrequency();
  DicesRcUnitTest ConvertIntellivueFloatTypeToDicesFloatType();
  DicesRcUnitTest ConvertIntellivuePatDemoStateToDicesPatAdmitState();
  DicesRcUnitTest ConvertIntellivuePatientTypeToDicesPatientType();
  DicesRcUnitTest ConvertIntellivuePatientSexToDicesPatientSex();
  DicesRcUnitTest ConvertIntellivueTextIdToVMOLabelString();
  DicesRcUnitTest ConvertIntellivueTextIdStringToTextId();
  DicesRcUnitTest TranslateIntellivePhysioIdToDicesMetricId();
};

#endif

