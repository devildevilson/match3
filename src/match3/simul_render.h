#ifndef MATCH3_SIMUL_RENDER_H
#define MATCH3_SIMUL_RENDER_H

#include <mutex>
#include <atomic>
#include <chrono>
#include "simul_interface.h"
#include "utils/core.h"

using namespace devils_engine;

namespace match3 {
class simul_render : public simul_interface {
public:
  simul_render() noexcept;
  void run() override;
  void set_quit(const bool val) override;
  void set_frame_time(const size_t val) override;
private:
  std::atomic_bool quit;
  std::mutex mutex;  // главный мьютекс чтобы перекинуть сюда данные
  size_t expected_frame_time;
  size_t next_expected_frame_time;
  
  // создадим рендер и обновим expected_frame_time по времени рендера
};
}

#endif