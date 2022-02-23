#ifndef CRYPTOPPEXAMPLE_INSECURE_H
#define CRYPTOPPEXAMPLE_INSECURE_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "cryptlib.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "md2.h"
#include "md4.h"
#include "md5.h"
#include "des.h"

#include "helpers.h"

using namespace facebook;

namespace rncryptopp
{
    void md2(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void md4(jsi::Runtime &rt, std::string &result, const jsi::Value *args);

    void md5(jsi::Runtime &rt, std::string &result, const jsi::Value *args);
}

#endif //CRYPTOPPEXAMPLE_INSECURE_H
