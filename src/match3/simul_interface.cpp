#include "simul_interface.h"
#include "utils/core.h"

using namespace devils_engine;

namespace match3 {
simul_const::simul_const(const size_t initial_frame_time) noexcept : quit(false), expected_frame_time(initial_frame_time), next_expected_frame_time(initial_frame_time) {}
void simul_const::run() {
  size_t counter = 0;
  size_t last_accumulator = 0;
  size_t time_accumulator = 0;
  const auto current_time = std::chrono::steady_clock::now();
  while (!quit) {
    last_accumulator = time_accumulator;
    time_accumulator += expected_frame_time;
    const size_t frame_time = expected_frame_time;  // константа
    const double frac = get_second_frac(frame_time);

    {
      std::unique_lock<std::mutex> lock(mutex);
      run_core(frame_time);
    }

    counter += 1;

    const auto sleep_time = std::chrono::steady_clock::now();
    const size_t sleep = std::chrono::duration_cast<std::chrono::microseconds>(sleep_time - current_time).count();
    utils::println("sound ", counter, " a ", time_accumulator, " sleep ", sleep, "\n");
    if (time_accumulator > sleep) {
      std::this_thread::sleep_for(std::chrono::microseconds(time_accumulator - sleep));
      expected_frame_time = next_expected_frame_time;
    }
  }
}

void simul_const::set_quit(const bool val) { quit = val; }
void simul_const::set_frame_time(const size_t val) {
  std::unique_lock<std::mutex> lock(mutex);
  next_expected_frame_time = val;
}

simul_var::simul_var(const size_t initial_frame_time) noexcept : quit(false), expected_frame_time(initial_frame_time), next_expected_frame_time(initial_frame_time) {}
void simul_var::run() {
  size_t counter = 0;
  size_t full_accumulator = 0;
  auto current_time = std::chrono::steady_clock::now();
  while (!quit) {
    const auto new_time = std::chrono::steady_clock::now();
    // frame_time не константное как в других системах, скорее всего нужно
    // сделать массив и считать среднее
    size_t frame_time = std::chrono::duration_cast<std::chrono::microseconds>(new_time - current_time).count();
    frame_time = std::min(frame_time, 250000ull);
    current_time = new_time;
    full_accumulator += frame_time;

    {
      std::unique_lock<std::mutex> lock(mutex);
      run_core(frame_time);
    }
    counter += 1;

    utils::print("render ", counter, " a ", full_accumulator, "\n");
    const auto sleep_time = std::chrono::steady_clock::now();
    const size_t sleep = std::chrono::duration_cast<std::chrono::microseconds>(sleep_time - new_time).count();
    if (expected_frame_time > sleep) {
      std::this_thread::sleep_for(std::chrono::microseconds(expected_frame_time - sleep));
      expected_frame_time = next_expected_frame_time;
    }
  }
}
void simul_var::set_quit(const bool val) { quit = val; }
void simul_var::set_frame_time(const size_t val) {
  std::unique_lock<std::mutex> lock(mutex);
  next_expected_frame_time = val;
}
}