---
sidebar_position: 6
title: 'SHA/SHA2/SHA3'
---

#

# SHA

```js
Cryptopp.hash.SHA1(data);
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |

#### Returns: `string` or `ArrayBuffer` based on the input type

# SHA2

```js
Cryptopp.hash.SHA224(data);
Cryptopp.hash.SHA256(data);
Cryptopp.hash.SHA384(data);
Cryptopp.hash.SHA512(data);
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |

#### Returns: `string` 

# SHA3

```js
Cryptopp.hash.SHA3_224(data);
Cryptopp.hash.SHA3_256(data);
Cryptopp.hash.SHA3_384(data);
Cryptopp.hash.SHA3_512(data);
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |

#### Returns: `string` 

