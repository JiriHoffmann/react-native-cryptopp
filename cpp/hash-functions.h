#ifndef REACT_NATIVE_CRYPTOPP_HASH_FUNCTIONS_H
#define REACT_NATIVE_CRYPTOPP_HASH_FUNCTIONS_H

#include <iostream>
#include <sstream>

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/blake2.h"
#include "cryptopp/crc.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/keccak.h"
#include "cryptopp/lsh.h"
#include "cryptopp/ripemd.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/shake.h"
#include "cryptopp/siphash.h"
#include "cryptopp/sm3.h"
#include "cryptopp/tiger.h"
#include "cryptopp/whrlpool.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp::hash {
jsi::Value blake2b(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count);

jsi::Value blake2s(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count);

jsi::Value keccak(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t count);

jsi::Value lsh(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count);

jsi::Value sha1(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count);

jsi::Value sha2(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count);

jsi::Value sha3(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t count);

jsi::Value shake(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t count);

jsi::Value sipHash(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t count);

jsi::Value sm3(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count);

jsi::Value tiger(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t count);

jsi::Value ripemd(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t count);

jsi::Value whirlpool(jsi::Runtime &rt, const jsi::Value &thisValue,
                     const jsi::Value *args, size_t count);

jsi::Value crc32(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t count);
} // namespace rncryptopp::hash

#endif // REACT_NATIVE_CRYPTOPP_HASH_FUNCTIONS_H
