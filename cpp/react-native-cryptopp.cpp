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
                    rncryptopp::sha1(rt,args, result);
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
                    rncryptopp::sha2(rt,args, result);
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
                    rncryptopp::sha3(rt,args, result);
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
                    rncryptopp::aes_encrypt(rt,args, result);
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
                    rncryptopp::aes_decrypt(rt,args, result);
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
                    rncryptopp::md2(rt,args, result);
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
                    rncryptopp::md4(rt,args, result);
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
                    rncryptopp::md5(rt,args, result);
                    return jsi::String::createFromUtf8(rt, result);
            });

        jsi::Object insecure = jsi::Object(jsiRuntime);
        insecure.setProperty(jsiRuntime, "md2", std::move(md2));
        insecure.setProperty(jsiRuntime, "md4", std::move(md4));
        insecure.setProperty(jsiRuntime, "md5", std::move(md5));

        /*
        Key Derivation Functions
        */
        auto pkcs5_pbkdf1 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf1"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::pkcs5_pbkdf1(rt,args, result);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto pkcs5_pbkdf2 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "pkcs5_pbkdf2"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::pkcs5_pbkdf2(rt,args, result);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto pbkdf12 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "pbkdf12"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::pbkdf12(rt,args, result);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto hkdf = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "hkdf"),
            4,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::hkdf(rt,args, result);
                    return jsi::String::createFromUtf8(rt, result);
            });

        jsi::Object keyDerivation = jsi::Object(jsiRuntime);
        keyDerivation.setProperty(jsiRuntime, "pkcs5_pbkdf1", std::move(pkcs5_pbkdf1));
        keyDerivation.setProperty(jsiRuntime, "pkcs5_pbkdf2", std::move(pkcs5_pbkdf2));
        keyDerivation.setProperty(jsiRuntime, "pbkdf12", std::move(pbkdf12));
        keyDerivation.setProperty(jsiRuntime, "hkdf", std::move(hkdf));

        /*
        Utils
        */
        auto toBase64 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "toBase64"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::toBase64(rt, &result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto toBase64Url = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "toBase64Url"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::toBase64Url(rt, &result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto toHex = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "toHex"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::toHex(rt, &result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto toUtf8 = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "toUtf8"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    std::string result;
                    rncryptopp::toUtf8(rt, &result, args);
                    return jsi::String::createFromUtf8(rt, result);
            });

        auto randomBytes = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "randomBytes"),
            1,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    int size;
                    if (!rncryptopp::valueToInt(args[0], &size))
                            throwJSError(rt, "RNCryptopp: randomBytes size is not a number");

                    jsi::Function array_buffer_ctor = rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
                    jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
                    jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

                    AutoSeededRandomPool prng;
                    SecByteBlock random(size);
                    prng.GenerateBlock(random, random.size());

                    // FIXME: see https://github.com/facebook/hermes/issues/564.
                    memcpy(buff.data(rt), random.data(), size);
                    return obj;
            });

        auto stringToBytes = jsi::Function::createFromHostFunction(
            jsiRuntime,
            jsi::PropNameID::forAscii(jsiRuntime, "stringToBytes"),
            2,
            [](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args,
               size_t count) -> jsi::Value
            {
                    int encoding = rncryptopp::getEncodingFromArgs(rt, args, 1);
                    if (encoding == -1)
                            throw jsi::JSError(rt, "RNCryptopp: stringToBytes invalid dataEncoding");

                    std::string bytes;
                    if (!rncryptopp::binaryLikeValueToString(rt, args[0], &bytes, encoding, encoding))
                            throw jsi::JSError(rt, "RNCryptopp: stringToBytes data is not a string");

                    int size = (int)bytes.size();

                    jsi::Function array_buffer_ctor = rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
                    jsi::Object obj = array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
                    jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);

                    // FIXME: see https://github.com/facebook/hermes/issues/564.
                    memcpy(buff.data(rt), bytes.data(), size);
                    return obj;
            });

        jsi::Object utils = jsi::Object(jsiRuntime);
        utils.setProperty(jsiRuntime, "toBase64", std::move(toBase64));
        utils.setProperty(jsiRuntime, "toBase64Url", std::move(toBase64Url));
        utils.setProperty(jsiRuntime, "toHex", std::move(toHex));
        utils.setProperty(jsiRuntime, "toUtf8", std::move(toUtf8));
        utils.setProperty(jsiRuntime, "randomBytes", std::move(randomBytes));
        utils.setProperty(jsiRuntime, "stringToBytes", std::move(stringToBytes));

        /*
        Cryptopp module
        */
        jsi::Object module = jsi::Object(jsiRuntime);
        module.setProperty(jsiRuntime, "SHA", std::move(SHA));
        module.setProperty(jsiRuntime, "AES", std::move(AES));
        module.setProperty(jsiRuntime, "insecure", std::move(insecure));
        module.setProperty(jsiRuntime, "keyDerivation", std::move(keyDerivation));
        module.setProperty(jsiRuntime, "utils", std::move(utils));

        jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule", std::move(module));
}

void rncryptopp_cleanup()
{
}
