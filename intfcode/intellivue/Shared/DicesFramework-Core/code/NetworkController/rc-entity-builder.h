#ifndef ENTITY_BUILDER_SRC_RETURN_CODES_H_
#define ENTITY_BUILDER_SRC_RETURN_CODES_H_

#include <string>

enum class DicesRcEntityBuilder
{
  OK = 0,
  FAIL,

  NETWORK_CONTROLLER_POINTER_IS_NULL,
  PARTICIPANT_POINTER_IS_NULL,
  SUBSCRIBER_POINTER_IS_NULL,
  PUBLISHER_POINTER_IS_NULL,
  TOPIC_POINTER_IS_NULL,

  SET_HOST_ID_AND_APP_ID_FAILURE,
  CREATE_PARTICIPANT_FAILURE,
  CREATE_PUBLISHER_FAILURE,
  CREATE_SUBSCRIBER_FAILURE,
  REGISTER_TYPES_FAILURE,

  TOPIC_NAME_IS_EMPTY,

  CREATE_TOPIC_FAILED,
  CREATE_READER_FAILED,
  CREATE_WRITER_FAILED,
  REGISTER_TYPE_FAILED
};

class DicesRcEntityBuilderStatusMessage
{
 public:

  const static std::string DicesRcEntityBuilderToString(const DicesRcEntityBuilder error_code)
  {
    std::string error_message;

    switch (error_code)
    {
      case DicesRcEntityBuilder::OK:
        error_message = "Ok";
        break;
      case DicesRcEntityBuilder::FAIL:
        error_message = "Fail";
        break;

      case DicesRcEntityBuilder::NETWORK_CONTROLLER_POINTER_IS_NULL:
        error_message = "Network Controller pointer is null";
        break;
      case DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL:
        error_message = "Participant pointer is null";
        break;
      case DicesRcEntityBuilder::SUBSCRIBER_POINTER_IS_NULL:
        error_message = "Subscriber pointer is null";
        break;
      case DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL:
        error_message = "Publisher pointer is null";
        break;
      case DicesRcEntityBuilder::TOPIC_POINTER_IS_NULL:
        error_message = "Topic pointer is null";
        break;
      case DicesRcEntityBuilder::SET_HOST_ID_AND_APP_ID_FAILURE:
        error_message = "Failed to set host id and app id of the DDS GUID";
        break;
      case DicesRcEntityBuilder::CREATE_PARTICIPANT_FAILURE:
        error_message = "Unable to create participant from provided configuration";
        break;
      case DicesRcEntityBuilder::CREATE_PUBLISHER_FAILURE:
        error_message = "Failed to create publisher by name";
        break;
      case DicesRcEntityBuilder::CREATE_SUBSCRIBER_FAILURE:
        error_message = "Failed to create subscriber by name";
        break;
      case DicesRcEntityBuilder::REGISTER_TYPES_FAILURE:
        error_message = "Failed to register DICES types";
        break;
      case DicesRcEntityBuilder::TOPIC_NAME_IS_EMPTY:
        error_message = "Topic name is empty";
        break;
      case DicesRcEntityBuilder::CREATE_TOPIC_FAILED:
        error_message = "Create topic failed";
        break;
      case DicesRcEntityBuilder::CREATE_READER_FAILED:
        error_message = "Create reader failed";
        break;
      case DicesRcEntityBuilder::CREATE_WRITER_FAILED:
        error_message = "Create writer failed";
        break;
      case DicesRcEntityBuilder::REGISTER_TYPE_FAILED:
        error_message = "Type registration failed";
        break;

      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }

    return error_message;
  }

 private:
  // Disallow use of implicitly generated member functions:
  DicesRcEntityBuilderStatusMessage(const DicesRcEntityBuilderStatusMessage &other);
  DicesRcEntityBuilderStatusMessage &operator=(const DicesRcEntityBuilderStatusMessage &other);
};

#endif
