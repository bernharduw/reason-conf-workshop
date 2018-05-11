let component = ReasonReact.statelessComponent("Issue");

let make = (~title, _children) => {
  ...component,
  render: (_) =>
    <div>(ReasonReact.string("Issue title: " ++ title)) </div>,
};