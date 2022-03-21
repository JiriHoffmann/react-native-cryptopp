#ifndef CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
#define CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/blake2.h"
#include "cryptopp/keccak.h"
#include "cryptopp/lsh.h"
#include "cryptopp/shake.h"
#include "cryptopp/siphash.h"
#include "cryptopp/sm3.h"
#include "cryptopp/tiger.h"
#include "cryptopp/ripemd.h"
#include "cryptopp/whrlpool.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp
{
    void blake2b(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void blake2s(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void keccak(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void lsh(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sha1(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sha2(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sha3(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void shake(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sipHash(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sm3(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void tiger(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void ripemd(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void whirlpool(jsi::Runtime &rt, const jsi::Value *args, std::string *result);
}

#endif // CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
