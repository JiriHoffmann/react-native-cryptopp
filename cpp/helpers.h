#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/aes.h"
#include "cryptopp/cast.h"
#include "cryptopp/mars.h"
#include "cryptopp/rc6.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/serpent.h"
#include "cryptopp/twofish.h"

#include "cryptopp/blake2.h"
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

#include "cryptopp/base64.h"
#include "cryptopp/hex.h"

#include "JSIHelper.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;
using namespace rncryptopp::jsiHelper;

namespace rncryptopp {

enum StringEncoding {
  ENCODING_UTF8,
  ENCODING_HEX,
  ENCODING_BASE64,
  ENCODING_BASE64URL
};

void encodeString(std::string *in, std::string *out, StringEncoding encoding);

void decodeJSIString(QuickValue &jsiValue, std::string *out,
                     StringEncoding encoding);

StringEncoding getEncodingFromArgs(jsi::Runtime &rt, CppArgs *args,
                                   int argIndex,
                                   StringEncoding defaultValue = ENCODING_UTF8,
                                   bool allowUTF8 = true);

jsi::Value returnStringOrArrayBuffer(jsi::Runtime &rt, std::string &input,
                                     QuickDataType &ouputType,
                                     StringEncoding &outputEncoding);

template <template <typename> class F> struct invokeWithHash {
  template <typename... R>
  bool operator()(std::string &hash_type, R... functionParams) const {
    if (hash_type == "BLAKE2b")
      F<BLAKE2b>()(functionParams...);
    else if (hash_type == "BLAKE2s")
      F<BLAKE2s>()(functionParams...);
    else if (hash_type == "Keccak224")
      F<Keccak_224>()(functionParams...);
    else if (hash_type == "Keccak256")
      F<Keccak_256>()(functionParams...);
    else if (hash_type == "Keccak384")
      F<Keccak_384>()(functionParams...);
    else if (hash_type == "Keccak512")
      F<Keccak_512>()(functionParams...);
    else if (hash_type == "LSH224")
      F<LSH224>()(functionParams...);
    else if (hash_type == "LSH256")
      F<LSH256>()(functionParams...);
    else if (hash_type == "LSH384")
      F<LSH384>()(functionParams...);
    else if (hash_type == "LSH512")
      F<LSH512>()(functionParams...);
    else if (hash_type == "SHA1")
      F<SHA1>()(functionParams...);
    else if (hash_type == "SHA224")
      F<SHA224>()(functionParams...);
    else if (hash_type == "SHA256")
      F<SHA256>()(functionParams...);
    else if (hash_type == "SHA384")
      F<SHA384>()(functionParams...);
    else if (hash_type == "SHA512")
      F<SHA512>()(functionParams...);
    else if (hash_type == "SHA3_224")
      F<SHA3_224>()(functionParams...);
    else if (hash_type == "SHA3_256")
      F<SHA3_256>()(functionParams...);
    else if (hash_type == "SHA3_384")
      F<SHA3_384>()(functionParams...);
    else if (hash_type == "SHA3_512")
      F<SHA3_512>()(functionParams...);
    else if (hash_type == "SHAKE128")
      F<SHAKE128>()(functionParams...);
    else if (hash_type == "SHAKE256")
      F<SHAKE256>()(functionParams...);
    else if (hash_type == "SM3")
      F<SM3>()(functionParams...);
    else if (hash_type == "Tiger")
      F<Tiger>()(functionParams...);
    else if (hash_type == "RIPEMD128")
      F<RIPEMD128>()(functionParams...);
    else if (hash_type == "RIPEMD160")
      F<RIPEMD160>()(functionParams...);
    else if (hash_type == "RIPEMD256")
      F<RIPEMD256>()(functionParams...);
    else if (hash_type == "RIPEMD320")
      F<RIPEMD320>()(functionParams...);
    else if (hash_type == "WHIRLPOOL")
      F<Whirlpool>()(functionParams...);
    else
      return false;
    return true;
  }
};

template <template <typename> class F> struct invokeWithBlockCipher {
  template <typename... R>
  bool operator()(std::string &cipher, bool allowAES, bool allowOther,
                  R... rest) const {
    // AES and candidates block ciphers
    if (cipher == "AES" && allowAES)
      F<AES>()(rest...);
    else if (cipher == "RC6" && allowAES)
      F<RC6>()(rest...);
    else if (cipher == "MARS" && allowAES)
      F<MARS>()(rest...);
    else if (cipher == "Twofish" && allowAES)
      F<Twofish>()(rest...);
    else if (cipher == "Serpent" && allowAES)
      F<Serpent>()(rest...);
    else if (cipher == "CAST256" && allowAES)
      F<CAST256>()(rest...);

    // Other block ciphers
    else if (cipher == "ARIA" && allowOther)
      F<ARIA>()(rest...);
    else if (cipher == "Blowfish" && allowOther)
      F<Blowfish>()(rest...);
    else if (cipher == "Camellia" && allowOther)
      F<Camellia>()(rest...);
    else if (cipher == "CHAM64" && allowOther)
      F<CHAM64>()(rest...);
    else if (cipher == "CHAM128" && allowOther)
      F<CHAM128>()(rest...);
    else if (cipher == "HIGHT" && allowOther)
      F<HIGHT>()(rest...);
    else if (cipher == "IDEA" && allowOther)
      F<IDEA>()(rest...);
    else if (cipher == "Kalyna128" && allowOther)
      F<Kalyna128>()(rest...);
    else if (cipher == "Kalyna256" && allowOther)
      F<Kalyna256>()(rest...);
    else if (cipher == "Kalyna512" && allowOther)
      F<Kalyna512>()(rest...);
    else if (cipher == "LEA" && allowOther)
      F<LEA>()(rest...);
    else if (cipher == "SEED" && allowOther)
      F<SEED>()(rest...);
    else if (cipher == "RC5" && allowOther)
      F<RC5>()(rest...);
    else if (cipher == "SHACAL2" && allowOther)
      F<SHACAL2>()(rest...);
    else if (cipher == "SIMECK32" && allowOther)
      F<SIMECK32>()(rest...);
    else if (cipher == "SIMECK64" && allowOther)
      F<SIMECK64>()(rest...);
    else if (cipher == "SIMON64" && allowOther)
      F<SIMON64>()(rest...);
    else if (cipher == "SIMON128" && allowOther)
      F<SIMON128>()(rest...);
    else if (cipher == "SKIPJACK" && allowOther)
      F<SKIPJACK>()(rest...);
    else if (cipher == "SPECK64" && allowOther)
      F<SPECK64>()(rest...);
    else if (cipher == "SPECK128" && allowOther)
      F<SPECK128>()(rest...);
    else if (cipher == "SM4" && allowOther)
      F<SM4>()(rest...);
    else if (cipher == "Threefish256" && allowOther)
      F<Threefish256>()(rest...);
    else if (cipher == "Threefish512" && allowOther)
      F<Threefish512>()(rest...);
    else if (cipher == "Threefish1024" && allowOther)
      F<Threefish1024>()(rest...);
    else if (cipher == "DES_EDE2" && allowOther)
      F<DES_EDE2>()(rest...);
    else if (cipher == "DES_EDE3" && allowOther)
      F<DES_EDE3>()(rest...);
    else if (cipher == "TEA" && allowOther)
      F<TEA>()(rest...);
    else if (cipher == "XTEA" && allowOther)
      F<XTEA>()(rest...);
    else
      return false;
    return true;
  }
};
} // namespace rncryptopp
