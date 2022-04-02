const p = require('process');
const fs = require('fs');

const pck = JSON.parse(fs.readFileSync('package.json').toString());

console.log(pck.cryptoppVersion);
p.exit(0);
