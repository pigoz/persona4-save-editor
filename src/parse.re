open Js.Typed_array;

type mem =
| Bool(int)
| Uint8(int)
| Uint16(int)
| Uint32(int)
| Str(string, int) /* (string itself, maximum string length) */
| Padding(int); /* (bytes of padding) */

/*
type field('name, 'mem) =
| Pristine('name, 'mem)
| Dirty('name, 'mem);
*/

let mbool = (x: int) => Bool(x);
let muint8 = (x: int) => Uint8(x);
let muint16 = (x: int) => Uint16(x);

let muint32 = (~start: int, dw: DataView.t) =>
  Uint32(Buf.uint32(~start, dw));

let mstr = (~start: int, ~len: int, dw: DataView.t) =>
  Str(Buf.str(~start, ~len, dw), len);

let mpad = (~start: int, ~len: int, dw: DataView.t) =>
  Padding(len);

type field = { name: string, mem: mem };
type save = array(field);

let layout = [|
  ("pad", mpad(~len=16)),
  ("last_name", mstr(~len=8)),
  ("pad", mpad(~len=2)),
  ("first_name", mstr(~len=8)),
  ("pad", mpad(~len=38)),
  ("yen", muint32), /* ends at 60 */
|];

let bytes = (adt: mem): int => {
  switch adt {
    | Bool(_) => 8
    | Uint8(_) => 8
    | Uint16(_) => 16
    | Uint32(_) => 32
    | Str(_, len) => len * 2
    | Padding(len) => len
  }
};

let parse = (xs: Uint8Array.t): save => {
  let buf = xs |> Uint8Array.buffer |> DataView.fromBuffer;
  let offset = ref(0);
  layout |> Array.map(x => {
    let (name, fn) = x;
    let adt = fn(~start=offset^, buf);
    offset := offset^ + bytes(adt);
    { name, mem: adt };
  });
};

let get = (key: string, sv: save): option(mem) => {
  sv
    |> Js.Array.find(x => { x.name == key })
    |> Js.Option.map([@bs] x => { x.mem });
};

/*
type stat = int; /* 99 max */
type sid = int;
type skills = (sid, sid, sid, sid, sid, sid, sid, sid);

type player = {
  last_name: string,
  first_name: string,
  yen: int
};

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
*/
