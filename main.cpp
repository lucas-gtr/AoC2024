#include "DayList.hpp"

long Timer::start_time = 0;

int main(int argc, char* argv[]) {
  std::cout << "ADVENT OF CODE" << std::endl;
  
  std::string input_file_path = "Ressources/input_day";
  
  if (argc > 1) {
    input_file_path = argv[1];
    std::cout << "Using input files from: " << input_file_path << '\n';
  } else {
    std::cout << "Invalid input. Please specify the directory and the input file name prefix." << '\n';
    return 1;
  }
  
  int day_to_solve;
  
  while (true) {
    std::cout << "Enter the day to solve (1-25, 0 for all days): ";
    std::cin >> day_to_solve;
    
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    
    if (day_to_solve >= 0 && day_to_solve <= 25) {
      break;
    } else {
      std::cout << "Invalid day. Please enter a number between 0 and 25." << std::endl;
    }
  }
  
  if (day_to_solve == 0) {
    for (int i = 1; i <= 25; i++) {
      Day(i, input_file_path);
    }
  } else {
    Day(day_to_solve, input_file_path);
  }
  
  return 0;
}
