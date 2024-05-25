#ifndef MATCH3_SIMUL_INTEFACE_H
#define MATCH3_SIMUL_INTEFACE_H

#include <cstdint>
#include <cstddef>
#include <atomic>
#include <mutex>

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

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void set_quit(const bool val) = 0;
    virtual void set_frame_time(const size_t val) = 0;
  };

  // тут было бы неплохо разделить на simul_const и simul_var
  // функции во многом сильно повторяются

  class simul_const : public simul_interface {
  public:
    simul_const(const size_t initial_frame_time) noexcept;
    virtual ~simul_const() noexcept = default;

    void run() override;
    void set_quit(const bool val) override;
    void set_frame_time(const size_t val) override;

    virtual void run_core(const size_t frame_time) = 0;
  protected:
    std::atomic_bool quit;
    std::mutex mutex;
    size_t expected_frame_time;
    size_t next_expected_frame_time;
  };

  class simul_var : public simul_interface {
  public:
    simul_var(const size_t initial_frame_time) noexcept;
    virtual ~simul_var() noexcept = default;

    void run() override;
    void set_quit(const bool val) override;
    void set_frame_time(const size_t val) override;

    virtual void run_core(const size_t frame_time) = 0;
  protected:
    std::atomic_bool quit;
    std::mutex mutex;
    size_t expected_frame_time;
    size_t next_expected_frame_time;
  };
}

#endif