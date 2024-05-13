#include <atomic>
#include <fstream>

#include <fastema/fastema.hpp>
#include <nanobench.h>

#include "vanilla_ema.hpp"

namespace bench
{

static constexpr uint32_t NUM_ITER = 1000000;

template<typename EMAType>
void benchmark_ema(const char* desc, EMAType& ema, const auto& values)
{
  std::ofstream out {std::string(desc) + ".json"};
  ankerl::nanobench::Bench()
      .minEpochIterations(NUM_ITER)
      .run(desc,
           [&]
           {
             for (const auto& value : values) {
               auto result = ema(value);
               ankerl::nanobench::doNotOptimizeAway(result);
             }
           })
      .render(ankerl::nanobench::templates::pyperf(), out);
}

}  // namespace bench

int main()
{
  std::vector<std::uint8_t>  input_values_uint8 = {100, 50, 100, 0};
  std::vector<std::uint16_t> input_values_uint16 = {100, 50, 100, 0};
  std::vector<std::uint32_t> input_values_uint32 = {100, 50, 100, 0};
  std::vector<double>        input_values_double = {100, 50, 100, 0};

  std::vector<std::int8_t>  input_values_int8 = {100, 50, 100, 0};
  std::vector<std::int16_t> input_values_int16 = {100, 50, 100, 0};
  std::vector<std::int32_t> input_values_int32 = {100, 50, 100, 0};

  // Unsigned filters -- expected fastest
  EMA<3, std::uint8_t>  ema_filter_uint8(100);
  EMA<3, std::uint16_t> ema_filter_uint16(100);
  EMA<3, std::uint32_t> ema_filter_uint32(100);

  // Double filter, expected slowest
  bench::SimpleEMA simple_ema_filter(100.0, 0.125);

  // Signed filters -- ???

  EMA<3, std::int8_t>  ema_filter_int8(100);
  EMA<3, std::int16_t> ema_filter_int16(100);
  EMA<3, std::int32_t> ema_filter_int32(100);

  bench::benchmark_ema("ema-filter-uint8", ema_filter_uint8, input_values_uint8);
  bench::benchmark_ema("ema-filter-uint16", ema_filter_uint16, input_values_uint16);
  bench::benchmark_ema("ema-filter-uint32", ema_filter_uint32, input_values_uint32);

  bench::benchmark_ema("simple-ema-filter", simple_ema_filter, input_values_double);

  bench::benchmark_ema("ema-filter-int8", ema_filter_int8, input_values_int8);
  bench::benchmark_ema("ema-filter-int16", ema_filter_int16, input_values_int16);
  bench::benchmark_ema("ema-filter-int32", ema_filter_int32, input_values_int32);
}