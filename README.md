# React Native Cryptopp


## Installation

```sh
npm install react-native-cryptopp
```
#### `iOS`

```
cd ios && pod install
# or 
npx pod install
```

The Crypto++ library is precompiled for each architecture and static binaries are contained `android` and `ios` folders respectively. Android builds per 
architecture and iOS uses a fat binary that is created before the pod is installed. You are more than welcome to complile the Crypto++ library locally using the `build_cryptopp.sh` script.

## Usage

- [Documentation]()
- [Crypto++](http://www.cryptopp.com/wiki/Main_Page)


# Supported Alghorithms
Here is the list of all Crypto++ algorithm supported by this library. You are 
always free to help exapand the list.

## Authenticated encryption schemes
| Name                                 | Supported |
|--------------------------------------|-----------|
| GCM                                  |     ❌    |
| CCM                                  |     ❌    |
| EAX                                  |     ❌    |
| ChaCha20Poly1305                     |     ❌    |
| XChaCha20Poly1305                    |     ❌    |

##  High speed stream ciphers
| Name                       | Supported |
|----------------------------|-----------|
| ChaCha (8/12/20)           | ❌        |
| ChaCha (IETF) HC (128/256) | ❌        |
| Panama                     | ❌        |
| Rabbit (128/256)           | ❌        |
| Sosemanuk                  | ❌        |
| Salsa20 (8/12/20)          | ❌        |
| XChaCha (8/12/20)          | ❌        |
| XSalsa20                   | ❌        |

## AES and AES candidates	
| Name           | Supported |
|----------------|-----------|
| AES (Rijndael) | ❌        |
| RC6            | ❌        |
| MARS           | ❌        |
| Twofish        | ❌        |
| Serpent        | ❌        |
| CAST-256       | ❌        |

## Other block ciphers	
| Name                               | Supported |
|------------------------------------|-----------|
| ARIA                               | ❌        |
| Blowfish                           | ❌        |
| Camellia                           | ❌        |
| CHAM                               | ❌        |
| HIGHT                              | ❌        |
| IDEA                               | ❌        |
| Kalyna (128/256/512)               | ❌        |
| LEA                                | ❌        |
| SEED                               | ❌        |
| RC5                                | ❌        |
| SHACAL-2                           | ❌        |
| SIMECK                             | ❌        |
| SIMON (64/128)                     | ❌        |
| Skipjack                           | ❌        |
| SPECK (64/128)                     | ❌        |
| Simeck                             | ❌        |
| SM4                                | ❌        |
| Threefish (256/512/1024)           | ❌        |
| Triple-DES (DES-EDE2 and DES-EDE3) | ❌        |
| TEA                                | ❌        |
| XTEA                               | ❌        |
## Block cipher modes of operation
| Name                               | Supported |
|------------------------------------|-----------|
| ECB                                | ❌        |
| CBC                                | ❌        |
| CBC ciphertext stealing (CTS)      | ❌        |
| CFB                                | ❌        |
| OFB                                | ❌        |
| counter mode (CTR)                 | ❌        |
| XTS                                | ❌        |
### Message authentication codes	
| Name                               | Supported |
|------------------------------------|-----------|
| BLVMACAKE2b                        | ❌        |
| BLAKE2s                            | ❌        |
| CMAC                               | ❌        |
| CBC-MAC                            | ❌        |
| DMAC                               | ❌        |
| GMAC (GCM)                         | ❌        |
| HMAC                               | ❌        |
| Poly1305                           | ❌        |
| SipHash                            | ❌        |
| Two-Track-MAC                      | ❌        |
| VMAC                               | ❌        |
### Hash functions	
| Name                               | Supported |
|------------------------------------|-----------|
| BLAKE2b                            | ❌         |
| BLAKE2s                            | ❌         |
| Keccack (F1600)                    | ❌         |
| SHA-1                              | ❌         |
| SHA-2                              | ❌         |
| SHA-3                              | ❌         |
| SHAKE (128/256)                    | ❌         |
| SipHash                            | ❌         |
| LSH (128/256)                      | ❌         |
| Tiger                              | ❌         |
| RIPEMD (128/160/256/320)           | ❌         |
| SM3                                | ❌         |
| WHIRLPOOL                          | ❌         |
### Public-key cryptography	
| Name                                       | Supported |
|--------------------------------------------|-----------|
| RSA                                        | ❌        |
| DSA                                        | ❌        |
| Determinsitic DSA (RFC 6979)               | ❌        |
| ElGamal                                    | ❌        |
| Nyberg-Rueppel (NR)                        | ❌        |
| Rabin-Williams (RW)                        | ❌        |
| EC-based German Digital Signature (ECGDSA) | ❌        |
| LUC                                        | ❌        |
| LUCELG                                     | ❌        |
| DLIES (variants of DHAES)                  | ❌        |
| ESIGN                                      | ❌        |
### Padding schemes for public-key systems	
| Name                                       | Supported |
|--------------------------------------------|-----------|
| PKCS#1 v2.0                                | ❌         |
| OAEP                                       | ❌         |
| PSS                                        | ❌         |
| PSSR                                       | ❌         |
| IEEE P1363 EMSA2 and EMSA5                 | ❌         |
### Key agreement schemes	
| Name                               | Supported |
|------------------------------------|-----------|
| Diffie-Hellman (DH)                | ❌         |
| Unified Diffie-Hellman (DH2)       | ❌         |
| Menezes-Qu-Vanstone (MQV)          | ❌         |
| Hashed MQV (HMQV)                  | ❌         |
| Fully Hashed MQV (FHMQV)           | ❌         |
| LUCDIF                             | ❌         |
| XTR-DH                             | ❌         |
### Elliptic curve cryptography	
| Name                               | Supported |
|------------------------------------|-----------|
| ECDSA                              | ❌         |
| Determinsitic ECDSA (RFC 6979)     | ❌         |
| ed25519                            | ❌         |
| ECGDSA                             | ❌         |
| ECNR                               | ❌         |
| ECIES                              | ❌         |
| x25519                             | ❌         |
| ECDH                               | ❌         |
| ECMQV                              | ❌         |
### Insecure or obsolescent algorithms retained for backwards compatibility and historical value	
| Name                               | Supported |
|------------------------------------|-----------|
| MD2                                | ❌         |
| MD4                                | ❌         |
| MD5                                | ❌         |
| Panama Hash                        | ❌         |
| DES                                | ❌         |
| ARC4                               | ❌         |
| SEAL 3.0                           | ❌         |
| WAKE-OFB                           | ❌         |
| DESX (DES-XEX3)                    | ❌         |
| RC2                                | ❌         |
| SAFER                              | ❌         |
| 3-WAY                              | ❌         |
| GOST                               | ❌         |
| SHARK                              | ❌         |
| CAST-128                           | ❌         |
| Square                             | ❌         |



## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
