#!/bin/bash
# Build all binaries to bin/

echo "=== Building all binaries ==="

cd "$(dirname "$0")"

# Get doctest
if [ ! -f ../doctest.h ]; then
    echo "Downloading doctest.h..."
    curl -L -o ../doctest.h "https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h"
fi

# Build stress_pi (v1)
echo "Building stress_pi..."
g++ -O3 -pthread stress_pi.cpp pi_lib.cpp -o ../bin/stress_pi

# Build stress_pi_test
echo "Building stress_pi_test..."
g++ -O3 -pthread -I.. stress_pi_test.cpp pi_lib.cpp -o ../bin/stress_pi_test

# Build stress_pi_progress
echo "Building stress_pi_progress..."
g++ -O3 -pthread stress_pi_progress.cpp -o ../bin/stress_pi_progress

# Build stress_pi_v2 (if GMP available)
if g++ -O3 -x c++ - -lgmpxx -lgmp -o /dev/null 2>/dev/null << 'EOF'
#include <gmpxx.h>
int main() { return 0; }
EOF
then
    echo "Building stress_pi_v2 (GMP)..."
    g++ -O3 stress_pi_v2.cpp -o ../bin/stress_pi_v2 -lgmpxx -lgmp
else
    echo "Skipping stress_pi_v2 (GMP not installed)"
fi

echo
echo "=== Done ==="
echo
echo "Binaries:"
ls -lh ../bin/