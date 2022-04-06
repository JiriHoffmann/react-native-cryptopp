#include "message-authentication.h"

namespace rncryptopp {

template <class MAC_HASH>
void runGenerate(std::string *key, std::string *data, std::string *result,
                 int encodeWith) {
  MAC_HASH mac((const byte *)key, key->size());

  std::string code;
  StringSource _(*data, true,
                 new HashFilter(mac,
                                new StringSink(code)) // HashFilter
  );                                                  // StringSource
  encode(&code, result, encodeWith);
}

template <class MAC_HASH>
bool runVerify(std::string *key, std::string *dataAndMac) {
  try {
    MAC_HASH mac((const byte *)key, key->size());
    const int flags = HashVerificationFilter::THROW_EXCEPTION |
                      HashVerificationFilter::HASH_AT_END;

    StringSource _(
        *dataAndMac, true,
        new HashVerificationFilter(mac, nullptr, flags)); // StringSource
    return true;
  } catch (const CryptoPP::Exception &e) {
  }
  return false;
}

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

  if (hash == "BLAKE2b")
    runGenerate<HMAC<BLAKE2b>>(&key, &data, result, encodeWith);
  else if (hash == "BLAKE2s")
    runGenerate<HMAC<BLAKE2s>>(&key, &data, result, encodeWith);
  else if (hash == "Keccak_224")
    runGenerate<HMAC<Keccak_224>>(&key, &data, result, encodeWith);
  else if (hash == "Keccak_256")
    runGenerate<HMAC<Keccak_256>>(&key, &data, result, encodeWith);
  else if (hash == "Keccak_384")
    runGenerate<HMAC<Keccak_384>>(&key, &data, result, encodeWith);
  else if (hash == "Keccak_512")
    runGenerate<HMAC<Keccak_512>>(&key, &data, result, encodeWith);
  else if (hash == "LSH224")
    runGenerate<HMAC<LSH224>>(&key, &data, result, encodeWith);
  else if (hash == "LSH256")
    runGenerate<HMAC<LSH256>>(&key, &data, result, encodeWith);
  else if (hash == "LSH384")
    runGenerate<HMAC<LSH384>>(&key, &data, result, encodeWith);
  else if (hash == "LSH512")
    runGenerate<HMAC<LSH512>>(&key, &data, result, encodeWith);
  else if (hash == "SHA1")
    runGenerate<HMAC<SHA1>>(&key, &data, result, encodeWith);
  else if (hash == "SHA224")
    runGenerate<HMAC<SHA224>>(&key, &data, result, encodeWith);
  else if (hash == "SHA256")
    runGenerate<HMAC<SHA256>>(&key, &data, result, encodeWith);
  else if (hash == "SHA384")
    runGenerate<HMAC<SHA384>>(&key, &data, result, encodeWith);
  else if (hash == "SHA512")
    runGenerate<HMAC<SHA512>>(&key, &data, result, encodeWith);
  else if (hash == "SHA3_224")
    runGenerate<HMAC<SHA3_224>>(&key, &data, result, encodeWith);
  else if (hash == "SHA3_256")
    runGenerate<HMAC<SHA3_256>>(&key, &data, result, encodeWith);
  else if (hash == "SHA3_384")
    runGenerate<HMAC<SHA3_384>>(&key, &data, result, encodeWith);
  else if (hash == "SHA3_512")
    runGenerate<HMAC<SHA3_512>>(&key, &data, result, encodeWith);
  else if (hash == "SHAKE128")
    runGenerate<HMAC<SHAKE128>>(&key, &data, result, encodeWith);
  else if (hash == "SHAKE256")
    runGenerate<HMAC<SHAKE256>>(&key, &data, result, encodeWith);
  else if (hash == "SM3")
    runGenerate<HMAC<SM3>>(&key, &data, result, encodeWith);
  else if (hash == "Tiger")
    runGenerate<HMAC<Tiger>>(&key, &data, result, encodeWith);
  else if (hash == "RIPEMD128")
    runGenerate<HMAC<RIPEMD128>>(&key, &data, result, encodeWith);
  else if (hash == "RIPEMD160")
    runGenerate<HMAC<RIPEMD160>>(&key, &data, result, encodeWith);
  else if (hash == "RIPEMD256")
    runGenerate<HMAC<RIPEMD256>>(&key, &data, result, encodeWith);
  else if (hash == "RIPEMD320")
    runGenerate<HMAC<RIPEMD320>>(&key, &data, result, encodeWith);
  else
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
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 5, 1, false);

  std::string mac;
  if (!binaryLikeValueToString(rt, args[4], &mac, macEncoding, macEncoding))
    throwJSError(rt,
                 "RNCryptopp: HMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;

  if (hash == "BLAKE2b")
    runVerify<HMAC<BLAKE2b>>(&key, &dataAndMac);
  else if (hash == "BLAKE2s")
    *result = runVerify<HMAC<BLAKE2s>>(&key, &dataAndMac);
  else if (hash == "Keccak_224")
    *result = runVerify<HMAC<Keccak_224>>(&key, &dataAndMac);
  else if (hash == "Keccak_256")
    *result = runVerify<HMAC<Keccak_256>>(&key, &dataAndMac);
  else if (hash == "Keccak_384")
    *result = runVerify<HMAC<Keccak_384>>(&key, &dataAndMac);
  else if (hash == "Keccak_512")
    *result = runVerify<HMAC<Keccak_512>>(&key, &dataAndMac);
  else if (hash == "LSH224")
    *result = runVerify<HMAC<LSH224>>(&key, &dataAndMac);
  else if (hash == "LSH256")
    *result = runVerify<HMAC<LSH256>>(&key, &dataAndMac);
  else if (hash == "LSH384")
    *result = runVerify<HMAC<LSH384>>(&key, &dataAndMac);
  else if (hash == "LSH512")
    *result = runVerify<HMAC<LSH512>>(&key, &dataAndMac);
  else if (hash == "SHA1")
    *result = runVerify<HMAC<SHA1>>(&key, &dataAndMac);
  else if (hash == "SHA224")
    *result = runVerify<HMAC<SHA224>>(&key, &dataAndMac);
  else if (hash == "SHA256")
    *result = runVerify<HMAC<SHA256>>(&key, &dataAndMac);
  else if (hash == "SHA384")
    *result = runVerify<HMAC<SHA384>>(&key, &dataAndMac);
  else if (hash == "SHA512")
    *result = runVerify<HMAC<SHA512>>(&key, &dataAndMac);
  else if (hash == "SHA3_224")
    *result = runVerify<HMAC<SHA3_224>>(&key, &dataAndMac);
  else if (hash == "SHA3_256")
    *result = runVerify<HMAC<SHA3_256>>(&key, &dataAndMac);
  else if (hash == "SHA3_384")
    *result = runVerify<HMAC<SHA3_384>>(&key, &dataAndMac);
  else if (hash == "SHA3_512")
    *result = runVerify<HMAC<SHA3_512>>(&key, &dataAndMac);
  else if (hash == "SHAKE128")
    *result = runVerify<HMAC<SHAKE128>>(&key, &dataAndMac);
  else if (hash == "SHAKE256")
    *result = runVerify<HMAC<SHAKE256>>(&key, &dataAndMac);
  else if (hash == "SM3")
    *result = runVerify<HMAC<SM3>>(&key, &dataAndMac);
  else if (hash == "Tiger")
    *result = runVerify<HMAC<Tiger>>(&key, &dataAndMac);
  else if (hash == "RIPEMD128")
    *result = runVerify<HMAC<RIPEMD128>>(&key, &dataAndMac);
  else if (hash == "RIPEMD160")
    *result = runVerify<HMAC<RIPEMD160>>(&key, &dataAndMac);
  else if (hash == "RIPEMD256")
    *result = runVerify<HMAC<RIPEMD256>>(&key, &dataAndMac);
  else if (hash == "RIPEMD320")
    *result = runVerify<HMAC<RIPEMD320>>(&key, &dataAndMac);
  else
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

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: CMAC generate, hash is not a string");

  // encode result with hex by default
  int encodeWith =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 3, 1, false);

  if (hash == "ARIA")
    runGenerate<CMAC<ARIA>>(&key, &data, result, encodeWith);
  else if (hash == "Blowfish")
    runGenerate<CMAC<Blowfish>>(&key, &data, result, encodeWith);
  else if (hash == "Camellia")
    runGenerate<CMAC<Camellia>>(&key, &data, result, encodeWith);
  else if (hash == "CHAM64")
    runGenerate<CMAC<CHAM64>>(&key, &data, result, encodeWith);
  else if (hash == "CHAM123")
    runGenerate<CMAC<CHAM128>>(&key, &data, result, encodeWith);
  else if (hash == "HIGHT")
    runGenerate<CMAC<HIGHT>>(&key, &data, result, encodeWith);
  else if (hash == "IDEA")
    runGenerate<CMAC<IDEA>>(&key, &data, result, encodeWith);
  else if (hash == "Kalyna128")
    runGenerate<CMAC<Kalyna128>>(&key, &data, result, encodeWith);
  else if (hash == "Kalyna256")
    runGenerate<CMAC<Kalyna256>>(&key, &data, result, encodeWith);
  else if (hash == "Kalyna512")
    runGenerate<CMAC<Kalyna512>>(&key, &data, result, encodeWith);
  else if (hash == "LEA")
    runGenerate<CMAC<LEA>>(&key, &data, result, encodeWith);
  else if (hash == "SEED")
    runGenerate<CMAC<SEED>>(&key, &data, result, encodeWith);
  else if (hash == "RC5")
    runGenerate<CMAC<RC5>>(&key, &data, result, encodeWith);
  else if (hash == "SHACAL2")
    runGenerate<CMAC<SHACAL2>>(&key, &data, result, encodeWith);
  else if (hash == "SIMECK32")
    runGenerate<CMAC<SIMECK32>>(&key, &data, result, encodeWith);
  else if (hash == "SIMECK64")
    runGenerate<CMAC<SIMECK64>>(&key, &data, result, encodeWith);
  else if (hash == "SIMON64")
    runGenerate<CMAC<SIMON64>>(&key, &data, result, encodeWith);
  else if (hash == "SIMON128")
    runGenerate<CMAC<SIMON128>>(&key, &data, result, encodeWith);
  else if (hash == "SKIPJACK")
    runGenerate<CMAC<SKIPJACK>>(&key, &data, result, encodeWith);
  else if (hash == "SPECK64")
    runGenerate<CMAC<SPECK64>>(&key, &data, result, encodeWith);
  else if (hash == "SPECK128")
    runGenerate<CMAC<SPECK128>>(&key, &data, result, encodeWith);
  else if (hash == "SM4")
    runGenerate<CMAC<SM4>>(&key, &data, result, encodeWith);
  else if (hash == "Threefish256")
    runGenerate<CMAC<Threefish256>>(&key, &data, result, encodeWith);
  else if (hash == "Threefish512")
    runGenerate<CMAC<Threefish512>>(&key, &data, result, encodeWith);
  else if (hash == "Threefish1024")
    runGenerate<CMAC<Threefish1024>>(&key, &data, result, encodeWith);
  else if (hash == "DES_EDE2")
    runGenerate<CMAC<DES_EDE2>>(&key, &data, result, encodeWith);
  else if (hash == "DES_EDE3")
    runGenerate<CMAC<DES_EDE3>>(&key, &data, result, encodeWith);
  else if (hash == "TEA")
    runGenerate<CMAC<TEA>>(&key, &data, result, encodeWith);
  else if (hash == "XTEA")
    runGenerate<CMAC<XTEA>>(&key, &data, result, encodeWith);
  else
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

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: CMAC verify, hash is not a string");

  // encode result with hex by default
  int macEncoding =
      rncryptopp::getEncodingFromArgs(rt, args, argCount, 5, 1, false);

  std::string mac;
  if (!binaryLikeValueToString(rt, args[4], &mac, macEncoding, macEncoding))
    throwJSError(rt,
                 "RNCryptopp: CMAC verify, mac is not a string or ArrayBuffer");

  std::string dataAndMac = data + mac;

  if (hash == "ARIA")
    runVerify<CMAC<ARIA>>(&key, &dataAndMac);
  else if (hash == "Blowfish")
    *result = runVerify<CMAC<Blowfish>>(&key, &dataAndMac);
  else if (hash == "Camellia")
    *result = runVerify<CMAC<Camellia>>(&key, &dataAndMac);
  else if (hash == "CHAM64")
    *result = runVerify<CMAC<CHAM64>>(&key, &dataAndMac);
  else if (hash == "CHAM123")
    *result = runVerify<CMAC<CHAM128>>(&key, &dataAndMac);
  else if (hash == "HIGHT")
    *result = runVerify<CMAC<HIGHT>>(&key, &dataAndMac);
  else if (hash == "IDEA")
    *result = runVerify<CMAC<IDEA>>(&key, &dataAndMac);
  else if (hash == "Kalyna128")
    *result = runVerify<CMAC<Kalyna128>>(&key, &dataAndMac);
  else if (hash == "Kalyna256")
    *result = runVerify<CMAC<Kalyna256>>(&key, &dataAndMac);
  else if (hash == "Kalyna512")
    *result = runVerify<CMAC<Kalyna512>>(&key, &dataAndMac);
  else if (hash == "LEA")
    *result = runVerify<CMAC<LEA>>(&key, &dataAndMac);
  else if (hash == "SEED")
    *result = runVerify<CMAC<SEED>>(&key, &dataAndMac);
  else if (hash == "RC5")
    *result = runVerify<CMAC<RC5>>(&key, &dataAndMac);
  else if (hash == "SHACAL2")
    *result = runVerify<CMAC<SHACAL2>>(&key, &dataAndMac);
  else if (hash == "SIMECK32")
    *result = runVerify<CMAC<SIMECK32>>(&key, &dataAndMac);
  else if (hash == "SIMECK64")
    *result = runVerify<CMAC<SIMECK64>>(&key, &dataAndMac);
  else if (hash == "SIMON64")
    *result = runVerify<CMAC<SIMON64>>(&key, &dataAndMac);
  else if (hash == "SIMON128")
    *result = runVerify<CMAC<SIMON128>>(&key, &dataAndMac);
  else if (hash == "SKIPJACK")
    *result = runVerify<CMAC<SKIPJACK>>(&key, &dataAndMac);
  else if (hash == "SPECK64")
    *result = runVerify<CMAC<SPECK64>>(&key, &dataAndMac);
  else if (hash == "SPECK128")
    *result = runVerify<CMAC<SPECK128>>(&key, &dataAndMac);
  else if (hash == "SM4")
    *result = runVerify<CMAC<SM4>>(&key, &dataAndMac);
  else if (hash == "Threefish256")
    *result = runVerify<CMAC<Threefish256>>(&key, &dataAndMac);
  else if (hash == "Threefish512")
    *result = runVerify<CMAC<Threefish512>>(&key, &dataAndMac);
  else if (hash == "Threefish1024")
    *result = runVerify<CMAC<Threefish1024>>(&key, &dataAndMac);
  else if (hash == "DES_EDE2")
    *result = runVerify<CMAC<DES_EDE2>>(&key, &dataAndMac);
  else if (hash == "DES_EDE3")
    *result = runVerify<CMAC<DES_EDE3>>(&key, &dataAndMac);
  else if (hash == "TEA")
    *result = runVerify<CMAC<TEA>>(&key, &dataAndMac);
  else if (hash == "XTEA")
    *result = runVerify<CMAC<XTEA>>(&key, &dataAndMac);
  else
    throwJSError(rt, "RNCryptopp: CMAC verify, invalid hash value");
}
} // namespace cmac
} // namespace rncryptopp
