type state = {starred: bool};

type action =
  | AddStar;

let component = ReasonReact.reducerComponent("Star");

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
  initialState: () => {starred: viewerHasStarred},
  reducer: (action, _state) =>
    switch (action) {
    | AddStar => ReasonReact.Update({starred: true})
    },
  render: self => (
    <AddStarMutation>
      ...(
           (addMutation, _) => {
             let newStar = AddStar.make(~starrableId=id, ());
             <button
               onClick=(
                 _event => {
                   self.send(AddStar);
                   addMutation(~variables=newStar##variables, ()) |> ignore;
                 }
               )>
               (
                 ReasonReact.string(
                   self.state.starred ? {js|★|js} : {js|☆|js},
                 )
               )
             </button>;
           }
         )
    </AddStarMutation>: _
  ),
};