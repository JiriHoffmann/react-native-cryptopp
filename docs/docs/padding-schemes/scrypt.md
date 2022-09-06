---
sidebar_position: 5
---

# Scrypt

```js
const { Scrypt } = Cryptopp.keyDerivation;
const derived = Scrypt(str, 1024, 8, 16, 64);
```

#### Parameters

| Parameter          | Type                         | Required |
| ------------------ | ---------------------------- | -------- |
| data               | `string` <br/> `ArrayBuffer` | ✅       |
| salt               | `string` <br/> `ArrayBuffer` | ✅       |
| cost               | `number`                     | ✅       |
| blockSize          | `number`                     | ✅       |
| parallelization    | `number`                     | ✅       |
| derived key length | `number`                     | ✅       |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

