#pragma once

#include <chrono>
#include <iostream>
#include <string>


namespace pal {

// TODO: Add user time and system time.
class Timer {
public:
  Timer() {
    start_ = std::chrono::steady_clock::now();
  }

  void finish(const std::string& operation) {
    const auto finish = std::chrono::steady_clock::now();
    const double time_sec = (finish - start_) / std::chrono::milliseconds(1) / 1000.;
    std::cout << "Timer: " << operation << " took " << time_sec << " seconds\n";
    start_ = finish;
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
};


class ScopedTimer {
public:
  ScopedTimer(std::string operation) : operation_(std::move(operation)) {}
  ~ScopedTimer() {
    timer_.finish(operation_);
  }

private:
  Timer timer_;
  std::string operation_;
};

}  // namespace pal
