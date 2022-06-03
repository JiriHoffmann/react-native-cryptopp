#include "helpers.h"

namespace rncryptopp {

InputType stringValueToString(jsi::Runtime &rt, const jsi::Value &value,
                              std::string *out, StringEncoding stringEncoding) {
  if (value.isString()) {
    std::string utf8 = value.asString(rt).utf8(rt);
    decodeString(&utf8, out, stringEncoding);
    return INP_STRING;
  }
  return INP_UNKNOWN;
}

InputType binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value,
                                  std::string *out,
                                  StringEncoding stringEncoding) {
  if (value.isObject()) {
    auto obj = value.asObject(rt);
    if (obj.isArrayBuffer(rt)) {
      auto buf = obj.getArrayBuffer(rt);
      *out = std::string((char *)buf.data(rt), buf.size(rt));
      return INP_ARRAYBUFFER;
    }
  }
  return stringValueToString(rt, value, out, stringEncoding);
}

void encodeString(std::string *in, std::string *out, StringEncoding encoding) {
  switch (encoding) {
  case ENCODING_HEX:
    StringSource(*in, true, new HexEncoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64:
    StringSource(*in, true, new Base64Encoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64URL:
    StringSource(*in, true, new Base64URLEncoder(new StringSink(*out)));
    break;
  default:
    *out = *in;
  }
}

void decodeString(std::string *in, std::string *out, StringEncoding encoding) {
  switch (encoding) {
  case ENCODING_HEX:
    StringSource(*in, true, new HexDecoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64:
    StringSource(*in, true, new Base64Decoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64URL:
    StringSource(*in, true, new Base64URLDecoder(new StringSink(*out)));
    break;
  default:
    *out = *in;
  }
}

bool valueToInt(const jsi::Value &value, int *res) {
  if (!value.isNumber())
    return false;

  *res = (int)value.asNumber();
  return true;
}

bool valueToDouble(const jsi::Value &value, double *res) {
  if (!value.isNumber())
    return false;

  *res = value.asNumber();
  return true;
}

/*
 * Int encoding from a JS string. Uses argCount to check
 * if index is out of JS array bounds
 * Returns:
 * 0: No encoding (uft8), if not allowed returns default value
 * 1: Hex encoding
 * 2: Base64 encoding
 * 3: Base64Url encoding
 */
StringEncoding getEncodingFromArgs(jsi::Runtime &rt, const jsi::Value *args,
                                   size_t argCount, int argIndex,
                                   StringEncoding defaultValue,
                                   bool allowUTF8) {
  if (argIndex >= (int)argCount)
    return defaultValue;

  std::string encoding = args[argIndex].asString(rt).utf8(rt);
  if (encoding == "utf8" && allowUTF8)
    return ENCODING_UTF8;
  if (encoding == "hex")
    return ENCODING_HEX;
  if (encoding == "base64")
    return ENCODING_BASE64;
  if (encoding == "base64url")
    return ENCODING_BASE64URL;
  return defaultValue;
}
} // namespace rncryptopp
