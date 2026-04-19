#include <iostream>
#include <cstdlib>

void print_header() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║     PI STRESS TEST - MENU INTERATIVO       ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n\n";
}

int main(int argc, char* argv[]) {
    print_header();

    if (argc > 1) {
        int choice = atoi(argv[1]);
        switch (choice) {
            case 1: system("cd .. && bin/stress_pi"); break;
            case 2: system("cd .. && bin/stress_pi_progress 100000000 ../pi_progress.log 500"); break;
            case 3: system("cd .. && bin/stress_pi_v2 1000"); break;
            case 4: system("cd .. && bin/stress_pi_test"); break;
            case 5: system("cd .. && make build && make build-test"); break;
            case 0: return 0;
        }
        return 0;
    }

    std::cout << "Selecione uma opção:\n\n";
    std::cout << "  [1] Stress Test Básico (1 bilhão passos)\n";
    std::cout << "  [2] Com Progresso em Arquivo\n";
    std::cout << "  [3] Alta Precisão (GMP)\n";
    std::cout << "  [4] Rodar Testes Unitários\n";
    std::cout << "  [5] Compilar Tudo\n";
    std::cout << "  [0] Sair\n\n";
    std::cout << "Uso: ./tui <opção>\n";
    std::cout << "Ex:  ./tui 1\n";

    return 0;
}