import fs from 'fs';
import { downloadFile, moduleDir } from './utils';
import { exit } from 'process';
import extract from 'extract-zip';
import path from 'path';
import { execSync } from 'child_process';

const pck = JSON.parse(fs.readFileSync('package.json').toString());
const repo = pck.repository;
const cryptopp_v = pck.cryptoppVersion;
const archive = `cryptopp_${cryptopp_v}.zip`;
const cppDir = path.join(moduleDir, 'cpp');

const compiledFiles = [
  'cpp/android/libcryptopp_arm64-v8a.a',
  'cpp/android/libcryptopp_armeabi-v7a.a',
  'cpp/android/libcryptopp_x86_64.a',
  'cpp/android/libcryptopp_x86.a',
  'cpp/ios/libcryptopp.a',
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
execSync(`rm -rf cryptopp_*.zip`);

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
