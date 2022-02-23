#include "utils.h"

namespace rncryptopp {

    void toBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string str;
        if (!valueToString(rt, args[0], &str)) {
            return;
        }
        base64Encode(&str, &result);
    }

    void fromBase64(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string str;
        if (!valueToString(rt, args[0], &str)) {
            return;
        }
        base64Decode(&str, &result);
    }

    void toHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string str;
        if (!valueToString(rt, args[0], &str)) {
            return;
        }
        hexEncode(&str, &result);
    }

    void fromHex(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string str;
        if (!valueToString(rt, args[0], &str)) {
            return;
        }
        hexDecode(&str, &result);
    }
}
