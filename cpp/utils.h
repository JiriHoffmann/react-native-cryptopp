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

    void randomBytesNative(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void hexToBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void base64ToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void hexToBase64Url(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void base64UrlToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void utf8ToBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void base64ToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void utf8ToBase64Url(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void base64UrlToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void utf8ToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void hexToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args);
}
#endif // REACT_NATIVE_CRYPTOPP_UTILS_H
