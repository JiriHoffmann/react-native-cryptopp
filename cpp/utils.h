#ifndef REACT_NATIVE_CRYPTOPP_UTILS_H
#define REACT_NATIVE_CRYPTOPP_UTILS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

using namespace facebook;

bool valueToString(jsi::Runtime &runtime, const jsi::Value &value, std::string *str);

bool valueToInt(jsi::Runtime &runtime, const jsi::Value &value, int *res);

bool valueToDouble(jsi::Runtime &runtime, const jsi::Value &value, double *res);

#endif //REACT_NATIVE_CRYPTOPP_UTILS_H
