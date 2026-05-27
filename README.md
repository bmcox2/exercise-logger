# Exercise Logger

A terminal-based C++ workout logger. Create workouts, log exercises with reps 
and weight, and persist your data across sessions using JSON.

## Dependencies

- g++ with C++17 support
- [nlohmann/json](https://github.com/nlohmann/json) — download `json.hpp` and 
place it in a `nlohmann/` folder in the project root

## Build & Run
make logger
./logger

## Project Structure
exercise-logger/  
src/          # Source files  
include/      # Header files  
data/         # workouts.json saved here  
nlohmann/     # json.hpp goes here  
Makefile  

## V1 Features

- Create workouts with name, date, and length
- Add exercises with reps and weight
- View all logged workouts
- Auto-save and load from JSON

## V2 Planned

- Edit existing workouts
- Delete workouts
- Add exercises to existing workouts
- Improved display and filtering
