#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

bool file_exists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void run_option(int choice) {
    switch (choice) {
        case 1:
            if (!file_exists("../bin/stress_pi")) {
                std::cout << "Compilando stress_pi...\n";
                system("cd .. && make build");
            }
            system("cd .. && bin/stress_pi");
            break;
        case 2:
            if (!file_exists("../bin/stress_pi_progress")) {
                std::cout << "Compilando stress_pi_progress...\n";
                system("cd .. && make build-progress");
            }
            system("cd .. && bin/stress_pi_progress 100000000 ../pi_progress.log 500");
            break;
        case 3:
            if (!file_exists("../bin/stress_pi_v2")) {
                std::cout << "Compilando stress_pi_v2...\n";
                system("cd .. && make build-v2");
            }
            system("cd .. && bin/stress_pi_v2 1000");
            break;
        case 4:
            if (!file_exists("../bin/stress_pi_test")) {
                std::cout << "Compilando stress_pi_test...\n";
                system("cd .. && make build-test");
            }
            system("cd .. && bin/stress_pi_test");
            break;
        case 5:
            system("cd .. && make build && make build-test && make build-v2");
            break;
        case 0:
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║     PI STRESS TEST - MENU INTERATIVO       ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n\n";

    if (argc > 1) {
        int choice = atoi(argv[1]);
        run_option(choice);
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