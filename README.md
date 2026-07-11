# Exercise Logger

A terminal-based C++ workout logger. Create workouts, log exercises with reps and
weight, and keep your history across sessions with JSON persistence.

This was my first project built entirely from scratch — not filling in `.cpp` files
inside a pre-made environment, but setting up the build system, project structure, and
file persistence myself. It's complete as a portfolio piece; the project now continues
as a React Native mobile app (see [Where it went next](#where-it-went-next)).

## Features

**Workouts**
- Create workouts with a name, date, and length
- Edit and delete existing workouts
- View all logged workouts

**Exercises**
- Add exercises with reps and weight
- Add exercises to workouts that already exist

**Persistence**
- Auto-save and load from JSON, so history survives between runs

## Build & Run

Requires g++ with C++17 support.

```
make logger
./logger
```

## Dependencies

- g++ with C++17 support
- [nlohmann/json](https://github.com/nlohmann/json) — download `json.hpp` and place it
  in a `nlohmann/` folder in the project root

## Project Structure

```
exercise-logger/
├── src/        # Source files
├── include/    # Header files
├── data/       # workouts.json is saved here
├── nlohmann/   # json.hpp goes here
└── Makefile
```

## How it was built

I built this in two passes. **V1** was the core loop: a `Workouts` container holding a
`vector` of `Exercise` objects, the create / add / view flow, and JSON save-and-load so
nothing was lost between sessions. **V2** added the editing surface — editing and
deleting workouts, adding exercises to workouts that already existed, and cleaning up
how everything displayed.

The real point wasn't the logger itself. My CS coursework always handed me a working
project skeleton where I only filled in the logic. This was the first time I owned
everything *around* the code: deciding what to build, breaking it into pieces, setting
up a Makefile and folder layout from nothing, wiring in a third-party JSON library, and
debugging all of it myself.

## Where it went next

Once the terminal version did everything I'd set out to build, I migrated the project to
a mobile app — so it'd be something I'd actually use day to day, and so I could learn a
new stack. That version lives in a separate repo,
[exercise-logger-mobile](https://github.com/bmcox2/exercise-logger-mobile), rebuilt in
React Native / Expo with TypeScript and SQLite. This C++ version stays as the finished
first chapter.
