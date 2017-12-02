open Js.Typed_array;

type player = {
  last_name: string,
  first_name: string,
  yen: int
};

type stat = int; /* 99 max */
type sid = int;
type skills = (sid, sid, sid, sid, sid, sid, sid, sid);

type persona = {
  exists: int,
  id: int,
  level: stat,
  xp: int,
  skill1: sid,
  /*
  skill2: sid,
  skill3: sid,
  skill4: sid,
  skill5: sid,
  skill6: sid,
  skill7: sid,
  skill8: sid,
  st: stat,
  ma: stat,
  de: stat,
  ag: stat,
  lu: stat
  */
};

type save = {
  player: player,
  persona1: persona
};

let parsePlayer = (buf: DataView.t): player => {
  let last_name = buf |> Buf.str(~start=16, ~len=8);
  let first_name = buf |> Buf.str(~start=34, ~len=8);
  let yen = buf |> Buf.uint32(~start=88);

  {
    last_name: last_name,
    first_name: first_name,
    yen: yen,
  }
};

let parsePersona = (~start: int, buf: DataView.t): persona => {
  {
    exists: buf |> Buf.uint8(~start=start),
    id: buf |> Buf.uint16(~start=start + 2),
    level: buf |> Buf.uint8(~start=start + 4),
    xp: buf |> Buf.uint32(~start=start + 8),
    skill1: buf |> Buf.uint16(~start=start + 9)
  };
};

let parse = (xs: Uint8Array.t): save => {
  let buf = xs |> Uint8Array.buffer |> DataView.fromBuffer;

  {
    player: buf |> parsePlayer,
    persona1: buf |> parsePersona(~start=2700)
  }
};
