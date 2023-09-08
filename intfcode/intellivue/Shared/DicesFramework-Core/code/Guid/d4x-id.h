/**
 * @file   d4x_id.h
 * @brief  DocBox ID.
 * @author WMS
 *
 * @note What is "d4x"? There are 4 letters between the 'D' and 'x' in "DocBox"
 */
//=============================================================================
#ifndef D4X_ID_H_
#define D4X_ID_H_

#include <cstdint>
#include <common.h>

// Kind of entity (KOE)
// KOE_UNKNOWN is defined in common.h
#define KOE_MANAGER      (0x0001)
#define KOE_SYSTEM_APP   (0x0002)
#define KOE_CLINICAL_APP (0x0003)
#define KOE_DEVICE       (0x0004)
#define KOE_COORDINATOR  (0x0080)
#define KOE_OPERATOR     (0x00c4)
#define KOE_PROVIDER     (0x00c7)
#define KOE_PATIENT      (0x00c8)

class D4X_ID
{
private:
  // DATA

  // NOT IMPLEMENTED
  // Disallow use of implicitly generated member functions.
  D4X_ID();
  D4X_ID(const D4X_ID &src);
  D4X_ID &operator=(const D4X_ID &rhs);

public:
  // CREATORS


  // MANIPULATORS

  /**
   * The D4X ID is defined as an ice::GUID. It must have
   * a unique value for all other instances of the ID within the domain of
   * interest. The ID is divided into four parts:
   *
   *   1. A 6-byte media access control address (MAC address).
   *   2. Timestamp represented as the number of seconds and nanoseconds since
   *      1970-01-01 00:00:00 UTC (known as Unix time, or POSIX time).
   *   3. 2-byte unsigned integer entity kind field specifies the kind of
   *      entity (IDS, numeric measured observed value, PatientIdentification).
   *   4. 2-byte unsigned integer entity key field is used to uniquely
   *      identify multiple instances of the same kind of entity within an
   *      ICE component.
   */
  static void create(const ice::EntityKind entity_kind, const ice::EntityKey entity_key, ice::GUID *guid);
  static bool is_entity_kind(const ice::EntityKind entity_kind, const ice::GUID *guid);

  static const ice::EntityKind *entity_kind(const ice::GUID *guid);

  // ACCESSORS


  // UTILITIES
  static bool compare(ice::GUID *guid1, ice::GUID *guid2);
};

#endif
