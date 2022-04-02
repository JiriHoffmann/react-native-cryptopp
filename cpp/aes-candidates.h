#ifndef REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H
#define REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <string>

#include "cryptopp/base64.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/xts.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp {
void aes_encrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
                 std::string *result);

void aes_decrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
                 std::string *result);
} // namespace rncryptopp

#endif // REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H
