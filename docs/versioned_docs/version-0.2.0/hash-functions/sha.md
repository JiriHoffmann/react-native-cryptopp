---
sidebar_position: 5
title: 'SHA/SHA2/SHA3'
---

#

# SHA

```js
Cryptopp.hashFunctions.SHA1(data);
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |

#### Returns: `string`

# SHA2

```js
Cryptopp.hashFunctions.SHA2(data, '512');
```

#### Parameters

| Parameter | Type                                            | Required |
| --------- | ----------------------------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer`                    | ✅       |
| size      | `"224"` <br/> `"256"` <br/>`"384"` <br/>`"512"` | ✅       |

#### Returns: `string`

# SHA3

```js
Cryptopp.hashFunctions.SHA3(data, '512');
```

#### Parameters

| Parameter | Type                                             | Required |
| --------- | ------------------------------------------------ | -------- |
| data      | `string` <br/> `ArrayBuffer`                     | ✅       |
| size      | `"224"` <br/> `"256"` <br/>`"384"` <br/> `"512"` | ✅       |

#### Returns: `string`
