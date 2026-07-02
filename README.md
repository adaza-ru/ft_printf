*This project has been created as part of the 42 curriculum by adaza-ru.*

# 📖 ft_printf - High-Performance String Formatting

## 🚀 Overview

This project consists of recoding the famous `printf` function from the C standard library (`libc`). While the main educational objective of the 42 curriculum is to master variadic functions (`stdarg.h`) and complex format management, this repository goes a step further.

Beyond simply parsing flags and specifiers, this implementation features a highly optimized, buffer-based I/O architecture. It is capable of processing various conversion specifiers, flags, field widths, and precisions, mimicking the behavior of the original function while maximizing CPU execution efficiency.

## 💻 Instructions & Usage
### Compilation

The project is compiled using a Makefile. It includes the standard rules required by the subject.

**To compile** `make` or ``make all``

This will generate the static library file libftprintf.a at the root of the repository.

### Usage

To use the function in your own projects, include the header and link the library during compilation:

```c
#include "include/ft_printf.h"
#include <stdio.h>

int main(void)
{
	int	ret_orig;
	int	ret_ft;

	char *str = "Prueba: %s | Numero: %d";
	char *arg_s = "42 Malaga";
	int arg_i = 42;

	printf("--- COMPARACIÓN DE SALIDA Y RETORNO ---\n\n");
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
		printf("✅ Los valores de retorno coinciden.\n");
	else
		printf("❌ Error: Los retornos son diferentes.\n");
	return (0);
}
```

```bash
cc main.c libftprintf.a -o test_printf
./test_printf
```

## 🏗️ Architecture & Refactoring: Why Use a Buffer?

### The Standard Project Approach (Subject Constraints)

The 42 `ft_printf` subject explicitly mandates that the function must handle output character by character, effectively prohibiting the use of internal buffers to simplify the understanding of low-level output handling via the `write()` system call. In the standard implementation, every character is processed and sent to the standard output using write`(1, &c, 1)`.

While this approach is perfect for learning the fundamentals of the system call interface, it introduces a significant I/O Bottleneck. Calling `write()` millions of times interrupts the CPU, forcing it to save the program's state, switch from User Space to Kernel Space (Context Switch), execute the hardware operation, and return.

### The Refactored Approach (Post-Project Optimization)

Once the project requirements were met, I refactored the underlying printing mechanism to move beyond the subject's constraints. I implemented a static `char buffer[BUFFER_SIZE]` (defaulting to 1024 bytes) located in the `.bss` memory segment to decouple the logic of formatting from the physical transmission of data.

How it works:

1. The formatting engine processes the entire string and its variables in User Space at pure CPU clock speed.

2. Data is pushed into the local static buffer.

3. A `write()` system call is only triggered when the buffer reaches its 1024-byte limit, or when the formatting process is completely finished.

This refactoring shifts the design from a naive character-by-character loop to an enterprise-grade stream buffer, mirroring the true behavior of modern standard libraries.

## 📊 Performance & Benchmarking

To prove the efficiency of this architectural refactoring, I conducted a series of low-level system benchmarks to measure execution time and system call overhead.

### 🧪 Benchmark SetupTest
* **Payload:** Continuous formatting and streaming of **5,000,000 characters**.
* **Environment:** Linux CPU performance profiling via the `time` and `strace` commands.

### 📈 Results: The Cost of Syscalls

Comparing the legacy single-character approach with the optimized 1024-byte buffer approach:

| Metric | Legacy Version (Unbuffered) |Optimized Version (`BUFFER_SIZE 1024`) |Impact / Improvement |
| --- | --- | --- | --- |
| Total `write()` **Syscalls** | 5,000,000 calls | ~4,883 calls | ⬇️ 99.90% Syscalls Saved |
|User Time (`user`) | 0.320s | 0.030s | 🚀 11x Faster processing |
| Kernel Time (system) | 0.740s | 0.000s | 🛑 Eradicated OS Overload |
| Total Execution Time | 1.061s | 0.035s |⚡ 30 x Overall Speedup| 

In the legacy version, the CPU spent ~70% of its time frozen, dealing with OS context switches. The buffered version drops Kernel execution time to absolute zero, keeping the flow entirely in the application space.

## 🎛️ Buffer Size & OS Page Cache Caching
To find the optimal threshold for the memory buffer, further benchmarks were conducted by altering the `BUFFER_SIZE` macro.

During extreme physical integration tests (writing 5,000,000 characters directly to a physical disk file), execution times remained incredibly homogeneous (around `0.050s`) even with a BUFFER_SIZE of 1.

This experiment highlighted the efficiency of the **Linux Virtual File System (VFS) Page Cache**. The Linux Kernel intercepts small byte payloads and groups them into `4KB execution pages` in RAM before sending them to the disk. However, relying on the OS to mitigate bad code is dangerous. My `1024` buffer architecture guarantees this optimal streaming behavior natively, protecting the application's throughput regardless of OS caching policies, network socket latencies, or unbuffered external environments.

## ⚙️ Technical Choices & Algorithm

The project architecture is divided into three logical phases to ensure extensibility and cleanliness:

**1. Parsing:** A `t_print` structure is used to store flag values (`-`, `0`, `.`, `#`, ` `, `+`), width, precision, and the identifier.

**2. Logic Hierarchy:** Before printing, a hierarchy logic is applied (via the apply_hierarchy function). For example, if the `-` flag is present, the `0` flag is ignored; if precision is set for an integer, the `0` flag is also ignored.

**3. Dispatching & Printing:** A "dispatcher" redirects to specific functions based on the identifier (`c`, `s`, `p`, etc.). These functions calculate the necessary padding (spaces) and zeros before and after printing the actual value, based on the data stored in the structure.

### Anatomy of the `t_print` Structure

The `t_print` structure acts as the "brain" of the project. Instead of passing multiple variables between functions, all formatting data for a specific placeholder (the % specifier) is encapsulated into a single block of memory.

| Member| Type |Purpose|
| --- | --- | --- |
| dash (`-`) | int (Boolean) | Left-alignment. If set to 1, the content is left-justified, and padding is added to the right.|
| zero (`0`) | int (Boolean) | Zero-padding. Indicates if empty spaces should be filled with '0' instead of spaces (ignored if - or precision in integers is present). |
| dot (`.`) | int (Boolean) | Precision trigger. Crucial for distinguishing between a precision of 0 (e.g., `%.d`) and no precision at all.|
| hash (`#`) | int (Boolean) | Alternate form. For `%x` it adds the `0x` prefix; for `%X` it adds `0X`. |
| space (` `) | int (Boolean) | Leading space. Leaves a space before positive numbers if no `+` sign is present. |
| plus (`+`) | int (Boolean) | Explicit sign. Forces positive numbers to display a `+` symbol. |
| width | int | Minimum field width. The minimum total number of characters to be printed. |
| precision | int | Precision limit. For strings, it’s the maximum characters; for integers, the minimum number of digits. |
| identifier | char | The conversion type. Stores the specifier (e.g., `s`, `d`, `x`) to apply the final logic. |

### Example Flow

If the user calls `ft_printf("%-10.5d", 42);`:

* **Init:** All structure fields are initialized to `0` (or `-1` for precision).

* **Parse:** `dash = 1`, `width = 10`, `dot = 1`, `precision = 5`, `identifier = 'd'`.

* **Print:** The `handle_integer` function receives this struct. It calculates that it must buffer `00042     ` (5 digits for precision) followed by `5 spaces` (to complete the width of 10).


# Resources

The following sources were consulted during the development of this project:

* printf(3) man page

* <stdarg.h> documentation for variadic list management.

* Linux Kernel VFS and Page Cache documentation for I/O optimization.
