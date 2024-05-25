#ifndef MATCH3_SIMUL_INTEFACE_H
#define MATCH3_SIMUL_INTEFACE_H

#include <cstdint>
#include <cstddef>

namespace match3 {
  constexpr size_t one_second = 1000000ull;
  constexpr size_t fps10 = double(1.0 / 10.0) * one_second;
  constexpr size_t fps30 = double(1.0 / 30.0) * one_second;
  constexpr size_t fps60 = double(1.0 / 60.0) * one_second;
  constexpr size_t fps120 = double(1.0 / 120.0) * one_second;
  constexpr size_t fps144 = double(1.0 / 144.0) * one_second;
  constexpr size_t fps20 = double(1.0 / 20.0) * one_second;

  constexpr double get_second_frac(const size_t val) {
    return double(val) / double(one_second);
  }

  class simul_interface {
  public:
    simul_interface() noexcept = default;
    virtual ~simul_interface() noexcept = default;

    virtual void run() = 0;
    virtual void set_quit(const bool val) = 0;
    virtual void set_frame_time(const size_t val) = 0;
  };
}

#endif