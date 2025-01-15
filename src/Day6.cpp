#include "DayList.hpp"

using namespace std;

int GetDirIndex(int d_y, int d_x) {
  if (d_y == -1) return 0;
  if (d_x == 1) return 1;
  if (d_y == 1) return 2;
  return 3;
}

void Day6(ifstream& input_file){
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  
  vector<string> grid;
  string line;
  
  pair<int, int> start_pos;
  int x = 0, y = 0;
    
  getline(input_file, line);
  while(!input_file.eof()){
    grid.push_back(line);
    
    x = (int) line.find('^');
    if(x != string::npos){
      start_pos = {y, x};
      grid[y][x] = '.';
    }
    y++;
    getline(input_file, line);
  }
  
  const int rows = (int) grid.size();
  const int cols = (int) grid[0].size();
  
  int pos_y = start_pos.first;
  int pos_x = start_pos.second;
  int dir = 0;
    
  vector<pair<int, int>> path = {make_pair(pos_y, pos_x)};
    
  int next_pos_y = pos_y + dirs[dir].first;
  int next_pos_x = pos_x + dirs[dir].second;
  
  while(next_pos_y >= 0 && next_pos_y < rows &&
        next_pos_x >= 0 && next_pos_x < cols){
    if(grid[next_pos_y][next_pos_x] == '#'){
      dir = (dir + 1) % 4;
    } else {
      pos_y = next_pos_y;
      pos_x = next_pos_x;
      path.push_back(make_pair(pos_y, pos_x));
    }
    next_pos_y = pos_y + dirs[dir].first;
    next_pos_x = pos_x + dirs[dir].second;
  }
  
  set<pair<int, int>> visited_positions(path.begin(), path.end());

  // PART 2
  int loop_count = 0;
  
  vector<vector<array<int, 4>>> visited_directions(rows, vector<array<int, 4>>(cols, {-1, -1, -1, -1}));
  
  set<pair<int, int>> obstacle_positions;

  pos_y = start_pos.first;
  pos_x = start_pos.second;
  dir = 0;
  
  next_pos_y = pos_y + dirs[dir].first;
  next_pos_x = pos_x + dirs[dir].second;
  for (int i = 1; i < path.size(); i++) {
    grid[path[i - 1].first][path[i - 1].second] = '.';
    
    if(obstacle_positions.count(path[i])) continue;
    obstacle_positions.insert(path[i]);
    
    next_pos_y = path[i].first;
    next_pos_x = path[i].second;
    
    pos_y = path[i - 1].first;
    pos_x = path[i - 1].second;
    dir = GetDirIndex(next_pos_y - pos_y, next_pos_x - pos_x);
    
    grid[next_pos_y][next_pos_x] = '#';

    while(next_pos_y >= 0 && next_pos_y < rows &&
          next_pos_x >= 0 && next_pos_x < cols){
      if(grid[next_pos_y][next_pos_x] == '#'){
        dir = (dir + 1) % 4;
      } else {
        pos_y = next_pos_y;
        pos_x = next_pos_x;
        int& position_visited_dir = visited_directions[pos_y][pos_x][dir];
        if(position_visited_dir == i){
          loop_count++;
          break;
        } else {
          position_visited_dir = i;
        }
      }
      next_pos_y = pos_y + dirs[dir].first;
      next_pos_x = pos_x + dirs[dir].second;
    }
  }
  cout << "Total cases visited : " << visited_positions.size() << '\n';
  cout << "Total loops possible : " << loop_count << '\n';  
}
