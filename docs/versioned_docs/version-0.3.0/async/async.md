---
sidebar_position: 1
---

# Asynchronous Functionality

Cryptopp.async provides exactly the same functionality to the synchronous counterparts, but with the ability to run all computations asynchronously offloaded to another thread. Even complex computations such as creating an RSA key pair can be done without a single FPS drop in the JS thread. 

All functions have the exact same signature but return a Promise.

Note: Progressive hashing does not have asynchronous functions.

# Example

```js
// Synchronous - returns string
const hash_result = Cryptopp.hash.SHA1('Hello World'); 

// Asynchronous - returns Promise<string>
const hash_result2 = await Cryptopp.async.hash.SHA1('Hello World'); 
```
