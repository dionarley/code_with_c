#!/bin/bash
# Run stress_pi_test - Unit tests

cd "$(dirname "$0")"

echo "=== Running unit tests ==="
echo

# Build if needed
if [ ! -f ../bin/stress_pi_test ]; then
    echo "Compilando..."
    make build-test
fi

../bin/stress_pi_test "$@"

echo
echo "Para rodar teste específico:"
echo "  ../bin/stress_pi_test -tc=\"test_name\""
echo "  ../bin/stress_pi_test -tc=\"*accuracy*\""