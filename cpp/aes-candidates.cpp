#include "aes-candidates.h"

namespace rncryptopp
{

    void aes_encrypt(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!stringValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: aes_encrypt data in not a string");

        std::string key;
        if (!binaryLikeValueToString(rt, args[1], &key, 1, 0))
            throwJSError(rt, "RNCryptopp: aes_encrypt iv in not a string or ArrayBuffer");

        std::string iv;
        if (!binaryLikeValueToString(rt, args[2], &iv, 1, 0))
            throwJSError(rt, "RNCryptopp: aes_encrypt iv in not a string or ArrayBuffer");

        std::string mode;
        if (!stringValueToString(rt, args[3], &mode))
            throwJSError(rt, "RNCryptopp: aes_encrypt mode in not a string");

        if (mode == "cbc")
        {
            CBC_Mode<AES>::Encryption e;
            e.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource(
                data,
                true,
                new StreamTransformationFilter(
                    e,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "cfb")
        {
            CFB_Mode<AES>::Encryption e;
            e.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource(
                data,
                true,
                new StreamTransformationFilter(
                    e,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ecb")
        {
            ECB_Mode<AES>::Encryption e;
            e.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource(
                data,
                true,
                new StreamTransformationFilter(
                    e,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ofb")
        {
            OFB_Mode<AES>::Encryption e;
            e.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource(
                data,
                true,
                new StreamTransformationFilter(
                    e,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ctr")
        {
            CTR_Mode<AES>::Encryption e;
            e.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource(
                data,
                true,
                new StreamTransformationFilter(
                    e,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else
        {
            throwJSError(rt, "RNCryptopp: Invalid mode");
        }
    }

    void aes_decrypt(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!stringValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: aes_decrypt data in not a string");

        std::string key;
        if (!binaryLikeValueToString(rt, args[1], &key, 0 ,0))
            throwJSError(rt, "RNCryptopp: aes_decrypt key in not a string");

        std::string iv;
        if (!binaryLikeValueToString(rt, args[2], &iv, 0,0))
            throwJSError(rt, "RNCryptopp: aes_decrypt iv in not a string");

        std::string mode;
        if (!stringValueToString(rt, args[3], &mode))
            throwJSError(rt, "RNCryptopp: aes_decrypt mode in not a string");

        std::string dec_data;
        base64Decode(&data, &dec_data);

        if (mode == "cbc")
        {
            CBC_Mode<AES>::Decryption d;
            d.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource s(
                dec_data,
                true,
                new StreamTransformationFilter(
                    d,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "cfb")
        {
            CFB_Mode<AES>::Decryption d;
            d.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource s(
                dec_data,
                true,
                new StreamTransformationFilter(
                    d,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ecb")
        {
            ECB_Mode<AES>::Decryption d;
            d.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource s(
                dec_data,
                true,
                new StreamTransformationFilter(
                    d,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ofb")
        {
            OFB_Mode<AES>::Decryption d;
            d.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource s(
                dec_data,
                true,
                new StreamTransformationFilter(
                    d,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else if (mode == "ctr")
        {
            CTR_Mode<AES>::Decryption d;
            d.SetKeyWithIV((const byte *)key.data(), key.size(),
                           (const byte *)iv.data(), iv.size());
            StringSource s(
                dec_data,
                true,
                new StreamTransformationFilter(
                    d,
                    new Base64Encoder(
                        new StringSink(result))));
        }
        else
        {
            throwJSError(rt, "RNCryptopp: Invalid mode");
        }
    }
}

#pragma clang diagnostic pop
