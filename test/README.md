# Test project for react-native-cryptopp

This folders includes a simple project to test the react-native-cryptopp library. As we have to test the native code, the testing is done via Detox with Jest. Currenly only set up for iOS since symlinking the project is much easier and since the codebase is identical for both platforms there is no need to test the code for both platforms.

Tests are located in the `e2e/tests` folder. To run use: 

```bash
# Install node modules
npm i

# Build
detox build

# Test
detox test
```
