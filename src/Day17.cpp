#include "DayList.hpp"

using namespace std;

string GetOutput(vector<pair<int, int>>& instruction_list, long A){
  string output;
  
  long B = 0;
  long C = 0;
  
  long opcode, operand;
  auto combo_operand = [&] {
    if(operand <= 3) return operand;
    else if(operand == 4) return A;
    else if(operand == 5) return B;
    else if(operand == 6) return C;
    else return 0L;
  };
  
  int current_instruction = 0;
  while(current_instruction < instruction_list.size()){
    opcode = instruction_list[current_instruction].first;
    operand = instruction_list[current_instruction].second;
    
    switch (opcode) {
      case 0:
        A >>= combo_operand();
        break;
      case 1:
        B ^= operand;
        break;
      case 2:
        B = combo_operand() % 8;
        break;
      case 3:
        if(A == 0) current_instruction++;
        else current_instruction = (int) operand;
        break;
      case 4:
        B ^= C;
        break;
      case 5:
        if(output != "") output += ',';
        output += (combo_operand() % 8) + '0';
        break;
      case 6:
        B = A >> combo_operand();
        break;
      case 7:
        C = A >> combo_operand();
        break;
      default:
        break;
    }
    if(opcode != 3) current_instruction++;
  }
  return output;
}

void Day17(ifstream& input_file){
    
  string full_file;
  string line;
  
  getline(input_file, line);
  while(!input_file.eof()){
    full_file += line + '\n';
    getline(input_file, line);
  }
  
  regex pattern("Register A: (\\d+)\\nRegister B: 0\\nRegister C: 0\\n\\nProgram: ((?:\\d,)*\\d)");
  
  smatch m;
  regex_search(full_file, m, pattern);
  
  long A = stol(m[1].str());
  string program = m[2].str();
  
  vector<pair<int, int>> instruction_list;
  for(int i = 0; i <= program.size(); i+=4)
    instruction_list.push_back(make_pair(int(program[i] - '0'), int(program[i+2] - '0')));
  
  string initial_output = GetOutput(instruction_list, A);
  
  queue<long> A_queue;
  for(int i = 0; i < 8; i++)
    A_queue.push(i);
    
  long A_copy_program = 0;
  string output;
  
  while(output != program && !A_queue.empty()){
    A_copy_program = A_queue.front();
    A_queue.pop();
    output = GetOutput(instruction_list, A_copy_program);
    if(output == program.substr(program.size() - output.size(), output.size())){
      for(int j = 0; j < 8; j++)
        A_queue.push(8*A_copy_program + j);
    }
  }
  cout << "The initial output of the program is : " << initial_output << '\n';
  cout << "The lowest positive initial value for register A that causes the program to output a copy of itself is : " << A_copy_program << '\n';
}
