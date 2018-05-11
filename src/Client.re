/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let options =
  Js.Dict.fromList([
    (
      "authorization",
      Js.Json.string("Bearer f010acf32bad0a3320eccc042182716723142633"),
    ),
  ]);

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://api.github.com/graphql",
    ~headers=Js.Json.object_(options),
    (),
  );

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());