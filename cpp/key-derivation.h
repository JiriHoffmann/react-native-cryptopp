#ifndef REACT_NATIVE_CRYPTOPP_KEY_DERIVATION_H
#define REACT_NATIVE_CRYPTOPP_KEY_DERIVATION_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/hkdf.h"
#include "cryptopp/pwdbased.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp::keyderivation {
jsi::Value hkdf(jsi::Runtime &rt, const jsi::Value &thisValue,
                const jsi::Value *args, size_t argCount);

jsi::Value pbkdf12(jsi::Runtime &rt, const jsi::Value &thisValue,
                   const jsi::Value *args, size_t argCount);

jsi::Value pkcs5_pbkdf1(jsi::Runtime &rt, const jsi::Value &thisValue,
                        const jsi::Value *args, size_t argCount);

jsi::Value pkcs5_pbkdf2(jsi::Runtime &rt, const jsi::Value &thisValue,
                        const jsi::Value *args, size_t argCount);
} // namespace rncryptopp::keyderivation

#endif // REACT_NATIVE_CRYPTOPP_KEY_DERIVATION_H
