import { exit } from 'process';
import fs from 'fs';

const pck = JSON.parse(fs.readFileSync('package.json').toString());

console.log(pck.cryptoppVersion);
exit(0);
