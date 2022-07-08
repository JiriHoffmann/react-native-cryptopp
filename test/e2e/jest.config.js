module.exports = {
  preset: 'ts-jest',
  testEnvironment: 'node',
  setupFilesAfterEnv: ['./testSetup.ts'],
  testRunner: 'jasmine2',
};
