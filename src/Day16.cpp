#include "DayList.hpp"

using namespace std;

void GetMinimumScores(int start_y, int start_x, const vector<string>& grid, vector<vector<array<int, 4>>>& scores) {
  scores[start_y][start_x][0] = 0;
  queue<array<int, 4>> q;
  q.push({start_y, start_x, 0, 0});
  
  vector<pair<int, int>> dirs = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
  
  while (!q.empty()) {
    auto [y, x, dir, score] = q.front();
    q.pop();
        
    if (score + 1000 < scores[y][x][(dir+1)%4]){
      scores[y][x][(dir+1)%4] = score + 1000;
      q.push({y, x, (dir+1)%4, score + 1000});
    }
    
    if (score + 1000 < scores[y][x][(dir+3)%4]){
      scores[y][x][(dir+3)%4] = score + 1000;
      q.push({y, x, (dir+3)%4, score + 1000});
    }
    
    int new_y = y + dirs[dir].first;
    int new_x = x + dirs[dir].second;

    if (grid[new_y][new_x] != '#'){
      if (score + 1 < scores[new_y][new_x][dir]){
        scores[new_y][new_x][dir] = score + 1;
        q.push({new_y, new_x, dir, score+1});
      }
    }
  }
}

bool CountTilesToEnd(array<int, 4> state, array<int, 4>& end_state, const vector<vector<array<int, 4>>>& scores, set<pair<int, int>>& path, vector<pair<int, int>>& dirs){
  if(state == end_state){
    return true;
  }
    
  bool reach_end = false;
  auto [y, x, dir, score] = state;
  
  if (score + 1000 == scores[y][x][(dir+1)%4]){
    if(CountTilesToEnd({y, x, (dir+1)%4, score + 1000}, end_state, scores, path, dirs)) reach_end = true;
  }
  
  if (score + 1000 == scores[y][x][(dir+3)%4]){
    if(CountTilesToEnd({y, x, (dir+3)%4, score + 1000}, end_state, scores, path, dirs)) reach_end = true;
  }
  
  int new_y = y + dirs[dir].first;
  int new_x = x + dirs[dir].second;
  
  if (score + 1 == scores[new_y][new_x][dir]){
    if(CountTilesToEnd({new_y, new_x, dir, score + 1}, end_state, scores, path, dirs)) reach_end = true;
    if(reach_end) {
      path.insert(make_pair(y, x));
    }
  }
  
  return reach_end;
  
}

void Day16(ifstream& input_file){  
  vector<string> grid;
  vector<vector<array<int, 4>>> scores;

  string line;
  
  int y = 0;
  
  int start_x = 0, start_y = 0;
  int end_x = 0, end_y = 0;
  
  getline(input_file, line);
  while(!input_file.eof()){
    grid.push_back(line);
    if(!(start_x && start_y && end_x && end_y)){
      for(int i = 0; i < (int) line.size(); i++){
        if(line[i]  == 'S'){
          start_x = i;
          start_y = y;
          line[i] = '.';
        } else if(line[i] == 'E'){
          end_x = i;
          end_y = y;
          line[i] = '.';
        }
      }
    }
    y++;
    getline(input_file, line);
  }
    
  int grid_height = (int) grid.size();
  int grid_width = (int) grid[0].size();
  
  scores = vector<vector<array<int, 4>>>(grid_height, vector<array<int, 4>>(grid_width, {INT_MAX, INT_MAX, INT_MAX, INT_MAX}));
  
  array<int, 4> start_state = {start_y, start_x, 0, 0};
  array<int, 4> end_state = {end_y, end_x, 0, INT_MAX};
  
  GetMinimumScores(start_y, start_x, grid, scores);
  
  for(int i = 0; i < 4; i++)
    if(scores[end_y][end_x][i] < end_state[3]){
      end_state[2] = i;
      end_state[3] = scores[end_y][end_x][i];
    }
  
  vector<pair<int, int>> dirs = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
  vector<vector<bool>> visited = vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size(), false));
    
  set<pair<int, int>> path = {make_pair(start_y, start_x), make_pair(end_y, end_x)};
  CountTilesToEnd(start_state, end_state, scores, path, dirs);
  
  cout << "Score to reach the end " << end_state[3] << '\n';
  cout << "Tiles for best path " << path.size() << '\n';
}
