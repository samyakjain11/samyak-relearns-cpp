# C++ Compiler

Some common C++ compiler flags include the following:

| Flag | Meaning |
|---|---|
| `-std=c++20` | Language standard to compile as |
| `-Wall` | Warnings: all the common, useful ones |
| `-Wextra` | More warnings: unused parameters, sign comparisons |
| `-g` | Retain debug info (line numbers and names) |
| `-fsanitize=address` | AddressSanitizer (ASan): catches out-of-bounds access, use-after-free and leaks at run time |
| `-fsanitize=undefined` | UndefinedBehaviorSanitizer (UBSan): catches signed overflow, null dereference and other undefined behavior at run time |
| `-o file` | Name of the output program |

Sanitizers can be combined: `-fsanitize=address,undefined`
