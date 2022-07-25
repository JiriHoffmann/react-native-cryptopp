#include "hash-functions-ho.h"

using namespace std;
using namespace facebook;

namespace rncryptopp::HostObjects {
template <class T_hash> HashHostObject<T_hash>::HashHostObject() {
  T_hash hash;
  hashInstance = hash;
}

template <class T_hash>
std::vector<jsi::PropNameID>
HashHostObject<T_hash>::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("update")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("finalize")));
  return result;
}

template <class T_hash>
jsi::Value HashHostObject<T_hash>::get(jsi::Runtime &runtime,
                                       const jsi::PropNameID &propNameId) {
  auto propName = propNameId.utf8(runtime);
  auto funcName = "RNCryptopp.hash." + propName;

  if (propName == "update") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, funcName), 1,
        [this](jsi::Runtime &rt, const jsi::Value &thisVal,
               const jsi::Value *args, size_t count) -> jsi::Value {
          if (count != 1)
            throw jsi::JSError(rt, "RNCryptopp: update() expects 1 argument");

          std::string data;
          if (!binaryLikeValueToString(rt, args[0], &data))
            throwJSError(
                rt, "RNCryptopp: update() data is not a string or ArrayBuffer");

          hashInstance.Update((const CryptoPP::byte *)data.data(), data.size());
          return jsi::Value(0);
        });
  }

  if (propName == "finalize") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, funcName), 0,
        [this](jsi::Runtime &rt, const jsi::Value &thisVal,
               const jsi::Value *args, size_t count) -> jsi::Value {
          if (hashInstance.AlgorithmName() == "CRC32") {
            CRC32 hash;
            word32 digestW32 = 0;
            hashInstance.Final((CryptoPP::byte *)&digestW32);
            std::stringstream ss;
            ss << std::hex << digestW32;
            return jsi::String::createFromUtf8(rt, ss.str());
          }
          std::string digest, encoded;
          digest.resize(hashInstance.DigestSize());
          hashInstance.Final((CryptoPP::byte *)&digest[0]);
          encodeString(&digest, &encoded, ENCODING_HEX);
          return jsi::String::createFromUtf8(rt, encoded);
        });
  }
  return jsi::Value::undefined();
}

// TODO: clean-up
jsi::Value createHashHostObject(jsi::Runtime &rt, const jsi::Value &thisValue,
                                const jsi::Value *args, size_t count) {
  if (count != 1)
    throw jsi::JSError(rt, "RNCryptopp: create() expects 1 argument");

  std::string hash;
  if (!stringValueToString(rt, args[0], &hash))
    throwJSError(rt, "RNCryptopp: Hash type is not a string");

  if (hash == "BLAKE2b") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<BLAKE2b>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "BLAKE2b") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<BLAKE2b>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "BLAKE2b") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<BLAKE2b>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "Keccak_256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<Keccak_256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "Keccak_384") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<Keccak_384>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "Keccak_512") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<Keccak_512>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "LSH224") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<LSH224>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "LSH256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<LSH256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "LSH384") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<LSH384>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "LSH512") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<LSH512>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA1") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA1>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA224") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA224>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA384") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA384>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA512") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA512>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA3_224") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA3_224>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA3_256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA3_256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA3_384") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA3_384>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHA3_512") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHA3_512>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHAKE128") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHAKE128>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SHAKE256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SHAKE256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "SM3") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<SM3>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "Tiger") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<Tiger>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "RIPEMD128") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<RIPEMD128>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "RIPEMD160") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<RIPEMD160>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "RIPEMD256") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<RIPEMD256>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "RIPEMD320") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<RIPEMD320>>();
    return jsi::Object::createFromHostObject(rt, instance);
  } else if (hash == "CRC32") {
    auto instance =
        std::make_shared<rncryptopp::HostObjects::HashHostObject<CRC32>>();
    return jsi::Object::createFromHostObject(rt, instance);
  }
  throwJSError(rt, "RNCryptopp: Hash type is not valid");
  return jsi::Value::undefined();
}
} // namespace rncryptopp::HostObjects
