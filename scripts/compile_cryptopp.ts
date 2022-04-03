import { execSync } from 'child_process';
import { exit } from 'process';
import path from 'path';
import { moduleDir, zipDirectories } from './utils';

// Compile iOS
const compile_cryptopp_ios = path.join(
  moduleDir,
  'scripts/compile_cryptopp_ios.sh'
);

execSync(`sh ${compile_cryptopp_ios}`);

// remove single architecture builds since
// we have the fat lib
execSync('rm cpp/ios/libcryptopp_arm64.a');
execSync('rm cpp/ios/libcryptopp_x86_64.a');

// Compile Android
if (!process.env.ANDROID_NDK_ROOT) {
  console.log('ANDROID_NDK_ROOT missing.');
  exit(1);
}

if (!process.env.ANDROID_SDK_ROOT) {
  console.log('ANDROID_SDK_ROOT missing.');
  exit(1);
}

const compile_cryptopp_android = path.join(
  moduleDir,
  'scripts/compile_cryptopp_android.sh'
);

const platform = 'android-21';

const sdk = process.env.ANDROID_SDK_ROOT;
const ndk = process.env.ANDROID_NDK_ROOT;

execSync(
  `sh ${compile_cryptopp_android} ${platform} ${moduleDir} ${sdk} ${ndk}`
);

// Create a single zip file that will be attached to the release.
zipDirectories(
  [
    { dir: 'cpp/cryptopp', dest: 'cryptopp' },
    { dir: 'cpp/android', dest: 'android' },
    { dir: 'cpp/ios', dest: 'ios' },
  ],
  'cryptopp.zip'
);
