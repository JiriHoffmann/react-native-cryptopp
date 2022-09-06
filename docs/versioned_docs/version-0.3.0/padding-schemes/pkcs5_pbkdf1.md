---
sidebar_position: 3
---

# PKCS5 PBKDF1

`Note from Crypyto++ Wiki:` New applications should consider using a modern KDF, like HKDF. HKDF is state of the art extract-then-expand derivation function with provable security properties.

```js
const { pkcs5_pbkdf1 } = Cryptopp.keyDerivation;
const derived = pkcs5_pbkdf1(str, 'salt', 'SHA256', 1024);
```

#### Parameters

| Parameter  | Type                         | Required |
| ---------- | ---------------------------- | -------- |
| data       | `string` <br/> `ArrayBuffer` | ✅       |
| salt       | `string` <br/> `ArrayBuffer` | ✅       |
| hash       | Name of any supported hash   | ✅       |
| iterations | `number`                     | ✅       |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`
