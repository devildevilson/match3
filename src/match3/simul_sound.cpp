#include "simul_sound.h"

namespace match3 {
simul_sound::simul_sound() noexcept : quit(false), expected_frame_time(fps10), next_expected_frame_time(fps10) {}
void simul_sound::run() {
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
      system.update(frame_time);
    }

    counter += 1;

    const auto sleep_time = std::chrono::steady_clock::now();
    const size_t sleep = std::chrono::duration_cast<std::chrono::microseconds>(
                             sleep_time - current_time)
                             .count();
    utils::print("sound ", counter, " a ", time_accumulator, " sleep ", sleep,
                 "\n");
    if (time_accumulator > sleep) {
      std::this_thread::sleep_for(
          std::chrono::microseconds(time_accumulator - sleep));
      expected_frame_time = next_expected_frame_time;
    }
  }
}

void simul_sound::set_quit(const bool val) { quit = val; }
void simul_sound::set_frame_time(const size_t val) {
  std::unique_lock<std::mutex> lock(mutex);
  next_expected_frame_time = val;
}
}