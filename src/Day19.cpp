#include "DayList.hpp"

using namespace std;

struct Node {
  int length;
  std::string sequence;
  std::vector<Node> child_sequences;
};

bool compare_size(string a, string b){
  return a.size() < b.size();
}

void AddNodeToTree(vector<Node>& node_tree, Node& new_node) {
  for (Node& node : node_tree) {
    if (node.sequence == new_node.sequence.substr(0, node.length)) {
      Node* current_node = &node;
      
      bool child_found = false;
      do {
        child_found = false;
        for (Node& child_node : current_node->child_sequences) {
          if (child_node.sequence == new_node.sequence.substr(0, child_node.length)) {
            current_node = &child_node;
            child_found = true;
            break;
          }
        }
      } while (child_found);
      current_node->child_sequences.push_back(new_node);
      return;
    }
  }
  node_tree.push_back(new_node);
}

void FindPatternsInSequence(vector<Node>& node_list, string current_sequence, long possible_ways, string sequence_to_find, map<string, long>& sequences_possibles){
  
  for(Node& node : node_list){
    if(node.sequence == sequence_to_find.substr(0, node.sequence.size())){
      sequences_possibles[current_sequence + node.sequence] += possible_ways;
      if(node.length == (int) sequence_to_find.size()) return;
      
      FindPatternsInSequence(node.child_sequences, current_sequence, possible_ways, sequence_to_find, sequences_possibles);
      return;
    }
  }
}

long CountPossibleSequences(vector<Node>& node_tree, string new_sequence){
  map<string, long> sequences_possibles;
  long count_possible = 0;
  sequences_possibles[""] = 1;
  
  while(!sequences_possibles.empty()){
    string current_sequence = sequences_possibles.begin()->first;
    long possible_ways = sequences_possibles.begin()->second;
    
    sequences_possibles.erase(sequences_possibles.begin());
    
    if(current_sequence.size() >= new_sequence.size()){
      count_possible += possible_ways;
      continue;
    }
    
    string sequence_to_find = new_sequence.substr(current_sequence.size());
    FindPatternsInSequence(node_tree, current_sequence, possible_ways, sequence_to_find, sequences_possibles);
  }
  return count_possible;
}

void Day19(ifstream& input_file){
  vector<string> pattern_list;
  vector<Node> node_tree;
    
  char c;
  string char_sequence;
  
  string line;
  getline(input_file, line);
  for(int i = 0; i <= (int) line.size(); i++){
    c = line[i];
    if(c == ',' || c == '\0'){
      pattern_list.push_back(char_sequence);
      char_sequence = "";
      
      i++; // Enlève l'espace
    }
    else char_sequence += c;
  }
  getline(input_file, line);

  sort(pattern_list.begin(), pattern_list.end(), compare_size);
  for(string& pattern : pattern_list){
    Node node;
    node.sequence = pattern;
    node.length = (int)pattern.size();
    
    AddNodeToTree(node_tree, node);
  }
  int count_possible_design = 0;
  long long count_possible_ways = 0;
  while(getline(input_file, line)){
    long possible_ways = CountPossibleSequences(node_tree, line);
    if(possible_ways){
      count_possible_design++;
      count_possible_ways += possible_ways;
    }
  }
  cout << "Number of possible sequences : " << count_possible_design << '\n';
  cout << "Number of ways of doing one design : " << count_possible_ways << '\n';
}
