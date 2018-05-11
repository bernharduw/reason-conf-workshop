/* Create a GraphQL Query by using the graphql_ppx */
module GetIssues = [%graphql
  {|
  query Issues($owner: String!, $name: String!) {
  repository(owner: $owner, name: $name) {
    issues(first: 50, states: [OPEN], orderBy: {direction: DESC, field: UPDATED_AT}) {
      nodes {
        title
      }
    }
  }
}
|}
];

module GetIssuesQuery = ReasonApollo.CreateQuery(GetIssues);

let component = ReasonReact.statelessComponent("IssueList");

let make = (~name, ~owner, _children) => {
  ...component,
  render: (_) => {
    let issuesQuery = GetIssues.make(~owner, ~name, ());
    <GetIssuesQuery variables=issuesQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(error) =>
               <div> (ReasonReact.string(Js.String.make(error))) </div>
             | Data(response) =>
               <ul>
                 (
                   switch (response##repository) {
                   | None => ReasonReact.null
                   | Some(repo) =>
                     switch (repo##issues##nodes) {
                     | None => ReasonReact.null
                     | Some(issues) =>
                       issues
                       |> Js.Array.map(issue =>
                            switch (issue) {
                            | None => ReasonReact.null
                            | Some(issue) => <Issue title=issue##title />
                            }
                          )
                       |> ReasonReact.array
                     }
                   }
                 )
               </ul>
             }
         )
    </GetIssuesQuery>;
  },
};