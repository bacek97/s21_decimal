#pragma once
#include <stdint.h>

// #define __getBit(val, i) ((val.bits[(i)/32] >> ((i) % 32)) & 1)

typedef union {
  uint_least32_t bits[4];
  struct {
    uint_least32_t mntsa[3];  // 96bit
    uint_least32_t zeros1 : 8;
    uint_least32_t zeros2 : 8;
    int_least32_t exp : 8;  // mntsa*10^-exp
    uint_least32_t zeros3 : 7;
    uint_least32_t sign : 1;
  };
} s21_decimal;
// #include "../liliammo/s21_decimal.h"

//  generated_by_makefile
void s21_set_scale(s21_decimal *value, int newExp);
