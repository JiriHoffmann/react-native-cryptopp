#ifndef CRYPTOPPEXAMPLE_HELPERS_H
#define CRYPTOPPEXAMPLE_HELPERS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/base64.h"
#include "cryptopp/hex.h"

using namespace facebook;
using namespace CryptoPP;

namespace rncryptopp
{

    bool stringValueToString(jsi::Runtime &runtime, const jsi::Value &value, std::string *str);

    bool binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value, std::string *str, int stringEncoding, int bufferEncoding);

    bool valueToInt(const jsi::Value &value, int *res);

    bool valueToDouble(const jsi::Value &value, double *res);

    void hexEncode(std::string *str, std::string *res);

    void hexDecode(std::string *str, std::string *res);

    void base64Decode(std::string *str, std::string *res);

    void base64Encode(std::string *str, std::string *res);

    void base64UrlDecode(std::string *str, std::string *res);

    void base64UrlEncode(std::string *str, std::string *res);
}

#endif // CRYPTOPPEXAMPLE_HELPERS_H
