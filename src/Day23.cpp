#include "DayList.hpp"

using namespace std;

void Day23(ifstream& input_file){  
  set<array<string, 3>> triangle_interconncetions;
  
  vector<unordered_set<string>> interconnection_lists;
  map<string, unordered_set<string>> connections_list;

  
  auto IsInterconnected = [&](unordered_set<string>& interconnection_list, string c1, string c2){
    if(!interconnection_list.count(c1)) return false;
    
    for(const auto& c3 : interconnection_list)
      if(!connections_list[c2].count(c3)) return false;
    
    return true;
  };
  
  int count_start_t = 0;

  string line;
  while(getline(input_file, line)){
    string computer1 = line.substr(0, 2);
    string computer2 = line.substr(3, 2);
    
    connections_list[computer1].insert(computer2);
    connections_list[computer2].insert(computer1);
    
    bool interconnection_created = false;
    
    for(unordered_set<string>& interconnection_list : interconnection_lists){
      if(IsInterconnected(interconnection_list, computer2, computer1)){
        interconnection_list.insert(computer1);
        interconnection_created = true;
        break;
      }
      else if(IsInterconnected(interconnection_list, computer1, computer2)){
        interconnection_list.insert(computer2);
        interconnection_created = true;
        break;
      }
    }
    
    for(const string& computer1_connection : connections_list[computer1]){
      for(const string& computer2_connection : connections_list[computer2]){
        if(computer1_connection == computer2_connection){
          triangle_interconncetions.insert({computer1, computer2, computer1_connection});
          if(!interconnection_created){
            interconnection_lists.push_back({computer1, computer2, computer1_connection});
          }
          if(computer1[0] == 't' || computer2[0] == 't' || computer1_connection[0] == 't'){
            count_start_t++;
          }
          break;
        }
      }
    }
  }
  
  set<string> greatest_connection;
  int max_size = 0;
  for(const unordered_set<string>& connection : interconnection_lists){
    if((int) connection.size() > max_size){
      max_size = (int) connection.size();
      greatest_connection = set<string>(connection.begin(), connection.end());
    }
  }
  
  string password = "";
  for(string computer : greatest_connection){
    if(password != "") password += ',';
    password += computer;
  }
  
  cout << "Number of interconnection starting with a -t : " << count_start_t << '\n';
  cout << "The password to get into the LAN party is : " << password << '\n';
}
