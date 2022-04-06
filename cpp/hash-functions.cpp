#include "hash-functions.h"

namespace rncryptopp {
namespace hash {

// function definition
template <class H> void hash(std::string *data, std::string *result) {
  H sha;
  StringSource(*data, true,
               new HashFilter(sha, new HexEncoder(new StringSink(*result))));
}

void blake2b(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2s data is not a string or ArrayBuffer");

  hash<BLAKE2b>(&data, result);
}

void blake2s(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2b data is not a string or ArrayBuffer");

  hash<BLAKE2s>(&data, result);
}

void keccak(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Keccak data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: Keccak size is not a string");

  if (size == "224")
    hash<Keccak_224>(&data, result);
  else if (size == "256")
    hash<Keccak_256>(&data, result);
  else if (size == "384")
    hash<Keccak_384>(&data, result);
  else if (size == "512")
    hash<Keccak_512>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: Keccak invalid size");
}

void lsh(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: LSH data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: LSH size is not a string");

  if (size == "224")
    hash<LSH224>(&data, result);
  else if (size == "256")
    hash<LSH256>(&data, result);
  else if (size == "384")
    hash<LSH384>(&data, result);
  else if (size == "512")
    hash<LSH512>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: LSH invalid size");
}

void sha1(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: sha1 data is not a string or ArrayBuffer");

  hash<SHA1>(&data, result);
}

void sha2(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA2 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA2 size is not a string");

  if (size == "224")
    hash<SHA224>(&data, result);
  else if (size == "256")
    hash<SHA256>(&data, result);
  else if (size == "384")
    hash<SHA384>(&data, result);
  else if (size == "512")
    hash<SHA512>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: SHA2 invalid size");
}

void sha3(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA3 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA3 size is not a string");

  if (size == "224")
    hash<SHA3_224>(&data, result);
  else if (size == "256")
    hash<SHA3_256>(&data, result);
  else if (size == "384")
    hash<SHA3_384>(&data, result);
  else if (size == "512")
    hash<SHA3_512>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: SHA3 invalid size");
}

void shake(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHAKE data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHAKE size is not a string");

  if (size == "128")
    hash<SHAKE128>(&data, result);
  else if (size == "256")
    hash<SHAKE256>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: SHAKE invalid size");
}

void sipHash(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SipHash data is not a string or ArrayBuffer");

  std::string type;
  if (!stringValueToString(rt, args[1], &type))
    throwJSError(rt, "RNCryptopp: SipHash type is not a string");

  if (type == "2_4_64")
    hash<SipHash<2, 4, false>>(&data, result);
  else if (type == "4_8_128")
    hash<SipHash<4, 8, true>>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: SipHash invalid type");
}

void sm3(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SM3 data is not a string or ArrayBuffer");

  hash<SM3>(&data, result);
}

void tiger(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Tiger data is not a string or ArrayBuffer");

  hash<Tiger>(&data, result);
}

void ripemd(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: RIPEMD data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: RIPEMD type is not a string");

  if (size == "128")
    hash<RIPEMD128>(&data, result);
  else if (size == "160")
    hash<RIPEMD160>(&data, result);
  else if (size == "256")
    hash<RIPEMD256>(&data, result);
  else if (size == "320")
    hash<RIPEMD320>(&data, result);
  else
    throwJSError(rt, "RNCryptopp: RIPEMD invalid size");
}

void whirlpool(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt,
                 "RNCryptopp: WHIRLPOOL data is not a string or ArrayBuffer");
  hash<Whirlpool>(&data, result);
}
} // namespace hash
} // namespace rncryptopp
