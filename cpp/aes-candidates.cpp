#include "aes-candidates.h"

namespace rncryptopp {
namespace aescandidates {

template <template <class> class T_Mode, class T_BlockCipher>
void runEncryption(std::string *key, std::string *iv, std::string *data,
                   int encodeTo, std::string *result) {

  typename T_Mode<T_BlockCipher>::Encryption e;
  e.SetKeyWithIV(reinterpret_cast<const byte *>(key->data()), key->size(),
                 reinterpret_cast<const byte *>(iv->data()), iv->size());
  std::string encrypted;
  StringSource _(*data, true,
                 new StreamTransformationFilter(e, new StringSink(encrypted)));
  encode(&encrypted, result, encodeTo);
}

template <typename T_BlockCipher> struct getModeAndRunEncryption {
  template <typename... R>
  void operator()(std::string &mode, bool *isModeValid, R... rest) const {
    if (mode == "ecb")
      runEncryption<ECB_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc")
      runEncryption<CBC_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc_cts")
      runEncryption<CBC_CTS_Mode, T_BlockCipher>(rest...);
    else if (mode == "cfb")
      runEncryption<CFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ofb")
      runEncryption<OFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ctr")
      runEncryption<CTR_Mode, T_BlockCipher>(rest...);
    else if (mode == "xts")
      runEncryption<XTS_Mode, T_BlockCipher>(rest...);
    else
      *isModeValid = false;
  }
};

void encrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string &cipher, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(rt,
                 "RNCryptopp: aes & candidates encrypt data is not a string");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt, "RNCryptopp: aes & candidates encrypt key is not a string "
                     "or ArrayBuffer");

  std::string iv;
  if (!binaryLikeValueToString(rt, args[2], &iv, 1, 0))
    throwJSError(rt, "RNCryptopp: aes & candidates encrypt iv is not a string "
                     "or ArrayBuffer");

  std::string mode;
  if (!stringValueToString(rt, args[3], &mode))
    throwJSError(rt,
                 "RNCryptopp: aes & candidates encrypt mode is not a string");

  // encode result with base64 by default
  int encodeTo =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2, false);

  bool isModeValid = true;
  invokeWithBlockCipherAES<getModeAndRunEncryption>()(
      cipher, mode, &isModeValid, &key, &iv, &data, encodeTo, result);

  if (!isModeValid)
    throwJSError(
        rt, "RNCryptopp: aes & candidates encrypt mode is not a valid mode");
}

template <template <class> class T_Mode, class T_BlockCipher>
void runDecryption(std::string *key, std::string *iv, std::string *data,
                   std::string *result) {

  typename T_Mode<T_BlockCipher>::Decryption d;
  d.SetKeyWithIV(reinterpret_cast<const byte *>(key->data()), key->size(),
                 reinterpret_cast<const byte *>(iv->data()), iv->size());
  StringSource s(*data, true,
                 new StreamTransformationFilter(d, new StringSink(*result)));
}

template <typename T_BlockCipher> struct getModeAndRunDecryption {
  template <typename... R>
  void operator()(std::string &mode, bool *isModeValid, R... rest) const {
    if (mode == "ecb")
      runDecryption<ECB_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc")
      runDecryption<CBC_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc_cts")
      runDecryption<CBC_CTS_Mode, T_BlockCipher>(rest...);
    else if (mode == "cfb")
      runDecryption<CFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ofb")
      runDecryption<OFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ctr")
      runDecryption<CTR_Mode, T_BlockCipher>(rest...);
    else if (mode == "xts")
      runDecryption<XTS_Mode, T_BlockCipher>(rest...);
    else
      *isModeValid = false;
  }
};

void decrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string &cipher, std::string *result) {

  // Result is encoded with base64 by default
  int dataEncoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2);

  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, dataEncoding, dataEncoding))
    throwJSError(rt,
                 "RNCryptopp: aes & candidates decrypt data is not a string");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt,
                 "RNCryptopp: aes & candidates decrypt key is not a string");

  std::string iv;
  if (!binaryLikeValueToString(rt, args[2], &iv, 1, 0))
    throwJSError(rt, "RNCryptopp: aes & candidates decrypt iv is not a string");

  std::string mode;
  if (!stringValueToString(rt, args[3], &mode))
    throwJSError(rt,
                 "RNCryptopp: aes & candidates decrypt mode is not a string");

  bool isModeValid = true;
  invokeWithBlockCipherAES<getModeAndRunDecryption>()(
      cipher, mode, &isModeValid, &key, &iv, &data, result);

  if (!isModeValid)
    throwJSError(
        rt, "RNCryptopp: aes & candidates decrypt mode is not a valid mode");
}

} // namespace aescandidates
} // namespace rncryptopp
