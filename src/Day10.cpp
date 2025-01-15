#include "DayList.hpp"

using namespace std;

void CheckNeighboors(int y, int x, vector<string>& grid, vector<pair<int, int>>& end_locations){
  char n = (grid[y][x]);
      
  if(n == '9'){
    end_locations.push_back(make_pair(y, x));
    return;
  }
  
  const int rows = (int) grid.size();
  const int cols = (int) grid[0].size();
  
  auto IsInside = [&](int _y, int _x){
    return (_y >= 0 && _y < rows && _x >= 0 && _x < cols);
  };
  
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
  for(auto [dir_y, dir_x] : dirs){
    int y2 = y + dir_y;
    int x2 = x + dir_x;
    if(IsInside(y2, x2))
      if((grid[y2][x2]) == n + 1)
        CheckNeighboors(y2, x2, grid, end_locations);
  }
}

void Day10(ifstream& input_file){  
  vector<string> grid;
  string line;
  
  int score = 0;
  int rate = 0;
    
  getline(input_file, line);
  while(!input_file.eof()) {
    grid.push_back(line);
    getline(input_file, line);
  }
  
  const int grid_height = (int) grid.size();
  const int grid_width = (int) grid[0].size();
    
  for(int y = 0; y < grid_height; y++){
    for(int x = 0; x < grid_width; x++){
      if(grid[y][x] == '0'){
        vector<pair<int, int>> end_locations;
        CheckNeighboors(y, x, grid, end_locations);
        set<pair<int, int>> unique_end_locations(end_locations.begin(), end_locations.end());
        
        // PART 1
        score += (int) unique_end_locations.size();
        // PART 2
        rate += (int) end_locations.size();
      }
    }
  }
  cout << "Totam sum of scores : " << score << endl;
  cout << "Totam sum of rating : " << rate << endl;
}
