#include <iostream>
#include <sstream>

#include "react-native-cryptopp.h"

void rncryptopp_install(jsi::Runtime &jsiRuntime)
{
        /*
        Hash functions
        */
        auto sha1 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "sha1"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::sha1(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });
        auto sha2 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "sha2"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::sha2(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });
        auto sha3 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "sha3"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::sha3(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        jsi::Object SHA = jsi::Object(jsiRuntime);
        SHA.setProperty(jsiRuntime, "sha1", std::move(sha1));
        SHA.setProperty(jsiRuntime, "sha2", std::move(sha2));
        SHA.setProperty(jsiRuntime, "sha3", std::move(sha3));

        /*
        AES and AES candidates
        */
        auto aes_encrypt = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "aes_encrypt"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::aes_encrypt(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });
        auto aes_decrypt = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "aes_decrypt"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::aes_decrypt(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        jsi::Object AES = jsi::Object(jsiRuntime);
        AES.setProperty(jsiRuntime, "encrypt", std::move(aes_encrypt));
        AES.setProperty(jsiRuntime, "decrypt", std::move(aes_decrypt));

        /*
        Insecure
        */
        auto md2 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "md2"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::md2(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });
        auto md4 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "md4"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::md4(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });
        auto md5 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "md5"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::md5(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        jsi::Object insecure = jsi::Object(jsiRuntime);
        insecure.setProperty(jsiRuntime, "md2", std::move(md2));
        insecure.setProperty(jsiRuntime, "md4", std::move(md4));
        insecure.setProperty(jsiRuntime, "md5", std::move(md5));

        /*
        Utils
        */
       auto randomBytesNative = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "randomBytesNative"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::randomBytesNative(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto hexToBase64 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "hexToBase64"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::hexToBase64(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto base64ToHex = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "base64ToHex"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::base64ToHex(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto hexToBase64Url = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "hexToBase64Url"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::hexToBase64Url(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto base64UrlToHex = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "base64UrlToHex"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::base64UrlToHex(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto utf8ToBase64 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "utf8ToBase64"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::utf8ToBase64(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto base64ToUtf8 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "base64ToUtf8"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::base64ToUtf8(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto utf8ToBase64Url = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "utf8ToBase64Url"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::utf8ToBase64Url(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto base64UrlToUtf8 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "base64UrlToUtf8"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::base64UrlToUtf8(rt, result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto utf8ToHex = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "utf8ToHex"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value
                {
                        std::string result;
                        rncryptopp::utf8ToHex(rt, result, args);
                        return jsi::String::createFromUtf8(rt, result);
                });

        auto hexToUtf8 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "hexToUtf8"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value
                {
                        std::string result;
                        rncryptopp::hexToUtf8(rt, result, args);
                        return jsi::String::createFromUtf8(rt, result);
                });


        jsi::Object utils = jsi::Object(jsiRuntime);
        utils.setProperty(jsiRuntime, "randomBytesNative", std::move(randomBytesNative));
        utils.setProperty(jsiRuntime, "hexToBase64", std::move(hexToBase64));
        utils.setProperty(jsiRuntime, "base64ToHex", std::move(base64ToHex));
        utils.setProperty(jsiRuntime, "hexToBase64Url", std::move(hexToBase64Url));
        utils.setProperty(jsiRuntime, "base64UrlToHex", std::move(base64UrlToHex));
        utils.setProperty(jsiRuntime, "utf8ToBase64", std::move(utf8ToBase64));
        utils.setProperty(jsiRuntime, "base64ToUtf8", std::move(base64ToUtf8));
        utils.setProperty(jsiRuntime, "utf8ToBase64Url", std::move(utf8ToBase64Url));
        utils.setProperty(jsiRuntime, "base64UrlToUtf8", std::move(base64UrlToUtf8));
        utils.setProperty(jsiRuntime, "utf8ToHex", std::move(utf8ToHex));
        utils.setProperty(jsiRuntime, "hexToUtf8", std::move(hexToUtf8));

        /*
        Cryptopp module
        */
        jsi::Object module = jsi::Object(jsiRuntime);
        module.setProperty(jsiRuntime, "SHA", std::move(SHA));
        module.setProperty(jsiRuntime, "AES", std::move(AES));
        module.setProperty(jsiRuntime, "utils", std::move(utils));
        module.setProperty(jsiRuntime, "insecure", std::move(insecure));

        jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule", std::move(module));
}

void rncryptopp_cleanup()
{
}
