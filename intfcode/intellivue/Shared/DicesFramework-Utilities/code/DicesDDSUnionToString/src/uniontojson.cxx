#include "uniontojson.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <iomanip>
#include "returncodes.h"

static log4cplus::Logger root_log = log4cplus::Logger::getRoot();

static const char* kJSONUndefined = "{}";

UnionToJSON::UnionToJSON()
{
}

UnionToJSON::~UnionToJSON()
{
}

DicesRcDDSUnionToString UnionToJSON::EffectiveTimeToJSON(ice::EffectiveTime* effective, std::string* return_str)
{
  static const char* sfn = "UnionToJSON::EffectiveTimeToJSON() ";
  // This function should be able to handle null pointer effectives
  // Because of optionals in IDL.
  if (!return_str)
  {
    LOG4CPLUS_ERROR(root_log, sfn << "Function argument return_str is a "
                                     "null pointer.");
    return DicesRcDDSUnionToString::FAIL;
  }

  if (!effective)
  {
    *return_str = "{}";
    return DicesRcDDSUnionToString::OK;
  }

  std::stringstream ss;
  ss << "{"
     << "\"_d\":" << static_cast<int>(effective->_d) << ",";
  switch(effective->_d)
  {
    case ice::EffectiveTimeType::et_datetime:
    {
      ss << "\"_u\":"
         << "{"
         << "\"datetime\":\"" << std::string(effective->_u.datetime) << "\""
         << "}"
         << "}";
      break;
    }
    case ice::EffectiveTimeType::et_period:
    {
      std::string period_start;
      std::string period_end;
      if (effective->_u.period.start)
      {
        period_start = std::string(effective->_u.period.start);
      }
      if (effective->_u.period.end)
      {
        period_end = std::string(effective->_u.period.end);
      }
      ss << "\"_u\":"
         << "{"
         << "\"start\":\"" << period_start << "\","
         << "\"end\":\"" << period_end << "\""
         << "}"
         << "}";
      break;
    }
    default:
      LOG4CPLUS_WARN(root_log, sfn << "Unknown ice::EffectiveTimeType ("
                     << static_cast<int>(effective->_d)
                     << ")");
      ss << "\"_u\":"
         << kJSONUndefined
         << "}";
      break;
  }
  *return_str = ss.str();
  return DicesRcDDSUnionToString::OK;
}

DicesRcDDSUnionToString UnionToJSON::EffectiveTimeToString(ice::EffectiveTime* eff_time, std::string* return_str)
{
    static const char* sfn = "UnionToJSON::EffectiveTimeToString() ";
    // This function should be able to handle null pointer effectives
    // Because of optionals in IDL.
    if (!return_str)
    {
      LOG4CPLUS_ERROR(root_log, sfn << "Function argumetn return_str is a "
                                       "null pointer.");
      return DicesRcDDSUnionToString::FAIL;
    }

    if (!eff_time)
    {
      *return_str = "";
      return DicesRcDDSUnionToString::OK;
    }

    switch(eff_time->_d)
    {
      case ice::EffectiveTimeType::et_datetime:
      {
        *return_str = std::string(eff_time->_u.datetime);
        break;
      }

      case ice::EffectiveTimeType::et_period:
      {
        std::stringstream val;
        val << "";
        if (eff_time->_u.period.start)
        {
          val << std::string(eff_time->_u.period.start);
          if (eff_time->_u.period.end)
          {
            val << " to ";
          }
        }
        if (eff_time->_u.period.end)
        {
          val << std::string(eff_time->_u.period.end);
        }
        *return_str = val.str();
        break;
      }
      default:
      {
        LOG4CPLUS_WARN(root_log, sfn << "Unknown ice::EffectiveTimeType ("
                     << static_cast<int>(eff_time->_d)
                     << ")");
        *return_str = ""; // We can't parse, returning undefined
        break;
      }
    }
    return DicesRcDDSUnionToString::OK;
}

DicesRcDDSUnionToString UnionToJSON::ObservationValueToJSON(
    ice::ObservationValue* obs_val,
    std::string* return_str)
{
  static const char* sfn = "UnionToJSON::ObservationValueToJSON() ";
  // This function should be able to handle null pointer effectives
  // Because of optionals in IDL.
  if (!return_str)
  {
    LOG4CPLUS_ERROR(root_log, sfn << "Function argumetn return_str is a "
                                     "null pointer.");
    return DicesRcDDSUnionToString::FAIL;
  }

  // Initialize string values for optional members to NULL
  static const char* knull_value = "NULL";

  if (!obs_val)
  {
    *return_str = "{}";
    return DicesRcDDSUnionToString::OK;
  }

  std::stringstream ss;
  ss << "{"
     << "\"_d\":" << static_cast<int>(obs_val->_d) << ",";
  switch(obs_val->_d)
  {
    case ice::ObservationValueType::ov_quantity:
    {
      ss << "\"_u\":"
         << "{"
            // Beginning of inherited members from SimpleQuantity
         << "\"value\":"
         << "{"
         << "\"value\":\"" << std::fixed << std::setprecision(static_cast<int>(obs_val->_u.val_quantity.value.presentation_precision)) << static_cast<float>(obs_val->_u.val_quantity.value.value) << "\","
         << "\"presentation_precision\":\"" << std::to_string(static_cast<int>(obs_val->_u.val_quantity.value.presentation_precision)) << "\""
         << "},"
         << "\"unit\":\"" << std::string(obs_val->_u.val_quantity.unit) << "\","
         << "\"system\":\"" << std::string(obs_val->_u.val_quantity.system) << "\","
         << "\"code_\":\"" << std::string(obs_val->_u.val_quantity.code_) << "\","
            // End inheritance.
         << "\"comparator\":\"" << std::string(obs_val->_u.val_quantity.comparator) << "\""
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_codeableconcept:
    {
      ss << "\"_u\":"
         << "{"
         << "\"coding\":"
         << "{"
         << "\"system\":\"" << std::string(obs_val->_u.val_codeableconcept.coding.system) << "\","
         << "\"version\":\"" << std::string(obs_val->_u.val_codeableconcept.coding.version) << "\","
         << "\"code_\":\"" << std::string(obs_val->_u.val_codeableconcept.coding.code_) << "\","
         << "\"display\":\"" << std::string(obs_val->_u.val_codeableconcept.coding.display) << "\","
         << "\"user_selected\":\"" << std::to_string(obs_val->_u.val_codeableconcept.coding.user_selected) << "\""
         << "},"
         << "\"text\":\"" << std::string(obs_val->_u.val_codeableconcept.text) << "\""
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_string:
    {
      ss << "\"_u\":"
         << "{"
         << "\"val_string\":\"" << std::string(obs_val->_u.val_string) << "\""
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_range:
    {
      ss << "\"_u\":"
         << "{"
         << "\"low\":"
         << "{"
         << "\"value\":"
         << "{"
         << "\"value\":\"" << std::fixed << std::setprecision(static_cast<int>(obs_val->_u.val_range.low.value.presentation_precision)) << static_cast<float>(obs_val->_u.val_range.low.value.value) << "\","
         << "\"presentation_precision\":\"" << std::to_string(static_cast<int>(obs_val->_u.val_range.low.value.presentation_precision)) << "\""
         << "},"
         << "\"unit\":\"" << std::string(obs_val->_u.val_range.low.unit) << "\","
         << "\"system\":\"" << std::string(obs_val->_u.val_range.low.system) << "\","
         << "\"code_\":\"" << std::string(obs_val->_u.val_range.low.code_) << "\""
         << "},"
         << "\"high\":"
         << "{"
         << "\"value\":"
         << "{"
         << "\"value\":\"" << std::fixed << std::setprecision(static_cast<int>(obs_val->_u.val_range.high.value.presentation_precision)) << static_cast<float>(obs_val->_u.val_range.high.value.value) << "\","
         << "\"presentation_precision\":\"" << std::to_string(static_cast<int>(obs_val->_u.val_range.high.value.presentation_precision)) << "\""
         << "},"
         << "\"unit\":\"" << std::string(obs_val->_u.val_range.high.unit) << "\","
         << "\"system\":\"" << std::string(obs_val->_u.val_range.high.system) << "\","
         << "\"code_\":\"" << std::string(obs_val->_u.val_range.high.code_) << "\""
         << "}"
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_ratio:
    case ice::ObservationValueType::ov_sampleddata:
    case ice::ObservationValueType::ov_attachment:
    {
      LOG4CPLUS_WARN(root_log, sfn << "The following types are not "
                                      "implemented yet: "
                                      "ice::ObservationValueType::ov_ratio, "
                                      "ice::ObservationValueType::ov_sampleddata"
                                      "and ice::ObservationValueType::ov_attachment.");
      ss << "\"_u\":{}"; // We can't parse, returning undefined
      break;
    }
    case ice::ObservationValueType::ov_time:
    {
      ss << "\"_u\":"
         << "{"
         << "\"val_time\":\"" << std::string(obs_val->_u.val_time) << "\""
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_datetime:
    {
      ss << "\"_u\":"
         << "{"
         << "\"val_datetime\":\"" << std::string(obs_val->_u.val_datetime) << "\""
         << "}";
      break;
    }
    case ice::ObservationValueType::ov_period:
    {
      ss << "\"_u\":"
         << "{";
      if (obs_val->_u.val_period.start)
      {
        ss << "\"start\":\"" << std::string(obs_val->_u.val_period.start) << "\"";
        if (obs_val->_u.val_period.end)
        {
          ss << ",";
        }
      }
      if (obs_val->_u.val_period.end)
      {
        ss << "\"end\":\"" << std::string(obs_val->_u.val_period.end) << "\"";
      }
      ss << "}";
      break;
    }
    default:
    {
      LOG4CPLUS_WARN(root_log, sfn << "Unknown ice::ObservationValueType ("
                     << static_cast<int>(obs_val->_d)
                     << ")");
      ss << "\"_u\":{}"; // We can't parse, returning undefined
      break;
    }
  }
  ss << "}";
  *return_str = ss.str();

  return DicesRcDDSUnionToString::OK;
}

DicesRcDDSUnionToString UnionToJSON::ObservationValue_valueToString(
    ice::ObservationValue* obs_val,
    std::string* return_str)
{
  static const char* sfn = "UnionToJSON::ObservationValue_valueToString() ";
  // This function should be able to handle null pointer effectives
  // Because of optionals in IDL.
  if (!return_str)
  {
    LOG4CPLUS_ERROR(root_log, sfn << "Function argumetn return_str is a "
                                     "null pointer.");
    return DicesRcDDSUnionToString::FAIL;
  }

  if (!obs_val)
  {
    *return_str = "";
    return DicesRcDDSUnionToString::OK;
  }

  switch(obs_val->_d)
  {
    case ice::ObservationValueType::ov_quantity:
    {
      std::stringstream val;
      val << std::fixed <<
             std::setprecision(static_cast<int>(obs_val->_u.val_quantity.value.presentation_precision)) <<
             static_cast<float>(obs_val->_u.val_quantity.value.value);
      *return_str = val.str();
      break;
    }

    case ice::ObservationValueType::ov_codeableconcept:
    {
      std::string val;
      if (obs_val->_u.val_codeableconcept.text)
      {
        val = std::string(obs_val->_u.val_codeableconcept.text);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_string:
    {
      std::string val;
      if (obs_val->_u.val_string)
      {
        val = std::string(obs_val->_u.val_string);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_range:
    {
      std::stringstream val;
      val << std::fixed <<
             std::setprecision(static_cast<int>(obs_val->_u.val_range.low.value.presentation_precision)) <<
             static_cast<float>(obs_val->_u.val_range.low.value.value) <<
             " to " <<
             std::fixed <<
             std::setprecision(static_cast<int>(obs_val->_u.val_range.high.value.presentation_precision)) <<
             static_cast<float>(obs_val->_u.val_range.high.value.value);
      *return_str = val.str();
      break;
    }

    case ice::ObservationValueType::ov_ratio:
    case ice::ObservationValueType::ov_sampleddata:
    case ice::ObservationValueType::ov_attachment:
    {
      LOG4CPLUS_WARN(root_log, sfn << "The following types are not "
                                      "yet defined: "
                                      "ice::ObservationValueType::ov_ratio, "
                                      "ice::ObservationValueType::ov_sampleddata"
                                      "and ice::ObservationValueType::ov_attachment.");
      *return_str = ""; // We can't parse, returning undefined
      break;
    }

    case ice::ObservationValueType::ov_time:
    {
      std::string val;
      if (obs_val->_u.val_time)
      {
        val = std::string(obs_val->_u.val_time);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_datetime:
    {
      std::string val;
      if (obs_val->_u.val_datetime)
      {
        val = std::string(obs_val->_u.val_datetime);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_period:
    {
      std::stringstream val;
      val << "";
      if (obs_val->_u.val_period.start)
      {
        val << std::string(obs_val->_u.val_period.start);
        if (obs_val->_u.val_period.end)
        {
          val << " to ";
        }
      }
      if (obs_val->_u.val_period.end)
      {
        val << std::string(obs_val->_u.val_period.end);
      }
      *return_str = val.str();
      break;
    }

    default:
    {
      LOG4CPLUS_WARN(root_log, sfn << "Unknown ice::ObservationValueType ("
                     << static_cast<int>(obs_val->_d)
                     << ")");
      *return_str = ""; // We can't parse, returning undefined
      break;
    }
  }

  return DicesRcDDSUnionToString::OK;
}

DicesRcDDSUnionToString UnionToJSON::ObservationValue_unitsToString(
    ice::ObservationValue* obs_val,
    std::string* return_str)
{
  static const char* sfn = "UnionToJSON::ObservationValue_unitsToString() ";
  // This function should be able to handle null pointer effectives
  // Because of optionals in IDL.
  if (!return_str)
  {
    LOG4CPLUS_ERROR(root_log, sfn << "Function argumetn return_str is a "
                                     "null pointer.");
    return DicesRcDDSUnionToString::FAIL;
  }

  if (!obs_val)
  {
    *return_str = "";
    return DicesRcDDSUnionToString::OK;
  }

  switch(obs_val->_d)
  {
    case ice::ObservationValueType::ov_quantity:
    {
      std::string val;
      if (obs_val->_u.val_quantity.unit)
      {
        val = std::string(obs_val->_u.val_quantity.unit);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_codeableconcept:
    {
      // this is a string that describes the codableconcept,
      // it's not necessarity "units" in the traditional sense.
      std::string val;
      if (obs_val->_u.val_codeableconcept.coding.display)
      {
        val = std::string(obs_val->_u.val_codeableconcept.coding.display);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_string:
    {
      *return_str = "";
      break;
    }

    case ice::ObservationValueType::ov_range:
    {
      std::string val;
      if (obs_val->_u.val_range.low.unit
          && obs_val->_u.val_range.high.unit)
      {
        val = std::string(obs_val->_u.val_range.low.unit) +
            " and " + std::string(obs_val->_u.val_range.high.unit);
      }
      *return_str = val;
      break;
    }

    case ice::ObservationValueType::ov_ratio:
    case ice::ObservationValueType::ov_sampleddata:
    case ice::ObservationValueType::ov_attachment:
    {
      LOG4CPLUS_WARN(root_log, sfn << "The following types are not "
                                      "implemented yet: "
                                      "ice::ObservationValueType::ov_ratio, "
                                      "ice::ObservationValueType::ov_sampleddata"
                                      "and ice::ObservationValueType::ov_attachment.");
      *return_str = ""; // We can't parse, returning undefined
      break;
    }

    case ice::ObservationValueType::ov_time:
    {
      // Maybe "units" should be built into the IDL
      *return_str = "";
      break;
    }

    case ice::ObservationValueType::ov_datetime:
    {
      // Maybe "units" should be built into the IDL
      *return_str = "";
      break;
    }

    case ice::ObservationValueType::ov_period:
    {
      // Maybe "units" should be built into the IDL
      *return_str = "";
      break;
    }

    default:
    {
      LOG4CPLUS_WARN(root_log, sfn << "Unknown ice::ObservationValueType ("
                     << static_cast<int>(obs_val->_d)
                     << ")");
      *return_str = ""; // We can't parse, returning undefined
      break;
    }
  }

  return DicesRcDDSUnionToString::OK;
}

DicesRcDDSUnionToString UnionToJSON::EscapeCommasForHadoop(
    std::string* src_str)
{
  static const char* sfn = "UnionToJSON::EscapeCommasForHadoop() ";
  if (!src_str)
  {
    LOG4CPLUS_ERROR(root_log, sfn << "Function argument src_str is a null "
                                     "pointer.");
    return DicesRcDDSUnionToString::FAIL;
  }

  static const std::string kcomma_str = ",";
  static const std::string kescaped_comma_str = "\\,";

  size_t position = src_str->find(kcomma_str, 0);
  while(position != std::string::npos)
  {
    try
    {
      src_str->replace(position, kcomma_str.length(), kescaped_comma_str);
    }
    catch (const std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_log, sfn << "Failed to replace comma with "
                                       "escaped comma. " << ex.what());
      return DicesRcDDSUnionToString::FAIL;
    }
    position += kescaped_comma_str.length();

    position = src_str->find(kcomma_str, position);
  }
  return DicesRcDDSUnionToString::OK;
}



