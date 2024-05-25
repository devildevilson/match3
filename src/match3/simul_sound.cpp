#include "simul_sound.h"

namespace match3 {
simul_sound::simul_sound() noexcept : simul_const(fps10) {}
void simul_sound::init() {}
void simul_sound::run_core(const size_t frame_time) {
  system.update(frame_time);
}
}