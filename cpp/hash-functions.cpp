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

    // function definition
    template <class H>
    void getSHA2(std::string &data,
                 std::string &result)
    {
        H sha;
        StringSource(data, true, new HashFilter(sha, new HexEncoder(new StringSink(result))));
    }

    // Array of function pointers
    void (*SHA2ptrs[])(std::string &data,
                       std::string &result) =
        {&getSHA2<SHA224>, &getSHA2<SHA256>, &getSHA2<SHA384>, &getSHA2<SHA512>};

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

        int index = size == "224" ? 0 : size == "256 " ? 1
                                    : size == "384"    ? 2
                                    : size == "512"    ? 3
                                                       : -1;

        if (index == -1)
        {
            throwJSError(rt, "RNCryptopp: sha3 hash invalid hash value");
            return;
        }

        SHA2ptrs[index](data, result);
    }

    // function definition
    template <class H>
    void getSHA3(std::string &data,
                 std::string &result)
    {
        H sha;
        StringSource(data, true, new HashFilter(sha, new HexEncoder(new StringSink(result))));
    }

    // Array of function pointers
    void (*SHA3ptrs[])(std::string &data,
                       std::string &result) =
        {&getSHA3<SHA3_224>, &getSHA3<SHA3_256>, &getSHA3<SHA3_384>, &getSHA3<SHA3_512>};

    void sha3(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: sha3 data in not a string or ArrayBuffer");
        }
        std::string size;
        if (!stringValueToString(rt, args[1], &size))
        {
            throwJSError(rt, "RNCryptopp: sha3 size in not a string");
        }

        int index = size == "224" ? 0 : size == "256 " ? 1
                                    : size == "384"    ? 2
                                    : size == "512"    ? 3
                                                       : -1;

        if (index == -1)
        {
            throwJSError(rt, "RNCryptopp: sha3 hash invalid hash value");
            return;
        }

        SHA3ptrs[index](data, result);
    }
}
