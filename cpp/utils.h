#ifndef REACT_NATIVE_CRYPTOPP_UTILS_H
#define REACT_NATIVE_CRYPTOPP_UTILS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "helpers.h"

using namespace facebook;

namespace rncryptopp {

    void toBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void fromBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void toHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void fromHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

}
#endif //REACT_NATIVE_CRYPTOPP_UTILS_H
