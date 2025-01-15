#include "DayList.hpp"

using namespace std;

void Day8(ifstream& input_file){
  map<char, vector<pair<int, int>>> antenna_list;
    
  int map_width = 0, map_height = 0;

  char c;
  int y = 0;
    
  string line;
  while(getline(input_file, line)) {
    map_width = (int) line.size();
    for (int x = 0; x < map_width; ++x) {
      c = line[x];
      if (c != '.') {
        antenna_list[c].push_back({y, x});
      }
    }
    y++;
  }
  map_height = y;
  
  auto IsInside = [&](int _x, int _y){
    return (_y >= 0 && _x < map_height && _x >= 0 && _y < map_width);
  };
  
  set<pair<int, int>> antinode_locations;
  set<pair<int, int>> antinode_locations_harmonics;
  
  int y1, x1, y2, x2;
  int loc_y, loc_x;
  
  int h = 0;
    
  for(const auto& [_, positions] : antenna_list){
    for(int i = 0; i < (int) positions.size(); i++){
      for(int j = 0; j < (int) positions.size(); j++){
        if(i == j) continue;
        
        y1 = positions[i].first;
        x1 = positions[i].second;
        y2 = positions[j].first;
        x2 = positions[j].second;
        
        loc_y = y2;
        loc_x = x2;

        h = 0;

        while(IsInside(loc_y, loc_x)){
          // PART 1
          if(h == 1)
            antinode_locations.insert(make_pair(loc_y, loc_x));
          // PART 2
          antinode_locations_harmonics.insert(make_pair(loc_y, loc_x));
          
          h++;
          loc_y += y2 - y1;
          loc_x += x2 - x1;
        }
      }
    }
  }
  cout << "Total number of unique antinodes : " << antinode_locations.size() << '\n';
  cout << "Total number of unique antinodes with harmonics : " << antinode_locations_harmonics.size() << '\n';
}
