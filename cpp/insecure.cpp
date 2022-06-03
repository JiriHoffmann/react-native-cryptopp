#include "insecure.h"

namespace rncryptopp::insecure {

jsi::Value md2(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data)) {
    throwJSError(rt, "RNCryptopp: Data is not a string");
  }
  Weak::MD2 hash;
  StringSource(data, true,
               new HashFilter(hash, new HexEncoder(new StringSink(result))));
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value md4(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data)) {
    throwJSError(rt, "RNCryptopp: Data is not a string");
  }
  Weak::MD4 hash;
  StringSource(data, true,
               new HashFilter(hash, new HexEncoder(new StringSink(result))));
  return jsi::String::createFromUtf8(rt, result);
}

jsi::Value md5(jsi::Runtime &rt, const jsi::Value &thisValue,
               const jsi::Value *args, size_t count) {
  std::string data, result;
  if (!binaryLikeValueToString(rt, args[0], &data)) {
    throwJSError(rt, "RNCryptopp: Data is not a string");
  }
  Weak::MD5 hash;
  StringSource(data, true,
               new HashFilter(hash, new HexEncoder(new StringSink(result))));
  return jsi::String::createFromUtf8(rt, result);
}

} // namespace rncryptopp::insecure
