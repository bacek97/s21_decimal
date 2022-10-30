//  Copyright by liliammo 2022   --RC--
#include "s21_decimal.h"

void S21_strMulBy2(char *str, char bit) {  //  Release
  while (*str) {
    bit = (*str - '0') * 2 + bit;
    *str++ = (bit % 10) + '0';
    bit /= 10;
    if (bit && *str == '\0') *str = '0';
  }
}
void S21_sPrintDec09(s21_decimal value, char *str2) {  //  Release
  char str[32] = "0";
  char negate = value.sign;
  if (negate)s21_(negate)(value, &value);
  for (int i = 95; 0 <= i; i--) {
    S21_strMulBy2(str, __getBit(value, i));
  }
  if (negate) *str2++ = '-';
  for (int i = 29; 0 <= i; i--) {
    if (str[i]) *str2++ = str[i];
    if (i == value.exp) *str2++ = ('.');
  }
*str2 = '\0';
}

s21_decimal DEC(char *src) {  //  Release
  s21_decimal dst = {0};
  int sign = 0;
  int digits;
  while ((digits = ('0' <= *src && *src <= '9')) || *src == ' ' || *src == '.' || *src == '-' ||
         *src == '#') {
    if (digits) {
      if (dst.exp) dst.exp++;
      S21_mul_mntsa(dst, (s21_decimal){{10}}, &dst);
      S21_add_mntsa(dst, (s21_decimal){{*src - '0'}}, &dst);
    }
    if (*src == '.') dst.exp++;
    if (*src == '-') sign = 1;
    if (*src == '#') dst.exp--;
    src++;
  }
  dst.exp--;
  if (sign) s21_(negate)(dst, &dst);
  return dst;
}

#include <stdio.h>

// void S21_print01Szf(int_fast64_t d, int szof) {  //  Release
//   szof *= 8;
//   while (szof--) {
//     if (!((szof+1) % 4)) printf("\033[0;32;32m");
//     if (!((szof+1) % 8)) printf("\033[0;32;34m");
//     putchar(((d >> szof)& 1) + '0');
//     // d >>= 1;
//   }
//   printf("\033[m");
// }

// void S21_printDec01(s21_decimal value) {  //  Release
//   S21_print01Szf(value.bits[0], sizeof(value.bits[0]));
//   putchar(' ');
//   S21_print01Szf(value.bits[1], sizeof(value.bits[1]));
//   putchar(' ');
//   S21_print01Szf(value.bits[2], sizeof(value.bits[2]));
//   putchar(' ');
//   S21_print01Szf(value.bits[3], sizeof(value.bits[3]));
//   putchar('\n');
// }

// void S21_printDec09(s21_decimal value) {  //  Release
//   char str[32];
//   S21_sPrintDec09(value, str);
//   printf("%s", str);
// }
