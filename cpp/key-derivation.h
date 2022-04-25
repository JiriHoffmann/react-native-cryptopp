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

namespace rncryptopp {
void hkdf(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void pbkdf12(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void pkcs5_pbkdf1(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result);

void pkcs5_pbkdf2(jsi::Runtime &rt, const jsi::Value *args,
                  std::string *result);
} // namespace rncryptopp

#endif // REACT_NATIVE_CRYPTOPP_KEY_DERIVATION_H
