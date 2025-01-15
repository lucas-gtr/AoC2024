#include "DayList.hpp"

using namespace std;

long long FillGates(map<string, int>& gates_input, map<string, array<string, 3>> gates_operation){
  bool operation_made = true;
  
  long z_result = 0;
  
  while(operation_made){
    operation_made = false;
    
    for(auto [gate, operation] : gates_operation){
      
      string gate_operand_1 = operation[0];
      string gate_operand_2 = operation[1];
      
      if(gates_input.count(gate_operand_1) && gates_input.count(gate_operand_2) && !gates_input.count(gate)){
        operation_made = true;
        
        int value_operand_1 = gates_input[gate_operand_1];
        int value_operand_2 = gates_input[gate_operand_2];
        
        if(operation[2] == "AND")
          gates_input[gate] = value_operand_1 & value_operand_2;
        else if(operation[2] == "OR")
          gates_input[gate] = value_operand_1 | value_operand_2;
        else if(operation[2] == "XOR")
          gates_input[gate] = value_operand_1 ^ value_operand_2;
        
        if(gate[0] == 'z' && gates_input[gate] == 1){
          z_result += pow(2, stoi(gate.substr(1, 2)));
        }
      }
    }
  }
  return z_result;
}

void DisplayOperation(string gate, map<string, array<string, 3>> gates_operation, int current_depth, int max_depth=5){
  current_depth++;
  cout << gate << " = " << gates_operation[gate][0] << " " << gates_operation[gate][2] << " " << gates_operation[gate][1] << '\n';
  if(gates_operation[gate][0][0] != 'x' && gates_operation[gate][0][0] != 'y' && current_depth <= max_depth){
    for(int i = 0; i < current_depth; i++) cout << "  ";
    DisplayOperation(gates_operation[gate][0], gates_operation, current_depth);
  }
  if(gates_operation[gate][1][0] != 'x' && gates_operation[gate][1][0] != 'y' && current_depth <= max_depth){
    for(int i = 0; i < current_depth; i++) cout << "  ";
    DisplayOperation(gates_operation[gate][1], gates_operation, current_depth);
  }
}

void SwapKey(map<string, array<std::string, 3>>& gates_operation, string key1, string key2){
  array<string, 3> temp = gates_operation[key2];
  gates_operation[key2] = gates_operation[key1];
  gates_operation[key1] = temp;
}

void Day24(ifstream& input_file){  
  regex gates_pattern("([a-z0-9]{3}): ([0-1])");
  
  map<string, int> gates_value;
  map<string, array<string, 3>> gates_operations;
  
  long long x_result = 0;
  long long y_result = 0;
  long long z_result = 0;

  string line;
  getline(input_file, line);
  while(line != ""){
    smatch m;
    regex_search(line, m, gates_pattern);
    
    string gate_name = m[1].str();
    int gate_value = stoi(m[2].str());
    gates_value[gate_name] = gate_value;
    
    if(gate_name[0] == 'x' && gate_value == 1){
      x_result += pow(2, stoi(gate_name.substr(1, 2)));
    }
    if(gate_name[0] == 'y' && gate_value == 1){
      y_result += pow(2, stoi(gate_name.substr(1, 2)));
    }
        
    getline(input_file, line);
  }
  
  regex operations_pattern("([a-z0-9]{3}) ([A-Z]{2,3}) ([a-z0-9]{3}) -> ([a-z0-9]{3})");
  
  getline(input_file, line);
  while(!input_file.eof()){
    smatch m;
    regex_search(line, m, operations_pattern);
    
    string gate_operand_1 = m[1].str();
    string operator_name = m[2].str();
    string gate_operand_2 = m[3].str();
    string gate_result = m[4].str();
    
    gates_operations[gate_result] = {gate_operand_1, gate_operand_2, operator_name};
    getline(input_file, line);
  }
  
  map<string, int> gates_inputs = gates_value;

  z_result = FillGates(gates_value, gates_operations);

  cout << "The binary number formed by the z gates is : " << z_result << '\n';
  
  SwapKey(gates_operations, "z14", "hbk");
  SwapKey(gates_operations, "z18", "kvn");
  SwapKey(gates_operations, "dbb", "z23");
  SwapKey(gates_operations, "cvh", "tfn");
  
  cout << "The eight wires involved in a swap are : cvh,dbb,hbk,kvn,tfn,z14,z18,z23" << '\n';
  
}
