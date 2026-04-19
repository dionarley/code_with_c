# AGENTS.md - Agentic Coding Guidelines

## Overview

This repository contains C++ stress testing implementations for calculating Pi using various algorithms:
- `stress_pi.cpp` - Multi-threaded integration method (rectangle rule)
- `stress_pi_v2.cpp` - Chudnovsky series with GMP for high precision
- `stress_pi_progress.cpp` - Multi-threaded with progress logging to file

**Test framework: doctest v2.4.11** - Header-only C++ testing framework

---

## Build Commands

### Basic Build (stress_pi v1)
```bash
g++ -O3 -pthread stress_pi.cpp -o stress_pi
```

### High-Precision Build (stress_pi v2 with GMP)
```bash
g++ -O3 stress_pi_v2.cpp -o stress_pi_v2 -lgmpxx -lgmp
```

### Run Compiled Binaries
```bash
./stress_pi        # Multi-threaded version
./stress_pi_v2    # GMP high-precision version
```

### Build & Test Commands
```bash
make get-doctest   # Download doctest.h (first time only)
make build         # Build stress_pi
make build-test    # Build test binary
make build-progress # Build progress version
make test          # Run all unit tests
make test-v1       # Run stress_pi binary
make test-progress # Run with progress to file
make clean         # Clean build artifacts
```

### Progress Version (visualizar cálculo)
```bash
# Sintaxe: ./stress_pi_progress [passos] [output_file] [intervalo_ms]
./stress_pi_progress 100000000 pi_progress.log 500   # 100M passos, log a cada 500ms

# Para acompanhar em tempo real:
tail -f pi_progress.log
```

### Run Single Test
```bash
./stress_pi_test -tc="test_name"  # Run specific test case
./stress_pi_test -tc="*accuracy*"  # Run tests matching pattern
```

### Run Single Test
```bash
./stress_pi_test -tc="test_name"  # Run specific test case
./stress_pi_test -tc="*accuracy*"  # Run tests matching pattern
```

### CMake Alternative
```bash
make cmake-build   # Build with CMake
make cmake-test    # Run tests via CMake/ctest

### Compiler Flags Reference
| Flag | Purpose |
|------|---------|
| `-O3` | Maximum optimization |
| `-pthread` | Enable pthreads for std::thread |
| `-lgmpxx -lgmp` | Link GMP C++ and C libraries |
| `-march=native` | CPU-specific optimizations |

**Note**: For GMP version, ensure GMP is installed:
- Arch Linux: `sudo pacman -S gmp`
- Debian/Ubuntu: `sudo apt-get install libgmp-dev`

---

## Code Style Guidelines

### Imports
```cpp
#include <iostream>     // I/O
#include <vector>
#include <thread>
#include <atomic>
#include <iomanip>
#include <chrono>
#include <gmp.h>
#include <gmpxx.h>
```
**Order**: Standard library, then third-party, then project headers.

### Types
- `long long`: Large integer counts (steps, iterations)
- `unsigned long long`: Non-negative large values
- `double`: Floating-point calculations
- `std::atomic<T>`: Thread-safe shared values
- `mpf_class`: GMP arbitrary precision floats
- `mpz_class`: GMP arbitrary precision integers

### Naming Conventions

- **Functions**: `camelCase` (e.g., `calculate_pi_slice`)
- **Constants**: `SCREAMING_SNAKE_CASE` (e.g., `MAX_ITERATIONS`)
- **Variables**: `camelCase` (e.g., `global_sum`, `num_steps`)
- **Classes**: `PascalCase` (not currently used)

### Formatting

- **Indentation**: 4 spaces (no tabs)
- **Line length**: No strict limit, but prefer <= 100 chars
- **Braces**: Same-line style:
  ```cpp
  if (condition) {
      // code
  }
  ```
- **Semicolons**: Required after every statement

### Thread Safety

- Use `std::atomic` for shared mutable state
- Pass values by reference with `std::ref()` for atomic wrappers
- Use atomic compare-exchange for lock-free updates:
  ```cpp
  double current = global.load();
  while (!global.compare_exchange_weak(current, current + value));
  ```
- Join all threads before accessing final results

### Error Handling

- **No exception handling** currently used in this codebase
- For production code: prefer RAII patterns
- For GMP errors: check return values from `mpf_*` functions

### Performance Considerations

1. Use `-O3` optimization level
2. Prefer `std::thread::hardware_concurrency()` for thread count
3. Avoid atomic operations in tight loops; use local accumulation
4. Use `compare_exchange_weak` (not `strong`) in loops
5. Reserve `std::vector` capacity when size is known

### Code Documentation

- Comments in Portuguese (original author preference)
- Use descriptive names to minimize comment need
- Document算法 complexity for new implementations

---

## Project-Specific Notes

### v1 (stress_pi.cpp) - Integration Method
- Uses rectangle rule numerical integration
- Divides work evenly across hardware threads
- Atomic final sum aggregation
- ~1 billion steps = significant CPU/RAM stress

### v2 (stress_pi_v2.cpp) - Chudnovsky Method
- Requires GMP library for arbitrary precision
- Each term adds ~14.18 decimal digits
- Memory requirements scale with digit count
- Binary splitting used in production implementations

### Running Tests
Tests are in `stress_pi_test.cpp`. Run with:
```bash
make test    # Run all tests
./stress_pi_test -tc="test_name"  # Single test
```

### Test Coverage
| Test | Description |
|------|-----------|
| `calculate_pi_slice` | Basic computation |
| `zero steps` | Edge case: 0 |
| `single step` | Edge case: 1 |
| `small steps accuracy` | 1K steps, tol 0.01 |
| `medium steps accuracy` | 100K steps, tol 0.0001 |
| `large steps accuracy` | 1M steps, tol 0.00001 |
| `single thread consistency` | Same result reproducibility |
| `multi-thread consistency` | Same result across thread counts |

---

## Dependencies

| Library | Version | Purpose |
|---------|--------|---------|
| g++ | C++17+ | Compiler |
| libpthread | - | Threading support |
| libgmp | 6.x+ | Arbitrary precision (v2 only) |
| doctest | 2.4.11 | Unit testing framework |

---

## Limitations

1. Stress test ~1B steps is CPU-intensive
2. No CI/CD - Build manually before commits
3. Platform-specific - Uses `std::thread::hardware_concurrency()`
4. No code formatting tool - Manually maintain style
5. Portuguese comments - Original codebase language preference