#include "DayList.hpp"

using namespace std;

bool PushBlock(int y, int x, int dir_y, int dir_x, vector<string>& grid){
  char& next_c = grid[y+dir_y][x+dir_x];
  char& c = grid[y][x];
  
  bool push_blocks;
  switch (next_c) {
    case '.':
      push_blocks = true;
      break;
    case '#':
      push_blocks = false;
      break;
    default:
      push_blocks = PushBlock(y+dir_y, x+dir_x, dir_y, dir_x, grid);
      break;
  }
  if(push_blocks){
    next_c = c;
    grid[y][x] = '.';
  }
  return push_blocks;
}
bool CanPushWideBlock(int y, int x, int dir_y, int dir_x, const vector<string>& wide_grid){
  char next_c = wide_grid[y+dir_y][x+dir_x];
  
  if(next_c == '.') return true;
  else if(next_c == '#') return false;
  else if(dir_x) return CanPushWideBlock(y, x+dir_x, 0, dir_x, wide_grid);
  else if (next_c == '[')
    return (CanPushWideBlock(y + dir_y, x, dir_y, 0, wide_grid) &&
            CanPushWideBlock(y + dir_y, x + 1,  dir_y, 0, wide_grid));
  else if(next_c == ']')
    return (CanPushWideBlock(y + dir_y, x, dir_y, 0, wide_grid) &&
            CanPushWideBlock(y + dir_y, x - 1, dir_y, 0, wide_grid));
  
  assert(false);
}

void PushWideBlock(int y, int x, int dir_y, int dir_x, vector<string>& wide_grid){
  char& c = wide_grid[y][x];
  char& next_c = wide_grid[y+dir_y][x+dir_x];
  
  if(dir_y){
    if(next_c == '['){
      PushWideBlock(y+dir_y, x, dir_y, dir_x, wide_grid);
      PushWideBlock(y+dir_y, x+1, dir_y, dir_x, wide_grid);
    } else if(next_c == ']'){
      PushWideBlock(y+dir_y, x, dir_y, dir_x, wide_grid);
      PushWideBlock(y+dir_y, x-1, dir_y, dir_x, wide_grid);
    }
  } else {
    if(next_c == '[' || next_c == ']') PushWideBlock(y, x+dir_x, dir_y, dir_x, wide_grid);
  }
  next_c = c;
  c = '.';
}

void Day15(ifstream& input_file) {  
  vector<string> grid;
  vector<string> wide_grid;
  
  long sum_position = 0;
  long sum_wide_position = 0;
  
  int grid_width = 0, grid_height = 0;
  int wide_grid_width = 0, wide_grid_height = 0;
  
  int x = 0, y = 0;
  int x_wide = 0, y_wide = 0;
  
  int dir_x, dir_y;
  char c;
    
  map<char, pair<int, int>> dirs = {
    {'^', make_pair(-1, 0)},
    {'>', make_pair(0, 1)},
    {'v', make_pair(1, 0)},
    {'<', make_pair(0, -1)}
  };
  
  string line;
  string wide_line;
  getline(input_file, line);
  while(!input_file.eof()){
    if(line[0] == '#'){
      grid_width = (int) line.size();
      wide_line = "";
      for(int i = 0; i < grid_width; i++){
        if(line[i] == '@'){
          x = i;
          y = grid_height;
          
          y_wide = grid_height;
          x_wide = 2*i;
          
          line[i] = '.';
          wide_line += "..";
        }
        else if(line[i] == '#'){
          wide_line += "##";
        } else if(line[i] == 'O'){
          wide_line += "[]";
        } else if(line[i] == '.'){
          wide_line += "..";
        }
      }
      grid_height++;
      wide_grid_height++;
      wide_grid_width = (int) wide_line.size();
      
      grid.push_back(line);
      wide_grid.push_back(wide_line);
    } else if(line != ""){
      int line_size = (int) line.size();
      // PART 1
      for(int i = 0; i < line_size; i++){
        dir_y = dirs[line[i]].first;
        dir_x = dirs[line[i]].second;
                
        if(PushBlock(y, x, dir_y, dir_x, grid)){
          y += dir_y;
          x += dir_x;
        }
        // PART 2
        c = wide_grid[y_wide+dir_y][x_wide+dir_x];
        if(c == '.'){
          y_wide += dir_y;
          x_wide += dir_x;
        } else if (c == '[' || c == ']'){
          if(CanPushWideBlock(y_wide, x_wide, dir_y, dir_x, wide_grid)){
            PushWideBlock(y_wide, x_wide, dir_y, dir_x, wide_grid);
            y_wide += dir_y;
            x_wide += dir_x;
          }
        }
      }
    }
    getline(input_file, line);
  }
  
  for(int i = 0; i < grid_height; i++)
    for(int j = 0; j < grid_width; j++)
      if(grid[i][j] == 'O') sum_position += 100*i + j;

  for(int i = 0; i < wide_grid_height; i++)
    for(int j = 0; j < wide_grid_width; j++)
      if(wide_grid[i][j] == '[') sum_wide_position += 100*i + j;
  
  cout << "Sum of boxes positions : " << sum_position << '\n';
  cout << "Sum of boxes positions (wide grid) : " << sum_wide_position << '\n';
}
