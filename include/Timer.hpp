#pragma once

#include <sys/time.h>

class Timer {
private:
  static long start_time;

public:
  static void StartTimer(){
    timeval time_start;
    gettimeofday(&time_start, NULL);
    start_time = (time_start.tv_sec * 10'000) + (time_start.tv_usec / 100);
  }
  static void StopTimer(){
    timeval time_end;
    gettimeofday(&time_end, NULL);
    long end_time = (time_end.tv_sec * 10'000) + (time_end.tv_usec / 100);

    std::cout << "Finished in " << (end_time - start_time) / 10.0 << " ms\n";
  }
};
