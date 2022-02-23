#ifndef CRYPTOPPEXAMPLE_HELPERS_H
#define CRYPTOPPEXAMPLE_HELPERS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/base64.h"
#include "cryptopp/hex.h"

using namespace facebook;

namespace rncryptopp {

    bool valueToString(jsi::Runtime &runtime, const jsi::Value &value, std::string *str);

    bool valueToInt(const jsi::Value &value, int *res);

    void hexEncode(std::string *str, std::string *res);

    void hexDecode(std::string *str, std::string *res);

    void base64Decode(std::string *str, std::string *res);

    void base64Encode(std::string *str, std::string *res);

}

#endif //CRYPTOPPEXAMPLE_HELPERS_H
