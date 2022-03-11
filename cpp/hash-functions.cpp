#include "hash-functions.h"

namespace rncryptopp
{
    void sha1(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        SHA1 sha1;
        StringSource(data, true, new HashFilter(sha1, new HexEncoder(new StringSink(result))));
    }

    void sha2(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        std::string size;
        if (!stringValueToString(rt, args[1], &size))
        {
            throwJSError(rt, "RNCryptopp: Size in not a string");
        }

        if (size == "224")
        {
            SHA224 sha;
            StringSource(data, true,
                                   new HashFilter(sha,
                                                            new HexEncoder(
                                                                new StringSink(
                                                                    result))));
        }
        else if (size == "256")
        {
            SHA256 sha;
            StringSource(data, true,
                                   new HashFilter(sha,
                                                            new HexEncoder(
                                                                new StringSink(
                                                                    result))));
        }
        else if (size == "384")
        {
            SHA384 sha;
            StringSource(data, true,
                                   new HashFilter(sha,
                                                            new HexEncoder(
                                                                new StringSink(
                                                                    result))));
        }
        else if (size == "512")
        {
            SHA512 sha;
            StringSource(data, true,
                                   new HashFilter(sha,
                                                            new HexEncoder(
                                                                new StringSink(
                                                                    result))));
        }
        else
        {
            throwJSError(rt, "RNCryptopp: Not a valid size");
        }
    }

    void sha3(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        std::string size;
        if (!stringValueToString(rt, args[1], &size))
        {
            throwJSError(rt, "RNCryptopp: Size in not a string");
        }

        if (size == "224")
        {
            SHA3_224 sha;
            StringSource(data, true, new HashFilter(sha, new HexEncoder(new StringSink(result))));
        }
        else if (size == "256")
        {
            SHA3_256 sha;
            StringSource(data, true,
                                   new HashFilter(sha, new HexEncoder(
                                                                     new StringSink(result))));
        }
        else if (size == "384")
        {
            SHA3_384 sha;
            StringSource(data, true,
                                   new HashFilter(sha, new HexEncoder(
                                                                     new StringSink(result))));
        }
        else if (size == "512")
        {
            SHA3_512 sha;
            StringSource(data, true,
                                   new HashFilter(sha, new HexEncoder(
                                                                     new StringSink(result))));
        }
        else
        {
            throwJSError(rt, "RNCryptopp: Not a valid size");
        }
    }
}
