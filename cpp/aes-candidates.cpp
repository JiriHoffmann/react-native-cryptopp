#include "aes-candidates.h"

namespace rncryptopp {

template <class CIPHER>
void encrypt(std::string *key, std::string *iv, std::string *data,
             std::string *result, int encodingWith) {

  typename CIPHER::Encryption e;
  e.SetKeyWithIV(reinterpret_cast<const byte *>(key), key->size(),
                 reinterpret_cast<const byte *>(iv), iv->size());
  std::string encrypted;
  StringSource _(*data, true,
                 new StreamTransformationFilter(e, new StringSink(encrypted)));
  encode(&encrypted, result, encodingWith);
}

template <class CIPHER>
void decrypt(std::string *key, std::string *iv, std::string *data,
             std::string *result) {

  typename CIPHER::Decryption d;
  d.SetKeyWithIV(reinterpret_cast<const byte *>(key), key->size(),
                 reinterpret_cast<const byte *>(iv), iv->size());
  StringSource s(*data, true,
                 new StreamTransformationFilter(d, new StringSink(*result)));
}

void aes_encrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
                 std::string *result) {

  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
    throwJSError(rt, "RNCryptopp: aes_encrypt data is not a string");

  std::string key;
  if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
    throwJSError(rt,
                 "RNCryptopp: aes_encrypt iv is not a string or ArrayBuffer");

  std::string iv;
  if (!binaryLikeValueToString(rt, args[2], &iv, 1, 0))
    throwJSError(rt,
                 "RNCryptopp: aes_encrypt iv is not a string or ArrayBuffer");

  std::string mode;
  if (!stringValueToString(rt, args[3], &mode))
    throwJSError(rt, "RNCryptopp: aes_encrypt mode is not a string");

  // encode result with base64 by default
  int encodingWith =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2, false);

  if (mode == "ecb")
    encrypt<ECB_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "cbc")
    encrypt<CBC_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "cbc_cts")
    encrypt<CBC_CTS_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "cfb")
    encrypt<CFB_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "ofb")
    encrypt<OFB_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "ctr")
    encrypt<CTR_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else if (mode == "xts")
    encrypt<XTS_Mode<AES>>(&key, &iv, &data, result, encodingWith);
  else
    throwJSError(rt,
                 "RNCryptopp: aes_encrypt mode is not a invalid mode value");
}

void aes_decrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
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

  if (mode == "ecb")
    decrypt<ECB_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "cbc")
    decrypt<CBC_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "cbc_cts")
    decrypt<CBC_CTS_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "cfb")
    decrypt<CFB_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "ofb")
    decrypt<OFB_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "ctr")
    decrypt<CTR_Mode<AES>>(&key, &iv, &data, result);
  else if (mode == "xts")
    decrypt<XTS_Mode<AES>>(&key, &iv, &data, result);
  else
    throwJSError(rt,
                 "RNCryptopp: aes_decrypt mode is not a invalid mode value");
}
} // namespace rncryptopp
