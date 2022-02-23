#ifndef CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
#define CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H

#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "helpers.h"


using namespace facebook;

namespace rncryptopp {
    void sha1(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void sha2(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void sha3(jsi::Runtime &rt, std::string &result, const jsi::Value *args);
}


#endif //CRYPTOPPEXAMPLE_HASH_FUNCTIONS_H
