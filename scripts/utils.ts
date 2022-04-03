import archiver from 'archiver';
import fs from 'fs';
import https from 'https';
import path from 'path';

interface Source {
  dir: string;
  dest: string;
}

export const moduleDir = path.join(__dirname, '..');

export const zipDirectories = (sourceDirs: Source[], outPath: string) => {
  const archive = archiver('zip', { zlib: { level: 9 } });
  const stream = fs.createWriteStream(outPath);

  return new Promise<void>((resolve, reject) => {
    var result = archive;
    sourceDirs.forEach((sourceDir) => {
      result = result.directory(sourceDir.dir, sourceDir.dest);
    });
    result.on('error', (err: any) => reject(err)).pipe(stream);

    stream.on('close', () => resolve());
    archive.finalize();
  });
};

export const downloadFile = (
  url: string,
  dest: string,
  file?: fs.WriteStream
) => {
  return new Promise<void>((resolve, reject) => {
    const f = file ?? fs.createWriteStream(dest);

    const request = https.get(url, (response) => {
      if (response.statusCode === 301 || response.statusCode === 302) {
        return downloadFile(response.headers.location!, dest, f)
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
