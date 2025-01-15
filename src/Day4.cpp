#include "DayList.hpp"

using namespace std;

void Day4(ifstream& input_file){  
  vector<string> file_string;

  string line;  
  while(getline(input_file, line))
    file_string.push_back(line);
  
  int grid_height = (int) file_string.size();
  int grid_width = (int) file_string[0].size();
  
  auto IsXmas = [](const string& str_xmas){
    return (str_xmas == "XMAS" || str_xmas == "SAMX");
  };
  
  auto IsXmasCross = [](const string& str_cross){
    return (str_cross == "MMSS" || str_cross == "MSMS" || str_cross == "SSMM" || str_cross == "SMSM");
  };
  
  int xmas_count = 0;
  int xmas_cross_count = 0;

  // PART 1
  for(int y = 0; y < grid_height; y++){
    for(int x = 0; x < grid_width; x++){
      if(file_string[y][x] == 'X' || file_string[y][x] == 'S'){
        char xmas[5];
        xmas[4] = '\0';
        if(x+3 < grid_width){
          for(int c = 0; c < 4; c++) xmas[c] = file_string[y][x+c];
          if(IsXmas(string(xmas))) xmas_count++;
        }
        if(y+3 < grid_height){
          for(int c = 0; c < 4; c++) xmas[c] = file_string[y+c][x];
          if(IsXmas(string(xmas))) xmas_count++;
        }
        if(x+3 < grid_width && y+3 < grid_height){
          for(int c = 0; c < 4; c++) xmas[c] = file_string[y+c][x+c];
          if(IsXmas(string(xmas))) xmas_count++;
        }
        if(x+3 < grid_width && y-3 >= 0){
          for(int c = 0; c < 4; c++) xmas[c] = file_string[y-c][x+c];
          if(IsXmas(string(xmas))) xmas_count++;
        }
      }
      // PART 2
      else if(file_string[y][x] == 'A'){
        if (y > 0 && y < grid_height - 1 && x > 0 && x < grid_width - 1){
          char cross[5];
          cross[0] = file_string[y - 1][x - 1];
          cross[1] = file_string[y - 1][x + 1];
          cross[2] = file_string[y + 1][x - 1];
          cross[3] = file_string[y + 1][x + 1];
          cross[4] = '\0';
          if(IsXmasCross(string(cross))) xmas_cross_count++;
        }
      }
    }
  }
  
  cout << "Count of XMAS word : " << xmas_count << endl;
  cout << "Count of X-MAS : " << xmas_cross_count << endl;
}
