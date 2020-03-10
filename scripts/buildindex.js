const fs = require('fs');
const path = require('path');
const Root = path.join(__dirname, '../');
const config = require(path.join(Root, '.indexconfig.json'));
const NodeGreaterThanXX = nodeGreaterThanXX();

buildIndexRecursively(config.root);

/**
 * @param {string} directory
 * @param {string} extname
 * @param {string} entry
 */
function buildIndexRecursively(directory, extname = config.extname, entry = directory) {
  const basename = path.basename(directory);
  const indexFile = (directory === entry ? config.entry : directory).concat(extname);
  const absoluteIndexFile = path.join(Root, indexFile);
  const absoluteDirectory = path.join(Root, directory);

  if (!fs.existsSync(absoluteDirectory)) {
    throw new Error('directory does not extists: '.concat(absoluteDirectory));
  }

  if (fs.existsSync(absoluteIndexFile)) {
    console.warn('index file already extists: '.concat(absoluteIndexFile));
  }

  const filesStats = NodeGreaterThanXX
    ? fs
        .readdirSync(absoluteDirectory, { withFileTypes: true })
        .map(stat => ({ stat, name: stat.name }))
    : fs
        .readdirSync(absoluteDirectory)
        .map(name => ({ stat: fs.statSync(path.join(directory, name)), name }));

  /** @type {string[]} */
  const relativeIncludes = filesStats.map(({ stat, name }) => {
    if (stat.isFile() && name.endsWith(extname)) return path.join(basename, name);
    if (stat.isDirectory()) {
      buildIndexRecursively(path.join(directory, name), extname, entry);
      return path.join(basename, name).concat(extname);
    }
    return '';
  });

  if (config.excludes && config.excludes.some(pattern => new RegExp(pattern).test(indexFile))) {
    return;
  }

  const relativeIncludesSet = new Set(relativeIncludes);
  relativeIncludesSet.delete('');

  const includes = Array.from(relativeIncludesSet).reduce((prev, relativePath) => {
    return relativePath ? prev.concat('#include "', relativePath, '"\n') : prev;
  }, '\n');

  const identifier = path
    .relative(entry, directory)
    .replace('/', '_')
    .toUpperCase();
  const macroName = config.macroprefix.concat(identifier && '_', identifier);

  const indexContent = [
    '#ifndef '.concat(macroName),
    '#define '.concat(macroName),
    includes,
    '#endif /* '.concat(macroName, ' */\n'),
  ].join('\n');

  fs.writeFileSync(absoluteIndexFile, indexContent, 'utf8');
}

function nodeGreaterThanXX() {
  const [major, minor] = process.version.match(/(\d*)\.(\d*)\.(\d*)/).slice(1);
  if (parseInt(major) > 10) return true;
  return major === '10' && parseInt(minor) >= 10;
}
