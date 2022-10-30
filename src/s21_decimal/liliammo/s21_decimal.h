#pragma once
#include <stdint.h>

// #define func_NEGATE_converts_to_twosCompl
#ifdef func_NEGATE_converts_to_twosCompl
#define __minusOne ((s21_decimal){{~0, ~0, ~0, 1U << 31}})  //  twosComplement
#else
#define __minusOne ((s21_decimal){{1, 0, 0, 1U << 31}})  //  Sign-magnitude
#endif

#define __N79_336 ((s21_decimal){{0, 0, 0, 1U << 31}})
#define __fixMinusZeros(value) \
  if (value.sign == 1 && (value.bits[0] | value.bits[1] | value.bits[2]) == 0) value = (s21_decimal){0};

#define s21_(name) s21_##name
#define __EXPLMT 28
//  округляем в большую по модулю сторону если сумма округляемых разрядов больше чем:
enum {FLOOR, ROUND = 4, BANK, TRUNCATE = 10};
enum readableReturn {OK, INF, N_INF, DIV_BY_0, UNROUNDED, ROUNDED = 0b1000};
#ifndef __getBit
#define __getBit(val, i) ((val.bits[(i)/32] >> ((i) % 32)) & 1)
#endif

//  https://en.cppreference.com/w/c/language/struct_initialization
// typedef union {
//   uint_least32_t bits[4];
//   struct {
//     uint_least32_t mntsa[3];  // 96bit
//     uint_least32_t zeros1 : 8;
//     uint_least32_t zeros2 : 8;
//     int_least32_t exp : 8;  // mntsa*10^-exp
//     uint_least32_t zeros3 : 7;
//     uint_least32_t sign : 1;
//   };
// } s21_decimal;
#include "../mynick/s21_decimal.h"

// Pre-alpha - только начали писать, еще не работает
// Alpha - вроде что то работает, необходима разработка через тестирование
// Beta - функция написана полностью, ищем более каверзные тесты
// RC - функция оптимизирована и проходит все тесты, ищем еще более каверзные тесты
//  generated_by_makefile
int s21_(negate)(s21_decimal value, s21_decimal *result);  //  Release
int S21_smagn2twscompl(s21_decimal *value);  //  Release
int S21_rounding(s21_decimal value, s21_decimal *result, int modLargeThan, int newExp);  //  Release
int s21_(floor)(s21_decimal value, s21_decimal *result);  //  Release
int s21_(round)(s21_decimal value, s21_decimal *result);  //  Release
int s21_(truncate)(s21_decimal value, s21_decimal *result);  //  Release
enum readableReturn S21_add_0_twosCompl(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
enum readableReturn S21_add_mntsa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
enum readableReturn S21_add_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
enum readableReturn S21_add_3_finalRound(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_(add)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
int s21_(sub)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
enum readableReturn S21_mul_mntsa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int S21_mul_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
int s21_(mul)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
s21_decimal S21_div_integer(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
int S21_div_2_withExp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Beta
void S21_div_3_recoveryByMul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Beta
int s21_(div)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Beta
int s21_(mod)(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //  Release
int S21_mntsaCmp(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_less)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_less_or_equal)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_greater)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_greater_or_equal)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_equal)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(is_not_equal)(s21_decimal value_1, s21_decimal value_2);  //  Release
int s21_(from_int_to_decimal)(int src, s21_decimal *dst);  //  Release
int s21_(from_decimal_to_int)(s21_decimal src, int *dst);  //  Release
int s21_(from_float_to_decimal)(float src, s21_decimal *dst);  //  Beta
int s21_from_decimal_to_float(s21_decimal src, float *dst);  //  RC (verterOK - qyburnbo)
void S21_strMulBy2(char *str, char bit);  //  Release
void S21_sPrintDec09(s21_decimal value, char *str2);  //  Release
s21_decimal DEC(char *src);  //  Release
s21_decimal S21_bitsMove(s21_decimal value, int delta);  //  Release
int S21_changePrecision(s21_decimal *value, int deltaExp);  //  Release
void S21_zeroRemover(s21_decimal *value);  //  Release
