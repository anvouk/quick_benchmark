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

#ifndef QUICK_BENCHMARK_H
#define QUICK_BENCHMARK_H

#ifdef __cplusplus
#  include <cstdio>
#else
#  include <stdio.h>
#endif

#define _QSTR(x) #x
#define QSTR _QSTR

#ifndef NOINLINE
#  define NOINLINE		__declspec(noinline)
#endif

#ifndef INLINE
#  define INLINE		__inline
#endif

#ifndef FORCEINLINE
#  define FORCEINLINE	__forceinline
#endif

#ifdef __cplusplus
extern "C" {
#endif

unsigned __int64 __rdtsc(void);

#ifdef __cplusplus
}
#endif

#define BENCHMARK_N(n_runs, x, ...) \
	do { \
		unsigned __int64 _tot = 0; \
		for (int _j = 0; _j < n_runs; _j++) { \
			unsigned __int64 _start, _end;	\
			_start = __rdtsc(); \
			x(__VA_ARGS__); \
			_end = __rdtsc(); \
			_tot += _end - _start; \
		} \
		printf("[" QSTR(x) "]:\t\tcycles: %lld\n", _tot / n_runs); \
	} while(0)

#define BENCHMARK(x, ...) \
	BENCHMARK_N(1000, x, __VA_ARGS__)

#define BENCHMARK_GROUP_START(g_runs, n_runs) \
	for (int _i = 0; _i < (g_runs); _i++) { \
		unsigned __int64 _single_runs = (n_runs); \
		printf("=========================================== n. %.2d\n", _i + 1)

#define BENCHMARK_GROUP_ADD(x, ...) \
	BENCHMARK_N(_single_runs, x, __VA_ARGS__)

#define BENCHMARK_GROUP_END() \
	} ((void*)0) /* for the ; */

#endif /* QUICK_BENCHMARK_H */