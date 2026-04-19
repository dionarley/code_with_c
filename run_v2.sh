#!/bin/bash
# Run stress_pi_v2 - High precision with GMP
# Uso: ./run_v2.sh [digitos]

DIGITS=${1:-1000}

echo "=== Running stress_pi_v2 (GMP) ==="
echo "Digitos: $DIGITS"
echo

./stress_pi_v2 "$DIGITS"