*This project has been created as part of the 42 curriculum by adaza-ru.*

# Description

This project consists of recoding the famous printf function from the C standard library (libc). The main objective is to learn about variadic functions and complex format management. The implementation is capable of processing various conversion specifiers and handling flags, field widths, and precisions, mimicking the behavior of the original function.

# Instructions
### Compilation

The project is compiled using a Makefile. It includes the standard rules required by the subject.

* To compile the mandatory part: `make` or ``make all``
* To compile with bonus support: ``make bonus``

This will generate the static library file libftprintf.a at the root of the repository.

###Usage

To use the function in your own projects, include the header and link the library during compilation:

```c
#include "ft_printf.h"
#include <stdio.h>

int main()
{
    printf("Original printf:	\n");
	ft_printf("42 ft_printf:	\n\n");
    return (0);
}
```

# Technical Choices & Algorithm

The project architecture is divided into three logical phases to ensure extensibility and cleanliness:

**1. Parsing:** A t_print structure is used to store flag values (-, 0, ., #,      , +), width, precision, and the identifier.

**2. Logic Hierarchy:** Before printing, a hierarchy logic is applied (via the apply_hierarchy function). For example, if the - flag is present, the 0 flag is ignored; if precision is set for an integer, the 0 flag is also ignored.

**3. Dispatching & Printing:** A "dispatcher" redirects to specific functions based on the identifier (c, s, p, etc.). These functions calculate the necessary padding (spaces) and zeros before and after printing the actual value, based on the data stored in the structure.

### Anatomy of the t_print Structure

The t_print structure acts as the "brain" of the project. Instead of passing multiple variables between functions, all formatting data for a specific placeholder (the % specifier) is encapsulated into a single block of memory.

| Member| Type |Purpose|
| --- | --- | --- |
| dash (-) | int (Boolean) | Left-alignment. If set to 1, the content is left-justified, and padding is added to the right.|
| zero (0) | int (Boolean) | Zero-padding. Indicates if empty spaces should be filled with '0' instead of spaces (ignored if - or precision in integers is present). |
| dot (.) | int (Boolean) | Precision trigger. Crucial for distinguishing between a precision of 0 (e.g., %.d) and no precision at all.|
| hash (#) | int (Boolean) | Alternate form. For %x it adds the 0x prefix; for %X it adds 0X. |
| space ( ) | int (Boolean) | Leading space. Leaves a space before positive numbers if no + sign is present. |
| plus (+) | int (Boolean) | Explicit sign. Forces positive numbers to display a + symbol. |
| width | int | Minimum field width. The minimum total number of characters to be printed. |
| precision | int | Precision limit. For strings, it’s the maximum characters; for integers, the minimum number of digits. |
| identifier | char | The conversion type. Stores the specifier (e.g., s, d, x) to apply the final logic. |

### Example Flow

If the user calls ft_printf("%-10.5d", 42);:

    Init: All structure fields are initialized to 0 (or -1 for precision).

    Parse:

        dash = 1

        width = 10

        dot = 1

        precision = 5

        identifier = 'd'

    Print: The handle_integer function receives this struct. It calculates that it must print 00042 (5 digits for precision) followed by 5 spaces (to complete the width of 10).


# Resources

The following sources were consulted during the development of this project:

    printf(3) man page

    <stdarg.h> documentation for variadic list management.

### AI Implementation Details


    Theoretical Research: AI helped in deeply understanding the internal workings of variadic functions (va_start, va_arg) and the behavior of flag and their hierarchies (e.g., the interaction between precision and 0).

    Architecture: Support in outlining the initial pseudocode and defining the t_print structure for bonus handling.

    Makefile & Documentation: Assistance in creating the Makefile logic and drafting this README.

    Debugging: Support in identifying edge cases reported by community testers, such as NULL pointer behavior and negative width/precision handling.
