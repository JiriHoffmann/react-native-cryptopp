#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/osrng.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp::utils {
void toBase64(jsi::Runtime &rt, CppArgs *args, std::string *target,
              StringEncoding *targetEncoding);

void toBase64Url(jsi::Runtime &rt, CppArgs *args, std::string *target,
                 StringEncoding *targetEncoding);

void toHex(jsi::Runtime &rt, CppArgs *args, std::string *target,
           StringEncoding *targetEncoding);

void toUtf8(jsi::Runtime &rt, CppArgs *args, std::string *target,
            StringEncoding *targetEncoding);

void randomBytes(jsi::Runtime &rt, CppArgs *args, std::string *target,
                 QuickDataType *targetType);

void stringToBytes(jsi::Runtime &rt, CppArgs *args, std::string *target,
                   QuickDataType *targetType);

} // namespace rncryptopp::utils
