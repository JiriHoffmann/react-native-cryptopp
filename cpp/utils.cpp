#include "cryptopp/base64.h"
#include "cryptopp/hex.h"

#include "utils.h"

namespace rncryptopp {

    // Returns false if the passed value is not a string or an ArrayBuffer.
    bool valueToString(jsi::Runtime &rt, const jsi::Value &value, std::string *str) {
        if (value.isString()) {
            *str = value.asString(rt).utf8(rt);
            return true;
        }

        if (value.isObject()) {
            auto obj = value.asObject(rt);
            if (!obj.isArrayBuffer(rt)) {
                return false;
            }
            auto buf = obj.getArrayBuffer(rt);
            *str = std::string((char *) buf.data(rt), buf.size(rt));
            return true;
        }

        return false;
    }

    void hexDecode(std::string *str, std::string *res) {
        CryptoPP::StringSource(*str, true, new CryptoPP::HexDecoder(
                new CryptoPP::StringSink(*res)));// NOLINT(bugprone-unused-raii)
    }

    void hexEncode(std::string *str, std::string *res) {
        CryptoPP::StringSource(*str, true, new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(*res))); // NOLINT(bugprone-unused-raii)
    }


    bool valueToInt(const jsi::Value &value, int *res) {
        if (!value.isNumber())
            return false;

        *res = (int) value.asNumber();
        return true;
    }

    bool valueToDouble(const jsi::Value &value, double *res) {
        if (!value.isNumber())
            return false;

        *res = value.asNumber();
        return true;
    }
}
