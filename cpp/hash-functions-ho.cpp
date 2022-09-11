#include "hash-functions-ho.h"

#include <utility>

namespace rncryptopp::HostObjects {
HashHostObject::HashHostObject(std::string name) { hashName = std::move(name); }

std::vector<jsi::PropNameID>
HashHostObject::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("update")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("finalize")));
  return result;
}

jsi::Value HashHostObject::get(jsi::Runtime &runtime,
                               const jsi::PropNameID &propNameId) {
  auto propName = propNameId.utf8(runtime);
  auto funcName = "RNCryptopp.hash." + propName;

  if (propName == "update") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, funcName), 1,
        [this](jsi::Runtime &rt, const jsi::Value &thisVal,
               const jsi::Value *functionArgs, size_t count) -> jsi::Value {
          CppArgs args;
          parseJSIArgs(rt, functionArgs, count, &args);

          if (args.empty())
            throw jsi::JSError(rt,
                               "RNCryptopp: update() expects 1 argument: data");

          if (args.at(0).dataType != STRING &&
              args.at(0).dataType != ARRAY_BUFFER)
            throw jsi::JSError(rt, "RNCryptopp: update() first argument must "
                                   "be a string or ArrayBuffer");

          std::string newData = args.at(0).stringValue;
          hashData = hashData + newData;
          return jsi::Value();
        });
  }

  if (propName == "finalize") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, funcName), 0,
        [this](jsi::Runtime &rt, const jsi::Value &thisVal,
               const jsi::Value *args, size_t count) -> jsi::Value {
          std::string result;
          if (hashName == "SipHash_2_4_64") {
            SipHash<2, 4, false> hash;
            StringSource(
                hashData, true,
                new HashFilter(hash, new HexEncoder(new StringSink(result))));
          } else if (hashName == "SipHash_4_8_128") {
            SipHash<4, 8, true> hash;
            StringSource(
                hashData, true,
                new HashFilter(hash, new HexEncoder(new StringSink(result))));

          } else if (hashName == "CRC32") {
            CRC32 hash;
            word32 digest = 0;
            hash.CalculateDigest(
                reinterpret_cast<CryptoPP::byte *>(&digest),
                reinterpret_cast<CryptoPP::byte const *>(hashData.data()),
                hashData.size());
            std::stringstream ss;
            ss << std::hex << digest;
            result = ss.str();
          } else {
            auto hasResult = invokeWithHash<rncryptopp::hash::calculate_hash>()(
                hashName, &hashData, &result);
            if (!hasResult)
              throwJSError(rt, "RNCryptopp: hash - invalid hash name.");
          }
          hashData = "";
          return jsi::String::createFromUtf8(rt, result);
        });
  }
  return jsi::Value::undefined();
}

jsi::Value createHashHostObject(jsi::Runtime &rt, const jsi::Value &thisValue,
                                const jsi::Value *functionArgs, size_t count) {
  CppArgs args;
  parseJSIArgs(rt, functionArgs, count, &args);

  if (args.empty() || args.at(0).dataType != STRING)
    throw jsi::JSError(rt, "RNCryptopp: create() expects 1 argument: name");

  std::string hash = args.at(0).stringValue;

  auto instance =
      std::make_shared<rncryptopp::HostObjects::HashHostObject>(hash);
  return jsi::Object::createFromHostObject(rt, instance);
}
} // namespace rncryptopp::HostObjects
