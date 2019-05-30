[@bs.val] [@bs.module "fs"] external readFileSync: string => string = "";

let raw = readFileSync("ship.json");

let json = Js.Json.parseExn(raw);

switch (TypeSerde.deserializeShip(json)) {
| Ok(result) =>
  let ship = result;
  Js.log(ship.name);
  Js.log3("Good", Js.Json.stringifyAny(result), Js.Json.stringify(json));
| Error(error) => Js.log2("Failed", error)
};
