#include "key-derivation.h"

namespace rncryptopp {
/**
 * Derivation function used for HKDF
 *
 * @tparam T_hash HashTransformation class
 */
template <class T_hash>
void deriveHKDF(std::string *secret, std::string *salt, std::string *info,
                std::string *result) {
  HKDF<T_hash> hkdf;
  byte derived[T_hash::DIGESTSIZE];
  size_t derivedLen = sizeof(derived);

  hkdf.DeriveKey(derived, derivedLen, reinterpret_cast<const byte *>(secret),
                 secret->size(), reinterpret_cast<const byte *>(salt),
                 salt->size(), reinterpret_cast<const byte *>(info),
                 info->size());
  std::string s(reinterpret_cast<char const *>(derived), derivedLen);
  hexEncode(s, *result);
}

void hkdf(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string pass;
  if (!binaryLikeValueToString(rt, args[0], &pass))
    throwJSError(rt,
                 "RNCryptopp: hkdf password is not a string or ArrayBuffer");

  std::string salt;
  if (!binaryLikeValueToString(rt, args[1], &salt))
    throwJSError(rt, "RNCryptopp: hkdf salt is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: hkdf hash is not a string");

  std::string info;
  if (!binaryLikeValueToString(rt, args[3], &info))
    throwJSError(rt, "RNCryptopp: hkdf info is not a string or ArrayBuffer");

  if (hash == "BLAKE2b")
    deriveHKDF<BLAKE2b>(&pass, &salt, &info, result);
  else if (hash == "BLAKE2s")
    deriveHKDF<BLAKE2s>(&pass, &salt, &info, result);
  else if (hash == "Keccak_224")
    deriveHKDF<Keccak_224>(&pass, &salt, &info, result);
  else if (hash == "Keccak_256")
    deriveHKDF<Keccak_256>(&pass, &salt, &info, result);
  else if (hash == "Keccak_384")
    deriveHKDF<Keccak_384>(&pass, &salt, &info, result);
  else if (hash == "Keccak_512")
    deriveHKDF<Keccak_512>(&pass, &salt, &info, result);
  else if (hash == "LSH224")
    deriveHKDF<LSH224>(&pass, &salt, &info, result);
  else if (hash == "LSH256")
    deriveHKDF<LSH256>(&pass, &salt, &info, result);
  else if (hash == "LSH384")
    deriveHKDF<LSH384>(&pass, &salt, &info, result);
  else if (hash == "LSH512")
    deriveHKDF<LSH512>(&pass, &salt, &info, result);
  else if (hash == "SHA1")
    deriveHKDF<SHA1>(&pass, &salt, &info, result);
  else if (hash == "SHA224")
    deriveHKDF<SHA224>(&pass, &salt, &info, result);
  else if (hash == "SHA256")
    deriveHKDF<SHA256>(&pass, &salt, &info, result);
  else if (hash == "SHA384")
    deriveHKDF<SHA384>(&pass, &salt, &info, result);
  else if (hash == "SHA512")
    deriveHKDF<SHA512>(&pass, &salt, &info, result);
  else if (hash == "SHA3_224")
    deriveHKDF<SHA3_224>(&pass, &salt, &info, result);
  else if (hash == "SHA3_256")
    deriveHKDF<SHA3_256>(&pass, &salt, &info, result);
  else if (hash == "SHA3_384")
    deriveHKDF<SHA3_384>(&pass, &salt, &info, result);
  else if (hash == "SHA3_512")
    deriveHKDF<SHA3_512>(&pass, &salt, &info, result);
  else if (hash == "SHAKE128")
    deriveHKDF<SHAKE128>(&pass, &salt, &info, result);
  else if (hash == "SHAKE256")
    deriveHKDF<SHAKE256>(&pass, &salt, &info, result);
  else if (hash == "SM3")
    deriveHKDF<SM3>(&pass, &salt, &info, result);
  else if (hash == "Tiger")
    deriveHKDF<Tiger>(&pass, &salt, &info, result);
  else if (hash == "RIPEMD128")
    deriveHKDF<RIPEMD128>(&pass, &salt, &info, result);
  else if (hash == "RIPEMD160")
    deriveHKDF<RIPEMD160>(&pass, &salt, &info, result);
  else if (hash == "RIPEMD256")
    deriveHKDF<RIPEMD256>(&pass, &salt, &info, result);
  else if (hash == "RIPEMD320")
    deriveHKDF<RIPEMD320>(&pass, &salt, &info, result);
  else
    throwJSError(rt, "RNCryptopp: hkdf hash invalid hash value");
}

/**
 * Derivation function used for pbkdf12, pkcs5_pbkdf1, and pkcs5_pbkdf2
 *
 * @tparam T_func PasswordBasedKeyDerivationFunction
 * @tparam T_hash HashTransformation class
 */
template <template <class> class T_func, class T_hash>
void derivePBKDF(std::string *secret, std::string *salt,
                 unsigned int iterations, std::string *result) {
  T_func<T_hash> func;
  byte derived[T_hash::DIGESTSIZE];
  size_t derivedLen = sizeof(derived);
  byte unused = 0;

  func.DeriveKey(derived, derivedLen, unused,
                 reinterpret_cast<const byte *>(secret), secret->size(),
                 reinterpret_cast<const byte *>(salt), salt->size(), iterations,
                 0.0f);
  std::string s(reinterpret_cast<char const *>(derived), derivedLen);
  hexEncode(s, *result);
}

template <template <class> class T_func>
void getHashAndDerivePBKDF(jsi::Runtime &rt, std::string *secret,
                           std::string *salt, std::string &hash, int numIter,
                           std::string *result) {
  if (hash == "BLAKE2b")
    derivePBKDF<T_func, BLAKE2b>(secret, salt, numIter, result);
  else if (hash == "BLAKE2s")
    derivePBKDF<T_func, BLAKE2s>(secret, salt, numIter, result);
  else if (hash == "Keccak_224")
    derivePBKDF<T_func, Keccak_224>(secret, salt, numIter, result);
  else if (hash == "Keccak_256")
    derivePBKDF<T_func, Keccak_256>(secret, salt, numIter, result);
  else if (hash == "Keccak_384")
    derivePBKDF<T_func, Keccak_384>(secret, salt, numIter, result);
  else if (hash == "Keccak_512")
    derivePBKDF<T_func, Keccak_512>(secret, salt, numIter, result);
  else if (hash == "LSH224")
    derivePBKDF<T_func, LSH224>(secret, salt, numIter, result);
  else if (hash == "LSH256")
    derivePBKDF<T_func, LSH256>(secret, salt, numIter, result);
  else if (hash == "LSH384")
    derivePBKDF<T_func, LSH384>(secret, salt, numIter, result);
  else if (hash == "LSH512")
    derivePBKDF<T_func, LSH512>(secret, salt, numIter, result);
  else if (hash == "SHA1")
    derivePBKDF<T_func, SHA1>(secret, salt, numIter, result);
  else if (hash == "SHA224")
    derivePBKDF<T_func, SHA224>(secret, salt, numIter, result);
  else if (hash == "SHA256")
    derivePBKDF<T_func, SHA256>(secret, salt, numIter, result);
  else if (hash == "SHA384")
    derivePBKDF<T_func, SHA384>(secret, salt, numIter, result);
  else if (hash == "SHA512")
    derivePBKDF<T_func, SHA512>(secret, salt, numIter, result);
  else if (hash == "SHA3_224")
    derivePBKDF<T_func, SHA3_224>(secret, salt, numIter, result);
  else if (hash == "SHA3_256")
    derivePBKDF<T_func, SHA3_256>(secret, salt, numIter, result);
  else if (hash == "SHA3_384")
    derivePBKDF<T_func, SHA3_384>(secret, salt, numIter, result);
  else if (hash == "SHA3_512")
    derivePBKDF<T_func, SHA3_512>(secret, salt, numIter, result);
  else if (hash == "SHAKE128")
    derivePBKDF<T_func, SHAKE128>(secret, salt, numIter, result);
  else if (hash == "SHAKE256")
    derivePBKDF<T_func, SHAKE256>(secret, salt, numIter, result);
  else if (hash == "SM3")
    derivePBKDF<T_func, SM3>(secret, salt, numIter, result);
  else if (hash == "Tiger")
    derivePBKDF<T_func, Tiger>(secret, salt, numIter, result);
  else if (hash == "RIPEMD128")
    derivePBKDF<T_func, RIPEMD128>(secret, salt, numIter, result);
  else if (hash == "RIPEMD160")
    derivePBKDF<T_func, RIPEMD160>(secret, salt, numIter, result);
  else if (hash == "RIPEMD256")
    derivePBKDF<T_func, RIPEMD256>(secret, salt, numIter, result);
  else if (hash == "RIPEMD320")
    derivePBKDF<T_func, RIPEMD320>(secret, salt, numIter, result);
  else
    throwJSError(rt,
                 "RNCryptopp: key derivation hash is not a valid hash value");
}

void pbkdf12(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string pass;
  if (!binaryLikeValueToString(rt, args[0], &pass))
    throwJSError(rt, "RNCryptopp: pbkdf12 pass is not a string or ArrayBuffer");

  std::string salt;
  if (!binaryLikeValueToString(rt, args[1], &salt))
    throwJSError(rt, "RNCryptopp: pbkdf12 salt is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: pbkdf12 hash is not a string");

  int numIter;
  if (!valueToInt(args[3], &numIter))
    throwJSError(rt, "RNCryptopp: pbkdf12 numIter in not a number");

  getHashAndDerivePBKDF<PKCS12_PBKDF>(rt, &pass, &salt, hash, numIter, result);
}

void pkcs5_pbkdf1(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result) {
  std::string pass;
  if (!binaryLikeValueToString(rt, args[0], &pass))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf1 pass is not a string or ArrayBuffer");

  std::string salt;
  if (!binaryLikeValueToString(rt, args[1], &salt))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf1 salt is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash is not a string");

  int numIter;
  if (!valueToInt(args[3], &numIter))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 numIter in not a number");

  getHashAndDerivePBKDF<PKCS5_PBKDF1>(rt, &pass, &salt, hash, numIter, result);
}

void pkcs5_pbkdf2(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result) {
  std::string pass;
  if (!binaryLikeValueToString(rt, args[0], &pass))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf2 pass is not a string or ArrayBuffer");

  std::string salt;
  if (!binaryLikeValueToString(rt, args[1], &salt))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf2 salt is not a string or ArrayBuffer");

  std::string hash;
  if (!stringValueToString(rt, args[2], &hash))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash is not a string");

  int numIter;
  if (!valueToInt(args[3], &numIter))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 numIter in not a number");

  getHashAndDerivePBKDF<PKCS5_PBKDF2_HMAC>(rt, &pass, &salt, hash, numIter,
                                           result);
}
} // namespace rncryptopp
