#pragma once

//  Created by Oscar Franco

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <map>
#include <stdio.h>
#include <vector>

using namespace facebook;

namespace rncryptopp::jsiHelper {
/**
 * Enum for QuickValue to store/determine correct type for dynamic JSI values
 */
enum QuickDataType {
  STRING,
  ARRAY_BUFFER,
  NULL_VALUE,
  INTEGER,
  INT64,
  DOUBLE,
  BOOLEAN,
};

/**
 * Wrapper struct to allocate dynamic JSI values to static C++ primitives
 */
struct QuickValue {
  QuickDataType dataType;
  bool booleanValue;
  double doubleOrIntValue;
  long long int64Value;
  std::string stringValue;
};

using CppArgs = std::vector<QuickValue>;

QuickValue createNullQuickValue();
QuickValue createBooleanQuickValue(bool value);
QuickValue createStringQuickValue(std::string value);
QuickValue createIntegerQuickValue(int value);
QuickValue createInt64QuickValue(long long value);
QuickValue createDoubleQuickValue(double value);

void parseJSIArgs(jsi::Runtime &rt, const jsi::Value *args, size_t count,
                  CppArgs *target);

bool isDataString(QuickValue &value);
bool isDataStringOrAB(QuickValue &value);
bool isDataInteger(QuickValue &value);

} // namespace rncryptopp::jsiHelper
