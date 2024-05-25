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
class simul_sound : public simul_interface {
public:
  simul_sound() noexcept;
  void run() override;
  void set_quit(const bool val) override;
  void set_frame_time(const size_t val) override;

  // здесь добавим несколько функций для sound::system
 private:
  std::atomic_bool quit;
  std::mutex mutex;
  size_t expected_frame_time;
  size_t next_expected_frame_time;

  sound::system system;
};
}

#endif