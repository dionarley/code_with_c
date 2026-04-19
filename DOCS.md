# Documentação Técnica - Pi Stress Test

## 1. Introdução

Projeto C++ para cálculo de Pi com dois objetivos: stress testing de CPU/memória e computação de dígitos de Pi. Três implementações:

- **stress_pi**: Integração numérica multi-thread (veloz)
- **stress_pi_v2**: GMP alta precisão
- **stress_pi_progress**: Integração com progresso em arquivo

---

## 2. Algoritmos

### 2.1 Integração Numérica (stress_pi)

Método dos retângulos para integral:

```
π = ∫₀¹ 4/(1+x²) dx
```

```cpp
double step = 1.0 / num_steps;
double sum = 0;
for (int i = 0; i < num_steps; i++) {
    double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x*x);
}
double pi = sum * step;
```

- Complexidade: O(n)
- Precisão: ~15 dígitos (double)
- Tempo: ~4s para 1 bilhão de passos (4 threads)

### 2.2 Chudnovsky (stress_pi_v2)

Série usada em recordes mundiais. Cada termo adiciona ~14.18 dígitos:

```
π = Σ ((-1)^k * (6k)! * (13591409 + 545140134k)) / ((3k)! * (k!)³ * 640320^(3k+3/2))
```

- Precisão: Arbitrária (limitada pela memória)
- Mais lenta que integração

### 2.3 Progresso (stress_pi_progress)

Mesma implementação do stress_pi com monitoramento:

```bash
./stress_pi_progress 100000000 pi.log 500
tail -f pi.log
```

---

## 3. Instalação

### 3.1 Dependências

| Biblioteca | Ubuntu | Arch Linux |
|------------|--------|------------|
| g++ | `build-essential libgmp-dev` | `base-devel gmp` |
| doctest | `doctest-dev` | `doctest` |

```bash
# Ubuntu
sudo apt install build-essential libgmp-dev doctest-dev

# Arch
sudo pacman -S base-devel gmp doctest
```

### 3.2 Compilar

```bash
make build          # Compilar tudo
make test           # Rodar testes
ls -lh stress_pi*   # Ver binários
```

---

## 4. Uso

### Scripts

| Script | Uso |
|--------|-----|
| `./run.sh` | Básico (1 bilhão passos) |
| `./run.sh 1000000` | Passos customizados |
| `./run_v2.sh 1000` | Alta precisão (GMP) |
| `./run_progress.sh 10000000 log.txt 500` | Com progresso |
| `./run_test.sh` | Testes unitários |

### Exemplos

**Stress test básico:**
```bash
./run.sh
# Output:
# --- Stress Test Iniciado ---
# Threads: 4 | Passos: 1000000000
# Valor de PI: 3.14159265358983
# Tempo: 3.73 segundos
```

**Acompanhar progresso:**
```bash
./run_progress.sh 100000000 pi.log 500
# Em outro terminal:
tail -f pi.log
```

**Alta precisão:**
```bash
./run_v2.sh 500
# Output:
# Digitos: 500
# Pi: 0.3141592653589793238462643383279502884197...
```

---

## 5. Testes (17 casos)

| # | Teste | Descrição |
|---|-------|-----------|
| 1-3 | calculate_pi_slice | Soma parcial, vazio, single |
| 4-6 | Edge cases | 0 passos, 0 threads, 1 passo |
| 7-10 | Precisão | 1K→tol 0.01, 100K→0.0001, 1M→0.00001, 10M→0.000001 |
| 11-13 | Determinismo | Single thread, multi-thread, scaling |
| 14-17 | Sistema | Hardware concurrency, thread creation, bounds, convergência |

```bash
make test                  # Todos
./stress_pi_test -tc="*"  # Específico
```

---

## 6. Benchmarks

### Threads (100M passos)

| Threads | Tempo |
|---------|-------|
| 1 | 38s |
| 2 | 19s |
| 4 | 4.5s |

### Velocidade típica: ~50M iterações/segundo (4 threads)

---

## 7. Limitações

### Memória por Dígitos (GMP)

| Dígitos | RAM |
|---------|-----|
| 1K | 2 KB |
| 1M | 100 MB |
| 1B | 100 GB |

Para bilhões de dígitos, use y-cruncher.

### Precisão

- **double**: ~15 dígitos
- **GMP**: Arbitrária

---

## 8. Arquitetura

```
pi_lib.h/cpp       → Biblioteca central
stress_pi.cpp      → Main usando pi_lib
stress_pi_test.cpp → Testes
stress_pi_progress.cpp → Com logging
stress_pi_v2.cpp   → Versão GMP
```

### API pi_lib

```cpp
double calculate_pi_slice(long long start, long long end, double step);
double calculate_pi_integration(long long num_steps, unsigned int num_threads);
```

---

## 9. Referências

- Método dos retângulos: https://pt.wikipedia.org/wiki/Método_dos_retângulos
- Chudnovsky: https://en.wikipedia.org/wiki/Chudnovsky_algorithm
- GMP: https://gmplib.org/
- y-cruncher: http://www.numberworld.org/y-cruncher/