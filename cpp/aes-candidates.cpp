#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "aes-candidates.h"

namespace rncryptopp {

    void aes_encrypt(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string data;
        if (!valueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: Data in not a string");

        std::string key;
        if (!valueToString(rt, args[1], &key))
            throwJSError(rt, "RNCryptopp: Size in not a string");

        std::string iv;
        if (!valueToString(rt, args[2], &iv))
            throwJSError(rt, "RNCryptopp: Size in not a string");

        std::string mode;
        if (!valueToString(rt, args[3], &mode))
            throwJSError(rt, "RNCryptopp: Mode in not a string");


        std::string dec_key;
        hexDecode(&key, &dec_key);

        std::string dec_iv;
        hexDecode(&iv, &dec_iv);

        if (mode == "cbc") {
            CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
            e.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource(
                    data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            e,
                            new CryptoPP::Base64Encoder(
                                    new CryptoPP::StringSink(result)))
            );
        } else if (mode == "cfb") {
            CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption e;
            e.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource(
                    data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            e,
                            new CryptoPP::Base64Encoder(
                                    new CryptoPP::StringSink(result))
                           )
            );
        } else if (mode == "ecb") {
            CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption e;
            e.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource(
                    data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            e,
                            new CryptoPP::Base64Encoder(
                                    new CryptoPP::StringSink(result)))
            );
        } else if (mode == "ofb") {
            CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption e;
            e.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource(
                    data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            e,
                            new CryptoPP::Base64Encoder(
                                    new CryptoPP::StringSink(result)))
            );
        } else if (mode == "ctr") {
            CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption e;
            e.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource(
                    data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            e,
                            new CryptoPP::Base64Encoder(
                                    new CryptoPP::StringSink(result)))
            );
        } else {
            throwJSError(rt, "RNCryptopp: Invalid mode");
        }
    }


    void aes_decrypt(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string data;
        if (!valueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: Data in not a string");

        std::string key;
        if (!valueToString(rt, args[1], &key))
            throwJSError(rt, "RNCryptopp: Size in not a string");

        std::string iv;
        if (!valueToString(rt, args[2], &iv))
            throwJSError(rt, "RNCryptopp: Size in not a string");

        std::string mode;
        if (!valueToString(rt, args[3], &mode))
            throwJSError(rt, "RNCryptopp: Mode in not a string");

        std::string dec_data;
        hexDecode(&data, &dec_data);

        std::string dec_key;
        hexDecode(&key, &dec_key);

        std::string dec_iv;
        base64Decode(&iv, &dec_iv);


        if (mode == "cbc") {
            CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
            d.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource s(
                    dec_data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            d,
                            new CryptoPP::StringSink(result)
                    )
            );
        } else if (mode == "cfb") {
            CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption d;
            d.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource s(
                    dec_data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            d,
                            new CryptoPP::StringSink(result)
                    )
            );
        } else if (mode == "ecb") {
            CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption d;
            d.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource s(
                    dec_data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            d,
                            new CryptoPP::StringSink(result)
                    )
            );
        } else if (mode == "ofb") {
            CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption d;
            d.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource s(
                    dec_data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            d,
                            new CryptoPP::StringSink(result)
                    )
            );
        } else if (mode == "ctr") {
            CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption d;
            d.SetKeyWithIV((const CryptoPP::byte *) dec_key.data(), dec_key.size(),
                           (const CryptoPP::byte *) dec_iv.data(), dec_iv.size());
            CryptoPP::StringSource s(
                    dec_data,
                    true,
                    new CryptoPP::StreamTransformationFilter(
                            d,
                            new CryptoPP::StringSink(result)
                    )
            );
        } else {
            throwJSError(rt, "RNCryptopp: Invalid mode");
        }
    }
}

#pragma clang diagnostic pop
