#include <quick_benchmark/quick_benchmark.h>

/*-------------------------------------------------------------------------
	functions to benchmark
-------------------------------------------------------------------------*/

NOINLINE
void test_c(int val) {
	val += 256;
}

NOINLINE
void test_asm(int val) {
	__asm {
		add		val, 100h
	}
}

NOINLINE
void test_cpp(int val) {
	val += 256;
}

/*-------------------------------------------------------------------------
	main()
-------------------------------------------------------------------------*/

int main() {
	BENCHMARK_GROUP_START(10, 100);
		BENCHMARK_GROUP_ADD(test_c, 0);
		BENCHMARK_GROUP_ADD(test_asm, 0);
		BENCHMARK_GROUP_ADD(test_cpp, 0);
	BENCHMARK_GROUP_END();
	getchar();
}