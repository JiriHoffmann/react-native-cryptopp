#include "insecure.h"

namespace rncryptopp::insecure {

void md2(jsi::Runtime &rt, CppArgs *args, std::string &target) {
  if (args->size() != 2)
    throwJSError(rt, "RNCryptopp: hash invalid number of arguments");

  if (!isDataStringOrAB(args->at(1))) {
    throwJSError(rt, "RNCryptopp: md2 sata is not a string");
  }
  Weak::MD2 hash;
  StringSource(args->at(1).stringValue, true,
               new HashFilter(hash, new HexEncoder(new StringSink(target))));
}

void md4(jsi::Runtime &rt, CppArgs *args, std::string &target) {
  if (args->size() != 2)
    throwJSError(rt, "RNCryptopp: hash invalid number of arguments");

  if (!isDataStringOrAB(args->at(1))) {
    throwJSError(rt, "RNCryptopp: Data is not a string");
  }
  Weak::MD4 hash;
  StringSource(args->at(1).stringValue, true,
               new HashFilter(hash, new HexEncoder(new StringSink(target))));
}

void md5(jsi::Runtime &rt, CppArgs *args, std::string &target) {
  if (args->size() != 2)
    throwJSError(rt, "RNCryptopp: hash invalid number of arguments");

  if (!isDataStringOrAB(args->at(1))) {
    throwJSError(rt, "RNCryptopp: Data is not a string");
  }
  Weak::MD5 hash;
  StringSource(args->at(1).stringValue, true,
               new HashFilter(hash, new HexEncoder(new StringSink(target))));
}

} // namespace rncryptopp::insecure
