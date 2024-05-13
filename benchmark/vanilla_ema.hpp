#pragma once
#include <cmath>

namespace bench
{

class SimpleEMA
{
public:
  SimpleEMA(double initial = 0.0, double alpha_ = 0.1)
      : value(initial)
      , alpha(alpha_)
  {
  }

  void reset(double initial) { value = initial; }

  double operator()(double input)
  {
    value = smooth(value, input, alpha);
    return value;
  }

  [[always_inline]] [[nodiscard]] static double smooth(double curr, double new_value, double a)
  {
    return std::isnan(curr) ? new_value : curr * (1 - a) + new_value * a;
  }

private:
  double value;
  double alpha;
};

}  // namespace bench