#include "utils.h"
namespace rncryptopp
{
    void toBase64(jsi::Runtime &rt, std::string *result, const jsi::Value *args)
    {
        int encoding = getEncodingFromArgs(rt, args, 1);
        if (encoding == -1)
            throw jsi::JSError(rt, "RNCryptopp: toBase64 invalid dataEncoding");

        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, encoding, encoding))
            throw jsi::JSError(rt, "RNCryptopp: toBase64 data is not a string or ArrayBuffer");

        base64Encode(&bytes, result);
    }

    void toBase64Url(jsi::Runtime &rt, std::string *result, const jsi::Value *args)
    {
        int encoding = getEncodingFromArgs(rt, args, 1);
        if (encoding == -1)
            throw jsi::JSError(rt, "RNCryptopp: toBase64Url invalid dataEncoding");

        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, encoding, encoding))
            throw jsi::JSError(rt, "RNCryptopp: toBase64Url data is not a string or ArrayBuffer");

        base64UrlEncode(&bytes, result);
    }

    void toHex(jsi::Runtime &rt, std::string *result, const jsi::Value *args)
    {
        int encoding = getEncodingFromArgs(rt, args, 1);
        if (encoding == -1)
            throw jsi::JSError(rt, "RNCryptopp: toHex invalid dataEncoding");

        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, encoding, encoding))
            throw jsi::JSError(rt, "RNCryptopp: toHex data is not a string or ArrayBuffer");

        hexEncode(&bytes, result);
    }

    void toUtf8(jsi::Runtime &rt, std::string *result, const jsi::Value *args)
    {
        int encoding = getEncodingFromArgs(rt, args, 1);
        if (encoding == -1)
            throw jsi::JSError(rt, "RNCryptopp: toUtf8 invalid dataEncoding");

        if (!binaryLikeValueToString(rt, args[0], result, encoding, encoding))
            throw jsi::JSError(rt, "RNCryptopp: toUtf8 data is not a string or ArrayBuffer");
    }
}
