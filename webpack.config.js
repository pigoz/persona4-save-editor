const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const buildDir = path.join(__dirname, "build");
const src = file => path.join(__dirname, './src', file);

module.exports = {
  entry: src('index.re'),
  output: {
    path: buildDir,
    filename: 'app.js',
  },
  module: {
    rules: [
      { test: /\.(re|ml)$/, use: 'bs-loader' },
    ],
  },
  resolve: {
    extensions: ['.re', '.ml', '.js'],
  },
  plugins: [
    new HtmlWebpackPlugin({
      inject: true,
      template: src('index.html'),
    }),
  ],
  devServer: {
    contentBase: buildDir,
    compress: true,
    port: 9000
  }
};
