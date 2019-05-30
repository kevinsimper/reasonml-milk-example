[@ocaml.warning "-34-39"];
module Types1 = {
  type _Spaceship__ship = Spaceship.ship = {name: int};
};
let currentVersion = 1;
type target = Js.Json.t;
let schemaPropertyName = "$schemaVersion";
type result('a, 'b) = Belt.Result.t('a, 'b) = | Ok('a) | Error('b);
module Version1 = {
  open Types1;
  let rec deserialize_Spaceship____ship:
    target => result(_Spaceship__ship, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_name => Ok({name: attr_name}: _Spaceship__ship);
        switch (Js.Dict.get(dict, "name")) {
        | None => Belt.Result.Error(["No attribute 'name'"])
        | Some(json) =>
          switch (
            (
              number =>
                switch (Js.Json.classify(number)) {
                | JSONNumber(number) => Belt.Result.Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'name'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and serialize_Spaceship____ship: _Spaceship__ship => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          (
            "name",
            (int => Js.Json.number(float_of_int(int)))(record.name),
          ),
        |]),
      );
};
module Current = Version1;
let parseVersion = json =>
  switch (Js.Json.classify(json)) {
  | JSONObject(dict) =>
    switch (Js.Dict.get(dict, schemaPropertyName)) {
    | Some(schemaVersion) =>
      switch (Js.Json.classify(schemaVersion)) {
      | JSONNumber(version) =>
        [@implicit_arity] Belt.Result.Ok(int_of_float(version), json)
      | _ => Belt.Result.Error("Invalid " ++ schemaPropertyName)
      }
    | None => Belt.Result.Error("No " ++ schemaPropertyName ++ " present")
    }
  | JSONArray([|version, payload|]) =>
    switch (Js.Json.classify(version)) {
    | JSONNumber(version) =>
      [@implicit_arity] Belt.Result.Ok(int_of_float(version), payload)
    | _ => Belt.Result.Error("Invalid wrapped version")
    }
  | _ => Belt.Result.Error("Must have a schema version")
  };
let wrapWithVersion = (version, payload) =>
  switch (Js.Json.classify(payload)) {
  | JSONObject(dict) =>
    Js.Dict.set(
      dict,
      schemaPropertyName,
      Js.Json.number(float_of_int(version)),
    );
    Js.Json.object_(dict);
  | _ => Js.Json.array([|Js.Json.number(float_of_int(version)), payload|])
  };
let serializeShip = data =>
  wrapWithVersion(currentVersion, Version1.serialize_Spaceship____ship(data))
and deserializeShip = data =>
  switch (parseVersion(data)) {
  | Error(err) => Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_Spaceship____ship(data)) {
      | Error(error) => Error(error)
      | Ok(data) => Ok(data)
      }
    | _ => Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module Ship = {
    type t = Types1._Spaceship__ship;
    let serialize = serializeShip;
    let deserialize = deserializeShip;
  };
};
