#include "DayList.hpp"

using namespace std;

bool IsGoodReport(const vector<int>& report){
  bool increasing = true;
  bool decreasing = true;
  
  for(int i = 0; i < report.size() - 1; i++){
    int diff = report[i+1] - report[i];
    
    if(diff < 0) increasing = false;
    else if(diff > 0) decreasing = false;
    
    if(!(1 <= abs(diff) && abs(diff) <= 3)) return false;
  }
  return (increasing || decreasing);
}

void Day2(std::ifstream& input_file){
  long good_reports = 0;
  long good_reports_corrected = 0;
  
  string line;
  while (getline(input_file, line)){
    vector<int> report;
    stringstream ss(line);
    int n;
    while (ss >> n) {
      report.push_back(n);
    }
    // PART 1
    if(IsGoodReport(report)) good_reports++;
    // PART 2
    else{
      for(size_t i = 0; i < report.size(); i++){
        vector<int> report_corrected = report;
        report_corrected.erase(report_corrected.begin() + i);
        if(IsGoodReport(report_corrected)){
          good_reports_corrected++;
          break;
        }
      }
    }
  }
  cout << "Number of good reports : " << good_reports << '\n';
  cout << "Number of good reports corrected : " << good_reports + good_reports_corrected << '\n';
}
