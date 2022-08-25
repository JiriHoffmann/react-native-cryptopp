#include "key-derivation.h"

namespace rncryptopp::keyderivation {
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
  *result = std::string(reinterpret_cast<char const *>(derived), derivedLen);
}

template <typename T> struct deriveHKDF_wrapper {
  template <typename... R> void operator()(R... rest) const {
    deriveHKDF<T>(rest...);
  }
};

void hkdf(jsi::Runtime &rt, CppArgs *args, std::string *target,
          QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 5)
    throwJSError(rt, "RNCryptopp: hkdf invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt,
                 "RNCryptopp: hkdf password is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(rt, "RNCryptopp: hkdf salt is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(3)))
    throwJSError(rt, "RNCryptopp: hkdf info is not a string or ArrayBuffer");

  if (!isDataString(args->at(4)))
    throwJSError(rt, "RNCryptopp: hkdf hash is not a string");

  std::string pass = args->at(1).stringValue;
  std::string salt = args->at(2).stringValue;
  std::string info = args->at(3).stringValue;
  std::string hash = args->at(4).stringValue;

  //  Derive
  if (!invokeWithHash<deriveHKDF_wrapper>()(hash, &pass, &salt, &info, target))
    throwJSError(rt, "RNCryptopp: hkdf hash invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_HEX;
}

/**
 * Derivation function used for pbkdf12, pkcs5_pbkdf1, and pkcs5_pbkdf2
 *
 * @tparam T_func PasswordBasedKeyDerivationFunction
 * @tparam T_hash HashTransformation class
 */
template <template <class> class T_func, class T_hash>
void derivePBKDF(std::string *secret, std::string *salt, int iterations,
                 std::string *result) {
  T_func<T_hash> func;
  byte derived[T_hash::DIGESTSIZE];
  size_t derivedLen = sizeof(derived);
  byte unused = 0;

  func.DeriveKey(derived, derivedLen, unused,
                 reinterpret_cast<const byte *>(secret->data()), secret->size(),
                 reinterpret_cast<const byte *>(salt->data()), salt->size(),
                 iterations, 0.0f);
  *result = std::string(reinterpret_cast<char const *>(derived), derivedLen);
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

void pbkdf12(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 5)
    throwJSError(rt, "RNCryptopp: pbkdf12 invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt,
                 "RNCryptopp: pbkdf12 password is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(rt, "RNCryptopp: pbkdf12 salt is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: pbkdf12 hash is not a string");

  if (!isDataInteger(args->at(4)))
    throwJSError(rt, "RNCryptopp: pbkdf12 numIter in not a number");

  std::string pass = args->at(1).stringValue;
  std::string salt = args->at(2).stringValue;
  std::string hash = args->at(3).stringValue;
  int numIter = args->at(4).doubleOrIntValue;

  // Derive
  if (!invokeWithHash<derivePKCS12_PBKDF_wrapper>()(hash, &pass, &salt, numIter,
                                                    target))
    throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_HEX;
}

void pkcs5_pbkdf1(jsi::Runtime &rt, CppArgs *args, std::string *target,
                  QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 5)
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf1 password is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf1 salt is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash is not a string");

  if (!isDataInteger(args->at(4)))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 numIter in not a number");

  std::string pass = args->at(1).stringValue;
  std::string salt = args->at(2).stringValue;
  std::string hash = args->at(3).stringValue;
  int numIter = args->at(4).doubleOrIntValue;

  if (!invokeWithHash<derivePKCS5_PBKDF1_wrapper>()(hash, &pass, &salt, numIter,
                                                    target))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_HEX;
}

void pkcs5_pbkdf2(jsi::Runtime &rt, CppArgs *args, std::string *target,
                  QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 5)
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf2 password is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(
        rt, "RNCryptopp: pkcs5_pbkdf2 salt is not a string or ArrayBuffer");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash is not a string");

  if (!isDataInteger(args->at(4)))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 numIter in not a number");

  std::string pass = args->at(1).stringValue;
  std::string salt = args->at(2).stringValue;
  std::string hash = args->at(3).stringValue;
  int numIter = args->at(4).doubleOrIntValue;

  if (!invokeWithHash<derivePKCS5_PBKDF2_HMAC_wrapper>()(hash, &pass, &salt,
                                                         numIter, target))
    throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash invalid hash value");

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_HEX;
}

void scrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
            QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 7)
    throwJSError(rt, "RNCryptopp: scrypt invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt,
                 "RNCryptopp: scrypt password is not a string or ArrayBuffer");

  if (!isDataStringOrAB(args->at(2)))
    throwJSError(rt, "RNCryptopp: scrypt salt is not a string or ArrayBuffer");

  if (!isDataInteger(args->at(3)))
    throwJSError(rt, "RNCryptopp: scrypt N is not a string");

  if (!isDataInteger(args->at(4)))
    throwJSError(rt, "RNCryptopp: scrypt r in not a number");

  if (!isDataInteger(args->at(5)))
    throwJSError(rt, "RNCryptopp: scrypt p in not a number");

  if (!isDataInteger(args->at(6)))
    throwJSError(rt, "RNCryptopp: scrypt dkLen in not a number");

  std::string pass = args->at(1).stringValue;
  std::string salt = args->at(2).stringValue;
  int N = args->at(3).doubleOrIntValue;
  int r = args->at(4).doubleOrIntValue;
  int p = args->at(5).doubleOrIntValue;
  int dkLen = args->at(6).doubleOrIntValue;

  SecByteBlock derived(dkLen);

  Scrypt scrypt;
  scrypt.DeriveKey(derived, derived.size(),
                   reinterpret_cast<const byte *>(pass.data()), pass.size(),
                   reinterpret_cast<const byte *>(salt.data()), salt.size(), N,
                   r, p);

  StringSource(derived, int(dkLen / 4), true, new StringSink(*target));
  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_HEX;
}
} // namespace rncryptopp::keyderivation
