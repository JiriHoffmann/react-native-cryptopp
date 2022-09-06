---
sidebar_position: 1
---

# Progressive Hashing

## create

```js
const hash = Cryptopp.hash.create('BLAKE2b');
```

#### Parameters

| Parameter | Type                       | Required |
| --------- | -------------------------- | -------- |
| hash      | Name of any supported hash | ✅       |

#### Returns: Hash object

## hash.update

```js
hash.update('Message');
```

#### Parameters

| Parameter | Type                         | Required |
| --------- | ---------------------------- | -------- |
| data      | `string` <br/> `ArrayBuffer` | ✅       |

## hash.finalize

```js
const BLAKE2b_progressive = hash.finalize();
```

#### Returns: `string`

