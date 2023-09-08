/**
 * @file dd_philips_intellivue_mp70_unit_test.cxx
 *
 * @brief Declares a unit test class for DDPhilipsIntellivueMP70 class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_DD_PHILIPS_INTELLIVUE_MP70_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_DD_PHILIPS_INTELLIVUE_MP70_UNIT_TEST_H_

enum class DicesRcUnitTest;

class DDPhilipsIntellivueMP70UnitTest
{
 public:
  DDPhilipsIntellivueMP70UnitTest();
  ~DDPhilipsIntellivueMP70UnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  DDPhilipsIntellivueMP70UnitTest(const DDPhilipsIntellivueMP70UnitTest &src);
  DDPhilipsIntellivueMP70UnitTest &operator=(const DDPhilipsIntellivueMP70UnitTest &rhs);

  DicesRcUnitTest ParseIniCfgFile();
  DicesRcUnitTest ParseCommandLine();
  DicesRcUnitTest RunDriver();
};

#endif
