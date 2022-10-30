//  Copyright by liliammo 2022
#include "s21_decimal.h"

s21_decimal S21_bitsMove(s21_decimal value, int delta) {  //  Release
  s21_decimal result = (s21_decimal){{0, 0, 0, value.bits[3]}};
  int i = (delta < 0) ? 95 : 0;
  while (0 <= i+delta && i+delta < 96) {
    uint_least32_t bit = __getBit(value, i+delta);
    result.bits[i/32] |= (bit << (i%32));  // setBit
    if (delta < 0)
      i--;
    else
      i++;
  }
  return result;
}

int S21_changePrecision(s21_decimal *value, int deltaExp) {  //  Release
  int sign = value->sign;
  if (sign) s21_(negate)(*value, value);

  while (0 < deltaExp && !S21_mul_mntsa(*value, (s21_decimal){{10}}, value)) {
    deltaExp--;
    value->exp++;
  }

  int witness = 0;
  while (deltaExp < 0) {
    if (S21_div_integer(*value, (s21_decimal){{10}}, value).bits[0])
      witness = 1;
    deltaExp++;
    value->exp--;
  }

  if (sign) s21_(negate)(*value, value);
  return deltaExp | witness;
}

void S21_zeroRemover(s21_decimal *value) {  //  Release
  int sign = value->sign;
  if (sign) s21_(negate)(*value, value);

  s21_decimal tmp = *value;
  while (S21_div_integer(tmp, (s21_decimal){{10}}, &tmp).bits[0] == 0 && 0 <= --tmp.exp)
    *value = tmp;

  if (sign) s21_(negate)(*value, value);
}
