#include "public-key.h"

namespace rncryptopp::RSA
{
    void generateKeyPair(jsi::Runtime &rt, const jsi::Value *args, jsi::Object &result)
    {
        int size;
        if (!valueToInt(args[0], &size))
            throwJSError(rt,
                         "RNCryptopp: RSA generateKeyPair size is not a number");

        // Generate Parameters
        AutoSeededRandomPool rng;
        InvertibleRSAFunction key_params;
        key_params.GenerateRandomWithKeySize(rng, size);

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

        jsi::Object params = jsi::Object(rt);
        params.setProperty(rt, "n", n_stream.str());
        params.setProperty(rt, "p", p_stream.str());
        params.setProperty(rt, "q", q_stream.str());
        params.setProperty(rt, "d", d_stream.str());
        params.setProperty(rt, "e", e_stream.str());

        result.setProperty(rt, "public", pem_public);
        result.setProperty(rt, "private", pem_private);
        result.setProperty(rt, "parameters", params);
    }

    void encrypt(jsi::Runtime &rt, const jsi::Value *args, std::string *result)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: RSA encrypt data in not a string");

        std::string publicKeyString;
        if (!stringValueToString(rt, args[1], &publicKeyString))
            throwJSError(rt, "RNCryptopp: RSA encrypt publicKey in not a string");

        StringSource PKeyStringSource(publicKeyString, true);
        CryptoPP::RSA::PublicKey publicKey;
        PEM_Load(PKeyStringSource, publicKey);

        AutoSeededRandomPool rng;
        RSAES_OAEP_SHA_Encryptor e(publicKey);

        StringSource ss1(data,
                         true,
                         new PK_EncryptorFilter(rng,
                                                e,
                                                new Base64Encoder(new StringSink(*result))));
    }

    void decrypt(jsi::Runtime &rt, const jsi::Value *args, std::string *result)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 2, 2))
            throwJSError(rt, "RNCryptopp: RSA decrypt data in not a string");

        std::string privateKeyString;
        if (!stringValueToString(rt, args[1], &privateKeyString))
            throwJSError(rt, "RNCryptopp: RSA decrypt privateKey in not a string");

        StringSource PKeyStringSource(privateKeyString, true);
        CryptoPP::RSA::PrivateKey privateKey;
        PEM_Load(PKeyStringSource, privateKey);

        AutoSeededRandomPool rng;
        RSAES_OAEP_SHA_Decryptor d(privateKey);

        StringSource ss2(data,
                         true,
                         new PK_DecryptorFilter(rng,
                                                d,
                                                new StringSink(*result)));
    }

    void sign(jsi::Runtime &rt, const jsi::Value *args, std::string *result)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: RSA sign data in not a string");

        std::string privateKeyString;
        if (!stringValueToString(rt, args[1], &privateKeyString))
            throwJSError(rt, "RNCryptopp: RSA sign privateKey in not a string");

        StringSource PKeyStringSource(privateKeyString, true);
        CryptoPP::RSA::PrivateKey privateKey;
        PEM_Load(PKeyStringSource, privateKey);

        AutoSeededRandomPool rng;
        RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

        StringSource ss1(data,
                         true,
                         new SignerFilter(rng,
                                          signer,
                                          new Base64Encoder(new StringSink(*result))));
    }

    void verify(jsi::Runtime &rt, const jsi::Value *args, bool *result)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: RSA verify data in not a string");

        std::string publicKeyString;
        if (!stringValueToString(rt, args[1], &publicKeyString))
            throwJSError(rt, "RNCryptopp: RSA verify publicKey in not a string");

        std::string signature;
        if (!binaryLikeValueToString(rt, args[2], &signature, 2, 2))
            throwJSError(rt, "RNCryptopp: RSA verify signature in not a string");


        StringSource PKeyStringSource(publicKeyString, true);
        CryptoPP::RSA::PublicKey publicKey;
        PEM_Load(PKeyStringSource, publicKey);

        RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

        // Verify
        *result = verifier.VerifyMessage((const byte*)data.data(),
                                         data.size(), (const byte*)signature.data(), signature.size());
    }
}
