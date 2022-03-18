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
    void toBase64(jsi::Runtime &rt, std::string *result, const jsi::Value *args);

    void toBase64Url(jsi::Runtime &rt, std::string *result, const jsi::Value *args);

    void toHex(jsi::Runtime &rt, std::string *result, const jsi::Value *args);

    void toUtf8(jsi::Runtime &rt, std::string *result, const jsi::Value *args);
}
#endif // REACT_NATIVE_CRYPTOPP_UTILS_H
