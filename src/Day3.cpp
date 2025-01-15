#include "DayList.hpp"

using namespace std;

int GetMulResults(const string& line, const regex& pattern) {
  int sum_mul = 0;
  sregex_iterator iter(line.begin(), line.end(), pattern);
  
  bool enable = true;
  for (; iter != sregex_iterator(); ++iter) {
    smatch match = *iter;
    if (match[0] == "do()") {
      enable = true;
    } else if (match[0] == "don't()") {
      enable = false;
    } else if (enable) {
      sum_mul += stoi(match[1].str()) * stoi(match[2].str());
    }
  }
  return sum_mul;
}

void Day3(ifstream& input_file) {
  string file_string;
    
  int total_sum = 0;
  int total_sum_activation = 0;

  string line;
  while(!input_file.eof()){
    getline(input_file, line);
    file_string += line;
  }
  
  // PART 1
  const regex pattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
  total_sum = GetMulResults(file_string, pattern);

  // PART 2
  const regex pattern_activation("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|do\\(\\)|don't\\(\\)");
  total_sum_activation = GetMulResults(file_string, pattern_activation);
  
  cout << "Total sum mul : " << total_sum << '\n';
  cout << "Total sum mul with activations : " << total_sum_activation << '\n';
}
