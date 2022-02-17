#ifndef REACT_NATIVE_CRYPTOPP_UTILS_H
#define REACT_NATIVE_CRYPTOPP_UTILS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

using namespace facebook;

namespace rncryptopp {

    bool valueToString(jsi::Runtime &runtime, const jsi::Value &value, std::string *str);

    bool valueToInt(const jsi::Value &value, int *res);

    void hexEncode(std::string *str, std::string *res);

    void hexDecode(std::string *str, std::string *res);

}
#endif //REACT_NATIVE_CRYPTOPP_UTILS_H
