#ifndef CRYPTOPPEXAMPLE_INSECURE_H
#define CRYPTOPPEXAMPLE_INSECURE_H

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

namespace rncryptopp {
void md2(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void md4(jsi::Runtime &rt, const jsi::Value *args, std::string *result);

void md5(jsi::Runtime &rt, const jsi::Value *args, std::string *result);
} // namespace rncryptopp

#endif // CRYPTOPPEXAMPLE_INSECURE_H
