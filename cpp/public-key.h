#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <sstream>

#include "cryptopp/osrng.h"
#include "cryptopp/pem.h"
#include "cryptopp/pssr.h"
#include "cryptopp/rsa.h"
#include "cryptopp/whrlpool.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace rncryptopp::jsiHelper;

struct RSAKeyPair {
  std::string n;
  std::string p;
  std::string q;
  std::string d;
  std::string e;
  std::string public_key;
  std::string private_key;
};

namespace rncryptopp::rsa {
RSAKeyPair generateKeyPair(jsi::Runtime &rt, CppArgs *args);

void encrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding);

void decrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType);

void sign(jsi::Runtime &rt, CppArgs *args, std::string *target,
          QuickDataType *targetType, StringEncoding *targetEncoding);

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType);

void recover(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding);
} // namespace rncryptopp::rsa
