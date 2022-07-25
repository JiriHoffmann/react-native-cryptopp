var fs = require('fs');
const { exit } = require('process');
const extract = require('extract-zip');
const path = require('path');
const https = require('https');
const rimraf = require('rimraf');

const downloadFile = (url, dest, file) => {
  return new Promise((resolve, reject) => {
    const f = file ?? fs.createWriteStream(dest);

    const request = https.get(url, (response) => {
      if (response.statusCode === 301 || response.statusCode === 302) {
        return downloadFile(response.headers.location, dest, f)
          .then(resolve)
          .catch(reject);
      } else if (response.statusCode !== 200) {
        fs.unlink(dest, () => {});
        return reject('Response status was ' + response.statusCode);
      } else {
        response.pipe(f);
      }
    });

    // check for request error too
    request.on('error', (err) => {
      fs.unlink(dest, () => reject(err.message));
    });

    // close() is async, call cb after close completes
    f.on('finish', () => f.close((err) => (err ? reject(err) : resolve())));

    // Handle errors
    f.on('error', (err) => {
      fs.unlink(dest, () => reject(err.message));
    });
  });
};

const moduleDir = path.join(__dirname, '..');
const packageLocation = `${moduleDir}/package.json`;
const pck = JSON.parse(fs.readFileSync(packageLocation).toString());
const repo = pck.repository;
const cryptopp_v = pck.cryptoppVersion;
const archive = `${moduleDir}/cryptopp_${cryptopp_v}.zip`;
const cppDir = `${moduleDir}/cpp`;

const compiledFiles = [
  `${moduleDir}/cpp/android/libcryptopp_arm64-v8a.a`,
  `${moduleDir}/cpp/android/libcryptopp_armeabi-v7a.a`,
  `${moduleDir}/cpp/android/libcryptopp_x86_64.a`,
  `${moduleDir}/cpp/android/libcryptopp_x86.a`,
  `${moduleDir}/cpp/ios/libcryptopp.xcframework`,
];

// Check if all files exist and archive version matches
if (
  compiledFiles.every((f) => fs.existsSync(f)) &&
  fs.existsSync(archive) &&
  !process.argv.includes('--force')
) {
  console.log(
    'Compiled Crypto++ files already downloaded. If you wish to overwrite them, run with --force'
  );
  exit(0);
}

// Clean up old archives
rimraf.sync(`${moduleDir}/cryptopp_*.zip`);

// example: https://github.com/JiriHoffmann/react-native-cryptopp/releases/download/cryptopp_8.6.0/cryptopp.zip
const link = `${repo}/releases/download/cryptopp_${cryptopp_v}/cryptopp.zip`;

console.log('Downloading compiled Crypto++ from...');
console.log(link);

downloadFile(link, archive)
  .then(() => {
    console.log('Extracting Crypto++...');
    extract(archive, { dir: cppDir })
      .then(() => {
        console.log('Compiled Crypto++ files downloaded.');
        exit(0);
      })
      .catch((err) => {
        console.log(err);
        exit(1);
      });
  })
  .catch((err) => {
    console.log(err);
    exit(1);
  });
