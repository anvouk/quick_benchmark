# quick_benchmark
A simple C/C++ one header file for quick and dirty benchmarking.<br><br>
<i><b>See more examples in the <a href="https://github.com/QwertyQaz414/quick_benchmark/tree/master/examples">example folder.</a></i></b>

## Features
- Less than 200 lines of code.
- Customizable benchmark function.
- Cross-platform.
- No dependencies (No POSIX libraries. Only standard C libraries).
- Extremely easy and quick to use.

## Quick start
```cpp
void multi_param_func(int* v1, float v2, float v3)
{
    /* ... */
}

void no_param_func()
{
    /* ... */
}

void func_version_a(int val)
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
    /* ... */

    BENCHMARK_N(stdout, 1000, multi_param_func, &v1, v2, v3);
    BENCHMARK(no_param_func);

    BENCHMARK_GROUP_BEGIN(stdout, 5, 2000);
        BENCHMARK_GROUP_ADD(func_version_a, 40);
        BENCHMARK_GROUP_ADD(func_version_b, 40);
        BENCHMARK_GROUP_ADD(func_version_c, 40);
        BENCHMARK_GROUP_ADD(func_version_c, 4342);
    BENCHMARK_GROUP_END();
}
```
