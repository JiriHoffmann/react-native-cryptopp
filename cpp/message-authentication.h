#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/cryptlib.h"

#include "cryptopp/blake2.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/hmac.h"
#include "cryptopp/keccak.h"
#include "cryptopp/lsh.h"
#include "cryptopp/ripemd.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/shake.h"
#include "cryptopp/sm3.h"
#include "cryptopp/tiger.h"
#include "cryptopp/whrlpool.h"

#include "cryptopp/aria.h"
#include "cryptopp/blowfish.h"
#include "cryptopp/camellia.h"
#include "cryptopp/cham.h"
#include "cryptopp/cmac.h"
#include "cryptopp/des.h"
#include "cryptopp/hight.h"
#include "cryptopp/idea.h"
#include "cryptopp/kalyna.h"
#include "cryptopp/lea.h"
#include "cryptopp/rc5.h"
#include "cryptopp/seed.h"
#include "cryptopp/shacal2.h"
#include "cryptopp/simeck.h"
#include "cryptopp/simon.h"
#include "cryptopp/skipjack.h"
#include "cryptopp/sm4.h"
#include "cryptopp/speck.h"
#include "cryptopp/tea.h"
#include "cryptopp/threefish.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp {
namespace hmac {

void generate(jsi::Runtime &rt, CppArgs *args, std::string *target,
              QuickDataType *targetType, StringEncoding *targetEncoding);

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType);

} // namespace hmac

namespace cmac {

void generate(jsi::Runtime &rt, CppArgs *args, std::string *target,
              QuickDataType *targetType, StringEncoding *targetEncoding);

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType);

} // namespace cmac
} // namespace rncryptopp
