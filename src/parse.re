open Js.Typed_array;

type player = {
  last_name: string,
  first_name: string,
  yen: int,
};

type save = {
  player: player
};

let parse = (buf: Uint8Array.t): save => {
  let last_name = (buf |> Buf.words(~start=16, ~len=8) |> Buf.asJString);
  let first_name = (buf |> Buf.words(~start=34, ~len=8) |> Buf.asJString);
  let yen = buf |> Buf.uint32At(~start=88);

  {
    player: {
      last_name: last_name,
      first_name: first_name,
      yen: yen,
    }
  }
};
