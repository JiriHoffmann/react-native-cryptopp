// Created by Oscar Franco, edited

#include "JSIHelper.h"

using namespace facebook;
namespace rncryptopp::jsiHelper {
QuickValue createNullQuickValue() { return QuickValue{.dataType = NULL_VALUE}; }

QuickValue createBooleanQuickValue(bool value) {
  return QuickValue{.dataType = BOOLEAN, .booleanValue = value};
}

QuickValue createStringQuickValue(std::string value) {
  return QuickValue{.dataType = STRING, .stringValue = value};
}

QuickValue createIntegerQuickValue(int value) {
  return QuickValue{.dataType = INTEGER,
                    .doubleOrIntValue = static_cast<double>(value)};
}

QuickValue createInt64QuickValue(long long value) {
  return QuickValue{.dataType = INT64, .int64Value = value};
}

QuickValue createDoubleQuickValue(double value) {
  return QuickValue{.dataType = DOUBLE, .doubleOrIntValue = value};
}

QuickValue createArrayBufferQuickValue(char *arrayBufferValue,
                                       size_t arrayBufferSize) {
  std::string value = std::string(arrayBufferValue, arrayBufferSize);
  return QuickValue{.dataType = ARRAY_BUFFER, .stringValue = value};
}

void parseJSIArgs(jsi::Runtime &rt, const jsi::Value *args, size_t count,
                  CppArgs *target) {
  for (int i = 0; i < int(count); i++) {

    auto &value = args[i];
    if (value.isNull() || value.isUndefined()) {
      target->push_back(createNullQuickValue());
    } else if (value.isBool()) {
      target->push_back(createBooleanQuickValue(value.getBool()));
    } else if (value.isNumber()) {
      double doubleVal = value.asNumber();
      int intVal = (int)doubleVal;
      long long longVal = (long)doubleVal;
      if (intVal == doubleVal) {
        target->push_back(createIntegerQuickValue(intVal));
      } else if (longVal == doubleVal) {
        target->push_back(createInt64QuickValue(longVal));
      } else {
        target->push_back(createDoubleQuickValue(doubleVal));
      }
    } else if (value.isString()) {
      std::string strVal = value.asString(rt).utf8(rt);
      target->push_back(createStringQuickValue(strVal));
    } else if (value.isObject()) {
      auto obj = value.asObject(rt);
      if (obj.isArrayBuffer(rt)) {
        auto buf = obj.getArrayBuffer(rt);
        target->push_back(
            createArrayBufferQuickValue((char *)buf.data(rt), buf.size(rt)));
      }
    } else {
      target->push_back(createNullQuickValue());
    }
  }
}

bool isDataString(QuickValue &value) {
  if (value.dataType == STRING)
    return true;
  return false;
}

bool isDataStringOrAB(QuickValue &value) {
  if (value.dataType == STRING || value.dataType == ARRAY_BUFFER)
    return true;
  return false;
}

bool isDataInteger(QuickValue &value) {
  if (value.dataType == INTEGER)
    return true;
  return false;
}
} // namespace rncryptopp::jsiHelper
