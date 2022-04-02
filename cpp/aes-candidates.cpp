#include "aes-candidates.h"

namespace rncryptopp {
int getModeIndex(std::string &mode) {
  if (mode == "ecb")
    return 0;
  if (mode == "cbc")
    return 1;
  if (mode == "cbc_cts")
    return 2;
  if (mode == "cfb")
    return 3;
  if (mode == "ofb")
    return 4;
  if (mode == "ctr")
    return 5;
  if (mode == "xts")
    return 6;
  return -1;
}

// function definition
template <class CIPHER>
void exec_AES(const byte *key, size_t length, const byte *iv, size_t ivLength,
              std::string *data, std::string *result, int encrypt,
              int encodeTo) {
  if (encrypt == 1) {
    typename CIPHER::Encryption e;
    e.SetKeyWithIV(key, length, iv, ivLength);
    std::string encrypted;
    StringSource(*data, true,
                 new StreamTransformationFilter(e, new StringSink(encrypted)));
    if (encodeTo == 1)
      hexEncode(encrypted, *result);
    else if (encodeTo == 2)
      base64Encode(encrypted, *result);
    else if (encodeTo == 3)
      base64UrlEncode(encrypted, *result);
    else
      *data = encrypted;
  } else {
    typename CIPHER::Decryption d;
    d.SetKeyWithIV(key, length, iv, ivLength);
    StringSource s(*data, true,
                   new StreamTransformationFilter(d, new StringSink(*result)));
  }
}

// Array of function pointers
void (*modePtrs[])(const byte *key, size_t length, const byte *iv,
                   size_t ivLength, std::string *data, std::string *result,
                   int encrypt, int encodeTo) = {
    &exec_AES<ECB_Mode<AES>>,     &exec_AES<CBC_Mode<AES>>,
    &exec_AES<CBC_CTS_Mode<AES>>, &exec_AES<CFB_Mode<AES>>,
    &exec_AES<OFB_Mode<AES>>,     &exec_AES<CTR_Mode<AES>>,
    &exec_AES<XTS_Mode<AES>>};

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
  int encoding =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, 2, false);

  auto modeIndex = getModeIndex(mode);

  if (modeIndex == -1) {
    throwJSError(rt,
                 "RNCryptopp: aes_encrypt mode is not a invalid mode value");
    return;
  }

  modePtrs[modeIndex]((const byte *)key.data(), key.size(),
                      (const byte *)iv.data(), iv.size(), &data, result, 1,
                      encoding);
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

  auto modeIndex = getModeIndex(mode);

  if (modeIndex == -1) {
    throwJSError(rt,
                 "RNCryptopp: aes_decrypt mode is not a invalid mode value");
    return;
  }

  modePtrs[modeIndex]((const byte *)key.data(), key.size(),
                      (const byte *)iv.data(), iv.size(), &data, result, 0, 0);
}
} // namespace rncryptopp
