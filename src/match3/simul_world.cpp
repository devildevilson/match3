#include "simul_world.h"
#include "simul_sound.h"
#include "simul_render.h"

namespace match3 {
simul_world::simul_world() noexcept : 
  simul_const(fps20),
  r(new simul_render),
  s(new simul_sound),
  t1([this]() { this->r->run(); }),
  t2([this]() { this->s->run(); }) 
{}

simul_world::~simul_world() noexcept {
  r->set_quit(true);
  s->set_quit(true);
  t1.join();
  t2.join();
}

void simul_world::init() {}
void simul_world::run_core(const size_t frame_time) {
  std::this_thread::sleep_for(std::chrono::microseconds(100));
}

//void simul_world::run() {
//  size_t counter = 0;
//  size_t time_accumulator = 0;
//  const auto current_time = std::chrono::steady_clock::now();
//  while (!quit) {
//    time_accumulator += expected_frame_time;
//    size_t frame_time = expected_frame_time;  // константа
//
//    // тут запускаем вход интерфейса + обновляем буферы с интерфейсом
//    std::this_thread::sleep_for(std::chrono::microseconds(100));
//    counter += 1;
//
//    //copy_data();  // поди копируем мы все таки тут
//
//    utils::println("simul ", counter, " a ", time_accumulator);
//
//    const auto sleep_time = std::chrono::steady_clock::now();
//    const size_t sleep = std::chrono::duration_cast<std::chrono::microseconds>(sleep_time - current_time).count();
//    if (time_accumulator > sleep) {
//      std::this_thread::sleep_for(std::chrono::microseconds(time_accumulator - sleep));
//      expected_frame_time = next_expected_frame_time;
//    } else {
//      // страдает производительность
//    }
//  }
//}
//
//void simul_world::set_quit(const bool val) { quit = val; }
//void simul_world::set_frame_time(const size_t val) {
//  //std::unique_lock<std::mutex> lock(mutex);
//  next_expected_frame_time = val;
//}
}