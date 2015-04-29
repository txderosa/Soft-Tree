#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <iomanip>
#include <chrono>

class Timer{

 private:
  std::chrono::high_resolution_clock clock;
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point end_time;
  bool started;
  bool ended;

 public:
  Timer();
  
  void reset(void);
  void start(void);
  void end(void);
  double elapsedSeconds(void);
  double elapsedMicro(void);

  void printElapsedSeconds(std::ostream &out);

  ~Timer();

}; // end of class Timer

#endif
