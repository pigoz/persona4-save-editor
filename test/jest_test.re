open Jest;
open Expect;
open! Expect.Operators;

describe("Expectt", () => {

  test("toBe", () => {
    expect(1 + 2) |> toBe(3);
  });

});

describe("Expect.Operators", () => {

  test("==", () => {
    expect(1 + 2) === 3;
  });
});
