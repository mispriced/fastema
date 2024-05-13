#pragma once
#include <cstdint>
#include <limits>
#include <type_traits>

// Returns the next larger type, one step up from T
template<class T>
struct size_up
{
  using type = std::conditional_t<
      sizeof(T) == 1,
      std::uint16_t,
      std::conditional_t<sizeof(T) == 2, std::uint32_t, std::conditional_t<sizeof(T) == 4, std::uint64_t, void>>>;
};

template<uint8_t K, class input_t>
class EMA
{
public:
  using state_t = typename size_up<std::make_unsigned_t<input_t>>::type;

  static_assert(!std::is_same<state_t, void>::value,
                "Unsupported input type. Supported types: int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t");

  static_assert(K + sizeof(input_t) * 8 <= sizeof(state_t) * 8,
                "State type is too small to hold the filter constant K and input type");

  EMA(input_t initial = input_t {0}) { reset(initial); }

  void reset(input_t initial)
  {
    state_t initial_s = static_cast<state_t>(initial);
    _state = zero + (initial_s << K) - initial_s;
  }

  input_t operator()(input_t input)
  {
    _state += static_cast<state_t>(input);
    state_t output = (_state + half) >> K;
    output -= zero >> K;
    _state -= output;
    return static_cast<input_t>(output);
  }

  constexpr static state_t max_state = std::numeric_limits<state_t>::max();
  constexpr static state_t half_state = max_state / 2 + 1;
  constexpr static state_t zero = std::is_unsigned<input_t>::value ? state_t {0} : half_state;
  constexpr static state_t half = K > 0 ? state_t {1} << (K - 1) : state_t {0};

private:
  state_t _state;
};