# quick_benchmark
A simple C/C++ one header only library for benchmarking

## Quick start
```cpp
void test(int val)
{
    val += 256;
}

int main()
{
    // Benchmark over 150 calls of test(10) and print the result to stdout.
    BENCHMARK_N(stdout, 150, test, 10);
    
    // Just like before but this time iterates over 1000 function calls.
    BENCHMARK(test, 10);
}
```

## Benchmark groups of functions
```cpp
MSVC_NOINLINE void test_a(int val) GCC_NOINLINE
{
    val -= 256;
}

MSVC_NOINLINE void test_b(int val) GCC_NOINLINE
{
    val += val;
}

MSVC_NOINLINE void test_c(int val) GCC_NOINLINE
{
    val *= val;
}

int main()
{
    // Every function is benchmarked against 2000 iterations for 5 times.
    BENCHMARK_GROUP_START(stdout, 5, 2000);
        BENCHMARK_GROUP_ADD(test_a, -10);
        BENCHMARK_GROUP_ADD(test_b, 20);
        BENCHMARK_GROUP_ADD(test_b, 200);
        BENCHMARK_GROUP_ADD(test_c, 40);
    BENCHMARK_GROUP_END();
}
```
