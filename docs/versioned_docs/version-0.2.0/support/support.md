---
sidebar_position: 1
---

# Crypto++ Support

Here is the list of all Crypto++ algorithms supported in React Native. It will be progressively updated as new functionality is added.

#### Authenticated encryption schemes

| Name              | Supported |
| ----------------- | --------- |
| GCM               | ❌        |
| CCM               | ❌        |
| EAX               | ❌        |
| ChaCha20Poly1305  | ❌        |
| XChaCha20Poly1305 | ❌        |

#### High speed stream ciphers

| Name                       | Supported |
| -------------------------- | --------- |
| ChaCha (8/12/20)           | ❌        |
| ChaCha (IETF) HC (128/256) | ❌        |
| Panama                     | ❌        |
| Rabbit (128/256)           | ❌        |
| Sosemanuk                  | ❌        |
| Salsa20 (8/12/20)          | ❌        |
| XChaCha (8/12/20)          | ❌        |
| XSalsa20                   | ❌        |

#### AES and AES candidates

| Name           | Supported |
| -------------- | --------- |
| AES (Rijndael) | ✅        |
| RC6            | ❌        |
| MARS           | ❌        |
| Twofish        | ❌        |
| Serpent        | ❌        |
| CAST-256       | ❌        |

#### Other block ciphers

| Name                               | Supported |
| ---------------------------------- | --------- |
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

#### Block cipher modes of operation

| Name                          | Supported |
| ----------------------------- | --------- |
| ECB                           | ✅        |
| CBC                           | ✅        |
| CBC ciphertext stealing (CTS) | ✅        |
| CFB                           | ✅        |
| OFB                           | ✅        |
| counter mode (CTR)            | ✅        |
| XTS                           | ✅        |

#### Message authentication codes

| Name          | Supported |
| ------------- | --------- |
| BLAKE2s       | ❌        |
| BLAKE2b       | ❌        |
| CMAC          | ❌        |
| CBC-MAC       | ❌        |
| DMAC          | ❌        |
| GMAC (GCM)    | ❌        |
| HMAC          | ❌        |
| Poly1305      | ❌        |
| SipHash       | ❌        |
| Two-Track-MAC | ❌        |
| VMAC          | ❌        |

#### Hash functions

| Name                     | Supported |
| ------------------------ | --------- |
| BLAKE2b                  | ✅        |
| BLAKE2s                  | ✅        |
| Keccack (F1600)          | ✅        |
| SHA-1                    | ✅        |
| SHA-2                    | ✅        |
| SHA-3                    | ✅        |
| SHAKE (128/256)          | ✅        |
| SipHash                  | ✅        |
| LSH (128/256)            | ✅        |
| Tiger                    | ✅        |
| RIPEMD (128/160/256/320) | ✅        |
| SM3                      | ✅        |
| WHIRLPOOL                | ✅        |

#### Public-key cryptography

| Name                                       | Supported |
| ------------------------------------------ | --------- |
| RSA                                        | ✅        |
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

#### Padding schemes for public-key systems

| Name                       | Supported |
| -------------------------- | --------- |
| PKCS#1 v2.0                | ✅        |
| OAEP                       | ✅        |
| PSSR                       | ✅        |
| IEEE P1363 EMSA2 and EMSA5 | ❌        |

#### Key agreement schemes

| Name                         | Supported |
| ---------------------------- | --------- |
| Diffie-Hellman (DH)          | ❌        |
| Unified Diffie-Hellman (DH2) | ❌        |
| Menezes-Qu-Vanstone (MQV)    | ❌        |
| Hashed MQV (HMQV)            | ❌        |
| Fully Hashed MQV (FHMQV)     | ❌        |
| LUCDIF                       | ❌        |
| XTR-DH                       | ❌        |

#### Elliptic curve cryptography

| Name                           | Supported |
| ------------------------------ | --------- |
| ECDSA                          | ❌        |
| Determinsitic ECDSA (RFC 6979) | ❌        |
| ed25519                        | ❌        |
| ECGDSA                         | ❌        |
| ECNR                           | ❌        |
| ECIES                          | ❌        |
| x25519                         | ❌        |
| ECDH                           | ❌        |
| ECMQV                          | ❌        |

#### Insecure or obsolescent algorithms retained for backwards compatibility and historical value

| Name            | Supported |
| --------------- | --------- |
| MD2             | ✅        |
| MD4             | ✅        |
| MD5             | ✅        |
| Panama Hash     | ❌        |
| DES             | ❌        |
| ARC4            | ❌        |
| SEAL 3.0        | ❌        |
| WAKE-OFB        | ❌        |
| DESX (DES-XEX3) | ❌        |
| RC2             | ❌        |
| SAFER           | ❌        |
| 3-WAY           | ❌        |
| GOST            | ❌        |
| SHARK           | ❌        |
| CAST-128        | ❌        |
| Square          | ❌        |
