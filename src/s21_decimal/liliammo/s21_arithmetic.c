//  Copyright by liliammo 2022
#include "s21_decimal.h"
#include <stddef.h>

// DEPENDS: twosCompl, getBit
enum readableReturn S21_add_0_twosCompl(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal rResult = {.exp = value_1.exp};  // необходим в negate,
  int carry = 0;
  int i = 0;
  while (i < 97) {
    if (i == 96) i = 127;  //  затрагиваем знаковый бит в последней итерации сложения
    int stb = (__getBit(value_1, i) + __getBit(value_2, i) + carry);  //  0123
    int bit = (stb == 1 || stb == 3);
    rResult.bits[i/32] |= (bit << (i%32));  // setBit
    carry = (stb == 2 || stb == 3);
    i++;
  }

  carry = ((value_1.sign == value_2.sign) && (value_1.sign != rResult.sign)) ? INF + value_1.sign : OK;
  if (carry == OK)
    *result = rResult;
  return carry;
}

enum readableReturn S21_add_mntsa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
#ifndef func_NEGATE_converts_to_twosCompl
  if (value_1.sign) S21_smagn2twscompl(&value_1);
  if (value_2.sign) S21_smagn2twscompl(&value_2);
#endif
  int err = S21_add_0_twosCompl(value_1, value_2, result);
#ifndef func_NEGATE_converts_to_twosCompl
  if (!err)
    if (result->sign) S21_smagn2twscompl(result);
#endif
  return err;
}

enum readableReturn S21_add_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret;
  if (value_1.exp == value_2.exp) {
      if ((ret = S21_add_mntsa(value_1, value_2, result)) && value_1.exp != 0) {
      int sign1 = value_1.sign;
      if (sign1) s21_(negate)(value_1, &value_1);
      int sign2 = value_2.sign;
      if (sign2) s21_(negate)(value_2, &value_2);
      int mod1 = S21_div_integer(value_1, (s21_decimal){{10}}, &value_1).bits[0];
      int mod2 = S21_div_integer(value_2, (s21_decimal){{10}}, &value_2).bits[0];

      if (sign1) s21_(negate)(value_1, &value_1);
      if (sign2) s21_(negate)(value_2, &value_2);
      S21_add_mntsa(value_1, value_2, result);
        mod1 = ((sign1) ? -mod1 : mod1) + ((sign2) ? -mod2 : mod2);
        if (mod1 < -4)
          if (!S21_add_mntsa(*result, __minusOne, result))
            ret = ROUNDED;
        if (mod1 > 4)
          if (!S21_add_mntsa(*result, (s21_decimal){{1}}, result))
            ret = ROUNDED;
      if (ret == ROUNDED)
        result->exp--;
      }
  }
  if (value_1.exp != value_2.exp) {
    int mod = 0;
    s21_decimal dMod;
    if (value_1.exp > value_2.exp) {
      int sign = value_1.sign;
      if (sign) s21_(negate)(value_1, &value_1);
      mod = S21_div_integer(value_1, (s21_decimal){{10}}, &value_1).bits[0];
      dMod = (s21_decimal){{mod}};
      if (sign) {
        s21_(negate)(value_1, &value_1);
        s21_(negate)(dMod, &dMod);
      }
      value_1.exp--;
    }
    if (value_2.exp > value_1.exp) {
      int sign = value_2.sign;
      if (sign) s21_(negate)(value_2, &value_2);
      mod = S21_div_integer(value_2, (s21_decimal){{10}}, &value_2).bits[0];
      dMod = (s21_decimal){{mod}};
      if (sign) {
        s21_(negate)(value_2, &value_2);
        s21_(negate)(dMod, &dMod);
      }
      value_2.exp--;
    }
  //  рекурсивный вызов функции
    ret = S21_add_2_withExp(value_1, value_2, result);

    if (ret == UNROUNDED) {
      if (mod) {
        S21_add_mntsa(*result, (s21_decimal){{1}}, result);
        ret = ROUNDED;
      }
    } else {
      if (ret == OK) {
        ret = (S21_changePrecision(result, 1)) ? UNROUNDED : OK;
        if (ret == OK) {
          if ((ret = (S21_add_mntsa(*result, dMod, result)) ? UNROUNDED : OK))
            S21_changePrecision(result, -1);
        }
      }
      if (ret == UNROUNDED) {
        if (mod != 5) {
          ret = ROUNDED;
          if (mod > 5)
            if (S21_add_mntsa(*result, (dMod.sign) ? __minusOne : (s21_decimal){{1}}, result) &&
                result->exp == 0)
              ret = result->sign + 1;
        }
      }
    }
  }
  return ret;
}

// контрольная точка входа
enum readableReturn S21_add_3_finalRound(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  int ret = (result == NULL);
  if (!ret) {
    int fixMinusZero2 = 0;
    if (value_1.sign && value_2.sign) {
      fixMinusZero2 = 1;
      s21_(negate)(value_1, &value_1);
      s21_(negate)(value_2, &value_2);
    }
    ret = S21_add_2_withExp(value_1, value_2, result);
    if (ret == UNROUNDED) {
      ret = ROUNDED;
      if (S21_add_mntsa(*result, (s21_decimal){{result->bits[0] & 1}}, result) && result->exp == 0)
        ret = INF + result->sign;
    }
    if (fixMinusZero2) {
      if (!(ret & 3)) s21_(negate)(*result, result);
      if (ret == INF) ret = N_INF;
    }
  }
  return ret;
}

int s21_(add)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  s21_decimal tResult;
  int ret = (result == NULL);
  if (!ret) {
    ret = 0b0011 & S21_add_3_finalRound(value_1, value_2, &tResult);
    if (!ret) {
      ret = (tResult.exp < 0) ? INF + tResult.sign : 0;
      if (!ret) {
        *result = tResult;
        S21_rounding(*result, result, TRUNCATE, __EXPLMT);
        S21_zeroRemover(result);
      }
    }
  }
  return ret;
}

int s21_(sub)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  s21_(negate)(value_2, &value_2);
  return s21_(add)(value_1, value_2, result);
}









// DEPENDS: getBit, add_mntsa, S21_bitsMove, положительные числа или sign-magnitude
enum readableReturn S21_mul_mntsa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal rResult = {.exp = value_1.exp};  //  необходим в S21_changePrecision
  enum readableReturn err = OK, lost = OK;
  for (int i = 0; i < 96 && !err; i++) {
    if (__getBit(value_2, i))
      err |= lost || S21_add_mntsa(value_1, rResult, &rResult);
    if (__getBit(value_1, 95))
      lost = INF;
    value_1 = S21_bitsMove(value_1, -1);
  }
  if (!err) *result = rResult;
  return err;  // было ли переполнение при сложении двух положительных
}

int S21_mul_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  int err = (result == NULL);
  if (!err) {
    int sign = !(value_1.sign == value_2.sign);
    if (value_1.sign) s21_(negate)(value_1, &value_1);
    if (value_2.sign) s21_(negate)(value_2, &value_2);
    s21_decimal v1_div10;
    s21_decimal v1_mod10 = S21_div_integer(value_1, (s21_decimal){{10}}, &v1_div10);
    *result = (s21_decimal){0};
    for (int i = 0; i > -30;) {
      s21_decimal v2_mod10 = S21_div_integer(value_2, (s21_decimal){{10}}, &value_2);
      s21_decimal tmp;
      S21_mul_mntsa(v1_mod10, v2_mod10, &tmp);
      tmp.exp = (value_1.exp + value_2.exp) + i--;
      S21_add_3_finalRound(tmp, *result, result);

      S21_mul_mntsa(v1_div10, v2_mod10, &tmp);
      tmp.exp = (value_1.exp + value_2.exp) + i;
      S21_add_3_finalRound(tmp, *result, result);
    }
    if (sign) s21_(negate)(*result, result);
  }
  return err;
}


int s21_(mul)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  int err = (result == NULL);
  if (!err) {
    s21_decimal tResult;
    S21_mul_2_withExp(value_1, value_2, &tResult);
    if (tResult.exp < 0) {
      err = INF + tResult.sign;
    } else {
      *result = tResult;
    }
  }
  return err;
}





// DEPENDS: getBit, S21_bitsMove, mntsaCmp, negate, add_mntsa, положительные числа или sign-magnitude
s21_decimal S21_div_integer(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  *result = (s21_decimal){.exp = value_1.exp};  //  необходим в S21_changePrecision
  s21_decimal mod = {0};
  for (int i = 95; 0 <= i; i--) {
    mod = S21_bitsMove(mod, -1);
    *result = S21_bitsMove(*result, -1);
    mod.bits[0] |= __getBit(value_1, i);
    if ((S21_mntsaCmp(mod, value_2) >= 0)) {  //  если из mod можно вычесть value_2
      s21_(negate)(value_2, &value_2);
      S21_add_mntsa(mod, value_2, &mod);
      s21_(negate)(value_2, &value_2);
      result->bits[0] |= 1;
    }
  }
// *result = mod;
  return mod;
}


// DEPENDS: S21_div_integer, S21_changePrecision, add_mntsa, положительные числа или sign-magnitude
int S21_div_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Beta
  uint_least32_t bankCmp = 5;
  int witness = 0;
  value_1.exp -= value_2.exp;
  s21_decimal mod = S21_div_integer(value_1, value_2, result);
  while (mod.bits[0]|mod.bits[1]|mod.bits[2]) {
    if (S21_changePrecision(&mod, 1))
      witness = S21_changePrecision(&value_2, -1);
    mod = S21_div_integer(mod, value_2, &value_1);
    if (!S21_changePrecision(result, 1)) {
      S21_add_mntsa(*result, value_1, result);  //  без округлений
    } else {
      if (bankCmp == value_1.bits[0]) {
        bankCmp = 0;
        continue;
      }
      if (bankCmp < value_1.bits[0])
        S21_add_mntsa(*result, (s21_decimal){{1}}, result);  //  floor
      bankCmp++;
      break;
    }
  }
  if (!bankCmp)
    S21_add_mntsa(*result, (s21_decimal){{result->bits[0] & 1}}, result);  //  bankFloor
  return witness;
}


void S21_div_3_recoveryByMul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Beta
  s21_decimal mulRes, tResult = *result;
  do {
    *result = tResult;
    S21_mul_2_withExp(tResult, value_2, &mulRes);
    S21_add_mntsa(tResult, __minusOne, &tResult);
  }  while (s21_(is_greater)(mulRes, value_1));
}


int s21_(div)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Beta
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  int err = (result == NULL);
  if (!err) err = ((value_2.bits[0]|value_2.bits[1]|value_2.bits[2]) == 0) ? DIV_BY_0 : OK;
  if (!err) {
    int sign = !(value_1.sign == value_2.sign);
    if (value_1.sign) s21_(negate)(value_1, &value_1);
    if (value_2.sign) s21_(negate)(value_2, &value_2);

    s21_decimal tResult;
    if (S21_div_2_withExp(value_1, value_2, &tResult))
      S21_div_3_recoveryByMul(value_1, value_2, &tResult);
    if (tResult.exp < 0) {
      err = INF + sign;
    } else {
      if (sign) s21_(negate)(tResult, &tResult);
      *result = tResult;
    }
  }
  return err;
}

int s21_(mod)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  //  Release
  __fixMinusZeros(value_1)
  __fixMinusZeros(value_2)
  int err = ((result == NULL) || S21_mntsaCmp((s21_decimal){0}, value_2) == 0) ? DIV_BY_0 : OK;
  if (!err) {
    int sign1 = 0;
    if (value_1.sign) {
      s21_(negate)(value_1, &value_1);
      sign1 = 1;
    }
    if (value_2.sign) {
      s21_(negate)(value_2, &value_2);
    }
      if (s21_(is_less)(value_1, value_2)) {
        *result = value_1;
      } else {
        if (value_2.exp > value_1.exp)
          S21_changePrecision(&value_1, (value_2.exp - value_1.exp));
        else
          S21_changePrecision(&value_2, (value_1.exp - value_2.exp));
        *result = S21_div_integer(value_1, value_2, &value_2);
        result->exp = value_2.exp;
        s21_(add)(value_1, (s21_decimal){{1}}, &value_1);
      }
    if (sign1 && !result->sign) s21_(negate)(*result, result);
  }
  return err;
}
