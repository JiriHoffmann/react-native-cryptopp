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

  hkdf.DeriveKey(derived, derivedLen,
                 reinterpret_cast<const byte *>(secret->data()), secret->size(),
                 reinterpret_cast<const byte *>(salt->data()), salt->size(),
                 reinterpret_cast<const byte *>(info->data()), info->size());
  std::string s(reinterpret_cast<char const *>(derived), derivedLen);
  hexEncode(s, *result);
}

template <typename T> struct deriveHKDF_wrapper {
  template <typename... R> void operator()(R... rest) const {
    deriveHKDF<T>(rest...);
  }
};

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

  if (!invokeWithHash<deriveHKDF_wrapper>()(hash, &pass, &salt, &info, result))
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
                 reinterpret_cast<const byte *>(secret->data()), secret->size(),
                 reinterpret_cast<const byte *>(salt->data()), salt->size(),
                 iterations, 0.0f);
  std::string s(reinterpret_cast<char const *>(derived), derivedLen);
  hexEncode(s, *result);
}

template <typename T> struct derivePKCS12_PBKDF_wrapper {
  template <typename... R> void operator()(R... rest) const {
    derivePBKDF<PKCS12_PBKDF, T>(rest...);
  }
};

template <typename T> struct derivePKCS5_PBKDF1_wrapper {
  template <typename... R> void operator()(R... rest) const {
    derivePBKDF<PKCS5_PBKDF1, T>(rest...);
  }
};

template <typename T> struct derivePKCS5_PBKDF2_HMAC_wrapper {
  template <typename... R> void operator()(R... rest) const {
    derivePBKDF<PKCS5_PBKDF2_HMAC, T>(rest...);
  }
};

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

  if (!invokeWithHash<derivePKCS12_PBKDF_wrapper>()(hash, &pass, &salt, numIter,
                                                    result))
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

  if (!invokeWithHash<derivePKCS5_PBKDF1_wrapper>()(hash, &pass, &salt, numIter,
                                                    result))
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

  if (!invokeWithHash<derivePKCS5_PBKDF2_HMAC_wrapper>()(hash, &pass, &salt,
                                                         numIter, result))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash invalid hash value");
}
} // namespace rncryptopp
