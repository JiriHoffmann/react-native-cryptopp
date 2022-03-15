#include "helpers.h"

namespace rncryptopp
{

    // Returns false if the passed value is not a string.
    bool stringValueToString(jsi::Runtime &rt, const jsi::Value &value, std::string *str)
    {
        if (value.isString())
        {
            *str = value.asString(rt).utf8(rt);
            return true;
        }
        return false;
    }

    // Returns false if the passed value is not a string or an ArrayBuffer.
    // String and ArrayBuffer encoding types:
    // 0: No encoding
    // 1: Hex encoding
    // 2: Base64 encoding
    bool binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value, std::string *str, int stringEncoding, int bufferEncoding)
    {
        if (value.isString())
        {
            std::string utf8 = value.asString(rt).utf8(rt);
            switch (stringEncoding)
            {
            case 1:
                hexDecode(&utf8, str);
                break;
            case 2:
                base64Decode(&utf8, str);
                break;
            default:
                *str = utf8;
            }
            return true;
        }
        if (value.isObject())
        {
            auto obj = value.asObject(rt);
            if (!obj.isArrayBuffer(rt))
            {
                return false;
            }
            auto buf = obj.getArrayBuffer(rt);
            std::string utf8 = std::string((char *)buf.data(rt), buf.size(rt));
            switch (bufferEncoding)
            {
            case 1:
                hexDecode(&utf8, str);
                break;
            case 2:
                base64Decode(&utf8, str);
                break;
            default:
                *str = utf8;
            }
            return true;
        }

        return false;
    }

    void hexEncode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new HexEncoder(new StringSink(*res)));
    }

    void hexDecode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new HexDecoder(new StringSink(*res)));
    }

    void base64Encode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new Base64Encoder(new StringSink(*res)));
    }

    void base64Decode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new Base64Decoder(new StringSink(*res)));
    }

    void base64UrlEncode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new Base64URLEncoder(new StringSink(*res)));
    }

    void base64UrlDecode(std::string *str, std::string *res)
    {
        StringSource(*str, true, new Base64URLDecoder(new StringSink(*res)));
    }

    bool valueToInt(const jsi::Value &value, int *res)
    {
        if (!value.isNumber())
            return false;

        *res = (int)value.asNumber();
        return true;
    }

    bool valueToDouble(const jsi::Value &value, double *res)
    {
        if (!value.isNumber())
            return false;

        *res = value.asNumber();
        return true;
    }
}
