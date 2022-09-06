---
sidebar_position: 1
---

# HMAC

## Generate

```js
const hmac = Cryptopp.HMAC.generate(str, key, 'AES', 'hex');
```

#### Parameters

| Parameter | Type                                             | Required | Default |
| --------- | ------------------------------------------------ | -------- | ------- |
| data      | `string` <br/> `ArrayBuffer`                     | ✅       |
| key       | `string` <br/> `ArrayBuffer`                     | ✅       |
| hash      | Name of any supported hash                       | ✅       |
| encodeTo  | `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"hex"` |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

## Verify

```js
const hmac_verify = Cryptopp.HMAC.verify(str, key, 'AES', hmac, 'hex');
```

#### Parameters

| Parameter         | Type                                             | Required | Default |
| ----------------- | ------------------------------------------------ | -------- | ------- |
| data              | `string` <br/> `ArrayBuffer`                     | ✅       |
| key               | `string` <br/> `ArrayBuffer`                     | ✅       |
| hash              | Name of any supported hash                       | ✅       |
| mac               | `string` <br/> `ArrayBuffer`                     | ✅       |
| macStringEncoding | `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"hex"` |

#### Returns: `boolean`

