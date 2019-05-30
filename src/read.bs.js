// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var TypeSerde = require("./TypeSerde.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

var raw = Fs.readFileSync("ship.json");

var json = JSON.parse(raw);

var match = TypeSerde.deserializeShip(json);

if (match.tag) {
  console.log("Failed", match[0]);
} else {
  var result = match[0];
  console.log(result[/* name */0]);
  console.log("Good", Caml_option.undefined_to_opt(JSON.stringify(result)), JSON.stringify(json));
}

exports.raw = raw;
exports.json = json;
/* raw Not a pure module */