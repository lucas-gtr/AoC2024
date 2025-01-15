#include "DayList.hpp"

using namespace std;

void Day9(ifstream& input_file){
  struct FileBlock{
    int ID;
    int pos;
    int size;
  };
  
  vector<FileBlock> block_list;
  
  string line;
  getline(input_file, line);
  
  long sum_position_id = 0;
  long sum_position_id_p2 = 0;
  
  int pos = 0;
  for(int i = 0; i < (int) line.size(); i++){
    int block_size = (line[i] - '0');
    if(i % 2 == 0){
      FileBlock block;
      block.ID = i / 2;
      block.size = block_size;
      block.pos = pos;
      
      if(block_size != 0)
        block_list.push_back(block);
    }
    pos += block_size;
  }
  
  vector<FileBlock> block_list_p2 = block_list;

  // PART 1
  for(int i = 0; i < (int) block_list.size() - 1; i++){
    FileBlock block = block_list[i];
    sum_position_id += block.ID * (block.size / 2.0) * (2 * block.pos + block.size - 1);
  
    int p1 = block.pos + block.size;
    int p2 = block_list[i+1].pos;
    
    int gap = p2 - p1;
    if(gap > 0){
      FileBlock new_block = block_list.back();
      new_block.pos = p1;
      block_list.back().size -= gap;
      
      if(block_list.back().size <= 0)
        block_list.pop_back();
      else new_block.size = gap;
      
      block_list.insert(block_list.begin() + i + 1, new_block);
    }
  }
  // PART 2
  vector<set<int>> gap_position(10);

  for(int j = 0; j < (int) block_list_p2.size() - 1; j++){
    int pos1 = block_list_p2[j].pos + block_list_p2[j].size;
    int pos2 = block_list_p2[j+1].pos;
    int gap = pos2 - pos1;
    if(gap > 0)
      gap_position[gap].insert(pos1);
  }
    
  while(!block_list_p2.empty()){
    FileBlock last_block = block_list_p2.back();
    block_list_p2.pop_back();
    
    int gap_needed = last_block.size;
    
    int first_pos = INT_MAX;
    int gap_taken = -1;

    for (int i = gap_needed; i < (int) gap_position.size(); i++) {
      if (!gap_position[i].empty()) {
        int pos = *(gap_position[i].begin());
        if (pos < first_pos) {
          first_pos = pos;
          gap_taken = i;
        }
      }
    }
    
    if (gap_taken != -1) {
      gap_position[gap_taken].erase(gap_position[gap_taken].begin());
    }
    
    first_pos = min(first_pos, last_block.pos);
        
    sum_position_id_p2 += last_block.ID * (last_block.size / 2.0) * (2 * first_pos + last_block.size - 1);
    
    int new_gap_created = gap_taken - last_block.size;
    if (first_pos != last_block.pos && new_gap_created > 0) {
      gap_position[new_gap_created].insert(first_pos + last_block.size);
    }
  }
  cout << "Sum of ID multiplied by position : " << sum_position_id << '\n';
  cout << "Sum of ID multiplied by position (P2) : " << sum_position_id_p2 << '\n';
}
