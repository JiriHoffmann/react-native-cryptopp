#ifndef REACT_NATIVE_CRYPTOPP_UTILS_H
#define REACT_NATIVE_CRYPTOPP_UTILS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/osrng.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp
{
    void toBase64(jsi::Runtime &rt, const jsi::Value *args, size_t argCount, std::string *result);

    void toBase64Url(jsi::Runtime &rt, const jsi::Value *args, size_t argCount, std::string *result);

    void toHex(jsi::Runtime &rt, const jsi::Value *args, size_t argCount, std::string *result);

    void toUtf8(jsi::Runtime &rt, const jsi::Value *args, size_t argCount, std::string *result);
}
#endif // REACT_NATIVE_CRYPTOPP_UTILS_H
