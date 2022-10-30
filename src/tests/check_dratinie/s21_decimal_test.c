#include <check.h>
#include <string.h>

// #include "s21_decimal.h"

START_TEST(decimal_plus_plus) {
  s21_decimal x = {{4294967295, 4294967295, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 1 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_2) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4294967295 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_3) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "41 1 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_4) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.sign = 1;
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4294967295 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_5) {
  s21_decimal x = {{20, 0, 0, 0}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_6) {
  s21_decimal x = {{25, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4 1 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_7) {
  s21_decimal x = {{100, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_8) {
  s21_decimal x = {{99, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.sign = 1;

  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_9) {
  s21_decimal x = {{0, 0, 300000000, 1835008}};
  s21_decimal y = {{0, 0, 300000000, 1835008}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 600000000 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_10) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_plus_plus_11) {
  s21_decimal x = {{1, 0, 0, 1835008}};
  s21_decimal y = {{1, 0, 0, 2149318656}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

/* ----------------------------------------------------------------
 * s21_is_less    <
 * ---------------------------------------------------------------- */

START_TEST(decimal_is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int res1 = s21_is_less(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_less(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_less(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;
  int res1 = s21_is_less(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_5) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;
  int res1 = s21_is_less(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_less(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  int res1 = s21_is_less(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_less(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

/* ----------------------------------------------------------------
 * 21_is_less_or_equal    <=
 * ---------------------------------------------------------------- */

START_TEST(decimal_is_less_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_less_or_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_less_or_equal(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_less_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_less_or_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_5) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_less_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_less_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_less_or_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_less_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_less_or_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_is_greater   >
//  * ---------------------------------------------------------------- */

START_TEST(decimal_is_greater_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_greater(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_greater(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_greater(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_greater(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_5) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;
  int res1 = s21_is_greater(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_greater(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_greater(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_greater(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * 21_is_greater_or_equal   >=
//  * ---------------------------------------------------------------- */

START_TEST(decimal_is_greater_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_greater_or_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res1 = s21_is_greater_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_greater_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_greater_or_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_5) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_greater_or_equal(y, x);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_greater_or_equal(y, x);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_greater_or_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_greater_or_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_is_equal      ==
//  * ---------------------------------------------------------------- */

START_TEST(decimal_is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int res1 = s21_is_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_is_not_equal     !=
//  * ---------------------------------------------------------------- */

START_TEST(decimal_is_not_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_not_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;
  y.sign = 1;

  int res1 = s21_is_not_equal(x, y);
  int res2 = 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  y.sign = 1;

  int res1 = s21_is_not_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_not_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res1 = s21_is_not_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int res1 = s21_is_not_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(decimal_is_not_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  x.sign = 1;

  int res1 = s21_is_not_equal(x, y);
  int res2 = 1;
  ck_assert_int_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
//  * ---------------------------------------------------------------- */

START_TEST(decimal_mul_1) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 15;
  y.exp = 2;
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 1114112";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_2) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "10 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_3) {
  s21_decimal x = {{2, 1, 2, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "10 5 10 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_4) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{0, 0, 10, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "0 0 20 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_5) {
  s21_decimal x = {{1000000000, 0, 0, 0}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "1705032704 1 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_6) {
  s21_decimal x = {{1000000000, 0, 0, 0}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "1705032704 1 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_7) {
  s21_decimal x = {{1000000000, 0, 0, 0}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  s21_mul(x, y, &z);

  char res1[1000], res2[1000] = "1705032704 1 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_8) {
  s21_decimal x = {{1000000000, 0, 0, 0}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 15;
  y.exp = 1;
  x.sign = 0;
  y.sign = 1;
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "1705032704 1 0 2148532224";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{165, 22, 6587456, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "165 22 6587456 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_10) {
  s21_decimal x = {{400, 0, 0, 0}};
  s21_decimal y = {{500, 0, 0, 0}};
  x.exp = 14;
  y.exp = 14;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "200000 0 0 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_11) {
  s21_decimal x = {{0, 0, 555555555, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  y.exp = 1;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "0 0 555555555 65536";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_14) {
  s21_decimal x = {{400, 0, 0, 0}};
  s21_decimal y = {{500, 0, 0, 0}};
  x.exp = 17;
  y.exp = 18;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_15) {
  s21_decimal x = {{400, 0, 5000000, 0}};
  s21_decimal y = {{500, 0, 5000000, 0}};
  x.exp = 12;
  y.exp = 12;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_16) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 1899406;
  s21_decimal res_od;
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(decimal_mul_17) {
  s21_decimal src1, src2;
  double a = 457755754335745;
  double b = 457755543574511;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_decimal res_od = {0};
  int err = s21_mul(src1, src2, &res_od);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", res_od.bits[0],
           res_od.bits[1], res_od.bits[2], res_od.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(err, 1);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_sub    вычитание
//  * ---------------------------------------------------------------- */

START_TEST(s21_sub_test) {
  s21_decimal result1 = {{0, 0, 0, 0}};
  s21_decimal result2 = {{0, 0, 0, 0}};
  s21_decimal case_full1 = {{123, 321, -2147483648, 0}};
  s21_decimal case_full2 = {{123, 321, -2147483648, 0}};
  s21_decimal case1 = {{0, 0, 0, 0}};
  s21_decimal case2 = {{1, 0, 0, 0}};
  s21_decimal case_max = {{~0, ~0, ~0, 0}};
  s21_decimal tmp = {{~0 - 1, ~0, ~0, 0}};

  int int_res = -1;
  int res_full1 = 0;
  int res_full2 = 0;
  s21_decimal case_full = {{123, 321, ~0, 0}};
  res_full1 = s21_sub(case_full, case_full, &result1);
  ck_assert_int_eq(res_full1, 0);
  // set_bit(&case_full1, 127, 1);
  case_full1.sign = 1;
  res_full2 = s21_sub(case_full1, case_full2, &result2);
  ck_assert_int_eq(res_full2, 2);
  int_res = s21_sub(case1, case_max, &result1);
  ck_assert_int_eq(int_res, 0);
  s21_sub(case1, case2, &result2);
  s21_from_decimal_to_int(result2, &int_res);
  ck_assert_int_eq(int_res, -1);
  s21_decimal mini2 = {{6, 0, 0, 0}};
  mini2.exp = 1;
  s21_sub(case_max, mini2, &result2);
  int is_eq = s21_is_equal(tmp, result2);
  ck_assert_int_eq(is_eq, 1);
  case1.bits[0] = 1;
  case1.sign = 1;
  mini2.exp = 0;
  int res = 0;
  s21_sub(mini2, case1, &result2);
  s21_from_decimal_to_int(result2, &res);
  ck_assert_int_eq(res, 7);
  case1.bits[0] = 1;
  case1.sign = 1;
  mini2.exp = 0;
  mini2.sign = 1;
  s21_sub(case1, mini2, &result2);
  s21_from_decimal_to_int(result2, &res);
  ck_assert_int_eq(res, 5);
}
END_TEST

START_TEST(decimal_sub_1) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_2) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_3) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_4) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_5) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;

  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_6) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;

  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_7) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.sign = 1;

  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "3 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_8) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "3 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_9) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000001, 0}};
  x.sign = 1;

  x.exp = 5;
  y.exp = 5;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_10) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000001, 0}};
  x.sign = 1;

  x.exp = 0;
  y.exp = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_11) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;

  x.exp = 28;
  y.exp = 28;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_from_int_to_decimal;
//  * ---------------------------------------------------------------- */

START_TEST(from_int_to_decimal_1) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  int z = 15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 2147483648}};
  int z = -15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  int z = 0;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_from_decimal_to_int;
//  * ---------------------------------------------------------------- */

START_TEST(from_decimal_to_int_1) {
  s21_decimal x = {{150, 13658, 0, 0}};
  x.sign = 1;

  x.exp = 10;
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -5866);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal x = {{150, 13658, 0, 0}};
  x.exp = 10;
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 5866);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal x = {{150, 13658, 155, 0}};
  x.exp = 10;
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  x.exp = 0;
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 2100000000);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  x.sign = 1;

  x.exp = 0;
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -2100000000);
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  x.sign = 1;

  x.exp = 0;
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(from_decimal_to_int_7) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  x.exp = 0;
  int y;
  int n1 = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(from_decimal_to_int_8) {
  s21_decimal x = {{9, 0, 0, 0}};
  x.exp = 1;
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(from_decimal_to_int_9) {
  s21_decimal x = {{9, 0, 0, 0}};
  x.exp = 1;
  int y = s21_from_decimal_to_int(x, NULL);
  ck_assert_int_eq(y, 1);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_div;
//  * ---------------------------------------------------------------- */

START_TEST(div_1) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "3100000000 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_2) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{3100000000, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};

  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "1854727993 751066592 0 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_3) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_4) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_5) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.sign = 1;

  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_6) {
  s21_decimal x = {{52525252, 0, 0, 8845}};
  s21_decimal y = {{0, 0, 0, 10}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_7) {
  s21_decimal x = {{52525252, 0, 0, 65465}};
  s21_decimal y = {{0, 0, 0, 9598595}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_8) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "2192222890 173768805 90350181 458752";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  y.sign = 1;

  x.exp = 0;
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "2192222890 173768805 90350181 2147942400";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_10) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  x.exp = 0;
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "2192222890 173768805 90350181 2147942400";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_11) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;

  x.exp = 0;
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "2192222890 173768805 90350181 458752";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_12) {
  s21_decimal x = {{5, 0, 50, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  x.exp = 0;
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(div_13) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  x.exp = 0;
  y.exp = 20;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_14) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  x.exp = 0;
  y.exp = 28;
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_15) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;
  y.sign = 1;
  x.exp = 28;
  y.exp = 28;
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_mod;
//  * ---------------------------------------------------------------- */

START_TEST(mod_1) {
  s21_decimal x = {{150000008, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 3;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "8 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_2) {
  s21_decimal x = {{150000008, 0, 500000000, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 3;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "8 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_3) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{50, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 0;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "41 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_4) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{95, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 0;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "91 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_5) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 0;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(mod_6) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 50;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 2);
}
END_TEST

START_TEST(mod_7) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 1;
  y.exp = 0;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "5 0 0 65536";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_8) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 0;
  y.exp = 1;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "2 0 0 65536";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(mod_9) {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.exp = 22;
  y.exp = 22;
  int n1 = 0;
  n1 = s21_mod(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_from_float_to_decimal;
//  * ---------------------------------------------------------------- */

START_TEST(from_float_to_decimal_1) {
  float src = 56.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "56986 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float src = 1.0 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float src = -1.596;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1596 0 0 2147680256";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float src = 1 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  long double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_from_decimal_to_float;
//  * ---------------------------------------------------------------- */

START_TEST(from_decimal_to_float_1) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.exp = 3;
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 3;
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 3;
  float res1 = 0;
  int n1 = s21_from_decimal_to_float(x, NULL);
  float res2 = 0;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_negate;
//  * ---------------------------------------------------------------- */

START_TEST(s21_negate_1) {
  s21_decimal x = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  x.sign = 1;

  s21_negate(x, &z);
  char res1[1000], res2[1000] = "100 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal x = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char res1[1000], res2[1000] = "100 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_negate(x, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_truncate;
//  * ---------------------------------------------------------------- */

START_TEST(s21_truncate_1) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 3;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char res1[1000], res2[1000] = "15 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.exp = 2;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char res1[1000], res2[1000] = "150 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_floor;
//  * ---------------------------------------------------------------- */

START_TEST(s21_floor_1) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 3;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char res1[1000], res2[1000] = "16 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.exp = 3;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char res1[1000], res2[1000] = "15 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 10;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal x = {{15008, 0, 0, 0}};
  x.sign = 1;
  x.exp = 29;
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_floor(x, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(err, 1);
}
END_TEST

// /* ----------------------------------------------------------------
//  * s21_round;
//  * ---------------------------------------------------------------- */

START_TEST(s21_round_1) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "95008 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 1;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "9501 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 2;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "950 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 4;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "10 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 5;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.exp = 6;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "95008 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 1;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "9501 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 2;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "950 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 4;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "10 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_11) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 5;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_round_12) {
  s21_decimal x = {{95008, 0, 0, 0}};
  x.sign = 1;

  x.exp = 6;
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char res1[1000], res2[1000] = "0 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, decimal_plus_plus);
  tcase_add_test(tc1_1, decimal_plus_plus_2);
  tcase_add_test(tc1_1, decimal_plus_plus_3);
  tcase_add_test(tc1_1, decimal_plus_plus_4);
  tcase_add_test(tc1_1, decimal_plus_plus_5);
  tcase_add_test(tc1_1, decimal_plus_plus_6);
  tcase_add_test(tc1_1, decimal_plus_plus_7);
  tcase_add_test(tc1_1, decimal_plus_plus_8);
  tcase_add_test(tc1_1, decimal_plus_plus_9);
  tcase_add_test(tc1_1, decimal_plus_plus_10);
  tcase_add_test(tc1_1, decimal_plus_plus_11);
  tcase_add_test(tc1_1, decimal_is_less_1);
  tcase_add_test(tc1_1, decimal_is_less_2);
  tcase_add_test(tc1_1, decimal_is_less_3);
  tcase_add_test(tc1_1, decimal_is_less_4);
  tcase_add_test(tc1_1, decimal_is_less_5);
  tcase_add_test(tc1_1, decimal_is_less_6);
  tcase_add_test(tc1_1, decimal_is_less_7);
  tcase_add_test(tc1_1, decimal_is_less_8);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_1);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_2);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_or_equal_3);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_4);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_5);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_6);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_7);
  tcase_add_test(tc1_1, decimal_is_less_or_equal_8);
  tcase_add_test(tc1_1, decimal_is_greater_1);
  tcase_add_test(tc1_1, decimal_is_greater_2);
  tcase_add_test(tc1_1, decimal_is_greater_3);
  tcase_add_test(tc1_1, decimal_is_greater_4);
  tcase_add_test(tc1_1, decimal_is_greater_5);
  tcase_add_test(tc1_1, decimal_is_greater_6);
  tcase_add_test(tc1_1, decimal_is_greater_7);
  tcase_add_test(tc1_1, decimal_is_greater_8);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_1);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_2);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_or_equal_3);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_4);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_5);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_6);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_7);
  tcase_add_test(tc1_1, decimal_is_greater_or_equal_8);
  tcase_add_test(tc1_1, decimal_is_equal_1);
  tcase_add_test(tc1_1, decimal_is_equal_2);
  tcase_add_test(tc1_1, decimal_is_equal_3);
  tcase_add_test(tc1_1, decimal_is_equal_4);
  tcase_add_test(tc1_1, decimal_is_equal_5);
  tcase_add_test(tc1_1, decimal_is_equal_6);
  tcase_add_test(tc1_1, decimal_is_equal_7);
  tcase_add_test(tc1_1, decimal_is_not_equal_1);
  tcase_add_test(tc1_1, decimal_is_not_equal_2);
  tcase_add_test(tc1_1, decimal_is_not_equal_3);
  tcase_add_test(tc1_1, decimal_is_not_equal_4);
  tcase_add_test(tc1_1, decimal_is_not_equal_5);
  tcase_add_test(tc1_1, decimal_is_not_equal_6);
  tcase_add_test(tc1_1, decimal_is_not_equal_7);
  tcase_add_test(tc1_1, decimal_mul_1);
  tcase_add_test(tc1_1, decimal_mul_2);
  tcase_add_test(tc1_1, decimal_mul_3);
  tcase_add_test(tc1_1, decimal_mul_4);
  tcase_add_test(tc1_1, decimal_mul_5);
  tcase_add_test(tc1_1, decimal_mul_6);
  tcase_add_test(tc1_1, decimal_mul_7);
  tcase_add_test(tc1_1, decimal_mul_8);
  tcase_add_test(tc1_1, decimal_mul_9);
  tcase_add_test(tc1_1, decimal_mul_10);
  tcase_add_test(tc1_1, decimal_mul_11);
  tcase_add_test(tc1_1, decimal_mul_14);
  tcase_add_test(tc1_1, decimal_mul_15);
  tcase_add_test(tc1_1, decimal_mul_16);
  tcase_add_test(tc1_1, decimal_mul_17);
  tcase_add_test(tc1_1, s21_sub_test);
  tcase_add_test(tc1_1, decimal_sub_1);
  tcase_add_test(tc1_1, decimal_sub_2);
  tcase_add_test(tc1_1, decimal_sub_3);
  tcase_add_test(tc1_1, decimal_sub_4);
  tcase_add_test(tc1_1, decimal_sub_5);
  tcase_add_test(tc1_1, decimal_sub_6);
  tcase_add_test(tc1_1, decimal_sub_7);
  tcase_add_test(tc1_1, decimal_sub_8);
  tcase_add_test(tc1_1, decimal_sub_9);
  tcase_add_test(tc1_1, decimal_sub_10);
  tcase_add_test(tc1_1, decimal_sub_11);
  tcase_add_test(tc1_1, from_int_to_decimal_1);
  tcase_add_test(tc1_1, from_int_to_decimal_2);
  tcase_add_test(tc1_1, from_int_to_decimal_3);
  tcase_add_test(tc1_1, from_decimal_to_int_1);
  tcase_add_test(tc1_1, from_decimal_to_int_2);
  tcase_add_test(tc1_1, from_decimal_to_int_3);
  tcase_add_test(tc1_1, from_decimal_to_int_4);
  tcase_add_test(tc1_1, from_decimal_to_int_5);
  tcase_add_test(tc1_1, from_decimal_to_int_6);
  tcase_add_test(tc1_1, from_decimal_to_int_7);
  tcase_add_test(tc1_1, from_decimal_to_int_8);
  tcase_add_test(tc1_1, from_decimal_to_int_9);
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, div_11);
  tcase_add_test(tc1_1, div_12);
  tcase_add_test(tc1_1, div_13);
  tcase_add_test(tc1_1, div_14);
  tcase_add_test(tc1_1, div_15);
  tcase_add_test(tc1_1, mod_1);
  tcase_add_test(tc1_1, mod_2);
  tcase_add_test(tc1_1, mod_3);
  tcase_add_test(tc1_1, mod_4);
  tcase_add_test(tc1_1, mod_5);
  tcase_add_test(tc1_1, mod_6);
  tcase_add_test(tc1_1, mod_7);
  tcase_add_test(tc1_1, mod_8);
  tcase_add_test(tc1_1, mod_9);
  tcase_add_test(tc1_1, from_float_to_decimal_1);
  tcase_add_test(tc1_1, from_float_to_decimal_2);
  tcase_add_test(tc1_1, from_float_to_decimal_3);
  tcase_add_test(tc1_1, from_decimal_to_float_1);
  tcase_add_test(tc1_1, from_decimal_to_float_2);
  tcase_add_test(tc1_1, from_decimal_to_float_3);
  tcase_add_test(tc1_1, from_float_to_decimal_4);
  tcase_add_test(tc1_1, from_float_to_decimal_5);
  tcase_add_test(tc1_1, from_float_to_decimal_6);
  tcase_add_test(tc1_1, s21_negate_1);
  tcase_add_test(tc1_1, s21_negate_2);
  tcase_add_test(tc1_1, s21_negate_3);
  tcase_add_test(tc1_1, s21_truncate_1);
  tcase_add_test(tc1_1, s21_truncate_2);
  tcase_add_test(tc1_1, s21_floor_1);
  tcase_add_test(tc1_1, s21_floor_2);
  tcase_add_test(tc1_1, s21_floor_3);
  tcase_add_test(tc1_1, s21_floor_4);
  tcase_add_test(tc1_1, s21_round_1);
  tcase_add_test(tc1_1, s21_round_2);
  tcase_add_test(tc1_1, s21_round_3);
  tcase_add_test(tc1_1, s21_round_4);
  tcase_add_test(tc1_1, s21_round_5);
  tcase_add_test(tc1_1, s21_round_6);
  tcase_add_test(tc1_1, s21_round_7);
  tcase_add_test(tc1_1, s21_round_8);
  tcase_add_test(tc1_1, s21_round_9);
  tcase_add_test(tc1_1, s21_round_10);
  tcase_add_test(tc1_1, s21_round_11);
  tcase_add_test(tc1_1, s21_round_12);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
