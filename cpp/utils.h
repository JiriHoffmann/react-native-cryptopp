#ifndef REACT_NATIVE_CRYPTOPP_UTILS_H
#define REACT_NATIVE_CRYPTOPP_UTILS_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/osrng.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp::utils {
jsi::Value toBase64(jsi::Runtime &rt, const jsi::Value &thisValue,
                    const jsi::Value *args, size_t argCount);

jsi::Value toBase64Url(jsi::Runtime &rt, const jsi::Value &thisValue,
                       const jsi::Value *args, size_t argCount);

jsi::Value toHex(jsi::Runtime &rt, const jsi::Value &thisValue,
                 const jsi::Value *args, size_t argCount);

jsi::Value toUtf8(jsi::Runtime &rt, const jsi::Value &thisValue,
                  const jsi::Value *args, size_t argCount);

jsi::Value randomBytes(jsi::Runtime &rt, const jsi::Value &thisValue,
                       const jsi::Value *args, size_t argCount);

jsi::Value stringToBytes(jsi::Runtime &rt, const jsi::Value &thisValue,
                         const jsi::Value *args, size_t argCount);

} // namespace rncryptopp::utils
#endif // REACT_NATIVE_CRYPTOPP_UTILS_H
