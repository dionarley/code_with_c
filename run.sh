#!/bin/bash
# Run stress_pi v1 - Multi-threaded integration

STEPS=${1:-1000000000}

echo "=== Running stress_pi v1 ==="
echo "Passos: $STEPS"
echo

./stress_pi "$STEPS"