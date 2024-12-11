# My attempt at [Advent Of Code](https://adventofcode.com/2024/) 2024 in C

## Requirements
- C compiler
- CMake and your default build system config out eg: Makefile, Ninja, etc...

## Building
```bash
cmake -Bbuild ./
```
- Builds and prints instructions on how to run/show results of days

## Running
```bash
cmake --build ./build -t day1
```
- This assumes you are trying to show results for day1
- For other days just do `day[the_day]` and for the second part just add a .5, eg: `day2.5` is answer for day 2 part 2.
