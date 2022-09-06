---
sidebar_position: 1
---

# CMAC

## Generate

```js
const cmac = Cryptopp.CMAC.generate(str, key, 'AES', 'hex');
```

#### Parameters

| Parameter | Type                                             | Required | Default |
| --------- | ------------------------------------------------ | -------- | ------- |
| data      | `string` <br/> `ArrayBuffer`                     | ✅       |
| key       | `string` <br/> `ArrayBuffer`                     | ✅       |
| cipher    | Name of any supported block cipher               | ✅       |
| encodeTo  | `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"hex"` |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

## Verify

```js
const cmac_verify = Cryptopp.CMAC.verify(str, key, 'AES', cmac, 'hex');
```

#### Parameters

| Parameter         | Type                                             | Required | Default |
| ----------------- | ------------------------------------------------ | -------- | ------- |
| data              | `string` <br/> `ArrayBuffer`                     | ✅       |
| key               | `string` <br/> `ArrayBuffer`                     | ✅       |
| cipher            | Name of any supported block cipher               | ✅       |
| mac               | `string` <br/> `ArrayBuffer`                     | ✅       |
| macStringEncoding | `"hex"` <br/> `"base64"` <br/>`"base64url"`<br/> | ❌       | `"hex"` |

#### Returns: `boolean`

