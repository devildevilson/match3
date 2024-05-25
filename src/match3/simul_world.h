#ifndef MATCH3_SIMUL_WORLD_H
#define MATCH3_SIMUL_WORLD_H

#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>
#include <memory>
#include "simul_interface.h"
#include "utils/core.h"

using namespace devils_engine;

namespace match3 {
// по идее тут мы бы тоже хотели simul_const, что мешает? нужны ли нам атомики?
class simul_world final : public simul_const {
public:
  // сюда надо передать аргументы
  simul_world() noexcept;
  ~simul_world() noexcept;

  void init() override;
  void run_core(const size_t frame_time) override;
  /*void run() override;
  void set_quit(const bool val) override;
  void set_frame_time(const size_t val) override;*/
 private:
  /*bool quit;
  size_t expected_frame_time;
  size_t next_expected_frame_time;*/

  std::unique_ptr<simul_interface> r;
  std::unique_ptr<simul_interface> s;
  std::thread t1;
  std::thread t2;
};
}

#endif