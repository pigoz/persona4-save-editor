const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const UglifyJSPlugin = require('uglifyjs-webpack-plugin');

const buildDir = path.join(__dirname, "build");
const src = file => path.join(__dirname, './src', file);

function uglify(xs) {
  if (process.env.NODE_ENV === 'production') {
    xs.push(new UglifyJSPlugin({
      parallel: true,
      uglifyOptions: {
        ie8: false,
        ecma: 8,
        output: {
          comments: false,
          beautify: false,
        },
      },
    }));
  }
  return xs;
}

module.exports = {
  entry: src('index.re'),
  output: {
    path: buildDir,
    filename: 'app.bs.js',
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        use: {
          loader: 'bs-loader',
          options: {
            module: 'es6',
          },
        },
      },
    ],
  },
  resolve: {
    extensions: ['.js'],
  },
  plugins: uglify([
    new HtmlWebpackPlugin({
      inject: true,
      template: src('index.html'),
    }),
  ]),
  devServer: {
    contentBase: buildDir,
    compress: true,
    port: 9000
  }
};
