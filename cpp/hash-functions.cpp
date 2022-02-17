#include "hash-functions.h"

namespace rncryptopp {
    void sha1(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string data;
        if (!valueToString(rt, args[0], &data)) {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        CryptoPP::SHA1 sha1;
        CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(sha1,
                                                                      new CryptoPP::HexEncoder(
                                                                              new CryptoPP::StringSink(
                                                                                      result))));
    }

    void sha2(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string data;
        if (!valueToString(rt, args[0], &data)) {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        std::string size;
        if (!valueToString(rt, args[1], &size)) {
            jsi::detail::throwJSError(rt, "RNCryptopp: Size in not a string");
        }

        if (size == "224") {
            CryptoPP::SHA224 sha;
            CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(sha,
                                                                          new CryptoPP::HexEncoder(
                                                                                  new CryptoPP::StringSink(
                                                                                          result))));
        } else if (size == "256") {
            CryptoPP::SHA256 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "384") {
            CryptoPP::SHA384 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "512") {
            CryptoPP::SHA512 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else {
            jsi::detail::throwJSError(rt, "RNCryptopp: Not a valid size");
        }
    }

    void sha3(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string data;
        if (!valueToString(rt, args[0], &data)) {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        std::string size;
        if (!valueToString(rt, args[1], &size)) {
            jsi::detail::throwJSError(rt, "RNCryptopp: Size in not a string");
        }

        if (size == "224") {
            CryptoPP::SHA3_224 sha;
            CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(sha,
                                                                          new CryptoPP::HexEncoder(
                                                                                  new CryptoPP::StringSink(
                                                                                          result))));
        } else if (size == "256") {
            CryptoPP::SHA3_256 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "384") {
            CryptoPP::SHA3_384 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "512") {
            CryptoPP::SHA3_512 sha;
            CryptoPP::StringSource(data, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else {
            jsi::detail::throwJSError(rt, "RNCryptopp: Not a valid size");
        }
    }
}
