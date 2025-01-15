#include "DayList.hpp"

using namespace std;

int GetCheatPathsCount(int y_start, int x_start, const vector<vector<int>>& time_grid, int max_steps){
  
  int start_time = time_grid[y_start][x_start];
  int count_cheat_path = 0;
  
  const int rows = (int) time_grid.size();
  const int cols = (int) time_grid[0].size();

  for(int i = -max_steps; i <= max_steps; i++){
    for(int j = -(max_steps - abs(i)); j <= (max_steps - abs(i)); j++){
      int y = y_start+i;
      int x = x_start+j;
      
      if(y >= 0 && y < rows && x >= 0 && x < cols && time_grid[y][x] != INT_MAX){
        int dist = abs(i) + abs(j);
        if(start_time + dist + 100 <= time_grid[y][x]){
          count_cheat_path++;
        }
      }
    }
  }
  return count_cheat_path;
}


void Day20(ifstream& input_file){  
  vector<string> grid;
  
  pair<int, int> start_position = {0, 0};
  pair<int, int> end_position = {0, 0};
  
  int y = 0;
  
  string line;
  getline(input_file, line);
  while(!input_file.eof()){
    if(start_position == make_pair(0, 0) || end_position == make_pair(0, 0)){
      for(int x = 0; x < (int) line.size(); x++){
        if(line[x] == 'S'){
          start_position = make_pair(y, x);
          line[x] = '.';
          break;
        }
        if(line[x] == 'E'){
          end_position = make_pair(y, x);
          line[x] = '.';
          break;
        }
      }
    }
    grid.push_back(line);
    y++;
    getline(input_file, line);
  }
  
  vector<vector<int>> time_grid((int)grid.size(), vector<int>((int)grid[0].size(), INT_MAX));
  
  queue<pair<int, int>> to_visit;
  to_visit.push(make_pair(start_position.first, start_position.second));
  
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  time_grid[start_position.first][start_position.second] = 0;
  
  int rows = (int) grid.size();
  int cols = (int) grid[0].size();

  while(!to_visit.empty()){
    auto [y, x] = to_visit.front();
    to_visit.pop();
    
    for(auto [dir_y, dir_x] : dirs){
      if(y+dir_y >= 0 && y+dir_y < rows && x+dir_x >= 0 && x+dir_x < cols && grid[y+dir_y][x+dir_x] != '#'){
        if(time_grid[y + dir_y][x + dir_x] > time_grid[y][x] + 1){
          time_grid[y + dir_y][x + dir_x] = time_grid[y][x] + 1;
          to_visit.push(make_pair(y + dir_y, x + dir_x));
        }
      }
    }
  }
  int cheat_paths_2_pico = 0;
  int cheat_paths_20_pico = 0;

  for(y = 0; y < (int) time_grid.size(); y++){
    for(int x = 0; x < (int) time_grid[0].size(); x++){
      if(grid[y][x] == '.'){
        cheat_paths_2_pico += GetCheatPathsCount(y, x, time_grid, 2);
        cheat_paths_20_pico += GetCheatPathsCount(y, x, time_grid, 20);
      }
    }
  }
  cout << "Number of cheat possibles to save at least 100 picoseconds : " << cheat_paths_2_pico << '\n';
  cout << "Number of cheat of 20 picoseconds possibles to save at least 100 picoseconds : " << cheat_paths_20_pico << '\n';
}
