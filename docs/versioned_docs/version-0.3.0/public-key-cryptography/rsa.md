---
sidebar_position: 1
---

# RSA

This library uses the [Cryptop++ PEM_PACK](https://github.com/noloader/cryptopp-pem) to parse and store RSA keys in the PEM format.

## Generate Key Pair

```js
const rsa_keypair = Cryptopp.RSA.generateKeyPair(2048);
```

#### Returns: Object containing the public and private keys, as well as the parameters used to generate the keys.

```json
{
    public: "...",
    private: "...",
    params: {
        n: "...",
        p:"...",
        q:"...",
        d:"...",
        e:"...",
    },
};
```

Example of a returned public/private key:

```
-----BEGIN FOO BAR KEY-----
MIIBgjAcBgoqhkiG9w0BDAEDMA4ECKZesfWLQOiDAgID6ASCAWBu7izm8N4V
2puRO/Mdt+Y8ceywxiC0cE57nrbmvaTSvBwTg9b/xyd8YC6QK7lrhC9Njgp/
...
-----END FOO BAR KEY-----
```

## Encrypt

Encrypts a message using the public key.

```js
const publicKey = ... // obtained from second party
const encrypted = Cryptopp.RSA.encrypt(data, publicKey, 'OAEP_SHA1');
```

#### Parameters

| Parameter        | Type                                                   | Required |
| ---------------- | ------------------------------------------------------ | -------- |
| data             | `string` <br/> `ArrayBuffer`                           | ✅       |
| publicKey        | `string`                                               | ✅       |
| encryptionScheme | `"OAEP_SHA1"` <br/> `"OAEP_SHA256"` <br/> `"PKCS1v15"` | ✅       |
#### Returns: Based on `data` input type: `ArrayBuffer` or `base64-encoded string`

## Decrypt

Decrypts a message using the private key.

```js
const rsa_keypair = ... // some locally stored keypair
const encryptedData = Cryptopp.RSA.encrypt(data, rsa_keypair.private, 'OAEP_SHA1');
```

#### Parameters

| Parameter        | Type                                                   | Required |
| ---------------- | ------------------------------------------------------ | -------- |
| data             | `base64-encoded string` <br/> `ArrayBuffer`            | ✅       |
| privateKey       | `string`                                               | ✅       |
| encryptionScheme | `"OAEP_SHA1"` <br/> `"OAEP_SHA256"` <br/> `"PKCS1v15"` | ✅       |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

## Sign

Signs a message with a private key to ensure authenticity.

```js
const rsa_keypair = ... // some locally stored keypair
const signedData = Cryptopp.RSA.sign(encryptedData, rsa_keypair.private, 'PKCS1v15_SHA1');
```

#### Parameters

| Parameter        | Type                                             | Required |
| ---------------- | ------------------------------------------------ | -------- |
| data             | `string` <br/> `ArrayBuffer`                         | ✅       |
| privateKey       | `string`                                         | ✅       |
| signatureScheme  | `"PKCS1v15_SHA1"`  <br/> `"PKCS1v15_SHA256"`  <br/> `"PSSR_SHA1"`   <br/> `"PSSR_SHA256"`  <br/> `"PSSR_Whirlpool"`  <br/> `"PSS_SHA1"`  <br/> `"PSS_SHA256"`  <br/> `"PSS_Whirlpool"`| ✅       |

`Note:` Crypto++ supports two broad categories of digital signatures: Signature Schemes with Appendix (PKCS1v15_SHA1 and PKCS1v15_SHA256) and Signature Schemes with Recovery (PSSR_SHA1, PSSR_SHA256, and PSSR_Whirlpool).

A signature scheme with appendix requires the verifier to have three items: the public key, the message, and the signature. Can be verified using the `Cryptopp.RSA.verify` function.

A signature scheme with recovery requires only the public key and signature - the message is recovered from the signature. Can be recovered using the `Cryptopp.RSA.recover` function.

#### Returns: Based on `data` input type: `ArrayBuffer` or `base64-encoded string`

## Verify

Valides signature of a message.

```js
const data = ...
const dataSignature = ...
const publicKey = ... // obtained from second party
const isSignatureValid = Cryptopp.RSA.verify(signedData, publicKey, 'PKCS1v15_SHA1', dataSignature);
```

#### Parameters

| Parameter       | Type                                        | Required |
| --------------- | ------------------------------------------- | -------- |
| data            | `base64-encoded string` <br/> `ArrayBuffer` | ✅       |
| publicKey       | `string`                                    | ✅       |
| signatureScheme | `"PKCS1v15_SHA1"` <br/> `"PKCS1v15_SHA256"` <br/> `"PSS_SHA1"` <br/> `"PSS_SHA256"` <br/> `"PSS_Whirlpool"` | ✅       |
| signature       | `base64-encoded string` <br/> `ArrayBuffer` | ✅       |
#### Returns: `true` if the signature is valid, `false` otherwise.

## Recover

Recovers the message from the signature using the public key.

```js
// In this case, data has to be signed with PSSR and will be then distributed as the message
const data = ...
const rsa_keypair = ... // some locally stored keypair
const signature = Cryptopp.RSA.sign(data, rsa_keypair.private, 'PSSR_SHA1');

// Recipient can now verify the signature and recover the message
const publicKey = ... // obtained from second party
try {
    const recoveredData = Cryptopp.RSA.recover(signature, publicKey, 'PSSR_SHA1');
} catch (e) {
    // handle error if signature doens't match the key
}
```

#### Parameters

| Parameter       | Type                                                         | Required |
| --------------- | ------------------------------------------------------------ | -------- |
| signature       | `base64-encoded string` <br/> `ArrayBuffer`                  | ✅       |
| publicKey       | `string`                                                     | ✅       |
| signatureScheme | `"PSSR_SHA1"` <br/> `"PSSR_SHA256"` <br/> `"PSSR_Whirlpool"` | ✅       |

#### Returns: Based on `data` input type: `ArrayBuffer` or `string`

#### Throws error if the signature doesn't match the key
