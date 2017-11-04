let component = ReasonReact.statelessComponent("FilePicker");

let make = (~onChange, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <input _type={"file"} onChange={onChange} />
    </div>
};
