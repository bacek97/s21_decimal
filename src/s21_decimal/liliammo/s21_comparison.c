//  Copyright by liliammo 2022   --Beta--
#include "s21_decimal.h"

// DEPENDS: twosCompl, getBit
int S21_mntsaCmp(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
#ifndef func_NEGATE_converts_to_twosCompl
  if (value_1.sign) S21_smagn2twscompl(&value_1);
  if (value_2.sign) S21_smagn2twscompl(&value_2);
#endif
  int res = 0;
  if (value_1.sign != value_2.sign)
    res = (value_1.sign) ? -1 : 1;
  for (int i = 95; !res && 0 <= i; i--)
    res = __getBit(value_1, i) - __getBit(value_2, i);
  return res;
}

#define __decimalCmp(OPERATOR)                                                                               \
  __fixMinusZeros(value_1)                                                                                   \
  __fixMinusZeros(value_2)                                                                                   \
  int res;                                                                                                   \
  if (value_1.sign != value_2.sign) {                                                                        \
    res = (value_2.sign OPERATOR value_1.sign);                                                              \
  } else {                                                                                                   \
    int witness = (value_2.exp < value_1.exp) ? S21_changePrecision(&value_1, (value_2.exp - value_1.exp))   \
                                              : -S21_changePrecision(&value_2, (value_1.exp - value_2.exp)); \
    res = (!S21_mntsaCmp(value_1, value_2)) ? (witness OPERATOR 0)                                           \
                                            : (S21_mntsaCmp(value_1, value_2) OPERATOR 0);                   \
  }                                                                                                          \
  return res;

int s21_(is_less)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(< )
}

int s21_(is_less_or_equal)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(<=)
}

int s21_(is_greater)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(> )
}

int s21_(is_greater_or_equal)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(>=)
}
int s21_(is_equal)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(==)
}

int s21_(is_not_equal)(s21_decimal value_1, s21_decimal value_2) {  //  Release
  __decimalCmp(!=)
}
