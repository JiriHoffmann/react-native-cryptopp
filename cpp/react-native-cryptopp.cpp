#include <iostream>
#include <sstream>

#include "react-native-cryptopp.h"


namespace rncryptopp {
    void install(jsi::Runtime &jsiRuntime) {
        /*
        Hash functions
        */
        auto sha1 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "sha1"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::sha1(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );
        auto sha2 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "sha2"),
                2,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::sha2(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );
        auto sha3 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "sha3"),
                2,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::sha3(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );

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
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::aes_encrypt(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );
            auto aes_decrypt = jsi::Function::createFromHostFunction(
                    jsiRuntime,
                    jsi::PropNameID::forAscii(jsiRuntime, "aes_decrypt"),
                    4,
                    [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                       size_t count) -> jsi::Value {
                        std::string result;
                        rncryptopp::aes_decrypt(rt, result, args);
                        return jsi::Value(jsi::String::createFromUtf8(rt, result));
                    }
            );

        jsi::Object AES = jsi::Object(jsiRuntime);
        AES.setProperty(jsiRuntime, "encrypt", std::move(aes_encrypt));
        AES.setProperty(jsiRuntime, "decrypt", std::move(aes_decrypt));

        
        /*
        Utils
        */
        auto toBase64 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "toBase64"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::toBase64(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );

        auto fromBase64 = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "fromBase64"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::fromBase64(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );

        auto toHex = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "toHex"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::toHex(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );

        auto fromHex = jsi::Function::createFromHostFunction(
                jsiRuntime,
                jsi::PropNameID::forAscii(jsiRuntime, "fromHex"),
                1,
                [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
                   size_t count) -> jsi::Value {
                    std::string result;
                    rncryptopp::fromHex(rt, result, args);
                    return jsi::Value(jsi::String::createFromUtf8(rt, result));
                }
        );

        jsi::Object utils = jsi::Object(jsiRuntime);
        utils.setProperty(jsiRuntime, "toBase64", std::move(toBase64));
        utils.setProperty(jsiRuntime, "fromBase64", std::move(fromBase64));
        utils.setProperty(jsiRuntime, "toHex", std::move(toHex));
        utils.setProperty(jsiRuntime, "fromHex", std::move(fromHex));


        /*
        Cryptopp module
        */
        jsi::Object module = jsi::Object(jsiRuntime);
        module.setProperty(jsiRuntime, "SHA", std::move(SHA));
        module.setProperty(jsiRuntime, "AES", std::move(AES));
        module.setProperty(jsiRuntime, "utils", std::move(utils));


        jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule", std::move(module));
    }

    void cleanup() {
    }
}
