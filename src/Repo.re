let component = ReasonReact.statelessComponent("Repo");

let make = (~name, ~owner, ~viewerHasStarred, ~id, _children) => {
  ...component,
  render: (_) =>
    <li>
      <h2>
        <Star viewerHasStarred={viewerHasStarred} id={id} />

        (ReasonReact.string("Repo name: " ++ name))
      </h2>
      <div> (ReasonReact.string(owner)) </div>
    </li>,
};