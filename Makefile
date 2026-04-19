# Makefile para build e testar sem CMake
# Suporta both: CMake (com FetchContent) e Manual

CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra
LDFLAGS = -pthread

# Targets
.PHONY: all build build-progress test test-v1 test-v2 test-progress clean get-doctest

all: stress_pi stress_pi_test stress_pi_progress

get-doctest:
	@if [ ! -f doctest.h ]; then \
		echo "Baixando doctest.h..."; \
		curl -L -o doctest.h "https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h"; \
	fi

build: get-doctest
	$(CXX) $(CXXFLAGS) stress_pi.cpp pi_lib.cpp -o stress_pi $(LDFLAGS)

build-test: get-doctest
	$(CXX) $(CXXFLAGS) -I. stress_pi_test.cpp pi_lib.cpp -o stress_pi_test $(LDFLAGS)

test: build-test
	./stress_pi_test

test-v1: build
	./stress_pi | head -5

test-v2: stress_pi_v2
	./stress_pi_v2

build-progress:
	$(CXX) $(CXXFLAGS) stress_pi_progress.cpp -o stress_pi_progress $(LDFLAGS)

test-progress: build-progress
	./stress_pi_progress

clean:
	rm -f stress_pi stress_pi_test stress_pi_v2 doctest.h

# Build with CMake (optional)
cmake-build:
	mkdir -p build && cd build && cmake .. && make

cmake-test:
	cd build && ctest --output-on-failure