# React Native Cryptopp

The goal of this library is to provide a wide variety cryptography functionality to React Native at super fast speeds by using a C++ library called [Cryptopp](https://www.cryptopp.com/) under the hood.

## Installation

```sh
npm install react-native-cryptopp
```

#### `iOS`

```sh
cd ios && pod install
# or
npx pod install
```

**`Important:`** First time builds will take several minutes as Crypto++ has to be compiled for all CPU architectures. Make sure the `android build` and `pod install` is **NOT** running at the same time! More information about the build process can be found [here]().

## Usage

- [Documentation]()
- [Crypto++ Wiki](http://www.cryptopp.com/wiki/Main_Page)

```js
import Cryptopp from 'react-native-cryptopp';

const hash = Cryptopp.hashFunctions.SHA1('Hello World');
```

## TODOs:

- [ ] Implement remaining functionality
- [ ] GitHub Actions pipeline to auto pre-compile Crypto++ for all CPU architectures
- [ ] Async multi-threaded version of each function

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

Check [Crypto++](https://github.com/weidai11/cryptopp/blob/master/License.txt) for additional licensing.
