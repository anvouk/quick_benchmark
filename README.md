# quick_benchmark
A simple C/C++ one header only library for benchmarking

## Quick start
```cpp
void test(int val) {
    val += 256;
}

int main() {
    BENCHMARK(test, 10); // calls test(10)
}
```

## Benchmark groups of functions
```cpp
void test_c(int val) {
    val += 256;
}

void test_asm(int val) {
    __asm {
        add     val, 100h
    }
}

int main() {
    BENCHMARK_GROUP_START(10, 100); // benchmarks on 100 calls and for 10 times
        BENCHMARK_GROUP_ADD(test_c, 0);
        BENCHMARK_GROUP_ADD(test_asm, 0);
    BENCHMARK_GROUP_END();
}
```
