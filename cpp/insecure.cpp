#include "insecure.h"

namespace rncryptopp
{

    void md2(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!valueToString(rt, args[0], &data))
        {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        CryptoPP::Weak::MD2 hash;
        CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result))));
    }

    void md4(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!valueToString(rt, args[0], &data))
        {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        CryptoPP::Weak::MD4 hash;
        CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result))));
    }

    void md5(jsi::Runtime &rt, std::string &result, const jsi::Value *args)
    {
        std::string data;
        if (!valueToString(rt, args[0], &data))
        {
            jsi::detail::throwJSError(rt, "RNCryptopp: Data in not a string");
        }
        CryptoPP::Weak::MD5 hash;
        CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result))));
    }
}
