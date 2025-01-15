#include "DayList.hpp"

using namespace std;

void Day1(ifstream& input_file){
  vector<int> c1, c2;
  int x, y;
  
  while(input_file >> x >> y){
    c1.push_back(x);
    c2.push_back(y);
  }
  
  // PART 1
  long sum_distances = 0;
  
  sort(c1.begin(), c1.end());
  sort(c2.begin(), c2.end());

  for(size_t i = 0; i < c1.size(); i++)
    sum_distances += abs(c1[i] - c2[i]);
    
  // PART 2
  long similarity = 0;
  
  map<int, int> freq;
  for(int n : c2){
    freq[n]++;
  }
  
  for(int n : c1)
    similarity += n * freq[n];

  cout << "Sum of distances : " << sum_distances << '\n';
  cout << "Similarity score : " << similarity << '\n';
}
