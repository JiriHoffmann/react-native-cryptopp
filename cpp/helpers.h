#ifndef CRYPTOPPEXAMPLE_HELPERS_H
#define CRYPTOPPEXAMPLE_HELPERS_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/aes.h"
#include "cryptopp/cast.h"
#include "cryptopp/mars.h"
#include "cryptopp/rc6.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/serpent.h"
#include "cryptopp/twofish.h"
#include "cryptopp/base64.h"
#include "cryptopp/hex.h"

using namespace facebook;
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

#endif // CRYPTOPPEXAMPLE_HELPERS_H
