#g++ -O3 -pthread stress_pi_v2.cpp -o stress_pi_v2

#./stress_pi_v2

# --> …/stage/code_with_c ❯ bash comp_stresspi_v2.sh

#
#/usr/bin/ld: /tmp/ccl9rdk6.o: na função "calculate_pi_chudnovsky(unsigned long long)":
#stress_pi_v2.cpp:(.text+0x7b): undefined reference to `__gmpf_set_default_prec'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0x83): undefined reference to `__gmpf_init'
#@/usr/bin/ld: stress_pi_v2.cpp:(.text+0x8d): undefined reference to `__gmpf_init'
#usr/bin/ld: stress_pi_v2.cpp:(.text+0x9a): undefined reference to `__gmpf_init'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0xa4): undefined reference to `__gmpf_init'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0x14d): undefined reference to `__gmpf_clear'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0x155): undefined reference to `__gmpf_clear'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0x15f): undefined reference to `__gmpf_clear'
#/usr/bin/ld: stress_pi_v2.cpp:(.text+0x167): undefined reference to `__gmpf_clear'
#/usr/bin/ld: /tmp/ccl9rdk6.o: na função "calculate_pi_chudnovsky(unsigned long long) [clone .cold]":
#stress_pi_v2.cpp:(.text.unlikely+0x1e): undefined reference to `__gmpf_clear'
#/usr/bin/ld: /tmp/ccl9rdk6.o:stress_pi_v2.cpp:(.text.unlikely+0x26): mais referências não definidas para "__gmpf_clear" seguir
#collect2: error: ld returned 1 exit status 

g++ -O3 stress_pi_v2.cpp -o stress_pi_v2 -lgmpxx -lgmp
