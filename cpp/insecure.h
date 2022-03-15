#ifndef CRYPTOPPEXAMPLE_INSECURE_H
#define CRYPTOPPEXAMPLE_INSECURE_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "cryptopp/md2.h"
#include "cryptopp/md4.h"
#include "cryptopp/md5.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp
{
    void md2(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void md4(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void md5(jsi::Runtime &rt, std::string &result, const jsi::Value *args);
}

#endif // CRYPTOPPEXAMPLE_INSECURE_H
