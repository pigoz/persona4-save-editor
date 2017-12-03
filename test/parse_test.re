open Jest;
open Expect;
open Parse;

let some = Js.Option.some;

describe("parse", () => {
  let x = parse(Fixture.data0001);

  test("parses first_name", () => {
    expect(get("first_name", x)) |> toEqual(some(Str("Yu", 8)));
  });

  test("parses last_name", () => {
    expect(get("last_name", x)) |> toEqual(some(Str("Narukami", 8)));
  });

  test("parses yen", () => {
    expect(get("yen", x)) |> toEqual(some(Uint32(77228)));
  });

  /*
  test("parses persona", () => {
    Js.log(Skills.all[x.persona1.skill1]);
    expect(x.persona1.exists) |> toBe(1); /* true */
    expect(x.persona1.id) |> toBe(7); /* jack frost */
    expect(x.persona1.level) |> toBe(19);
  });
  */
});
