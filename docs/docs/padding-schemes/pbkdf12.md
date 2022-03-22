---
sidebar_position: 2
---

# PKCS12 PBKDF

`Note from Crypyto++ Wiki:` New applications should consider using a modern KDF, like HKDF. HKDF is state of the art extract-then-expand derivation function with provable security properties.

```js
const {pbkdf12} = Cryptopp.keyDerivation;
const derived = pbkdf12(str, 'salt', 'SHA256', 1024);
```

#### Parameters

| Parameter  | Type                                             | Required |
| ---------- | ------------------------------------------------ | -------- |
| data       | `string` <br/> `ArrayBuffer`                     | ✅       |
| salt       | `string`                                         | ✅       |
| hash       | `"SHA1"` <br/> `"SHA256"` <br/> `"SHA512"` <br/>  `"SHA3_256"`  <br/> `"SHA3_512"` <br/>  `"SHAKE128"` <br/> `"SHAKE256"` <br/> `"BLAKE2b"` <br/>  `"BLAKE2s"` <br/>  `"LSH256"` <br/>  `"LSH512"` <br/>  `"SM3"`              | ✅       |
| iterations | `number`                                         | ✅       |

#### Returns: `string`
