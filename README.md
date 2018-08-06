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
void test_a(int* v1, float v2, float v3)
{
	/* ... */
}

void test_b()
{
    /* ... */
}

void test_c1(int val)
{
    /* ... */
}

void test_c2(int val)
{
    /* ... */
}

void test_c3(int val)
{
    /* ... */
}

int main()
{
	/* ... */

    BENCHMARK_N(stdout, 1000, test_a, &v1, v2, v3);
    BENCHMARK(test_b);

    BENCHMARK_GROUP_BEGIN(stdout, 5, 2000);
        BENCHMARK_GROUP_ADD(test_c1, 40);
        BENCHMARK_GROUP_ADD(test_c2, 40);
        BENCHMARK_GROUP_ADD(test_c3, 40);
        BENCHMARK_GROUP_ADD(test_c3, 4342);
    BENCHMARK_GROUP_END();
}
```
