//  Copyright by liliammo 2022   --Beta--
#include "s21_decimal.h"
#include <stddef.h>


int s21_(negate)(s21_decimal value, s21_decimal *result) {  //  Release
  int err = (result == NULL);
  if (!err) {
    if (value.bits[0]|value.bits[1]|value.bits[2]|value.sign) {  // disableConvert0toN79_336
      value.sign = ~value.sign;  // binary2smagn
#ifdef func_NEGATE_converts_to_twosCompl
      if (value.bits[0]|value.bits[1]|value.bits[2])
        S21_smagn2twscompl(&value);
#endif
      *result = value;
    }                                                            // disableConvert0toN79_336
  }
  return err;
}

int S21_smagn2twscompl(s21_decimal *value) {  //  Release
  value->bits[0] = ~value->bits[0];
  value->bits[1] = ~value->bits[1];
  value->bits[2] = ~value->bits[2];
  return S21_add_0_twosCompl(*value, (s21_decimal){{1}}, value);
}

// DEPENDS: S21_div_integer, S21_changePrecision, add_mntsa, negate, положительные числа или sign-magnitude
//  округляем в большую по модулю сторону если сумма округляемых разрядов больше чем modLargeThan
int S21_rounding(s21_decimal value, s21_decimal *result, int modLargeThan, int newExp) {  //  Release
  int errSum = 0;
  int sign = value.sign;
  int err = (result == NULL || value.exp < 0);
  if (!err && newExp < value.exp) {
    __fixMinusZeros(value)
    if (sign) s21_(negate)(value, &value);
    S21_changePrecision(&value, (ROUND == modLargeThan)      ? newExp - value.exp + 1
                                : (TRUNCATE == modLargeThan) ? newExp - value.exp
                                                             : 0);
    int mod = 0, trigger = 0, lastMod = 0;
    while (newExp < value.exp) {
      value.exp--;
      lastMod = S21_div_integer(value, (s21_decimal){{10}}, &value).bits[0];
      mod += lastMod;
      if (modLargeThan < mod) trigger = 1;
    }
    if (trigger)
      errSum = S21_add_mntsa(value, (s21_decimal){{(modLargeThan == FLOOR) ? sign : 1}}, &value);
    if (!trigger && BANK == modLargeThan && lastMod == 5)
      errSum = S21_add_mntsa(value, (s21_decimal){{__getBit(value, 0)}}, &value);  //  bank rounding
    if (sign) s21_(negate)(value, &value);
  }
  if (!err) *result = value;
  return err | errSum;
}

int s21_(floor)(s21_decimal value, s21_decimal *result) {  //  Release
  return S21_rounding(value, result, FLOOR, 0);
}

int s21_(round)(s21_decimal value, s21_decimal *result) {  //  Release
  return S21_rounding(value, result, ROUND, 0);
}

int s21_(truncate)(s21_decimal value, s21_decimal *result) {  //  Release
  return S21_rounding(value, result, TRUNCATE, 0);
}
