#include "key-derivation.h"

namespace rncryptopp
{
    // returns: pair of index and hash DIGESTSIZE
    // index is -1 is hash is not valid
    std::pair<int, int> getHashIndexAndSize(std::string &hash)
    {
        if (hash == "SHA1")
            return std::make_pair(0, SHA1::DIGESTSIZE);
        if (hash == "SHA256")
            return std::make_pair(1, SHA256::DIGESTSIZE);
        if (hash == "SHA512")
            return std::make_pair(2, SHA512::DIGESTSIZE);
        if (hash == "SHA3_256")
            return std::make_pair(3, SHA3_256::DIGESTSIZE);
        if (hash == "SHA3_512")
            return std::make_pair(4, SHA3_512::DIGESTSIZE);
        if (hash == "SHAKE128")
            return std::make_pair(5, SHAKE128::DIGESTSIZE);
        if (hash == "SHAKE256")
            return std::make_pair(6, SHAKE256::DIGESTSIZE);
        if (hash == "BLAKE2B")
            return std::make_pair(7, BLAKE2b::DIGESTSIZE);
        if (hash == "BLAKE2S")
            return std::make_pair(8, BLAKE2s::DIGESTSIZE);
        if (hash == "LSH256")
            return std::make_pair(9, LSH256::DIGESTSIZE);
        if (hash == "LSH512")
            return std::make_pair(10, LSH512::DIGESTSIZE);
        if (hash == "SM3")
            return std::make_pair(11, SM3::DIGESTSIZE);
        return std::make_pair(-1, 0);
    }

    // function definition
    template <class H>
    void getHDKF(byte *derived, size_t derivedLen, const byte *secret, size_t secretLen,
                 const byte *salt, size_t saltLen, const byte *info, size_t infoLen,
                 std::string &result)
    {
        HKDF<H> hkdf;
        hkdf.DeriveKey(derived, derivedLen,
                       secret, secretLen,
                       salt, saltLen,
                       info, infoLen);
        std::string s(reinterpret_cast<char const *>(derived), derivedLen);
        hexEncode(&s, &result);
    }

    // Array of function pointers
    void (*HKDFptrs[])(byte *derived, size_t derivedLen,
                       const byte *secret, size_t secretLen,
                       const byte *salt, size_t saltLen,
                       const byte *info, size_t infoLen,
                       std::string &result) =
        {&getHDKF<SHA1>, &getHDKF<SHA256>,
         &getHDKF<SHA512>, &getHDKF<SHA3_256>, &getHDKF<SHA3_512>, &getHDKF<SHAKE128>, &getHDKF<SHAKE256>, &getHDKF<BLAKE2b>,
         &getHDKF<BLAKE2s>, &getHDKF<LSH256>, &getHDKF<LSH512>, &getHDKF<SM3>};

    void hkdf(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string password;
        if (!binaryLikeValueToString(rt, args[0], &password, 0, 0))
            throwJSError(rt, "RNCryptopp: hkdf password in not a string or ArrayBuffer");

        std::string salt;
        if (!binaryLikeValueToString(rt, args[1],
                                     &salt, 0, 0))
            throwJSError(rt, "RNCryptopp: hkdf salt in not a string or ArrayBuffer");

        std::string info;
        if (!binaryLikeValueToString(rt, args[2],
                                     &info, 0, 0))
            throwJSError(rt, "RNCryptopp: hkdf info in not a string or ArrayBuffer");

        std::string hash;
        if (!stringValueToString(rt, args[3], &hash))
            throwJSError(rt, "RNCryptopp: hkdf hash in not a string");

        auto hashType = getHashIndexAndSize(hash);

        if (hashType.first == -1)
        {
            throwJSError(rt, "RNCryptopp: hkdf hash invalid hash value");
            return;
        }

        byte derived[hashType.second];
        HKDFptrs[hashType.first](derived, sizeof(derived),
                                 reinterpret_cast<const byte *>(password.data()), password.size(),
                                 reinterpret_cast<const byte *>(salt.data()), salt.size(),
                                 reinterpret_cast<const byte *>(info.data()), info.size(), result);
    }

    // function definition
    template <class H>
    void getPBKDF12(byte *derived, size_t derivedLen, const byte *secret,
                    size_t secretLen, const byte *salt, size_t saltLen, unsigned int iterations, std::string &result)
    {
        byte unused = 0;
        PKCS12_PBKDF<H> pbkdf;
        pbkdf.DeriveKey(derived, derivedLen, unused,
                        secret, secretLen,
                        salt, saltLen,
                        iterations, 0.0f);
        std::string s(reinterpret_cast<char const *>(derived), derivedLen);
        hexEncode(&s, &result);
    }

    // Array of function pointers
    void (*PKCS12_PBKDFptrs[])(byte *derived, size_t derivedLen,
                               const byte *secret, size_t secretLen,
                               const byte *salt, size_t saltLen,
                               unsigned int iterations,
                               std::string &result) =
        {&getPBKDF12<SHA1>, &getPBKDF12<SHA256>,
         &getPBKDF12<SHA512>, &getPBKDF12<SHA3_256>, &getPBKDF12<SHA3_512>, &getPBKDF12<SHAKE128>, &getPBKDF12<SHAKE256>, &getPBKDF12<BLAKE2b>,
         &getPBKDF12<BLAKE2s>, &getPBKDF12<LSH256>, &getPBKDF12<LSH512>, &getPBKDF12<SM3>};

    void pbkdf12(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string password;
        if (!binaryLikeValueToString(rt, args[0], &password, 0, 0))
            throwJSError(rt, "RNCryptopp: pbkdf12 password in not a string or ArrayBuffer");

        std::string salt;
        if (!binaryLikeValueToString(rt, args[1],
                                     &salt, 0, 0))
            throwJSError(rt, "RNCryptopp: pbkdf12 salt in not a string or ArrayBuffer");

        std::string hash;
        if (!stringValueToString(rt, args[2], &hash))
            throwJSError(rt, "RNCryptopp: pbkdf12 hash in not a string");

        int iterations;
        if (!valueToInt(args[3], &iterations))
            throwJSError(rt, "RNCryptopp: pbkdf12 iterations in not a number");

        auto hashType = getHashIndexAndSize(hash);

        if (hashType.first == -1)
        {
            throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");
            return;
        }

        byte derived[hashType.second];
        PKCS12_PBKDFptrs[hashType.first](derived, sizeof(derived),
                                         reinterpret_cast<const byte *>(password.data()), password.size(),
                                         reinterpret_cast<const byte *>(salt.data()), salt.size(),
                                         iterations, result);
    }

    // function definition
    template <class H>
    void getPKCS5_PBKDF1(byte *derived, size_t derivedLen, const byte *secret,
                         size_t secretLen, const byte *salt, size_t saltLen, unsigned int iterations, std::string &result)
    {
        byte unused = 0;
        PKCS5_PBKDF1<H> pbkdf;
        pbkdf.DeriveKey(derived, derivedLen, unused,
                        secret, secretLen,
                        salt, saltLen,
                        iterations, 0.0f);
        std::string s(reinterpret_cast<char const *>(derived), derivedLen);
        hexEncode(&s, &result);
    }

    // Array of function pointers
    void (*PKCS5_PBKDF1ptrs[])(byte *derived, size_t derivedLen,
                               const byte *secret, size_t secretLen,
                               const byte *salt, size_t saltLen,
                               unsigned int iterations,
                               std::string &result) =
        {&getPKCS5_PBKDF1<SHA1>, &getPKCS5_PBKDF1<SHA256>,
         &getPKCS5_PBKDF1<SHA512>, &getPKCS5_PBKDF1<SHA3_256>, &getPKCS5_PBKDF1<SHA3_512>, &getPKCS5_PBKDF1<SHAKE128>, &getPKCS5_PBKDF1<SHAKE256>, &getPKCS5_PBKDF1<BLAKE2b>,
         &getPKCS5_PBKDF1<BLAKE2s>, &getPKCS5_PBKDF1<LSH256>, &getPKCS5_PBKDF1<LSH512>, &getPKCS5_PBKDF1<SM3>};

    void pkcs5_pbkdf1(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string password;
        if (!binaryLikeValueToString(rt, args[0], &password, 0, 0))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 password in not a string or ArrayBuffer");

        std::string salt;
        if (!binaryLikeValueToString(rt, args[1],
                                     &salt, 0, 0))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 salt in not a string or ArrayBuffer");

        std::string hash;
        if (!stringValueToString(rt, args[2], &hash))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash in not a string");

        int iterations;
        if (!valueToInt(args[3], &iterations))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 iterations in not a number");

        auto hashType = getHashIndexAndSize(hash);

        if (hashType.first == -1)
        {
            throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");
            return;
        }

        byte derived[hashType.second];
        PKCS5_PBKDF1ptrs[hashType.first](derived, sizeof(derived),
                                         reinterpret_cast<const byte *>(password.data()), password.size(),
                                         reinterpret_cast<const byte *>(salt.data()), salt.size(),
                                         iterations, result);
    }

    // function definition
    template <class H>
    void getPKCS5_PBKDF2_HMAC(byte *derived, size_t derivedLen, const byte *secret,
                              size_t secretLen, const byte *salt, size_t saltLen, unsigned int iterations, std::string &result)
    {
        byte unused = 0;
        PKCS5_PBKDF2_HMAC<H> pbkdf;
        pbkdf.DeriveKey(derived, derivedLen, unused,
                        secret, secretLen,
                        salt, saltLen,
                        iterations, 0.0f);
        std::string s(reinterpret_cast<char const *>(derived), derivedLen);
        hexEncode(&s, &result);
    }

    // Array of function pointers
    void (*PKCS5_PBKDF2_HMACptrs[])(byte *derived, size_t derivedLen,
                                    const byte *secret, size_t secretLen,
                                    const byte *salt, size_t saltLen,
                                    unsigned int iterations,
                                    std::string &result) =
        {&getPKCS5_PBKDF2_HMAC<SHA1>, &getPKCS5_PBKDF2_HMAC<SHA256>,
         &getPKCS5_PBKDF2_HMAC<SHA512>, &getPKCS5_PBKDF2_HMAC<SHA3_256>, &getPKCS5_PBKDF2_HMAC<SHA3_512>, &getPKCS5_PBKDF2_HMAC<SHAKE128>, &getPKCS5_PBKDF2_HMAC<SHAKE256>, &getPKCS5_PBKDF2_HMAC<BLAKE2b>,
         &getPKCS5_PBKDF2_HMAC<BLAKE2s>, &getPKCS5_PBKDF2_HMAC<LSH256>, &getPKCS5_PBKDF2_HMAC<LSH512>, &getPKCS5_PBKDF2_HMAC<SM3>};

    void pkcs5_pbkdf2(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string password;
        if (!binaryLikeValueToString(rt, args[0], &password, 0, 0))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 password in not a string or ArrayBuffer");

        std::string salt;
        if (!binaryLikeValueToString(rt, args[1],
                                     &salt, 0, 0))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 salt in not a string or ArrayBuffer");

        std::string hash;
        if (!stringValueToString(rt, args[2], &hash))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash in not a string");

        int iterations;
        if (!valueToInt(args[3], &iterations))
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 iterations in not a number");

        auto hashType = getHashIndexAndSize(hash);

        if (hashType.first == -1)
        {
            throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");
            return;
        }

        byte derived[hashType.second];
        PKCS5_PBKDF2_HMACptrs[hashType.first](derived, sizeof(derived),
                                              reinterpret_cast<const byte *>(password.data()), password.size(),
                                              reinterpret_cast<const byte *>(salt.data()), salt.size(),
                                              iterations, result);
    }
}
