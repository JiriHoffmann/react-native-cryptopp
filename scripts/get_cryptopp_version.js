const { exit } = require('process');
const fs = require('fs');
const path = require('path');

const moduleDir = path.join(__dirname, '..');
const packageFile = `${moduleDir}/package.json`;

const pck = JSON.parse(fs.readFileSync(packageFile).toString());

console.log(pck.cryptoppVersion);
exit(0);
