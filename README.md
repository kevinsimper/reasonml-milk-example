# How to use ReasonML Milk

https://github.com/jaredly/milk

It is a cool project that can automatically generate serialize and deserialize code from your types. Normally you would have to write them by hand.

1. Download Milk from https://github.com/jaredly/milk/releases

2. Setup a ReasonML Project https://medium.com/@kevinsimper/how-to-start-a-minimal-reasonml-project-without-boilerplate-57e9e19bfa88

3. Write your code in `src`

   You can see I wrote a simple type in `Spaceship.re`

4. Run `milk --init`

   That generates `types.json`

5. Update the entries in `types.json` with a reference to your types

6. Run `$ milk` to generate the code that will go into `src/TypeSerde.re`

7. Write your code that loads in a JSON file with the new code from TypeSerde

   Note that your JSON requires a version eg. `$schemaVersion` that is the same as it is in your `types.json`!

8. Run the code

   You can use this example with `npm run compile` and `npm start`

9. Profit!
