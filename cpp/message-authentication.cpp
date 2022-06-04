#include "message-authentication.h"

namespace rncryptopp {

template <class T_MAC>
void runGenerate(std::string *key, std::string *data, std::string *result) {
  T_MAC mac((const byte *)key->data(), key->size());

  StringSource _(*data, true,
                 new HashFilter(mac,
                                new StringSink(*result)) // HashFilter
  );                                                     // StringSource
}

template <typename T> struct runGenerateWrapperHMAC {
  template <typename... R> void operator()(R... rest) const {
    runGenerate<HMAC<T>>(rest...);
  }
};

template <typename T> struct runGenerateWrapperCMAC {
  template <typename... R> void operator()(R... rest) const {
    runGenerate<CMAC<T>>(rest...);
  }
};

template <class T_MAC>
void runVerify(std::string *key, std::string *dataAndMac, bool *result) {
  try {
    T_MAC mac((const byte *)key->data(), key->size());
    const int flags = HashVerificationFilter::THROW_EXCEPTION |
                      HashVerificationFilter::HASH_AT_END;

    StringSource _(
        *dataAndMac, true,
        new HashVerificationFilter(mac, nullptr, flags)); // StringSource
    *result = true;
  } catch (const CryptoPP::Exception &e) {
    *result = false;
  }
}

template <typename T> struct runVerifyWrapperHMAC {
  template <typename... R> void operator()(R... rest) const {
    runVerify<HMAC<T>>(rest...);
  }
};

template <typename T> struct runVerifyWrapperCMAC {
  template <typename... R> void operator()(R... rest) const {
    runVerify<CMAC<T>>(rest...);
  }
};

namespace hmac {
jsi::Value generate(jsi::Runtime &rt, const jsi::Value &thisValue,
                    const jsi::Value *args, size_t argCount) {
  std::string data, key, hash, result;

  auto dataInputType = binaryLikeValueToString(rt, args[0], &data);
  if (dataInputType == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: HMAC generate, data is not a string or ArrayBuffer");

  if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: HMAC generate, key is not a string or ArrayBuffer");

  if (stringValueToString(rt, args[2], &hash) == INP_UNKNOWN)
    throwJSError(rt, "RNCryptopp: HMAC generate, hash is not a string");

  if (!invokeWithHash<runGenerateWrapperHMAC>()(hash, &key, &data, &result))
    throwJSError(rt, "RNCryptopp: HMAC generate, invalid hash value");

  // Return string
  if (dataInputType == INP_STRING) {
    std::string encoded;
    encodeString(&result, &encoded, ENCODING_HEX);
    return jsi::String::createFromUtf8(rt, encoded);
  }

  // Return ArrayBuffer
  int size = (int)result.size();
  jsi::Function array_buffer_ctor =
      rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
  jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
  jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);
  // FIXME: see https://github.com/facebook/hermes/issues/564.
  memcpy(buff.data(rt), result.data(), size);

  return obj;
}

jsi::Value verify(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t argCount) {
  std::string data, key, hash, mac;
  auto dataInputType = binaryLikeValueToString(rt, args[0], &data);
  if (dataInputType == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: HMAC verify, data is not a string or ArrayBuffer");

  if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, key is not a string or ArrayBuffer");

  if (stringValueToString(rt, args[2], &hash) == INP_UNKNOWN)
    throwJSError(rt, "RNCryptopp: HMAC verify, hash is not a string");

  auto macEncoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 4,
                                                     ENCODING_HEX, false);

  if (binaryLikeValueToString(rt, args[3], &mac, macEncoding) == INP_UNKNOWN)
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;
  bool result;
  if (!invokeWithHash<runVerifyWrapperHMAC>()(hash, &key, &dataAndMac, &result))
    throwJSError(rt, "RNCryptopp: HMAC verify, invalid hash value");

  return jsi::Value(result);
}
} // namespace hmac

namespace cmac {
jsi::Value generate(jsi::Runtime &rt, const jsi::Value &thisValue,
                    const jsi::Value *args, size_t argCount) {
  std::string data, key, cipher, result;
  auto dataInputType = binaryLikeValueToString(rt, args[0], &data);
  if (dataInputType == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: CMAC generate, data is not a string or ArrayBuffer");

  if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: CMAC generate, key is not a string or ArrayBuffer");

  if (!stringValueToString(rt, args[2], &cipher))
    throwJSError(rt, "RNCryptopp: CMAC generate, hash is not a string");

  if (!invokeWithBlockCipher<runGenerateWrapperCMAC>()(cipher, true, true, &key,
                                                       &data, &result))
    throwJSError(rt, "RNCryptopp: CMAC generate, invalid hash value");

  // Return string
  if (dataInputType == INP_STRING) {
    std::string encoded;
    encodeString(&result, &encoded, ENCODING_HEX);
    return jsi::String::createFromUtf8(rt, encoded);
  }

  // Return ArrayBuffer
  int size = (int)result.size();
  jsi::Function array_buffer_ctor =
      rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
  jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
  jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);
  // FIXME: see https://github.com/facebook/hermes/issues/564.
  memcpy(buff.data(rt), result.data(), size);

  return obj;
}

jsi::Value verify(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t argCount) {
  std::string data, key, cipher, mac;
  auto dataInputType = binaryLikeValueToString(rt, args[0], &data);
  if (dataInputType == INP_UNKNOWN)
    throwJSError(
        rt, "RNCryptopp: CMAC verify, data is not a string or ArrayBuffer");

  if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, key is not a string or ArrayBuffer");

  if (stringValueToString(rt, args[2], &cipher) == INP_UNKNOWN)
    throwJSError(rt, "RNCryptopp: CMAC verify, hash is not a string");

  auto macEncoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 4,
                                                     ENCODING_HEX, false);

  if (binaryLikeValueToString(rt, args[3], &mac, macEncoding) == INP_UNKNOWN)
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;
  bool result;
  if (!invokeWithBlockCipher<runVerifyWrapperCMAC>()(cipher, true, true, &key,
                                                     &dataAndMac, &result))
    throwJSError(rt, "RNCryptopp: CMAC verify, invalid hash value");

  return jsi::Value(result);
}
} // namespace cmac
} // namespace rncryptopp
