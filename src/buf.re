open Js.Typed_array;
open Prelude;
type b = Uint8Array.t;

[@bs.send.pipe : b] external subarray: (~start: int, ~end_: int) => b = "";
[@bs.send.pipe : b] external map : (int => int) => b = "";
[@bs.send.pipe : b] external map2 : ((int, int) => int) => b = "map";
[@bs.send.pipe : b] external filter : (int => bool) => b = "";
[@bs.send.pipe : b] external filter2 : ((int, int) => bool) => b = "filter";

/* len is 16bit words (2-bytes) */
let words = (~start, ~len, buffer) => {
  let end_ = start + len * 2;
  buffer |> subarray(~start, ~end_);
};

let utf8: (b) => string = [%bs.raw {|
  function(buffer) {
    // XXX: should probably only use the npm package on node? chrome has this
    const x = require("text-encoding");
    return new x.TextDecoder("utf-8").decode(buffer);
  }
|}];

let asJString: (Uint8Array.t) => string =
  /* this is big-endian because lol psvita, ignore the least significant
   * byte since it's useless anyway */
  filter2((_x, idx) => idx mod 2 !== 0) >>
  /* not sure why but the most significant part in the unicode word
   * is saved by summing 96/0x60 to the actual unicode/ascii value, maybe they
   * store hiragana/katakana before A+96? */
  map(x => x - 0x60) >>
  utf8;
