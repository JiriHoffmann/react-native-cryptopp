#include "key-derivation.h"

// TODO: Cleanup if statements
namespace rncryptopp {

    void hkdf(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
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

        byte derived[hash == "SHA1" ? SHA1::DIGESTSIZE :
                     hash == "SHA256" ? SHA256::DIGESTSIZE :
                     hash == "SHA512" ? SHA512::DIGESTSIZE :
                     hash == "SHA3_256" ? SHA3_224::DIGESTSIZE :
                     hash == "SHA3_512" ? SHA3_512::DIGESTSIZE :
                     hash == "BLAKE2b" ? BLAKE2b::DIGESTSIZE :
                     hash == "BLAKE2s" ? BLAKE2s::DIGESTSIZE :
                     0];


        if (sizeof(derived) == 0)
            throwJSError(rt, "RNCryptopp: hkdf hash invalid hash value");


        if (hash == "SHA1") {
            HKDF<SHA1> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        } else if (hash == "SHA256") {
            HKDF<SHA256> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        } else if (hash == "SHA512") {
            HKDF<SHA512> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        } else if (hash == "SHA3_256") {
            HKDF<SHA3_256> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        } else if (hash == "SHA3_512") {
            HKDF<SHA3_512> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        }
        else if (hash == "BLAKE2b") {
            HKDF<BLAKE2b> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        }
        else if (hash == "BLAKE2b") {
            HKDF<BLAKE2s> hkdf;
            hkdf.DeriveKey(derived, sizeof(derived),
                           reinterpret_cast<const byte *>(password.data()), password.size(),
                           reinterpret_cast<const byte *>(salt.data()), salt.size(),
                           reinterpret_cast<const byte *>(info.data()), info.size()
            );
        }

        std::string s( reinterpret_cast<char const*>(derived), sizeof(derived) );
        hexEncode(&s, &result);
    }

    void pbkdf12(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
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


        byte unused = 0;
        byte derived[hash == "SHA1" ? SHA1::DIGESTSIZE :
                     hash == "SHA256" ? SHA256::DIGESTSIZE :
                     hash == "SHA512" ? SHA512::DIGESTSIZE :
                     hash == "SHA3_256" ? SHA3_224::DIGESTSIZE :
                     hash == "SHA3_512" ? SHA3_512::DIGESTSIZE :
                     hash == "BLAKE2b" ? BLAKE2b::DIGESTSIZE :
                     hash == "BLAKE2s" ? BLAKE2s::DIGESTSIZE :
                     0];

        if (sizeof(derived) == 0)
            throwJSError(rt, "RNCryptopp: pbkdf12 hash invalid hash value");


        if (hash == "SHA1") {
            PKCS12_PBKDF<SHA1> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA256") {
            PKCS12_PBKDF<SHA256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA512") {
            PKCS12_PBKDF<SHA512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_256") {
            PKCS12_PBKDF<SHA3_256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_512") {
            PKCS12_PBKDF<SHA3_512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), 0.0f,
                            0.0f);
        }else if (hash == "BLAKE2b") {
            PKCS12_PBKDF<BLAKE2b> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "BLAKE2s") {
            PKCS12_PBKDF<BLAKE2s> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), 0.0f,
                            0.0f);
        }

        std::string s( reinterpret_cast<char const*>(derived), sizeof(derived) );
        hexEncode(&s, &result);
    }

    void pkcs5_pbkdf1(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
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


        byte unused = 0;
        byte derived[hash == "SHA1" ? SHA1::DIGESTSIZE :
                     hash == "SHA256" ? SHA256::DIGESTSIZE :
                     hash == "SHA512" ? SHA512::DIGESTSIZE :
                     hash == "SHA3_256" ? SHA3_224::DIGESTSIZE :
                     hash == "SHA3_512" ? SHA3_512::DIGESTSIZE :
                     hash == "BLAKE2b" ? BLAKE2b::DIGESTSIZE :
                     hash == "BLAKE2s" ? BLAKE2s::DIGESTSIZE :
                     0];

        if (sizeof(derived) == 0)
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf1 hash invalid hash value");

        int iters = 0;

        if (hash == "SHA1") {
            PKCS5_PBKDF1<SHA1> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA256") {
            PKCS5_PBKDF1<SHA256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA512") {
            PKCS5_PBKDF1<SHA512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_256") {
            PKCS5_PBKDF1<SHA3_256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_512") {
            PKCS5_PBKDF1<SHA3_512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        }  else if (hash == "BLAKE2s") {
            PKCS5_PBKDF1<BLAKE2s> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "BLAKE2b") {
            PKCS5_PBKDF1<BLAKE2b> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        }

        std::string s( reinterpret_cast<char const*>(derived), sizeof(derived) );
        hexEncode(&s, &result);

    }

    void pkcs5_pbkdf2(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
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

        byte unused = 0;
        byte derived[hash == "SHA1" ? SHA1::DIGESTSIZE :
                     hash == "SHA256" ? SHA256::DIGESTSIZE :
                     hash == "SHA512" ? SHA512::DIGESTSIZE :
                     hash == "SHA3_256" ? SHA3_224::DIGESTSIZE :
                     hash == "SHA3_512" ? SHA3_512::DIGESTSIZE :
                     0];

        if (sizeof(derived) == 0)
            throwJSError(rt, "RNCryptopp: pkcs5_pbkdf2 hash invalid hash value");


        if (hash == "SHA1") {
            PKCS5_PBKDF2_HMAC<SHA1> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA256") {
            PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA512") {
            PKCS5_PBKDF2_HMAC<SHA512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_256") {
            PKCS5_PBKDF2_HMAC<SHA3_256> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "SHA3_512") {
            PKCS5_PBKDF2_HMAC<SHA3_512> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "BLAKE2s") {
            PKCS5_PBKDF2_HMAC<BLAKE2s> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        } else if (hash == "BLAKE2b") {
            PKCS5_PBKDF2_HMAC<BLAKE2b> pbkdf;
            pbkdf.DeriveKey(derived, sizeof(derived), unused,
                            reinterpret_cast<const byte *>(password.data()), password.size(),
                            reinterpret_cast<const byte *>(salt.data()), salt.size(), iterations,
                            0.0f);
        }
        std::string s( reinterpret_cast<char const*>(derived), sizeof(derived) );
        hexEncode(&s, &result);
    }
}



