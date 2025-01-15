#include "DayList.hpp"

void Day(int i, const std::string& input_file_path) {
  static const std::vector<std::function<void(std::ifstream&)>> days = {
    Day1,
    Day2,
    Day3,
    Day4,
    Day5,
    Day6,
    Day7,
    Day8,
    Day9,
    Day10,
    Day11,
    Day12,
    Day13,
    Day14,
    Day15,
    Day16,
    Day17,
    Day18,
    Day19,
    Day20,
    Day21,
    Day22,
    Day23,
    Day24,
    Day25
  };
  
  if (i >= 1 && i <= days.size()) {
    Timer::StartTimer();
    std::cout << "------- DAY " << i << " -------" << '\n';
    std::ifstream input_file(input_file_path + std::to_string(i));
    if(!input_file.is_open()){
      std::cerr << "Error opening file: " << input_file_path + std::to_string(i) << '\n';
      return;
    }
    days[i - 1](input_file);
    Timer::StopTimer();
    std::cout << '\n';
  } else {
    std::cout << "Day " << i << " not implemented yet.\n";
  }
}
