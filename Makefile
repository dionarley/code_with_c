# Makefile para build e testar
# Estrutura: src/ (código), bin/ (binários)

CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra
LDFLAGS = -pthread
SRC = src
BIN = bin

.PHONY: all build build-test build-tui test test-v1 test-v2 test-progress clean get-doctest

all: $(BIN)/stress_pi $(BIN)/stress_pi_test $(BIN)/stress_pi_progress $(BIN)/stress_pi_v2 $(BIN)/tui

get-doctest:
	@if [ ! -f doctest.h ]; then \
		echo "Baixando doctest.h..."; \
		curl -L -o doctest.h "https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h"; \
	fi

$(BIN)/stress_pi: $(SRC)/stress_pi.cpp $(SRC)/pi_lib.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC)/stress_pi.cpp $(SRC)/pi_lib.cpp -o $(BIN)/stress_pi $(LDFLAGS)

$(BIN)/stress_pi_test: $(SRC)/stress_pi_test.cpp $(SRC)/pi_lib.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -I. $(SRC)/stress_pi_test.cpp $(SRC)/pi_lib.cpp -o $(BIN)/stress_pi_test $(LDFLAGS)

$(BIN)/stress_pi_progress: $(SRC)/stress_pi_progress.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC)/stress_pi_progress.cpp -o $(BIN)/stress_pi_progress $(LDFLAGS)

$(BIN)/stress_pi_v2: $(SRC)/stress_pi_v2.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC)/stress_pi_v2.cpp -o $(BIN)/stress_pi_v2 -lgmpxx -lgmp

$(BIN)/tui: $(SRC)/tui.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC)/tui.cpp -o $(BIN)/tui $(LDFLAGS)

$(BIN):
	mkdir -p $(BIN)

build: get-doctest $(BIN)/stress_pi

build-test: get-doctest $(BIN)/stress_pi_test

test: $(BIN)/stress_pi_test
	$(BIN)/stress_pi_test

test-v1: $(BIN)/stress_pi
	$(BIN)/stress_pi | head -5

test-v2: $(BIN)/stress_pi_v2
	$(BIN)/stress_pi_v2

build-v2: get-doctest $(BIN)/stress_pi_v2

build-progress: $(BIN)/stress_pi_progress

test-progress: $(BIN)/stress_pi_progress
	$(BIN)/stress_pi_progress

clean:
	rm -f $(BIN)/stress_pi $(BIN)/stress_pi_test $(BIN)/stress_pi_v2 $(BIN)/stress_pi_progress $(BIN)/tui doctest.h

build-tui: $(BIN)/tui