open Js.Typed_array;

type player = {
  last_name: string,
};

type save = {
  player: player
};

let parse = (buf: Uint8Array.t): save => {
  let last_name = (buf |> Buf.words(~start=16, ~len=8) |> Buf.asJString);
  { player: { last_name: last_name } }
};
