import archiver from 'archiver';
import fs from 'fs';

interface Source {
  dir: string;
  dest: string;
}

function zipDirectories(sourceDirs: Source[], outPath: string) {
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
}

export default { zipDirectories };
