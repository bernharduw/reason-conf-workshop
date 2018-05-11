let component = ReasonReact.statelessComponent("Star");

module AddStar = [%graphql
  {|
  mutation addStar($starrableId: ID!) {
  addStar(input: {starrableId: $starrableId}) {
    starrable {
      id
    }
  }
}
|}
];

module AddStarMutation = ReasonApollo.CreateMutation(AddStar);

module RemoveStar = [%graphql
  {|
  mutation removeStar($starrableId: ID!) {
  removeStar(input: {starrableId: $starrableId}) {
    starrable {
      id
    }
  }
}
|}
];

module RemoveStarMutation = ReasonApollo.CreateMutation(RemoveStar);

let make = (~viewerHasStarred, ~id, _children) => {
  ...component,
  render: (_) =>
    <AddStarMutation>
      ...(
           (addMutation, _) => {
             let newStar = AddStar.make(~starrableId=id, ());
             <button
               onClick=(
                 _event =>
                   addMutation(~variables=newStar##variables, ()) |> ignore
               )>
               (
                 ReasonReact.string(
                   viewerHasStarred ? {js|★|js} : {js|☆|js},
                 )
               )
             </button>;
           }
         )
    </AddStarMutation>,
};