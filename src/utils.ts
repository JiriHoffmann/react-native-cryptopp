function stringToArrayBuffer(str: string) {
  const len = str.length;
  const buf = new ArrayBuffer(len * 2); // 2 bytes for each char
  const bufView = new Uint16Array(buf);
  for (let i = 0; i < len; i++) {
    bufView[i] = str.charCodeAt(i);
  }
  return buf;
}

function arrayBufferToString(buf: ArrayBuffer) {
  const bufView = new Uint16Array(buf);
  let str = '';
  for (let i = 0; i < bufView.length; i++) {
    str = str + String.fromCharCode(bufView[i]);
  }
  return str;
}

const utils = {
  stringToArrayBuffer,
  arrayBufferToString,
};

export default utils;
