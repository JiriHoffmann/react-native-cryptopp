#ifndef REACT_NATIVE_CRYPTOPP_HELPERS_H
#define REACT_NATIVE_CRYPTOPP_HELPERS_H

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

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp {
bool stringValueToString(jsi::Runtime &runtime, const jsi::Value &value,
                         std::string *str);

bool binaryLikeValueToString(jsi::Runtime &rt, const jsi::Value &value,
                             std::string *str, int stringEncoding = 0,
                             int bufferEncoding = 0);

bool valueToInt(const jsi::Value &value, int *res);

bool valueToDouble(const jsi::Value &value, double *res);

void encode(std::string *in, std::string *out, int encoding);

void hexEncode(std::string &in, std::string &out);

void hexDecode(std::string &in, std::string &out);

void base64Decode(std::string &in, std::string &out);

void base64Encode(std::string &in, std::string &out);

void base64UrlDecode(std::string &in, std::string &out);

void base64UrlEncode(std::string &in, std::string &out);

int getEncodingFromArgs(jsi::Runtime &rt, const jsi::Value *args,
                        size_t argCount, int index, int defaultValue = 0,
                        bool allowUTF8 = true);

template <template <typename> class F> struct invokeWithHash {
  template <typename... R> bool operator()(std::string &hash, R... rest) const {
    if (hash == "BLAKE2b")
      F<BLAKE2b>()(rest...);
    else if (hash == "BLAKE2s")
      F<BLAKE2s>()(rest...);
    else if (hash == "Keccak_224")
      F<Keccak_224>()(rest...);
    else if (hash == "Keccak_256")
      F<Keccak_256>()(rest...);
    else if (hash == "Keccak_384")
      F<Keccak_384>()(rest...);
    else if (hash == "Keccak_512")
      F<Keccak_512>()(rest...);
    else if (hash == "LSH224")
      F<LSH224>()(rest...);
    else if (hash == "LSH256")
      F<LSH256>()(rest...);
    else if (hash == "LSH384")
      F<LSH384>()(rest...);
    else if (hash == "LSH512")
      F<LSH512>()(rest...);
    else if (hash == "SHA1")
      F<SHA1>()(rest...);
    else if (hash == "SHA224")
      F<SHA224>()(rest...);
    else if (hash == "SHA256")
      F<SHA256>()(rest...);
    else if (hash == "SHA384")
      F<SHA384>()(rest...);
    else if (hash == "SHA512")
      F<SHA512>()(rest...);
    else if (hash == "SHA3_224")
      F<SHA3_224>()(rest...);
    else if (hash == "SHA3_256")
      F<SHA3_256>()(rest...);
    else if (hash == "SHA3_384")
      F<SHA3_384>()(rest...);
    else if (hash == "SHA3_512")
      F<SHA3_512>()(rest...);
    else if (hash == "SHAKE128")
      F<SHAKE128>()(rest...);
    else if (hash == "SHAKE256")
      F<SHAKE256>()(rest...);
    else if (hash == "SM3")
      F<SM3>()(rest...);
    else if (hash == "Tiger")
      F<Tiger>()(rest...);
    else if (hash == "RIPEMD128")
      F<RIPEMD128>()(rest...);
    else if (hash == "RIPEMD160")
      F<RIPEMD160>()(rest...);
    else if (hash == "RIPEMD256")
      F<RIPEMD256>()(rest...);
    else if (hash == "RIPEMD320")
      F<RIPEMD320>()(rest...);
    else
      return false;
    return true;
  }
};

template <template <typename T, typename... R> class F>
struct invokeWithBlockCipher {
  template <typename... R>
  bool operator()(std::string &cipher, R... rest) const {
    if (cipher == "ARIA")
      F<ARIA>()(rest...);
    else if (cipher == "Blowfish")
      F<Blowfish>()(rest...);
    else if (cipher == "Camellia")
      F<Camellia>()(rest...);
    else if (cipher == "CHAM64")
      F<CHAM64>()(rest...);
    else if (cipher == "CHAM128")
      F<CHAM128>()(rest...);
    else if (cipher == "HIGHT")
      F<HIGHT>()(rest...);
    else if (cipher == "IDEA")
      F<IDEA>()(rest...);
    else if (cipher == "Kalyna128")
      F<Kalyna128>()(rest...);
    else if (cipher == "Kalyna256")
      F<Kalyna256>()(rest...);
    else if (cipher == "Kalyna512")
      F<Kalyna512>()(rest...);
    else if (cipher == "LEA")
      F<LEA>()(rest...);
    else if (cipher == "SEED")
      F<SEED>()(rest...);
    else if (cipher == "RC5")
      F<RC5>()(rest...);
    else if (cipher == "SHACAL2")
      F<SHACAL2>()(rest...);
    else if (cipher == "SIMECK32")
      F<SIMECK32>()(rest...);
    else if (cipher == "SIMECK64")
      F<SIMECK64>()(rest...);
    else if (cipher == "SIMON64")
      F<SIMON64>()(rest...);
    else if (cipher == "SIMON128")
      F<SIMON128>()(rest...);
    else if (cipher == "SKIPJACK")
      F<SKIPJACK>()(rest...);
    else if (cipher == "SPECK64")
      F<SPECK64>()(rest...);
    else if (cipher == "SPECK128")
      F<SPECK128>()(rest...);
    else if (cipher == "SM4")
      F<SM4>()(rest...);
    else if (cipher == "Threefish256")
      F<Threefish256>()(rest...);
    else if (cipher == "Threefish512")
      F<Threefish512>()(rest...);
    else if (cipher == "Threefish1024")
      F<Threefish1024>()(rest...);
    else if (cipher == "DES_EDE2")
      F<DES_EDE2>()(rest...);
    else if (cipher == "DES_EDE3")
      F<DES_EDE3>()(rest...);
    else if (cipher == "TEA")
      F<TEA>()(rest...);
    else if (cipher == "XTEA")
      F<XTEA>()(rest...);
    else
      return false;
    return true;
  }
};

template <template <typename T, typename... R> class F>
struct invokeWithBlockCipherAES {
  template <typename... R>
  bool operator()(std::string &cipher, R... rest) const {
    if (cipher == "AES")
      F<AES>()(rest...);
    else if (cipher == "RC6")
      F<RC6>()(rest...);
    else if (cipher == "MARS")
      F<MARS>()(rest...);
    else if (cipher == "Twofish")
      F<Twofish>()(rest...);
    else if (cipher == "Serpent")
      F<Serpent>()(rest...);
    else if (cipher == "CAST256")
      F<CAST256>()(rest...);
    else
      return false;
    return true;
  }
};

} // namespace rncryptopp

#endif // REACT_NATIVE_CRYPTOPP_HELPERS_H
