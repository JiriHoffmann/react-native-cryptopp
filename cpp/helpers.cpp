#include "helpers.h"

namespace rncryptopp {

void encodeString(std::string *in, std::string *out, StringEncoding encoding) {
  switch (encoding) {
  case ENCODING_HEX:
    StringSource(*in, true, new HexEncoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64:
    StringSource(*in, true, new Base64Encoder(new StringSink(*out), false));
    break;
  case ENCODING_BASE64URL:
    StringSource(*in, true, new Base64URLEncoder(new StringSink(*out)));
    break;
  default:
    *out = *in;
  }
}

void decodeJSIString(QuickValue &jsiValue, std::string *out,
                     StringEncoding encoding) {
  if (jsiValue.dataType == ARRAY_BUFFER) {
    *out = jsiValue.stringValue;
    return;
  }
  switch (encoding) {
  case ENCODING_HEX:
    StringSource(jsiValue.stringValue, true,
                 new HexDecoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64:
    StringSource(jsiValue.stringValue, true,
                 new Base64Decoder(new StringSink(*out)));
    break;
  case ENCODING_BASE64URL:
    StringSource(jsiValue.stringValue, true,
                 new Base64URLDecoder(new StringSink(*out)));
    break;
  default:
    *out = jsiValue.stringValue;
  }
}

/*
 * Encoding from a JS string.
 */
StringEncoding getEncodingFromArgs(jsi::Runtime &rt, CppArgs *args,
                                   int argIndex, StringEncoding defaultValue,
                                   bool allowUTF8) {
  if (argIndex >= args->size())
    return defaultValue;

  std::string encoding = args->at(argIndex).stringValue;
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

jsi::Value returnStringOrArrayBuffer(jsi::Runtime &rt, std::string &input,
                                     QuickDataType &ouputType,
                                     StringEncoding &outputEncoding) {
  if (ouputType == STRING) {
    std::string encoded;
    encodeString(&input, &encoded, outputEncoding);
    return jsi::String::createFromUtf8(rt, encoded);
  }

  // Return ArrayBuffer
  int size = (int)input.size();
  jsi::Function array_buffer_ctor =
      rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
  jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
  jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);
  // FIXME: see https://github.com/facebook/hermes/issues/564.
  memcpy(buff.data(rt), input.data(), size);

  return obj;
}
} // namespace rncryptopp
