#include <benchmark/benchmark.h>

import std;
import CowString;

namespace sea_jackal
{
namespace
{

void StringSizes(benchmark::internal::Benchmark *benchmark)
{
    for (const auto size : {0, 8, 15, 16, 23, 24, 64, 1024, 65536, 1048576})
    {
        benchmark->Arg(size);
    }
}

template <typename String>
void Copy(benchmark::State &state)
{
    const String source(
        std::string(static_cast<std::size_t>(state.range(0)), 'x'));
    for (auto _ : state)
    {
        String copy(source);
        benchmark::DoNotOptimize(copy);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_TEMPLATE(Copy, CowString)->Apply(StringSizes);
BENCHMARK_TEMPLATE(Copy, std::string)->Apply(StringSizes);

} // namespace
} // namespace sea_jackal
