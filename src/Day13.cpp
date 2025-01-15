#include "DayList.hpp"

using namespace std;

pair<long, long> GetCoeffs(string machine_string, long offset = 0){
  regex reg_expr_mul("Button A: X\\+(\\d+), Y\\+(\\d+)\\nButton B: X\\+(\\d+), Y\\+(\\d+)\\nPrize: X=(\\d+), Y=(\\d+)");
  
  smatch m;
  regex_search(machine_string, m, reg_expr_mul);
  
  long x1 = stol(m[1].str()), y1 = stol(m[2].str());
  long x2 = stol(m[3].str()), y2 = stol(m[4].str());
  long X = stol(m[5].str()) + offset, Y = stol(m[6].str()) + offset;
  
  if(x1*y2 != x2*y1){
    long a = (X*y2 - Y*x2) / (x1*y2 - x2*y1);
    long b = (Y*x1 - X*y1) / (x1*y2 - x2*y1);
    if(a * x1 + b * x2 == X && a * y1 + b * y2 == Y)
      return make_pair(a, b);
  }
  return make_pair(0, 0);
}

void Day13(ifstream& input_file) {
  long tokens_count = 0;
  long tokens_count_offset = 0;

  string line;
  getline(input_file, line);
  while(!input_file.eof()){
    string machine_string;
    
    while(line != "") {
      machine_string += line + '\n';
      getline(input_file, line);
    }
    // PART 1
    pair<long, long> coeffs = GetCoeffs(machine_string);
    tokens_count += 3 * coeffs.first + coeffs.second;
    
    // PART 2
    pair<long, long> coeffs_offset = GetCoeffs(machine_string, 10000000000000);
    tokens_count_offset += 3 * coeffs_offset.first + coeffs_offset.second;
    
    getline(input_file, line);
  }
  cout << "Total tokens : " << tokens_count << endl;  
  cout << "Total tokens with 10000000000000 offset : " << tokens_count_offset << endl;
}
