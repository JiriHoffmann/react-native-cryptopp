#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#include "hash-functions.h"
#include "utils.h"

namespace rncryptopp {
    void sha1(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string source;
        if (!valueToString(rt, args[0], &source)) {
            jsi::detail::throwJSError(rt, "Input in not a string");
        }
        CryptoPP::SHA1 sha1;
        CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha1,
                                                                      new CryptoPP::HexEncoder(
                                                                              new CryptoPP::StringSink(
                                                                                      result))));
    }

    void sha2(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string source;
        if (!valueToString(rt, args[0], &source)) {
            jsi::detail::throwJSError(rt, "Input in not a string");
        }
        std::string size;
        if (!valueToString(rt, args[1], &size)) {
            jsi::detail::throwJSError(rt, "Size in not a string");
        }

        if (size == "224") {
            CryptoPP::SHA224 sha;
            CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha,
                                                                          new CryptoPP::HexEncoder(
                                                                                  new CryptoPP::StringSink(
                                                                                          result))));
        } else if (size == "256") {
            CryptoPP::SHA256 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "384") {
            CryptoPP::SHA384 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "512") {
            CryptoPP::SHA512 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else {
            jsi::detail::throwJSError(rt, "Not a valid size");
        }
    }

    void sha3(jsi::Runtime &rt, std::string &result, const jsi::Value *args) {
        std::string source;
        if (!valueToString(rt, args[0], &source)) {
            jsi::detail::throwJSError(rt, "Input in not a string");
        }
        std::string size;
        if (!valueToString(rt, args[1], &size)) {
            jsi::detail::throwJSError(rt, "Size in not a string");
        }

        if (size == "224") {
            CryptoPP::SHA3_224 sha;
            CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha,
                                                                          new CryptoPP::HexEncoder(
                                                                                  new CryptoPP::StringSink(
                                                                                          result))));
        } else if (size == "256") {
            CryptoPP::SHA3_256 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "384") {
            CryptoPP::SHA3_384 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else if (size == "512") {
            CryptoPP::SHA3_512 sha;
            CryptoPP::StringSource(source, true,
                                   new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(
                                           new CryptoPP::StringSink(result))));
        } else {
            jsi::detail::throwJSError(rt, "Not a valid size");
        }
    }
}
