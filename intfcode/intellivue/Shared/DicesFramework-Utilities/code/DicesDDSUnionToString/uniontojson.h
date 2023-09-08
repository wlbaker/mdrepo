#ifndef UNION_TO_JSON_H_
#define UNION_TO_JSON_H_


#include <string>
#include <diagnostics.h>

enum class DicesRcDDSUnionToString;

class UnionToJSON
{
  public:
    ~UnionToJSON();

    static DicesRcDDSUnionToString EffectiveTimeToJSON(
        ice::EffectiveTime* effective,
        std::string* return_str);
    static DicesRcDDSUnionToString EffectiveTimeToString(
        ice::EffectiveTime* eff_time,
        std::string* return_str);

    static DicesRcDDSUnionToString ObservationValueToJSON(
        ice::ObservationValue* obs_val,
        std::string* return_str);
    static DicesRcDDSUnionToString ObservationValue_valueToString(
        ice::ObservationValue* obs_val,
        std::string* return_str);

    static DicesRcDDSUnionToString ObservationValue_unitsToString(
        ice::ObservationValue* obs_val,
        std::string* return_str);

    static DicesRcDDSUnionToString EscapeCommasForHadoop(
        std::string* src_str);

  private:
    UnionToJSON();
};

#endif
