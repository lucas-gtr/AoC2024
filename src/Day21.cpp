#include "DayList.hpp"

using namespace std;

map<string, long long> cache[27];

map<char, pair<int, int>> numeric_pad = {
  {'7', make_pair(0, 0)}, {'8', make_pair(0, 1)}, {'9', make_pair(0, 2)},
  {'4', make_pair(1, 0)}, {'5', make_pair(1, 1)}, {'6', make_pair(1, 2)},
  {'1', make_pair(2, 0)}, {'2', make_pair(2, 1)}, {'3', make_pair(2, 2)},
  {'0', make_pair(3, 1)}, {'A', make_pair(3, 2)}
};

map<char, pair<int, int>> arrow_pad = {
  {'^', make_pair(0, 1)}, {'A', make_pair(0, 2)},
  {'<', make_pair(1, 0)}, {'v', make_pair(1, 1)}, {'>', make_pair(1, 2)}
};

map<pair<int, int>, char> dirs = {
  {make_pair(-1, 0), '^'},
  {make_pair(0, 1), '>'},
  {make_pair(1, 0), 'v'},
  {make_pair(0, -1), '<'}
};

long long GetSequenceLength(string sequence, int pad_left, map<char, pair<int, int>>& pad, int y_empty, int x_empty){
  long long& length = cache[pad_left][sequence];
  
  if(length) return length;
  if(pad_left == 0) return length = sequence.size();
  
  int from_y = pad['A'].first;
  int from_x = pad['A'].second;
  
  for(char c : sequence){
    string short_sequene = "";
    
    int to_y = pad[c].first;
    int to_x = pad[c].second;
    
    pair<int, int> distance = make_pair(to_y - from_y, to_x - from_x);
    
    int y_move = (distance.first > 0) - (distance.first < 0);
    int x_move = (distance.second > 0) - (distance.second < 0);
    
    if((from_y == y_empty && to_x == x_empty) || (x_move == 1 && (to_y != y_empty || from_x != x_empty))){
      short_sequene += string(abs(distance.first), dirs[make_pair(y_move, 0)]);
      short_sequene += string(abs(distance.second), dirs[make_pair(0, x_move)]);
    }
    else {
      short_sequene += string(abs(distance.second), dirs[make_pair(0, x_move)]);
      short_sequene += string(abs(distance.first), dirs[make_pair(y_move, 0)]);
    }
    
    short_sequene += 'A';
    from_y = to_y;
    from_x = to_x;
    length += GetSequenceLength(short_sequene, pad_left - 1, arrow_pad, 0, 0);
  }
  
  return length;
}

void Day21(ifstream& input_file) {
  string sequence;
  
  long long sum_sequences_2_pad = 0;
  long long sum_sequences_25_pad = 0;

  while(getline(input_file, sequence)) {
    long long sequence_length_2_pad = GetSequenceLength(sequence, 3, numeric_pad, 3, 0);
    long long sequence_length_25_pad = GetSequenceLength(sequence, 26, numeric_pad, 3, 0);
    
    int numerical_part = stoi(sequence.substr(0, 3));
    sum_sequences_2_pad += sequence_length_2_pad * numerical_part;
    sum_sequences_25_pad += sequence_length_25_pad * numerical_part;
  }
  
  cout << "The sum of the complexities with 2 pads is : " << sum_sequences_2_pad << '\n';
  cout << "The sum of the complexities with 25 pads is : " << sum_sequences_25_pad << '\n';
}
