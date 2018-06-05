/*
 * The MIT License
 *
 * Copyright 2018 Andrea Vouk.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <quick_benchmark/quick_benchmark.h>

#include <math.h>

/*------------------------------------------------------------------------------
	functions to benchmark
------------------------------------------------------------------------------*/

MSVC_NOINLINE void test_multi_param(int v1, int v2, unsigned v3) GCC_NOINLINE
{
	v1 += (int)pow(2, v2 * v3);
	v1 *= (int)sqrt(v2 / (v3 + 1));
}

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

MSVC_NOINLINE void test_d() GCC_NOINLINE
{
	int val = 100;
	val = (int)pow(2, 10 + sqrt(val));
}

/*------------------------------------------------------------------------------
	BENCHMARK() usage
------------------------------------------------------------------------------*/

void benchmark_usage()
{
	puts("\n/// BENCHMARK() usage ///\n");

	BENCHMARK_N(stdout, 10, test_multi_param, 30, 56, 120);
	BENCHMARK_N(stdout, 20, test_multi_param, 1, 560, 23);
	BENCHMARK_N(stdout, 30, test_multi_param, -45, 1000, 99);

	puts("");

	BENCHMARK(test_multi_param, 30, 56, 120);
	BENCHMARK(test_multi_param, 1, 560, 23);
	BENCHMARK(test_multi_param, -45, 1000, 99);

	puts("");

	BENCHMARK(test_d);

	puts("\n/////////////////////////\n");
}

/*------------------------------------------------------------------------------
	BENCHMARK_GROUP() usage
------------------------------------------------------------------------------*/

void benchmark_group_usage()
{
	puts("\n/// BENCHMARK_GROUP() usage ///\n");

	BENCHMARK_GROUP_START(stdout, 10, 100);
		BENCHMARK_GROUP_ADD(test_a, 0);
		BENCHMARK_GROUP_ADD(test_b, 0);
		BENCHMARK_GROUP_ADD(test_c, 0);
	BENCHMARK_GROUP_END();

	puts("\n\n");

	BENCHMARK_GROUP_START(stdout, 5, 2000);
		BENCHMARK_GROUP_ADD(test_a, -10);
		BENCHMARK_GROUP_ADD(test_b, 20);
		BENCHMARK_GROUP_ADD(test_b, 200);
		BENCHMARK_GROUP_ADD(test_c, 40);
	BENCHMARK_GROUP_END();

	puts("\n///////////////////////////////\n");
}

/*------------------------------------------------------------------------------
	main()
------------------------------------------------------------------------------*/

int main()
{
	benchmark_usage();
	benchmark_group_usage();
	getchar();
}