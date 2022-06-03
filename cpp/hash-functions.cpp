#include "hash-functions.h"

namespace rncryptopp::hash {

// function definition
template <class H> void hash(std::string *data, std::string *result) {
  H sha;
  StringSource(*data, true,
               new HashFilter(sha, new HexEncoder(new StringSink(*result))));
}

jsi::Value blake2b(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2s data is not a string or ArrayBuffer");

  hash<BLAKE2b>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value blake2s(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2b data is not a string or ArrayBuffer");

  hash<BLAKE2s>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value keccak(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Keccak data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: Keccak size is not a string");

  if (size == "224")
    hash<Keccak_224>(&data, &result);
  else if (size == "256")
    hash<Keccak_256>(&data, &result);
  else if (size == "384")
    hash<Keccak_384>(&data, &result);
  else if (size == "512")
    hash<Keccak_512>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: Keccak invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value lsh(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: LSH data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: LSH size is not a string");

  if (size == "224")
    hash<LSH224>(&data, &result);
  else if (size == "256")
    hash<LSH256>(&data, &result);
  else if (size == "384")
    hash<LSH384>(&data, &result);
  else if (size == "512")
    hash<LSH512>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: LSH invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value sha1(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: sha1 data is not a string or ArrayBuffer");

  hash<SHA1>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value sha2(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA2 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA2 size is not a string");

  if (size == "224")
    hash<SHA224>(&data, &result);
  else if (size == "256")
    hash<SHA256>(&data, &result);
  else if (size == "384")
    hash<SHA384>(&data, &result);
  else if (size == "512")
    hash<SHA512>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: SHA2 invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value sha3(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA3 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA3 size is not a string");

  if (size == "224")
    hash<SHA3_224>(&data, &result);
  else if (size == "256")
    hash<SHA3_256>(&data, &result);
  else if (size == "384")
    hash<SHA3_384>(&data, &result);
  else if (size == "512")
    hash<SHA3_512>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: SHA3 invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value shake(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHAKE data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHAKE size is not a string");

  if (size == "128")
    hash<SHAKE128>(&data, &result);
  else if (size == "256")
    hash<SHAKE256>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: SHAKE invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value sipHash(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SipHash data is not a string or ArrayBuffer");

  std::string type;
  if (!stringValueToString(rt, args[1], &type))
    throwJSError(rt, "RNCryptopp: SipHash type is not a string");

  if (type == "2_4_64")
    hash<SipHash<2, 4, false>>(&data, &result);
  else if (type == "4_8_128")
    hash<SipHash<4, 8, true>>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: SipHash invalid type");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value sm3(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SM3 data is not a string or ArrayBuffer");

  hash<SM3>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value tiger(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Tiger data is not a string or ArrayBuffer");

  hash<Tiger>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value ripemd(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: RIPEMD data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: RIPEMD type is not a string");

  if (size == "128")
    hash<RIPEMD128>(&data, &result);
  else if (size == "160")
    hash<RIPEMD160>(&data, &result);
  else if (size == "256")
    hash<RIPEMD256>(&data, &result);
  else if (size == "320")
    hash<RIPEMD320>(&data, &result);
  else
    throwJSError(rt, "RNCryptopp: RIPEMD invalid size");
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value whirlpool(jsi::Runtime &rt, const jsi::Value &thisValue,
                     const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt,
                 "RNCryptopp: WHIRLPOOL data is not a string or ArrayBuffer");
  hash<Whirlpool>(&data, &result);
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value crc32(jsi::Runtime &rt, const jsi::Value &thisValue,
                       const jsi::Value *args, size_t count) {
    std::string data;
    if (!binaryLikeValueToString(rt, args[0], &data))
      throwJSError(rt,
                   "RNCryptopp: CRC32 data is not a string or ArrayBuffer");

  CRC32 hash;
  word32 digest = 0;
  hash.CalculateDigest(
          reinterpret_cast<byte*>( &digest ),
          reinterpret_cast<byte const*>(data.c_str()),
          data.size()
  );
    std::stringstream ss;
    ss << std::hex << digest;
    return jsi::String::createFromUtf8(rt, ss.str());
}
} // namespace rncryptopp::hash
