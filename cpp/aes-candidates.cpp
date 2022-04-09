#include "aes-candidates.h"

namespace rncryptopp {
namespace aescandidates {

template <template <class> class Mode, class T_BlockCipher>
void runEncrypt(std::string *key, std::string *iv, std::string *data,
                std::string *result, int encodeTo) {

  typename Mode<T_BlockCipher>::Encryption e;
  e.SetKeyWithIV(reinterpret_cast<const byte *>(key), key->size(),
                 reinterpret_cast<const byte *>(iv), iv->size());
  std::string encrypted;
  StringSource _(*data, true,
                 new StreamTransformationFilter(e, new StringSink(encrypted)));
  encode(&encrypted, result, encodeTo);
}

template <class T_BlockCipher>
void getModeAndRunEncrypt(jsi::Runtime &rt, std::string *key, std::string *iv,
                          std::string *data, std::string &mode,
                          std::string *result, int encodeTo) {
  if (mode == "ecb")
    runEncrypt<ECB_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "cbc")
    runEncrypt<CBC_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "cbc_cts")
    runEncrypt<CBC_CTS_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "cfb")
    runEncrypt<CFB_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "ofb")
    runEncrypt<OFB_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "ctr")
    runEncrypt<CTR_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else if (mode == "xts")
    runEncrypt<XTS_Mode, T_BlockCipher>(key, iv, data, result, encodeTo);
  else
    throwJSError(rt, "RNCryptopp: encrypt mode is not a valid mode value");
}

template <class T_BlockCipher>
void encrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(rt, "RNCryptopp: encrypt data is not a string");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt, "RNCryptopp: encrypt key is not a string or ArrayBuffer");

  std::string iv;
  if (!binaryLikeValueToString(rt, args[2], &iv, 1, 0))
    throwJSError(rt, "RNCryptopp: encrypt iv is not a string or ArrayBuffer");

  std::string mode;
  if (!stringValueToString(rt, args[3], &mode))
    throwJSError(rt, "RNCryptopp: encrypt mode is not a string");

  // encode result with base64 by default
  int encodeTo =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2, false);

  getModeAndRunEncrypt<T_BlockCipher>(rt, &key, &iv, &data, mode, result,
                                      encodeTo);
}

template <template <class> class Mode, class T_BlockCipher>
void runDecrypt(std::string *key, std::string *iv, std::string *data,
                std::string *result) {

  typename Mode<T_BlockCipher>::Decryption d;
  d.SetKeyWithIV(reinterpret_cast<const byte *>(key), key->size(),
                 reinterpret_cast<const byte *>(iv), iv->size());
  StringSource s(*data, true,
                 new StreamTransformationFilter(d, new StringSink(*result)));
}

template <class T_BlockCipher>
void getModeAndRunDecrypt(jsi::Runtime &rt, std::string *key, std::string *iv,
                          std::string *data, std::string &mode,
                          std::string *result) {
  if (mode == "ecb")
    runDecrypt<ECB_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "cbc")
    runDecrypt<CBC_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "cbc_cts")
    runDecrypt<CBC_CTS_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "cfb")
    runDecrypt<CFB_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "ofb")
    runDecrypt<OFB_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "ctr")
    runDecrypt<CTR_Mode, T_BlockCipher>(key, iv, data, result);
  else if (mode == "xts")
    runDecrypt<XTS_Mode, T_BlockCipher>(key, iv, data, result);
  else
    throwJSError(rt, "RNCryptopp: decrypt mode is not a valid mode value");
}

template <class T_BlockCipher>
void decrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string *result) {
  // Result is encoded with base64 by default
  int encoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2);

  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, encoding, encoding))
    throwJSError(rt, "RNCryptopp: aes_decrypt data is not a string");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 0, 0))
    throwJSError(rt, "RNCryptopp: aes_decrypt key is not a string");

  std::string iv;
  if (!binaryLikeValueToString(rt, args[2], &iv, 0, 0))
    throwJSError(rt, "RNCryptopp: aes_decrypt iv is not a string");

  std::string mode;
  if (!stringValueToString(rt, args[3], &mode))
    throwJSError(rt, "RNCryptopp: aes_decrypt mode is not a string");

  getModeAndRunDecrypt<T_BlockCipher>(rt, &key, &iv, &data, mode, result);
}
} // namespace aescandidates
} // namespace rncryptopp
