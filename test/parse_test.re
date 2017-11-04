open Jest;
open Expect;

let loadfixture: (string) => Js.Typed_array.Uint8Array.t = [%bs.raw {|
  function(file) {
    const fs = require("fs");
    const path = require("path");
    const buf = fs.readFileSync(path.join(__dirname, "../fixtures", file));
    return new Uint8Array(buf);
  }
|}];

let data0001 = loadfixture("data0001.bin");

describe("parse", () => {
  test("works", () => {
    let x = Parse.parse(data0001);
    expect(x.player.last_name) |> toBe("Narukami");
  });
});
