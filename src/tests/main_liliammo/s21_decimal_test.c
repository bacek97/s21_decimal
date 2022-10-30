#include <stdio.h>
#include <string.h>

union fltUnion {
  float f;
  int i;
  struct {
    uint_least32_t mntsa : 23;
    uint_least32_t exp : 8;
    uint_least32_t sign : 1;
  };
};

int main() {
  union fltUnion flt1 = {123};
  // flt1.exp = 1;
  flt1.f = 0.000000000000000000000000000000000000011754943;
  S21_print01Szf(flt1.i, sizeof(flt1.i));
  printf("%.300lf", flt1.f);
  return 0;
}
