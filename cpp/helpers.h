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

    bool binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value, std::string *str, int stringEncoding = 0, int bufferEncoding = 0);

    bool valueToInt(const jsi::Value &value, int *res);

    bool valueToDouble(const jsi::Value &value, double *res);

    void hexEncode(std::string &in, std::string &out);

    void hexDecode(std::string &in, std::string &out);

    void base64Decode(std::string &in, std::string &out);

    void base64Encode(std::string &in, std::string &out);

    void base64UrlDecode(std::string &in, std::string &out);

    void base64UrlEncode(std::string &in, std::string &out);

    int getEncodingFromArgs(jsi::Runtime &rt, const jsi::Value *args, size_t argCount, int index, int defaultValue = 0);
}

#endif // CRYPTOPPEXAMPLE_HELPERS_H
