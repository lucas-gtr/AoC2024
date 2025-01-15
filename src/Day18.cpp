#include "DayList.hpp"

using namespace std;

void dijkstra_id(int start_y, int start_x, const vector<vector<int>>& id_grid, vector<vector<int>>& distances_id) {
  const int rows = (int) id_grid.size();
  const int cols = (int) id_grid[0].size();
  
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, less<>> pq;
  
  distances_id[start_y][start_x] = id_grid[start_y][start_x];
  pq.emplace(distances_id[start_y][start_x], start_y, start_x);
  
  while (!pq.empty()) {
    auto [current_id, y, x] = pq.top();
    pq.pop();
    
    if (current_id < distances_id[y][x]) continue;
    
    for (const auto& [dir_y, dir_x] : dirs) {
      int new_y = y + dir_y;
      int new_x = x + dir_x;
      
      if (new_y >= 0 && new_y < rows && new_x >= 0 && new_x < cols) {
        int new_id = min(current_id, id_grid[new_y][new_x]);
        
        if (new_id > distances_id[new_y][new_x]) {
          distances_id[new_y][new_x] = new_id;
          pq.emplace(new_id, new_y, new_x);
        }
      }
    }
  }
}

void Day18(ifstream& input_file) {
  const int map_size = 71;
  
  const int bytes = 1024;
  
  vector<string> grid(map_size, string(map_size, '.'));
  vector<vector<int>> id_grid(map_size, vector<int>(map_size, INT_MAX));
  vector<pair<int, int>> id_list;

  char c;
  int x = 0, y = 0;
  int id = 0;
  while(input_file >> x >> c >> y){
    if(c == ','){
      if(id < bytes)
        grid[y][x] = '#';
      id_grid[y][x] = id;
      id_list.push_back(make_pair(y, x));
      
      id++;
    }
  }
  
  queue<pair<int, int>> to_visit;
  to_visit.push({0, 0});
  
  vector<vector<int>> distances(map_size, vector<int>(map_size, INT_MAX));
  distances[0][0] = 0;
  
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  
  int rows = (int) grid.size();
  int cols = (int) grid[0].size();
  
  while (!to_visit.empty()) {
    auto [y, x] = to_visit.front();
    to_visit.pop();
    
    for (const auto& [dir_y, dir_x] : dirs) {
      int new_y = y + dir_y;
      int new_x = x + dir_x;
      
      if (new_y >= 0 && new_y < rows && new_x >= 0 && new_x < cols){
        if(grid[y][x] != '#' && distances[y][x] + 1 < distances[new_y][new_x]) {
          distances[new_y][new_x] = distances[y][x] + 1;
          to_visit.push({new_y, new_x});
        }
      }
    }
  }
      
  vector<vector<int>> distances_id(map_size, vector<int>(map_size, 0));
      
  dijkstra_id(0, 0, id_grid, distances_id);
  
  int min_id = distances_id[map_size - 1][map_size - 1];
  
  y = id_list[min_id].first;
  x = id_list[min_id].second;
  
  cout << "The shortes path to exit is : " << distances[map_size - 1][map_size - 1] << '\n';
  cout << "The first byte that prevents the exit is at position : " << x << "," << y << '\n';
}
