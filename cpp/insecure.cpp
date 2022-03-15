#include "insecure.h"

namespace rncryptopp
{

    void md2(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        Weak::MD2 hash;
        StringSource(data, true, new HashFilter(hash, new HexEncoder(new StringSink(result))));
    }

    void md4(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        Weak::MD4 hash;
        StringSource(data, true, new HashFilter(hash, new HexEncoder(new StringSink(result))));
    }

    void md5(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!binaryLikeValueToString(rt, args[0], &data, 0, 0))
        {
            throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        Weak::MD5 hash;
        StringSource(data, true, new HashFilter(hash, new HexEncoder(new StringSink(result))));
    }
}
