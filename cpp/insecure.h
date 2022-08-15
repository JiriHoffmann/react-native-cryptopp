#pragma once

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
using namespace rncryptopp::jsiHelper;

namespace rncryptopp::insecure {
void md2(jsi::Runtime &rt, CppArgs *args, std::string &target);

void md4(jsi::Runtime &rt, CppArgs *args, std::string &target);

void md5(jsi::Runtime &rt, CppArgs *args, std::string &target);
} // namespace rncryptopp::insecure
