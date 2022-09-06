---
sidebar_position: 1
---

# HDKF

```js
const { hkdf } = Cryptopp.keyDerivation;
const derived = hkdf(str, 'salt', 'HKDF key derivation', 1024);
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |
| salt      | `string` <br/> `ArrayBuffer` | ✅       |
| hash      | Name of any supported hash   | ✅       |
| info      | `string`                     | ✅       |

`info` is additional, possibly public information to use during derivation.

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

