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
execSync(`rm -rf ${moduleDir}/cpp/android`);
execSync(`rm -rf ${moduleDir}/cpp/cryptopp`);

// Validate env variables
if (!process.env.ANDROID_NDK_ROOT) {
  console.log('ANDROID_NDK_ROOT missing.');
  exit(1);
}

if (!process.env.ANDROID_SDK_ROOT) {
  console.log('ANDROID_SDK_ROOT missing.');
  exit(1);
}

// Compile iOS
execSync(`sh ${moduleDir}/scripts/compile_cryptopp_ios.sh`);

// Compile Android
const android_script = `${moduleDir}/scripts/compile_cryptopp_android.sh`;
const platform = 'android-21';
const sdk = process.env.ANDROID_SDK_ROOT;
const ndk = process.env.ANDROID_NDK_ROOT;

execSync(`sh ${android_script} ${platform} ${moduleDir} ${sdk} ${ndk}`);

// Create a single zip file that will be attached to the release.
zipDirectories(
  [
    { dir: `${moduleDir}/cpp/cryptopp`, dest: 'cryptopp' },
    { dir: `${moduleDir}/cpp/android`, dest: 'android' },
    {
      dir: `${moduleDir}/cpp/ios/libcryptopp.xcframework`,
      dest: 'ios/libcryptopp.xcframework',
    },
  ],
  'cryptopp.zip'
);
