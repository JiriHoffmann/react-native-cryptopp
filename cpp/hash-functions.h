#pragma once

#include <iostream>
#include <sstream>

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "JSIHelper.h"
#include "cryptopp/blake2.h"
#include "cryptopp/crc.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/keccak.h"
#include "cryptopp/lsh.h"
#include "cryptopp/ripemd.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/shake.h"
#include "cryptopp/siphash.h"
#include "cryptopp/sm3.h"
#include "cryptopp/tiger.h"
#include "cryptopp/whrlpool.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp::hash {
template <typename H> struct calculate_hash {
  void operator()(std::string *data, std::string *result) const {
    H hash;
    StringSource(*data, true,
                 new HashFilter(hash, new HexEncoder(new StringSink(*result))));
  }
};

void hash(jsi::Runtime &rt, CppArgs *args, std::string *result);
} // namespace rncryptopp::hash
