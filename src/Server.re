open Async;

module App =
  Serbet.App({});

open App;

module HelloEndpoint =
  App.Handle({
    let verb = GET;
    let path = "/hello/:name";

    [@decco.decode]
    type params = {name: string};

    let handler = req => {
      let%Async params = requireParams(params_decode, req);
      OkString("Hello, " ++ params.name ++ "!!!!!")->async;
    };
  });

App.start(~port=1337, ());