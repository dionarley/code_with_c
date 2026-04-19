# Pi Stress Test

Projeto C++ para cálculo de Pi com stress testing de CPU e memória.

## Estrutura

```
src/        # Código fonte
bin/       # Binários compilados
```

## Implementações

| Arquivo | Algoritmo | Uso |
|--------|----------|-----|
| `stress_pi` | Integração numérica | Stress rápido (~15 dígitos) |
| `stress_pi_v2` | Chudnovsky (GMP) | Alta precisão |
| `stress_pi_progress` | Integração + logging | Com progresso em arquivo |

## Instalação

```bash
cd src
./build_all.sh

# Ou com make
make build
```

## Uso Rápido

```bash
cd src

# Stress test básico (1 bilhão de passos)
./run.sh

# Com progresso em arquivo
./run_progress.sh 100000000 pi.log 500

# Ver progresso em tempo real
tail -f pi.log

# Alta precisão (GMP)
./run_v2.sh 1000

# Testes unitários
./run_test.sh
```

## Testes

17 casos cobrindo:
- Edge cases (0, 1 passo)
- Precisão (1K → 10M passos)
- Thread safety
- Determinismo

```bash
make test
# Output: 17 passed | 0 failed
```

## Documentação

- `DOCS.md` - Documentação técnica
- `AGENTS.md` - Guidelines para agentes

## Requisitos

- g++ (C++17+)
- GMP (para stress_pi_v2)
- doctest (para testes)