# Snake

## Requirements

- [Emscripten](https://emscripten.org/)

## Building

[Setup Emscripten](https://emscripten.org/docs/getting_started/downloads.html) and then run the following command in the _src/Snake_ directory:

    emcc --bind -o ./public/index.js snake.cc food.cc snake_body_part.cc character_batch.cc random.cc snake_game.cc -s ASYNCIFY

Now you should have _index.js_ and _index.wasm_ in the _src/Snake/public_ directory. To be able to play the game you need a web server to serve the static files inside the folder.
