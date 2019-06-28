***DEPRECATED:*** improved version available [here](https://github.com/QwertyQaz414/anv)

# quick_benchmark
A simple C/C++ one header file for quick and dirty benchmarking.<br><br>
<i><b>See more examples in the <a href="https://github.com/QwertyQaz414/quick_benchmark/tree/master/examples">example folder.</a></i></b>

## Features
- Less than 200 lines of code in 1 header file.
- Customizable benchmark function (default is rdtsc).
- Cross-platform.
- No dependencies (No POSIX libraries. Only standard C libraries).
- Extremely easy and quick to use.

## Quick start

### Simple benchmark
```cpp
void my_func(int a, int b, int c)
{
    /* ... */
}

int main()
{
    /* benchmark my_func(10, 23, 50) */
    BENCHMARK(my_func, 10, 23, 50);
}
```

### Group benchmark
```cpp
void func_version_a(int val, int val2)
{
    /* ... */
}

void func_version_b(int val)
{
    /* ... */
}

void func_version_c(int val)
{
    /* ... */
}

int main()
{
    /* every function gets benchmarked over 2000 iterations for 5 times */
    BENCHMARK_GROUP_BEGIN(stdout, 5, 2000);
        BENCHMARK_GROUP_ADD(func_version_a, 40, 52);
        BENCHMARK_GROUP_ADD(func_version_b, 40);
        BENCHMARK_GROUP_ADD(func_version_c, 40);
        BENCHMARK_GROUP_ADD(func_version_c, 4342);
    BENCHMARK_GROUP_END();
}
```
