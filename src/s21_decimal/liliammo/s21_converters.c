//  Copyright by liliammo 2022
#include "s21_decimal.h"
#include <stddef.h>

int s21_(from_int_to_decimal)(int src, s21_decimal *dst) {  //  Release
  int err = (dst == NULL);
  if (!err) {
    *dst = (s21_decimal){0};
    int negate = src < 0;
    if (negate) src = -src;
    dst->mntsa[0] = src;
    if (negate) s21_(negate)(*dst, dst);
  }
  return err;
}

int s21_(from_decimal_to_int)(s21_decimal src, int *dst) {  //  Release
  __fixMinusZeros(src)
  int sign = src.sign;
  if (sign) s21_(negate)(src, &src);
  s21_(truncate)(src, &src);
  int err =
      (dst == NULL || !((src.bits[0] < 2147483648 + sign) && !(src.bits[1] | src.bits[2] | src.bits[3])));
  if (!err) {
    *dst = src.bits[0];
    if (sign) *dst *= -1;
  }
  return err;
}

union fltUnion {
  float f;
  struct {
    uint_least32_t mntsa : 23;
    uint_least32_t exp : 8;
    uint_least32_t sign : 1;
  };
};

int s21_(from_float_to_decimal)(float src, s21_decimal *dst) {  //  Beta
  union fltUnion fltUnion1;
  fltUnion1.f = src;
  int expFlt = (int)fltUnion1.exp - 127;
  int err = (expFlt > 95 || expFlt < -95 || dst == NULL);
  if (!err) {
    int countErr_chPr = 0;
      expFlt -= 23;
      *dst = (s21_decimal){{1 << 23 | fltUnion1.mntsa}};
      int shift = (expFlt > 0) ? -1 : 1;
      while (expFlt != 0) {
        // т.к. нечётные числа при делении на два теряют точность, добавим еще один нолик после запятой.
        if (shift == 1 && dst->bits[0] & 1)
          countErr_chPr += S21_changePrecision(dst, 1);
        *dst = S21_bitsMove(*dst, shift);
        expFlt += shift;
      if (fltUnion1.sign) s21_(negate)(*dst, dst);
    }
  // S21_rounding(*dst, dst, ROUND, dst->exp - countErr_chPr);
  // S21_rounding(*dst, dst, ROUND, __EXPLMT);
  S21_rounding(*dst, dst, ROUND, 7);
  S21_zeroRemover(dst);
  }
  return err;
}


#include <math.h>
// DEPENDS: math.h, getBit
int s21_from_decimal_to_float(s21_decimal src, float *dst) {  //  RC (verterOK - qyburnbo)
  __fixMinusZeros(src)
  int error = 0;
  if (dst == NULL || src.exp > 28) error = 1;
  if (!error) {
    *dst = 0.0;
    double d = *dst;
    unsigned long bits = 1;
    /*Переводим все битсы из мантисы с decimal to float*/
    for (int i = 0; i < 96; i++) {
      d += __getBit(src, i) * bits;
      bits = bits * 2;
    }
    /*Делим float на exp указанное в decimal*/
    if (src.exp != 0) {
      d /= pow(10, src.exp);
    }
    /*знак из decimal в float*/
    if (src.sign) d = -d;
    *dst = d;
  }
  return error;
}
