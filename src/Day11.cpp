#include "DayList.hpp"

using namespace std;

long GetStoneCount(long stone_number, int blink_left, map<pair<int, int>, long>& memo){
  long& result = memo[{stone_number, blink_left}];
  if(result) return result;
  if(blink_left == 0) return 1;
  if(stone_number == 0) return result = GetStoneCount(1, blink_left - 1, memo);
  
  int number_count = (int)log10(stone_number) + 1 % 2;
  if(number_count % 2 == 0){
    int pow_ten = pow(10, number_count / 2);
    
    int first_half = (int)(stone_number / pow_ten);
    int second_half = (int) stone_number - (first_half * pow_ten);
    
    return result = GetStoneCount(first_half, blink_left - 1, memo) +
    GetStoneCount(second_half, blink_left - 1, memo);
  }
  return result = GetStoneCount(stone_number * 2024, blink_left - 1, memo);
}

void Day11(ifstream& input_file){  
  long stone_number;
  
  long total_count_25_blinks = 0;
  long long total_count_75_blinks = 0;
  
  map<pair<int, int>, long> memo;
  while (input_file >> stone_number) {
    // PART 1
    total_count_25_blinks += GetStoneCount(stone_number, 25, memo);
    // PART 2
    total_count_75_blinks += GetStoneCount(stone_number, 75, memo);
  }
  
  cout << "Stone count after 25 blinks : " << total_count_25_blinks << endl;
  cout << "Stone count after 75 blinks : " << total_count_75_blinks << endl;
}
