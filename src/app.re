let component = ReasonReact.statelessComponent("App");

let parse = File.reader(Js.log);

let handleFileSelectionSafe = (event, _self) => {
  /* https://reasonml.github.io/reason-react/docs/en/event.html */
  let target = ReactEventRe.Form.target(event);
  let files = ReactDOMRe.domElementToObj(target)##files;
  if (files##length == 1) {
    parse(files[0]);
  }
};

let make = (_children) => {
  ...component,
  render: (self) =>
    <div>
      <FilePicker onChange={self.handle(handleFileSelectionSafe)} />
      {ReasonReact.stringToElement("aa")}
    </div>
};
