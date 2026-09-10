*This project has been created as part of the 42 curriculum by adaza-ru.*

<div align="center">

# ft_printf — High-Performance String Formatting

**A from-scratch reimplementation of `printf`, refactored past the school requirements into a buffered, syscall-efficient I/O engine.**

![C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Make](https://img.shields.io/badge/build-Make-red)
![Static Library](https://img.shields.io/badge/output-static_library-blue)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Architecture & Refactoring: Why Use a Buffer?](#architecture--refactoring-why-use-a-buffer)
- [Performance & Benchmarking](#performance--benchmarking)
- [Buffer Size & OS Page Cache](#buffer-size--os-page-cache)
- [Technical Choices & Algorithm](#technical-choices--algorithm)
- [Resources](#resources)
- [Notes](#notes)

---

## Overview

This project recodes the standard C library's `printf` from scratch. The core exercise is mastering variadic functions (`stdarg.h`) and format-string parsing — but this implementation goes further: it replaces the naive, character-by-character output required by the original spec with a **buffered, syscall-efficient I/O architecture**, and benchmarks the result against the unbuffered version to quantify the difference.

It supports the standard conversion specifiers, flags, field widths, and precisions, matching the behavior (and return value) of the original `printf`.

## Getting Started

### Requirements

- A C compiler
- `make`

### Build

```bash
git clone https://github.com/adaza-ru/ft_printf.git
cd ft_printf
make
```

This generates the static library `libftprintf.a` at the root of the repository.

## Usage

Include the header and link the library when compiling your own project:

```c
#include "include/ft_printf.h"
#include <stdio.h>

int main(void)
{
	int	ret_orig;
	int	ret_ft;

	char *str = "Test: %s | Number: %d";
	char *arg_s = "42 Malaga";
	int arg_i = 42;

	printf("--- OUTPUT AND RETURN VALUE COMPARISON ---\n\n");
	printf("Original  : [");
	ret_orig = printf(str, arg_s, arg_i);
	fflush(stdout);

	printf("] -> Return: %d\n", ret_orig);
	fflush(stdout);

	printf("ft_printf : [");
	fflush(stdout);

	ret_ft = ft_printf(str, arg_s, arg_i);
	printf("] -> Return: %d\n", ret_ft);
	fflush(stdout);

	printf("\n---------------------------------------\n");

	if (ret_orig == ret_ft)
		printf("Return values match.\n");
	else
		printf("Error: return values differ.\n");
	return (0);
}
```

```bash
cc main.c libftprintf.a -o test_printf
./test_printf
```

## Architecture & Refactoring: Why Use a Buffer?

### The standard project approach

The 42 `ft_printf` subject requires the function to write output character by character, explicitly prohibiting internal buffers, to keep the focus on the raw `write()` system call. In the baseline implementation, every character triggers `write(1, &c, 1)`.

That's fine for learning the syscall interface, but it introduces a real I/O bottleneck: each `write()` call interrupts the CPU, forcing a context switch from user space to kernel space, a hardware operation, and back.

### The refactored approach

Once the base requirements were met, I refactored the printing mechanism beyond the subject's constraints. A static `char buffer[BUFFER_SIZE]` (1024 bytes by default, living in `.bss`) decouples formatting logic from the physical transmission of data:

1. The formatting engine processes the full string and its arguments in user space, at CPU clock speed.
2. Output is pushed into the local static buffer.
3. A single `write()` call fires only when the buffer hits 1024 bytes, or when formatting is complete.

This moves the design from a naive per-character loop to a stream-buffered model closer to how modern standard libraries actually behave.

## Performance & Benchmarking

To validate the refactor, I benchmarked execution time and syscall overhead directly.

**Setup**
- Payload: continuous formatting and streaming of **5,000,000 characters**
- Environment: Linux, profiled with `time` and `strace`

**Results — legacy (unbuffered) vs. optimized (`BUFFER_SIZE 1024`)**

| Metric | Legacy (unbuffered) | Optimized (buffered) | Improvement |
|---|---|---|---|
| `write()` syscalls | 5,000,000 calls | ~4,883 calls | 99.90% fewer syscalls |
| User time (`user`) | 0.320s | 0.030s | ~11x faster |
| Kernel time (`system`) | 0.740s | 0.000s | Kernel overhead eliminated |
| Total execution time | 1.061s | 0.035s | ~30x overall speedup |

In the legacy version, the CPU spent roughly 70% of its time frozen on context switches. The buffered version drops kernel time to zero, keeping execution entirely in application space.

## Buffer Size & OS Page Cache

To find the optimal buffer threshold, I re-ran benchmarks while varying `BUFFER_SIZE`.

During physical-disk integration tests (writing 5,000,000 characters directly to a file), execution time stayed remarkably flat (~0.050s) even with `BUFFER_SIZE` set to 1.

The reason is the **Linux VFS page cache**: the kernel groups small writes into 4KB pages in RAM before flushing to disk, masking the cost of unbuffered writes. Relying on that behavior is risky, though — it's an OS implementation detail, not a guarantee. The 1024-byte buffer implemented here guarantees efficient streaming natively, regardless of OS caching policy, socket latency, or unbuffered environments.

## Technical Choices & Algorithm

The implementation is split into three phases:

1. **Parsing** — a `t_print` structure stores flag values (`-`, `0`, `.`, `#`, ` `, `+`), width, precision, and the conversion identifier.
2. **Logic hierarchy** — `apply_hierarchy()` resolves flag precedence before printing (e.g. `-` overrides `0`; a set precision on an integer overrides `0` as well).
3. **Dispatching & printing** — a dispatcher routes to the function matching the identifier (`c`, `s`, `p`, etc.), which computes padding and zeros based on the `t_print` data.

### The `t_print` structure

Instead of threading multiple variables through every function, all formatting data for a given `%` specifier is encapsulated in one struct:

| Member | Type | Purpose |
|---|---|---|
| `dash` (`-`) | bool (int) | Left-alignment; padding moves to the right |
| `zero` (`0`) | bool (int) | Zero-padding instead of spaces (ignored with `-` or precision on integers) |
| `dot` (`.`) | bool (int) | Precision trigger — distinguishes `%.d` (precision 0) from no precision at all |
| `hash` (`#`) | bool (int) | Alternate form — adds `0x`/`0X` prefix for `%x`/`%X` |
| `space` (` `) | bool (int) | Leading space before positive numbers when `+` is absent |
| `plus` (`+`) | bool (int) | Forces an explicit `+` on positive numbers |
| `width` | int | Minimum total field width |
| `precision` | int | Max characters (strings) or min digits (integers) |
| `identifier` | char | The conversion type (`s`, `d`, `x`, ...) |

### Example flow

For `ft_printf("%-10.5d", 42)`:

1. **Init** — all fields start at `0` (`-1` for precision).
2. **Parse** — `dash = 1`, `width = 10`, `dot = 1`, `precision = 5`, `identifier = 'd'`.
3. **Print** — `handle_integer` builds `00042` (5 digits for precision) followed by 5 spaces to reach the width of 10.

## Resources

- `printf(3)` man page
- `<stdarg.h>` documentation for variadic argument handling
- Linux kernel VFS and page cache documentation for I/O optimization

## Notes

Originally built as part of the 42 curriculum, then extended past the subject's constraints as a personal optimization exercise.
