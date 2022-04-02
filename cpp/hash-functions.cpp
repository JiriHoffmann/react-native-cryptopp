#include "hash-functions.h"

namespace rncryptopp {

// function definition
template <class H> void hash(std::string &data, std::string *result) {
  H sha;
  StringSource(data, true,
               new HashFilter(sha, new HexEncoder(new StringSink(*result))));
}

// Array of function pointers
void (*hashPtrs[])(std::string &data,
                   std::string *result) = {
    &hash<BLAKE2b>, // 0
    &hash<BLAKE2s>, // 1

    &hash<Keccak_224>, // 2
    &hash<Keccak_256>, // 3
    &hash<Keccak_384>, // 4
    &hash<Keccak_512>, // 5

    &hash<LSH224>, // 6
    &hash<LSH256>, // 7
    &hash<LSH384>, // 8
    &hash<LSH512>, // 9

    &hash<SHA1>, // 10

    &hash<SHA224>, // 11
    &hash<SHA256>, // 12
    &hash<SHA384>, // 13
    &hash<SHA512>, // 14

    &hash<SHA3_224>, // 15
    &hash<SHA3_256>, // 16
    &hash<SHA3_384>, // 17
    &hash<SHA3_512>, // 18

    &hash<SHAKE128>, // 19
    &hash<SHAKE256>, // 20

    &hash<SipHash<2, 4, false>>, // 21
    &hash<SipHash<4, 8, true>>,  // 22

    &hash<SM3>, // 23

    &hash<Tiger>, // 24

    &hash<RIPEMD128>, // 25
    &hash<RIPEMD160>, // 26
    &hash<RIPEMD256>, // 27
    &hash<RIPEMD320>, // 28

    &hash<Whirlpool> // 29
};

void blake2b(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2s data is not a string or ArrayBuffer");
  hashPtrs[0](data, result);
}

void blake2s(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: BLAKE2b data is not a string or ArrayBuffer");
  hashPtrs[1](data, result);
}

void keccak(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Keccak data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: Keccak size is not a string");

  int sizeIndex = size == "224"   ? 0
                  : size == "256" ? 1
                  : size == "384" ? 2
                  : size == "512" ? 3
                                  : -1;

  if (sizeIndex == -1) {
    throwJSError(rt, "RNCryptopp: Keccak invalid size");
    return;
  }

  hashPtrs[2 + sizeIndex](data, result);
}

void lsh(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: LSH data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: LSH size is not a string");

  int sizeIndex = size == "224"   ? 0
                  : size == "256" ? 1
                  : size == "384" ? 2
                  : size == "512" ? 3
                                  : -1;

  if (sizeIndex == -1) {
    throwJSError(rt, "RNCryptopp: LSH invalid size");
    return;
  }

  hashPtrs[6 + sizeIndex](data, result);
}

void sha1(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: sha1 data is not a string or ArrayBuffer");

  hashPtrs[10](data, result);
}

void sha2(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA2 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA2 size is not a string");

  int index = size == "224"   ? 0
              : size == "256" ? 1
              : size == "384" ? 2
              : size == "512" ? 3
                              : -1;

  if (index == -1) {
    throwJSError(rt, "RNCryptopp: SHA2 invalid size");
    return;
  }

  hashPtrs[11 + index](data, result);
}

void sha3(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHA3 data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHA3 size is not a string");

  int index = size == "224"   ? 0
              : size == "256" ? 1
              : size == "384" ? 2
              : size == "512" ? 3
                              : -1;

  if (index == -1) {
    throwJSError(rt, "RNCryptopp: SHA3 invalid size");
    return;
  }

  hashPtrs[15 + index](data, result);
}

void shake(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SHAKE data is not a string or ArrayBuffer");

  std::string size;
  if (!stringValueToString(rt, args[1], &size))
    throwJSError(rt, "RNCryptopp: SHAKE size is not a string");

  int index = size == "128" ? 0 : size == "256" ? 1 : -1;

  if (index == -1) {
    throwJSError(rt, "RNCryptopp: SHAKE invalid size");
    return;
  }

  hashPtrs[19 + index](data, result);
}

void sipHash(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SipHash data is not a string or ArrayBuffer");

  std::string type;
  if (!stringValueToString(rt, args[1], &type))
    throwJSError(rt, "RNCryptopp: SipHash type is not a string");

  int index = type == "2_4_64" ? 0 : type == "4_8_128" ? 1 : -1;

  if (index == -1) {
    throwJSError(rt, "RNCryptopp: SipHash invalid type");
    return;
  }

  hashPtrs[21 + index](data, result);
}

void sm3(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: SM3 data is not a string or ArrayBuffer");

  hashPtrs[23](data, result);
}

void tiger(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: Tiger data is not a string or ArrayBuffer");

  hashPtrs[24](data, result);
}

void ripemd(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt, "RNCryptopp: RIPEMD data is not a string or ArrayBuffer");

  std::string type;
  if (!stringValueToString(rt, args[1], &type))
    throwJSError(rt, "RNCryptopp: RIPEMD type is not a string");

  int index = type == "128"   ? 0
              : type == "160" ? 1
              : type == "256" ? 2
              : type == "320" ? 3
                              : -1;

  if (index == -1) {
    throwJSError(rt, "RNCryptopp: RIPEMD invalid type");
    return;
  }

  hashPtrs[25 + index](data, result);
}

void whirlpool(jsi::Runtime &rt, const jsi::Value *args, std::string *result) {
  std::string data;
  if (!binaryLikeValueToString(rt, args[0], &data))
    throwJSError(rt,
                 "RNCryptopp: WHIRLPOOL data is not a string or ArrayBuffer");
  hashPtrs[29](data, result);
}
} // namespace rncryptopp
