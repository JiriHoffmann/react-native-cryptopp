const { execSync } = require('child_process');
const { exit } = require('process');
const path = require('path');
const archiver = require('archiver');
const fs = require('fs');

const moduleDir = path.join(__dirname, '..');

// source: { dir: string; dest: string; }[], outPath: string
const zipDirectories = (sourceDirs, outPath) => {
  const archive = archiver('zip', { zlib: { level: 9 } });
  const stream = fs.createWriteStream(outPath);

  return new Promise((resolve, reject) => {
    var result = archive;
    sourceDirs.forEach((sourceDir) => {
      result = result.directory(sourceDir.dir, sourceDir.dest);
    });
    result.on('error', (err) => reject(err)).pipe(stream);

    stream.on('close', () => resolve());
    archive.finalize();
  });
};

// Remove all compiled files
execSync(`rm -rf ${moduleDir}/cpp/ios`);
execSync(`rm -rf ${moduleDir}/cpp/adnroid`);
execSync(`rm -rf ${moduleDir}/cpp/cryptopp`);

// Compile iOS
const compile_cryptopp_ios = `${moduleDir}/scripts/compile_cryptopp_ios.sh`;
execSync(`sh ${compile_cryptopp_ios}`);

// remove single architecture builds since
// we have the fat lib
execSync(`rm -f ${moduleDir}/cpp/ios/libcryptopp_*.a`);

// Compile Android
if (!process.env.ANDROID_NDK_ROOT) {
  console.log('ANDROID_NDK_ROOT missing.');
  exit(1);
}

if (!process.env.ANDROID_SDK_ROOT) {
  console.log('ANDROID_SDK_ROOT missing.');
  exit(1);
}

const compile_cryptopp_android = `${moduleDir}/scripts/compile_cryptopp_android.sh`;

const platform = 'android-21';

const sdk = process.env.ANDROID_SDK_ROOT;
const ndk = process.env.ANDROID_NDK_ROOT;

execSync(
  `sh ${compile_cryptopp_android} ${platform} ${moduleDir} ${sdk} ${ndk}`
);

// Create a single zip file that will be attached to the release.
zipDirectories(
  [
    { dir: `${moduleDir}/cpp/cryptopp`, dest: 'cryptopp' },
    { dir: `${moduleDir}/cpp/android`, dest: 'android' },
    { dir: `${moduleDir}/cpp/ios`, dest: 'ios' },
  ],
  'cryptopp.zip'
);
