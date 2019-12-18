open Async;
open Serbet.Endpoint;

module HelloEndpoint = {
  [@decco.decode]
  type params = {name: string};

  let endpoint =
    Serbet.endpoint({
      verb: GET,
      path: "/hello/:name",
      handler: req => {
        let%Async params = req.requireParams(params_decode);
        OkString("Hello, " ++ params.name ++ "!!!!!")->async;
      },
    });
};

module HelloJsonEndpoint = {
  [@decco.decode]
  type body_in = {name: string};

  [@decco.encode]
  type body_out = {greeting: string};

  let endpoint =
    Serbet.jsonEndpoint({
      verb: GET,
      path: "/hello/:name",
      body_in_decode,
      body_out_encode,
      handler: (body, _req) => {
        {greeting: "Hey there, " ++ body.name}->async;
      },
    });
};

module HelloQueryEndpoint = {
  [@decco.decode]
  type query = {name: string};

  let endpoint =
    Serbet.endpoint({
      verb: GET,
      path: "/hello/:name",
      handler: req => {
        let%Async query = req.requireQuery(query_decode);
        OkString("Hello, " ++ query.name ++ "!!!!!")->async;
      },
    });
};

let app =
  Serbet.application([HelloEndpoint.endpoint, HelloJsonEndpoint.endpoint]);