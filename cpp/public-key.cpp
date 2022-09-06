#include "public-key.h"

#define PUT_MESSAGE 2
#define THROW_EXCEPTION 16

namespace rncryptopp::rsa {
RSAKeyPair generateKeyPair(jsi::Runtime &rt, CppArgs *args) {
  if (args->size() != 3)
    throwJSError(rt,
                 "RNCryptopp: RSA generateKeyPair invalid number of arguments");

  if (!isDataInteger(args->at(1)))
    throwJSError(rt, "RNCryptopp: RSA generateKeyPair size is not a number");

  if (!isDataInteger(args->at(2)))
    throwJSError(
        rt,
        "RNCryptopp: RSA generateKeyPair public_e is not a number, use 65537");

  int size = args->at(1).doubleOrIntValue;
  int public_e = args->at(2).doubleOrIntValue;

  // Generate Parameters
  AutoSeededRandomPool rng;
  InvertibleRSAFunction key_params;
  key_params.Initialize(rng, size, public_e);

  // Create Keys
  CryptoPP::RSA::PrivateKey privateKey(key_params);
  CryptoPP::RSA::PublicKey publicKey(key_params);

  const Integer &n = key_params.GetModulus();
  std::stringstream n_stream;
  n_stream << n;

  const Integer &p = key_params.GetPrime1();
  std::stringstream p_stream;
  p_stream << p;

  const Integer &q = key_params.GetPrime2();
  std::stringstream q_stream;
  q_stream << q;

  const Integer &d = key_params.GetPrivateExponent();
  std::stringstream d_stream;
  d_stream << d;

  const Integer &e = key_params.GetPublicExponent();
  std::stringstream e_stream;
  e_stream << e;

  std::string pem_public;
  StringSink pem_public_sink(pem_public);
  PEM_Save(pem_public_sink, publicKey);

  std::string pem_private;
  StringSink pem_private_sink(pem_private);
  PEM_Save(pem_private_sink, privateKey);

  return RSAKeyPair{
      .n = n_stream.str(),
      .p = p_stream.str(),
      .q = q_stream.str(),
      .d = d_stream.str(),
      .e = e_stream.str(),
      .public_key = pem_public,
      .private_key = pem_private,
  };
}

void encrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 4)
    throwJSError(rt, "RNCryptopp: RSA encrypt invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt, "RNCryptopp: RSA encrypt data is not a string");

  if (!isDataString(args->at(2)))
    throwJSError(rt, "RNCryptopp: RSA encrypt publicKey is not a string");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: RSA encrypt scheme is not a string");

  std::string data = args->at(1).stringValue;
  std::string publicKeyString = args->at(2).stringValue;
  std::string encryptScheme = args->at(3).stringValue;

  StringSource PKeyStringSource(publicKeyString, true);
  CryptoPP::RSA::PublicKey publicKey;
  PEM_Load(PKeyStringSource, publicKey);

  AutoSeededRandomPool rng;

  if (encryptScheme == "OAEP_SHA1") {
    RSAES<OAEP<SHA1>>::Encryptor e(publicKey);
    StringSource(data, true,
                 new PK_EncryptorFilter(rng, e, new StringSink(*target)));
  } else if (encryptScheme == "OAEP_SHA256") {
    RSAES<OAEP<SHA256>>::Encryptor e(publicKey);
    StringSource(data, true,
                 new PK_EncryptorFilter(rng, e, new StringSink(*target)));
  } else if (encryptScheme == "PKCS1v15") {
    RSAES<PKCS1v15>::Encryptor e(publicKey);
    StringSource(data, true,
                 new PK_EncryptorFilter(rng, e, new StringSink(*target)));
  } else {
    throwJSError(rt, "RNCryptopp: RSA encrypt invalid scheme");
  }

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_BASE64;
}

void decrypt(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType) {
  if (args->size() != 4)
    throwJSError(rt, "RNCryptopp: RSA decrypt invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt, "RNCryptopp: RSA decrypt data is not a string");

  if (!isDataString(args->at(2)))
    throwJSError(rt, "RNCryptopp: RSA decrypt privateKey is not a string");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: RSA decrypt scheme is not a string");

  std::string privateKeyString = args->at(2).stringValue;
  std::string encryptScheme = args->at(3).stringValue;
  std::string data;
  decodeJSIString(args->at(1), &data, ENCODING_BASE64);

  StringSource PKeyStringSource(privateKeyString, true);
  CryptoPP::RSA::PrivateKey privateKey;
  PEM_Load(PKeyStringSource, privateKey);

  AutoSeededRandomPool rng;
  try {
    if (encryptScheme == "OAEP_SHA1") {
      RSAES<OAEP<SHA1>>::Decryptor e(privateKey);
      StringSource(data, true,
                   new PK_DecryptorFilter(rng, e, new StringSink(*target)));
    } else if (encryptScheme == "OAEP_SHA256") {
      RSAES<OAEP<SHA256>>::Decryptor e(privateKey);
      StringSource ss1(data, true,
                       new PK_DecryptorFilter(rng, e, new StringSink(*target)));
    } else if (encryptScheme == "PKCS1v15") {
      RSAES<PKCS1v15>::Decryptor e(privateKey);
      StringSource(data, true,
                   new PK_DecryptorFilter(rng, e, new StringSink(*target)));
    } else {
      throwJSError(rt, "RNCryptopp: RSA decrypt invalid scheme");
    }
  } catch (const std::exception &e) {
    throwJSError(rt, "RNCryptopp: RSA decryption failed");
  }

  *targetType = args->at(1).dataType;
}

template <class SCHEME>
void exec_sign(std::string *data, CryptoPP::RSA::PrivateKey *privateKey,
               std::string *result, bool putMessage = false) {
  AutoSeededRandomPool rng;
  typename SCHEME::Signer signer(*privateKey);

  StringSource(
      *data, true,
      new SignerFilter(rng, signer, new StringSink(*result), putMessage));
}

void sign(jsi::Runtime &rt, CppArgs *args, std::string *target,
          QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 4)
    throwJSError(rt, "RNCryptopp: RSA sign invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt, "RNCryptopp: RSA sign data is not a string");

  if (!isDataString(args->at(2)))
    throwJSError(rt, "RNCryptopp: RSA sign privateKey is not a string");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: RSA decrypt scheme is not a string");

  std::string data = args->at(1).stringValue;
  std::string privateKeyString = args->at(2).stringValue;
  std::string signScheme = args->at(3).stringValue;

  StringSource PKeyStringSource(privateKeyString, true);
  CryptoPP::RSA::PrivateKey privateKey;
  PEM_Load(PKeyStringSource, privateKey);

  if (signScheme == "PKCS1v15_SHA1")
    exec_sign<RSASS<PKCS1v15, SHA1>>(&data, &privateKey, target);
  else if (signScheme == "PKCS1v15_SHA256")
    exec_sign<RSASS<PKCS1v15, SHA256>>(&data, &privateKey, target);
  // PSSR
  else if (signScheme == "PSSR_SHA1")
    exec_sign<RSASS<PSSR, SHA1>>(&data, &privateKey, target, true);
  else if (signScheme == "PSSR_SHA256")
    exec_sign<RSASS<PSSR, SHA256>>(&data, &privateKey, target, true);
  else if (signScheme == "PSSR_Whirlpool")
    exec_sign<RSASS<PSSR, Whirlpool>>(&data, &privateKey, target, true);
  // PSS
  else if (signScheme == "PSS_SHA1")
    exec_sign<RSASS<PSS, SHA1>>(&data, &privateKey, target);
  else if (signScheme == "PSS_SHA256")
    exec_sign<RSASS<PSS, SHA256>>(&data, &privateKey, target);
  else if (signScheme == "PSS_Whirlpool")
    exec_sign<RSASS<PSS, Whirlpool>>(&data, &privateKey, target);
  else
    throwJSError(rt, "RNCryptopp: RSA sign invalid scheme");

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_BASE64;
}

void verify(jsi::Runtime &rt, CppArgs *args, bool *target,
            QuickDataType *targetType) {
  if (args->size() != 5)
    throwJSError(rt, "RNCryptopp: RSA verify invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(rt, "RNCryptopp: RSA verify data is not a string");

  if (!isDataString(args->at(2)))
    throwJSError(rt, "RNCryptopp: RSA verify publicKey is not a string");

  if (!isDataString(args->at(3)))
    throwJSError(rt, "RNCryptopp: RSA verify signature scheme is not a string");

  if (!isDataString(args->at(4)))
    throwJSError(rt, "RNCryptopp: RSA verify signature is not a string");

  std::string data = args->at(1).stringValue;
  std::string publicKeyString = args->at(2).stringValue;
  std::string signScheme = args->at(3).stringValue;
  std::string signature;
  decodeJSIString(args->at(4), &signature, ENCODING_BASE64);

  StringSource PKeyStringSource(publicKeyString, true);
  CryptoPP::RSA::PublicKey publicKey;
  PEM_Load(PKeyStringSource, publicKey);

  bool result = false;
  if (signScheme == "PKCS1v15_SHA1") {
    RSASS<PKCS1v15, SHA1>::Verifier verifier(publicKey);
    result = verifier.VerifyMessage((const byte *)data.data(), data.size(),
                                    (const byte *)signature.data(),
                                    signature.size());
  } else if (signScheme == "PKCS1v15_SHA256") {
    RSASS<PKCS1v15, SHA256>::Verifier verifier(publicKey);
    result = verifier.VerifyMessage((const byte *)data.data(), data.size(),
                                    (const byte *)signature.data(),
                                    signature.size());
  }
  // PSS
  else if (signScheme == "PSS_SHA1") {
    RSASS<PSS, SHA1>::Verifier verifier(publicKey);
    result = verifier.VerifyMessage((const byte *)data.data(), data.size(),
                                    (const byte *)signature.data(),
                                    signature.size());
  } else if (signScheme == "PSS_SHA256") {
    RSASS<PSS, SHA256>::Verifier verifier(publicKey);
    result = verifier.VerifyMessage((const byte *)data.data(), data.size(),
                                    (const byte *)signature.data(),
                                    signature.size());
  } else if (signScheme == "PSS_Whirlpool") {
    RSASS<PSS, Whirlpool>::Verifier verifier(publicKey);
    result = verifier.VerifyMessage((const byte *)data.data(), data.size(),
                                    (const byte *)signature.data(),
                                    signature.size());
  } else
    throwJSError(rt, "RNCryptopp: RSA verify invalid scheme");

  *target = result;
  *targetType = jsiHelper::BOOLEAN;
}

void recover(jsi::Runtime &rt, CppArgs *args, std::string *target,
             QuickDataType *targetType, StringEncoding *targetEncoding) {
  if (args->size() != 4)
    throwJSError(rt, "RNCryptopp: RSA recover invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throwJSError(
        rt, "RNCryptopp: RSA recover signature is not a string or ArrayBuffer");

  if (!isDataString(args->at(2)))
    throwJSError(rt, "RNCryptopp: RSA recover publicKey is not a string");

  if (!isDataString(args->at(3)))
    throwJSError(rt,
                 "RNCryptopp: RSA recover signature scheme is not a string");

  std::string publicKeyString = args->at(2).stringValue;
  std::string signScheme = args->at(3).stringValue;
  std::string signature;
  decodeJSIString(args->at(1), &signature, ENCODING_BASE64);

  StringSource PKeyStringSource(publicKeyString, true);
  CryptoPP::RSA::PublicKey publicKey;
  PEM_Load(PKeyStringSource, publicKey);

  // try catch
  try {
    if (signScheme == "PSSR_SHA1") {
      RSASS<PSSR, SHA1>::Verifier verifier(publicKey);
      StringSource(
          signature, true,
          new SignatureVerificationFilter(verifier, new StringSink(*target),
                                          THROW_EXCEPTION | PUT_MESSAGE));
    } else if (signScheme == "PSSR_SHA256") {
      RSASS<PSSR, SHA256>::Verifier verifier(publicKey);
      StringSource(
          signature, true,
          new SignatureVerificationFilter(verifier, new StringSink(*target),
                                          THROW_EXCEPTION | PUT_MESSAGE));
    } else if (signScheme == "PSSR_Whirlpool") {
      RSASS<PSSR, Whirlpool>::Verifier verifier(publicKey);
      StringSource(
          signature, true,
          new SignatureVerificationFilter(verifier, new StringSink(*target),
                                          THROW_EXCEPTION | PUT_MESSAGE));
    } else {
      // Will not be caught by std::exception &e bellow
      throwJSError(rt, "RNCryptopp: RSA recover invalid scheme");
    }
  } catch (const std::exception &e) {
    throwJSError(rt, "RNCryptopp: RSA signatures do not match");
  }

  *targetType = args->at(1).dataType;
  *targetEncoding = ENCODING_UTF8;
}
} // namespace rncryptopp::rsa
