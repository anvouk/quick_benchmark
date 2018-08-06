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

#define QB_VERSION_MAJOR 1
#define QB_VERSION_MINOR 0
#define QB_VERSION_PATCH 0
#define QB_VERSION_STATE "stable"

#define _QB_VERSION_STR(major, minor, patch) \
	QBSTR(major) "." \
	QBSTR(minor) "." \
	QBSTR(patch) "-" \
	QB_VERSION_STATE

#define QB_VERSION_STR \
	_QB_VERSION_STR(QB_VERSION_MAJOR, QB_VERSION_MINOR, QB_VERSION_PATCH)

#define QB_VERSION_MAKE(major, minor, patch) \
	((major) << 16) | ((minor) << 8) | (patch))

#ifdef _MSC_VER
#  ifndef QB_NOINLINE_MSVC
#    define QB_NOINLINE_MSVC __declspec(noinline)
#  endif /* !QB_NOINLINE_MSVC */
#  ifndef QB_NOINLINE_GCC
#    define QB_NOINLINE_GCC
#  endif /* !QB_NOINLINE_GCC */
#else
#  ifndef QB_NOINLINE_MSVC
#    define QB_NOINLINE_MSVC
#  endif /* !QB_NOINLINE_MSVC */
#  ifndef QB_NOINLINE_GCC
#    define QB_NOINLINE_GCC __attribute__((noinline))
#  endif /* !QB_NOINLINE_GCC */
#endif /* _MSC_VER */

#ifndef QB_BENCHMARK_BENCH_FUNC
#  ifdef _MSC_VER
#    ifdef __cplusplus
extern "C" {
#    endif
unsigned long long __rdtsc(void);
#    ifdef __cplusplus
}
#    endif
#    define QB_BENCHMARK_BENCH_FUNC __rdtsc
#  else
#    define QB_BENCHMARK_BENCH_FUNC __builtin_ia32_rdtsc
#  endif /* _MSC_VER */
#endif /* !QB_BENCHMARK_BENCH_FUNC */

#define BENCHMARK_N(file, n_runs, x, ...) \
	do { \
		uint64_t _tot = 0; \
		for (int _j = 0; _j < n_runs; _j++) { \
			uint64_t _start, _end;	\
			_start = (uint64_t)QB_BENCHMARK_BENCH_FUNC(); \
			x(__VA_ARGS__); \
			_end = (uint64_t)QB_BENCHMARK_BENCH_FUNC(); \
			_tot += _end - _start; \
		} \
		fprintf(file, "[" QBSTR(x) "(" QBSTR(__VA_ARGS__) ")]: \tcalls: %.4d\t\tcycles: %lld\n", \
			(int)n_runs, _tot / n_runs); \
	} while(0)

#define BENCHMARK(x, ...) \
	BENCHMARK_N(stdout, 1000, x, __VA_ARGS__)

#define BENCHMARK_GROUP_BEGIN(file, g_runs, n_runs) \
	for (int _i = 0; _i < (g_runs); _i++) { \
		FILE* _outfile = file; \
		uint64_t _single_runs = (n_runs); \
		fprintf(file, "========================================================== n. %.2d\n", _i + 1)

#define BENCHMARK_GROUP_ADD(x, ...) \
	BENCHMARK_N(_outfile, _single_runs, x, __VA_ARGS__)

#define BENCHMARK_GROUP_END() \
	} ((void)0) /* for the ; */

#endif /* QUICK_BENCHMARK_H */