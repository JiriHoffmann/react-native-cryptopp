import p from 'process';
import fs from 'fs';

const pck = JSON.parse(fs.readFileSync('package.json').toString());

console.log(pck.cryptoppVersion);
p.exit(0);
