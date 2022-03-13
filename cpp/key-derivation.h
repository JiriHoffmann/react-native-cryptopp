#ifndef CRYPTOPPEXAMPLE_KEY_DERIVATION_H
#define CRYPTOPPEXAMPLE_KEY_DERIVATION_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/hkdf.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/blake2.h"
#include "cryptopp/pwdbased.h"

#include "helpers.h"


using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp
{
    void hkdf(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void pbkdf12(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void pkcs5_pbkdf1(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void pkcs5_pbkdf2(jsi::Runtime &rt, std::string &result, const jsi::Value *args);
}

#endif //CRYPTOPPEXAMPLE_KEY_DERIVATION_H
