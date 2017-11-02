type a = { x: string };
type b = { x: int };
type c = { y: string };
type d = A | B(int);
type some_union =
 | A(a)
 | B(b)
 | C(c)
 | D(d);

/* i costruttori sono necessari per poter passare il tipo come props,
   la tipizzazione non è strutturale appena si tirano in mezzo type
   constructors

   esempio del chiamante:
   ReactDOMRe.renderToElementWithId(<App msg={App.make_da()}/>, "index");
*/
let make_a = (x) => A({ x: x });
let make_b = (x) => B({ x: x });
let make_c = (x) => C({ y: x });
let make_da = () => D(A);
let make_db = () => D(B(1));

/* inferisce da solo union -> string */
let getMsg = (msg) => {
  switch msg {
  | A(a) => a.x
  | B(b) => string_of_int(b.x)
  | C(c) => c.y
  | D(d) => switch d {
    | A => "D.A"
    | B(_) => "D.B"
    }
  };
};

let component = ReasonReact.statelessComponent("App");
let handleClick = (_event, _self) => Js.log("clicked!");
let make = (~msg : some_union, _children) => {
  ...component,
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      (ReasonReact.stringToElement(getMsg(msg)))
    </div>
};
