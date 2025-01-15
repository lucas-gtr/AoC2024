#include "DayList.hpp"

using namespace std;

long ProcessSecretNumber(long n){
  
  n = ((n*64) ^ n) % 16777216;
  n = ((n/32) ^ n ) % 16777216;
  n = ((n*2048) ^ n ) % 16777216;
  
  return n;
}

void Day22(ifstream& input_file){  
  long secret_number;
  long sum = 0;
  
  int d[4];
  
  int sequence_seen[20][20][20][20];
  long sequence_list[20][20][20][20];
  
  int id = 0;
    
  while (input_file >> secret_number) {
    id++;
    int bananas = secret_number % 10;
    d[0] = bananas;
    int last_bananas = bananas;

    for(int i = 1; i <= 2000; i++){
      secret_number = ProcessSecretNumber(secret_number);
            
      bananas = secret_number % 10;
      d[i%4] = bananas - last_bananas;
      last_bananas = bananas;
      if(i >= 3){
        int i1 = d[(i+1)%4]+10;
        int i2 = d[(i+2)%4]+10;
        int i3 = d[(i+3)%4]+10;
        int i4 = d[i%4]+10;

        if(sequence_seen[i1][i2][i3][i4] != id){
          sequence_list[i1][i2][i3][i4] += bananas;
          sequence_seen[i1][i2][i3][i4] = id;
        }
      }
    }
    sum += secret_number;
  }
  long max_bananas = 0;
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      for(int k = 0; k < 20; k++){
        for(int l = 0; l < 20; l++){
          max_bananas = max(sequence_list[i][j][k][l], max_bananas);
        }
      }
    }
  }
  cout << "The sum of the secrets number after 2000 new secret numbers is : " << sum << '\n';
  cout << "The most bananas you can get is : " << max_bananas << '\n';
}

