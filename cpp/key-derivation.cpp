#include "key-derivation.h"

namespace rncryptopp {
/// \brief Derivation function used for HKDF
/// \tparam HASH HashTransformation class
template <class HASH>
void deriveHKDF(std::string *secret, std::string *salt, std::string *info,
                std::string *result) {
  HKDF<HASH> hkdf;
  byte derived[HASH::DIGESTSIZE];
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

/// \brief Derivation function used for pbkdf12, pkcs5_pbkdf1, and pkcs5_pbkdf2
/// \tparam FUNC PasswordBasedKeyDerivationFunction
/// \tparam HASH HashTransformation class
template <template <class> class FUNC, class HASH>
void derivePBKDF(std::string *secret, std::string *salt,
                 unsigned int iterations, std::string *result) {
  FUNC<HASH> func;
  byte derived[HASH::DIGESTSIZE];
  size_t derivedLen = sizeof(derived);
  byte unused = 0;

  func.DeriveKey(derived, derivedLen, unused,
                 reinterpret_cast<const byte *>(secret), secret->size(),
                 reinterpret_cast<const byte *>(salt), salt->size(), iterations,
                 0.0f);
  std::string s(reinterpret_cast<char const *>(derived), derivedLen);
  hexEncode(s, *result);
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

  if (hash == "BLAKE2b")
    derivePBKDF<PKCS12_PBKDF, BLAKE2b>(&pass, &salt, numIter, result);
  else if (hash == "BLAKE2s")
    derivePBKDF<PKCS12_PBKDF, BLAKE2s>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_224")
    derivePBKDF<PKCS12_PBKDF, Keccak_224>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_256")
    derivePBKDF<PKCS12_PBKDF, Keccak_256>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_384")
    derivePBKDF<PKCS12_PBKDF, Keccak_384>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_512")
    derivePBKDF<PKCS12_PBKDF, Keccak_512>(&pass, &salt, numIter, result);
  else if (hash == "LSH224")
    derivePBKDF<PKCS12_PBKDF, LSH224>(&pass, &salt, numIter, result);
  else if (hash == "LSH256")
    derivePBKDF<PKCS12_PBKDF, LSH256>(&pass, &salt, numIter, result);
  else if (hash == "LSH384")
    derivePBKDF<PKCS12_PBKDF, LSH384>(&pass, &salt, numIter, result);
  else if (hash == "LSH512")
    derivePBKDF<PKCS12_PBKDF, LSH512>(&pass, &salt, numIter, result);
  else if (hash == "SHA1")
    derivePBKDF<PKCS12_PBKDF, SHA1>(&pass, &salt, numIter, result);
  else if (hash == "SHA224")
    derivePBKDF<PKCS12_PBKDF, SHA224>(&pass, &salt, numIter, result);
  else if (hash == "SHA256")
    derivePBKDF<PKCS12_PBKDF, SHA256>(&pass, &salt, numIter, result);
  else if (hash == "SHA384")
    derivePBKDF<PKCS12_PBKDF, SHA384>(&pass, &salt, numIter, result);
  else if (hash == "SHA512")
    derivePBKDF<PKCS12_PBKDF, SHA512>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_224")
    derivePBKDF<PKCS12_PBKDF, SHA3_224>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_256")
    derivePBKDF<PKCS12_PBKDF, SHA3_256>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_384")
    derivePBKDF<PKCS12_PBKDF, SHA3_384>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_512")
    derivePBKDF<PKCS12_PBKDF, SHA3_512>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE128")
    derivePBKDF<PKCS12_PBKDF, SHAKE128>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE256")
    derivePBKDF<PKCS12_PBKDF, SHAKE256>(&pass, &salt, numIter, result);
  else if (hash == "SM3")
    derivePBKDF<PKCS12_PBKDF, SM3>(&pass, &salt, numIter, result);
  else if (hash == "Tiger")
    derivePBKDF<PKCS12_PBKDF, Tiger>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD128")
    derivePBKDF<PKCS12_PBKDF, RIPEMD128>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD160")
    derivePBKDF<PKCS12_PBKDF, RIPEMD160>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD256")
    derivePBKDF<PKCS12_PBKDF, RIPEMD256>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD320")
    derivePBKDF<PKCS12_PBKDF, RIPEMD320>(&pass, &salt, numIter, result);
  else
    throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");
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

  if (hash == "BLAKE2b")
    derivePBKDF<PKCS5_PBKDF1, BLAKE2b>(&pass, &salt, numIter, result);
  else if (hash == "BLAKE2s")
    derivePBKDF<PKCS5_PBKDF1, BLAKE2s>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_224")
    derivePBKDF<PKCS5_PBKDF1, Keccak_224>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_256")
    derivePBKDF<PKCS5_PBKDF1, Keccak_256>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_384")
    derivePBKDF<PKCS5_PBKDF1, Keccak_384>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_512")
    derivePBKDF<PKCS5_PBKDF1, Keccak_512>(&pass, &salt, numIter, result);
  else if (hash == "LSH224")
    derivePBKDF<PKCS5_PBKDF1, LSH224>(&pass, &salt, numIter, result);
  else if (hash == "LSH256")
    derivePBKDF<PKCS5_PBKDF1, LSH256>(&pass, &salt, numIter, result);
  else if (hash == "LSH384")
    derivePBKDF<PKCS5_PBKDF1, LSH384>(&pass, &salt, numIter, result);
  else if (hash == "LSH512")
    derivePBKDF<PKCS5_PBKDF1, LSH512>(&pass, &salt, numIter, result);
  else if (hash == "SHA1")
    derivePBKDF<PKCS5_PBKDF1, SHA1>(&pass, &salt, numIter, result);
  else if (hash == "SHA224")
    derivePBKDF<PKCS5_PBKDF1, SHA224>(&pass, &salt, numIter, result);
  else if (hash == "SHA256")
    derivePBKDF<PKCS5_PBKDF1, SHA256>(&pass, &salt, numIter, result);
  else if (hash == "SHA384")
    derivePBKDF<PKCS5_PBKDF1, SHA384>(&pass, &salt, numIter, result);
  else if (hash == "SHA512")
    derivePBKDF<PKCS5_PBKDF1, SHA512>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_224")
    derivePBKDF<PKCS5_PBKDF1, SHA3_224>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_256")
    derivePBKDF<PKCS5_PBKDF1, SHA3_256>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_384")
    derivePBKDF<PKCS5_PBKDF1, SHA3_384>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_512")
    derivePBKDF<PKCS5_PBKDF1, SHA3_512>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE128")
    derivePBKDF<PKCS5_PBKDF1, SHAKE128>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE256")
    derivePBKDF<PKCS5_PBKDF1, SHAKE256>(&pass, &salt, numIter, result);
  else if (hash == "SM3")
    derivePBKDF<PKCS5_PBKDF1, SM3>(&pass, &salt, numIter, result);
  else if (hash == "Tiger")
    derivePBKDF<PKCS5_PBKDF1, Tiger>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD128")
    derivePBKDF<PKCS5_PBKDF1, RIPEMD128>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD160")
    derivePBKDF<PKCS5_PBKDF1, RIPEMD160>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD256")
    derivePBKDF<PKCS5_PBKDF1, RIPEMD256>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD320")
    derivePBKDF<PKCS5_PBKDF1, RIPEMD320>(&pass, &salt, numIter, result);
  else
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash invalid hash value");
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

  if (hash == "BLAKE2b")
    derivePBKDF<PKCS5_PBKDF2_HMAC, BLAKE2b>(&pass, &salt, numIter, result);
  else if (hash == "BLAKE2s")
    derivePBKDF<PKCS5_PBKDF2_HMAC, BLAKE2s>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_224")
    derivePBKDF<PKCS5_PBKDF2_HMAC, Keccak_224>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, Keccak_256>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_384")
    derivePBKDF<PKCS5_PBKDF2_HMAC, Keccak_384>(&pass, &salt, numIter, result);
  else if (hash == "Keccak_512")
    derivePBKDF<PKCS5_PBKDF2_HMAC, Keccak_512>(&pass, &salt, numIter, result);
  else if (hash == "LSH224")
    derivePBKDF<PKCS5_PBKDF2_HMAC, LSH224>(&pass, &salt, numIter, result);
  else if (hash == "LSH256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, LSH256>(&pass, &salt, numIter, result);
  else if (hash == "LSH384")
    derivePBKDF<PKCS5_PBKDF2_HMAC, LSH384>(&pass, &salt, numIter, result);
  else if (hash == "LSH512")
    derivePBKDF<PKCS5_PBKDF2_HMAC, LSH512>(&pass, &salt, numIter, result);
  else if (hash == "SHA1")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA1>(&pass, &salt, numIter, result);
  else if (hash == "SHA224")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA224>(&pass, &salt, numIter, result);
  else if (hash == "SHA256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA256>(&pass, &salt, numIter, result);
  else if (hash == "SHA384")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA384>(&pass, &salt, numIter, result);
  else if (hash == "SHA512")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA512>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_224")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA3_224>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA3_256>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_384")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA3_384>(&pass, &salt, numIter, result);
  else if (hash == "SHA3_512")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHA3_512>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE128")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHAKE128>(&pass, &salt, numIter, result);
  else if (hash == "SHAKE256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SHAKE256>(&pass, &salt, numIter, result);
  else if (hash == "SM3")
    derivePBKDF<PKCS5_PBKDF2_HMAC, SM3>(&pass, &salt, numIter, result);
  else if (hash == "Tiger")
    derivePBKDF<PKCS5_PBKDF2_HMAC, Tiger>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD128")
    derivePBKDF<PKCS5_PBKDF2_HMAC, RIPEMD128>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD160")
    derivePBKDF<PKCS5_PBKDF2_HMAC, RIPEMD160>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD256")
    derivePBKDF<PKCS5_PBKDF2_HMAC, RIPEMD256>(&pass, &salt, numIter, result);
  else if (hash == "RIPEMD320")
    derivePBKDF<PKCS5_PBKDF2_HMAC, RIPEMD320>(&pass, &salt, numIter, result);
  else
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash invalid hash value");
}
} // namespace rncryptopp
