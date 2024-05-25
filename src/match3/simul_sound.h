#ifndef MATCH3_SIMUL_SOUND_H
#define MATCH3_SIMUL_SOUND_H

#include <mutex>
#include <atomic>
#include <chrono>
#include "simul_interface.h"
#include "utils/core.h"
#include "sound/system.h"

using namespace devils_engine;

namespace match3 {
class simul_sound final : public simul_const {
public:
  simul_sound() noexcept;
  void init() override;
  void run_core(const size_t frame_time) override;

  // здесь добавим несколько функций для sound::system
 private:
  sound::system system;
};
}

#endif