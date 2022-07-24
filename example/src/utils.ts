export const PerformanceNow =
  // @ts-ignore
  (global.performance && global.performance.now) ||
  // @ts-ignore
  global.performanceNow ||
  // @ts-ignore
  global.nativePerformanceNow ||
  (() => {
    try {
      var now = require('fbjs/lib/performanceNow');
    } finally {
      return now;
    }
  })();

const fixed = (n: number) => (Math.trunc(n) === n ? n + '' : n.toFixed(3));

export const timeDelta = (start: number, end: number) =>
  fixed(end - start) + ' ms';
