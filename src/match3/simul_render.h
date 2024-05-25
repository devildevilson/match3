#ifndef MATCH3_SIMUL_RENDER_H
#define MATCH3_SIMUL_RENDER_H

#include <mutex>
#include <atomic>
#include <chrono>
#include "simul_interface.h"
#include "utils/core.h"

using namespace devils_engine;

namespace match3 {
class simul_render final : public simul_var {
public:
  simul_render() noexcept;
  void init() override;
  void run_core(const size_t frame_time) override;
private:
  // создадим рендер и обновим expected_frame_time по времени рендера
};
}

#endif