#include "DayList.hpp"

using namespace std;

bool Recur(long current_result, int current_idx, long result_final, const vector<long>& v){
  long r1 = current_result + v[current_idx];
  long r2 = current_result * v[current_idx];
  
  if(current_idx == (int) v.size() - 1){
    if(r1 == result_final || r2 == result_final){
      return true;
    }
    return false;
  } else {
    bool result_r1 = (r1 <= result_final) ? Recur(r1, current_idx + 1, result_final, v) : false;
    bool result_r2 = (r2 <= result_final) ? Recur(r2, current_idx + 1, result_final, v) : false;
    
    return result_r1 || result_r2;
  }
}

bool RecurConcat(long current_result, int current_idx, long result_final, const vector<long>& v){
  int power_of_ten = int(log10(v[current_idx]) + 1);
  
  long r1 = current_result + v[current_idx];
  long r2 = current_result * v[current_idx];
  long r3 = current_result * pow(10, power_of_ten) + v[current_idx];
  
  
  if(current_idx == (int) v.size() - 1){
    if(r1 == result_final || r2 == result_final || r3 == result_final){
      return true;
    }
    return false;
  } else {
    bool result_r1 = (r1 <= result_final) ? RecurConcat(r1, current_idx + 1, result_final, v) : false;
    bool result_r2 = (r2 <= result_final) ? RecurConcat(r2, current_idx + 1, result_final, v) : false;
    bool result_r3 = (r3 <= result_final) ? RecurConcat(r3, current_idx + 1, result_final, v) : false;
    
    return (result_r1 || result_r2 || result_r3);
  }
}

void Day7(ifstream& input_file){
  long total_sum = 0;
  long total_sum_concat = 0;
  
  string line;
  getline(input_file, line);
  while(line != ""){
    stringstream ss(line);
    
    long result, n;
    vector<long> number_list;

    ss >> result;
    ss.get(); // Remove the ':'

    while(ss >> n)
      number_list.push_back(n);
    
    // PART 1
    if(Recur(number_list[0], 1, result, number_list)) total_sum += result;
    // PART 2
    else if(RecurConcat(number_list[0], 1, result, number_list)) total_sum_concat += result;

    getline(input_file, line);
  }
  cout << "Total sum of results with '+' and '*' operations : " << total_sum << '\n';
  cout << "Total sum of results with '+', '*' and '||' operations : " << total_sum + total_sum_concat << '\n';
}
