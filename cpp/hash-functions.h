#ifndef CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
#define CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp
{
    void sha1(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sha2(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

    void sha3(jsi::Runtime &rt, const jsi::Value *args, std::string *result);
}

#endif // CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
