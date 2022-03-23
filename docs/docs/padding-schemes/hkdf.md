---
sidebar_position: 1
---

# HDKF

```js
const {hkdf} = Cryptopp.keyDerivation;
const derived = hkdf(str, 'salt', 'HKDF key derivation', 1024);
```

#### Parameters

| Parameter  | Type                                             | Required |
| ---------- | ------------------------------------------------ | -------- |
| data       | `string` <br/> `ArrayBuffer`                     | ✅       |
| salt       | `string`                                         | ✅       |
| hash       | `"SHA1"` <br/> `"SHA256"` <br/> `"SHA512"` <br/>  `"SHA3_256"`  <br/> `"SHA3_512"` <br/>  `"SHAKE128"` <br/> `"SHAKE256"` <br/> `"BLAKE2b"` <br/>  `"BLAKE2s"` <br/>  `"LSH256"` <br/>  `"LSH512"` <br/>  `"SM3"`              | ✅       |
| info      | `string`                                         | ✅       |

`info` is additional, possibly public information to use during derivation.

#### Returns: `string`