#include "react-native-cryptopp.h"

void rncryptopp_install(jsi::Runtime &jsiRuntime) {
  /*
  Hash functions
  */
  auto blake2b = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha1"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::blake2b(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto blake2s = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha1"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::blake2s(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto keccak = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha2"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::keccak(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto lsh = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::lsh(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto sha1 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha1"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::sha1(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto sha2 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha2"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::sha2(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto sha3 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::sha3(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto shake = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha1"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::shake(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto sipHash = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha2"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::sipHash(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto sm3 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::sm3(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto tiger = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::tiger(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto ripemd = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::ripemd(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto whirlpool = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sha3"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hash::whirlpool(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  jsi::Object hashFunctions = jsi::Object(jsiRuntime);
  hashFunctions.setProperty(jsiRuntime, "BLAKE2b", std::move(blake2b));
  hashFunctions.setProperty(jsiRuntime, "BLAKE2s", std::move(blake2s));
  hashFunctions.setProperty(jsiRuntime, "Keccak", std::move(keccak));
  hashFunctions.setProperty(jsiRuntime, "LSH", std::move(lsh));
  hashFunctions.setProperty(jsiRuntime, "SHA1", std::move(sha1));
  hashFunctions.setProperty(jsiRuntime, "SHA2", std::move(sha2));
  hashFunctions.setProperty(jsiRuntime, "SHA3", std::move(sha3));
  hashFunctions.setProperty(jsiRuntime, "SHAKE", std::move(shake));
  hashFunctions.setProperty(jsiRuntime, "SipHash", std::move(sipHash));
  hashFunctions.setProperty(jsiRuntime, "SM3", std::move(sm3));
  hashFunctions.setProperty(jsiRuntime, "Tiger", std::move(tiger));
  hashFunctions.setProperty(jsiRuntime, "RIPEMD", std::move(ripemd));
  hashFunctions.setProperty(jsiRuntime, "WHIRLPOOL", std::move(whirlpool));

  /*
  AES and AES candidates
  */
  auto aes_encrypt = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "aes_encrypt"), 5,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::aes_encrypt(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto aes_decrypt = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "aes_decrypt"), 5,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::aes_decrypt(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  jsi::Object AES = jsi::Object(jsiRuntime);
  AES.setProperty(jsiRuntime, "encrypt", std::move(aes_encrypt));
  AES.setProperty(jsiRuntime, "decrypt", std::move(aes_decrypt));

  /*
  Insecure
  */
  auto md2 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "md2"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::md2(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto md4 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "md4"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::md4(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });
  auto md5 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "md5"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::md5(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  jsi::Object insecure = jsi::Object(jsiRuntime);
  insecure.setProperty(jsiRuntime, "md2", std::move(md2));
  insecure.setProperty(jsiRuntime, "md4", std::move(md4));
  insecure.setProperty(jsiRuntime, "md5", std::move(md5));

  /*
  Key Derivation Functions
  */
  auto pkcs5_pbkdf1 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf1"), 4,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::pkcs5_pbkdf1(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto pkcs5_pbkdf2 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf2"), 4,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::pkcs5_pbkdf2(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto pbkdf12 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pbkdf12"), 4,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::pbkdf12(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto hkdf = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "hkdf"), 4,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::hkdf(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  jsi::Object keyDerivation = jsi::Object(jsiRuntime);
  keyDerivation.setProperty(jsiRuntime, "pkcs5_pbkdf1",
                            std::move(pkcs5_pbkdf1));
  keyDerivation.setProperty(jsiRuntime, "pkcs5_pbkdf2",
                            std::move(pkcs5_pbkdf2));
  keyDerivation.setProperty(jsiRuntime, "pbkdf12", std::move(pbkdf12));
  keyDerivation.setProperty(jsiRuntime, "hkdf", std::move(hkdf));

  /*
  Public-key cryptography
  */
  auto generate_rsa_keypair = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "generate_rsa_keypair"),
      1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        jsi::Object result = jsi::Object(rt);
        rncryptopp::RSA::generateKeyPair(rt, args, result);
        return result;
      });

  auto rsa_encrypt = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "rsa_encrypt"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::RSA::encrypt(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto rsa_decrypt = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "rsa_decrypt"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::RSA::decrypt(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto rsa_sign = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "rsa_sign"), 3,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::RSA::sign(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto rsa_verify = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "rsa_verify"), 4,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        bool result;
        rncryptopp::RSA::verify(rt, args, &result);
        return jsi::Value(result);
      });

  auto rsa_recover = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "rsa_recover"), 3,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::RSA::recover(rt, args, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  jsi::Object RSA = jsi::Object(jsiRuntime);
  RSA.setProperty(jsiRuntime, "generateKeyPair",
                  std::move(generate_rsa_keypair));
  RSA.setProperty(jsiRuntime, "encrypt", std::move(rsa_encrypt));
  RSA.setProperty(jsiRuntime, "decrypt", std::move(rsa_decrypt));
  RSA.setProperty(jsiRuntime, "sign", std::move(rsa_sign));
  RSA.setProperty(jsiRuntime, "verify", std::move(rsa_verify));
  RSA.setProperty(jsiRuntime, "recover", std::move(rsa_recover));

  /*
  Utils
  */
  auto toBase64 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "toBase64"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::toBase64(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto toBase64Url = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "toBase64Url"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::toBase64Url(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto toHex = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "toHex"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::toHex(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto toUtf8 = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "toUtf8"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        std::string result;
        rncryptopp::toUtf8(rt, args, count, &result);
        return jsi::String::createFromUtf8(rt, result);
      });

  auto randomBytes = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "randomBytes"), 1,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        int size;
        if (!rncryptopp::valueToInt(args[0], &size))
          throwJSError(rt, "RNCryptopp: randomBytes size is not a number");

        jsi::Function array_buffer_ctor =
            rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
        jsi::Object obj =
            array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
        jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

        AutoSeededRandomPool prng;
        SecByteBlock random(size);
        prng.GenerateBlock(random, random.size());

        // FIXME: see https://github.com/facebook/hermes/issues/564.
        memcpy(buff.data(rt), random.data(), size);
        return obj;
      });

  auto stringToBytes = jsi::Function::createFromHostFunction(
      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "stringToBytes"), 2,
      [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
         size_t count) -> jsi::Value {
        int encoding = rncryptopp::getEncodingFromArgs(rt, args, count, 1);

        std::string bytes;
        if (!rncryptopp::binaryLikeValueToString(rt, args[0], &bytes, encoding,
                                                 encoding))
          throw jsi::JSError(rt,
                             "RNCryptopp: stringToBytes data is not a string");

        int size = (int)bytes.size();

        jsi::Function array_buffer_ctor =
            rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
        jsi::Object obj =
            array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
        jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

        // FIXME: see https://github.com/facebook/hermes/issues/564.
        memcpy(buff.data(rt), bytes.data(), size);
        return obj;
      });

  jsi::Object utils = jsi::Object(jsiRuntime);
  utils.setProperty(jsiRuntime, "toBase64", std::move(toBase64));
  utils.setProperty(jsiRuntime, "toBase64Url", std::move(toBase64Url));
  utils.setProperty(jsiRuntime, "toHex", std::move(toHex));
  utils.setProperty(jsiRuntime, "toUtf8", std::move(toUtf8));
  utils.setProperty(jsiRuntime, "randomBytes", std::move(randomBytes));
  utils.setProperty(jsiRuntime, "stringToBytes", std::move(stringToBytes));

  /*
  Cryptopp module
  */
  jsi::Object module = jsi::Object(jsiRuntime);
  module.setProperty(jsiRuntime, "AES", std::move(AES));
  module.setProperty(jsiRuntime, "RSA", std::move(RSA));
  module.setProperty(jsiRuntime, "hashFunctions", std::move(hashFunctions));
  module.setProperty(jsiRuntime, "insecure", std::move(insecure));
  module.setProperty(jsiRuntime, "keyDerivation", std::move(keyDerivation));
  module.setProperty(jsiRuntime, "utils", std::move(utils));

  jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule",
                                  std::move(module));
}

void rncryptopp_cleanup() {}
