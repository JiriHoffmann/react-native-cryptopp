#include "utils.h"
namespace rncryptopp
{

    void randomBytesNative(jsi::Runtime &rt, jsi::Object &o, const jsi::Value *args)
    {
        int length;
        if (!valueToInt(args[0], &length))
            throwJSError(rt, "RNCryptopp: randomBytes length in not a number");

        AutoSeededRandomPool prng;
        SecByteBlock random(length);
        prng.GenerateBlock(random, random.size());

        auto size1 = random.size();
        auto size2 = length;



        int buffSize = random.size();
        jsi::Function array_buffer_ctor = rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
        jsi::Object o = array_buffer_ctor.callAsConstructor(rt, buffSize).getObject(rt);
        jsi::ArrayBuffer buf = o.getArrayBuffer(rt);

        // FIXME: see https://github.com/facebook/hermes/issues/564.
        memcpy(buf.data(rt), random.data(), buffSize);
        entry.setProperty(rt, column_name.c_str(), o);
    }

    void hexToBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 1, 1))
            return;

        StringSource(bytes, true, new Base64Encoder(new StringSink(result)));
    }

    void base64ToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 2, 2))
            return;

        StringSource(bytes, true, new HexEncoder(new StringSink(result)));
    }

    void hexToBase64Url(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 1, 1))
            return;

        StringSource(bytes, true, new Base64URLEncoder(new StringSink(result)));
    }

    void base64UrlToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 2, 2))
            return;

        StringSource(bytes, true, new HexEncoder(new StringSink(result)));
    }

    void utf8ToBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 0, 0))
            return;

        StringSource(bytes, true, new Base64Encoder(new StringSink(result)));
    }

    void base64ToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 2, 2))
            return;

        StringSource(bytes, true, new Base64Decoder(new StringSink(result)));
    }

    void utf8ToBase64Url(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 0, 0))
            return;

        StringSource(bytes, true, new Base64URLEncoder(new StringSink(result)));
    }

    void base64UrlToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 2, 2))
            return;

        StringSource(bytes, true, new Base64URLDecoder(new StringSink(result)));
    }

    void utf8ToHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 0, 0))
            return;

        StringSource(bytes, true, new HexEncoder(new StringSink(result)));
    }

    void hexToUtf8(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string bytes;
        if (!binaryLikeValueToString(rt, args[0], &bytes, 1, 1))
            return;

        StringSource(bytes, true, new HexDecoder(new StringSink(result)));
    }
}
