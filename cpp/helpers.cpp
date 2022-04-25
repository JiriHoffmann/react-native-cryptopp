#include "helpers.h"

namespace rncryptopp {

// Returns false if the passed value is not a string.
bool stringValueToString(jsi::Runtime &rt, const jsi::Value &value,
                         std::string *str) {
  if (value.isString()) {
    *str = value.asString(rt).utf8(rt);
    return true;
  }
  return false;
}
/*
 * Returns false if the passed value is not a string or an ArrayBuffer.
 * String and ArrayBuffer encoding types:
 * 0: No encoding
 * 1: Hex encoding
 * 2: Base64 encoding
 * 3: Base64Url encoding
 */
bool binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value,
                             std::string *str, int stringEncoding,
                             int bufferEncoding) {
  if (value.isString()) {
    std::string utf8 = value.asString(rt).utf8(rt);
    switch (stringEncoding) {
    case 1:
      hexDecode(utf8, *str);
      break;
    case 2:
      base64Decode(utf8, *str);
      break;
    case 3:
      base64UrlDecode(utf8, *str);
      break;
    default:
      *str = utf8;
    }
    return true;
  }
  if (value.isObject()) {
    auto obj = value.asObject(rt);
    if (!obj.isArrayBuffer(rt)) {
      return false;
    }
    auto buf = obj.getArrayBuffer(rt);
    std::string utf8 = std::string((char *)buf.data(rt), buf.size(rt));
    switch (bufferEncoding) {
    case 1:
      hexDecode(utf8, *str);
      break;
    case 2:
      base64Decode(utf8, *str);
      break;
    case 3:
      base64UrlDecode(utf8, *str);
    default:
      *str = utf8;
    }
    return true;
  }

  return false;
}

/*
 * Encode string, otherwise just set pointer
 * 1: Hex encoding
 * 2: Base64 encoding
 * 3: Base64Url encoding
 */
void encode(std::string *in, std::string *out, int encoding) {
  if (encoding == 1)
    hexEncode(*in, *out);
  else if (encoding == 2)
    base64Encode(*in, *out);
  else if (encoding == 3)
    base64UrlEncode(*in, *out);
  else
    *in = *out;
}

void hexEncode(std::string &in, std::string &out) {
  StringSource(in, true, new HexEncoder(new StringSink(out)));
}

void hexDecode(std::string &in, std::string &out) {
  StringSource(in, true, new HexDecoder(new StringSink(out)));
}

void base64Encode(std::string &in, std::string &out) {
  StringSource(in, true, new Base64Encoder(new StringSink(out)));
}

void base64Decode(std::string &in, std::string &out) {
  StringSource(in, true, new Base64Decoder(new StringSink(out)));
}

void base64UrlEncode(std::string &in, std::string &out) {
  StringSource(in, true, new Base64URLEncoder(new StringSink(out)));
}

void base64UrlDecode(std::string &in, std::string &out) {
  StringSource(in, true, new Base64URLDecoder(new StringSink(out)));
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
int getEncodingFromArgs(jsi::Runtime &rt, const jsi::Value *args,
                        size_t argCount, int argIndex, int defaultValue,
                        bool allowUTF8) {
  if (argIndex >= (int)argCount)
    return defaultValue;

  std::string encoding = args[argIndex].asString(rt).utf8(rt);
  if (encoding == "utf8" && allowUTF8)
    return 0;
  if (encoding == "hex")
    return 1;
  if (encoding == "base64")
    return 2;
  if (encoding == "base64url")
    return 3;
  return defaultValue;
}
} // namespace rncryptopp
