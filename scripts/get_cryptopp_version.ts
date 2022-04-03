import { exit } from 'process';
import fs from 'fs';
import path from 'path';
import { moduleDir } from './utils';

const packageFile = path.join(moduleDir, 'package.json');

const pck = JSON.parse(fs.readFileSync(packageFile).toString());

console.log(pck.cryptoppVersion);
exit(0);
