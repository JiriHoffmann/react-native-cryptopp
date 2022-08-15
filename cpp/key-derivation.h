#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/cryptlib.h"
#include "cryptopp/hkdf.h"
#include "cryptopp/pwdbased.h"
#include "cryptopp/scrypt.h"
#include "cryptopp/secblock.h"

#include "JSIHelper.h"
#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp::keyderivation {
void hkdf(jsi::Runtime &rt, CppArgs *args, std::string *target,
          QuickDataType *targetType, StringEncoding *targetEncoding);

void pbkdf12(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding);

void pkcs5_pbkdf1(jsi::Runtime &rt, CppArgs *args, std::string *target,
                  QuickDataType *targetType, StringEncoding *targetEncoding);

void pkcs5_pbkdf2(jsi::Runtime &rt, CppArgs *args, std::string *target,
                  QuickDataType *targetType, StringEncoding *targetEncoding);

void scrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
            QuickDataType *targetType, StringEncoding *targetEncoding);
} // namespace rncryptopp::keyderivation
