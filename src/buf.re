open Js.Typed_array;
type b = Uint8Array.t;

[@bs.send.pipe : b] external subarray: (~start: int, ~end_: int) => b = "";
[@bs.send.pipe : b] external map : (int => int) => b = "";
[@bs.send.pipe : b] external map2 : ((int, int) => int) => b = "map";
[@bs.send.pipe : b] external filter : (int => bool) => b = "";
[@bs.send.pipe : b] external filter2 : ((int, int) => bool) => b = "filter";
[@bs.send.pipe : b] external reduce : (('a, int) => 'a, 'a) => 'a = "";
[@bs.send] external reverse : ('b) => 'b = "";

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

let dropWhile = (fn: (int => bool), xs: b): b => {
  let result = xs |> reduce((accu, el) => {
    switch accu {
    | None => fn(el) ? None : Some([|el|])
    | Some(x) => Some(x |> Js.Array.append(el))
    }
  }, None);
  Uint8Array.make(result |> Js.Option.getWithDefault([||]));
};

let fill: (int, 'a) => array('a) = [%bs.raw {|
  function(len, start) {
    return Array(len).fill(1).map((x, idx) => start + (idx * 2));
  }
|}];

let stringAt = (~start: int, ~len: int, xs: Uint8Array.t): string => {
  let buffer = xs |> Uint8Array.buffer;
  let dw = DataView.fromBuffer(buffer);
  let xs = fill(len, start) |> Js.Array.map(x => {
    /* not sure why this is shifted by this value... */
    DataView.getUint16(dw, x) - 32864;
  });
  Uint8Array.make(xs) |>
  /* trim spaces */
  reverse |>
  dropWhile(x => x == 160) |>
  reverse |>
  utf8;
};

let uint32At = (~start: int, xs: Uint8Array.t): int => {
  let buffer = xs |> Uint8Array.buffer;
  let dw = DataView.fromBuffer(buffer);
  DataView.getUint32LittleEndian(dw, start);
};
