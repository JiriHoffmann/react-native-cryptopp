#ifndef CRYPTOPPEXAMPLE_KEY_DERIVATION_H
#define CRYPTOPPEXAMPLE_KEY_DERIVATION_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/blake2.h"
#include "cryptopp/hkdf.h"
#include "cryptopp/lsh.h"
#include "cryptopp/pwdbased.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/shake.h"
#include "cryptopp/sm3.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp {
void hkdf(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void pbkdf12(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void pkcs5_pbkdf1(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result);

void pkcs5_pbkdf2(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result);
} // namespace rncryptopp

#endif // CRYPTOPPEXAMPLE_KEY_DERIVATION_H
