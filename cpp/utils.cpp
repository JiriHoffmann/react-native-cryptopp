#include "utils.h"

namespace rncryptopp::utils {
jsi::Value toBase64(jsi::Runtime &rt, const jsi::Value &thisValue,
                    const jsi::Value *args, size_t argCount) {
  std::string in, out;
  auto encoding = getEncodingFromArgs(rt, args, argCount, 1);
  if (binaryLikeValueToString(rt, args[0], &in, encoding) == INP_UNKNOWN)
    throw jsi::JSError(
        rt, "RNCryptopp: toBase64 data is not a string or ArrayBuffer");
  encodeString(&in, &out, ENCODING_BASE64);
  return jsi::String::createFromUtf8(rt, out);
}

jsi::Value toBase64Url(jsi::Runtime &rt, const jsi::Value &thisValue,
                       const jsi::Value *args, size_t argCount) {
  std::string in, out;
  auto encoding = getEncodingFromArgs(rt, args, argCount, 1);
  if (binaryLikeValueToString(rt, args[0], &in, encoding) == INP_UNKNOWN)
    throw jsi::JSError(
        rt, "RNCryptopp: toBase64Url data is not a string or ArrayBuffer");
  encodeString(&in, &out, ENCODING_BASE64URL);
  return jsi::String::createFromUtf8(rt, out);
}

jsi::Value toHex(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t argCount) {
  std::string in, out;
  auto encoding = getEncodingFromArgs(rt, args, argCount, 1);
  if (binaryLikeValueToString(rt, args[0], &in, encoding) == INP_UNKNOWN)
    throw jsi::JSError(rt,
                       "RNCryptopp: toHex data is not a string or ArrayBuffer");
  encodeString(&in, &out, ENCODING_HEX);
  return jsi::String::createFromUtf8(rt, out);
}

jsi::Value toUtf8(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t argCount) {
  std::string out;
  auto encoding = getEncodingFromArgs(rt, args, argCount, 1);
  if (binaryLikeValueToString(rt, args[0], &out, encoding) == INP_UNKNOWN)
    throw jsi::JSError(
        rt, "RNCryptopp: toUtf8 data is not a string or ArrayBuffer");
  return jsi::String::createFromUtf8(rt, out);
}

jsi::Value randomBytes(jsi::Runtime &rt, const jsi::Value &thisValue,
                       const jsi::Value *args, size_t argCount) {
  int size;
  if (!rncryptopp::valueToInt(args[0], &size))
    throwJSError(rt, "RNCryptopp: randomBytes size is not a number");

  jsi::Function array_buffer_ctor =
      rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
  jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
  jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

  AutoSeededRandomPool prng;
  SecByteBlock random(size);
  prng.GenerateBlock(random, random.size());

  // FIXME: see https://github.com/facebook/hermes/issues/564.
  memcpy(buff.data(rt), random.data(), size);
  return obj;
}

jsi::Value stringToBytes(jsi::Runtime &rt, const jsi::Value &thisValue,
                         const jsi::Value *args, size_t argCount) {
  auto encoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 1);

  std::string bytes;
  if (stringValueToString(rt, args[0], &bytes, encoding) == INP_UNKNOWN)
    throw jsi::JSError(rt, "RNCryptopp: stringToBytes data is not a string");

  int size = (int)bytes.size();

  jsi::Function array_buffer_ctor =
      rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
  jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
  jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

  // FIXME: see https://github.com/facebook/hermes/issues/564.
  memcpy(buff.data(rt), bytes.data(), size);
  return obj;
}
} // namespace rncryptopp::utils
