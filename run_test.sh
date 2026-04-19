#!/bin/bash
# Run stress_pi_test - Unit tests

echo "=== Running unit tests ==="
echo

if [ ! -f stress_pi_test ]; then
    echo "Compilando..."
    make build-test
fi

./stress_pi_test "$@"

echo
echo "Para rodar teste específico:"
echo "  ./stress_pi_test -tc=\"test_name\""
echo "  ./stress_pi_test -tc=\"*accuracy*\""