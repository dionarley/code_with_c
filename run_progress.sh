#!/bin/bash
# Run stress_pi_progress - Multi-threaded com progresso em arquivo

echo "=== Running stress_pi com progresso ==="
echo

PASSOS=${1:-100000000}
ARQUIVO=${2:-pi_progress.log}
INTERVALO=${3:-500}

echo "Passos: $PASSOS"
echo "Arquivo: $ARQUIVO"
echo "Intervalo: ${INTERVALO}ms"
echo

./stress_pi_progress "$PASSOS" "$ARQUIVO" "$INTERVALO"