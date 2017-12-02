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

  test("parses persona", () => {
    let x = Parse.parse(Fixture.data0001);
    Js.log(Skills.all[x.persona1.skill1]);
    expect(x.persona1.exists) |> toBe(1); /* true */
    expect(x.persona1.id) |> toBe(7); /* jack frost */
    expect(x.persona1.level) |> toBe(19);
  });
});
