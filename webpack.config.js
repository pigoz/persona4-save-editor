const path = require('path');

module.exports = {
  entry: './src/index.re',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'app.js',
  },
  module: {
    rules: [
      { test: /\.(re|ml)$/, use: 'bs-loader' },
    ],
  },
  resolve: {
    extensions: ['.re', '.ml', '.js'],
  }
};
