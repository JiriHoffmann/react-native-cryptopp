#ifndef REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H
#define REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <string>

#include "cryptopp/modes.h"

#include "cryptopp/ccm.h"
#include "cryptopp/eax.h"
#include "cryptopp/gcm.h"
#include "cryptopp/xts.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp {
namespace aescandidates {

void encrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string &cipher, std::string *result);

void decrypt(jsi::Runtime &rt, const jsi::Value *args, size_t argCount,
             std::string &cipher, std::string *result);

} // namespace aescandidates
} // namespace rncryptopp

#endif // REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_H
