/**
 * @file intellivue_association_release_request.h
 *
 * @brief Declares a class which creates an association release request.
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_RELEASE_REQUEST_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_RELEASE_REQUEST_H_

#include <cstdint>
#include <string>

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueAssociationReleaseRequest
{
 public:
  IntellivueAssociationReleaseRequest();
  virtual ~IntellivueAssociationReleaseRequest();

  /**
   * Create the entire association release request buffer.
   * @return complete association release request buffer.
   */
  static DicesRcPhilipsIntellivueMP70 CreateAssociationReleaseRequest(
    uint8_t* association_release_request_buffer,
    unsigned int size_of_buffer,
    unsigned int* size_of_request);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueAssociationReleaseRequest(const IntellivueAssociationReleaseRequest& src);
  IntellivueAssociationReleaseRequest &operator=(const IntellivueAssociationReleaseRequest& rhs);
};

#endif
