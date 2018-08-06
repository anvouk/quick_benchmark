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

#include <math.h>

#include <quick_benchmark/quick_benchmark.h>

/*------------------------------------------------------------------------------
	functions
------------------------------------------------------------------------------*/

QB_NOINLINE_MSVC void
test_math() QB_NOINLINE_GCC
{
	int val = 100;
	val = (int)pow(2, 10 + sqrt(val));
}

QB_NOINLINE_MSVC void
test_multi_param(int v1, int v2, unsigned v3) QB_NOINLINE_GCC
{
	v1 += (int)pow(2, v2 * v3);
	v1 *= (int)sqrt(v2 / (v3 + 1));
}

/*------------------------------------------------------------------------------
	benchmark
------------------------------------------------------------------------------*/

int main()
{
	printf("quick_benchmark | %s | examples/single.c\n\n", QB_VERSION_STR);

	/* Be careful not to add void when the function requires no parameters. */
	BENCHMARK_N(stderr, 200, test_math);

	puts("");

	/* These 2 macro do exactly the same thing. */
	BENCHMARK_N(stdout, 1000, test_multi_param, 30, 56, 120);
	BENCHMARK(test_multi_param, 30, 56, 120);

	getchar();
}