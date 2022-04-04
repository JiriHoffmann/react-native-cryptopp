---
sidebar_position: 1
---

# Utilities

## randomBytes

Generates a ArrayBuffer with random bytes using Crypto++ AutoSeededRandomPool.

```js
const bytes = Cryptopp.utils.randomBytes(32);
```

#### Parameters

| Parameter | Type     | Required |
| --------- | -------- | -------- |
| size      | `number` | ✅       |

#### Returns: `ArrayBuffer`

## stringToBytes

Tranforms a string into an ArrayBuffer.

```js
const string = 'Hello World';
const bytes = Cryptopp.utils.stringToBytes(string);
```

#### Parameters

| Parameter      | Type                                                            | Required | Default  |
| -------------- | --------------------------------------------------------------- | -------- | -------- |
| string         | `string`                                                        | ✅       |
| stringEncoding | `"utf8"` <br/> `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"utf8"` |

#### Returns: `ArrayBuffer`

## toBase64

Transforms a string or an ArrayBuffer into a base64 string.

```js
const b64 = Cryptopp.utils.toBase64(str);
```

#### Parameters

| Parameter     | Type                                                            | Required | Default  |
| ------------- | --------------------------------------------------------------- | -------- | -------- |
| input         | `string` <br/> `ArrayBuffer`                                    | ✅       |
| inputEncoding | `"utf8"` <br/> `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"utf8"` |

#### Returns: `string`

## toBase64Url

Transforms a string or an ArrayBuffer into a base64 url safe string.

```js
const b64url = Cryptopp.utils.toBase64Url(str);
```

#### Parameters

| Parameter     | Type                                                            | Required | Default  |
| ------------- | --------------------------------------------------------------- | -------- | -------- |
| input         | `string` <br/> `ArrayBuffer`                                    | ✅       |
| inputEncoding | `"utf8"` <br/> `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"utf8"` |

#### Returns: `string`

## toHex

Transforms a string or an ArrayBuffer into a hex string.

```js
const toHex = Cryptopp.utils.toHex(str);
```

#### Parameters

| Parameter     | Type                                                            | Required | Default  |
| ------------- | --------------------------------------------------------------- | -------- | -------- |
| input         | `string` <br/> `ArrayBuffer`                                    | ✅       |
| inputEncoding | `"utf8"` <br/> `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"utf8"` |

#### Returns: `string`

## toUtf8

Transforms a string or an ArrayBuffer into a utf8 string.

```js
const utf8 = Cryptopp.utils.toUtf8(str);
```

#### Parameters

| Parameter     | Type                                                            | Required | Default  |
| ------------- | --------------------------------------------------------------- | -------- | -------- |
| input         | `string` <br/> `ArrayBuffer`                                    | ✅       |
| inputEncoding | `"utf8"` <br/> `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"utf8"` |

#### Returns: `string`
