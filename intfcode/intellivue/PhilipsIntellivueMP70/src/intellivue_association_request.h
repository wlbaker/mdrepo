/**
 * @file intellivue_association_request.h
 *
 * Reads xml file with configuration and creates request message.
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_REQUEST_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_REQUEST_H_

#include <cstdint>
#include <string>

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueAssociationRequest
{
 public:
  friend class IntellivueAssociationRequestUnitTest;

  IntellivueAssociationRequest(const char* filename);
  IntellivueAssociationRequest();
  virtual ~IntellivueAssociationRequest();

  /**
   * Piece together the entire association request buffer
   * based on the information given in the XML configuration file.
   * @return complete association request buffer.
   */
  DicesRcPhilipsIntellivueMP70 CreateAssociationRequest(
    uint8_t* association_request_buffer,
    unsigned int size_of_buffer,
    unsigned int* size_of_request);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueAssociationRequest(const IntellivueAssociationRequest& src);
  IntellivueAssociationRequest &operator=(const IntellivueAssociationRequest& rhs);

  std::string _cfg_filename;
};

#endif
