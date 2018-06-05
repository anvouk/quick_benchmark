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
#  include <cstdint>
#else
#  include <stdio.h>
#  include <stdint.h>
#endif

/* note: using va_args is a nice hack for the MSVC warning
 * "warning C4003: not enough actual parameters for macro '_QBSTR'" that
 * happens when trying to benchmark a function without parameters.
 */
#define _QBSTR(...) #__VA_ARGS__
#define QBSTR _QBSTR

#ifdef _MSC_VER
#  ifndef MSVC_NOINLINE
#    define MSVC_NOINLINE __declspec(noinline)
#  endif /* !MSVC_NOINLINE */
#  ifndef GCC_NOINLINE
#    define GCC_NOINLINE
#  endif /* !GCC_NOINLINE */
#else
#  ifndef MSVC_NOINLINE
#    define MSVC_NOINLINE __declspec(noinline)
#  endif /* !MSVC_NOINLINE */
#  ifndef GCC_NOINLINE
#    define GCC_NOINLINE __declspec(noinline)
#  endif /* !GCC_NOINLINE */
#endif /* _MSC_VER */

#ifndef BENCHMARK_BENCH_FUNC
#  ifdef _MSC_VER
#    ifdef __cplusplus
extern "C" {
#    endif
unsigned __int64 __rdtsc(void);
#    ifdef __cplusplus
}
#    endif
#    define BENCHMARK_BENCH_FUNC __rdtsc
#  else
#    define BENCHMARK_BENCH_FUNC __builtin_ia32_rdtsc
#  endif /* _MSC_VER */
#endif /* !BENCHMARK_BENCH_FUNC */

#define BENCHMARK_N(file, n_runs, x, ...) \
	do { \
		uint64_t _tot = 0; \
		for (int _j = 0; _j < n_runs; _j++) { \
			uint64_t _start, _end;	\
			_start = (uint64_t)BENCHMARK_BENCH_FUNC(); \
			x(__VA_ARGS__); \
			_end = (uint64_t)BENCHMARK_BENCH_FUNC(); \
			_tot += _end - _start; \
		} \
		fprintf(file, "[" QBSTR(x) "(" QBSTR(__VA_ARGS__) ")]: \tcalls: %.4d\t\tcycles: %lld\n", \
			(int)n_runs, _tot / n_runs); \
	} while(0)

#define BENCHMARK(x, ...) \
	BENCHMARK_N(stdout, 1000, x, __VA_ARGS__)

#define BENCHMARK_GROUP_START(file, g_runs, n_runs) \
	for (int _i = 0; _i < (g_runs); _i++) { \
		FILE* _outfile = file; \
		uint64_t _single_runs = (n_runs); \
		fprintf(file, "========================================================== n. %.2d\n", _i + 1)

#define BENCHMARK_GROUP_ADD(x, ...) \
	BENCHMARK_N(_outfile, _single_runs, x, __VA_ARGS__)

#define BENCHMARK_GROUP_END() \
	} ((void)0) /* for the ; */

#endif /* QUICK_BENCHMARK_H */