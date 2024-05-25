#include "simul_render.h"

namespace match3 {
simul_render::simul_render() noexcept : quit(false), expected_frame_time(fps144), next_expected_frame_time(fps144) {}

void simul_render::run() {
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
      // тут мы пройдем рендер и начнем наверное копирование данных
      // после чего ждать по идее не имеет смысла
      // в случае интерфейса его нужно считать вне а затем засунуть сюда
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

void simul_render::set_quit(const bool val) { quit = val; }
void simul_render::set_frame_time(const size_t val) {
  std::unique_lock<std::mutex> lock(mutex);
  next_expected_frame_time = val;
}
}