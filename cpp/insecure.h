#ifndef REACT_NATIVE_CRYPTOPP_INSECURE_H
#define REACT_NATIVE_CRYPTOPP_INSECURE_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "cryptopp/md2.h"
#include "cryptopp/md4.h"
#include "cryptopp/md5.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp::insecure {
jsi::Value md2(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count);

jsi::Value md4(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count);

jsi::Value md5(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count);
} // namespace rncryptopp::insecure

#endif // REACT_NATIVE_CRYPTOPP_INSECURE_H
