#include "aes-candidates.h"

namespace rncryptopp
{
    int getModeIndex(std::string &mode)
    {
        if (mode == "ecb")
            return 0;
        if (mode == "cbc")
            return 1;
        if (mode == "cbc_cts")
            return 2;
        if (mode == "cfb")
            return 3;
        if (mode == "ofb")
            return 4;
        if (mode == "ctr")
            return 5;
        if (mode == "xts")
            return 6;
        return -1;
    }

    // function definition
    template <class CIPHER>
    void exec_AES(const byte *key, size_t length, const byte *iv, size_t ivLength, std::string &data,
                  std::string &result, int encrypt)
    {
        if (encrypt == 1)
        {
            typename CIPHER::Encryption e;
            e.SetKeyWithIV(key, length, iv, ivLength);
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
            typename CIPHER::Decryption d;
            d.SetKeyWithIV(key, length, iv, ivLength);
            StringSource s(
                data,
                true,
                new StreamTransformationFilter(
                    d,
                        new StringSink(result)));
        }
    }

    // Array of function pointers
    void (*modePtrs[])(const byte *key, size_t length, const byte *iv, size_t ivLength,
                       std::string &data, std::string &result, int encrypt) =
        {&exec_AES<ECB_Mode<AES>>, &exec_AES<CBC_Mode<AES>>, &exec_AES<CBC_CTS_Mode<AES>>,
         &exec_AES<CFB_Mode<AES>>, &exec_AES<OFB_Mode<AES>>, &exec_AES<CTR_Mode<AES>>,
         &exec_AES<XTS_Mode<AES>>};

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

        auto modeIndex = getModeIndex(mode);

        if (modeIndex == -1)
        {
            throwJSError(rt, "RNCryptopp: aes_encrypt mode is not a invalid mode value");
            return;
        }

        modePtrs[modeIndex]((const byte *)key.data(), key.size(),
                            (const byte *)iv.data(), iv.size(), data, result, 1);
    }

    void aes_decrypt(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!stringValueToString(rt, args[0], &data))
            throwJSError(rt, "RNCryptopp: aes_decrypt data in not a string");

        std::string key;
        if (!binaryLikeValueToString(rt, args[1], &key, 0, 0))
            throwJSError(rt, "RNCryptopp: aes_decrypt key in not a string");

        std::string iv;
        if (!binaryLikeValueToString(rt, args[2], &iv, 0, 0))
            throwJSError(rt, "RNCryptopp: aes_decrypt iv in not a string");

        std::string mode;
        if (!stringValueToString(rt, args[3], &mode))
            throwJSError(rt, "RNCryptopp: aes_decrypt mode in not a string");

        std::string dec_data;
        base64Decode(&data, &dec_data);

        auto modeIndex = getModeIndex(mode);

        if (modeIndex == -1)
        {
            throwJSError(rt, "RNCryptopp: aes_decrypt mode is not a invalid mode value");
            return;
        }

        modePtrs[modeIndex]((const byte *)key.data(), key.size(),
                            (const byte *)iv.data(), iv.size(), dec_data, result, 0);
    }
}
