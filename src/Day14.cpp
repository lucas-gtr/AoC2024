#include "DayList.hpp"

using namespace std;

void Day14(ifstream& input_file){
  const int tile_width = 101;
  const int tile_height = 103;
  
  int quarters_count[4] = {0, 0, 0, 0};
  auto GetQuarter = [&](int px, int py, int vx, int vy, int seconds){
    int px2 = ((px + seconds * vx) % tile_width + tile_width) % tile_width;
    int py2 = ((py + seconds * vy) % tile_height + tile_height) % tile_height;
    
    if(py2 < tile_height / 2){
      if(px2 < tile_width / 2) quarters_count[0]++;
      if(px2 > tile_width / 2) quarters_count[1]++;
    }
    if(py2 > tile_height/ 2){
      if(px2 < tile_width / 2) quarters_count[2]++;
      if(px2 > tile_width / 2) quarters_count[3]++;
    }
  };
  
  vector<pair<int, int>> pos, velocity;
  
  regex pattern("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");

  string line;
  getline(input_file, line);
  while(!input_file.eof()){
    int px, py, vx, vy;
        
    smatch m;
    regex_search(line, m, pattern);
        
    px = stoi(m[1].str());
    py = stoi(m[2].str());
    
    vx = stoi(m[3].str());
    vy = stoi(m[4].str());
    
    pos.push_back(make_pair(px, py));
    velocity.push_back(make_pair(vx, vy));
    // PART 1
    GetQuarter(px, py, vx, vy, 100);
    
    getline(input_file, line);
  }
  long multiplication_count = quarters_count[0] * quarters_count[1] * quarters_count[2] * quarters_count[3];

  // PART 2
  const int symetric_threshold = 60;
  int seconds = 0;
  int symetric_count = 0;
  while (symetric_count < symetric_threshold) {
    vector<string> grid(tile_height, string(tile_width, ' '));

    seconds++;
    symetric_count = 0;
    
    for(int i = 0; i < (int)pos.size(); i++){
      int& x = pos[i].first;
      int& y = pos[i].second;
      
      x += velocity[i].first;
      x = ((x % tile_width) + tile_width) % tile_width;
      
      y += velocity[i].second;
      y = ((y % tile_height) + tile_height) % tile_height;
      grid[y][x] = 'X';
      if(grid[tile_height-1-y][x] == 'X'){
        symetric_count++;
      }
    }
  }
  cout << "Multiplication of robots per quarter after 100 seconds : " << multiplication_count << '\n';
  cout << "Appartion of christams tree after " << seconds << " seconds" << '\n';
}
