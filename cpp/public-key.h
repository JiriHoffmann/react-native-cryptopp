#ifndef REACT_NATIVE_CRYPTOPP_PUBLIC_KEY_H
#define REACT_NATIVE_CRYPTOPP_PUBLIC_KEY_H

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

namespace rncryptopp::rsa {
jsi::Value generateKeyPair(jsi::Runtime &rt, const jsi::Value &thisValue,
                           const jsi::Value *args, size_t argCount);

jsi::Value encrypt(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t argCount);

jsi::Value decrypt(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t argCount);

jsi::Value sign(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t argCount);

jsi::Value verify(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t argCount);

jsi::Value recover(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t argCount);
} // namespace rncryptopp::rsa
#endif // REACT_NATIVE_CRYPTOPP_PUBLIC_KEY_H
