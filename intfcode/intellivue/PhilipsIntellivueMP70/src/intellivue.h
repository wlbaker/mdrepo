/**
 * @file intellivue.h
 *
 * Reference:
 *   Data Export Interface Programming Guide
 *   IntelliVue Patient Monitor
 *   MP70
 *
 *   Philips Reorder Part Number: 451261001426
 *
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_H_

#include <cstdint>
#include <cstdint>

namespace intellivue
{
// Invoke ids for commands
#define ALARM_STATIC_INVOKE_ID (6)
#define ALARM_INVOKE_ID (7)
#define NUMERIC_STATIC_INVOKE_ID (8)
#define NUMERIC_DYNAMIC_INVOKE_ID (9)
#define NUMERIC_ALL_GROUPS_INVOKE_ID (5)
#define WAVEFORM_STATIC_INVOKE_ID (10)
#define WAVEFORM_DYNAMIC_INVOKE_ID (11)
#define WAVEFORM_ALL_GROUPS_INVOKE_ID (1)

#pragma pack(push, 1) // set alignment to 1 byte boundary

typedef struct
{
  int id;
  uint8_t* ps;
} dbx_attrib;

typedef struct
{
  uint8_t value[6];
} MACAddress;

typedef struct
{
  uint8_t value[4];
} IPAddress;

/**
 * The IP Address Information attribute identifies the network interface of
 * the IntelliVue monitor.
 */
typedef struct
{
  MACAddress mac_address;
  IPAddress ip_address;
  IPAddress subnet_mask;
} IpAddressInfo;

/**
 * Absolute Time
 * The Absolute Time data type is used whenever data is time stamped and a
 * resolution of 1s is sufficient.
 */
typedef struct
{
  uint8_t century;
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t sec_fractions;
} AbsoluteTime;

/**
 * The individual fields are BCD encoded, they are not encoded as regular
 * integer values. E.g. the year 99 (decimal) is coded as 0x99.
 * Note that the time resolution in IntelliVue monitor with this format is ONE
 * second. The sec_fractions element in the structure is not used.
 */

/**
 * Relative Time
 * The Relative Time is a high resolution time marker which defines a time
 * relative to an event (e.g. power-on). It is used to position events (a
 * particular event message) relative to each other with a higher resolution.
 * It is defined as follows:
 */
typedef uint32_t RelativeTime;

/**
 * The resolution of the RelativeTime is 1/8ms (125us). The IntelliVue monitor
 * sets the Relative Time with a precision of 2 ms. The Computer Client can
 * calculate the absolute time (wall clock) from a known relation between
 * Absolute Time and Relative Time with a precision of about 1s. For more
 * information on the time mapping refer to MDS CREATE EVENT on page 44.
 */

/**
 * OID Type
 * For the identification of all protocol elements (e.g. physiological meaning,
 * alert codes, units of measure), the OIDType (Object Identifier Type) is used
 */
typedef uint16_t OIDType;

/**
 * Values for the OIDType (the nomenclature) are listed at the end of the
 * section Attribute Data Types and Constants Used on page 65. Independent
 * value ranges (partitions) exist, e.g. for physiological identifiers, alert
 * condition identifiers, units of measurement etc.
 */

/**
 * Private OID
 * To identify private or manufacturer specific elements, use a special type:
 * Values for the PrivateOIDs are listed whenever a PrivateOID is used. Refer
 * to the section Attribute Data Types and Constants Used on page 65 for a
 * complete list of identifiers.
 */

typedef uint16_t PrivateOID;


/**
 * TYPE
 * Whenever it is not clear from the context from which nomenclature value
 * range the OIDType comes, the TYPE data type is used. Here, the nomenclature
 * value range (the partition) is explicitly identified.
 */
typedef uint16_t NomPartition;

typedef struct
{
  NomPartition partition;
  OIDType code;
} TYPE;

/**
 * The code values are grouped in the following partitions:
 * NOM_PART_OBJ: Object oriented element, device nomenclature
 * NOM_PART_SCADA: Types of measurement and place of the measurement
 * NOM_PART_EVT: Codes for alerts
 * NOM_PART_DIM: Units of measurement
 * NOM_PART_PGRP: Identification of parameter groups
 * NOM_PART_INFRASTRUCT: Infrastructure for Data Export applications
 *
 * The code is only unique in a given partition. The values for the OIDType are
 * defined in the section Attribute Data Types and Constants Used on page 65.
 */

/**
 * Handle
 * Object instances, e.g. Numeric object instances, are identified with a 16bit
 * ID, the object Handle:
 */
typedef uint16_t Handle;

/**
 * Global Handle
 * Handles are unique within the context of a particular system. The Protocol
 * supports multiple measurement servers, where each measurement server assigns
 * object handles independently. To assure handle uniqueness across system
 * boundaries, the Global Handle contains an additional identifier for the
 * source system, e.g., each measurement server has a distinct context id. The
 * context id is assigned dynamically when a measurement server is connected.
 */
typedef uint16_t MdsContext;

typedef struct
{
  MdsContext context_id;
  Handle handle;
} GlbHandle;

/**
 * Managed Object Identifier
 * The Managed Object Identifier is a fully qualified object identifier which
 * contains an identifier for the object class (e.g. Numeric object) together
 * with a Global Handle.
 */
typedef struct
{
  OIDType m_obj_class;
  GlbHandle m_obj_inst;
} ManagedObjectId;

/**
 * Attribute Value Assertion
 * Object attributes are represented in the form of data record structures
 * which contain an identifier for the attribute, a length field for parsing
 * and the actual value of the attribute. The structure of such an attribute
 * record is the Attribute Value Assertion, which is defined as follows:
 */
typedef struct
{
  OIDType attribute_id;
  uint16_t length;
  uint8_t* attribute_val;
} AVAType;
/**
 * The attribute_id identifies the type of the attribute. The length field
 * contains the size of the attribute_val field in bytes. The attribute_val
 * field itself is only a placeholder in this structure. The parsing algorithm
 * must assign the attribute value to the correct data structure based on the
 * value of the attribute_id.
 */

/**
 * Attribute List
 * Typically, object instances have multiple attributes which are captured in a
 * list with the following data type:
 */
typedef struct
{
  uint16_t count;
  uint16_t length;
  AVAType* value;
} AttributeList;

/**
 * The count field contains the number of Attribute Value Assertion elements in
 * the list. The length field contains the size of the list (the value array)
 * in bytes. The value field itself again is only a placeholder data structure.
 * A parser must be used to interpret the data structure. Refer to Protocol
 * Examples on page 215 for an example of an AttributeList.
 */

typedef uint32_t Nomenclature;
typedef uint16_t CMDType;

/**
 * Variable Label
 * The string is preceded by a length field, followed by the value. If the
 * length is zero, no octets are appended. The VariableLabel data type uses 8
 * bit ASCII encoding for the text. The length of a VariableLabel is always
 * even.
 */
typedef struct
{
  uint16_t length;
  uint8_t* value;
} VariableLabel;


/**
 * TextId
 * The TextId type is a 32-bit private ID.
 */
typedef uint32_t TextId;

typedef struct
{
  uint16_t count;
  uint16_t length;
  TextId* value;
} TextIdList;

/**
 * Session/Presentation Header
 * Each protocol message starts with a common data structure representing the
 * session and presentation protocol, defined as follows:
 */
typedef struct
{
  uint16_t session_id; /// contains a fixed value 0xE100
  uint16_t p_context_id; /// negotiated in association phase
} SPpdu;

/**
 * session_id
 * This field identifies a Protocol message. The field contains a fixed value
 * 0xE100. Conceptually, this field represents the session header.
 *
 * p_context_id
 * The presentation context identifier is negotiated during the exchange of the
 * association messages.
 *
 * The Computer Client can use the first byte of the session_id to distinguish
 * between Data Export protocol commands and Association Control protocol
 * commands.
 *
 * If a Computer Client encodes the Association Control protocol commands as
 * suggested in Definition of the Association Control Protocol on page 55, the
 * context_id for the Data Export protocol commands is 2.
 */

/**
 * Remote Operation Header
 * A protocol message is considered a remote operation. There are different
 * types of operations as defined below. The different operations are
 * described by a common operation header data structure:
 */
typedef struct
{
  uint16_t ro_type; /// ID for operation
#define ROIV_APDU (1)
#define RORS_APDU (2)
#define ROER_APDU (3)
#define ROLRS_APDU (5)
  uint16_t length; /// bytes to follow
} ROapdus;

/**
 * ro_type
 * This field defines which type of remote operation is appended.
 * The following remote operation types exist:
 * -- Remote Operation Invoke (ROIV_APDU) invokes (calls) a remote operation.
 * -- Remote Operation Result (RORS_APDU) returns the result of a remote
 * operation
 * -- Remote Operation Error (ROER_APDU) returns an error for a remote
 * operation.
 * -- Remote Operation Linked Result (ROLRS_APDU) returns parts of the result
 * of a remote operation. It is used when the size of the complete result
 * exceeds the maximum size of one message.
 *
 * length
 * This field defines the remaining number of bytes in the message.
 */


///	Remote Operation Invoke

typedef struct
{
  uint16_t invoke_id; /// identifies the transaction
  CMDType command_type; /// identifies type of command
  uint16_t length; /// no. of bytes in rest of message
} ROIVapdu;


///	A Remote Operation Result message is a response to an Operation Invoke
///	message requiring confirmation.

typedef struct
{
  uint16_t invoke_id; /// identifies the transaction
  CMDType command_type; /// identifies type of command
  uint16_t length; /// no. of bytes in rest of message
} RORSapdu;

/**
 * invoke_id
 * The invoke identifier is used to reference the specific operation while it
 * is being processed. Result messages or error messages will use this
 * identifier as a reference. Therefore, the invoke identifier should be unique
 * while the operation transaction is in process.
 *
 * command_type
 * The command type identifier defines what command data type is appended to
 * this structure.
 *
 * length
 * This field defines the remaining number of bytes in the message.
 */

/**
 * Event Report
 * The Event Report command (CMD_EVENT_REPORT) is used for unsolicited messages
 * from the sending device to the receiving device. It is appended to the
 * Remote Operation Invoke message. In the Protocol the Event Report may
 * require a response from the receiver (if a response is required, the
 * CMD_CONFIRMED_EVENT_REPORT Command identifier is used).
 *
 * 	The Event Report message uses the following data structure:
 */
typedef struct
{
  ManagedObjectId managed_object; /// ident. of sender
  RelativeTime event_time; /// event time stamp
  OIDType event_type; /// identification of event
  uint16_t length; /// size of appended data
} EventReportArgument;
/**
 * managed_object
 * Identifies the object that generates the unsolicited Event Report command.
 *
 * event_time
 * The relative time (in 1/8ms time ticks) of the event.
 *
 * event_type
 * Identifies the event type and thus the data structure that is appended.
 *
 * length
 * Defines the remaining number of bytes in the message (which is the size of
 * the event specific data appended to this data structure).
 *
 * Event-specific data is appended to the data type.
 */

typedef AttributeList ConnectIndInfo;

/**
 * Attribute Data Types, Constants
 *
 * Attribute:	Production Specification
 * IntelliVue monitor serial number uses 10 characters, part number uses 14
 * characters and revision strings use 8 characters. The strings are NOT
 * null-terminated.
 *
 * The supported components are:
 *
 * Component ID: ID_COMP_PRODUCT
 * Description: Overall product specification
 * Component ID: ID_COMP_CONFIG
 * Description: Specific system configuration
 * Component ID: ID_COMP_BOOT
 * Description: Boot code specification
 * Component ID: ID_COMP_MAIN_BD
 * Description: Mainboard hardware specification
 * Component ID: ID_COMP_APPL_SW
 * Description: Application software specification
 */
#define MAXCHARS_SERIAL_NUMBER (10)
#define MAXCHARS_PART_NUMBER (14)
#define MAXCHARS_REVISION_STRING (8)

typedef struct
{
  uint16_t spec_type;
#define UNSPECIFIED (0)
#define SERIAL_NUMBER (1)
#define PART_NUMBER (2)
#define HW_REVISION (3)
#define SW_REVISION (4)
#define FW_REVISION (5)
#define PROTOCOL_REVISION (6)
  PrivateOID component_id;
  VariableLabel prod_spec;
} ProdSpecEntry;

typedef struct
{
  uint16_t count;
  uint16_t length;
  ProdSpecEntry* value;
} ProductionSpec;

/**
 * Attribute: System Model
 * The System Model attribute contains a manufacturer ID and a
 * manufacturer-specific model number for the device.
 * Attribute ID: NOM_ATTR_ID_MODEL
 * Attribute Type: SystemModel
 * Attribute Groups: System Identification Attribute Group
 * Availability: Mandatory
 */
typedef struct
{
  VariableLabel manufacturer;
  VariableLabel model_number;
} SystemModel;

/**
 * The manufacturer field has variable length, hence the offset of model_number
 * depends on the length of manufacturer. Currently, the IntelliVue uses 4
 * characters for the manufacturer and 6 characters for the model_number
 * (including the terminating �\0�).
 */

/**
 * Attribute:	System Localization
 * The System Localization attribute contains information about the language
 * version used by the device.
 * Attribute ID: NOM_ATTR_LOCALIZN
 * Attribute Type: SystemLocal
 * Attribute Groups: System Identification Attribute Group
 * Availability: Optional
 */
typedef uint16_t Language;
typedef uint16_t StringFormat;

typedef struct
{
  uint32_t text_catalog_revision;
  Language language;
  StringFormat format;
} SystemLocal;

/**
 * The text_catalog_revision contains revision information about the texts used
 * by the monitor. The two most significant bytes contain the version of the
 * text catalog (one byte major, one byte minor revision). The text catalog
 * defines the possible values for Attributes of the type TextId. A client
 * which depends on a TextId having a specific value can use this information
 * for revision control.
 *
 * The lower two bytes of the text_catalog_revision are used for a language
 * revision (one byte major, one byte minor revision). The language revision
 * denotes the mapping from a TextId to an actual string in the monitor
 * language.
 *
 * The Language field describes the language used by the monitor.
 * It is defined as follows:
 */
#define LANGUAGE_UNSPEC (0)
#define ENGLISH (1)
#define GERMAN (2)
#define FRENCH (3)
#define ITALIAN (4)
#define SPANISH (5)
#define DUTCH (6)
#define SWEDISH (7)
#define FINNISH (8)
#define NORWEG (9)
#define DANISH (10)
#define JAPANESE (11)
#define REP_OF_CHINA (12)
#define PEOPLE_REP_CHINA (13)
#define PORTUGUESE (14)
#define RUSSIAN (15)
#define BYELORUSSIAN (16)
#define UKRAINIAN (17)
#define CROATIAN (18)
#define SERBIAN (19)
#define MACEDONIAN (20)
#define BULGARIAN (21)
#define GREEK (22)
#define POLISH (23)
#define CZECH (24)
#define SLOVAK (25)
#define SLOVENIAN (26)
#define HUNGARIAN (27)
#define ROMANIAN (28)
#define TURKISH (29)
#define LATVIAN (30)
#define LITHUANIAN (31)
#define ESTONIAN (32)
#define KOREAN (33)

///	The StringFormat describes how strings are encoded.
///	The IntelliVue monitor uses unicode encoding.

#define STRFMT_UNICODE_NT (11)


/**
 * Attribute:	Protocol Support
 * The Protocol Support contains an entry for each protocol supported on the
 * network interface.
 *
 * Attribute ID:	NOM_ATTR_PCOL_SUPPORT
 * Attribute Type:	ProtoSupport
 * Attribute Groups: -
 * Availability: -
 */

typedef uint16_t ApplProtoId;
#define AP_ID_ACSE (1)
#define AP_ID_DATA_OUT (5)

typedef uint16_t TransProtoId;
#define TP_ID_UDP (1)

typedef uint16_t ProtoOptions;
#define P_OPT_WIRELESS (0x8000)

typedef struct
{
  ApplProtoId appl_proto;
  TransProtoId trans_proto;
  uint16_t port_number;
  ProtoOptions options;
} ProtoSupportEntry;

typedef struct
{
  uint16_t count;
  uint16_t length;
  ProtoSupportEntry* value;
} ProtoSupport;
/**
 * The Computer Client should parse the available protocols and
 * search for the AP_ID_DATA_OUT. This entry specifies the port for the Data
 * Export Protocol. The corresponding Association Control Protocol runs on the
 * same port.
 *
 * The Computer Client must only send requests to the port specified for the
 * Data Export Protocol.
 */

/**
 * The Action Result command is used as a response message to the Action
 * message. It is appended to the Operation Result message or an Operation
 * Linked Result message (if the size of the returned data
 * exceeds a maximum message size). The command_type is set to
 * CMD_CONFIRMED_ACTION.
 */
typedef struct
{
  ManagedObjectId managed_object;
  OIDType action_type; /// identification of method
  uint16_t length;
} ActionResult;



/**
 * Session Headers
 * Session Headers can be used to identify the protocol commands. Each Session
 * Header type maps to one protocol command.
 *
 * The Session Header occupies the first bytes of the message.
 */
typedef uint8_t* LI;

typedef struct
{
  uint8_t type;
#define CN_SPDU_SI (0x0D)
#define AC_SPDU_SI (0x0E)
#define RF_SPDU_SI (0x0C)
#define FN_SPDU_SI (0x09)
#define DN_SPDU_SI (0x0A)
#define AB_SPDU_SI (0x19)
  LI length;
} SessionHeader;
/**
 * The type field has the following meaning:
 * CN_SPDU_SI: A Session Connect header. The message contains an Association
 * Request.
 * AC_SPDU_SI: A Session Accept header. The message contains an Association
 * Response, indicating successful association.
 * RF_SPDU_SI: A Session Refuse header. Failed to establish an association.
 * FN_SPDU_SI: A Session Finish header. The message contains a Release Request,
 * indicating that the association should be terminated.
 * DN_SPDU_SI: A Session Disconnect header. The message contains a Release
 * Response, indicating that the association has been terminated.
 * AB_SPDU_SI: A Session Abort header. The message contains an Abort message,
 * indicating the immediate termination of the association.
 *
 * If the first byte is 0xE1, the message is a Data Export Protocol command
 * message (see page 25 for Definition of the Data Export Protocol).
 *
 * The LI field contains the length of the appended data (including all
 * presentation data). The length encoding uses the following rules:
 * -- If length is smaller or equal 254 bytes, LI is one byte containing the
 * actual length.
 * -- If the length is greater than 254 bytes, LI is three bytes, the first
 * being 0xff, the following two bytes containing the actual length.
 * Examples:
 * L = 15 is encoded as 0x0f
 * L = 256 is encoded as {0xff,0x01,0x00}
 */


///	MDSEUserInfoStd

typedef uint32_t ProtocolVersion;
#define MDDL_VERSION1 (0x80000000)

typedef uint32_t NomenclatureVersion;
#define NOMEN_VERSION (0x40000000)

typedef uint32_t FunctionalUnits;

typedef uint32_t SystemType;
#define SYST_CLIENT (0x80000000)
#define SYST_SERVER (0x00800000)

typedef uint32_t StartupMode;
#define HOT_START (0x80000000)
#define WARM_START (0x40000000)
#define COLD_START (0x20000000)

typedef struct MDSEUserInfoStd
{
  ProtocolVersion protocol_version;
  NomenclatureVersion nomenclature_version;
  FunctionalUnits functional_units;
  SystemType system_type;
  StartupMode startup_mode;
  AttributeList option_list;
  AttributeList supported_aprofiles;
} MDSEUserInfoStd;

/**
 * The Computer Client must fill out the MDSEUserInfoStd data structure. It
 * specifies the protocol versions and options the Computer Client supports.
 * The IntelliVue monitor parses the MDSEUserInfoStd and constructs an
 * Association Response message, which also contains a MDSEUserInfoStd data
 * structure. The Association Response specifies which protocol versions and
 * options will be used for the session.
 *
 * The ProtocolVersion bit field contains the supported versions of the Data
 * Export protocol. The Computer Client must set the bits for each version is
 * supports. The IntelliVue monitor checks the supported versions and returns
 * the bit for the highest commonly supported protocol version. If no
 * matching version is found, the Association Request is refused.
 *
 * The NomenclatureVersion bit field contains the revision of the nomenclature
 * which is used to name objects and their attributes. The Computer Client
 * must set the bits for each version is supports. The IntelliVue monitor
 * checks the supported versions and returns the bit for the highest commonly
 * supported nomenclature version. If no matching version is found, the
 * Association Request is refused.
 *
 * The FunctionalUnits activates additional protocol functions. The Computer
 * Client must set the bit for each functional unit it supports. The
 * IntelliVue monitor checks the supported functional units and returns the
 * bits for all commonly supported units (bitwise AND). No additional protocol
 * functions have been defined yet.
 *
 * The SystemType bit field indicates whether the device is a Computer Client
 * or a server. The Computer Client must set the SYST_CLIENT bit and the
 * IntelliVue monitor will return the SYST_SERVER bit. If the SYST_CLIENT bit
 * is not set in the Association Request, the association is refused.
 *
 * The StartupMode indicates the startup mode of the Computer Client and the
 * IntelliVue monitor respectively. The IntelliVue monitor sets the bit for
 * the startup mode which was used for the last reboot.
 *
 * If the IntelliVue monitor performs a COLD_START, all device settings are
 * reset to the factory defaults. The configurations of the measurements
 * might have changed and the patient data is lost.
 *
 * The startup mode WARM_START and HOT_START indicate that configuration was
 * not reset during the last restart.
 *
 * The option_list can be used to negotiate additional protocol options in the
 * form of an AttributeList. Currently, no further options are supported.
 *
 * The option_list has a variable length. The offset of the
 * supported_aprofiles field depends on the length of the option_list.
 *
 * The supported_aprofiles AttributeList is used to define the available
 * application profiles. An application profile specifies a set of protocol
 * commands that is supported by the system. The Computer Client must add an
 * entry for each supported profile to this list. The IntelliVue monitor
 * parses the supported_aprofiles and returns the first profile in the list
 * that is supported. If none of the profiles is supported, the Association
 * Request is refused. The IntelliVue monitor supports the following profiles:
 *
 * Poll Profile Support
 * Poll Profile Extensions
 */

/**
 * PollProfileSupport
 * The Poll Profile Support attribute contains the specification of the polling
 * profile supported by the system.
 * Attribute ID: NOM_POLL_PROFILE_SUPPORT
 * Attribute Type: PollProfileSupport
 */
typedef uint32_t PollProfileRevision;
#define POLL_PROFILE_REV_0 (0x80000000)

typedef uint32_t PollProfileOptions;
#define P_OPT_DYN_CREATE_OBJECTS (0x40000000)
#define P_OPT_DYN_DELETE_OBJECTS (0x20000000)

typedef struct PollProfileSupport
{
  PollProfileRevision poll_profile_revision;
  RelativeTime min_poll_period;
  uint32_t max_mtu_rx;
  uint32_t max_mtu_tx;
  uint32_t max_bw_tx;
  PollProfileOptions options;
  AttributeList optional_packages;
} PollProfileSupport;

/**
 * The PollProfileRevision is a bit field containing the supported versions
 * of the Polling Profile. The Computer Client must set the bits for each
 * version it supports. The IntelliVue monitor checks the supported versions
 * and returns the bit for the highest commonly supported profile version.
 * If no matching version is found, the profile is not supported.
 *
 * The min_poll_period specifies the minimum period with which the Computer
 * Client wants to poll. If the IntelliVue monitor supports the requested
 * poll period, it will return the value, otherwise it will return the
 * minimum poll period it supports. The Computer Client should not send poll
 * requests with a higher period than the negotiated value. For more
 * information on poll periods, refer to the section SINGLE POLL DATA REQUEST
 * on page 45.
 *
 * The min_poll_period is also used to specify association time-outs. If the
 * IntelliVue monitor does not receive any messages from the Computer Client
 * within a given time, it sends an Abort message and terminates the
 * association. The time-out periods depend on the negotiated
 * min_poll_period, they are listed in the table below.
 *
 * min_poll_period  Association Time out
 * < 3.3s           10s
 * 3.3s - 43s       3*min_poll_period
 * > 43s            130s
 *
 *
 * The max_mtu_rx and max_mtu_tx fields contain the maximum size (MTU -
 * Maximum Transport Unit) for protocol commands (the size of the protocol
 * command is the size of the data appended after the Remote Operation Header).
 * The MTU negotiation uses the following procedure:
 *
 * -- The Computer Client determines the maximum size of a protocol command
 * it can send and receive.
 * -- The Computer Client sets max_mtu_tx to the maximum size it can transmit
 * (i.e. the IntelliVue monitor should provide receive capabilities for
 * messages of this size) and the max_mtu_rx to the maximum size it can
 * receive (i.e. the IntelliVue monitor should not send larger commands).
 * -- The IntelliVue monitor determines the maximum size of a protocol
 * command it can send and receive.
 * -- The IntelliVue monitor sets max_mtu_tx to the maximum size the Computer
 * Client is allowed to transmit (this is the minimum of the max_mtu_tx the
 * Computer Client requested and the message size the IntelliVue monitor can
 * receive). The IntelliVue monitor sets max_mtu_rx to the maximum
 * size the client must be able to receive (this is the minimum of the
 * max_mtu_rx the Computer Client requested and the message size the
 * IntelliVue monitor can send).
 *
 * Example:
 * -- The Computer Client can send 800 bytes and receive 500 bytes of user
 * data in one message.
 * -- The Computer Client sets max_mtu_tx to 800 and max_mtu_rx to 500.
 * -- The IntelliVue monitor can send 700 bytes and receive 600 bytes in one
 * message.
 * -- The IntelliVue monitor sets max_mtu_tx to 600 bytes (the IntelliVue
 * monitor can not receive larger messages) and max_mtu_rx to 500 bytes (the
 * Computer Client can not receive more than 500 bytes in a message).
 *
 * The IntelliVue monitor requires that the Computer Client can receive
 * protocol commands of at least 300 bytes. Otherwise the profile is not
 * supported. Smaller command sizes would lead to a considerable
 * communication overhead. The largest negotiable MTU is 1364 bytes for the
 * LAN interface and 1000 Bytes for the MIB/RS232 interface. The resulting
 * size of the data packets may be larger than the MTU, because the MTU
 * covers only the size of the Command Header and the Command Specific Data.
 *
 * It is recommended that the Computer Client uses a large MTU. This reduces
 * processing overhead and in most cases avoids splitting of messages.
 *
 * For wave data export, the Computer Client needs to be able to receive
 * observed values with 256 ms of wave data in one message. The MTU should be
 * at least 500 bytes (700 bytes with multiplexed context).
 *
 * The max_bw_tx contains the estimated maximum transmit bandwidth which will
 * be used. The IntelliVue monitor fills in the maximum transmit bandwidth it
 * uses, the value 0xffffffff indicates that no estimation is possible (this
 * is the default). The current software does not support bandwidth
 * estimation.
 *
 * The PollProfileOptions bit field is used to set additional profile options.
 * The IntelliVue monitor sets the P_OPT_DYN_CREATE_OBJECTS and
 * P_OPT_DYN_DELETE_OBJECTS bits to indicate that the number of internal
 * objects (e.g. the number of Numerics) may change dynamically.
 *
 * The optional_packages AttributeList allows the definition of additional
 * options supported in the profile. The Computer Client must add an entry for
 * each optional package it requests. The IntelliVue monitor checks the
 * packages and adds an entry for each package it supports in the Association
 * Response. An attribute constitutes an optional package. The Poll Profile
 * Extension is an optional package available for use.
 *
 */

/**
 * Poll Profile Extensions
 * The Poll Profile Extensions attribute specifies some extensions for the
 * standard polling profile. For more information on how to use these
 * extensions refer to the section EXTENDED POLL DATA REQUEST on page 49.
 * Attribute ID: NOM_ATTR_POLL_PROFILE_EXT
 * Attribute Type: PollProfileExt
 * Attribute Groups: -
 */
typedef uint32_t PollProfileExtOptions;
#define POLL_EXT_PERIOD_NU_1SEC (0x80000000)
#define POLL_EXT_PERIOD_NU_AVG_12SEC (0x40000000)
#define POLL_EXT_PERIOD_NU_AVG_60SEC (0x20000000)
#define POLL_EXT_PERIOD_NU_AVG_300SEC (0x10000000)
#define POLL_EXT_PERIOD_RTSA (0x08000000)

typedef struct
{
  PollProfileExtOptions options;
  AttributeList ext_attr;
} PollProfileExt;

/**
 * The PollProfileExtOptions bit field defines available options for the Poll
 * Profile Extensions package. If the POLL_EXT_PERIOD_NU_1SEC bit is set,
 * the Computer Client requests real-time measurements as source for Numeric
 * data.
 *
 * If the POLL_EXT_PERIOD_NU_AVG_12SEC bit is set, the Computer Client
 * requests 12 second averaged data as source for Numeric data.
 *
 * If the POLL_EXT_PERIOD_NU_AVG_60SEC bit is set, the Computer Client
 * requests 1 minute averaged data as source for Numeric data.
 *
 * If the POLL_EXT_PERIOD_NU_AVG_300SEC bit is set, the Computer Client
 * requests 5 minute averaged data as source for Numeric data.
 *
 * The Computer Client must set at least one of the bits, otherwise the
 * optional package is ignored. Currently, the IntelliVue monitor supports
 * only one source for an association. If more than one of the bits is set,
 * the source with the smallest measurement period is selected. The IntelliVue
 * monitor sets the corresponding bit in the Association Response message.
 *
 * There may be only one active numeric source at a given time. If there is an
 * active association on the LAN interface which has requested realtime
 * numerics, it is not possible to establish another association
 * on the MIB/RS232 interface which requests 1 minute averaged data. In this
 * case, the association request would result in a refuse message.
 *
 * If the POLL_EXT_PERIOD_RTSA bit is set, the computer client requests wave
 * data. The patient monitor sets the corresponding bit in its response
 * message to indicate wave data export capability.
 *
 * The ext_attr AttributeList is reserved for future extensions.
 *
 * The Computer Client must parse the Association Response message to find out
 * whether the requested options have been accepted by the IntelliVue monitor.
 */

/**
 * SINGLE POLL DATA REQUEST
 * This message can be sent as soon as the logical connection is established
 * and the MDS Create Event/Reply message sequence is finished. The message
 * calls a method that returns IntelliVue monitor device data in a single
 * response message.
 *
 * MDSPollAction ::=
 * <SPpdu>
 * <ROapdus (ro_type := ROIV_APDU)>
 * <ROIVapdu (command_type := CMD_CONFIRMED_ACTION)>
 * <ActionArgument
 * (managed_object := {NOM_MOC_VMS_MDS, 0, 0},
 * action_type := NOM_ACT_POLL_MDIB_DATA)>
 * <PollMdibDataReq>
 *
 * The managed_object must be the same as the managed_object in the MDS Create
 * Event message. This is the top level object which actually implements the
 * Data Export protocol.
 *
 * The appended PollMdibDataRequest has the following data type:
 */
typedef struct
{
  uint16_t poll_number;
  TYPE polled_obj_type;
  OIDType polled_attr_grp;
} PollMdibDataReq;

/**
 * poll_number
 * This field will be sent back in the response message. It is recommended to
 * use this field as a counter.
 *
 * polled_obj_type
 * Defines which objects (Numerics or Alarms or MDS or Patient Demographics)
 * is polled. The following lists supported objects and their corresponding
 * TYPE values:
 *
 * NUMERICS:	partition:	0x0001
 * 				code:			NOM_MOC_VMO_METRIC_NU
 * WAVES:		partition:	0x0001
 * 				code:			NOM_MOC_VMO_METRIC_SA_RT
 * ALERTS:		partition:	0x0001
 * 				code:			NOM_MOC_VMO_AL_MON
 * Pat.Demog:	partition:	0x0001
 * 				code:			NOM_MOC_PT_DEMOG
 * MDS:			partition:	0x0001
 * 				code:			NOM_MOC_VMS_MDS
 *
 * The codes are taken from the Object Oriented Elements partition of the
 * nomenclature (see Object Classes on page 98).
 *
 * polled_attr_grp
 * Defines which set of attributes is polled. For more information on the
 * supported attribute groups and their contents, please refer to the
 * section Attribute Data Types and Constants Used on page 65.
 *
 * The IntelliVue monitor specifies limits on the maximum frequency for
 * incoming SINGLE POLL DATA REQUEST messages. If the Computer Client sends
 * messages with a frequency above the limit, some of the messages will be
 * ignored (no response is sent). Separate limits are calculated for each
 * object.
 *
 * The IntelliVue monitor will process a maximum of one POLL DATA REQUEST
 * messages for each object type per second. An additional POLL DATA REQUEST
 * for Numeric Observed Values is allowed.
 */


///  The ObservationPoll represents the polled data of one object instance.

typedef struct
{
  Handle obj_handle;
  AttributeList attributes;
} ObservationPoll;


/// The Single Context Poll structure contains polled data of all object
/// instances within one unique naming context (IntelliVue monitor supports
/// multiple naming contexts).

typedef struct
{
  MdsContext context_id;

  struct
  {
    uint16_t count;
    uint16_t length;
    ObservationPoll* value;
  } poll_info;
} SingleContextPoll;


/// The Poll Info List is an array structure where each SingleContextPoll
/// element contains the poll result data of one naming context

typedef struct
{
  uint16_t count;
  uint16_t length;
  SingleContextPoll* value;
} PollInfoList;


/// The PollMdibDataReply structure is the top level data structure returned
/// in the Single Poll Data Result message.

typedef struct
{
  uint16_t poll_number;
  RelativeTime rel_time_stamp;
  AbsoluteTime abs_time_stamp;
  TYPE polled_obj_type;
  OIDType polled_attr_grp;
  PollInfoList poll_info_list;
} PollMdibDataReply;

/// poll_number
/// The poll number field contains the value of the same field in the Poll
/// Request message.

typedef uint16_t AlertPriority;

typedef uint16_t AlertFlags;
#define BEDSIDE_AUDIBLE (0x4000)
#define CENTRAL_AUDIBLE (0x2000)
#define VISUAL_LATCHING (0x1000)
#define AUDIBLE_LATCHING (0x0800)
#define SHORT_YELLOW_EXTENSION (0x0400)
#define DERIVED (0x0200)

typedef uint16_t AlertType;
#define NO_ALERT (0)
#define LOW_PRI_T_AL (1)
#define MED_PRI_T_AL (2)
#define HI_PRI_T_AL (4)
#define LOW_PRI_P_AL (256)
#define MED_PRI_P_AL (512)
#define HI_PRI_P_AL (1024)

typedef uint16_t AlertState;
#define AL_INHIBITED (0x8000)
#define AL_SUSPENDED (0x4000)
#define AL_LATCHED (0x2000)
#define AL_SILENCED_RESET (0x1000)
#define AL_DEV_IN_TEST_MODE (0x0400)
#define AL_DEV_IN_STANDBY (0x0200)
#define AL_DEV_IN_DEMO_MODE (0x0100)
#define AL_NEW_ALERT (0x0008)

typedef struct
{
  uint16_t length;
  uint16_t* value;
} String;

typedef struct
{
  OIDType al_source;
  OIDType al_code;
  AlertType al_type;
  AlertState al_state;
  ManagedObjectId object;
  PrivateOID alert_info_id;
#define GEN_ALMON_INFO (513)
#define STR_ALMON_INFO (516)
  uint16_t length;
  // NOTE: The following alert_info member doesn't exist in the intellivue
  // manual, but I'm adding it here because either a AlMonGenInfo or a
  // StrAlMonInfo structure is appended. The alert_info member will be used
  // to make parsing easier.
  uint8_t* alert_info;
} DevAlarmEntry;


/// The Device T-Alarm List attribute contains the active technical alarms
/// (inops) in the system.

typedef struct
{
  uint16_t count;
  uint16_t length;
  DevAlarmEntry* value;
} DevAlarmList;


/**
 * The al_source is taken from the Object Oriented or the SCADA partition
 * (depending on al_code). It identifies the origin of the alert (e.g.
 * temperature). The al_code is taken from the Events partition and describes
 * the reason for the alert (e.g. high alarm).
 * The least significant bit is used to define the nomenclature partition for
 * al_source. Last bit 0 means SCADA partition, last bit 1 means Object
 * Oriented partition. The definitions for AlertType and AlertState can be
 * found in the paragraph about the Device Alert Condition.
 * The object field contains a reference to the object which generated the
 * alert. The object may not be known to the Computer Client, if the Data
 * Export protocol does not allow accessing the specific object.
 */


/// If the alert_info_id is set to GEN_ALMON_INFO, an AlMonGenInfo structure
/// is appended:

typedef struct
{
  uint16_t al_inst_no;
  TextId al_text;
  AlertPriority priority;
  AlertFlags flags;
} AlMonGenInfo;


/// If the alert_info_id is set to STR_ALMON_INFO, an StrAlMonInfo structure
// is appended:

typedef struct
{
  uint16_t al_inst_no;
  TextId al_text;
  AlertPriority priority;
  AlertFlags flags;
  String string;
} StrAlMonInfo;


/// The Application Area attribute describes the intended application area for
/// the device
typedef uint16_t ApplicationArea;
#define AREA_UNSPEC (0)
#define AREA_OPERATING_ROOM (1)
#define AREA_INTENSIVE_CARE (2)
#define AREA_NEONATAL_INTENSIVE_CARE (3)
#define AREA_CARDIOLOGY_CARE (4)


/// The Color attribute describes the color in which a numeric is displayed on
/// the screen.
typedef uint16_t SimpleColour;
#define COL_BLACK (0)
#define COL_RED (1)
#define COL_GREEN (2)
#define COL_YELLOW (3)
#define COL_BLUE (4)
#define COL_MAGENTA (5)
#define COL_CYAN (6)
#define COL_WHITE (7)
#define COL_PINK (20)
#define COL_ORANGE (35)
#define COL_LIGHT_GREEN (50)
#define COL_LIGHT_RED (65)


/// The Device Alert Condition attribute contains global device alert status
/// information

typedef struct
{
  AlertState device_alert_state;
  uint16_t al_stat_chg_cnt;
  AlertType max_p_alarm;
  AlertType max_t_alarm;
  AlertType max_aud_alarm;
} DeviceAlertCondition;

/**
 * The Display Resolution attribute is present if the resolution of the
 * numeric shown on the display must be different from the resolution
 * communicated in the Numeric Observed Value attribute. E.g. a Temperature is
 * displayed with a resolution of 1/10, but the Observed Value is sent with
 * a precision of 1/100 to get the necessary accuracy for differential
 * temperatures. The Display Resolution attribute describes the format in
 * which the value of a numeric is displayed on the screen
 */
typedef struct
{
  uint8_t pre_point;
  uint8_t post_point;
} DispResolution;

/**
 * FLOATType
 * first 8 bits are a signed exponent
 * next 24 bits are a signed mantissa
 * The number represented is (mantissa)*(10^exponent).
 */
typedef uint32_t FLOATType;

/**
 * There are four special values of the mantissa that can be represented:
 * NaN (Not a Number), which has a mantissa of +(223 -1) (0x7fffff)
 * NRes (Not at this resolution), which has a mantissa of -(223) (0x800000)
 * +/- INFINITY, which have mantissa of +/- (223-2) (0x7ffffe, 0x800002).
 */


typedef struct
{
  FLOATType absolute_value;
  uint16_t scaled_value;
  uint16_t level;
} SaGridEntry16;
/// Different levels define relative importance of grid lines. 0 is the first
/// (most important) level.

typedef struct
{
  uint16_t count;
  uint16_t length;
  SaGridEntry16* value;
} SaVisualGrid16;
/// The Visual Grid attribute allows to define grid lines.

typedef uint32_t TextId;

/// The Line Frequency attribute describes the frequency of the main power
// supply in Hz.
typedef uint16_t LineFrequency;
#define LINE_F_UNSPEC (0)
#define LINE_F_50HZ (1)
#define LINE_F_60HZ (2)


/// It allows to distinguish between measurements, calculations and settings.
typedef uint16_t MetricCategory;
#define MCAT_UNSPEC (0)
#define AUTO_MEASUREMENT (1)
#define MANUAL_MEASUREMENT (2)
#define AUTO_SETTING (3)
#define MANUAL_SETTING (4)
#define AUTO_CALCULATION (5)
#define MANUAL_CALCULATION (6)
#define AUTO_ADJUST_PAT_TEMP (128)
#define MANUAL_ADJUST_PAT_TEMP (129)
#define AUTO_ALARM_LIMIT_SETTING (130)
/**
 * MCAT_UNSPEC: not specified
 * AUTO_MEASUREMENT: automatic measurement
 * MANUAL_MEASUREMENT: manual measurement
 * AUTO_SETTING: automatic setting
 * MANUAL_SETTING: manual setting
 * AUTO_CALCULATION: automatic calculation, e.g. differential temperature
 * MANUAL_CALCULATION: manual calculation
 * AUTO_ADJUST_PAT_TEMP: measurement is automatically adjusted for patient
 * temperature
 * MANUAL_ADJUST_PAT_TEMP: measurement manually adjusted for patient
 * temperature
 * AUTO_ALARM_LIMIT_SETTING: this is not a measurement, but an alarm limit
 * setting
 */

/// The MetricAccess bit field provides info on how the metric value can be
/// accessed and when a measurement is available.
typedef uint16_t MetricAccess;
#define AVAIL_INTERMITTEND (0x8000)
#define UPD_PERIODIC (0x4000)
#define UPD_EPISODIC (0x2000)
#define MSMT_NONCONTINUOUS (0x1000)
/**
 * AVAIL_INTERMITTEND: The intermitted availability bit is set, if the
 * observed values not always available (e.g. only if a measurement is
 * explicitly started).
 * UPD_PERIODIC: observed value is updated periodically
 * UPD_EPISODIC: observed value is updated episodically (exactly one update
 * mode (UPD_) must be set
 * MSMT_NONCONTINUOUS: indicates that the measurement is non continuous
 * (this is different from the update mode)
 */

/**
 * The MetricStructure describes if the object represents a single measurement
 * or multiple related measurements (an invasive blood pressure could be
 * compound when it represents a pulsatile pressure like ABP and derives
 * systolic, diastolic, mean values)
 */
typedef struct
{
  uint8_t ms_struct;
  uint8_t ms_comp_no;
} MetricStructure;
/**
 * ms_struct describes the structure of the object, 0 means simple, 1 means
 * compound object.
 * ms_comp_no contains the maximum number of components in the compound,
 * it contains 0 for simple objects.
 */

/// The MetricRelevance is a 16 bit wide field for internal use only.
typedef uint16_t MetricRelevance;


/// The Metric Specification attribute describes static properties of a
/// numeric.

typedef struct
{
  RelativeTime update_period;
  MetricCategory category;
  MetricAccess access;
  MetricStructure structure;
  MetricRelevance relevance;
} MetricSpec;

typedef uint16_t MetricModality;
#define METRIC_MODALITY_MANUAL (0x4000)
#define METRIC_MODALITY_APERIODIC (0x2000)
#define METRIC_MODALITY_VERIFIED (0x1000)

/// indicates metric on or off state.
typedef uint16_t MetricState;
#define METRIC_OFF (0x8000)

/// The Measure Mode attribute defines specific measurement modes.
typedef uint16_t MeasureMode;
#define CO2_SIDESTREAM (0x0400)
#define ECG_PACED (0x0200)
#define ECG_NONPACED (0x0100)
#define ECG_DIAG (0x0080)
#define ECG_MONITOR (0x0040)
#define ECG_FILTER (0x0020)
#define ECG_MODE_EASI (0x0008)
#define ECG_LEAD_PRIMARY (0x0004)
/**
 * CO2_SIDESTREAM: CO2 sidestream.
 * ECG_PACED, ECG_NONPACED: Paced mode setting.
 * ECG_DIAG, ECG_MONITOR, ECG_FILTER: ECG filter setting.
 * ECG_MODE_EASI: EASI derived lead.
 * ECG_LEAD_PRIMARY: ECG primary lead.
 */
/// The Operating Mode attribute identifies the current operating mode of the
/// device.
#define OPMODE_UNSPEC (0x8000)
#define MONITORING (0x4000)
#define DEMO (0x2000)
#define SERVICE (0x1000)
#define OPMODE_STANDBY (0x0002)
#define CONFIG (0x0001)
/**
 * OPMODE_UNSPEC: The Operating Mode is not specified.
 * MONITORING: Device is configured to monitor patient data (the default mode).
 * DEMO: Demonstration Mode with simulated patient data.
 * SERVICE: Device is in Service Mode.
 * STANDBY: Standby and Power Safe Mode.
 * CONFIG: Device is in Configuration Mode.
 */

typedef uint16_t MeasurementState;
#define INVALID (0x8000)
#define QUESTIONABLE (0x4000)
#define UNAVAILABLE (0x2000)
#define CALIBRATION_ONGOING (0x1000)
#define TEST_DATA (0x0800)
#define DEMO_DATA (0x0400)
#define VALIDATED_DATA (0x0080)
#define EARLY_INDICATION (0x0040)
#define MSMT_ONGOING (0x0020)
#define MSMT_STATE_IN_ALARM (0x0002)
#define MSMT_STATE_AL_INHIBITED (0x0001)

/**
 * INVALID: The source detects a sufficient degradation to render the data
 * meaningless.
 * QUESTIONABLE: A problem exists, but it is still appropriate to present the
 * data. This occurs when (1) either the degradation in the data is marginal
 * or (2) the source cannot make a definite judgement on the reliability of
 * the data.
 * UNAVAILABLE: The signal does not permit derivation of the numeric in
 * question. This could be a transient state (e.g. first breath detected
 * after an apnea -> no rate available), or a continuous state (no
 * etCO2 detection possible on a flat CO2 wave).
 * CALIBRATION_ONGOING: Parameter is currently being calibrated.
 * TEST_DATA: The signal is an automatically generated test signal only and
 * is not a valid patient
 * signal. If this bit is set, the value is not suitable for patient diagnosis.
 * DEMO_DATA: The IntelliVue monitor runs in demonstration mode, the signal
 * is automatically generated and is not a valid patient signal. If this bit
 * is set, the value is not suitable for patient diagnosis.
 * VALIDATED_DATA: The value has been manually validated.
 * EARLY_INDICATION: The value represents an early estimate of the actual
 * signal (the Non-Invasive Blood Pressure measurement e.g. sets this bit as
 * soon as it has derived a systolic value, even
 * if mean and diastolic values are still missing).
 * MSMT_ONGOING: A new aperiodic measurement is currently ongoing.
 * MSMT_STATE_IN_ALARM: Indicates that the numeric has an active alarm
 * condition
 * MSMT_STATE_AL_INHIBITED: Alarms are switched off for the numeric (crossed
 * bell)
 */


/// The Numeric Observed Value attribute represents the (measured) value,
/// along with state and identification data.

typedef struct
{
  OIDType physio_id;
  MeasurementState state;
  OIDType unit_code;
  FLOATType value;
} NuObsValue;
/**
 * The physio_id (physiological identifier) field contains a nomenclature code
 * from the SCADA partition that identifies the represented value (typically
 * a physiological measurement).
 * The unit_code field contains a nomenclature code from the dimension
 * nomenclature partition. It identifies the units of measure.
 * The value field is a floating point number with the actual value. Before
 * interpreting the numeric value, the state must be checked. Only if state
 * indicates a valid measurement, should the value field be interpreted.
 */

/**
 * The Compound Numeric Observed Value attribute represents multiple
 * (measured) values modelled in one Numeric object, along with state and
 * identification data. The Compound Numeric Observed Value is e.g. used to
 * represent Blood Pressure measurements. For these measurements, systolic,
 * diastolic and mean values are represented by a single Numeric object.
 */
typedef struct
{
  uint16_t count;
  uint16_t length;
  NuObsValue* value;
} NuObsValueCmp;

typedef struct
{
  FLOATType value;
  OIDType m_unit;
} PatMeasure;
/// The value contains the actual value of the attribute and the m_units
/// indicates the unit of measurement for the value.

typedef uint16_t PatDemoState;
#define EMPTY (0)
#define PRE_ADMITTED (1)
#define ADMITTED (2)
#define DISCHARGED (8)
/**
 * EMPTY: No patient information present.
 * PRE_ADMITTED: Currently not used.
 * ADMITTED: Patient information is present and valid.
 * DISCHARGED: Data is still available, but patient is no longer assigned to
 * device.
 */
typedef uint16_t PatPacedMode;
#define PAT_NOT_PACED (0)
#define PAT_PACED_GEN (1)
/**
 * Values greater one are reserved to indicate special paced modes. The
 * Computer Client should test for "== 0" or "!= 0".
 */
typedef uint16_t PatientSex;
#define SEX_UNKNOWN (0)
#define MALE (1)
#define FEMALE (2)
#define SEX_UNSPECIFIED (9)
/**
 * SEX_UNKNOWN: Patient sex is not known
 * MALE: Patient is male
 * FEMALE: Patient is female
 * SEX_UNSPECIFIED: Patient sex is not specified
 */
typedef uint16_t PatientType;
#define PAT_TYPE_UNSPECIFIED (0)
#define ADULT (1)
#define PEDIATRIC (2)
#define NEONATAL (3)


/// The Sample Array Calibration Specification allows to define the presence
/// of a calibration bar or calibration stair.

typedef struct
{
  FLOATType lower_absolute_value;
  FLOATType upper_absolute_value;
  uint16_t lower_scaled_value;
  uint16_t upper_scaled_value;
  uint16_t increment;
  uint16_t cal_type;
#define BAR (0)
#define STAIR (1)
} SaCalData16;

typedef struct
{
  OIDType physio_id;
  MeasurementState state;

  struct
  {
    uint16_t length;
    uint8_t* value;
  } array;
} SaObsValue;

/**
 * The physio_id (physiological identifier) field contains a nomenclature code
 * from the SCADA partition that identifies the represented wave (typically
 * a physiological measurement). The state indicates measurement validity.
 * Refer to the Numeric object for a definition of the bit field.
 * The measurement is valid if the first octet of the state is all 0.
 *
 * The Sample Array Observed Value attribute represents the wave samples,
 * along with state and identification data.
 */
typedef struct
{
  uint16_t count;
  uint16_t length;
  SaObsValue* value;
} SaObsValueCmp;


/// The Sample Array Physiological Range is used for display scaling

typedef struct
{
  uint16_t lower_scaled_value;
  uint16_t upper_scaled_value;
} ScaledRange16;

typedef struct
{
  uint8_t sample_size;
  uint8_t significant_bits;
} SampleType;
/**
 * The sample_size specifies the number of bits used to encode one wave sample.
 * The number of significant_bits is less or equal sample_size. To get the
 * actual sample value, nonsignificant bits must be masked if indicated in the
 * flags value.
 */


typedef uint16_t SaFlags;
#define SMOOTH_CURVE (0x8000)
#define DELAYED_CURVE (0x4000)
#define STATIC_SCALE (0x2000)
#define SA_EXT_VAL_RANGE (0x1000)
/**
 * SMOOTH_CURVE, DELAYED_CURVE : used for wave presentation
 * STATIC_SCALE: Scale and range specification does not change.
 * SA_EXT_VAL_RANGE: The non-significant bits in the sample value must be
 * masked.
 */


/// The Sample Array Specification describes static properties of a wave
/// object.

typedef struct
{
  uint16_t array_size;
  SampleType sample_type;
  SaFlags flags;
} SaSpec;


/// The Scale and Range Specification describes a relation between scaled
/// values and absolute values and also defines the range of the measured
/// values and samples.

typedef struct
{
  FLOATType lower_absolute_value;
  FLOATType upper_absolute_value;
  uint16_t lower_scaled_value;
  uint16_t upper_scaled_value;
} ScaleRangeSpec16;

/**
 * The scaled values refer to the wave samples in the observed values.
 * If the wave does not represent any absolute value, the absolute value
 * fields must be NaN (Not a Number).
 */

typedef struct
{
  OIDType obj_id;
  FLOATType num_val;
  OIDType unit_code;
} EnumObjIdVal;

typedef struct
{
  uint16_t choice;
  uint16_t length;

  union
  {
    OIDType enum_obj_id;
    EnumObjIdVal enum_obj_id_val;
  } u;
} EnumVal;

/**
 * The field choice of structure EnumVal defines the valid structure of
 * union u. Its values are defined as follows:
 */
#define ENUM_OBJ_ID_CHOSEN (1)
#define ENUM_OBJ_ID_VAL_CHOSEN (4)

typedef struct
{
  OIDType physio_id;
  MeasurementState state;
  EnumVal value;
} EnumObsVal;

typedef struct
{
  TYPE object_type;
  uint32_t max_inst;
} MdibObjectSupportEntry;

typedef struct
{
  uint16_t count;
  uint16_t length;
  MdibObjectSupportEntry* value;
} MdibObjectSupport;
/// The MdibObjextSupport contains a list of all object classes supported by
/// the system and the maximum number of instances per class. If max_inst
/// contains 0xffffffff, it is not defined.

typedef struct
{
  PrivateOID component_capab_id;
  uint16_t length;
  uint16_t* value;
} SystemSpecEntry;


/// The System Specification attribute contains a set of functional components
/// supported by the system.

typedef struct
{
  uint16_t count;
  uint16_t length;
  SystemSpecEntry* value;
} SystemSpec;


typedef uint16_t MDSStatus;
#define DISCONNECTED (0)
#define UNASSOCIATED (1)
#define OPERATING (6)
/**
 * The MDSStatus values have the following meaning:
 * DISCONNECTED: The IntelliVue monitor is not connected to the network.
 * UNASSOCIATED: The IntelliVue monitor is connected to the network, but no
 * association is currently active.
 * OPERATING: The IntelliVue monitor has an association with a Computer Client.
 * Currently, a Computer Client will only see the MDS Status OPERATING, if
 * the MDS has another Status, there is no association with a Computer Client.
 */
typedef uint16_t SaFixedValId;
#define SA_FIX_UNSPEC (0)
#define SA_FIX_INVALID_MASK (1)
#define SA_FIX_PACER_MASK (2)
#define SA_FIX_DEFIB_MARKER_MASK (3)
#define SA_FIX_SATURATION (4)
#define SA_FIX_QRS_MASK (5)

/**
 * SA_FIX_UNSPEC: Not specified.
 * SA_FIX_INVALID_MASK: Invalid sample mask.
 * SA_FIX_PACER_MASK: Pace pulse detected.
 * SA_FIX_DEFIB_MARKER_MASK: Defib marker in this sample.
 * SA_FIX_SATURATION: Indicates saturation condition in this sample.
 * (Note: despite the name, this is a mask as well.)
 * SA_FIX_QRS_MASK: Indicates QRS trigger around this sample.
 * The sa_fixed_val may be a value or a bit mask, as indicated in the
 * sa_fixed_val_id.
 */


typedef struct
{
  SaFixedValId sa_fixed_val_id;
  uint16_t sa_fixed_val;
} SaFixedValSpecEntry16;


/// The Sample Array Fixed Value Specification defines a list of fixed sample
/// values or bit masks that indicate specific conditions

typedef struct
{
  uint16_t count;
  uint16_t length;
  SaFixedValSpecEntry16* value;
} SaFixedValSpec16;


/// The Time Periodic Data Poll attribute allows to request periodic Poll
/// Replies for a given time.

typedef struct
{
  RelativeTime active_period;
} PollDataReqPeriod;
/// The active_period specifies the time for which the IntelliVue monitor
/// will send periodic Poll Replies.

typedef uint16_t PtBsaFormula;
#define BSA_FORMULA_UNSPEC (0)
#define BSA_FORMULA_BOYD (1)
#define BSA_FORMULA_DUBOIS (2)

/**
 * BSA_FORMULA_UNSPEC: Formula not specified
 * BSA_FORMULA_BOYD: BSA calculation according to Boyd
 * BDA_FORMULA_DUBOIS:: BSA calculation according to Dubois
 */


typedef struct
{
  ManagedObjectId system_pulse;
  ManagedObjectId alarm_source;
} SystemPulseInfo;

/// The MdsGenSysemInfoEntry allows to encode generic system information.

typedef struct
{
  uint16_t choice;
#define MDS_GEN_SYSTEM_INFO_SYSTEM_PULSE_CHOSEN (1)
  uint16_t length;
  uint8_t* value; /// placeholder for appended data
} MdsGenSystemInfoEntry;
/// One MdsGenSytemInfoEntry is used to encode the System Pulse information.
/// The monitor can generate a pulse rate from several sources.


/// The Mds General System Info attribute contains global information about
/// the monitor and its configuration

typedef struct
{
  uint16_t count;
  uint16_t length;
  MdsGenSystemInfoEntry* value;
} MdsGenSystemInfo;

/// command type
typedef uint16_t CMDType;
#define CMD_EVENT_REPORT (0)
#define CMD_CONFIRMED_EVENT_REPORT (1)
#define CMD_GET (3)
#define CMD_SET (4)
#define CMD_CONFIRMED_SET (5)
#define CMD_CONFIRMED_ACTION (7)


/// action type
#define NOM_NOTI_MDS_CREAT (3334)
/// MDS Create Notification
#define NOM_NOTI_CONN_INDIC (3351)
/// connect indication event type
#define NOM_ACT_POLL_MDIB_DATA (3094)
/// poll data action
#define NOM_ACT_POLL_MDIB_DATA_EXT (61755)
/// extended poll data action

typedef struct
{
  uint16_t poll_number;
  uint16_t sequence_no;
  RelativeTime rel_time_stamp;
  AbsoluteTime abs_time_stamp;
  TYPE polled_obj_type;
  OIDType polled_attr_grp;
  PollInfoList poll_info_list;
} PollMdibDataReplyExt;

typedef struct
{
  uint8_t state;
#define RORLS_FIRST (1) /// set in the first message
#define RORLS_NOT_FIRST_NOT_LAST (2)
#define RORLS_LAST (3) /// last RORLSapdu, one RORSapdu to follow
  uint8_t count; /// counter starts with 1
} RorlsId;

typedef struct
{
  RorlsId linked_id; /// see below
  uint16_t invoke_id; /// see below
  CMDType command_type; /// identifies type of command
  uint16_t length; /// no of bytes in rest of message
} ROLRSapdu;

typedef struct
{
  uint16_t invoke_id;
  uint16_t error_value;
#define NO_SUCH_OBJECT_CLASS (0)
#define NO_SUCH_OBJECT_INSTANCE (1)
#define ACCESS_DENIED (2)
#define GET_LIST_ERROR (7)
#define SET_LIST_ERROR (8)
#define NO_SUCH_ACTION (9)
#define PROCESSING_FAILURE (10)
#define INVALID_ARGUMENT_VALUE (15)
#define INVALID_SCOPE (16)
#define INVALID_OBJECT_INSTANCE (17)
  uint16_t length;
} ROERapdu;


typedef uint16_t ErrorStatus;
#define ATTR_ACCESS_DENIED (2)
#define ATTR_NO_SUCH_ATTRIBUTE (5)
#define ATTR_INVALID_ATTRIBUTE_VALUE (6)
#define ATTR_INVALID_OPERATION (24)
#define ATTR_INVALID_OPERATOR (25)

typedef struct
{
  ErrorStatus errorStatus;
  OIDType attributeId;
} GetError;

typedef struct
{
  ManagedObjectId managed_object;

  struct
  {
    uint16_t count;
    uint16_t length;
    GetError* value;
  } getInfoList;
} GetListError;

typedef struct
{
  OIDType error_id;
  uint16_t length;
} ProcessingFailure;


typedef uint16_t ModifyOperator;
#define REPLACE (0)
#define ADD_VALUES (1)
#define REMOVE_VALUES (2)
#define SET_TO_DEFAULT (3)

typedef struct
{
  ErrorStatus errorStatus;
  ModifyOperator modifyOperator;
  OIDType attributeId;
} SetError;

typedef struct
{
  ManagedObjectId managed_object;

  struct
  {
    uint16_t count;
    uint16_t length;
    SetError value[1];
  } setInfoList;
} SetListError;

typedef struct
{
  ManagedObjectId managed_object;
  AttributeList attributeList;
} SetResult;

typedef struct
{
  ManagedObjectId managed_object;
  AttributeList attributeList;
} GetResult;

typedef struct
{
  uint16_t count;
  uint16_t length;
  OIDType value[1];
} AttributeIdList;

typedef struct
{
  ManagedObjectId managed_object;
  uint32_t scope;
  AttributeIdList attributeIdList;
} GetArgument;


typedef uint16_t ModifyOperator;
#define REPLACE (0)
#define ADD_VALUES (1)
#define REMOVE_VALUES (2)
#define SET_TO_DEFAULT (3)

typedef struct
{
  ModifyOperator modifyOperator;
  AVAType attribute;
} AttributeModEntry;

typedef struct
{
  uint16_t count;
  uint16_t length;
  AttributeModEntry value[1];
} ModificationList;

typedef struct
{
  ManagedObjectId managed_object;
  uint32_t scope;
  ModificationList modificationList;
} SetArgument;

typedef struct
{
  ManagedObjectId managed_object; /// addressed object
  uint32_t scope; /// fixed value 0
  OIDType action_type; /// identification of method
  uint16_t length; /// size of appended data
} ActionArgument;

typedef struct
{
  ManagedObjectId managed_object;
  AttributeList attribute_list;
} MdsCreateInfo;

typedef struct
{
  uint16_t poll_number;
  TYPE polled_obj_type;
  OIDType polled_attr_grp;
  AttributeList poll_ext_attr;
} PollMdibDataReqExt;


/// The array_size specifies the maximum number of samples in one observed
/// value.
/**
 * Attribute IDs
 * (Programming Guide, page 167)
 * Attribute ID specifies the type of an attribute in the AttributeList.
 * The IDs derive from the Object Oriented Elements partition.
 * Ignore unknown attributes.
 */

/// Device P-Alarm List
#define NOM_ATTR_AL_MON_P_AL_LIST (0x0902)

/// Device T-Alarm List
#define NOM_ATTR_AL_MON_T_AL_LIST (0x0904)

/// Altitude
#define NOM_ATTR_ALTITUDE (0x090C)

/// Application Area
#define NOM_ATTR_AREA_APPL (0x090D)

/// Color
#define NOM_ATTR_COLOR (0x0911)

/// Device Alert Condition
#define NOM_ATTR_DEV_AL_COND (0x0916)

/// Display Resolution
#define NOM_ATTR_DISP_RES (0x0917)

/// Visual Grid
#define NOM_ATTR_GRID_VIS_I16 (0x091A)

/// Association Invoke Id
#define NOM_ATTR_ID_ASSOC_NO (0x091D)

/// Bed Label
#define NOM_ATTR_ID_BED_LABEL (0x091E)

/// Object Handle
#define NOM_ATTR_ID_HANDLE (0x0921)

/// Label
#define NOM_ATTR_ID_LABEL (0x0924)

/// Label String
#define NOM_ATTR_ID_LABEL_STRING (0x0927)

/// System Model
#define NOM_ATTR_ID_MODEL (0x0928)

/// Product Specification
#define NOM_ATTR_ID_PROD_SPECN (0x092D)

/// Object Type
#define NOM_ATTR_ID_TYPE (0x092F)

/// Line Frequency
#define NOM_ATTR_LINE_FREQ (0x0935)

/// System Localization
#define NOM_ATTR_LOCALIZN (0x0937)

/// Metric Info Label
#define NOM_ATTR_METRIC_INFO_LABEL (0x093C)

/// Metric Info Label String
#define NOM_ATTR_METRIC_INFO_LABEL_STR (0x093D)

/// Metric Specification
#define NOM_ATTR_METRIC_SPECN (0x093F)

/// Metric State
#define NOM_ATTR_METRIC_STAT (0x0940)

/// Measure Mode
#define NOM_ATTR_MODE_MSMT (0x0945)

/// Operating Mode
#define NOM_ATTR_MODE_OP (0x0946)

/// Nomenclature Version
#define NOM_ATTR_NOM_VERS (0x0948)

/// Compound Numeric Observed Value
#define NOM_ATTR_NU_CMPD_VAL_OBS (0x094B)

/// Numeric Observed Value
#define NOM_ATTR_NU_VAL_OBS (0x0950)

/// Patient BSA
#define NOM_ATTR_PT_BSA (0x0956)

/// Pat Demo State
#define NOM_ATTR_PT_DEMOG_ST (0x0957)

/// Patient Date of Birth
#define NOM_ATTR_PT_DOB (0x0958)

/// Patient ID
#define NOM_ATTR_PT_ID (0x095A)

/// Family Name
#define NOM_ATTR_PT_NAME_FAMILY (0x095C)

/// Given Name
#define NOM_ATTR_PT_NAME_GIVEN (0x095D)

/// Patient Sex
#define NOM_ATTR_PT_SEX (0x0961)

/// Patient Type
#define NOM_ATTR_PT_TYPE (0x0962)

/// Sample Array Calibration Specification
#define NOM_ATTR_SA_CALIB_I16 (0x0964)

/// Compound Sample Array Observed Value
#define NOM_ATTR_SA_CMPD_VAL_OBS (0x0967)

/// Sample Array Physiological Range
#define NOM_ATTR_SA_RANGE_PHYS_I16 (0x096A)

/// Sample Array Specification
#define NOM_ATTR_SA_SPECN (0x096D)

/// Sample Array Observed Value
#define NOM_ATTR_SA_VAL_OBS (0x096E)

/// Scale and Range Specification
#define NOM_ATTR_SCALE_SPECN_I16 (0x096F)

/// Safety Standard
#define NOM_ATTR_STD_SAFETY (0x0982)

/// System ID
#define NOM_ATTR_SYS_ID (0x0984)

/// System Specification
#define NOM_ATTR_SYS_SPECN (0x0985)

/// System Type
#define NOM_ATTR_SYS_TYPE (0x0986)

/// Date and Time
#define NOM_ATTR_TIME_ABS (0x0987)

/// Sample Period
#define NOM_ATTR_TIME_PD_SAMP (0x098D)

/// Relative Time
#define NOM_ATTR_TIME_REL (0x098F)

/// Absolute Time Stamp
#define NOM_ATTR_TIME_STAMP_ABS (0x0990)

/// Relative Time Stamp
#define NOM_ATTR_TIME_STAMP_REL (0x0991)

/// Unit Code
#define NOM_ATTR_UNIT_CODE (0x0996)

// Enumeration Observed Value
#define NOM_ATTR_VAL_ENUM_OBS (0x099E)

/// MDS Status
#define NOM_ATTR_VMS_MDS_STAT (0x09A7)

/// Patient Age
#define NOM_ATTR_PT_AGE (0x09D8)

/// Patient Height
#define NOM_ATTR_PT_HEIGHT (0x09DC)

/// Patient Weight
#define NOM_ATTR_PT_WEIGHT (0x09DF)

/// Sample Array Fixed Values Specification
#define NOM_ATTR_SA_FIXED_VAL_SPECN (0x0A16)

/// Patient Paced Mode
#define NOM_ATTR_PT_PACED_MODE (0x0A1E)

/// Internal Patient ID
#define NOM_ATTR_PT_ID_INT (0xF001)

/// Private Attribute
#define NOM_SAT_O2_TONE_FREQ (0xF008)

/// Private Attribute
#define NOM_ATTR_CMPD_REF_LIST (0xF009)

/// IP Address Information
#define NOM_ATTR_NET_ADDR_INFO (0xF100)

/// Protocol Support
#define NOM_ATTR_PCOL_SUPPORT (0xF101)

/// Notes1
#define NOM_ATTR_PT_NOTES1 (0xF129)

/// Notes2
#define NOM_ATTR_PT_NOTES2 (0xF12A)

/// Time for Periodic Polling
#define NOM_ATTR_TIME_PD_POLL (0xF13E)

/// Patient BSA Formula
#define NOM_ATTR_PT_BSA_FORMULA (0xF1EC)

/// Mds General System Info
#define NOM_ATTR_MDS_GEN_INFO (0xF1FA)

/// no of prioritized objects for poll request
#define NOM_ATTR_POLL_OBJ_PRIO_NUM (0xF228)

/// Numeric Object Priority List
#define NOM_ATTR_POLL_NU_PRIO_LIST (0xF239)

/// Wave Object Priority List
#define NOM_ATTR_POLL_RTSA_PRIO_LIST (0xF23A)

/// Metric Modality
#define NOM_ATTR_METRIC_MODALITY (0xF294)


/// Attribute Groups in which attributes are arranged

/// Alert Monitor Group
#define NOM_ATTR_GRP_AL_MON (0x0801)

/// Metric Observed Value Group
#define NOM_ATTR_GRP_METRIC_VAL_OBS (0x0803)

/// Patient Demographics Attribute Group
#define NOM_ATTR_GRP_PT_DEMOG (0x0807)

/// System Application Attribute Group
#define NOM_ATTR_GRP_SYS_APPL (0x080A)

/// System Identification Attribute Group
#define NOM_ATTR_GRP_SYS_ID (0x080B)

/// System Production Attribute Group
#define NOM_ATTR_GRP_SYS_PROD (0x080C)

/// VMO Dynamic Attribute Group
#define NOM_ATTR_GRP_VMO_DYN (0x0810)

/// VMO Static Attribute Group
#define NOM_ATTR_GRP_VMO_STATIC (0x0811)


/**
 * Component IDs
 *
 * Component IDs specify system components such as entries in the Production
 * Specification attribute of the Medical Device Service object. A Component ID
 * is a PrivateOid and is not assigned to any nomenclature partition.
 */
/// for the overall product
#define ID_COMP_PRODUCT (0x0008)

/// for the specific bundle
#define ID_COMP_CONFIG (0x0010)

/// for the boot code
#define ID_COMP_BOOT (0x0018)

/// mainboard component
#define ID_COMP_MAIN_BD (0x0050)

/// application software component
#define ID_COMP_APPL_SW (0x0058)


/**
 * Unit Codes
 *
 * Unit Codes describe the dimension of a physiological measurement.
 * They are grouped in the Units partition.
 */
/// NOS (no dimension)
#define NOM_DIM_NOS (0x0000)

/// /
#define NOM_DIM_DIV (0x0002)

/// - (no dimension)
#define NOM_DIM_DIMLESS (0x0200)

/// % (percentage)
#define NOM_DIM_PERCENT (0x0220)

/// ppth (parts per thousand)
#define NOM_DIM_PARTS_PER_THOUSAND (0x0240)

/// ppm (parts per million)
#define NOM_DIM_PARTS_PER_MILLION (0x0260)

/// mol/mol (mole per mole)
#define NOM_DIM_X_MOLE_PER_MOLE (0x0360)

/// ppb (parts per billion)
#define NOM_DIM_PARTS_PER_BILLION (0x02A0)

/// ppt (parts per trillion)
#define NOM_DIM_PARTS_PER_TRILLION (0x02C0)

/// pH
#define NOM_DIM_PH (0x03E0)

/// drop (vital signs count drop)
#define NOM_DIM_DROP (0x0400)

/// rbc (vital signs count red blood cells)
#define NOM_DIM_RBC (0x0420)

/// beat (vital signs count beat)
#define NOM_DIM_BEAT (0x0440)

/// breath (vital signs count breath)
#define NOM_DIM_BREATH (0x0460)

/// cell (vital signs count cells)
#define NOM_DIM_CELL (0x0480)

/// cough (vital signs count cough)
#define NOM_DIM_COUGH (0x04A0)

/// sigh (vital signs count sigh)
#define NOM_DIM_SIGH (0x04C0)

/// %PCV (percent of packed cell volume)
#define NOM_DIM_PCT_PCV (0x04E0)

/// m (meter)
#define NOM_DIM_X_M (0x0500)

/// cm (centimeter)
#define NOM_DIM_CENTI_M (0x0511)

/// mm (millimeter)
#define NOM_DIM_MILLI_M (0x0512)

/// um (micro-meter)
#define NOM_DIM_MICRO_M (0x0513)

/// in (inch)
#define NOM_DIM_X_INCH (0x0560)

/// ml/m2 (used e.g. for SI and ITBVI)
#define NOM_DIM_MILLI_L_PER_M_SQ (0x0592)

/// /m (per meter)
#define NOM_DIM_PER_X_M (0x05A0)

/// /mm (per millimeter)
#define NOM_DIM_PER_MILLI_M (0x05B2)

/// m2 (used e.g. for BSA calculation)
#define NOM_DIM_SQ_X_M (0x05C0)

/// in2 (used e.g. for BSA calculation)
#define NOM_DIM_SQ_X_INCH (0x05E0)

/// m3 (cubic meter)
#define NOM_DIM_CUBIC_X_M (0x0620)

/// cm3 (cubic centimeter)
#define NOM_DIM_CUBIC_CENTI_M (0x0631)

/// l (liter)
#define NOM_DIM_X_L (0x0640)

/// ml (milli-liters, used e.g. for EVLW, ITBV, SV)
#define NOM_DIM_MILLI_L (0x0652)

/// ml/breath (milli-liter per breath)
#define NOM_DIM_MILLI_L_PER_BREATH (0x0672)

/// /cm3 (per cubic centimeter)
#define NOM_DIM_PER_CUBIC_CENTI_M (0x0691)

/// /l (per liter)
#define NOM_DIM_PER_X_L (0x06A0)

/// 1/nl (per nano-liter)
#define NOM_DIM_PER_NANO_LITER (0x06B4)

/// g (gram)
#define NOM_DIM_X_G (0x06C0)

/// kg (kilo-gram)
#define NOM_DIM_KILO_G (0x06C3)

/// mg (milli-gram)
#define NOM_DIM_MILLI_G (0x06D2)

/// ug (micro-gram)
#define NOM_DIM_MICRO_G (0x06D3)

/// ng (nono-gram)
#define NOM_DIM_NANO_G (0x06D4)

/// lb (pound)
#define NOM_DIM_X_LB (0x06E0)

/// oz (ounce)
#define NOM_DIM_X_OZ (0x0700)

/// /g (per gram)
#define NOM_DIM_PER_X_G (0x0720)

/// g-m (used e.g. for LVSW, RVSW)
#define NOM_DIM_X_G_M (0x0740)

/// kg-m (used e.g. for RCW, LCW)
#define NOM_DIM_KILO_G_M (0x0743)

/// g-m/m2 (used e.g. for LVSWI and RVSWI)
#define NOM_DIM_X_G_M_PER_M_SQ (0x0760)

/// kg-m/m2 (used e.g. for LCWI and RCWI)
#define NOM_DIM_KILO_G_M_PER_M_SQ (0x0763)

/// kg-m2 (kilo-gram meter squared)
#define NOM_DIM_KILO_G_M_SQ (0x0783)

/// kg/m2 (kilo-gram per square meter)
#define NOM_DIM_KG_PER_M_SQ (0x07A3)

/// kg/m3 (kilo-gram per cubic meter)
#define NOM_DIM_KILO_G_PER_M_CUBE (0x07C3)

/// g/cm3 (gram per cubic meter)
#define NOM_DIM_X_G_PER_CM_CUBE (0x07E0)

/// mg/cm3 (milli-gram per cubic centimeter)
#define NOM_DIM_MILLI_G_PER_CM_CUBE (0x07F2)

/// ug/cm3 (micro-gram per cubic centimeter)
#define NOM_DIM_MICRO_G_PER_CM_CUBE (0x07F3)

/// ng/cm3 (nano-gram per cubic centimeter)
#define NOM_DIM_NANO_G_PER_CM_CUBE (0x07F4)

/// g/l (gram per liter)
#define NOM_DIM_X_G_PER_L (0x0800)

/// g/dl (used e.g. for Hb)
#define NOM_DIM_X_G_PER_DL (0x0840)

/// mg/dl (milli-gram per deciliter)
#define NOM_DIM_MILLI_G_PER_DL (0x0852)

/// g/ml (gram per milli-liter)
#define NOM_DIM_X_G_PER_ML (0x0860)

/// mg/ml (milli-gram per milli-liter)
#define NOM_DIM_MILLI_G_PER_ML (0x0872)

/// ug/ml (micro-gram per milli-liter)
#define NOM_DIM_MICRO_G_PER_ML (0x0873)

/// ng/ml (nano-gram per milli-liter)
#define NOM_DIM_NANO_G_PER_ML (0x0874)

/// sec (seconds)
#define NOM_DIM_SEC (0x0880)

/// msec (milli-seconds)
#define NOM_DIM_MILLI_SEC (0x0892)

/// usec (micro-seconds)
#define NOM_DIM_MICRO_SEC (0x0893)

/// min (minutes)
#define NOM_DIM_MIN (0x08A0)

/// hrs (hours)
#define NOM_DIM_HR (0x08C0)

/// days (days)
#define NOM_DIM_DAY (0x08E0)

/// weeks (weeks)
#define NOM_DIM_WEEKS (0x0900)

/// months (months)
#define NOM_DIM_MON (0x0920)

/// years (years)
#define NOM_DIM_YR (0x0940)

/// TOD (time of day)
#define NOM_DIM_TOD (0x0960)

/// date (date)
#define NOM_DIM_DATE (0x0980)

/// /sec (per second)
#define NOM_DIM_PER_X_SEC (0x09A0)

/// Hz (hertz)
#define NOM_DIM_HZ (0x09C0)

/// /min (per minute, used e.g. for the PVC count numerical value)
#define NOM_DIM_PER_MIN (0x09E0)

/// /hour (per hour)
#define NOM_DIM_PER_HR (0x0A00)

/// /day (per day)
#define NOM_DIM_PER_DAY (0x0A20)

/// /week (per week)
#define NOM_DIM_PER_WK (0x0A40)

/// /month (per month)
#define NOM_DIM_PER_MO (0x0A60)

/// /year (per year)
#define NOM_DIM_PER_YR (0x0A80)

/// bpm (beats per minute, used e.g. for HR/PULSE)
#define NOM_DIM_BEAT_PER_MIN (0x0AA0)

/// puls/min (puls per minute)
#define NOM_DIM_PULS_PER_MIN (0x0AC0)

/// rpm (respiration breathes per minute)
#define NOM_DIM_RESP_PER_MIN (0x0AE0)

/// m/sec (meter per second)
#define NOM_DIM_X_M_PER_SEC (0x0B00)

/// mm/sec (speed for recordings)
#define NOM_DIM_MILLI_M_PER_SEC (0x0B12)

/// l/min/m2 (used for CI)
#define NOM_DIM_X_L_PER_MIN_PER_M_SQ (0x0B20)

/// ml/min/m2 (used for DO2I, VO2I, O2AVI)
#define NOM_DIM_MILLI_L_PER_MIN_PER_M_SQ (0x0B32)

/// m2/sec (square meter per second)
#define NOM_DIM_SQ_X_M_PER_SEC (0x0B40)

/// cm2/sec (square centimeter per second)
#define NOM_DIM_SQ_CENTI_M_PER_SEC (0x0B51)

/// m3/sec (cubic meter per second)
#define NOM_DIM_CUBIC_X_M_PER_SEC (0x0B60)

/// cm3/sec (cubic centimeter per second)
#define NOM_DIM_CUBIC_CENTI_M_PER_SEC (0x0B71)

/// l/sec (liter per second)
#define NOM_DIM_X_L_PER_SEC (0x0BE0)

/// l/min (liter per minutes, used e.g. for MINVOL)
#define NOM_DIM_X_L_PER_MIN (0x0C00)

/// dl/min (deciliter per second)
#define NOM_DIM_DECI_L_PER_MIN (0x0C10)

/// ml/min (used for DO2, VO2, ALVENT)
#define NOM_DIM_MILLI_L_PER_MIN (0x0C12)

/// l/hour (liter per hour)
#define NOM_DIM_X_L_PER_HR (0x0C20)

/// ml/hour (milli-liter per hour)
#define NOM_DIM_MILLI_L_PER_HR (0x0C32)

/// l/day (liter per day)
#define NOM_DIM_X_L_PER_DAY (0x0C40)

/// ml/day (milli-liter per day)
#define NOM_DIM_MILLI_L_PER_DAY (0x0C52)

/// ml/kg (used e.g. for EVLWI)
#define NOM_DIM_MILLI_L_PER_KG (0x0C72)

/// kg/sec (kilo-gram per second)
#define NOM_DIM_KILO_G_PER_SEC (0x0CE3)

/// g/min (gram per minute)
#define NOM_DIM_X_G_PER_MIN (0x0D00)

/// kg/min (kilo-gram per minute)
#define NOM_DIM_KILO_G_PER_MIN (0x0D03)

/// mg/min (milli-gram per minute)
#define NOM_DIM_MILLI_G_PER_MIN (0x0D12)

/// ug/min (micro-gram per minute)
#define NOM_DIM_MICRO_G_PER_MIN (0x0D13)

/// ng/min (nano-gram per minute)
#define NOM_DIM_NANO_G_PER_MIN (0x0D14)

/// g/hour (gram per hour)
#define NOM_DIM_X_G_PER_HR (0x0D20)

/// kg/hour (kilo-gram per hour)
#define NOM_DIM_KILO_G_PER_HR (0x0D23)

/// mg/hour (milli-gram per hour)
#define NOM_DIM_MILLI_G_PER_HR (0x0D32)

/// ug/hour (micro-gram per hour)
#define NOM_DIM_MICRO_G_PER_HR (0x0D33)

/// ng/hr (nano-gram per hour)
#define NOM_DIM_NANO_G_PER_HR (0x0D34)

/// kg/day (kilo-gram per day)
#define NOM_DIM_KILO_G_PER_DAY (0x0D43)

/// g/kg/min (gram per kilo-gram per minute)
#define NOM_DIM_X_G_PER_KG_PER_MIN (0x0D80)

/// mg/kg/min (milli-gram per kilo-gram per minute)
#define NOM_DIM_MILLI_G_PER_KG_PER_MIN (0x0D92)

/// ug/kg/min (micro-gram per kilo-gram per minute)
#define NOM_DIM_MICRO_G_PER_KG_PER_MIN (0x0D93)

/// ng/kg/min (nano-gram per kilo-gram per minute)
#define NOM_DIM_NANO_G_PER_KG_PER_MIN (0x0D94)

/// g/kg/hour (gram per kilo-gram per hour)
#define NOM_DIM_X_G_PER_KG_PER_HR (0x0DA0)

/// mg/kg/hour (mili-gram per kilo-gram per hour)
#define NOM_DIM_MILLI_G_PER_KG_PER_HR (0x0DB2)

/// ug/kg/hour (micro-gram per kilo-gram per hour)
#define NOM_DIM_MICRO_G_PER_KG_PER_HR (0x0DB3)

/// ng/kg/hour (nano-gram per kilo-gram per hour)
#define NOM_DIM_NANO_G_PER_KG_PER_HR (0x0DB4)

/// kg/l/sec (kilo-gram per liter per second)
#define NOM_DIM_KILO_G_PER_L_SEC (0x0DE3)

/// kg/m/sec (kilo-gram per meter per second)
#define NOM_DIM_KILO_G_PER_M_PER_SEC (0x0E63)

/// kg-m/sec (kilo-gram meter per second)
#define NOM_DIM_KILO_G_M_PER_SEC (0x0E83)

/// N-s (newton seconds)
#define NOM_DIM_X_NEWTON_SEC (0x0EA0)

/// N (newton)
#define NOM_DIM_X_NEWTON (0x0EC0)

/// Pa (pascal)
#define NOM_DIM_X_PASCAL (0x0F00)

/// hPa (hekto-pascal)
#define NOM_DIM_HECTO_PASCAL (0x0F02)

/// kPa (kilo-pascal)
#define NOM_DIM_KILO_PASCAL (0x0F03)

/// mmHg (mm mercury)
#define NOM_DIM_MMHG (0x0F20)

/// cmH2O (centimeter H20)
#define NOM_DIM_CM_H2O (0x0F40)

/// mBar (milli-bar)
#define NOM_DIM_MILLI_BAR (0x0F72)

/// J (Joules)
#define NOM_DIM_X_JOULES (0x0F80)

/// eV (electronvolts)
#define NOM_DIM_EVOLT (0x0FA0)

/// W (watt)
#define NOM_DIM_X_WATT (0x0FC0)

/// mW (milli-watt)
#define NOM_DIM_MILLI_WATT (0x0FD2)

/// nW (nano-watt)
#define NOM_DIM_NANO_WATT (0x0FD4)

/// pW (pico-watt)
#define NOM_DIM_PICO_WATT (0x0FD5)

/// Dyn-sec/cm^5 (dyne second per cm^5)
#define NOM_DIM_X_DYNE_PER_SEC_PER_CM5 (0x1020)

/// A (ampere)
#define NOM_DIM_X_AMPS (0x1040)

/// mA (milli-ampere, used e.g. for the battery indications)
#define NOM_DIM_MILLI_AMPS (0x1052)

/// C (coulomb)
#define NOM_DIM_X_COULOMB (0x1060)

/// uC (micro-coulomb)
#define NOM_DIM_MICRO_COULOMB (0x1073)

/// V (volts)
#define NOM_DIM_X_VOLT (0x10A0)

/// mV (milli-volt)
#define NOM_DIM_MILLI_VOLT (0x10B2)

/// uV (micro-volt)
#define NOM_DIM_MICRO_VOLT (0x10B3)

/// Ohm
#define NOM_DIM_X_OHM (0x10C0)

/// kOhm (kilo-ohm)
#define NOM_DIM_OHM_K (0x10C3)

/// F (farad)
#define NOM_DIM_X_FARAD (0x1100)

/// Kelvin
#define NOM_DIM_KELVIN (0x1120)

/// Degree fahrenheit
#define NOM_DIM_FAHR (0x1140)

/// cd (candela)
#define NOM_DIM_X_CANDELA (0x1180)

/// mOsm (milli-osmole)
#define NOM_DIM_MILLI_OSM (0x11B2)

/// mol (mole)
#define NOM_DIM_X_MOLE (0x11C0)

/// mmol (milli-mole)
#define NOM_DIM_MILLI_MOLE (0x11D2)

/// mEq (milli-equivalents)
#define NOM_DIM_MILLI_EQUIV (0x11F2)

/// mOsm/l (milli-osmole per liter)
#define NOM_DIM_MILLI_OSM_PER_L (0x1212)

/// mmol/l (used for HB)
#define NOM_DIM_MILLI_MOLE_PER_L (0x1272)

/// umol/l (micro-mol per liter)
#define NOM_DIM_MICRO_MOLE_PER_L (0x1273)

/// mEq/l (milli-equivalents per liter)
#define NOM_DIM_MILLI_EQUIV_PER_L (0x12F2)

/// mEq/day (milli-equivalents per day)
#define NOM_DIM_MILLI_EQUIV_PER_DAY (0x1452)

/// i.u. (international unit)
#define NOM_DIM_X_INTL_UNIT (0x1560)

/// mi.u. (mili-international unit)
#define NOM_DIM_MILLI_INTL_UNIT (0x1572)

/// i.u./cm3 (international unit per cubic centimeter)
#define NOM_DIM_X_INTL_UNIT_PER_CM_CUBE (0x1580)

/// mi.u./cm3 (mili-international unit per cubic centimeter)
#define NOM_DIM_MILLI_INTL_UNIT_PER_CM_CUBE (0x1592)

/// i.u./ml (international unit per milli-liter)
#define NOM_DIM_X_INTL_UNIT_PER_ML (0x15E0)

/// i.u./min (international unit per minute)
#define NOM_DIM_X_INTL_UNIT_PER_MIN (0x1620)

/// mi.u./ml (milli-international unit per milli-liter)
#define NOM_DIM_MILLI_INTL_UNIT_PER_ML (0x15F2)

/// mi.u./min (milli-international unit per minute)
#define NOM_DIM_MILLI_INTL_UNIT_PER_MIN (0x1632)

/// i.u./hour (international unit per hour)
#define NOM_DIM_X_INTL_UNIT_PER_HR (0x1640)

/// mi.u./hour (milli-international unit per hour)
#define NOM_DIM_MILLI_INTL_UNIT_PER_HR (0x1652)

/// i.u./kg/min (international unit per kilo-gram per minute)
#define NOM_DIM_X_INTL_UNIT_PER_KG_PER_MIN (0x16A0)

/// mi.u./kg/min (milli-international unit per kilo-gram per minute)
#define NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_MIN (0x16B2)

/// i.u./kg/hour (international unit per kilo-gram per hour)
#define NOM_DIM_X_INTL_UNIT_PER_KG_PER_HR (0x16C0)

/// mi.u./kg/hour (milli-international unit per kilo-gram per hour)
#define NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_HR (0x16D2)

/// ml/cmH2O (milli-liter per centimeter H2O)
#define NOM_DIM_MILLI_L_PER_CM_H2O (0x1712)

/// cmH2O/l/sec (centimeter H2O per second)
#define NOM_DIM_CM_H2O_PER_L_PER_SEC (0x1720)

/// ml2/sec (milli-liter per second)
#define NOM_DIM_MILLI_L_SQ_PER_SEC (0x1752)

/// cmH2O/% (centimeter H2O per percent)
#define NOM_DIM_CM_H2O_PER_PERCENT (0x1760)

/// DS*m2/cm5 (used for SVRI and PVRI)
#define NOM_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5 (0x1780)

/// Degree celsius
#define NOM_DIM_DEGC (0x17A0)

/// cmH2O/l (centimeter H2O per liter)
#define NOM_DIM_CM_H2O_PER_L (0x1800)

/// mmHg/% (milli-meter mercury per percent)
#define NOM_DIM_MM_HG_PER_PERCENT (0x1820)

/// kPa/% (kilo-pascal per percent)
#define NOM_DIM_KILO_PA_PER_PERCENT (0x1843)

/// mAh (milli-ampere per hour, used e.g. for the battery indications)
#define NOM_DIM_MILLI_AMP_HR (0x17D2)

/// ml/dl (used for CaO2, CvO2, Ca-vO2)
#define NOM_DIM_MILLI_L_PER_DL (0x1912)

/// dB (decibel)
#define NOM_DIM_DECIBEL (0x1920)

/// g/mg (gram per milli-gram)
#define NOM_DIM_X_G_PER_MILLI_G (0x1940)

/// mg/mg (milli-gram per milli-gram)
#define NOM_DIM_MILLI_G_PER_MILLI_G (0x1952)

/// bpm/l (beats per minute per liter)
#define NOM_DIM_BEAT_PER_MIN_PER_X_L (0x1960)

/// bpm/ml (beats per minute per milli-liter)
#define NOM_DIM_BEAT_PER_MIN_PER_MILLI_L (0x1972)

/// 1/(min*l) (per minute per liter)
#define NOM_DIM_PER_X_L_PER_MIN (0x1980)

/// m/min (meter per minute)
#define NOM_DIM_X_M_PER_MIN (0x19A0)

/// cm/min (speed for recordings)
#define NOM_DIM_CENTI_M_PER_MIN (0x19B1)

/// complx
#define NOM_DIM_COMPLEX (0xF000)

/// count (count as a dimension)
#define NOM_DIM_COUNT (0xF001)

/// part (part)
#define NOM_DIM_PART (0xF002)

/// puls (puls)
#define NOM_DIM_PULS (0xF003)

/// uV p-p (micro-volt peak to peak)
#define NOM_DIM_UV_PP (0xF004)

/// uV2 (micro-volt square)
#define NOM_DIM_UV_SQ (0xF005)

/// lumen (lumen)
#define NOM_DIM_LUMEN (0xF007)

/// lb/in2 (pound per square inch)
#define NOM_DIM_LB_PER_INCH_SQ (0xF008)

#define NOM_DIM_ML_PER_SEC (61450)
#define NOM_DIM_BEAT_PER_MIN_PER_ML_C (61451)
#define NOM_DIM_X_MOLE_PER_HR (62176)
#define NOM_DIM_DECA_MOLE_PER_HR (62177)
#define NOM_DIM_HECTO_MOLE_PER_HR (62178)
#define NOM_DIM_KILO_MOLE_PER_HR (62179)
#define NOM_DIM_MEGA_MOLE_PER_HR (62180)
#define NOM_DIM_GIGA_MOLE_PER_HR (62181)
#define NOM_DIM_TERA_MOLE_PER_HR (62182)
#define NOM_DIM_PETA_MOLE_PER_HR (62183)
#define NOM_DIM_EXA_MOLE_PER_HR (62184)
#define NOM_DIM_ZETTA_MOLE_PER_HR (62185)
#define NOM_DIM_YOTTA_MOLE_PER_HR (62186)
#define NOM_DIM_DECI_MOLE_PER_HR (62192)
#define NOM_DIM_CENTI_MOLE_PER_HR (62193)
#define NOM_DIM_MILLI_MOLE_PER_HR (62194)
#define NOM_DIM_MICRO_MOLE_PER_HR (62195)
#define NOM_DIM_NANO_MOLE_PER_HR (62196)
#define NOM_DIM_PICO_MOLE_PER_HR (62197)
#define NOM_DIM_FEMTO_MOLE_PER_HR (62198)
#define NOM_DIM_ATTO_MOLE_PER_HR (62199)
#define NOM_DIM_ZEPTO_MOLE_PER_HR (62200)
#define NOM_DIM_YOCTO_MOLE_PER_HR (62201)
#define NOM_DIM_X_L_PER_BEAT (62208)
#define NOM_DIM_DECA_L_PER_BEAT (62209)
#define NOM_DIM_HECTO_L_PER_BEAT (62210)
#define NOM_DIM_KILO_L_PER_BEAT (62211)
#define NOM_DIM_MEGA_L_PER_BEAT (62212)
#define NOM_DIM_GIGA_L_PER_BEAT (62213)
#define NOM_DIM_TERA_L_PER_BEAT (62214)
#define NOM_DIM_PETA_L_PER_BEAT (62215)
#define NOM_DIM_EXA_L_PER_BEAT (62216)
#define NOM_DIM_ZETTA_L_PER_BEAT (62217)
#define NOM_DIM_YOTTA_L_PER_BEAT (62218)
#define NOM_DIM_DECI_L_PER_BEAT (62224)
#define NOM_DIM_CENTI_L_PER_BEAT (62225)
#define NOM_DIM_MILLI_L_PER_BEAT (62226)
#define NOM_DIM_MICRO_L_PER_BEAT (62227)
#define NOM_DIM_NANO_L_PER_BEAT (62228)
#define NOM_DIM_PICO_L_PER_BEAT (62229)
#define NOM_DIM_FEMTO_L_PER_BEAT (62230)
#define NOM_DIM_ATTO_L_PER_BEAT (62231)
#define NOM_DIM_ZEPTO_L_PER_BEAT (62232)
#define NOM_DIM_YOCTO_L_PER_BEAT (62233)

/**
 * Alert Codes
 *
 * The LSB of the alert codes identifies the source of an alert (refer to Alert
 * Monitor Object. If LSB is set to 1, the associated alert source is from the
 * object oriented nomenclature partition.
 */
/// The following code from the SCADA partition are used for the alert source:
#define NOM_ECG_LEAD_LA (21)
#define NOM_ECG_LEAD_RA (22)
#define NOM_ECG_LEAD_LL (23)
#define NOM_ECG_LEAD_C (66)
#define NOM_ECG_LEAD_C1FR (82)
#define NOM_ECG_LEAD_C2FR (83)
#define NOM_ECG_LEAD_C3FR (84)
#define NOM_ECG_LEAD_C4FR (85)
#define NOM_ECG_LEAD_C5FR (87)
#define NOM_ECG_LEAD_C6FR (88)
#define NOM_ECG_LEAD_ES (100)
#define NOM_ECG_LEAD_AS (101)
#define NOM_ECG_LEAD_AI (102)
#define NOM_ECG_LEAD_RL (115)
#define NOM_ECG_ELEC_POTL (256)
#define NOM_ECG_AMPL_ST (768)
#define NOM_ECG_AMPL_ST_I (769)
#define NOM_ECG_AMPL_ST_II (770)
#define NOM_ECG_AMPL_ST_V1 (771)
#define NOM_ECG_AMPL_ST_V2 (772)
#define NOM_ECG_AMPL_ST_V3 (773)
#define NOM_ECG_AMPL_ST_V4 (774)
#define NOM_ECG_AMPL_ST_V5 (775)
#define NOM_ECG_AMPL_ST_V6 (776)
#define NOM_ECG_AMPL_ST_III (829)
#define NOM_ECG_AMPL_ST_AVR (830)
#define NOM_ECG_AMPL_ST_AVL (831)
#define NOM_ECG_AMPL_ST_AVF (832)
#define NOM_ECG_AMPL_ST_V (835)
#define NOM_ECG_AMPL_ST_MCL (843)
#define NOM_ECG_CARD_BEAT_RATE (16770)
#define NOM_ECG_V_P_C_CNT (16993)
#define NOM_PULS_RATE (18442)
#define NOM_PLETH_PULS_RATE (18466)
#define NOM_RES_VASC_SYS_INDEX (18688)
#define NOM_PRESS_BLD (18944)
#define NOM_PRESS_BLD_SYS (18945)
#define NOM_PRESS_BLD_DIA (18946)
#define NOM_PRESS_BLD_MEAN (18947)
#define NOM_PRESS_BLD_NONINV (18948)
#define NOM_PRESS_BLD_NONINV_SYS (18949)
#define NOM_PRESS_BLD_NONINV_DIA (18950)
#define NOM_PRESS_BLD_NONINV_MEAN (18951)
#define NOM_PRESS_BLD_AORT (18956)
#define NOM_PRESS_BLD_AORT_SYS (18957)
#define NOM_PRESS_BLD_AORT_DIA (18958)
#define NOM_PRESS_BLD_AORT_MEAN (18959)
#define NOM_PRESS_BLD_ART (18960)
#define NOM_PRESS_BLD_ART_SYS (18961)
#define NOM_PRESS_BLD_ART_DIA (18962)
#define NOM_PRESS_BLD_ART_MEAN (18963)
#define NOM_PRESS_BLD_ART_ABP (18964)
#define NOM_PRESS_BLD_ART_ABP_SYS (18965)
#define NOM_PRESS_BLD_ART_ABP_DIA (18966)
#define NOM_PRESS_BLD_ART_ABP_MEAN (18967)
#define NOM_PRESS_BLD_ART_PULM (18972)
#define NOM_PRESS_BLD_ART_PULM_SYS (18973)
#define NOM_PRESS_BLD_ART_PULM_DIA (18974)
#define NOM_PRESS_BLD_ART_PULM_MEAN (18975)
#define NOM_PRESS_BLD_ART_UMB (18984)
#define NOM_PRESS_BLD_ART_UMB_SYS (18985)
#define NOM_PRESS_BLD_ART_UMB_DIA (18986)
#define NOM_PRESS_BLD_ART_UMB_MEAN (18987)
#define NOM_PRESS_BLD_ATR_LEFT (18992)
#define NOM_PRESS_BLD_ATR_LEFT_SYS (18993)
#define NOM_PRESS_BLD_ATR_LEFT_DIA (18994)
#define NOM_PRESS_BLD_ATR_LEFT_MEAN (18995)
#define NOM_PRESS_BLD_ATR_RIGHT (18996)
#define NOM_PRESS_BLD_ATR_RIGHT_SYS (18997)
#define NOM_PRESS_BLD_ATR_RIGHT_DIA (18998)
#define NOM_PRESS_BLD_ATR_RIGHT_MEAN (18999)
#define NOM_PRESS_BLD_VEN_CENT (19012)
#define NOM_PRESS_BLD_VEN_CENT_SYS (19013)
#define NOM_PRESS_BLD_VEN_CENT_DIA (19014)
#define NOM_PRESS_BLD_VEN_CENT_MEAN (19015)
#define NOM_PRESS_BLD_VEN_UMB (19016)
#define NOM_PRESS_BLD_VEN_UMB_SYS (19017)
#define NOM_PRESS_BLD_VEN_UMB_DIA (19018)
#define NOM_PRESS_BLD_VEN_UMB_MEAN (19019)
#define NOM_OUTPUT_CARD (19204)
#define NOM_RES_VASC_SYS (19240)
#define NOM_SAT_O2_VEN (19260)
#define NOM_TEMP (19272)
#define NOM_SETT_TEMP (19272)
#define NOM_TEMP_ART (19280)
#define NOM_TEMP_CORE (19296)
#define NOM_TEMP_ESOPH (19300)
#define NOM_TEMP_NASOPH (19308)
#define NOM_TEMP_SKIN (19316)
#define NOM_TEMP_VEN (19324)
#define NOM_PULS_OXIM_SAT_O2 (19384)
#define NOM_PULS_OXIM_SAT_O2_DIFF (19396)
#define NOM_PULS_OXIM_SAT_O2_ART_LEFT (19400)
#define NOM_PULS_OXIM_SAT_O2_ART_RIGHT (19404)
#define NOM_OUTPUT_CARD_CTS (19420)
#define NOM_RESP (20480)
#define NOM_RESP_RATE (20490)
#define NOM_AWAY_RESP_RATE (20498)
#define NOM_AWAY_CO2 (20652)
#define NOM_AWAY_CO2_ET (20656)
#define NOM_AWAY_CO2_INSP_MIN (20666)
#define NOM_CO2_TCUT (20684)
#define NOM_O2_TCUT (20688)
#define NOM_CONC_AWAY_O2 (20836)
#define NOM_CONC_AWAY_DESFL (20952)
#define NOM_CONC_AWAY_ENFL (20956)
#define NOM_CONC_AWAY_HALOTH (20960)
#define NOM_CONC_AWAY_SEVOFL (20964)
#define NOM_CONC_AWAY_ISOFL (20968)
#define NOM_CONC_AWAY_N2O (20976)
#define NOM_CONC_AWAY_DESFL_ET (21012)
#define NOM_CONC_AWAY_ENFL_ET (21016)
#define NOM_CONC_AWAY_HALOTH_ET (21020)
#define NOM_CONC_AWAY_SEVOFL_ET (21024)
#define NOM_CONC_AWAY_ISOFL_ET (21028)
#define NOM_CONC_AWAY_DESFL_INSP (21096)
#define NOM_CONC_AWAY_ENFL_INSP (21100)
#define NOM_CONC_AWAY_HALOTH_INSP (21104)
#define NOM_CONC_AWAY_SEVOFL_INSP (21108)
#define NOM_CONC_AWAY_ISOFL_INSP (21112)
#define NOM_CONC_AWAY_N2O_INSP (21120)
#define NOM_CONC_AWAY_O2_INSP (21124)
#define NOM_CONC_AWAY_N2 (21372)
#define NOM_CONC_AWAY_AGENT (21384)
#define NOM_CONC_AWAY_AGENT_ET (21388)
#define NOM_CONC_AWAY_AGENT_INSP (21392)
#define NOM_PRESS_CEREB_PERF (22532)
#define NOM_PRESS_INTRA_CRAN (22536)
#define NOM_PRESS_INTRA_CRAN_SYS (22537)
#define NOM_PRESS_INTRA_CRAN_DIA (22538)
#define NOM_PRESS_INTRA_CRAN_MEAN (22539)
#define NOM_EEG_ELEC_POTL_CRTX (22828)
#define NOM_TEMP_RECT (57348)
#define NOM_TEMP_BLD (57364)
#define NOM_TEMP_DIFF (57368)
#define NOM_OUTPUT_CARD_INDEX_CTS (61511)
#define NOM_ELECTRODE_IMPED (61515)
#define NOM_EEG_BIS_SIG_QUAL_INDEX (61517)
#define NOM_EEG_BISPECTRAL_INDEX (61518)
#define NOM_GAS_TCUT (61521)
#define NOM_SAT_DIFF_O2_ART_VEN (61548)
#define NOM_RATE_DIFF_CARD_BEAT_PULSE (61560)

/// The following codes are from the object oriented partition
/// are used for the alert source
#define NOM_MOC_VMS_MDS (33)
#define NOM_DEV_SYS_MULTI_MODAL_MDS (4493)
#define NOM_DEV_ANALY_CONC_GAS_MULTI_PARAM_VMD (4114)
#define NOM_DEV_ANALY_CARD_OUTPUT_VMD (4134)
#define NOM_OBJ_HIF_KEY (61584)
#define NOM_OBJ_SETTING (61649)
#define NOM_OBJ_INPUT_DEV (61692)
#define NOM_OBJ_NETWORK (61693)
#define NOM_OBJ_QUICKLINK (61694)
#define NOM_OBJ_SPEAKER (61695)
#define NOM_DEV_ANALY_BISPECTRAL_INDEX_VMD (61806)
#define NOM_OBJ_SENSOR (61902)
#define NOM_OBJ_XDUCR (61903)
#define NOM_OBJ_CHAN_1 (61916)
#define NOM_OBJ_CHAN_2 (61917)
#define NOM_OBJ_HIF_MOUSE (61983)
#define NOM_OBJ_HIF_TOUCH (61984)
#define NOM_OBJ_HIF_SPEEDPOINT (61985)
#define NOM_OBJ_HIF_ALARMBOX (61986)
#define NOM_OBJ_BUS_I2C (61987)
#define NOM_OBJ_CPU_SEC (61988)
#define NOM_OBJ_LED (61990)
#define NOM_OBJ_RELAY (61991)

/// The following codes are from the event partition
#define NOM_EVT_ABSENT (4)
#define NOM_EVT_CONTAM (14)
#define NOM_EVT_DISCONN (22)
#define NOM_EVT_DISTURB (24)
#define NOM_EVT_ERRATIC (32)
#define NOM_EVT_EXH (36)
#define NOM_EVT_HI (40)
#define NOM_EVT_IRREG (58)
#define NOM_EVT_LO (62)
#define NOM_EVT_MALF (70)
#define NOM_EVT_NOISY (74)
#define NOM_EVT_OBSTRUC (80)
#define NOM_EVT_SUST (106)
#define NOM_EVT_UNDEF (112)
#define NOM_EVT_WARMING (124)
#define NOM_EVT_BREATH_ABSENT (136)
#define NOM_EVT_CALIB_FAIL (138)
#define NOM_EVT_CONFIG_ERR (142)
#define NOM_EVT_RANGE_ERR (164)
#define NOM_EVT_CUFF_NOT_DEFLATED (230)
#define NOM_EVT_CUFF_INFLAT_OVER (232)
#define NOM_EVT_EQUIP_MALF (242)
#define NOM_EVT_TUBE_OCCL (250)
#define NOM_EVT_GAS_AGENT_IDENT_MALF (258)
#define NOM_EVT_LEAD_DISCONN (268)
#define NOM_EVT_LEADS_OFF (274)
#define NOM_EVT_O2_SUPPLY_LO (296)
#define NOM_EVT_OPTIC_MODULE_ABSENT (298)
#define NOM_EVT_OPTIC_MODULE_DEFECT (300)
#define NOM_EVT_SENSOR_DISCONN (308)
#define NOM_EVT_SENSOR_MALF (310)
#define NOM_EVT_SW_VER_UNK (322)
#define NOM_EVT_TUBE_DISCONN (326)
#define NOM_EVT_TUBE_OBSTRUC (330)
#define NOM_EVT_XDUCR_DISCONN (336)
#define NOM_EVT_XDUCR_MALF (338)
#define NOM_EVT_INTENS_LIGHT_ERR (350)
#define NOM_EVT_MSMT_DISCONN (352)
#define NOM_EVT_MSMT_ERR (354)
#define NOM_EVT_MSMT_FAIL (356)
#define NOM_EVT_MSMT_INOP (358)
#define NOM_EVT_MSMT_INTERRUP (362)
#define NOM_EVT_MSMT_RANGE_OVER (364)
#define NOM_EVT_MSMT_RANGE_UNDER (366)
#define NOM_EVT_SIG_LO (380)
#define NOM_EVT_SIG_UNANALYZEABLE (384)
#define NOM_EVT_TEMP_HI_GT_LIM (394)
#define NOM_EVT_UNSUPPORTED (400)
#define NOM_EVT_WAVE_ARTIF_ERR (432)
#define NOM_EVT_SIG_QUALITY (434)
#define NOM_EVT_MSMT_INTERF_ERR (436)
#define NOM_EVT_WAVE_OSCIL_ABSENT (442)
#define NOM_EVT_VOLTAGE_OUT_OF_RANGE (460)
#define NOM_EVT_INCOMPAT (600)
#define NOM_EVT_APNEA (3072)
#define NOM_EVT_ECG_ASYSTOLE (3076)
#define NOM_EVT_ECG_BEAT_MISSED (3078)
#define NOM_EVT_ECG_BIGEM (3082)
#define NOM_EVT_ECG_BRADY_EXTREME (3086)
#define NOM_EVT_ECG_PACING_NON_CAPT (3102)
#define NOM_EVT_ECG_PAUSE (3108)
#define NOM_EVT_ECG_TACHY_EXTREME (3122)
#define NOM_EVT_ECG_CARD_BEAT_RATE_IRREG (3158)
#define NOM_EVT_ECG_PACER_NOT_PACING (3182)
#define NOM_EVT_ECG_SV_TACHY (3192)
#define NOM_EVT_ECG_V_P_C_RonT (3206)
#define NOM_EVT_ECG_V_P_C_MULTIFORM (3208)
#define NOM_EVT_ECG_V_P_C_PAIR (3210)
#define NOM_EVT_ECG_V_P_C_RUN (3212)
#define NOM_EVT_ECG_V_RHY (3220)
#define NOM_EVT_ECG_V_TACHY (3224)
#define NOM_EVT_ECG_V_TACHY_NON_SUST (3226)
#define NOM_EVT_ECG_V_TRIGEM (3236)
#define NOM_EVT_DESAT (3246)
#define NOM_EVT_ECG_V_P_C_RATE (3252)
#define NOM_EVT_STAT_AL_OFF (6144)
#define NOM_EVT_STAT_CALIB_MODE (6152)
#define NOM_EVT_STAT_CALIB_RUNNING (6154)
#define NOM_EVT_STAT_CALIB_INVIVO_RUNNING (6156)
#define NOM_EVT_STAT_CALIB_LIGHT_RUNNING (6158)
#define NOM_EVT_STAT_CALIB_PREINS_RUNNING (6160)
#define NOM_EVT_STAT_SELFTEST_RUNNING (6164)
#define NOM_EVT_STAT_ZERO_RUNNING (6170)
#define NOM_EVT_STAT_OPT_MOD_SENSOR_CONN (6172)
#define NOM_EVT_STAT_OPT_MOD_SENSOR_WARMING (6174)
#define NOM_EVT_STAT_SENSOR_WARMING (6176)
#define NOM_EVT_STAT_ECG_AL_ALL_OFF (6182)
#define NOM_EVT_STAT_ECG_AL_SOME_OFF (6184)
#define NOM_EVT_STAT_LEARN (6224)
#define NOM_EVT_STAT_STANDBY (6228)
#define NOM_EVT_STAT_DISCONN (6256)
#define NOM_EVT_ADVIS_CHK (6658)
#define NOM_EVT_ADVIS_CALIB_REQD (6662)
#define NOM_EVT_ADVIS_CALIB_AND_ZERO_CHK (6664)
#define NOM_EVT_ADVIS_CONFIG_CHK (6666)
#define NOM_EVT_ADVIS_SETUP_CHK (6670)
#define NOM_EVT_ADVIS_SRC_CHK (6672)
#define NOM_EVT_ADVIS_CABLE_CHK (6680)
#define NOM_EVT_ADVIS_GAS_AGENT_CHK (6688)
#define NOM_EVT_ADVIS_SENSOR_CHK (6696)
#define NOM_EVT_ADVIS_GAIN_DECR (6704)
#define NOM_EVT_ADVIS_UNIT_CHK (6710)
#define NOM_EVT_ECG_V_FIB_TACHY (61444)
#define NOM_EVT_WAIT_CAL (61678)
#define NOM_EVT_ADVIS_CHANGE_SITE (61682)
#define NOM_EVT_ADVIS_CHECK_SITE_TIME (61684)
#define NOM_EVT_STAT_FW_UPDATE_IN_PROGRESS (61688)
#define NOM_EVT_EXT_DEV_AL_CODE_1 (61690)
#define NOM_EVT_EXT_DEV_AL_CODE_2 (61692)
#define NOM_EVT_EXT_DEV_AL_CODE_3 (61694)
#define NOM_EVT_EXT_DEV_AL_CODE_4 (61696)
#define NOM_EVT_EXT_DEV_AL_CODE_5 (61698)
#define NOM_EVT_EXT_DEV_AL_CODE_6 (61700)
#define NOM_EVT_EXT_DEV_AL_CODE_7 (61702)
#define NOM_EVT_EXT_DEV_AL_CODE_8 (61704)
#define NOM_EVT_EXT_DEV_AL_CODE_9 (61706)
#define NOM_EVT_EXT_DEV_AL_CODE_10 (61708)
#define NOM_EVT_EXT_DEV_AL_CODE_11 (61710)
#define NOM_EVT_EXT_DEV_AL_CODE_12 (61712)
#define NOM_EVT_EXT_DEV_AL_CODE_13 (61714)
#define NOM_EVT_EXT_DEV_AL_CODE_14 (61716)
#define NOM_EVT_EXT_DEV_AL_CODE_15 (61718)
#define NOM_EVT_EXT_DEV_AL_CODE_16 (61720)
#define NOM_EVT_EXT_DEV_AL_CODE_17 (61722)
#define NOM_EVT_EXT_DEV_AL_CODE_18 (61724)
#define NOM_EVT_EXT_DEV_AL_CODE_19 (61726)
#define NOM_EVT_EXT_DEV_AL_CODE_20 (61728)
#define NOM_EVT_EXT_DEV_AL_CODE_21 (61730)
#define NOM_EVT_EXT_DEV_AL_CODE_22 (61732)
#define NOM_EVT_EXT_DEV_AL_CODE_23 (61734)
#define NOM_EVT_EXT_DEV_AL_CODE_24 (61736)
#define NOM_EVT_EXT_DEV_AL_CODE_25 (61738)
#define NOM_EVT_EXT_DEV_AL_CODE_26 (61740)
#define NOM_EVT_EXT_DEV_AL_CODE_27 (61742)
#define NOM_EVT_EXT_DEV_AL_CODE_28 (61744)
#define NOM_EVT_EXT_DEV_AL_CODE_29 (61746)
#define NOM_EVT_EXT_DEV_AL_CODE_30 (61748)
#define NOM_EVT_EXT_DEV_AL_CODE_31 (61750)
#define NOM_EVT_EXT_DEV_AL_CODE_32 (61752)
#define NOM_EVT_EXT_DEV_AL_CODE_33 (61754)
#define NOM_EVT_ST_MULTI (61756)
#define NOM_EVT_ADVIS_BSA_REQD (61760)
#define NOM_EVT_ADVIS_PRESUMED_CVP (61762)
#define NOM_EVT_BRADY (61766)
#define NOM_EVT_TACHY (61768)
#define NOM_EVT_ADVIS_CHANGE_SCALE (61770)
#define NOM_EVT_MSMT_RESTART (61772)
#define NOM_EVT_TOO_MANY_AGENTS (61774)
#define NOM_EVT_STAT_PULSE_SRC_RANGE_OVER (61778)
#define NOM_EVT_STAT_PRESS_SRC_RANGE_OVER (61780)
#define NOM_EVT_MUSCLE_NOISE (61782)
#define NOM_EVT_LINE_NOISE (61784)
#define NOM_EVT_IMPED_HI (61786)
#define NOM_EVT_AGENT_MIX (61788)
#define NOM_EVT_IMPEDS_HI (61790)
#define NOM_EVT_ADVIS_PWR_HI (61792)
#define NOM_EVT_ADVIS_PWR_OFF (61794)
#define NOM_EVT_ADVIS_PWR_OVER (61796)
#define NOM_EVT_ADVIS_DEACT (61798)


/**
 * Partition IDs
 *
 * The following sections contain a list of identifiers which are used within
 * the IntelliVue monitor. Each identifier is unique within a given partition.
 */
#define NOM_PART_OBJ (1)
/// Object Oriented Elements
#define NOM_PART_SCADA (2)
/// Physiological Measurements
#define NOM_PART_EVT (3)
/// Events for Alerts
#define NOM_PART_DIM (4)
/// Units of Measurement
#define NOM_PART_PGRP (6)
/// Identification of Parameter Groups
#define NOM_PART_INFRASTRUCT (8)
/// Infrastructure Elements


/**
 * Object Classes
 *
 * The following IDs identify object types that exist within the Object
 * Oriented Elements partition.
 *
 * These objects may be the source of alerts (see Alert Monitor Object, pg 85)
 */
#define NOM_MOC_VMO_VMD (2)
/// Virtual Medical Device
#define NOM_MOC_VMO_CHAN (3)
/// Channel Object, used for grouping objects
#define NOM_MOC_VMO_METRIC_ENUM (5)
/// Enumeration Object, status/annotation information
#define NOM_MOC_VMO_METRIC_NU (6)
/// Numeric Object
#define NOM_MOC_VMO_METRIC_SA_RT (9)
/// Real Time Sample Array
#define NOM_MOC_VMS_MDS (33)
/// Medical Device Service Object
#define NOM_MOC_VMS_MDS_COMPOS_SINGLE_BED (35)
/// Composite Single Bed MDS (multiple MDS objects)
#define NOM_MOC_VMS_MDS_HYD (36)
/// Hydra Mds with multiple devices (VMDs)
#define NOM_MOC_VMS_MDS_SIMP (37)
/// Simple Mds with a single device (VMD)
#define NOM_MOC_LOG_ERR (39)
/// Status Log Object
#define NOM_MOC_BATT (41)
/// Battery Object
#define NOM_MOC_PT_DEMOG (42)
/// Patient Demographics Object
#define NOM_MOC_VMO_AL_MON (54)
/// Alert Monitor Object
#define NOM_MOC_VMO_PMSTORE (61)
/// Persistent Metric Store Object
#define NOM_MOC_PRINTER (74)
/// Printer Object
#define NOM_MOC_PT_DEMOG_MGR (75)
/// Patient Demographics Manager Object
#define NOM_DEV_ANALY_SAT_O2_VMD (4106)
/// SpO2 Device
#define NOM_DEV_ANALY_PRESS_BLD_VMD (4174)
/// Blood Pressure Device
#define NOM_DEV_ANALY_RESP_RATE_VMD (4186)
/// Respiration Rate Device
#define NOM_DEV_ECG_VMD (4262)
/// ECG Device
#define NOM_DEV_METER_TEMP_VMD (4366)
/// Temperature Device
#define NOM_DEV_MON_PHYSIO_MULTI_PARAM_MDS (4429)
/// Multi Parameter MDS
#define NOM_DEV_ANALY_SAT_O2_CHAN (4107)
/// SpO2 Channel
#define NOM_DEV_ANALY_AWAY_MULTI_PARAM_CHAN (4147)
/// Airway Gas Channel
#define NOM_DEV_ANALY_RESP_RATE_CHAN (4187)
/// Resp Rate Channel
#define NOM_DEV_ECG_CHAN (4263)
/// ECG Channel
#define NOM_DEV_METER_PRESS_BLD_CHAN (4319)
/// Blood Pressure Channel
#define NOM_DEV_METER_TEMP_CHAN (4367)
/// Temperature Channel
#define NOM_DEV_GENERAL_VMD (5122)
/// general Device
#define NOM_DEV_GENERAL_CHAN (5123)
/// General Channel
#define NOM_DEV_AUX_VMD (5126)
/// auxiliary VMD
#define NOM_DEV_ECG_RESP_VMD (5130)
/// ECG/Resp Device
#define NOM_DEV_ARRHY_VMD (5134)
/// Arrhythmia Analysis Device
#define NOM_DEV_PULS_VMD (5138)
/// Pulse Device
#define NOM_DEV_ST_VMD (5142)
/// ST Analysis Device
#define NOM_DEV_CO2_VMD (5146)
/// CO2 Device
#define NOM_DEV_PRESS_BLD_NONINV_VMD (5150)
/// NBP Device
#define NOM_DEV_TEMP_DIFF_VMD (5178)
/// Temperature Difference Device
#define NOM_DEV_CNTRL_VMD (5182)
/// Control Device
#define NOM_DEV_AL_VMD (5186)
/// Alarming Device
#define NOM_DEV_PMSTORE_VMD (5198)
/// Persistent Metric Store Device
#define NOM_DEV_ARRHY_CHAN (5135)
/// Arrhythmia Channel
#define NOM_DEV_PULS_CHAN (5139)
/// Pulse Channel
#define NOM_DEV_ST_CHAN (5143)
/// ST Channel
#define NOM_DEV_CO2_CHAN (5147)
/// CO2 Channel
#define NOM_DEV_TEMP_DIFF_CHAN (5179)
/// Temperature Difference Channel
#define NOM_DEV_PMSTORE_CHAN (5199)
/// Persistent Metric Store Channel
#define NOM_DEV_CARD_RATE_CHAN (5203)
/// Heart Rate Channel
#define NOM_DEV_SYS_VS_UNCONFIG_MDS (5213)
/// Unconfigurable Device System
#define NOM_OBJ_DISP (61616)
/// Display Object
#define NOM_OBJ_SOUND_GEN (61648)
/// Sound Generator Object
#define NOM_OBJ_SETTING (61649)
/// Device Settings Object
#define NOM_OBJ_EVENT (61683)
/// Event Object
#define NOM_VMD_CONFIG (61684)
/// Configuration Device
#define NOM_OBJ_BATT_CHARGER (61690)
/// Battery Charger Object
#define NOM_OBJ_ECG_OUT (61691)
/// ECG Output Object
#define NOM_OBJ_INPUT_DEV (61692)
/// Input Device Object
#define NOM_OBJ_NETWORK (61693)
/// Network Object
#define NOM_OBJ_QUICKLINK (61694)
/// Quicklink Bar Object
#define NOM_OBJ_SPEAKER (61695)
/// Speaker Object
#define NOM_OBJ_AUTO_LIMIT (61706)
/// Automatic Alarm Limits Object
#define NOM_OBJ_RECORDING (61709)
/// Recorder Object
#define NOM_OBJ_PUMP (61716)
/// NBP Pump Object
#define NOM_OBJ_IR (61717)
/// IR Transmitter Object

/**
 * Protocol Identification
 * The IDs for the protocol identification are from the Infrastructure
 * nomenclature partition.
 */
#define NOM_POLL_PROFILE_SUPPORT (1)
/// id for polling profile

#define NOM_MDIB_OBJ_SUPPORT (258)
/// supported objects for the active profile

#define NOM_ATTR_POLL_PROFILE_EXT (61441)
/// id for poll profile extensions opt. package



/// TextID's for Waves
#define NLS_NOM_ECG_ELEC_POTL (0x00020100)
#define NLS_NOM_ECG_ELEC_POTL_I (0x00020101)
#define NLS_NOM_ECG_ELEC_POTL_II (0x00020102)
#define NLS_NOM_ECG_ELEC_POTL_III (0x0002013d)
#define NLS_NOM_ECG_ELEC_POTL_AVR (0x0002013e)
#define NLS_NOM_ECG_ELEC_POTL_AVL (0x0002013f)
#define NLS_NOM_ECG_ELEC_POTL_AVF (0x00020140)
#define NLS_NOM_ECG_ELEC_POTL_V (0x00020143)
#define NLS_NOM_ECG_ELEC_POTL_MCL (0x0002014b)
#define NLS_NOM_ECG_ELEC_POTL_V1 (0x00020103)
#define NLS_NOM_ECG_ELEC_POTL_V2 (0x00020104)
#define NLS_NOM_ECG_ELEC_POTL_V3 (0x00020105)
#define NLS_NOM_ECG_ELEC_POTL_V4 (0x00020106)
#define NLS_NOM_ECG_ELEC_POTL_V5 (0x00020107)
#define NLS_NOM_ECG_ELEC_POTL_V6 (0x00020108)
#define NLS_NOM_ECG_ELEC_POTL_MCL1 (0x0002014c)
#define NLS_NOM_PULS_OXIM_PLETH (0x00024bb4)
#define NLS_NOM_PULS_OXIM_PLETH_LEFT (0x0002f08d)
#define NLS_NOM_PULS_OXIM_PLETH_RIGHT (0x0002f08c)
#define NLS_NOM_PRESS_INTRA_CRAN (0x00025808)
#define NLS_NOM_CONC_AWAY_O2 (0x00025164)
#define NLS_NOM_RESP (0x00025000)
#define NLS_NOM_FLOW_AWAY (0x000250d4)
#define NLS_NOM_PRESS_AWAY_INSP (0x00025108)
#define NLS_NOM_EEG_ELEC_POTL_CRTX (0x0002592c)
#define NLS_EEG_NAMES_EEG_CHAN1_LBL (0x800f5401)
#define NLS_EEG_NAMES_EEG_CHAN2_LBL (0x800f5402)
#define NLS_NOM_CONC_AWAY_AGENT (0x00025388)
#define NLS_NOM_EMFC_P1 (0x04010030)
#define NLS_NOM_EMFC_P2 (0x04010034)
#define NLS_NOM_EMFC_P3 (0x04010038)
#define NLS_NOM_EMFC_P4 (0x0401003c)
#define NLS_NOM_EMFC_P5 (0x04010400)
#define NLS_NOM_EMFC_P6 (0x04010404)
#define NLS_NOM_EMFC_P7 (0x04010408)
#define NLS_NOM_EMFC_P8 (0x0401040c)
#define NLS_NOM_EMFC_IUP (0x04010054)
#define NLS_NOM_EMFC_AUX (0x040100b4)
#define NLS_NOM_EMFC_AWV (0x04010668)
#define NLS_NOM_EMFC_L_V1 (0x04010764)
#define NLS_NOM_EMFC_L_V2 (0x04010768)
#define NLS_NOM_EMFC_L_V3 (0x0401076c)
#define NLS_NOM_EMFC_L_V4 (0x04010770)
#define NLS_NOM_EMFC_L_V5 (0x04010774)
#define NLS_NOM_EMFC_L_V6 (0x04010778)
#define NLS_NOM_EMFC_L_I (0x0401077c)
#define NLS_NOM_EMFC_L_II (0x04010780)
#define NLS_NOM_EMFC_L_III (0x04010784)
#define NLS_NOM_EMFC_L_aVR (0x04010788)
#define NLS_NOM_EMFC_L_aVL (0x0401078c)
#define NLS_NOM_EMFC_L_aVF (0x04010790)
#define NLS_NOM_EMFC_AWVex (0x04010794)
#define NLS_NOM_EMFC_PLETH2 (0x0401079c)
#define NLS_NOM_EMFC_LT_EEG (0x040107f0)
#define NLS_NOM_EMFC_RT_EEG (0x0401082c)
#define NLS_NOM_EMFC_BP (0x04010888)
#define NLS_NOM_EMFC_AGTs (0x04010ce4)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE1 (0x80aaf001)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE2 (0x80aaf003)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE3 (0x80aaf005)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE4 (0x80aaf007)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE5 (0x80aaf009)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE6 (0x80aaf00b)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE7 (0x80aaf00d)
#define NLS_VUELINK_FLX1_NPS_TEXT_WAVE8 (0x80aaf00f)


/// TextId's for Numerics
#define NLS_NOM_ECG_V_P_C_CNT (0x00024261)
#define NLS_NOM_ECG_AMPL_ST (0x00020300)
#define NLS_NOM_ECG_CARD_BEAT_RATE (0x00024182)
#define NLS_NOM_PULS_OXIM_PULS_RATE (0x00024822)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_LEFT (0x80155401)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_RIGHT (0x80155402)
#define NLS_PRESS_NAMES_PULSE_FROM_ABP (0x80035402)
#define NLS_PRESS_NAMES_PULSE_FROM_ART (0x80035403)
#define NLS_PRESS_NAMES_PULSE_FROM_AO (0x80035404)
#define NLS_PRESS_NAMES_PULSE_FROM_PAP (0x80035405)
#define NLS_PRESS_NAMES_PULSE_FROM_CVP (0x80035406)
#define NLS_PRESS_NAMES_PULSE_FROM_RAP (0x80035407)
#define NLS_PRESS_NAMES_PULSE_FROM_LAP (0x80035408)
#define NLS_NOM_PRESS_INTRA_CRAN (0x00025808)
#define NLS_PRESS_NAMES_PULSE_FROM_ICP (0x80035409)
#define NLS_PRESS_NAMES_PULSE_FROM_P (0x80035401)
#define NLS_NOM_PRESS_CEREB_PERF (0x00025804)
#define NLS_NOM_AWAY_RESP_RATE (0x00025012)
#define NLS_NOM_CONC_AWAY_O2 (0x00025164)
#define NLS_NOM_VENT_CONC_AWAY_O2_INSP (0x00027498)
#define NLS_NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC (0x00025100)
#define NLS_NOM_PRESS_AWAY_INSP (0x00025108)
#define NLS_NOM_PRESS_AWAY_INSP_MAX (0x00025109)
#define NLS_NOM_RATIO_IE (0x00025118)
#define NLS_NOM_RES_AWAY (0x00025120)
#define NLS_NOM_VOL_MINUTE_AWAY (0x00025148)
#define NLS_NOM_VENT_CONC_AWAY_O2_DELTA (0x00025168)
#define NLS_NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX (0x00025190)
#define NLS_NOM_VENT_VOL_LEAK (0x00025370)
#define NLS_NOM_VENT_VOL_LUNG_ALV (0x00025374)
#define NLS_NOM_CAPAC_VITAL (0x00025080)
#define NLS_NOM_COMPL_LUNG (0x00025088)
#define NLS_NOM_COMPL_LUNG_STATIC (0x00025090)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE (0x00025988)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK (0x00025984)
#define NLS_NOM_EMFC_AAI (0x04011194)
#define NLS_NOM_EMFC_BSI (0x04011198)
#define NLS_NOM_EMFC_T1 (0x04010064)
#define NLS_NOM_EMFC_T2 (0x04010068)
#define NLS_NOM_EMFC_Tpat (0x04010a38)
#define NLS_DIFFTEMP_NAMES_TEMP_TRECT (0x800b5402)
#define NLS_DIFFTEMP_NAMES_TEMP_TBLOOD (0x800b5409)
#define NLS_DIFFTEMP_NAMES_TEMP_TCORE (0x800b5403)
#define NLS_DIFFTEMP_NAMES_TEMP_TSKIN (0x800b5404)
#define NLS_DIFFTEMP_NAMES_TEMP_TESOPH (0x800b5405)
#define NLS_DIFFTEMP_NAMES_TEMP_TNASO (0x800b5406)
#define NLS_DIFFTEMP_NAMES_TEMP_TART (0x800b5408)
#define NLS_DIFFTEMP_NAMES_TEMP_TVEN (0x800b5407)
#define NLS_DIFFTEMP_NAMES_TEMP_TAIRWY (0x800b540a)
#define NLS_DIFFTEMP_NAMES_TRECT_TEMP (0x800b5415)
#define NLS_DIFFTEMP_NAMES_TRECT_TBLOOD (0x800b541d)
#define NLS_DIFFTEMP_NAMES_TRECT_TCORE (0x800b5417)
#define NLS_DIFFTEMP_NAMES_TRECT_TSKIN (0x800b5418)
#define NLS_DIFFTEMP_NAMES_TRECT_TESOPH (0x800b5419)
#define NLS_DIFFTEMP_NAMES_TRECT_TNASO (0x800b541a)
#define NLS_DIFFTEMP_NAMES_TRECT_TART (0x800b541c)
#define NLS_DIFFTEMP_NAMES_TRECT_TVEN (0x800b541b)
#define NLS_DIFFTEMP_NAMES_TRECT_TAIRWY (0x800b541e)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TEMP (0x800b54a1)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TRECT (0x800b54a2)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TCORE (0x800b54a3)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TSKIN (0x800b54a4)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TESOPH (0x800b54a5)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TNASO (0x800b54a6)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TART (0x800b54a8)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TVEN (0x800b54a7)
#define NLS_DIFFTEMP_NAMES_TBLOOD_TAIRWY (0x800b54aa)
#define NLS_DIFFTEMP_NAMES_TCORE_TEMP (0x800b5429)
#define NLS_DIFFTEMP_NAMES_TCORE_TRECT (0x800b542a)
#define NLS_DIFFTEMP_NAMES_TCORE_TBLOOD (0x800b5431)
#define NLS_DIFFTEMP_NAMES_TCORE_TSKIN (0x800b542c)
#define NLS_DIFFTEMP_NAMES_TCORE_TESOPH (0x800b542d)
#define NLS_DIFFTEMP_NAMES_TCORE_TNASO (0x800b542e)
#define NLS_DIFFTEMP_NAMES_TCORE_TART (0x800b5430)
#define NLS_DIFFTEMP_NAMES_TCORE_TVEN (0x800b542f)
#define NLS_DIFFTEMP_NAMES_TCORE_TAIRWY (0x800b5432)
#define NLS_DIFFTEMP_NAMES_TSKIN_TEMP (0x800b543d)
#define NLS_DIFFTEMP_NAMES_TSKIN_TRECT (0x800b543e)
#define NLS_DIFFTEMP_NAMES_TSKIN_TBLOOD (0x800b5445)
#define NLS_DIFFTEMP_NAMES_TSKIN_TCORE (0x800b543f)
#define NLS_DIFFTEMP_NAMES_TSKIN_TESOPH (0x800b5441)
#define NLS_DIFFTEMP_NAMES_TSKIN_TNASO (0x800b5442)
#define NLS_DIFFTEMP_NAMES_TSKIN_TART (0x800b5444)
#define NLS_DIFFTEMP_NAMES_TSKIN_TVEN (0x800b5443)
#define NLS_DIFFTEMP_NAMES_TSKIN_TAIRWY (0x800b5446)
#define NLS_DIFFTEMP_NAMES_TESOPH_TEMP (0x800b5451)
#define NLS_DIFFTEMP_NAMES_TESOPH_TRECT (0x800b5452)
#define NLS_DIFFTEMP_NAMES_TESOPH_TBLOOD (0x800b5459)
#define NLS_DIFFTEMP_NAMES_TESOPH_TCORE (0x800b5453)
#define NLS_DIFFTEMP_NAMES_TESOPH_TSKIN (0x800b5454)
#define NLS_DIFFTEMP_NAMES_TESOPH_TNASO (0x800b5456)
#define NLS_DIFFTEMP_NAMES_TESOPH_TART (0x800b5458)
#define NLS_DIFFTEMP_NAMES_TESOPH_TVEN (0x800b5457)
#define NLS_DIFFTEMP_NAMES_TESOPH_TAIRWY (0x800b545a)
#define NLS_DIFFTEMP_NAMES_TNASO_TEMP (0x800b5465)
#define NLS_DIFFTEMP_NAMES_TNASO_TRECT (0x800b5466)
#define NLS_DIFFTEMP_NAMES_TNASO_TBLOOD (0x800b546d)
#define NLS_DIFFTEMP_NAMES_TNASO_TCORE (0x800b5467)
#define NLS_DIFFTEMP_NAMES_TNASO_TSKIN (0x800b5468)
#define NLS_DIFFTEMP_NAMES_TNASO_TESOPH (0x800b5469)
#define NLS_DIFFTEMP_NAMES_TNASO_TART (0x800b546c)
#define NLS_DIFFTEMP_NAMES_TNASO_TVEN (0x800b546b)
#define NLS_DIFFTEMP_NAMES_TNASO_TAIRWY (0x800b546e)
#define NLS_DIFFTEMP_NAMES_TART_TEMP (0x800b548d)
#define NLS_DIFFTEMP_NAMES_TART_TRECT (0x800b548e)
#define NLS_DIFFTEMP_NAMES_TART_TBLOOD (0x800b5495)
#define NLS_DIFFTEMP_NAMES_TART_TCORE (0x800b548f)
#define NLS_DIFFTEMP_NAMES_TART_TSKIN (0x800b5490)
#define NLS_DIFFTEMP_NAMES_TART_TESOPH (0x800b5491)
#define NLS_DIFFTEMP_NAMES_TART_TNASO (0x800b5492)
#define NLS_DIFFTEMP_NAMES_TART_TVEN (0x800b5493)
#define NLS_DIFFTEMP_NAMES_TART_TAIRWY (0x800b5496)
#define NLS_DIFFTEMP_NAMES_TVEN_TEMP (0x800b5479)
#define NLS_DIFFTEMP_NAMES_TVEN_TRECT (0x800b547a)
#define NLS_DIFFTEMP_NAMES_TVEN_TBLOOD (0x800b5481)
#define NLS_DIFFTEMP_NAMES_TVEN_TCORE (0x800b547b)
#define NLS_DIFFTEMP_NAMES_TVEN_TSKIN (0x800b547c)
#define NLS_DIFFTEMP_NAMES_TVEN_TESOPH (0x800b547d)
#define NLS_DIFFTEMP_NAMES_TVEN_TNASO (0x800b547e)
#define NLS_DIFFTEMP_NAMES_TVEN_TART (0x800b5480)
#define NLS_DIFFTEMP_NAMES_TVEN_TAIRWY (0x800b5482)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TEMP (0x800b54b5)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TRECT (0x800b54b6)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TBLOOD (0x800b54bd)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TCORE (0x800b54b7)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TSKIN (0x800b54b8)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TESOPH (0x800b54b9)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TNASO (0x800b54ba)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TART (0x800b54bc)
#define NLS_DIFFTEMP_NAMES_TAIRWY_TVEN (0x800b54bb)
#define NLS_NOM_CONC_AWAY_AGENT (0x00025388)
#define NLS_NOM_RES_VASC_SYS_INDEX (0x00024900)
#define NLS_NOM_WK_LV_STROKE_INDEX (0x00024904)
#define NLS_NOM_WK_RV_STROKE_INDEX (0x00024908)
#define NLS_NOM_SCORE_GLAS_COMA (0x00025880)
#define LS_NOM_SCORE_EYE_SUBSC_GLAS_COMA (0x00025882)
#define NLS_NOM_SCORE_MOTOR_SUBSC_GLAS_COMA (0x00025883)
#define NLS_NOM_SCORE_SUBSC_VERBAL_GLAS_COMA (0x00025884)
#define NLS_NOM_CIRCUM_HEAD (0x00025900)
#define NLS_NOM_TIME_PD_PUPIL_REACT_LEFT (0x00025924)
#define NLS_NOM_TIME_PD_PUPIL_REACT_RIGHT (0x00025928)
#define NLS_NOM_CONC_PH_ART (0x00027004)
#define NLS_NOM_CONC_PCO2_ART (0x00027008)
#define NLS_NOM_CONC_HB_ART (0x00027014)
#define NLS_NOM_CONC_HB_O2_ART (0x00027018)
#define NLS_NOM_CONC_PH_VEN (0x00027034)
#define NLS_NOM_CONC_PCO2_VEN (0x00027038)
#define NLS_NOM_CONC_HB_O2_VEN (0x00027048)
#define NLS_NOM_CONC_PH_GEN (0x00027104)
#define NLS_NOM_CONC_HCO3_GEN (0x00027108)
#define NLS_NOM_CONC_K_GEN (0x00027110)
#define NLS_NOM_CONC_GLU_GEN (0x00027114)
#define NLS_NOM_CONC_PCO2_GEN (0x00027140)
#define NLS_NOM_CONC_PO2_GEN (0x00027174)
#define NLS_NOM_CONC_HCT_GEN (0x00027184)
#define NLS_NOM_CONC_CHLORIDE_GEN (0x00027168)
#define NLS_NOM_EMFC_P1 (0x04010030)
#define NLS_NOM_EMFC_P1_SYS (0x04010031)
#define NLS_NOM_EMFC_P1_DIA (0x04010032)
#define NLS_NOM_EMFC_P1_MEAN (0x04010033)
#define NLS_NOM_EMFC_P2 (0x04010034)
#define NLS_NOM_EMFC_P2_SYS (0x04010035)
#define NLS_NOM_EMFC_P2_DIA (0x04010036)
#define NLS_NOM_EMFC_P2_MEAN (0x04010037)
#define NLS_NOM_EMFC_P3 (0x04010038)
#define NLS_NOM_EMFC_P3_SYS (0x04010039)
#define NLS_NOM_EMFC_P3_DIA (0x0401003a)
#define NLS_NOM_EMFC_P3_MEAN (0x0401003b)
#define NLS_NOM_EMFC_P4 (0x0401003c)
#define NLS_NOM_EMFC_P4_SYS (0x0401003d)
#define NLS_NOM_EMFC_P4_DIA (0x0401003e)
#define NLS_NOM_EMFC_P4_MEAN (0x0401003f)
#define NLS_NOM_EMFC_P5 (0x04010400)
#define NLS_NOM_EMFC_P5_SYS (0x04010401)
#define NLS_NOM_EMFC_P5_DIA (0x04010402)
#define NLS_NOM_EMFC_P5_MEAN (0x04010403)
#define NLS_NOM_EMFC_P6 (0x04010404)
#define NLS_NOM_EMFC_P6_SYS (0x04010405)
#define NLS_NOM_EMFC_P6_DIA (0x04010406)
#define NLS_NOM_EMFC_P6_MEAN (0x04010407)
#define NLS_NOM_EMFC_P7 (0x04010408)
#define NLS_NOM_EMFC_P7_SYS (0x04010409)
#define NLS_NOM_EMFC_P7_DIA (0x0401040a)
#define NLS_NOM_EMFC_P7_MEAN (0x0401040b)
#define NLS_NOM_EMFC_P8 (0x0401040c)
#define NLS_NOM_EMFC_P8_SYS (0x0401040d)
#define NLS_NOM_EMFC_P8_DIA (0x0401040e)
#define NLS_NOM_EMFC_P8_MEAN (0x0401040f)
#define NLS_NOM_EMFC_IUP (0x04010054)
#define NLS_NOM_EMFC_IUP_SYS (0x04010055)
#define NLS_NOM_EMFC_IUP_DIA (0x04010056)
#define NLS_NOM_EMFC_IUP_MEAN (0x04010057)
#define NLS_NOM_EMFC_VPB (0x04010088)
#define NLS_NOM_EMFC_AUX (0x040100b4)
#define NLS_NOM_EMFC_ST1 (0x040100b8)
#define NLS_NOM_EMFC_ST2 (0x040100c4)
#define NLS_NOM_EMFC_ST3 (0x040100c8)
#define NLS_NOM_EMFC_BUN_PER_cr (0x04010110)
#define NLS_NOM_EMFC_CH2O (0x04010118)
#define NLS_NOM_EMFC_COsm (0x04010120)
#define NLS_NOM_EMFC_CrCl (0x04010124)
#define NLS_NOM_EMFC_FeNa (0x0401012c)
#define NLS_NOM_EMFC_IMV (0x04010138)
#define NLS_NOM_EMFC_PlOsm (0x04010164)
#define NLS_NOM_EMFC_SCreat (0x04010180)
#define NLS_NOM_EMFC_U_PER_POsm (0x04010198)
#define NLS_NOM_EMFC_U_PER_SCr (0x0401019c)
#define NLS_NOM_EMFC_UCreat (0x040101a0)
#define NLS_NOM_EMFC_UrK (0x040101a4)
#define NLS_NOM_EMFC_UrKEx (0x040101a8)
#define NLS_NOM_EMFC_UrNa_PER_K (0x040101b0)
#define NLS_NOM_EMFC_UrNaEx (0x040101b4)
#define NLS_NOM_EMFC_UrOsm (0x040101b8)
#define NLS_NOM_EMFC_UrVol (0x040101bc)
#define NLS_NOM_EMFC_T3 (0x04010410)
#define NLS_NOM_EMFC_T4 (0x04010414)
#define NLS_NOM_EMFC_Length (0x04010420)
#define NLS_NOM_EMFC_G_Age (0x04010428)
#define NLS_NOM_EMFC_Cal (0x0401042c)
#define NLS_NOM_EMFC_I_O (0x04010430)
#define NLS_NOM_EMFC_Apgar (0x04010434)
#define NLS_NOM_EMFC_BSA_B (0x0401043c)
#define NLS_NOM_EMFC_BSA_D (0x04010440)
#define NLS_NOM_EMFC_PVcP (0x0401046c)
#define NLS_NOM_EMFC_Rdyn (0x04010480)
#define NLS_NOM_EMFC_NgInsP (0x04010484)
#define NLS_NOM_EMFC_SpPkFl (0x0401048c)
#define NLS_NOM_EMFC_SpAWRR (0x04010510)
#define NLS_NOM_EMFC_PlGain (0x04010514)
#define NLS_NOM_EMFC_AwN2O (0x04010518)
#define NLS_NOM_EMFC_fgAGT (0x04010520)
#define NLS_NOM_EMFC_O2EI (0x0401052c)
#define NLS_NOM_EMFC_REF (0x04010530)
#define NLS_NOM_EMFC_EDV (0x04010534)
#define NLS_NOM_EMFC_ESV (0x04010538)
#define NLS_NOM_EMFC_EDVI (0x0401053c)
#define NLS_NOM_EMFC_ESVI (0x04010540)
#define NLS_NOM_EMFC_SaO2 (0x04010548)
#define NLS_NOM_EMFC_DABP (0x0401054c)
#define NLS_NOM_EMFC_RiseTi (0x04010550)
#define NLS_NOM_EMFC_BasePr (0x04010554)
#define NLS_NOM_EMFC_HFVAmp (0x0401055c)
#define NLS_NOM_EMFC_UrUrea (0x04010580)
#define NLS_NOM_EMFC_UrpH (0x04010584)
#define NLS_NOM_EMFC_tCO2 (0x04010588)
#define NLS_NOM_EMFC_tBili (0x0401058c)
#define NLS_NOM_EMFC_SerGlc (0x04010590)
#define NLS_NOM_EMFC_UrGlc (0x04010594)
#define NLS_NOM_EMFC_dBili (0x04010598)
#define NLS_NOM_EMFC_SerCa (0x0401059c)
#define NLS_NOM_EMFC_tSerCa (0x040105a0)
#define NLS_NOM_EMFC_SerMg (0x040105a4)
#define NLS_NOM_EMFC_SerPho (0x040105a8)
#define NLS_NOM_EMFC_SerK (0x040105ac)
#define NLS_NOM_EMFC_SerCl (0x040105b0)
#define NLS_NOM_EMFC_SerAlb (0x040105b4)
#define NLS_NOM_EMFC_UrCl (0x040105b8)
#define NLS_NOM_EMFC_SerGlo (0x040105bc)
#define NLS_NOM_EMFC_SerPro (0x040105c0)
#define NLS_NOM_EMFC_SrUrea (0x040105c4)
#define NLS_NOM_EMFC_WBC (0x040105c8)
#define NLS_NOM_EMFC_RBC (0x040105cc)
#define NLS_NOM_EMFC_Plts (0x040105d0)
#define NLS_NOM_EMFC_MCV (0x040105d4)
#define NLS_NOM_EMFC_MCH (0x040105d8)
#define NLS_NOM_EMFC_MCHC (0x040105dc)
#define NLS_NOM_EMFC_PTT (0x040105e0)
#define NLS_NOM_EMFC_PT (0x040105e4)
#define NLS_NOM_EMFC_TT (0x040105e8)
#define NLS_NOM_EMFC_AP (0x040105f0)
#define NLS_NOM_EMFC_alphaA (0x040105f4)
#define NLS_NOM_EMFC_CHE (0x040105f8)
#define NLS_NOM_EMFC_SerCK (0x040105fc)
#define NLS_NOM_EMFC_CK_MB (0x04010600)
#define NLS_NOM_EMFC_CK_MM (0x04010604)
#define NLS_NOM_EMFC_GGT (0x04010608)
#define NLS_NOM_EMFC_GOT (0x0401060c)
#define NLS_NOM_EMFC_GPT (0x04010610)
#define NLS_NOM_EMFC_Fe (0x04010614)
#define NLS_NOM_EMFC_Chol (0x04010618)
#define NLS_NOM_EMFC_TGL (0x0401061c)
#define NLS_NOM_EMFC_UrPro (0x04010620)
#define NLS_NOM_EMFC_UrCa (0x04010624)
#define NLS_NOM_EMFC_CO_Hb (0x04010628)
#define NLS_NOM_EMFC_HbF (0x0401062c)
#define NLS_NOM_EMFC_Met_Hb (0x04010630)
#define NLS_NOM_EMFC_tProt (0x04010634)
#define NLS_NOM_EMFC_LDH (0x04010638)
#define NLS_NOM_EMFC_AST (0x0401063c)
#define NLS_NOM_EMFC_ALP (0x04010640)
#define NLS_NOM_EMFC_RC (0x04010644)
#define NLS_NOM_EMFC_CT (0x04010648)
#define NLS_NOM_EMFC_ESR (0x0401064c)
#define NLS_NOM_EMFC_PCV (0x04010650)
#define NLS_NOM_EMFC_KCT (0x04010654)
#define NLS_NOM_EMFC_KPLUS (0x0401065c)
#define NLS_NOM_EMFC_Rexp (0x04010664)
#define NLS_NOM_EMFC_AWV (0x04010668)
#define NLS_NOM_EMFC_ExpTi (0x0401066c)
#define NLS_NOM_EMFC_Rinsp (0x04010670)
#define NLS_NOM_EMFC_inPkFl (0x04010674)
#define NLS_NOM_EMFC_Pmax (0x04010678)
#define NLS_NOM_EMFC_Pmin (0x0401067c)
#define NLS_NOM_EMFC_AccVol (0x04010680)
#define NLS_NOM_EMFC_i_eN2O (0x04010688)
#define NLS_NOM_EMFC_i_eHAL (0x0401068c)
#define NLS_NOM_EMFC_i_eENF (0x04010690)
#define NLS_NOM_EMFC_i_eISO (0x04010694)
#define NLS_NOM_EMFC_i_eSEV (0x04010698)
#define NLS_NOM_EMFC_i_eDES (0x0401069c)
#define NLS_NOM_EMFC_i_eAGT (0x040106a0)
#define NLS_NOM_EMFC_i_eO2 (0x040106a4)
#define NLS_NOM_EMFC_cktO2 (0x040106a8)
#define NLS_NOM_EMFC_Patm (0x040106ac)
#define NLS_NOM_EMFC_TVin (0x040106b0)
#define NLS_NOM_EMFC_TVex (0x040106b4)
#define NLS_NOM_EMFC_MV (0x040106b8)
#define NLS_NOM_EMFC_Paw (0x040106bc)
#define NLS_NOM_EMFC_Pmean (0x040106c0)
#define NLS_NOM_EMFC_RRaw (0x040106c4)
#define NLS_NOM_EMFC_Ppeak (0x040106cc)
#define NLS_NOM_EMFC_HFMVin (0x040106d8)
#define NLS_NOM_EMFC_DCO2 (0x040106dc)
#define NLS_NOM_EMFC_SpTVex (0x040106e0)
#define NLS_NOM_EMFC_HFTVin (0x040106e4)
#define NLS_NOM_EMFC_HFVTV (0x040106e8)
#define NLS_NOM_EMFC_extHR (0x04010700)
#define NLS_NOM_EMFC_Rf_I (0x04010734)
#define NLS_NOM_EMFC_Rf_II (0x04010738)
#define NLS_NOM_EMFC_Rf_III (0x0401073c)
#define NLS_NOM_EMFC_Rf_aVR (0x04010740)
#define NLS_NOM_EMFC_Rf_aVL (0x04010744)
#define NLS_NOM_EMFC_Rf_aVF (0x04010748)
#define NLS_NOM_EMFC_Rf_V1 (0x0401074c)
#define NLS_NOM_EMFC_Rf_V2 (0x04010750)
#define NLS_NOM_EMFC_Rf_V3 (0x04010754)
#define NLS_NOM_EMFC_Rf_V4 (0x04010758)
#define NLS_NOM_EMFC_Rf_V5 (0x0401075c)
#define NLS_NOM_EMFC_Rf_V6 (0x04010760)
#define NLS_NOM_EMFC_SpO2_2 (0x040107a0)
#define NLS_NOM_EMFC_PERF2 (0x040107a4)
#define NLS_NOM_EMFC_LT_PCT_AL (0x040107d0)
#define NLS_NOM_EMFC_LT_PCT_BE (0x040107d4)
#define NLS_NOM_EMFC_LT_PCT_DL (0x040107d8)
#define NLS_NOM_EMFC_LT_PCT_TH (0x040107dc)
#define NLS_NOM_EMFC_LT_AL (0x040107e0)
#define NLS_NOM_EMFC_LT_BE (0x040107e4)
#define NLS_NOM_EMFC_LT_DL (0x040107e8)
#define NLS_NOM_EMFC_LT_TH (0x040107ec)
#define NLS_NOM_EMFC_LT_MDF (0x040107f4)
#define NLS_NOM_EMFC_LT_MPF (0x040107f8)
#define NLS_NOM_EMFC_LT_PPF (0x040107fc)
#define NLS_NOM_EMFC_LT_SEF (0x04010800)
#define NLS_NOM_EMFC_LT_TP (0x04010804)
#define NLS_NOM_EMFC_LSCALE (0x04010808)
#define NLS_NOM_EMFC_RT_PCT_AL (0x0401080c)
#define NLS_NOM_EMFC_RT_PCT_BE (0x04010810)
#define NLS_NOM_EMFC_RT_PCT_DL (0x04010814)
#define NLS_NOM_EMFC_RT_PCT_TH (0x04010818)
#define NLS_NOM_EMFC_RT_AL (0x0401081c)
#define NLS_NOM_EMFC_RT_BE (0x04010820)
#define NLS_NOM_EMFC_RT_DL (0x04010824)
#define NLS_NOM_EMFC_RT_TH (0x04010828)
#define NLS_NOM_EMFC_RT_MDF (0x04010830)
#define NLS_NOM_EMFC_RT_MPF (0x04010834)
#define NLS_NOM_EMFC_RT_PPF (0x04010838)
#define NLS_NOM_EMFC_RT_SEF (0x0401083c)
#define NLS_NOM_EMFC_RT_TP (0x04010840)
#define NLS_NOM_EMFC_RSCALE (0x04010844)
#define NLS_NOM_EMFC_DPosP (0x04010848)
#define NLS_NOM_EMFC_RRsync (0x0401084c)
#define NLS_NOM_EMFC_RRmech (0x04010850)
#define NLS_NOM_EMFC_fgDES (0x04010854)
#define NLS_NOM_EMFC_fgSEV (0x04010858)
#define NLS_NOM_EMFC_fgHAL (0x0401085c)
#define NLS_NOM_EMFC_fgENF (0x04010860)
#define NLS_NOM_EMFC_fgISO (0x04010864)
#define NLS_NOM_EMFC_fgN2O (0x04010868)
#define NLS_NOM_EMFC_fgO2 (0x0401086c)
#define NLS_NOM_EMFC_AGTLev (0x04010870)
#define NLS_NOM_EMFC_ISOLev (0x04010874)
#define NLS_NOM_EMFC_ENFLev (0x04010878)
#define NLS_NOM_EMFC_HALLev (0x0401087c)
#define NLS_NOM_EMFC_DESLev (0x04010880)
#define NLS_NOM_EMFC_SEVLev (0x04010884)
#define NLS_NOM_EMFC_BP (0x04010888)
#define NLS_NOM_EMFC_BP_SYS (0x04010889)
#define NLS_NOM_EMFC_BP_DIA (0x0401088a)
#define NLS_NOM_EMFC_BP_MEAN (0x0401088b)
#define NLS_NOM_EMFC_UrVSht (0x0401088c)
#define NLS_NOM_EMFC_UrFl (0x04010890)
#define NLS_NOM_EMFC_XXXVYY (0x04010898)
#define NLS_NOM_EMFC_XXXRYY (0x0401089c)
#define NLS_NOM_EMFC_iCa (0x04010a2c)
#define NLS_NOM_EMFC_HGB_CALC (0x04010a34)
#define NLS_NOM_EMFC_pHc (0x04010a44)
#define NLS_NOM_EMFC_pH_ADJ (0x04010a48)
#define NLS_NOM_EMFC_pHa_ADJ (0x04010a4c)
#define NLS_NOM_EMFC_pHv_ADJ (0x04010a50)
#define NLS_NOM_EMFC_pHc_ADJ (0x04010a54)
#define NLS_NOM_EMFC_PcO2 (0x04010a5c)
#define NLS_NOM_EMFC_PO2_ADJ (0x04010a60)
#define NLS_NOM_EMFC_PaO2_ADJ (0x04010a64)
#define NLS_NOM_EMFC_PvO2_ADJ (0x04010a68)
#define NLS_NOM_EMFC_PcO2_ADJ (0x04010a6c)
#define NLS_NOM_EMFC_PcCO2 (0x04010a78)
#define NLS_NOM_EMFC_PCO2_ADJ (0x04010a7c)
#define NLS_NOM_EMFC_PaCO2_ADJ (0x04010a80)
#define NLS_NOM_EMFC_PvCO2_ADJ (0x04010a84)
#define NLS_NOM_EMFC_PcCO2_ADJ (0x04010a88)
#define NLS_NOM_EMFC_tCO2_CALC (0x04010a8c)
#define NLS_NOM_EMFC_SO2_CALC (0x04010a90)
#define NLS_NOM_EMFC_SaO2_CALC (0x04010a94)
#define NLS_NOM_EMFC_SvO2_CALC (0x04010a98)
#define NLS_NOM_EMFC_ScO2_CALC (0x04010a9c)
#define NLS_NOM_EMFC_HCO3_CALC (0x04010aa0)
#define NLS_NOM_EMFC_BEecf_CALC (0x04010aa4)
#define NLS_NOM_EMFC_AnGap_CALC (0x04010aa8)
#define NLS_NOM_EMFC_Urea (0x04010ab8)
#define NLS_NOM_EMFC_FIO2_MANUAL (0x04010abc)
#define NLS_NOM_EMFC_BE_B_CALC (0x04010ac0)
#define NLS_NOM_EMFC_iMg (0x04010ac4)
#define NLS_NOM_EMFC_O2_MANUAL (0x04010ad4)
#define NLS_NOM_EMFC_SetTmp (0x04010ad8)
#define NLS_NOM_EMFC_Crea (0x04010adc)
#define NLS_NOM_EMFC_B_PER_Cre_CALC (0x04010ae0)
#define NLS_NOM_EMFC_U_PER_Cre_CALC (0x04010ae4)
#define NLS_NOM_EMFC_Lact (0x04010ae8)
#define NLS_NOM_EMFC_Sim (0x04010af0)
#define NLS_NOM_EMFC_Press1 (0x04010b10)
#define NLS_NOM_EMFC_Press2 (0x04010b14)
#define NLS_NOM_EMFC_ModTmp (0x04010b28)
#define NLS_NOM_EMFC_Pat_T (0x04010b54)
#define NLS_NOM_EMFC_Air_T (0x04010b58)
#define NLS_NOM_EMFC_Power (0x04010b5c)
#define NLS_NOM_EMFC_DET (0x04010b60)
#define NLS_NOM_EMFC_BagWgt (0x04010bb8)
#define NLS_NOM_EMFC_tUrVol (0x04010bbc)
#define NLS_NOM_EMFC_UrDens (0x04010bc0)
#define NLS_NOM_EMFC_Turine (0x04010bc4)
#define NLS_NOM_EMFC_Age (0x04010bc8)
#define NLS_NOM_EMFC_Urine (0x04010bd8)
#define NLS_NOM_EMFC_PaFIO2 (0x04010be0)
#define NLS_NOM_EMFC_SAPS (0x04010be8)
#define NLS_NOM_EMFC_VNrmal (0x04010bec)
#define NLS_NOM_EMFC_ALT (0x04010bf0)
#define NLS_NOM_EMFC_SpRR (0x04010bf4)
#define NLS_NOM_EMFC_XXXPYY (0x04010c80)
#define NLS_NOM_EMFC_inAGTs (0x04010cec)
#define NLS_NOM_EMFC_etAGTs (0x04010cf0)
#define NLS_NOM_EMFC_BagVol (0x04010cfc)
#define NLS_NOM_EMFC_TOFcnt (0x04010dac)
#define NLS_NOM_EMFC_TOFrat (0x04010db0)
#define NLS_NOM_EMFC_Twitch (0x04010db4)
#define NLS_NOM_EMFC_PTC (0x04010db8)
#define NLS_NOM_EMFC_RemTi (0x04010dbc)
#define NLS_NOM_EMFC_TOF1 (0x04010dc0)
#define NLS_NOM_EMFC_TOF2 (0x04010dc4)
#define NLS_NOM_EMFC_TOF3 (0x04010dc8)
#define NLS_NOM_EMFC_TOF4 (0x04010dcc)
#define NLS_NOM_EMFC_ACT (0x04010e10)
#define NLS_NOM_EMFC_InsTi (0x04010e74)
#define NLS_NOM_EMFC_C20_PER_C (0x04010e78)
#define NLS_NOM_EMFC_TC (0x04010e7c)
#define NLS_NOM_EMFC_r (0x04010e80)
#define NLS_NOM_EMFC_RVrat (0x04010e84)
#define NLS_NOM_EMFC_iCa_N (0x04010e88)
#define NLS_NOM_EMFC_TVPSV (0x04010e98)
#define NLS_NOM_EMFC_NIF (0x04010e9c)
#define NLS_NOM_EMFC_RSBI (0x04010ea0)
#define NLS_NOM_EMFC_iCa_N_CALC (0x04011114)
#define NLS_NOM_EMFC_sVMode (0x04018000)
#define NLS_NOM_EMFC_sAWRR (0x04018004)
#define NLS_NOM_EMFC_sTV (0x04018008)
#define NLS_NOM_EMFC_sPkFl (0x0401800c)
#define NLS_NOM_EMFC_sFIO2 (0x04018010)
#define NLS_NOM_EMFC_sTrig (0x04018014)
#define NLS_NOM_EMFC_sPltTi (0x04018018)
#define NLS_NOM_EMFC_sSghR (0x0401801c)
#define NLS_NOM_EMFC_sSghTV (0x04018020)
#define NLS_NOM_EMFC_sSghNr (0x04018024)
#define NLS_NOM_EMFC_sATV (0x04018028)
#define NLS_NOM_EMFC_sARR (0x0401802c)
#define NLS_NOM_EMFC_sAPkFl (0x04018030)
#define NLS_NOM_EMFC_sAFIO2 (0x04018034)
#define NLS_NOM_EMFC_sPSV (0x04018038)
#define NLS_NOM_EMFC_sPWave (0x0401803c)
#define NLS_NOM_EMFC_sEnSgh (0x04018040)
#define NLS_NOM_EMFC_sNeblr (0x04018044)
#define NLS_NOM_EMFC_sO2Suc (0x04018048)
#define NLS_NOM_EMFC_sDtaIv (0x04018050)
#define NLS_NOM_EMFC_sChrIv (0x04018054)
#define NLS_NOM_EMFC_sBasFl (0x04018058)
#define NLS_NOM_EMFC_sSenFl (0x0401805c)
#define NLS_NOM_EMFC_sOxiIv (0x04018060)
#define NLS_NOM_EMFC_sPVcP (0x04018064)
#define NLS_NOM_EMFC_sPVinT (0x04018068)
#define NLS_NOM_EMFC_sAPVcP (0x0401806c)
#define NLS_NOM_EMFC_sAPVRR (0x04018070)
#define NLS_NOM_EMFC_sAPVTi (0x04018074)
#define NLS_NOM_EMFC_sAPVO2 (0x04018078)
#define NLS_NOM_EMFC_sAPVhP (0x0401807c)
#define NLS_NOM_EMFC_sSilnc (0x04018080)
#define NLS_NOM_EMFC_sPVI (0x04018084)
#define NLS_NOM_EMFC_sPVE (0x04018088)
#define NLS_NOM_EMFC_sAPVI (0x0401808c)
#define NLS_NOM_EMFC_sAPVE (0x04018090)
#define NLS_NOM_EMFC_sPVCtl (0x04018094)
#define NLS_NOM_EMFC_sMode (0x04018098)
#define NLS_NOM_EMFC_sCycTi (0x0401809c)
#define NLS_NOM_EMFC_sIPPV (0x040180a0)
#define NLS_NOM_EMFC_sIMV (0x040180a4)
#define NLS_NOM_EMFC_sPEEP (0x040180a8)
#define NLS_NOM_EMFC_sSPEEP (0x040180ac)
#define NLS_NOM_EMFC_sMV (0x040180b0)
#define NLS_NOM_EMFC_sEnTrg (0x040180b4)
#define NLS_NOM_EMFC_sEnTP (0x040180b8)
#define NLS_NOM_EMFC_BPAPPL (0x040180bc)
#define NLS_NOM_EMFC_BPAPPH (0x040180c0)
#define NLS_NOM_EMFC_BPAPTL (0x040180c4)
#define NLS_NOM_EMFC_BPAPTH (0x040180c8)
#define NLS_NOM_EMFC_sAVDel (0x040180cc)
#define NLS_NOM_EMFC_sTPDel (0x040180d0)
#define NLS_NOM_EMFC_sO2Mon (0x040180d4)
#define NLS_NOM_EMFC_sO2Cal (0x040180d8)
#define NLS_NOM_EMFC_sMVAl (0x040180dc)
#define NLS_NOM_EMFC_sPmax (0x040180e0)
#define NLS_NOM_EMFC_sInsTi (0x040180e4)
#define NLS_NOM_EMFC_sExpTi (0x040180e8)
#define NLS_NOM_EMFC_sIE_1 (0x040180ec)
#define NLS_NOM_EMFC_sALMRT (0x040180f0)
#define NLS_NOM_EMFC_sCPAP (0x040180f4)
#define NLS_NOM_EMFC_sFlow (0x040180f8)
#define NLS_NOM_EMFC_sPIP (0x040180fc)
#define NLS_NOM_EMFC_sLInPr (0x04018100)
#define NLS_NOM_EMFC_sHFVFl (0x04018104)
#define NLS_NOM_EMFC_sHFVRR (0x04018108)
#define NLS_NOM_EMFC_Model (0x04018110)
#define NLS_NOM_EMFC_sO2 (0x0401810c)
#define NLS_NOM_EMFC_sCMV (0x04018114)
#define NLS_NOM_EMFC_sSIMV (0x04018118)
#define NLS_NOM_EMFC_sMMV (0x0401811c)
#define NLS_NOM_EMFC_sFWave (0x04018120)
#define NLS_NOM_EMFC_sDRate (0x04018124)
#define NLS_NOM_EMFC_sPin (0x04018128)
#define NLS_NOM_EMFC_sRRaw (0x0401812c)
#define NLS_NOM_EMFC_sInsFl (0x04018130)
#define NLS_NOM_EMFC_sExpFl (0x04018134)
#define NLS_NOM_EMFC_sTrVol (0x04018138)
#define NLS_NOM_EMFC_sAADel (0x0401813c)
#define NLS_NOM_EMFC_sHFVAm (0x04018140)
#define NLS_NOM_EMFC_sMVDel (0x04018144)
#define NLS_NOM_EMFC_sTrgFl (0x04018148)
#define NLS_NOM_EMFC_sPincR (0x0401814c)
#define NLS_NOM_EMFC_sVmax (0x04018150)
#define NLS_NOM_EMFC_sFlCal (0x04018154)
#define NLS_NOM_EMFC_sVolAl (0x04018158)
#define NLS_NOM_EMFC_sCO2Wm (0x0401815c)
#define NLS_NOM_EMFC_sCO2Al (0x04018160)
#define NLS_NOM_EMFC_sPtCat (0x04018164)
#define NLS_NOM_EMFC_sOxiAl (0x04018168)
#define NLS_NOM_EMFC_sAGTWm (0x0401816c)
#define NLS_NOM_EMFC_Wave (0x04018170)
#define NLS_NOM_EMFC_loPmax (0x04018174)
#define NLS_NOM_EMFC_sAgent (0x04018178)
#define NLS_NOM_EMFC_sADel (0x0401817c)
#define NLS_NOM_EMFC_sPSVrp (0x04018180)
#define NLS_NOM_EMFC_sTVap (0x04018184)
#define NLS_NOM_EMFC_sSens (0x04018188)
#define NLS_NOM_EMFC_sHInPr (0x0401818c)
#define NLS_NOM_EMFC_sBkgFl (0x04018190)
#define NLS_NOM_EMFC_sfgAGT (0x04018198)
#define NLS_NOM_EMFC_sfgISO (0x0401819c)
#define NLS_NOM_EMFC_sfgENF (0x040181a0)
#define NLS_NOM_EMFC_sfgHAL (0x040181a4)
#define NLS_NOM_EMFC_sfgDES (0x040181a8)
#define NLS_NOM_EMFC_sfgSEV (0x040181ac)
#define NLS_NOM_EMFC_sfgAir (0x040181b0)
#define NLS_NOM_EMFC_sfgO2 (0x040181b4)
#define NLS_NOM_EMFC_sfgFl (0x040181b8)
#define NLS_NOM_EMFC_sfgN2O (0x040181bc)
#define NLS_NOM_EMFC_sGasPr (0x040181c0)
#define NLS_NOM_EMFC_sO2Pr (0x040181c4)
#define NLS_NOM_EMFC_sCircl (0x040181c8)
#define NLS_NOM_EMFC_sTVin (0x040181cc)
#define NLS_NOM_EMFC_set_T (0x040181d0)
#define NLS_NOM_EMFC_sUrTi (0x040181d4)
#define NLS_NOM_EMFC_sBrSys (0x040181d8)
#define NLS_NOM_EMFC_GasCar (0x040181dc)
#define NLS_NOM_EMFC_CO2Cal (0x040181e0)
#define NLS_NOM_EMFC_sTlow (0x040181e4)
#define NLS_NOM_EMFC_sThigh (0x040181e8)
#define NLS_NOM_EMFC_sPlow (0x040181ec)
#define NLS_NOM_EMFC_sPhigh (0x040181f0)
#define NLS_NOM_EMFC_sVolas (0x040181f4)
#define NLS_NOM_EMFC_sFlas (0x040181f8)
#define NLS_NOM_EMFC_sCurnt (0x040181fc)
#define NLS_NOM_EMFC_sChrge (0x04018200)
#define NLS_NOM_EMFC_sPulsD (0x04018204)
#define NLS_NOM_EMFC_sRepTi (0x04018208)
#define NLS_NOM_EMFC_sfmax (0x0401820c)
#define NLS_NOM_EMFC_BO_ABG (0x04018274)
#define NLS_NOM_EMFC_BO_PAR (0x04018278)
#define NLS_NOM_EMFC_37_ABG (0x0401827c)
#define NLS_NOM_EMFC_37_PAR (0x04018280)
#define NLS_NOM_EMFC_highP (0x0401a000)
#define NLS_NOM_EMFC_loPEEP (0x0401a004)
#define NLS_NOM_EMFC_hiSghP (0x0401a008)
#define NLS_NOM_EMFC_liATi (0x0401a00c)
#define NLS_NOM_EMFC_liPVAT (0x0401a010)
#define NLS_NOM_EMFC_sustP (0x0401a014)
#define NLS_NOM_EMFC_lowMV (0x0401a018)
#define NLS_NOM_EMFC_lowO2 (0x0401a01c)
#define NLS_NOM_EMFC_highO2 (0x0401a020)
#define NLS_NOM_EMFC_sBPAl (0x0401a024)
#define NLS_NOM_EMFC_sPStat (0x0401a028)
#define NLS_NOM_EMFC_highMV (0x0401a02c)
#define NLS_NOM_EMFC_lowTV (0x0401a030)
#define NLS_NOM_EMFC_highTV (0x0401a034)
#define NLS_GASES_NAMES_DIAG_INFO_LBL (0x805a5403)
#define NLS_NOM_EMFC_BLANK (0x04010960)

#define NLS_NOM_EEG_PWR_SPEC_ALPHA_REL_LEFT (0x0002F859)
#define NLS_NOM_EEG_PWR_SPEC_ALPHA_REL_RIGHT (0x0002F85A)
#define NLS_NOM_EEG_PWR_SPEC_BETA_REL_LEFT (0x0002F85F)
#define NLS_NOM_EEG_PWR_SPEC_BETA_REL_RIGHT (0x0002F860)
#define NLS_NOM_EEG_PWR_SPEC_DELTA_REL_LEFT (0x0002F867)
#define NLS_NOM_EEG_PWR_SPEC_DELTA_REL_RIGHT (0x0002F868)
#define NLS_NOM_EEG_PWR_SPEC_THETA_REL_LEFT (0x0002F86D)
#define NLS_NOM_EEG_PWR_SPEC_THETA_REL_RIGHT (0x0002F86E)
#define NLS_NOM_CONC_PROT_SER (0x0002F178)
#define NLS_NOM_CONC_PRO_URINE (0x0002F19B)
#define NLS_NOM_SAT_O2_GEN_1 (0x0002F962)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM1 (0x80AAF064)
#define NLS_NOM_RATIO_IE (0x00025118)
#define NLS_NOM_SETT_RATIO_IE (0x04025118)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM10 (0x80AAF076)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM11 (0x80AAF078)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM12 (0x80AAF07A)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM13 (0x80AAF07C)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM14 (0x80AAF07E)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM15 (0x80AAF080)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM16 (0x80AAF082)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM17 (0x80AAF084)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM18 (0x80AAF086)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM19 (0x80AAF088)
#define NLS_NOM_SAT_O2_GEN_2 (0x0002F963)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM2 (0x80AAF066)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM20 (0x80AAF08A)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM21 (0x80AAF08C)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM22 (0x80AAF08E)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM23 (0x80AAF090)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM24 (0x80AAF092)
#define NLS_NOM_SAT_O2_GEN_3 (0x0002F964)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM3 (0x80AAF068)
#define NLS_NOM_SAT_O2_GEN_4 (0x0002F965)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM4 (0x80AAF06A)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM5 (0x80AAF06C)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM6 (0x80AAF06E)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM7 (0x80AAF070)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM8 (0x80AAF072)
#define NLS_VUELINK_FLX1_NPS_TEXT_NUM9 (0x80AAF074)
#define NLS_NOM_OUTPUT_CARD_INDEX_ACCEL (0x0002F889)
#define NLS_NOM_TIME_PD_ACT (0x0002F18A)
#define NLS_NOM_RATIO_TIME_PD_PTT (0x0002F896)
#define NLS_NOM_AGE (0x0002F810)
#define NLS_NOM_CONC_PO2_ART_ADJ (0x0002F83B)
#define NLS_NOM_CONC_PO2_CAP_ADJ (0x0002F83C)
#define NLS_NOM_CONC_PH_GEN_ADJ (0x0002F838)
#define NLS_NOM_CONC_PH_ART_ADJ (0x0002F836)
#define NLS_NOM_CONC_PH_CAP_ADJ (0x0002F837)
#define NLS_NOM_CONC_PH_VEN_ADJ (0x0002F839)
#define NLS_NOM_CONC_PO2_GEN_ADJ (0x0002F83D)
#define NLS_NOM_CONC_PO2_VEN_ADJ (0x0002F83E)
#define NLS_NOM_TEMP_AIR_INCUB (0x0002F12A)
#define NLS_NOM_VENT_CONC_AWAY_CO2_INSP (0x00025160)
#define NLS_NOM_VENT_FLOW_INSP (0x0002518C)
#define NLS_NOM_CONC_AWAY_SUM_MAC (0x0002F05D)
#define NLS_NOM_VOL_MINUTE_AWAY (0x00025148)
#define NLS_NOM_PRESS_AWAY_MIN (0x000250F2)
#define NLS_NOM_PRESS_AWAY (0x000250F0)
#define NLS_NOM_PRESS_AWAY_INSP (0x00025108)
#define NLS_NOM_AWAY_RESP_RATE (0x00025012)
#define NLS_NOM_VENT_RESP_RATE (0x00025022)
#define NLS_NOM_TEMP_AWAY (0x00024B54)
#define NLS_NOM_EEG_PWR_SPEC_ALPHA_ABS_LEFT (0x0002F855)
#define NLS_NOM_EEG_PWR_SPEC_ALPHA_ABS_RIGHT (0x0002F856)
#define NLS_NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_HI (0x0402F919)
#define NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_HI (0x0402F94B)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_LIMIT_HI (0x0402F930)
#define NLS_NOM_SETT_VENT_VOL_TIDAL_LIMIT_HI (0x0402F94D)
#define NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_LO (0x0402F94C)
#define NLS_NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_LO (0x0402F91A)
#define NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS_LIMIT_LO (0x0002F8BA)
#define NLS_NOM_SETT_VENT_VOL_TIDAL_LIMIT_LO (0x0402F94E)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_SUST_LIMIT_HI (0x0402F935)
#define NLS_NOM_CONC_ALB_SER (0x0002F163)
#define NLS_NOM_ELEC_EVOK_POTL_CRTX_ACOUSTIC_AAI (0x0002F873)
#define NLS_NOM_CONC_AP (0x0002F185)
#define NLS_NOM_CONC_ALPHA_AMYLASE (0x0002F186)
#define NLS_NOM_SAT_DIFF_O2_ART_ALV (0x00024B40)
#define NLS_NOM_VENT_VOL_LUNG_ALV (0x00025374)
#define NLS_NOM_CONC_ALP (0x0002F81D)
#define NLS_NOM_TEMP_AMBIENT (0x0002F0C6)
#define NLS_NOM_TIME_PD_APNEA (0x00025130)
#define NLS_NOM_TIME_PD_aPTT_PE (0x0002F18E)
#define NLS_NOM_TIME_PD_aPTT_WB (0x0002F18D)
#define NLS_NOM_TEMP_ART (0x00024B50)
#define NLS_NOM_PRESS_BLD_ART_ABP (0x00024A14)
#define NLS_NOM_PRESS_BLD_ART (0x00024A10)
#define NLS_NOM_PRESS_BLD_AORT (0x00024A0C)
#define NLS_NOM_PULS_OXIM_SAT_O2 (0x00024BB8)
#define NLS_NOM_CONC_HB_O2_ART (0x00027018)
#define NLS_NOM_CONC_DIFF_HB_O2_ATR_VEN (0x0002F092)
#define NLS_NOM_CONC_AST (0x0002F184)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_AUX (0x0002F977)
#define NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_AUX (0x0002F97C)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_STOP (0x0002F97B)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_START (0x0002F97A)
#define NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_AUX (0x0002F97E)
#define NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_AUX (0x0002F97D)
#define NLS_NOM_BASE_EXCESS_BLD_ART_CALC (0x0002F817)
#define NLS_NOM_PRESS_AIR_AMBIENT (0x0002F06B)
#define NLS_NOM_BASE_EXCESS_BLD_ART (0x0002716C)
#define NLS_NOM_CONC_BASE_EXCESS_ECF (0x0002F090)
#define NLS_NOM_EEG_PWR_SPEC_BETA_ABS_LEFT (0x0002F85B)
#define NLS_NOM_EEG_PWR_SPEC_BETA_ABS_RIGHT (0x0002F85C)
#define NLS_NOM_EEG_BISPECTRAL_INDEX (0x0002F04E)
#define NLS_NOM_PRESS_BLD_DIFF (0x0002F968)
#define NLS_NOM_PRESS_BLD_DIFF_GEN_1 (0x0002F96C)
#define NLS_NOM_PRESS_BLD_DIFF_GEN_2 (0x0002F970)
#define NLS_NOM_CONC_BLD_UREA_NITROGEN (0x0002F08F)
#define NLS_NOM_AREA_BODY_SURFACE (0x0002F071)
#define NLS_NOM_PRESS_BLD_ART_BRACHIAL (0x0002F0C0)
#define NLS_NOM_AREA_BODY_SURFACE_ACTUAL_BOYD (0x0002F812)
#define NLS_NOM_AREA_BODY_SURFACE_ACTUAL_DUBOIS (0x0002F813)
#define NLS_NOM_ECG_TIME_PD_QT_BASELINE (0x0002F155)
#define NLS_NOM_RATIO_BUN_CREA (0x0002F88F)
#define NLS_NOM_EEG_BURST_SUPPRN_INDEX (0x0002F840)
#define NLS_NOM_CONC_CA_SER (0x0002F824)
#define NLS_NOM_CONC_AN_GAP_CALC (0x0002F1A1)
#define NLS_NOM_CONC_BASE_EXCESS_ECF_CALC (0x0002F821)
#define NLS_NOM_CONC_HCO3_GEN_CALC (0x0002F82E)
#define NLS_NOM_CONC_HB_ART_CALC (0x0002F82B)
#define NLS_NOM_SAT_O2_ART_CALC (0x0002F164)
#define NLS_NOM_SAT_O2_CAP_CALC (0x0002F1A0)
#define NLS_NOM_SAT_O2_CALC (0x0002F89C)
#define NLS_NOM_SAT_O2_VEN_CALC (0x0002F166)
#define NLS_NOM_CONC_CO2_TOT_CALC (0x0002F826)
#define NLS_NOM_CONC_CA_URINE (0x0002F19C)
#define NLS_NOM_CONC_HB_CO_GEN (0x00027180)
#define NLS_NOM_ECG_CARD_BEAT_RATE_BTB (0x0002418A)
#define NLS_NOM_BNP (0x0002F0F6)
#define NLS_NOM_CARD_FUNC_INDEX (0x0002F046)
#define NLS_NOM_OUTPUT_CARD_INDEX (0x0002490C)
#define NLS_NOM_OUTPUT_CARD (0x00024B04)
#define NLS_NOM_CARDIAC_TROPONIN_I (0x0002F0F4)
#define NLS_NOM_CARDIO_PULMONARY_BYPASS_MODE (0x0002F0F5)
#define NLS_NOM_SAT_O2_VEN_CENT (0x0002F100)
#define NLS_NOM_PRESS_BLD_VEN_CENT (0x00024A44)
#define NLS_NOM_PRESS_CEREB_PERF (0x00025804)
#define NLS_NOM_TEMP_CEREBRAL (0x0002F0C5)
#define NLS_NOM_CONC_CHLORIDE_GEN (0x00027168)
#define NLS_NOM_CONC_CHOLESTEROL (0x0002F16E)
#define NLS_NOM_CONC_CHE (0x0002F182)
#define NLS_NOM_CONC_CHLOR_SER (0x0002F15F)
#define NLS_NOM_CONC_CHLOR_URINE (0x0002F19A)
#define NLS_NOM_AWAY_CO2 (0x000250AC)
#define NLS_NOM_FLOW_CO2_PROD_RESP (0x000250E0)
#define NLS_NOM_FLOW_CO2_PROD_RESP_TIDAL (0x0002F882)
#define NLS_NOM_TIME_PD_COAGULATION (0x0002F192)
#define NLS_NOM_CONC_PCO2_ART_ADJ (0x0002F832)
#define NLS_NOM_CONC_PCO2_GEN_ADJ (0x0002F834)
#define NLS_NOM_CONC_PCO2_CAP_ADJ (0x0002F833)
#define NLS_NOM_CONC_PCO2_VEN_ADJ (0x0002F835)
#define NLS_NOM_OUTPUT_CARD_CTS (0x00024BDC)
#define NLS_NOM_OUTPUT_CARD_INDEX_CTS (0x0002F047)
#define NLS_NOM_PRESS_AWAY_CTS_POS (0x000250F4)
#define NLS_NOM_TEMP_CORE (0x00024B60)
#define NLS_NOM_TEMP_CORE_GEN_1 (0x0002F966)
#define NLS_NOM_TEMP_CORE_GEN_2 (0x0002F967)
#define NLS_NOM_AWAY_CORR_COEF (0x0002F814)
#define NLS_NOM_COMPL_LUNG_PAV (0x0002F992)
#define NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN (0x0002F981)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_STOP (0x0002F980)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_START (0x0002F97F)
#define NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN (0x0002F983)
#define NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN (0x0002F982)
#define NLS_NOM_CONC_CRP (0x0002F183)
#define NLS_NOM_CONC_CREA_KIN_MM (0x0002F17F)
#define NLS_NOM_CONC_CREA_KIN_MB (0x0002F181)
#define NLS_NOM_CONC_CREA_KIN_SER (0x0002F180)
#define NLS_NOM_CONC_CREA (0x0002F173)
#define NLS_NOM_CONC_CREA_CLR (0x0002F16C)
#define NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE (0x0002F986)
#define NLS_NOM_CEREB_STATE_INDEX (0x0002F961)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_STOP (0x0002F985)
#define NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_START (0x0002F984)
#define NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE (0x0002F988)
#define NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE (0x0002F987)
#define NLS_NOM_VOL_URINE_COL (0x00026830)
#define NLS_NOM_FLOW_URINE_PREV_24HR (0x0002F883)
#define NLS_NOM_VENT_VOL_AWAY_DEADSP (0x000251B0)
#define NLS_NOM_ECG_TIME_PD_QTc_DELTA (0x0002F156)
#define NLS_NOM_CARD_BEAT_RATE_EXT (0x0002F81B)
#define NLS_NOM_FLUID_DENS_URINE (0x0002F19D)
#define NLS_NOM_SETT_TEMP (0x04024B48)
#define NLS_NOM_SAT_DIFF_O2_ART_VEN (0x0002F06C)
#define NLS_NOM_PULS_OXIM_SAT_O2_DIFF (0x00024BC4)
#define NLS_NOM_TEMP_DIFF (0x0002E018)
#define NLS_NOM_CONC_BILI_DIRECT (0x0002F17A)
#define NLS_NOM_EEG_PWR_SPEC_DELTA_ABS_LEFT (0x0002F863)
#define NLS_NOM_EEG_PWR_SPEC_DELTA_ABS_RIGHT (0x0002F864)
#define NLS_NOM_VENT_TIME_PD_PPV (0x00025360)
#define NLS_NOM_COMPL_LUNG_DYN (0x0002508C)
#define NLS_NOM_RES_AWAY_DYN (0x0002F899)
#define NLS_NOM_EMG_ELEC_POTL_MUSCL (0x0002593C)
#define NLS_NOM_VOL_VENT_L_END_DIA (0x00024C00)
#define NLS_NOM_VOL_VENT_L_END_DIA_INDEX (0x0002F8D0)
#define NLS_NOM_VOL_VENT_L_END_SYS (0x00024C04)
#define NLS_NOM_VOL_VENT_L_END_SYS_INDEX (0x0002F8D1)
#define NLS_NOM_CONC_AWAY_AGENT_ET_SEC (0x0002F81E)
#define NLS_NOM_SETT_CONC_AWAY_O2 (0x04025164)
#define NLS_NOM_ELAS_LUNG_PAV (0x0002F995)
#define NLS_NOM_ES_RATE (0x0002F17C)
#define NLS_NOM_TEMP_ESOPH (0x00024B64)
#define NLS_NOM_FLOW_AWAY_EXP_MAX (0x000250D9)
#define NLS_NOM_FLOW_AWAY_EXP_ET (0x0002F87A)
#define NLS_NOM_RES_AWAY_EXP (0x00025124)
#define NLS_NOM_TIME_PD_EXP (0x0002F8A1)
#define NLS_NOM_VOL_AWAY_EXP_TIDAL (0x0002F0E1)
#define NLS_NOM_VOL_LUNG_WATER_EXTRA_VASC (0x0002F042)
#define NLS_NOM_VOL_LUNG_WATER_EXTRA_VASC_INDEX (0x0002F043)
#define NLS_NOM_VOL_THERMO_EXTRA_VASC_INDEX (0x0002F07A)
#define NLS_NOM_PRESS_BLD_ART_FEMORAL (0x0002F0BC)
#define NLS_NOM_CONC_FE_GEN (0x0002F160)
#define NLS_NOM_CONC_HB_FETAL (0x0002F165)
#define NLS_NOM_FRACT_EXCR_NA (0x0002F194)
#define NLS_NOM_VENT_CONC_AWAY_O2_INSP (0x00027498)
#define NLS_NOM_FREE_WATER_CLR (0x0002F884)
#define NLS_NOM_FLOW_AWAY_DESFL (0x0002F878)
#define NLS_NOM_FLOW_AWAY_ENFL (0x0002F879)
#define NLS_NOM_FLOW_AWAY_HALOTH (0x0002F87B)
#define NLS_NOM_FLOW_AWAY_ISOFL (0x0002F87C)
#define NLS_NOM_FLOW_AWAY_SEVOFL (0x0002F880)
#define NLS_NOM_FLOW_AWAY_AGENT (0x0002F876)
#define NLS_NOM_FLOW_AWAY_AIR (0x0002F877)
#define NLS_NOM_CONC_GGT (0x0002F189)
#define NLS_NOM_CONC_AWAY_AGENT (0x00025388)
#define NLS_GASES_NAMES_CONC_AWAY_AGENT1 (0x805A5401)
#define NLS_GASES_NAMES_CONC_AWAY_AGENT2 (0x805A5402)
#define NLS_NOM_CONC_AWAY_DESFL (0x000251D8)
#define NLS_NOM_CONC_AWAY_ENFL (0x000251DC)
#define NLS_NOM_CONC_AWAY_HALOTH (0x000251E0)
#define NLS_NOM_CONC_AWAY_AGENT_INSP (0x00025390)
#define NLS_NOM_CONC_AWAY_ISOFL (0x000251E8)
#define NLS_EEG_NAMES_CHAN_FREQ1 (0x800F5413)
#define NLS_EEG_NAMES_CHAN_PCNT1 (0x800F5415)
#define NLS_EEG_NAMES_CHAN_FREQ2 (0x800F5414)
#define NLS_EEG_NAMES_CHAN_PCNT2 (0x800F5416)
#define NLS_NOM_COMPL_LUNG (0x00025088)
#define NLS_NOM_CONC_AWAY_N2 (0x0002537C)
#define NLS_NOM_CONC_AWAY_N2O (0x000251F0)
#define NLS_NOM_NUM_CALC_CONST (0x0002F07B)
#define NLS_NOM_NUM_CATHETER_CONST (0x0002F07C)
#define NLS_NOM_CONC_AWAY_O2 (0x00025164)
#define NLS_NOM_PRESS_GEN_1 (0x0002F0A4)
#define NLS_NOM_PRESS_GEN_2 (0x0002F0A8)
#define NLS_NOM_PRESS_GEN_3 (0x0002F0AC)
#define NLS_NOM_PRESS_GEN_4 (0x0002F0B0)
#define NLS_NOM_PRESS_GEN_5 (0x0002F3F4)
#define NLS_NOM_PRESS_GEN_6 (0x0002F3F8)
#define NLS_NOM_PRESS_GEN_7 (0x0002F3FC)
#define NLS_NOM_PRESS_GEN_8 (0x0002F400)
#define NLS_NOM_CONC_AWAY_SEVOFL (0x000251E4)
#define NLS_NOM_TEMP_GEN_1 (0x0002F0C7)
#define NLS_NOM_TEMP_GEN_2 (0x0002F0C8)
#define NLS_NOM_TEMP_GEN_3 (0x0002F0C9)
#define NLS_NOM_TEMP_GEN_4 (0x0002F0CA)
#define NLS_NOM_GAS_TCUT (0x0002F051)
#define NLS_NOM_AGE_GEST (0x0002F811)
#define NLS_NOM_SCORE_GLAS_COMA (0x00025880)
#define NLS_NOM_FRACT_EJECT (0x0002F105)
#define NLS_NOM_VOL_GLOBAL_END_DIA (0x0002F044)
#define NLS_NOM_VOL_GLOBAL_END_DIA_INDEX (0x0002F045)
#define NLS_NOM_CONC_GLO_SER (0x0002F829)
#define NLS_NOM_CONC_GLU_GEN (0x00027114)
#define NLS_NOM_CONC_GLU_SER (0x0002F82A)
#define NLS_NOM_CONC_GLU_URINE (0x0002F19F)
#define NLS_NOM_CONC_GOT (0x0002F188)
#define NLS_NOM_CONC_GPT (0x0002F187)
#define NLS_NOM_CONC_HCT_GEN (0x00027184)
#define NLS_NOM_CIRCUM_HEAD (0x00025900)
#define NLS_NOM_CARD_CONTRACT_HEATHER_INDEX (0x0002F81C)
#define NLS_NOM_ECG_CARD_BEAT_RATE (0x00024182)
#define NLS_NOM_HEATING_PWR_TCUT_SENSOR (0x0002F076)
#define NLS_NOM_CONC_HB_URINE (0x0002F19E)
#define NLS_NOM_CONC_HB_ART (0x00027014)
#define NLS_NOM_CONC_HDL (0x0002F170)
#define NLS_NOM_VENT_VOL_TIDAL_HFV (0x0002F8BF)
#define NLS_NOM_COEF_GAS_TRAN (0x000251D4)
#define NLS_NOM_VENT_AMPL_HFV (0x0002F8B1)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_MAIN (0x0002F974)
#define NLS_NOM_HUMID (0x0002F103)
#define NLS_NOM_CONC_HCO3_GEN (0x00027108)
#define NLS_NOM_GRAD_PRESS_BLD_AORT_POS_MAX (0x00024C25)
#define NLS_NOM_TEMP_AXIL_INFRARED (0x0002FB4D)
#define NLS_NOM_TEMP_CORE_INFRARED (0x0002FB4F)
#define NLS_NOM_TEMP_ORAL_INFRARED (0x0002FB4C)
#define NLS_NOM_TEMP_RECT_INFRARED (0x0002FB4E)
#define NLS_NOM_TEMP_TYMP_INFRARED (0x0002FB4B)
#define NLS_NOM_VOL_INFUS_ACTUAL_TOTAL (0x000268FC)
#define NLS_NOM_TEMP_INJ (0x00024B68)
#define NLS_NOM_VOL_INJ (0x0002F079)
#define NLS_NOM_PT_INTL_NORM_RATIO (0x0002F18C)
#define NLS_NOM_FLOW_AWAY_INSP_MAX (0x000250DD)
#define NLS_NOM_RES_AWAY_INSP (0x00025128)
#define NLS_NOM_VENT_CONC_AWAY_AGENT_DELTA (0x0002F8B2)
#define NLS_NOM_VENT_CONC_AWAY_DESFL_DELTA (0x0002F8B3)
#define NLS_NOM_VENT_CONC_AWAY_ENFL_DELTA (0x0002F8B4)
#define NLS_NOM_VENT_CONC_AWAY_HALOTH_DELTA (0x0002F8B5)
#define NLS_NOM_VENT_CONC_AWAY_ISOFL_DELTA (0x0002F8B6)
#define NLS_NOM_VENT_CONC_AWAY_N2O_DELTA (0x0002F8B7)
#define NLS_NOM_VENT_CONC_AWAY_SEVOFL_DELTA (0x0002F8B9)
#define NLS_NOM_VOL_MINUTE_AWAY_INSP_HFV (0x0002F8CD)
#define NLS_NOM_VENT_VOL_AWAY_INSP_TIDAL_HFV (0x0002F8BE)
#define NLS_NOM_CONC_AWAY_AGENT_INSP_SEC (0x0002F81F)
#define NLS_NOM_VOL_AWAY_INSP_TIDAL (0x0002F0E0)
#define NLS_NOM_VENT_MODE_MAND_INTERMIT (0x0002D02A)
#define NLS_NOM_PRESS_INTRA_CRAN (0x00025808)
#define NLS_NOM_PRESS_INTRA_CRAN_1 (0x0002F0B4)
#define NLS_NOM_PRESS_INTRA_CRAN_2 (0x0002F0B8)
#define NLS_NOM_VOL_BLD_INTRA_THOR (0x0002F040)
#define NLS_NOM_VOL_BLD_INTRA_THOR_INDEX (0x0002F041)
#define NLS_NOM_PRESS_INTRA_UTERAL (0x0002F0D8)
#define NLS_NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC (0x00025100)
#define NLS_NOM_CONC_CA_GEN (0x00027118)
#define NLS_NOM_CONC_CA_GEN_NORM (0x0002F822)
#define NLS_NOM_CONC_MG_ION (0x0002F15B)
#define NLS_NOM_CONC_K_GEN (0x00027110)
#define NLS_NOM_CONC_K_SER (0x0002F82F)
#define NLS_NOM_TIME_PD_KAOLIN_CEPHALINE (0x0002F8A4)
#define NLS_NOM_PULS_OXIM_SAT_O2_ART_LEFT (0x00024BC8)
#define NLS_NOM_SAT_O2_LEFT (0x0002F89D)
#define NLS_NOM_PULS_OXIM_PERF_REL_LEFT (0x0002F08A)
#define NLS_NOM_CONC_LDH (0x0002F17B)
#define NLS_NOM_CONC_LACT (0x0002F174)
#define NLS_NOM_VENT_VOL_LEAK (0x00025370)
#define NLS_NOM_PRESS_BLD_ATR_LEFT (0x00024A30)
#define NLS_NOM_WK_CARD_LEFT (0x00024B90)
#define NLS_NOM_WK_CARD_LEFT_INDEX (0x0002F068)
#define NLS_NOM_WK_LV_STROKE (0x00024B9C)
#define NLS_NOM_WK_LV_STROKE_INDEX (0x00024904)
#define NLS_NOM_BIRTH_LENGTH (0x0002F818)
#define NLS_NOM_INTENS_LIGHT (0x0002F072)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_AGENT (0x0002F8C7)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_DESFL (0x0002F8C8)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_ENFL (0x0002F8C9)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_HALOTH (0x0002F8CA)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_ISOFL (0x0002F8CB)
#define NLS_NOM_VOL_LVL_LIQUID_BOTTLE_SEVOFL (0x0002F8CC)
#define NLS_NOM_CONC_LDL (0x0002F171)
#define NLS_NOM_VENT_VOL_LUNG_TRAPD (0x000251B8)
#define NLS_NOM_CONC_MG_SER (0x0002F15C)
#define NLS_NOM_VENT_VOL_MINUTE_AWAY_MAND (0x000251CC)
#define NLS_NOM_VENT_RESP_RATE_MAND (0x0002F0F1)
#define NLS_NOM_VENT_VOL_TIDAL_MAND (0x0002F0F2)
#define NLS_NOM_VENT_PRESS_AWAY_INSP_MAX (0x0002F8BB)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN_LEFT (0x0002F849)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN_RIGHT (0x0002F84A)
#define NLS_NOM_PRESS_AWAY_INSP_MEAN (0x0002510B)
#define NLS_NOM_CONC_HB_CORP_MEAN (0x0002F82C)
#define NLS_NOM_HB_CORP_MEAN (0x0002F885)
#define NLS_NOM_VOL_CORP_MEAN (0x0002F8C4)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN (0x0002597C)
#define NLS_NOM_CONC_HB_MET_GEN (0x0002717C)
#define NLS_NOM_CONC_AWAY_MAC (0x0002F099)
#define NLS_NOM_SAT_O2_VEN (0x00024B3C)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_LEFT (0x0002F84B)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_RIGHT (0x0002F84C)
#define NLS_NOM_FLOW_AWAY_N2O (0x0002F87E)
#define NLS_NOM_TEMP_NASOPH (0x00024B6C)
#define NLS_NOM_CONC_NA_GEN (0x0002710C)
#define NLS_NOM_CONC_NA_SERUM (0x000270D8)
#define NLS_NOM_CONC_NA_URINE (0x0002706C)
#define NLS_NOM_PRESS_AWAY_NEG_MAX (0x000250F9)
#define NLS_NOM_NSLOSS (0x0002F16D)
#define NLS_NOM_PRESS_BLD_NONINV (0x00024A04)
#define NLS_NOM_VENT_CONC_AWAY_O2_CIRCUIT (0x0002F8B8)
#define NLS_NOM_SAT_O2 (0x00024B2C)
#define NLS_NOM_SAT_O2_TISSUE (0x0002F960)
#define NLS_NOM_VENT_PRESS_OCCL (0x0002519C)
#define NLS_NOM_CREA_OSM (0x0002F83F)
#define NLS_NOM_C20_PER_C_INDEX (0x0002F81A)
#define NLS_NOM_PULS_OXIM_SAT_O2_PRE_DUCTAL (0x0002F1C0)
#define NLS_NOM_PULS_OXIM_SAT_O2_POST_DUCTAL (0x0002F1D4)
#define NLS_NOM_SAT_O2_DELIVER (0x0002F06D)
#define NLS_NOM_SAT_O2_DELIVER_INDEX (0x0002F06E)
#define NLS_NOM_FLOW_AWAY_O2 (0x0002F87F)
#define NLS_NOM_SAT_O2_CONSUMP_INDEX (0x0002F06A)
#define NLS_NOM_SAT_O2_CONSUMP (0x00024B00)
#define NLS_NOM_EXTRACT_O2_INDEX (0x0002F875)
#define NLS_NOM_RATIO_SAT_O2_CONSUMP_DELIVER (0x0002F06F)
#define NLS_NOM_SAT_O2_ART (0x00024B34)
#define NLS_NOM_RATIO_PaO2_FIO2 (0x0002F894)
#define NLS_NOM_VENT_ACTIVE (0x0002F8B0)
#define NLS_NOM_CONC_PCO2_GEN (0x00027140)
#define NLS_NOM_CONC_PCO2_CAP (0x0002F159)
#define NLS_NOM_CONC_PCO2_VEN (0x00027038)
#define NLS_NOM_CONC_PO2_ART (0x0002700C)
#define NLS_NOM_CONC_PO2_CAP (0x0002F15A)
#define NLS_NOM_VENT_AWAY_CO2_EXP (0x0002517C)
#define NLS_NOM_CONC_PO2_VEN (0x0002703C)
#define NLS_NOM_CONC_PO2_GEN (0x00027174)
#define NLS_NOM_CONC_PCO2_ART (0x00027008)
#define NLS_NOM_TIME_PD_PTT (0x0002F8A5)
#define NLS_NOM_PAT_HEIGHT (0x0002F094)
#define NLS_NOM_TEMP_BODY (0x00024B5C)
#define NLS_NOM_PAT_WEIGHT (0x0002F093)
#define NLS_NOM_TIME_PD_PT_PE (0x0002F190)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK (0x00025984)
#define NLS_NOM_RATIO_ART_VEN_SHUNT (0x0002F070)
#define NLS_NOM_PULS_OXIM_PERF_REL (0x00024BB0)
#define NLS_NOM_CONC_PH_ART (0x00027004)
#define NLS_NOM_CONC_PH_GEN (0x00027104)
#define NLS_NOM_CONC_PH_VEN (0x00027034)
#define NLS_NOM_CONC_PH_CAP (0x0002F158)
#define NLS_NOM_CONC_PH_URINE (0x00027064)
#define NLS_NOM_CONC_P_SER (0x0002F15E)
#define NLS_NOM_PLASMA_OSM (0x0002F16B)
#define NLS_NOM_PRESS_RESP_PLAT (0x000250E8)
#define NLS_NOM_TIME_PD_RESP_PLAT (0x0002F0FF)
#define NLS_NOM_PLTS_CNT (0x0002F167)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN (0x0002F978)
#define NLS_NOM_PULS_OXIM_PLETH_GAIN (0x0002F88D)
#define NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS (0x000251A8)
#define NLS_NOM_PRESS_AWAY_INSP_MAX (0x00025109)
#define NLS_NOM_PTC_CNT (0x0002F88B)
#define NLS_NOM_PTC_CNT (0x0002F88B)
#define NLS_NOM_HEATING_PWR_INCUBATOR (0x0002F886)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK_LEFT (0x0002F84F)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK_RIGHT (0x0002F850)
#define NLS_NOM_TEMP_AXIL_PRED (0x0002F118)
#define NLS_NOM_TEMP_ORAL_PRED (0x0002F110)
#define NLS_NOM_TEMP_RECT_PRED (0x0002F114)
#define NLS_NOM_ECG_V_P_C_CNT (0x00024261)
#define NLS_NOM_VENT_PRESS_AWAY_PV (0x0002F8BC)
#define NLS_NOM_CONC_PCT (0x0002F17D)
#define NLS_NOM_TIME_PD_PT (0x0002F18B)
#define NLS_NOM_RATIO_TIME_PD_PT (0x0002F895)
#define NLS_NOM_PRESS_BLD_ART_PULM (0x00024A1C)
#define NLS_NOM_PRESS_BLD_ART_PULM_WEDGE (0x00024A24)
#define NLS_NOM_PERM_VASC_PULM_INDEX (0x0002F106)
#define NLS_NOM_RES_VASC_PULM (0x00024B24)
#define NLS_NOM_RES_VASC_PULM_INDEX (0x0002F067)
#define NLS_PRESS_NAMES_PULSE_FROM_ABP (0x80035402)
#define NLS_PRESS_NAMES_PULSE_FROM_AO (0x80035404)
#define NLS_PRESS_NAMES_PULSE_FROM_ART (0x80035403)
#define NLS_PRESS_NAMES_PULSE_FROM_BAP (0x80035437)
#define NLS_PRESS_NAMES_PULSE_FROM_CVP (0x80035406)
#define NLS_PRESS_NAMES_PULSE_FROM_FAP (0x80035434)
#define NLS_PRESS_NAMES_PULSE_FROM_IC1 (0x8003542E)
#define NLS_PRESS_NAMES_PULSE_FROM_IC2 (0x80035431)
#define NLS_PRESS_NAMES_PULSE_FROM_ICP (0x80035409)
#define NLS_PRESS_NAMES_PULSE_FROM_LAP (0x80035408)
#define NLS_PRESS_NAMES_PULSE_FROM_P1 (0x80035422)
#define NLS_PRESS_NAMES_PULSE_FROM_P2 (0x80035425)
#define NLS_PRESS_NAMES_PULSE_FROM_P3 (0x80035428)
#define NLS_PRESS_NAMES_PULSE_FROM_P4 (0x8003542B)
#define NLS_PRESS_NAMES_PULSE_FROM_PAP (0x80035405)
#define NLS_PRESS_NAMES_PULSE_FROM_RAP (0x80035407)
#define NLS_PRESS_NAMES_PULSE_FROM_UAP (0x8003540A)
#define NLS_PRESS_NAMES_PULSE_FROM_P (0x80035401)
#define NLS_PRESS_NAMES_PULSE_FROM_UVP (0x8003540B)
#define NLS_NOM_PRESS_BLD_NONINV_PULS_RATE (0x0002F0E5)
#define NLS_NOM_PULS_OXIM_PULS_RATE_TELE (0x0002F09D)
#define NLS_NOM_PULS_PRESS_VAR (0x0002F0E3)
#define NLS_NOM_PULS_RATE (0x0002480A)
#define NLS_NOM_PULS_OXIM_PULS_RATE (0x00024822)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_LEFT (0x80155401)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_POST_DUCTAL (0x80155440)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_PRE_DUCTAL (0x8015543D)
#define NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_RIGHT (0x80155402)
#define NLS_NOM_TIME_PD_PUPIL_REACT_LEFT (0x00025924)
#define NLS_NOM_TIME_PD_PUPIL_REACT_RIGHT (0x00025928)
#define NLS_NOM_ECG_TIME_PD_QT_GL (0x00023F20)
#define NLS_NOM_ECG_TIME_PD_QT_BASELINE_HEART_RATE (0x0002F157)
#define NLS_NOM_ECG_TIME_PD_QT_HEART_RATE (0x0002F154)
#define NLS_NOM_ECG_TIME_PD_QTc (0x00023F24)
#define NLS_NOM_PULS_OXIM_SAT_O2_ART_RIGHT (0x00024BCC)
#define NLS_NOM_SAT_O2_RIGHT (0x0002F89E)
#define NLS_NOM_PULS_OXIM_PERF_REL_RIGHT (0x0002F08B)
#define NLS_NOM_BREATH_RAPID_SHALLOW_INDEX (0x0002F819)
#define NLS_NOM_RATIO_AWAY_RATE_VOL_AWAY (0x0002F88E)
#define NLS_NOM_RATIO_CONC_BLD_UREA_NITROGEN_CREA_CALC (0x0002F890)
#define NLS_NOM_RATIO_AWAY_DEADSP_TIDAL (0x0002511C)
#define NLS_NOM_RATIO_CONC_URINE_CREA_CALC (0x0002F891)
#define NLS_NOM_TEMP_RECT (0x0002E004)
#define NLS_NOM_RB_CNT (0x0002F169)
#define NLS_NOM_VENT_CONC_AWAY_O2_DELTA (0x00025168)
#define NLS_NOM_VENT_VOL_AWAY_DEADSP_REL (0x000251B4)
#define NLS_NOM_PULS_OXIM_PERF_REL_PRE_DUCTAL (0x0002F22C)
#define NLS_NOM_PULS_OXIM_PERF_REL_POST_DUCTAL (0x0002F1DC)
#define NLS_NOM_TIME_PD_EVOK_REMAIN (0x0002F8A0)
#define NLS_NOM_TIME_PD_EVOK_REMAIN (0x0002F8A0)
#define NLS_NOM_VENT_PRESS_RESP_PLAT (0x00025368)
#define NLS_NOM_RESP_RATE (0x0002500A)
#define NLS_NOM_AWAY_RESP_RATE_SPIRO (0x0002F0E2)
#define NLS_NOM_RET_CNT (0x0002F16A)
#define NLS_NOM_PRESS_BLD_ATR_RIGHT (0x00024A34)
#define NLS_NOM_WK_CARD_RIGHT (0x00024B94)
#define NLS_NOM_WK_CARD_RIGHT_INDEX (0x0002F069)
#define NLS_NOM_RIGHT_HEART_FRACT_EJECT (0x0002F89B)
#define NLS_NOM_WK_RV_STROKE (0x00024BA4)
#define NLS_NOM_WK_RV_STROKE_INDEX (0x00024908)
#define NLS_NOM_SHUNT_RIGHT_LEFT (0x0002F14A)
#define NLS_NOM_VENT_TIME_PD_RAMP (0x0002F8BD)
#define NLS_NOM_RES_AWAY_PAV (0x0002F993)
#define NLS_NOM_BREATH_RAPID_SHALLOW_INDEX_NORM (0x0002F996)
#define NLS_NOM_RES_AWAY_EXP_TOTAL (0x0002F994)
#define NLS_NOM_EEG_ELEC_POTL_CRTX_GAIN_LEFT (0x0002F841)
#define NLS_NOM_EEG_ELEC_POTL_CRTX_GAIN_RIGHT (0x0002F842)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE_LEFT (0x0002F853)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE_RIGHT (0x0002F854)
#define NLS_NOM_TEMP_TCUT_SENSOR (0x0002F03F)
#define NLS_NOM_CONC_CREA_SER (0x0002F827)
#define NLS_NOM_UREA_SER (0x0002F8AD)
#define NLS_NOM_SETT_VENT_RESP_RATE (0x04025022)
#define NLS_NOM_SETT_AWAY_RESP_RATE (0x04025012)
#define NLS_NOM_SETT_VENT_TIME_PD_RAMP_AL (0x0402F946)
#define NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP_APNEA (0x0402F917)
#define NLS_NOM_SETT_FLOW_AWAY_INSP_APNEA (0x0402F8ED)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_PV_APNEA (0x0402F933)
#define NLS_NOM_SETT_RATIO_IE_EXP_PV_APNEA (0x0402F901)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_MAX_PV_APNEA (0x0402F931)
#define NLS_NOM_SETT_RATIO_IE_INSP_PV_APNEA (0x0402F903)
#define NLS_NOM_SETT_VENT_TIME_PD_INSP_PV_APNEA (0x0402F944)
#define NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP_PV_APNEA (0x0402F918)
#define NLS_NOM_SETT_VENT_RESP_RATE_PV_APNEA (0x0402F93A)
#define NLS_NOM_SETT_AWAY_RESP_RATE_APNEA (0x0402F8DE)
#define NLS_NOM_SETT_VOL_AWAY_TIDAL_APNEA (0x0402F951)
#define NLS_NOM_SETT_APNEA_ALARM_DELAY (0x0402F8D9)
#define NLS_NOM_SETT_VOL_AWAY_TIDAL_APPLIED (0x0402F952)
#define NLS_NOM_SETT_SENS_LEVEL (0x0402F904)
#define NLS_NOM_SETT_VENT_AWAY_FLOW_BACKGROUND (0x0402F90F)
#define NLS_NOM_SETT_PRESS_AWAY_CTS_POS (0x040250F4)
#define NLS_NOM_SETT_VENT_MODE_MAND_CTS_ONOFF (0x0402F922)
#define NLS_NOM_SETT_TIME_PD_MSMT (0x0402F909)
#define NLS_NOM_SETT_VENT_MODE_SIGH (0x0402F923)
#define NLS_NOM_SETT_VENT_TIME_PD_EXP (0x0402F93F)
#define NLS_NOM_SETT_FLOW_AWAY_EXP (0x0402F8EA)
#define NLS_NOM_SETT_VENT_FLOW (0x0402F91B)
#define NLS_NOM_SETT_VENT_FLOW_AWAY_ASSIST (0x0402F91C)
#define NLS_NOM_SETT_VENT_FLOW_INSP_TRIG (0x0402F91D)
#define NLS_NOM_SETT_VENT_AWAY_FLOW_BASE (0x0402F910)
#define NLS_NOM_SETT_VENT_AWAY_FLOW_SENSE (0x0402F911)
#define NLS_NOM_SETT_FLOW_AWAY_N2O (0x0402F87E)
#define NLS_NOM_SETT_FLOW_AWAY_O2 (0x0402F87F)
#define NLS_NOM_SETT_VENT_O2_PROBE_POSN (0x0402F927)
#define NLS_NOM_SETT_VENT_GAS_PROBE_POSN (0x0402F920)
#define NLS_NOM_SETT_HFV_AMPL (0x0402F8F3)
#define NLS_NOM_SETT_AWAY_RESP_RATE_HFV (0x0402F8DF)
#define NLS_NOM_SETT_FLOW_AWAY_HFV (0x0402F8EB)
#define NLS_NOM_SETT_FLOW_FLUID_PUMP (0x04026858)
#define NLS_NOM_SETT_FLOW_AWAY_INSP (0x0402F8EC)
#define NLS_NOM_SETT_VENT_TIME_PD_INSP (0x0402F941)
#define NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP (0x04027498)
#define NLS_NOM_SETT_VOL_AWAY_INSP_TIDAL (0x0402F0E0)
#define NLS_NOM_SETT_PRESS_AWAY_MIN (0x040250F2)
#define NLS_NOM_SETT_PRESS_AWAY_INSP_MAX_LIMIT_LO (0x0402F8FB)
#define NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_MAND (0x040251CC)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_INSP_MAX (0x0402F8BB)
#define NLS_NOM_SETT_VOL_MINUTE_AWAY (0x04025148)
#define NLS_NOM_SETT_VOL_MINUTE_ALARM_DELAY (0x0402F953)
#define NLS_NOM_SETT_VENT_SIGH_MULT_RATE (0x0402F93B)
#define NLS_NOM_SETT_VENT_O2_CAL_MODE (0x0402F926)
#define NLS_NOM_SETT_VENT_ANALY_CONC_GAS_O2_MODE (0x0402F90E)
#define NLS_NOM_SETT_VENT_RESP_RATE_LIMIT_HI_PANT (0x0402F937)
#define NLS_NOM_SETT_VENT_TIME_PD_EXP_APRV (0x0402F940)
#define NLS_NOM_SETT_VENT_TIME_PD_INSP_APRV (0x0402F942)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_EXP_APRV (0x0402F92D)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_INSP_APRV (0x0402F92E)
#define NLS_NOM_SETT_FLOW_AWAY_INSP_MAX (0x040250DD)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_END_EXP_POS (0x040251A8)
#define NLS_NOM_SETT_TIME_PD_RESP_PLAT (0x0402F0FF)
#define NLS_NOM_SETT_PRESS_AWAY_INSP_MAX (0x04025109)
#define NLS_NOM_SETT_URINE_BAL_PD (0x0402F8AF)
#define NLS_NOM_SETT_EVOK_CHARGE (0x0402F8E6)
#define NLS_NOM_SETT_EVOK_CURR (0x0402F8E7)
#define NLS_NOM_SETT_TIME_PD_EVOK (0x0402F908)
#define NLS_NOM_SETT_TIME_PD_TRAIN_OF_FOUR (0x0402F8A6)
#define NLS_NOM_SETT_TIME_PD_TRAIN_OF_FOUR (0x0402F8A6)
#define NLS_NOM_SETT_VENT_AWAY_PRESS_RATE_INCREASE (0x0402F912)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_END_EXP_POS_INTERMIT (0x0402F92C)
#define NLS_NOM_SETT_VENT_PRESS_AWAY_PV (0x0402F8BC)
#define NLS_NOM_SETT_PRESS_AWAY_INSP (0x04025108)
#define NLS_NOM_SETT_RATIO_IE_EXP_PV (0x0402F900)
#define NLS_NOM_SETT_RATIO_IE_INSP_PV (0x0402F902)
#define NLS_NOM_SETT_VENT_TIME_PD_INSP_PV (0x0402F943)
#define NLS_NOM_SETT_VENT_SIGH_RATE (0x0402F93C)
#define NLS_NOM_SETT_VENT_VOL_TIDAL_SIGH (0x0402F8C0)
#define NLS_NOM_SETT_VENT_O2_SUCTION_MODE (0x0402F928)
#define NLS_NOM_SETT_VENT_MODE_SYNC_MAND_INTERMIT (0x0402F924)
#define NLS_NOM_SETT_VOL_AWAY_TIDAL (0x0402513C)
#define NLS_NOM_SETT_FLOW_AWAY_AIR (0x0402F877)
#define NLS_NOM_SETT_FLOW_AWAY_TOT (0x0402F881)
#define NLS_NOM_SETT_VENT_VOL_LUNG_TRAPD (0x040251B8)
#define NLS_NOM_SETT_CONC_AWAY_DESFL (0x040251D8)
#define NLS_NOM_SETT_CONC_AWAY_ENFL (0x040251DC)
#define NLS_NOM_SETT_CONC_AWAY_HALOTH (0x040251E0)
#define NLS_NOM_SETT_CONC_AWAY_ISOFL (0x040251E8)
#define NLS_NOM_SETT_CONC_AWAY_SEVOFL (0x040251E4)
#define NLS_NOM_SETT_FLOW_AWAY_AGENT (0x0402F876)
#define NLS_NOM_SETT_VENT_RESP_RATE_MODE_MAND_INTERMITT (0x0402F938)
#define NLS_NOM_SETT_VENT_RESP_RATE_MODE_PPV_INTERMIT_PAP (0x0402F939)
#define NLS_NOM_SETT_VENT_VOL_AWAY_ASSIST (0x0402F948)
#define NLS_NOM_SETT_VENT_VOL_LIMIT_AL_HI_ONOFF (0x0402F949)
#define NLS_NOM_EEG_BIS_SIG_QUAL_INDEX (0x0002F04D)
#define NLS_NOM_SNR (0x0002F101)
#define NLS_NOM_TIME_TCUT_SENSOR (0x0002F03E)
#define NLS_NOM_TEMP_SKIN (0x00024B74)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_SLAVE (0x0002F975)
#define NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE (0x00025988)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE (0x0002F979)
#define NLS_NOM_PULS_OXIM_SAT_O2_TELE (0x0002F09C)
#define NLS_NOM_VOL_AWAY_EXP_TIDAL_SPONT (0x0002F8C2)
#define NLS_NOM_AWAY_RESP_RATE_SPONT (0x0002F815)
#define NLS_NOM_TIME_PD_INSP (0x0002F8A3)
#define NLS_NOM_VENT_VOL_MINUTE_AWAY_SPONT (0x0002F091)
#define NLS_NOM_FLOW_AWAY_MAX_SPONT (0x0002F87D)
#define NLS_NOM_RESP_RATE_SPONT (0x0002F828)
#define NLS_NOM_VENT_VOL_TIDAL_SPONT (0x0002F0F3)
#define NLS_NOM_ECG_AMPL_ST (0x00020300)
#define NLS_NOM_ECG_AMPL_ST_INDEX (0x0002F03D)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_AVF (0x0002F450)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_AVL (0x0002F44F)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_AVR (0x0002F44E)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_I (0x0002F411)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_II (0x0002F412)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_III (0x0002F44D)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V1 (0x0002F413)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V2 (0x0002F414)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V3 (0x0002F415)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V4 (0x0002F416)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V5 (0x0002F417)
#define NLS_NOM_ECG_AMPL_ST_BASELINE_V6 (0x0002F418)
#define NLS_NOM_COMPL_LUNG_STATIC (0x00025090)
#define NLS_NOM_RES_AWAY (0x00025120)
#define NLS_NOM_VOL_BLD_STROKE_INDEX (0x0002F048)
#define NLS_NOM_VOL_BLD_STROKE (0x00024B84)
#define NLS_NOM_VOL_BLD_STROKE_VAR (0x0002F049)
#define NLS_NOM_SCORE_EYE_SUBSC_GLAS_COMA (0x00025882)
#define NLS_NOM_SCORE_MOTOR_SUBSC_GLAS_COMA (0x00025883)
#define NLS_NOM_SCORE_SUBSC_VERBAL_GLAS_COMA (0x00025884)
#define NLS_NOM_FLOW_PUMP_HEART_LUNG_SUCTION (0x0002F976)
#define NLS_NOM_EEG_RATIO_SUPPRN (0x0002F04A)
#define NLS_NOM_RESP_BREATH_ASSIST_CNT (0x0002F89A)
#define NLS_NOM_RES_VASC_SYS (0x00024B28)
#define NLS_NOM_RES_VASC_SYS_INDEX (0x00024900)
#define NLS_NOM_TEMP_AIR_INCUB (0x0002F12A)
#define NLS_NOM_PULS_OXIM_PERF_REL_TELE (0x0002F12C)
#define NLS_NOM_TEMP_BLD (0x0002E014)
#define NLS_NOM_TEMP_INFRARED (0x0002FB4A)
#define NLS_NOM_TEMP_VESICAL (0x0002F0C4)
#define NLS_NOM_EEG_PWR_SPEC_THETA_ABS_LEFT (0x0002F869)
#define NLS_NOM_EEG_PWR_SPEC_THETA_ABS_RIGHT (0x0002F86A)
#define NLS_NOM_VOL_FLUID_THORAC (0x0002F8C5)
#define NLS_NOM_VOL_FLUID_THORAC_INDEX (0x0002F8C6)
#define NLS_NOM_TIME_PD_THROMBIN (0x0002F191)
#define NLS_NOM_TIME_PD_THROMBOPLAS (0x0002F193)
#define NLS_NOM_VOL_AWAY_TIDAL (0x0002513C)
#define NLS_NOM_VOL_AWAY_TIDAL_PSV (0x0002F8C3)
#define NLS_NOM_AWAY_TC (0x0002F816)
#define NLS_NOM_TIME_PD_FROM_LAST_MSMT (0x0002F8A2)
#define NLS_NOM_RATIO_INSP_TOTAL_BREATH_SPONT (0x0002F990)
#define NLS_NOM_CONC_BILI_TOT (0x0002F177)
#define NLS_NOM_FLOW_AWAY_TOT (0x0002F881)
#define NLS_NOM_CONC_tCA_SER (0x0002F15D)
#define NLS_NOM_CONC_CO2_TOT (0x0002F825)
#define NLS_NOM_EEG_PWR_SPEC_TOT (0x000259B8)
#define NLS_EEG_NAMES_CHAN_TP1 (0x800F5403)
#define NLS_EEG_NAMES_CHAN_TP2 (0x800F5404)
#define NLS_NOM_CONC_PROT_TOT (0x0002F179)
#define NLS_NOM_VOL_URINE_BAL_PD_INSTANT (0x0002F8CE)
#define NLS_NOM_EEG_PWR_SPEC_TOT_LEFT (0x0002F871)
#define NLS_NOM_EEG_PWR_SPEC_TOT_RIGHT (0x0002F872)
#define NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS_TOTAL (0x0002F991)
#define NLS_NOM_TRAIN_OF_FOUR_CNT (0x0002F8AB)
#define NLS_NOM_TRAIN_OF_FOUR_CNT (0x0002F8AB)
#define NLS_NOM_RATIO_TRAIN_OF_FOUR (0x0002F897)
#define NLS_NOM_RATIO_TRAIN_OF_FOUR (0x0002F897)
#define NLS_NOM_TRAIN_OF_FOUR_1 (0x0002F8A7)
#define NLS_NOM_TRAIN_OF_FOUR_1 (0x0002F8A7)
#define NLS_NOM_TRAIN_OF_FOUR_2 (0x0002F8A8)
#define NLS_NOM_TRAIN_OF_FOUR_2 (0x0002F8A8)
#define NLS_NOM_TRAIN_OF_FOUR_3 (0x0002F8A9)
#define NLS_NOM_TRAIN_OF_FOUR_3 (0x0002F8A9)
#define NLS_NOM_TRAIN_OF_FOUR_4 (0x0002F8AA)
#define NLS_NOM_TRAIN_OF_FOUR_4 (0x0002F8AA)
#define NLS_NOM_CO2_TCUT (0x000250CC)
#define NLS_NOM_O2_TCUT (0x000250D0)
#define NLS_NOM_IMPED_TTHOR (0x000250E4)
#define NLS_NOM_CONC_TGL (0x0002F16F)
#define NLS_NOM_TWITCH_AMPL (0x0002F8AC)
#define NLS_NOM_TWITCH_AMPL (0x0002F8AC)
#define NLS_NOM_TEMP_TYMP (0x00024B78)
#define NLS_NOM_PRESS_BLD_ART_UMB (0x00024A28)
#define NLS_NOM_PRESS_BLD_VEN_UMB (0x00024A48)
#define NLS_NOM_PRESS_BLD (0x00024A00)
#define NLS_NOM_TEMP (0x00024B48)
#define NLS_NOM_CONC_UREA_GEN (0x0002F172)
#define NLS_NOM_FLOW_URINE_INSTANT (0x0002680C)
#define NLS_NOM_VOL_URINE_SHIFT (0x0002F8CF)
#define NLS_NOM_CONC_K_URINE_EXCR (0x0002F198)
#define NLS_NOM_CONC_CREA_URINE (0x0002F196)
#define NLS_NOM_CONC_OSM_URINE (0x0002F199)
#define NLS_NOM_RATIO_URINE_SER_OSM (0x0002F898)
#define NLS_NOM_CONC_K_URINE (0x0002F197)
#define NLS_NOM_RATIO_CONC_URINE_CREA_SER (0x0002F892)
#define NLS_NOM_CONC_NA_EXCR (0x0002F830)
#define NLS_NOM_RATIO_CONC_URINE_NA_K (0x0002F893)
#define NLS_NOM_CONC_UREA_URINE (0x0002F195)
#define NLS_NOM_VOL_URINE_BAL_PD (0x00026824)
#define NLS_NOM_CONC_HB_O2_VEN (0x00027048)
#define NLS_NOM_TEMP_VEN (0x00024B7C)
#define NLS_NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX (0x00025190)
#define NLS_NOM_CAPAC_VITAL (0x00025080)
#define NLS_NOM_TIME_PD_PT_WB (0x0002F18F)
#define NLS_NOM_WEIGHT_URINE_COL (0x0002F8D3)
#define NLS_NOM_WB_CNT (0x0002F168)

/// Physio IDs
#define NOM_ECG_ELEC_POTL_I (0x0101)
#define NOM_ECG_ELEC_POTL_II (0x0102)
#define NOM_ECG_ELEC_POTL_III (0x013D)
#define NOM_ECG_ELEC_POTL_AVR (0x013E)
#define NOM_ECG_ELEC_POTL_AVL (0x013F)
#define NOM_ECG_ELEC_POTL_AVF (0x0140)
#define NOM_ECG_ELEC_POTL_V (0x0143)
#define NOM_ECG_ELEC_POTL_MCL (0x014B)
#define NOM_ECG_ELEC_POTL_V1 (0x0103)
#define NOM_ECG_ELEC_POTL_V2 (0x0104)
#define NOM_ECG_ELEC_POTL_V3 (0x0105)
#define NOM_ECG_ELEC_POTL_V4 (0x0106)
#define NOM_ECG_ELEC_POTL_V5 (0x0107)
#define NOM_ECG_ELEC_POTL_V6 (0x0108)
#define NOM_ECG_ELEC_POTL_MCL1 (0x014C)
#define NOM_PULS_OXIM_PLETH (0x4BB4)
#define NOM_PULS_OXIM_PLETH_LEFT (0xF08D)
#define NOM_PULS_OXIM_PLETH_RIGHT (0xF08C)
#define NOM_FLOW_AWAY (0x50D4)
#define NOM_PRESS_AWAY (0x50F0)
#define NOM_PRESS_AWAY_INSP (0x5108)
#define NOM_VENT_FLOW_INSP (0x518C)
#define NOM_METRIC_NOS (0xEFFF)
#define NOM_ECG_ELEC_POTL_V1 (0x0103)
#define NOM_ECG_ELEC_POTL_V2 (0x0104)
#define NOM_ECG_ELEC_POTL_V3 (0x0105)
#define NOM_ECG_ELEC_POTL_V4 (0x0106)
#define NOM_ECG_ELEC_POTL_V5 (0x0107)
#define NOM_ECG_ELEC_POTL_V6 (0x0108)




/// Numeric Physio ID
#define NOM_ECG_AMPL_ST_INDEX (0xF03D)
#define NOM_PULS_OXIM_PERF_REL (0x4BB0)
#define NOM_PULS_OXIM_PERF_REL_LEFT (0xF08A)
#define NOM_PULS_OXIM_PERF_REL_RIGHT (0xF08B)
#define NOM_PRESS_BLD_ART_PULM_WEDGE (0x4A24)
#define NOM_VOL_BLD_STROKE (0x4B84)
#define NOM_VOL_BLD_STROKE_INDEX (0xF048)
#define NOM_VOL_BLD_STROKE_VAR (0xF049)
#define NOM_GRAD_PRESS_BLD_AORT_POS_MAX (0x4C25)
#define NOM_OUTPUT_CARD_INDEX (0x490C)
#define NOM_VOL_BLD_INTRA_THOR (0xF040)
#define NOM_VOL_BLD_INTRA_THOR_INDEX (0xF041)
#define NOM_VOL_LUNG_WATER_EXTRA_VASC (0xF042)
#define NOM_VOL_LUNG_WATER_EXTRA_VASC_INDEX (0xF043)
#define NOM_VOL_GLOBAL_END_DIA (0xF044)
#define NOM_VOL_GLOBAL_END_DIA_INDEX (0xF045)
#define NOM_CARD_FUNC_INDEX (0xF046)
#define NOM_SAT_O2_ART (0x4B34)
#define NOM_SAT_DIFF_O2_ART_ALV (0x4B40)
#define NOM_CONC_AWAY_O2_ET (0x5378)
#define NOM_VENT_CONC_AWAY_O2_INSP (0x7498)
#define NOM_IMPED_TTHOR (0x50E4)
#define NOM_FLOW_CO2_PROD_RESP (0x50E0)
#define NOM_PRESS_RESP_PLAT (0x50E8)
#define NOM_PRESS_AWAY_MIN (0x50F2)
#define NOM_PRESS_AWAY_CTS_POS (0x50F4)
#define NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC (0x5100)
#define NOM_PRESS_AWAY_INSP (0x5108)
#define NOM_PRESS_AWAY_INSP_MAX (0x5109)
#define NOM_PRESS_AWAY_INSP_MEAN (0x510B)
#define NOM_RATIO_IE (0x5118)
#define NOM_RATIO_AWAY_DEADSP_TIDAL (0x511C)
#define NOM_RES_AWAY (0x5120)
#define NOM_VOL_AWAY_TIDAL (0x513C)
#define NOM_VOL_MINUTE_AWAY (0x5148)
#define NOM_VENT_VOL_MINUTE_AWAY_SPONT (0xF091)
#define NOM_VENT_CONC_AWAY_O2_DELTA (0x5168)
#define NOM_VENT_AWAY_CO2_EXP (0x517C)
#define NOM_VENT_FLOW_INSP (0x518C)
#define NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX (0x5190)
#define NOM_VENT_PRESS_OCCL (0x519C)
#define NOM_VENT_PRESS_AWAY_END_EXP_POS (0x51A8)
#define NOM_VENT_VOL_AWAY_DEADSP (0x51B0)
#define NOM_VENT_VOL_AWAY_DEADSP_REL (0x51B4)
#define NOM_VENT_VOL_LUNG_TRAPD (0x51B8)
#define NOM_VENT_VOL_LEAK (0x5370)
#define NOM_VENT_VOL_LUNG_ALV (0x5374)
#define NOM_CAPAC_VITAL (0x5080)
#define NOM_COMPL_LUNG (0x5088)
#define NOM_COMPL_LUNG_DYN (0x508C)
#define NOM_COMPL_LUNG_STATIC (0x5090)
#define NOM_EMG_ELEC_POTL_MUSCL (0x593C)
#define NOM_EEG_PWR_SPEC_TOT (0x59B8)
#define NOM_EEG_RATIO_SUPPRN (0xF04A)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE (0x5988)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN (0x597C)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK (0x5984)
#define NOM_EEG_PWR_SPEC_ALPHA_REL (0x59D4)
#define NOM_EEG_PWR_SPEC_BETA_REL (0x59D8)
#define NOM_EEG_PWR_SPEC_DELTA_REL (0x59DC)
#define NOM_EEG_PWR_SPEC_THETA_REL (0x59E0)
#define NOM_TEMP_AWAY (0x4B54)
#define NOM_CONC_AWAY_N2_ET (0x5380)
#define NOM_CONC_AWAY_N2_INSP (0x5384)
#define NOM_CONC_AWAY_N2O_ET (0x522C)
#define NOM_CONC_AWAY_SUM_MAC_ET (0xF05E)
#define NOM_CONC_AWAY_SUM_MAC_INSP (0xF05F)
#define NOM_WK_LV_STROKE_INDEX (0x4904)
#define NOM_WK_RV_STROKE_INDEX (0x4908)
#define NOM_SAT_O2_CONSUMP (0x4B00)
#define NOM_RES_VASC_PULM (0x4B24)
#define NOM_WK_CARD_LEFT (0x4B90)
#define NOM_WK_CARD_RIGHT (0x4B94)
#define NOM_WK_LV_STROKE (0x4B9C)
#define NOM_WK_RV_STROKE (0x4BA4)
#define NOM_SCORE_GLAS_COMA (0x5880)
#define NOM_SCORE_EYE_SUBSC_GLAS_COMA (0x5882)
#define NOM_SCORE_MOTOR_SUBSC_GLAS_COMA (0x5883)
#define NOM_SCORE_SUBSC_VERBAL_GLAS_COMA (0x5884)
#define NOM_CIRCUM_HEAD (0x5900)
#define NOM_TIME_PD_PUPIL_REACT_LEFT (0x5924)
#define NOM_TIME_PD_PUPIL_REACT_RIGHT (0x5928)
#define NOM_CONC_PH_ART (0x7004)
#define NOM_CONC_PCO2_ART (0x7008)
#define NOM_CONC_PO2_ART (0x700C)
#define NOM_CONC_HB_ART (0x7014)
#define NOM_CONC_HB_O2_ART (0x7018)
#define NOM_CONC_PH_VEN (0x7034)
#define NOM_CONC_PCO2_VEN (0x7038)
#define NOM_CONC_PO2_VEN (0x703C)
#define NOM_CONC_HB_O2_VEN (0x7048)
#define NOM_CONC_NA_URINE (0x706C)
#define NOM_CONC_NA_SERUM (0x70D8)
#define NOM_CONC_PH_GEN (0x7104)
#define NOM_CONC_HCO3_GEN (0x7108)
#define NOM_CONC_NA_GEN (0x710C)
#define NOM_CONC_K_GEN (0x7110)
#define NOM_CONC_GLU_GEN (0x7114)
#define NOM_CONC_PCO2_GEN (0x7140)
#define NOM_CONC_PO2_GEN (0x7174)
#define NOM_CONC_HCT_GEN (0x7184)
#define NOM_BASE_EXCESS_BLD_ART (0x716C)
#define NOM_RES_VASC_PULM_INDEX (0xF067)
#define NOM_WK_CARD_LEFT_INDEX (0xF068)
#define NOM_WK_CARD_RIGHT_INDEX (0xF069)
#define NOM_SAT_O2_CONSUMP_INDEX (0xF06A)
#define NOM_PRESS_AIR_AMBIENT (0xF06B)
#define NOM_SAT_O2_DELIVER (0xF06D)
#define NOM_SAT_O2_DELIVER_INDEX (0xF06E)
#define NOM_RATIO_SAT_O2_CONSUMP_DELIVER (0xF06F)
#define NOM_RATIO_ART_VEN_SHUNT (0xF070)
#define NOM_INTENS_LIGHT (0xF072)
#define NOM_VOL_THERMO_EXTRA_VASC_INDEX (0xF07A)
#define NOM_CONC_CHLORIDE_GEN (0x7168)
#define NOM_CONC_BLD_UREA_NITROGEN (0xF08F)
#define NOM_CONC_DIFF_HB_O2_ATR_VEN (0xF092)
#define NOM_AREA_BODY_SURFACE (0xF071)
#define NOM_PAT_WEIGHT (0xF093)
#define NOM_PAT_HEIGHT (0xF094)
#define NOM_ECG_V_P_C_FREQ (0x4268)
#define NOM_VENT_MODE_MAND_INTERMIT (0xD02A)
#define NOM_AREA_BODY_SURFACE (0xF071)
#define NOM_VOL_GLOBAL_END_DIA (0xF044)
#define NOM_VOL_GLOBAL_END_DIA_INDEX (0xF045)
#define NOM_PRESS_AWAY_INSP_MAX (0x5109)
#define NOM_PRESS_AWAY_MIN (0x50F2)
#define NOM_PRESS_AIR_AMBIENT (0xF06B)
#define NOM_VOL_MINUTE_AWAY (0x5148)
#define NOM_PRESS_AWAY (0x50F0)
#define NOM_PRESS_AWAY_INSP_MEAN (0x510B)
#define NOM_PULS_OXIM_PERF_REL (0x4BB0)
#define NOM_EEG_PWR_SPEC_ALPHA_REL (0x59D4)
#define NOM_EEG_PWR_SPEC_BETA_REL (0x59D8)
#define NOM_EEG_PWR_SPEC_DELTA_REL (0x59DC)
#define NOM_EEG_PWR_SPEC_THETA_REL (0x59E0)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN (0x597C)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK (0x5984)
#define NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE (0x5988)
#define NOM_EEG_PWR_SPEC_TOT (0x59B8)
#define NOM_CONC_CA_GEN (0x7118)
#define NOM_CONC_HB_ART (0x7014)
#define NOM_CONC_PH_GEN (0x7104)
#define NOM_CONC_PH_ART (0x7004)
#define NOM_CONC_PH_VEN (0x7034)
#define NOM_CONC_PO2_GEN (0x7174)
#define NOM_CONC_PO2_ART (0x700C)
#define NOM_CONC_PO2_VEN (0x703C)
#define NOM_CONC_PCO2_GEN (0x7140)
#define NOM_CONC_PCO2_ART (0x7008)
#define NOM_CONC_PCO2_VEN (0x7038)
#define NOM_SAT_O2_ART (0x4B34)
#define NOM_CONC_HCO3_GEN (0x7108)
#define NOM_CONC_BASE_EXCESS_ECF (0xF090)
#define NOM_VENT_CONC_AWAY_O2_INSP (0x7498)
#define NOM_BASE_EXCESS_BLD_ART (0x716C)
#define NOM_VOL_AWAY_TIDAL (0x513C)
#define NOM_VENT_PRESS_AWAY_END_EXP_POS (0x51A8)
#define NOM_VOL_MINUTE_AWAY (0x5148)
#define NOM_PRESS_AWAY_INSP_MAX (0x5109)
#define NOM_RATIO_IE (0x5118)
#define NOM_PRESS_AWAY_CTS_POS (0x50F4)

#define NOM_CONC_K_URINE (61847)
#define NOM_CONC_UREA_URINE (61845)
#define NOM_CONC_GLU_URINE (61855)
#define NOM_CONC_CA_URINE (61852)
#define NOM_CONC_UREA_GEN (61810)
#define NOM_TEMP_ORAL (61704)
#define NOM_PRESS_GEN_3 (61612)

// SUBSCRIPT CAPITAL E
#define SUBSCRIPT_CAPITAL_E_CHAR (0xE145)
// SUBSCRIPT CAPITAL L
#define SUBSCRIPT_CAPITAL_L_CHAR (0xE14C)
// LITER PER - used in 4 char unit "l/min"
#define LITER_PER_CHAR (0xE400)
// HYDROGEN - Used in 4 char unit "cmH2O"
#define HYDROGEN_CHAR (0xE401)
// ALARM STAR
#define ALARM_STAR_CHAR (0xE40D)
// CAPITAL_V_WITH_DOT_ABOVE (V with dot)
#define CAPITAL_V_WITH_DOT_ABOVE_CHAR (0xE425)
// The character 0xFEFF is used as FILL character. For each wide asian
// character, a FILL character is appended for size calculations.
#define ZERO_WIDTH_NO_BREAK_SPACE_CHAR (0xFEFF)

} // end of namespace intellivue

#pragma pack(pop)   /* restore original alignment from stack */
#endif
