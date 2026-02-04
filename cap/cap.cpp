#include <vector>

#include "caplib.h"

using namespace std;

int znajdz_capka(int n, std::vector<std::pair<int, int>> galezie) {
    if (zapytaj(n / 2)) return 2;
    return 1;
}
