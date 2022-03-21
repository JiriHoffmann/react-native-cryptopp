---
sidebar_position: 1
slug: /
---

# Installation

```sh
npm install react-native-cryptopp
# or 
yarn add react-native-cryptopp
```

#### iOS

```sh
cd ios && pod install
# or 
npx pod install
```

Make sure [Hermes](https://reactnative.dev/docs/hermes) is enabled in your project.

## Optional: Compiling CryptoPP
React Native CryptoPP is build on top of the Crypto++ library. Currently each platform (android & iOS) have their own precompiled static libraries that are distributed as a part of this package as it makes the build process easier. 

For security reasons you might want to compile the Crypto++ library yourself. You can do so by running the `compile_cryptopp.sh` script.

Run from the root of the project:
```sh
./node_modules/react-native-cryptopp/compile_cryptopp.sh
```

Ensure you have the following environment variables set correctly:
```
export ANDROID_HOME=
export ANDROID_SDK_ROOT=
export ANDROID_AVD_HOME=
export ANDROID_NDK_ROOT=
```

### Android binaries 
Can be found under `cpp/android` in a zip format to reduce package size and fit GitHub file size limits.
Extracted and linked during the android build process.

### iOS binaries 
Can be found under `cpp/iOS`. Combined into a fat binary and linked during pod install.