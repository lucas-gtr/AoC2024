#include "DayList.hpp"

using namespace std;

void GetGoodOrder(vector<int>& printing_order, const set<int> (&page_orders)[100]){
  set<int> page_printed;
  
  for(int idx1 = 0; idx1 < printing_order.size(); idx1++){
    int page = printing_order[idx1];
    for(auto page_after : page_orders[page]){
      if(page_printed.count(page_after)){
        auto idx_page = find(printing_order.begin(), printing_order.end(), page_after);
        int idx2 = (int)(idx_page - printing_order.begin());
        swap(printing_order[idx1], printing_order[idx2]);
        
        GetGoodOrder(printing_order, page_orders);
        return;
      }
    }
    page_printed.insert(page);
  }
}

void Day5(ifstream& input_file){
  set<int> page_orders[100];

  int sum_middle_pages = 0, sum_middle_pages_corrected = 0;
  
  auto IsGoodOrder = [&](vector<int> printing_order){
    set<int> page_printed;
    for(auto page : printing_order){
      for(auto page_after : page_orders[page]){
        if(page_printed.count(page_after)){
          return false;
        }
      }
      page_printed.insert(page);
    }
    return true;
  };
  
  string line;
  getline(input_file, line);
  while(line != ""){
    int n1 = 0, n2 = 0;
    char c;
    
    stringstream ss(line);
    ss >> n1 >> c >> n2; // 12|05
    
    page_orders[n1].insert(n2);
    getline(input_file, line);
  }
  
  while(getline(input_file, line)){
    stringstream ss(line);
    vector<int> printing_order;
    
    int n = 0;
    while(ss >> n){
      printing_order.push_back(n);
      ss.get(); // Remove the ','
    }
    
    // PART 1
    if(IsGoodOrder(printing_order))
      sum_middle_pages += printing_order[printing_order.size() / 2];
    // PART 2
    else {
      GetGoodOrder(printing_order, page_orders);
      sum_middle_pages_corrected += printing_order[printing_order.size() / 2];
    }
  }
  cout << "Sum of middle page : " << sum_middle_pages << endl;
  cout << "Sum of middle page corrected : " << sum_middle_pages_corrected << endl;
}
