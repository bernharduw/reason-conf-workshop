/* Create a GraphQL Query by using the graphql_ppx */
module GetRepos = [%graphql
  {|
  query {
   viewer {
    email,
    repositories(last:50, orderBy:{field:STARGAZERS, direction: DESC}) {
      nodes {
        id,
        name,
        viewerHasStarred,
        owner {
          login
        }
      }
    }
  }
}
|}
];

module GetReposQuery = ReasonApollo.CreateQuery(GetRepos);

let component = ReasonReact.statelessComponent("RepoList");

let make = _children => {
  ...component,
  render: (_) => {
    let reposQuery = GetRepos.make();
    <GetReposQuery variables=reposQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(error) =>
               <div> (ReasonReact.string(Js.String.make(error))) </div>
             | Data(response) =>
               <div>
                 (
                   ReasonReact.string(
                     "Repos starred by: " ++ response##viewer##email,
                   )
                 )
                 <ul>
                   (
                     switch (response##viewer##repositories##nodes) {
                     | None => ReasonReact.null
                     | Some(repos) =>
                       repos
                       |> Js.Array.map(repo =>
                            switch (repo) {
                            | None => ReasonReact.null
                            | Some(repo) =>
                              <Repo
                                id=repo##id
                                name=repo##name
                                owner=repo##owner##login
                                viewerHasStarred=repo##viewerHasStarred
                              />
                            }
                          )
                       |> ReasonReact.array
                     }
                   )
                 </ul>
               </div>
             }
         )
    </GetReposQuery>;
  },
};