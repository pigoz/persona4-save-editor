open Jest;
open Expect;

describe("parse", () => {
  test("parses first_name", () => {
    let x = Parse.parse(Fixture.data0001);
    expect(x.player.first_name) |> toBe("Yu");
  });

  test("parses last_name", () => {
    let x = Parse.parse(Fixture.data0001);
    expect(x.player.last_name) |> toBe("Narukami");
  });

  test("parses yen", () => {
    let x = Parse.parse(Fixture.data0001);
    expect(x.player.yen) |> toBe(77228);
  });
});
