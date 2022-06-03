#include "react-native-cryptopp.h"

void rncryptopp_install(jsi::Runtime &jsiRuntime) {
  /*
  Hash functions
  */
  jsi::Object hashFunctions = jsi::Object(jsiRuntime);
  hashFunctions.setProperty(
      jsiRuntime, "BLAKE2b",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "BLAKE2b"), 1,
          rncryptopp::hash::blake2b));
  hashFunctions.setProperty(
      jsiRuntime, "BLAKE2s",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "BLAKE2s"), 1,
          rncryptopp::hash::blake2s));
  hashFunctions.setProperty(jsiRuntime, "Keccak",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "Keccak"),
                                2, rncryptopp::hash::keccak));
  hashFunctions.setProperty(jsiRuntime, "LSH",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "LSH"), 2,
                                rncryptopp::hash::lsh));
  hashFunctions.setProperty(jsiRuntime, "SHA1",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "SHA1"),
                                1, rncryptopp::hash::sha1));
  hashFunctions.setProperty(jsiRuntime, "SHA2",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "SHA2"),
                                2, rncryptopp::hash::sha2));
  hashFunctions.setProperty(jsiRuntime, "SHA3",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "SHA3"),
                                2, rncryptopp::hash::sha3));
  hashFunctions.setProperty(jsiRuntime, "SHAKE",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "SHAKE"),
                                2, rncryptopp::hash::shake));
  hashFunctions.setProperty(
      jsiRuntime, "SipHash",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "SipHash"), 2,
          rncryptopp::hash::sipHash));
  hashFunctions.setProperty(jsiRuntime, "SM3",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "SM3"), 1,
                                rncryptopp::hash::sm3));
  hashFunctions.setProperty(jsiRuntime, "Tiger",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "Tiger"),
                                1, rncryptopp::hash::tiger));
  hashFunctions.setProperty(jsiRuntime, "RIPEMD",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "RIPEMD"),
                                2, rncryptopp::hash::ripemd));
  hashFunctions.setProperty(
      jsiRuntime, "WHIRLPOOL",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "WHIRLPOOL"), 1,
          rncryptopp::hash::whirlpool));

  hashFunctions.setProperty(
          jsiRuntime, "CRC32",
          jsi::Function::createFromHostFunction(
                  jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "CRC32"), 1,
                  rncryptopp::hash::crc32));
  /*
  AES and AES candidates
  */
  jsi::Object AES = jsi::Object(jsiRuntime);
  AES.setProperty(jsiRuntime, "encrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
                      rncryptopp::aescandidates::encrypt<CryptoPP::AES>));
  AES.setProperty(jsiRuntime, "decrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
                      rncryptopp::aescandidates::decrypt<CryptoPP::AES>));

  jsi::Object RC6 = jsi::Object(jsiRuntime);
  RC6.setProperty(jsiRuntime, "encrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
                      rncryptopp::aescandidates::encrypt<CryptoPP::RC6>));
  RC6.setProperty(jsiRuntime, "decrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
                      rncryptopp::aescandidates::decrypt<CryptoPP::RC6>));

  jsi::Object MARS = jsi::Object(jsiRuntime);
  MARS.setProperty(jsiRuntime, "encrypt",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
                       rncryptopp::aescandidates::encrypt<CryptoPP::MARS>));
  MARS.setProperty(jsiRuntime, "decrypt",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
                       rncryptopp::aescandidates::decrypt<CryptoPP::MARS>));

  jsi::Object Twofish = jsi::Object(jsiRuntime);
  Twofish.setProperty(
      jsiRuntime, "encrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
          rncryptopp::aescandidates::encrypt<CryptoPP::Twofish>));
  Twofish.setProperty(
      jsiRuntime, "decrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
          rncryptopp::aescandidates::decrypt<CryptoPP::Twofish>));

  jsi::Object Serpent = jsi::Object(jsiRuntime);
  Serpent.setProperty(
      jsiRuntime, "encrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
          rncryptopp::aescandidates::encrypt<CryptoPP::Serpent>));
  Serpent.setProperty(
      jsiRuntime, "decrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
          rncryptopp::aescandidates::decrypt<CryptoPP::Serpent>));

  jsi::Object CAST256 = jsi::Object(jsiRuntime);
  CAST256.setProperty(
      jsiRuntime, "encrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 5,
          rncryptopp::aescandidates::encrypt<CryptoPP::CAST256>));
  CAST256.setProperty(
      jsiRuntime, "decrypt",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 5,
          rncryptopp::aescandidates::decrypt<CryptoPP::CAST256>));

  /*
  Insecure
  */
  jsi::Object insecure = jsi::Object(jsiRuntime);
  insecure.setProperty(jsiRuntime, "md2",
                       jsi::Function::createFromHostFunction(
                           jsiRuntime,
                           jsi::PropNameID::forAscii(jsiRuntime, "md2"), 1,
                           rncryptopp::insecure::md2));
  insecure.setProperty(jsiRuntime, "md4",
                       jsi::Function::createFromHostFunction(
                           jsiRuntime,
                           jsi::PropNameID::forAscii(jsiRuntime, "md4"), 1,
                           rncryptopp::insecure::md4));
  insecure.setProperty(jsiRuntime, "md5",
                       jsi::Function::createFromHostFunction(
                           jsiRuntime,
                           jsi::PropNameID::forAscii(jsiRuntime, "md5"), 1,
                           rncryptopp::insecure::md5));

  /*
   * Message authentication codes
   */
  jsi::Object HMAC = jsi::Object(jsiRuntime);
  HMAC.setProperty(jsiRuntime, "generate",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "generate"), 4,
                       rncryptopp::hmac::generate));
  HMAC.setProperty(jsiRuntime, "verify",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "verify"), 5,
                       rncryptopp::hmac::verify));

  jsi::Object CMAC = jsi::Object(jsiRuntime);
  CMAC.setProperty(jsiRuntime, "generate",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "generate"), 4,
                       rncryptopp::cmac::generate));
  CMAC.setProperty(jsiRuntime, "verify",
                   jsi::Function::createFromHostFunction(
                       jsiRuntime,
                       jsi::PropNameID::forAscii(jsiRuntime, "verify"), 5,
                       rncryptopp::cmac::verify));

  /*
   * Public Key Derivation Functions
   */
  jsi::Object keyDerivation = jsi::Object(jsiRuntime);
  keyDerivation.setProperty(jsiRuntime, "hkdf",
                            jsi::Function::createFromHostFunction(
                                jsiRuntime,
                                jsi::PropNameID::forAscii(jsiRuntime, "hkdf"),
                                4, rncryptopp::keyderivation::hkdf));
  keyDerivation.setProperty(
      jsiRuntime, "pbkdf12",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pbkdf12"), 4,
          rncryptopp::keyderivation::pbkdf12));
  keyDerivation.setProperty(
      jsiRuntime, "pkcs5_pbkdf1",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf1"), 4,
          rncryptopp::keyderivation::pkcs5_pbkdf1));
  keyDerivation.setProperty(
      jsiRuntime, "pkcs5_pbkdf2",
      jsi::Function::createFromHostFunction(
          jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf2"), 4,
          rncryptopp::keyderivation::pkcs5_pbkdf2));

  /*
  Public-key cryptography
  */

  jsi::Object RSA = jsi::Object(jsiRuntime);
  RSA.setProperty(jsiRuntime, "generateKeyPair",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "generateKeyPair"),
                      1, rncryptopp::rsa::generateKeyPair));
  RSA.setProperty(jsiRuntime, "encrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "encrypt"), 2,
                      rncryptopp::rsa::encrypt));
  RSA.setProperty(jsiRuntime, "decrypt",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "decrypt"), 2,
                      rncryptopp::rsa::decrypt));
  RSA.setProperty(jsiRuntime, "sign",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "sign"),
                      3, rncryptopp::rsa::sign));
  RSA.setProperty(jsiRuntime, "verify",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "verify"), 4,
                      rncryptopp::rsa::verify));
  RSA.setProperty(jsiRuntime, "recover",
                  jsi::Function::createFromHostFunction(
                      jsiRuntime,
                      jsi::PropNameID::forAscii(jsiRuntime, "recover"), 3,
                      rncryptopp::rsa::recover));
  /*
  Utils
  */
  jsi::Object utils = jsi::Object(jsiRuntime);
  utils.setProperty(jsiRuntime, "toBase64",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "toBase64"), 2,
                        rncryptopp::utils::toBase64));
  utils.setProperty(jsiRuntime, "toBase64Url",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "toBase64Url"), 2,
                        rncryptopp::utils::toBase64Url));
  utils.setProperty(jsiRuntime, "toHex",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "toHex"), 2,
                        rncryptopp::utils::toHex));
  utils.setProperty(jsiRuntime, "toUtf8",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "toUtf8"), 2,
                        rncryptopp::utils::toUtf8));
  utils.setProperty(jsiRuntime, "randomBytes",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "randomBytes"), 1,
                        rncryptopp::utils::randomBytes));
  utils.setProperty(jsiRuntime, "stringToBytes",
                    jsi::Function::createFromHostFunction(
                        jsiRuntime,
                        jsi::PropNameID::forAscii(jsiRuntime, "stringToBytes"),
                        2, rncryptopp::utils::stringToBytes));

  /*
  Cryptopp module
  */
  jsi::Object module = jsi::Object(jsiRuntime);
  module.setProperty(jsiRuntime, "AES", std::move(AES));
  module.setProperty(jsiRuntime, "RC6", std::move(RC6));
  module.setProperty(jsiRuntime, "MARS", std::move(MARS));
  module.setProperty(jsiRuntime, "Twofish", std::move(Twofish));
  module.setProperty(jsiRuntime, "Serpent", std::move(Serpent));
  module.setProperty(jsiRuntime, "CAST256", std::move(CAST256));
  module.setProperty(jsiRuntime, "HMAC", std::move(HMAC));
  module.setProperty(jsiRuntime, "CMAC", std::move(CMAC));
  module.setProperty(jsiRuntime, "RSA", std::move(RSA));
  module.setProperty(jsiRuntime, "hashFunctions", std::move(hashFunctions));
  module.setProperty(jsiRuntime, "insecure", std::move(insecure));
  module.setProperty(jsiRuntime, "keyDerivation", std::move(keyDerivation));
  module.setProperty(jsiRuntime, "utils", std::move(utils));

  jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule",
                                  std::move(module));
}
