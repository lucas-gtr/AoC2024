#include "DayList.hpp"

using namespace std;

void VisitCase(int y, int x, const vector<string>& grid, vector<vector<bool>>& visited, int& area, int& perimeter, int& corners){
  char region = grid[y][x];
  
  visited[y][x] = true;
  area++;
  
  const int rows = (int) grid.size();
  const int cols = (int) grid[0].size();
  
  auto IsInside = [&](int _y, int _x){
    return (_y>= 0 && _y < rows && _x >= 0 && _x < cols);
  };
  
  auto IsInRegion = [&](pair<int, int> dir){
    int new_y = y + dir.first;
    int new_x = x + dir.second;
    return (IsInside(new_y, new_x) && grid[new_y][new_x] == region);
  };
  
  const pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
  for(int i = 0; i < 4; i++){
    pair<int, int> dir1 = dirs[i];
    pair<int, int> dir2 = dirs[(i+1)%4];
    
    // Count corners
    if(!IsInRegion(dir1) && !IsInRegion(dir2))
      corners++;
    else if(IsInRegion(dir1) && IsInRegion(dir2) && !IsInRegion(make_pair(dir1.first + dir2.first, dir1.second + dir2.second)))
      corners++;
    
    int new_y = y + dir1.first;
    int new_x = x + dir1.second;
    
    if(!IsInside(new_y, new_x) || grid[new_y][new_x] != region) perimeter++;
    else if(!visited[new_y][new_x])
      VisitCase(new_y, new_x, grid, visited, area, perimeter, corners);
  }
}


void Day12(ifstream& input_file){
  vector<string> grid;
  string line;
  
  long total_price_perimeter = 0;
  long total_price_sides = 0;

  getline(input_file, line);
  while(!input_file.eof()){
    grid.push_back(line);
    getline(input_file, line);
  }
  
  const int rows = (int) grid.size();
  const int cols = (int) grid[0].size();
  
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  
  for(int y = 0; y < rows; y++){
    for(int x = 0; x < cols; x++){
      if(!visited[y][x]){
        int area = 0, perimeter = 0, corners = 0;
        VisitCase(y, x, grid, visited, area, perimeter, corners);
        // PART 1
        total_price_perimeter += area * perimeter;
        // PART 2
        total_price_sides += area * corners;
      }
    }
  }
  cout << "Total price of hences (with perimeter) : " << total_price_perimeter << endl;
  cout << "Total price of hences (with sides) : " << total_price_sides << endl;
}
