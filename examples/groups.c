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

#include <time.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _WIN32
#  include <immintrin.h>
#else
#  include <x86intrin.h>
#endif /* _WIN32 */

#include "quick_benchmark/quick_benchmark.h"

/*------------------------------------------------------------------------------
	functions
------------------------------------------------------------------------------*/

QB_NOINLINE_MSVC void
set_zero_c(int* buff, size_t size) QB_NOINLINE_GCC
{
	for (int* i = buff, *end = buff + size; i < end; i++) {
		*i = 0;
	}
}

QB_NOINLINE_MSVC void
set_zero_memset(int* buff, size_t size) QB_NOINLINE_GCC
{
	memset(buff, 0, sizeof(int) * size);
}

QB_NOINLINE_MSVC void
set_zero_sse(int* buff, size_t size) QB_NOINLINE_GCC
{
	__m128i zero = _mm_setzero_si128();
	for (__m128i* i = (__m128i*)buff, *end = (__m128i*)(buff + size); i < end; i++) {
		_mm_store_si128(i, zero);
	}
}

QB_NOINLINE_MSVC void
set_zero_avx(int* buff, size_t size) QB_NOINLINE_GCC
{
	__m256i zero = _mm256_setzero_si256();
	for (__m256i* i = (__m256i*)buff, *end = (__m256i*)(buff + size); i < end; i++) {
		_mm256_store_si256(i, zero);
	}
}

QB_NOINLINE_MSVC void
set_random_c(int* buff, size_t size) QB_NOINLINE_GCC
{
	time_t t;
	srand((unsigned int)time(&t));
	int rn = rand();
	for (int* i = buff, *end = buff + size; i < end; i++) {
		*i = rn;
	}
}

QB_NOINLINE_MSVC void
set_random_sse(int* buff, size_t size) QB_NOINLINE_GCC
{
	time_t t;
	srand((unsigned int)time(&t));
	__m128i rn = _mm_set1_epi32(rand());
	for (__m128i* i = (__m128i*)buff, *end = (__m128i*)(buff + size); i < end; i++) {
		_mm_store_si128(i, rn);
	}
}

QB_NOINLINE_MSVC void
set_random_avx(int* buff, size_t size) QB_NOINLINE_GCC
{
	time_t t;
	srand((unsigned int)time(&t));
	__m256i rn = _mm256_set1_epi32(rand());
	for (__m256i* i = (__m256i*)buff, *end = (__m256i*)(buff + size); i < end; i++) {
		_mm256_store_si256(i, rn);
	}
}

/*------------------------------------------------------------------------------
	benchmark
------------------------------------------------------------------------------*/

#define BUFF_SIZE 4096

int
main(int argc, char* argv[])
{
	printf("quick_benchmark | %s <%d> | examples/groups.c\n\n", QB_VERSION_STR, QB_VERSION);
	int buff[BUFF_SIZE];

	QB_BENCH_BEGIN(stdout, 10, 1000);
		QB_BENCH_ADD(set_zero_c, buff, BUFF_SIZE);
		QB_BENCH_ADD(set_zero_memset, buff, BUFF_SIZE);
		QB_BENCH_ADD(set_zero_sse, buff, BUFF_SIZE);
		QB_BENCH_ADD(set_zero_avx, buff, BUFF_SIZE);
	QB_BENCH_END();

	puts("\n");

	QB_BENCH_BEGIN(stdout, 10, 1000);
		QB_BENCH_ADD_WITH_NAME(set_random_c,   "random fill - C",   buff, BUFF_SIZE);
		QB_BENCH_ADD_WITH_NAME(set_random_sse, "random fill - SSE", buff, BUFF_SIZE);
		QB_BENCH_ADD_WITH_NAME(set_random_avx, "random fill - AVX", buff, BUFF_SIZE);
	QB_BENCH_END();

	getchar();
}
