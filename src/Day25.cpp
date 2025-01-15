#include "DayList.hpp"

using namespace std;

void Day25(ifstream& input_file){
  vector<array<int, 5>> lockers;
  vector<array<int, 5>> keys;
  
  int pair_keys_lockers = 0;
  
  string line;
  do {
    array<int, 5> grid = {0, 0, 0, 0, 0};
    for(int i = 0; i < 7; i++){
      getline(input_file, line);
      for(int j = 0; j < 5; j++){
        if(line[j] == '#') grid[j]++;
      }
    }
    if(line[0] == '#') keys.push_back(grid); // keys last line starts with '#'
    else lockers.push_back(grid);
  } while(getline(input_file, line));
  
  for(const auto& locker : lockers){
    for(const auto& key : keys){
      bool is_fitting = true;
      for(int n = 0; n < 5; n++){
        if(key[n] + locker[n] > 7){
          is_fitting = false;
          break;
        }
      }
      if(is_fitting) pair_keys_lockers++;
    }
  }
  cout << "The number of pair key/lock who fit together without overlapping is : " << pair_keys_lockers << '\n';
}
