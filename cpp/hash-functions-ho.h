#pragma once

#include <iostream>
#include <sstream>

#include <jsi/jsi.h>

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

#include "hash-functions.h"
#include "helpers.h"

using namespace facebook;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp::HostObjects {
class JSI_EXPORT HashHostObject : public jsi::HostObject {
public:
  HashHostObject(std::string name);

  jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

private:
  std::string hashName;
  std::string hashData;
};

jsi::Value createHashHostObject(jsi::Runtime &rt, const jsi::Value &thisValue,
                                const jsi::Value *args, size_t count);
} // namespace rncryptopp::HostObjects
