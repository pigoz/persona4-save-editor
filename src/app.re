let component = ReasonReact.statelessComponent("App");
let handleClick = (_event, _self) => Js.log("clicked!");

let make = (_children) => {
  ...component,
  render: (self) =>
    <div>
      <Upload onUploaded=(self.handle(handleClick)) />
    </div>
};
