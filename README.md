# Advent Of Code

This project is an implementation of the **Advent of Code 2024** puzzles in C++.

## Features
- Solve puzzles for each day (1 to 25).
- Execute a specific day or run all days in a single command.
- Requires your own input file specifying the input directory and the file prefix.

## Instructions

### Prerequisites
- A compiler supporting C++17.
- CMake version 3.16 or higher.

### Build and Run
1. Clone the project:
   git clone https://github.com/lucas-gtr/AoC2024.git
   cd AoC2024

2. Configure the project with CMake:
   cmake -S . -B build

3. Build the project:
   cmake --build build

4. Run the program:
   ./build/AdventOfCode [input_directory/prefix]

   You **must** provide the directory and file prefix as an argument to the program. For example:
   ./build/AdventOfCode InputFiles/input_day

   This will allow the program to locate files named `InputFiles/input_day1`, `InputFiles/input_day2`, ..., up to `InputFiles/input_day25`.

### Usage
When running, the program will prompt you to:
- **Enter a specific day** (1 to 25) to solve a particular puzzle.
- **Enter 0** to solve all puzzles.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
