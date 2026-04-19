# Pi Stress Test

Projeto C++ para cálculo de Pi com stress testing de CPU e memória.

## Objetivo

Este projeto implementa métodos para calcular o valor de Pi enquanto estressa a CPU, útil para:
- Teste de estabilidade de hardware
- Stress test térmico
- Benchmarking
- Validação de precisões

## Implementações

| Arquivo | Algoritmo | Uso |
|--------|----------|-----|
| `stress_pi` | Integração numérica | Stress rápido (~15 dígitos) |
| `stress_pi_v2` | Chudnovsky (GMP) | Alta precisão |
| `stress_pi_progress` | Integração + logging | Com progresso em arquivo |

## Instalação

```bash
# Compilar tudo
./build_all.sh

# Ou com make
make build
```

## Uso Rápido

```bash
# Stress test básico (1 bilhão de passos)
./run.sh

# Com进度 acompanhamento
./run_progress.sh 100000000 pi.log 500
tail -f pi.log

# Alta precisão (GMP)
./run_v2.sh 1000

# Testes unitários
./run_test.sh
```

## Testes

17 casos de teste cobrindo:
- Edge cases (0, 1 passo)
- Precisão (1K → 10M passos)
- Thread safety
- Determinismo

```bash
make test
# Output: 17 passed | 0 failed
```

## Documentação

- `DOCS.md` - Documentação técnica detalhada
- `AGENTS.md` - guidelines para agentes

## Requisitos

- g++ (C++17+)
- GMP (para stress_pi_v2)
- doctest (para testes)