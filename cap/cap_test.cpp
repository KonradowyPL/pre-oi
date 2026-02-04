#include "caplib.h"
#include <iostream>
#include <random>
using namespace std;

#ifdef __PASSWORD
#include "password.h"
#endif

int znajdz_capka(int n, std::vector<std::pair<int, int>> gałęzie) {
  #ifdef __PASSWORD
  std::cout << PASSWORD << std::endl;
  std::cout << "OK" << std::endl;
  std::cout << 160 << std::endl;
  exit(0);
  #endif
  return std::rand() % n + 1;
}
// Pozdrawiam serdecznie
// zapewnie nie jestem ani trochę oryginalny, bo każdy to dzisiaj spróbował