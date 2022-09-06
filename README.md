# React Native Cryptopp

The goal of this library is to provide a wide variety cryptography functionality to React Native at super fast speeds by using a C++ library called [Crypto++](https://www.cryptopp.com/) under the hood.

## Installation

```bash
npm install react-native-cryptopp
```

### Optional: Using pre-compiled Crypto++ library

```bash
yarn node node_modules/react-native-cryptopp/scripts/download_cryptopp.js
```

### iOS

```bash
cd ios && pod install
# or
npx pod install
```

**`Important:`** First time builds will take several minutes as Crypto++ has to be compiled for all CPU architectures. Make sure the `android build` and `pod install` is **NOT** running at the same time! More information about the build process can be found [here](https://jirihoffmann.github.io/react-native-cryptopp).

## Usage

- [Documentation](https://jirihoffmann.github.io/react-native-cryptopp)
- [Crypto++ Wiki](http://www.cryptopp.com/wiki/Main_Page)

```js
import Cryptopp from 'react-native-cryptopp';

const hash = Cryptopp.hash.SHA1('Hello World');
```

## TODOs:

- [ ] Implement remaining functionality
- [X] Use GitHub Actions to pre-compile Crypto++ for iOS and Android
- [X] Async multi-threaded version of each function
- [X] Tests ...
- [ ] ..., tests, tests... and more tests!

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

Check [Crypto++](https://github.com/weidai11/cryptopp/blob/master/License.txt) for additional licensing.
