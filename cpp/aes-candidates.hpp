#ifndef REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_HPP
#define REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_HPP

#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <string>

#include "cryptopp/modes.h"

#include "cryptopp/ccm.h"
#include "cryptopp/eax.h"
#include "cryptopp/gcm.h"
#include "cryptopp/xts.h"

#include "helpers.h"

using namespace facebook;
using namespace facebook::jsi::detail;
using namespace CryptoPP;

namespace rncryptopp::aescandidates {

enum ExecType {ENCRYPT,DECRYPT,};

template <template <class> class T_Mode, class T_BlockCipher>
    void exec(std::string *key, std::string *iv, std::string *data,
              std::string *result, ExecType execType) {
    if (execType == ENCRYPT) {
        typename T_Mode<T_BlockCipher>::Encryption e;
        e.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte *>(key->data()), key->size(),
                       reinterpret_cast<const CryptoPP::byte *>(iv->data()), iv->size());
        std::string encrypted;
        StringSource _(*data, true,
                       new StreamTransformationFilter(e, new StringSink(*result)));
    }
    if (execType == DECRYPT) {
        typename T_Mode<T_BlockCipher>::Decryption d;
        d.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte *>(key->data()), key->size(),
                       reinterpret_cast<const CryptoPP::byte *>(iv->data()), iv->size());
        StringSource s(*data, true,
                       new StreamTransformationFilter(d, new StringSink(*result)));
    }
}

template <class T_BlockCipher, typename... R>
bool getModeAndExec(std::string &mode, R... rest) {
    if (mode == "ecb")
        exec<ECB_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc")
        exec<CBC_Mode, T_BlockCipher>(rest...);
    else if (mode == "cbc_cts")
        exec<CBC_CTS_Mode, T_BlockCipher>(rest...);
    else if (mode == "cfb")
        exec<CFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ofb")
        exec<OFB_Mode, T_BlockCipher>(rest...);
    else if (mode == "ctr")
        exec<CTR_Mode, T_BlockCipher>(rest...);
    else if (mode == "xts")
        exec<XTS_Mode, T_BlockCipher>(rest...);
    else
        return false;
    return true;
}

template <typename T_BlockCipher>
jsi::Value encrypt(jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t argCount){
    std::string data, key, iv, mode, result;
    auto dataInputType = binaryLikeValueToString(rt, args[0], &data);
    if(dataInputType == INP_UNKNOWN)
        throwJSError(rt,
                     "RNCryptopp: aes & candidates encrypt data is not a string");

    if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
        throwJSError(rt, "RNCryptopp: aes & candidates encrypt key is not a string "
                         "or ArrayBuffer");

    if (binaryLikeValueToString(rt, args[2], &iv, ENCODING_HEX) == INP_UNKNOWN)
        throwJSError(rt, "RNCryptopp: aes & candidates encrypt iv is not a string "
                         "or ArrayBuffer");

    if (stringValueToString(rt, args[3], &mode) == INP_UNKNOWN)
        throwJSError(rt,
                     "RNCryptopp: aes & candidates encrypt mode is not a string");

    // Encrypt
    if (!getModeAndExec<T_BlockCipher>(mode,&key, &iv, &data, &result, ENCRYPT))
        throwJSError(
                rt, "RNCryptopp: aes & candidates encrypt mode is not a valid mode");

    // Return string
    if(dataInputType == INP_STRING){
        std::string encoded;
        auto encodeTo =
                rncryptopp::getEncodingFromArgs(rt, args, argCount, 4, ENCODING_BASE64, false);
        encodeString(&result, &encoded, encodeTo);
        return jsi::String::createFromUtf8(rt, encoded);
    }
   // Return ArrayBuffer
    int size = (int)result.size();
    jsi::Function array_buffer_ctor =
            rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
    jsi::Object obj =
            array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
    jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);
    // FIXME: see https://github.com/facebook/hermes/issues/564.
    memcpy(buff.data(rt), result.data(), size);

    return obj;
    }

template <typename T_BlockCipher>
jsi::Value decrypt(jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t argCount){
    auto dataEncoding = rncryptopp::getEncodingFromArgs(rt, args, argCount, 4,ENCODING_BASE64, false);

    std::string data, key, iv, mode, result;
    auto dataInputType = binaryLikeValueToString(rt, args[0], &data, dataEncoding);
    if(dataInputType == INP_UNKNOWN)
        throwJSError(rt,
                     "RNCryptopp: aes & candidates decrypt data is not a string");

    if (binaryLikeValueToString(rt, args[1], &key, ENCODING_HEX) == INP_UNKNOWN)
        throwJSError(rt,
                     "RNCryptopp: aes & candidates decrypt key is not a string");

    if (binaryLikeValueToString(rt, args[2], &iv, ENCODING_HEX) == INP_UNKNOWN)
        throwJSError(rt, "RNCryptopp: aes & candidates decrypt iv is not a string");

    if (stringValueToString(rt, args[3], &mode) == INP_UNKNOWN)
        throwJSError(rt,
                     "RNCryptopp: aes & candidates decrypt mode is not a string");

    // Decrypt
    if (!getModeAndExec<T_BlockCipher>(mode, &key, &iv, &data, &result, DECRYPT))
        throwJSError(
                rt, "RNCryptopp: aes & candidates decrypt mode is not a valid mode");

    // Return string
    if(dataInputType == INP_STRING){
        return jsi::String::createFromUtf8(rt, result);
    }
    // Return ArrayBuffer
    int size = (int)result.size();
    jsi::Function array_buffer_ctor =
            rt.global().getPropertyAsFunction(rt, "ArrayBuffer");
    jsi::Object obj =
            array_buffer_ctor.callAsConstructor(rt, size).getObject(rt);
    jsi::ArrayBuffer buff = obj.getArrayBuffer(rt);
    // FIXME: see https://github.com/facebook/hermes/issues/564.
    memcpy(buff.data(rt), result.data(), size);

    return obj;
    }


} // namespace rncryptopp::aescandidates
#endif // REACT_NATIVE_CRYPTOPP_AES_CANDIDATES_HPP
