#include "message-authentication.h"

namespace rncryptopp {

template <class T_MAC>
void runGenerate(std::string *key, std::string *data, std::string *result) {
  T_MAC mac((const CryptoPP::byte *)key->data(), key->size());

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
    T_MAC mac((const CryptoPP::byte *)key->data(), key->size());
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
void generate(jsi::Runtime &rt, CppArgs *args, std::string *target,
              QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() < 4)
    throwJSError(rt, "RNCryptopp: HMAC generate invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: HMAC generate, data is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(
        rt, "RNCryptopp: HMAC generate, key is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: HMAC generate, hash is not a string");

  std::string data = args->at(1).stringValue;
  std::string hash = args->at(3).stringValue;
  std::string key;
  decodeJSIString(args->at(2), &key, ENCODING_HEX);

  if (!invokeWithHash<runGenerateWrapperHMAC>()(hash, &key, &data, target))
    throwJSError(rt, "RNCryptopp: HMAC generate, invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, 4, ENCODING_HEX, false);
}

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType) {
  if (args->size() < 5)
    throwJSError(rt, "RNCryptopp: HMAC verify invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: HMAC verify, data is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, key is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: HMAC verify, hash is not a string");

  if (!isDataStringOrAB(args->at(4)))
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, mac is not a string or ArrayBuffer");

  auto macEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, 5, ENCODING_HEX, false);

  std::string data = args->at(1).stringValue;
  std::string hash = args->at(3).stringValue;
  std::string key, mac;
  decodeJSIString(args->at(2), &key, ENCODING_HEX);
  decodeJSIString(args->at(4), &mac, macEncoding);

  std::string dataAndMac = data + mac;
  if (!invokeWithHash<runVerifyWrapperHMAC>()(hash, &key, &dataAndMac, target))
    throwJSError(rt, "RNCryptopp: HMAC verify, invalid hash value");

  *targetType = BOOLEAN;
}
} // namespace hmac

namespace cmac {
void generate(jsi::Runtime &rt, CppArgs *args, std::string *target,
              QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() < 4)
    throwJSError(rt, "RNCryptopp: CMAC generate invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: CMAC generate, data is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(
        rt, "RNCryptopp: CMAC generate, key is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: CMAC generate, cipher is not a string");

  std::string data = args->at(1).stringValue;
  std::string cipher = args->at(3).stringValue;
  std::string key;
  decodeJSIString(args->at(2), &key, ENCODING_HEX);

  if (!invokeWithBlockCipher<runGenerateWrapperCMAC>()(cipher, true, true, &key,
                                                       &data, target))
    throwJSError(rt, "RNCryptopp: CMAC generate, invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, 4, ENCODING_HEX, false);
}

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType) {
  if (args->size() < 5)
    throwJSError(rt, "RNCryptopp: CMAC verify invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: CMAC verify, data is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, key is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: CMAC verify, cipher is not a string");

  if (!isDataStringOrAB(args->at(4)))
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, mac is not a string or ArrayBuffer");

  auto macEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, 5, ENCODING_HEX, false);

  std::string data = args->at(1).stringValue;
  std::string cipher = args->at(3).stringValue;
  std::string key, mac;
  decodeJSIString(args->at(2), &key, ENCODING_HEX);
  decodeJSIString(args->at(4), &mac, macEncoding);

  std::string dataAndMac = data + mac;

  if (!invokeWithBlockCipher<runVerifyWrapperCMAC>()(cipher, true, true, &key,
                                                     &dataAndMac, target))
    throwJSError(rt, "RNCryptopp: CMAC verify, invalid hash value");

  *targetType = BOOLEAN;
}
} // namespace cmac
} // namespace rncryptopp
