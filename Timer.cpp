#include "Timer.h"

#define DEBUG 1 // 1 to turn debug on

Timer::Timer(){
  if(DEBUG) std::cerr << "Called Timer::Timer() [default constructor]" << std::endl;
  started = false;
  ended = false;

}

void Timer::reset(void){
  started = false;
  ended = false;

}

void Timer::start(void){
  if(!started && !ended){
    start_time = std::chrono::high_resolution_clock::now();
    started = true;
  }
  else if(started){
    std::cerr << "Timer: trying to start timer, but timer already started!" << std::endl;
    exit(EXIT_FAILURE);
  }
  else if(ended){
    std::cerr << "Timer: trying to start timer, but timer ended already!" << std::endl;
    exit(EXIT_FAILURE);
  }
  
}

void Timer::end(void){
  if(started && !ended){
    end_time = std::chrono::high_resolution_clock::now();
    ended = true;
  }
  else if(!started){
    std::cerr << "Timer: trying to end timer, but timer hasn't started yet!" << std::endl;
    exit(EXIT_FAILURE);
  }
  else if(ended){
    std::cerr << "Timer: trying to end timer, but timer already ended!" << std::endl;
    exit(EXIT_FAILURE);
  }
  
}

double Timer::elapsedSeconds(void){
  std::chrono::seconds dur = std::chrono::duration_cast<std::chrono::seconds> (end_time - start_time);

  return dur.count();
}

double Timer::elapsedMicro(void){
  std::chrono::microseconds dur = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time);

  return dur.count();
}

void Timer::printElapsedSeconds(std::ostream &out){
  std::streamsize prec = out.std::ios_base::precision();
  out << std::fixed << std::setprecision(7) << elapsedMicro()/1000000.0 << std::endl;
  out.unsetf(std::ios_base::fixed);
  out.precision(prec);
}

Timer::~Timer(){
  if(DEBUG) std::cerr << "Called Timer::Timer() [destructor]" << std::endl;

}
