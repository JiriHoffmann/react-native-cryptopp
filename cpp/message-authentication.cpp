#include "message-authentication.h"

namespace rncryptopp {

template <class MAC_HASH>
void runGenerate(std::string *key, std::string *data, std::string *result,
                 int encodeWith) {
  MAC_HASH mac((const byte *)key->data(), key->size());

  std::string code;
  StringSource _(*data, true,
                 new HashFilter(mac,
                                new StringSink(code)) // HashFilter
  );                                                  // StringSource
  encode(&code, result, encodeWith);
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

template <class MAC_HASH>
void runVerify(std::string *key, std::string *dataAndMac, bool *result) {
  try {
    MAC_HASH mac((const byte *)key->data(), key->size());
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
void generate(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
              std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(
        rt, "RNCryptopp: HMAC generate, data is not a string or ArrayBuffer");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(
        rt, "RNCryptopp: HMAC generate, key is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: HMAC generate, hash is not a string");

  // encode result with hex by default
  int encodeWith =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 3, 1, false);

  if (!invokeWithHash<runGenerateWrapperHMAC>()(hash, &key, &data, result,
                                                encodeWith))
    throwJSError(rt, "RNCryptopp: HMAC generate, invalid hash value");
}

void verify(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
            bool *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(
        rt, "RNCryptopp: HMAC verify, data is not a string or ArrayBuffer");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, key is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: HMAC verify, hash is not a string");

  // encode result with hex by default
  int macEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 1, false);

  std::string mac;
  if (!binaryLikeValueToString(rt, args[3], &mac, macEncoding, macEncoding))
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;

  if (!invokeWithHash<runVerifyWrapperHMAC>()(hash, &key, &dataAndMac, result))
    throwJSError(rt, "RNCryptopp: HMAC verify, invalid hash value");
}
} // namespace hmac
namespace cmac {
void generate(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
              std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(
        rt, "RNCryptopp: CMAC generate, data is not a string or ArrayBuffer");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(
        rt, "RNCryptopp: CMAC generate, key is not a string or ArrayBuffer");

  std::string cipher;
  if (!stringValueToString(rt, args[2], &cipher))
    throwJSError(rt, "RNCryptopp: CMAC generate, hash is not a string");

  // encode result with hex by default
  int encodeWith =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 3, 1, false);

  if (!invokeWithBlockCipher<runGenerateWrapperCMAC>()(
          cipher, true, true, &key, &data, result, encodeWith))
    throwJSError(rt, "RNCryptopp: CMAC generate, invalid hash value");
}

void verify(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
            bool *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(
        rt, "RNCryptopp: CMAC verify, data is not a string or ArrayBuffer");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, key is not a string or ArrayBuffer");

  std::string cipher;
  if (!stringValueToString(rt, args[2], &cipher))
    throwJSError(rt, "RNCryptopp: CMAC verify, hash is not a string");

  // encode result with hex by default
  int macEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 1, false);

  std::string mac;
  if (!binaryLikeValueToString(rt, args[3], &mac, macEncoding, macEncoding))
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;

  if (!invokeWithBlockCipher<runVerifyWrapperCMAC>()(cipher, true, true, &key,
                                                     &dataAndMac, result))
    throwJSError(rt, "RNCryptopp: CMAC verify, invalid hash value");
}
} // namespace cmac
} // namespace rncryptopp
