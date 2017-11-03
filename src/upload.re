let component = ReasonReact.statelessComponent("Upload");
let make = (~onUploaded, _children) => {
  ...component,
  render: (_self) =>
    <div onClick=(onUploaded)>
      (U.s("uploader"))
    </div>
};

