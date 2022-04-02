#ifndef CRYPTOPPEXAMPLE_PUBLIC_KEY_H
#define CRYPTOPPEXAMPLE_PUBLIC_KEY_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <sstream>

#include "cryptopp/osrng.h"
#include "cryptopp/pem.h"
#include "cryptopp/pssr.h"
#include "cryptopp/rsa.h"
#include "cryptopp/whrlpool.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp {
namespace RSA {
void generateKeyPair(jsi::Runtime &rt, const jsi::Value *args,
                     jsi::Object &result);

void encrypt(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void decrypt(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void sign(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void verify(jsi::Runtime &rt, const jsi::Value *args, bool *result);

void recover(jsi::Runtime &rt, const jsi::Value *args, std::string *result);
} // namespace RSA
} // namespace rncryptopp
#endif // CRYPTOPPEXAMPLE_PUBLIC_KEY_H
