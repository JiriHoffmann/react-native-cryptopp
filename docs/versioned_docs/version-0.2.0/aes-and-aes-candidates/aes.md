---
sidebar_position: 1
---

# AES

AES block size will be determined be the size of the key. Here are the block size for the variout key sizes:

| Key size | Block size |
| -------- | ---------- |
| 16 bytes | 128 bits   |
| 24 bytes | 128 bits   |
| 32 bytes | 128 bits   |

**IV must be 16 bytes long.**

## Key & IV

The easiest way to obtain a key or an iv is by using the [randomBytes](../../utils) utility function.

```js
const aes_key = Cryptopp.utils.randomBytes(32);
const aes_iv = Cryptopp.utils.randomBytes(16);
```

Key & IV can be also passed as a string. Both the string key and string iv **must be `HEX`** encoded because UTF-8 allows variable length, multi-byte characters, so a string that is 16 characters long may not be 16 bytes long.

## Encrypt

```js
Cryptopp.AES.encrypt(message, key, iv, 'cbc');
```

#### Parameters

| Parameter | Type                                                                                            | Required | Default    |
| --------- | ----------------------------------------------------------------------------------------------- | -------- | ---------- |
| data      | `string` <br/> `ArrayBuffer`                                                                    | ✅       |            |
| key       | `HEX-encoded string` <br/>`ArrayBuffer`                                                         | ✅       |            |
| iv        | `HEX-encoded string` <br/> `ArrayBuffer`                                                        | ✅       |            |
| mode      | `"ecb"` <br/> `"cbc"` <br/> `"cbc_cts"` <br/> `"cfb"` <br/> `"ofb"` <br/> `"ctr"` <br/> `"xts"` | ✅       |
| encodeTo  | `"hex"` <br/> `"base64"` <br/> `"base64url"`                                                    | ❌       | `"base64"` |

#### Returns: `encoded string`, base64 by default

## Decrypt

```js
Cryptopp.AES.decrypt(encrypted_message, key, iv, 'cbc');
```

#### Parameters

| Parameter    | Type                                                  | Required | Default  |
| ------------ | ----------------------------------------------------- | -------- | -------- |
| data         | `string` <br/> `ArrayBuffer`                          | ✅       |          |
| key          | `HEX-encoded string` <br/> `ArrayBuffer`              | ✅       |          |
| iv           | `HEX-encoded string` <br/> `ArrayBuffer`              | ✅       |          |
| mode         | `ecb` <br/> `cbc` <br/> `cfb` <br/> `ofb` <br/> `ctr` | ✅       |          |
| dataEncoding | `utf8` <br/> `hex` <br/> `base64` <br/> `base64url`   | ❌       | `base64` |

#### Returns: `string`
