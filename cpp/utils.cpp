#import "utils.h"


// Returns false if the passed value is not a string or an ArrayBuffer.
bool valueToString(jsi::Runtime &runtime, const jsi::Value &value, std::string *str) {
    if (value.isString()) {
        *str = value.asString(runtime).utf8(runtime);
        return true;
    }

    if (value.isObject()) {
        auto obj = value.asObject(runtime);
        if (!obj.isArrayBuffer(runtime)) {
            return false;
        }
        auto buf = obj.getArrayBuffer(runtime);
        *str = std::string((char *) buf.data(runtime), buf.size(runtime));
        return true;
    }

    return false;
}


bool valueToInt(jsi::Runtime &runtime, const jsi::Value &value, int *res) {
    if (!value.isNumber())
        return false;

    *res = (int) value.asNumber();
    return true;
}

bool valueToDouble(jsi::Runtime &runtime, const jsi::Value &value, double *res) {
    if (!value.isNumber())
        return false;

    *res = value.asNumber();
    return true;
}

