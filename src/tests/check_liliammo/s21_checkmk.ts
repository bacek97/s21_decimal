// https://libcheck.github.io/check/doc/doxygen/html/check_8h.html
// https://www.mankier.com/1/checkmk
#include <stdio.h>
#include "../../s21_decimal/liliammo/s21_decimal.h"

#define __CMP(V1, V2, L, LoEQ, EQ, GoEQ, G, NEQ) \
  ck_assert_int_eq(L,    s21_is_less            (DEC(V1), DEC(V2))); \
  ck_assert_int_eq(LoEQ, s21_is_less_or_equal   (DEC(V1), DEC(V2))); \
  ck_assert_int_eq(EQ,   s21_is_equal           (DEC(V1), DEC(V2))); \
  ck_assert_int_eq(GoEQ, s21_is_greater_or_equal(DEC(V1), DEC(V2))); \
  ck_assert_int_eq(G,    s21_is_greater         (DEC(V1), DEC(V2))); \
  ck_assert_int_eq(NEQ,  s21_is_not_equal       (DEC(V1), DEC(V2)));

#define __arithmetic(FUNCNAME, V1, V2, E, R) \
  s21_decimal value_1, value_2, expect, result = DEC("404."); \
  value_1 = DEC(V1); \
  value_2 = DEC(V2); \
  char strE[32]; \
  char strR[32]; \
  ck_assert_int_eq(R, \
  FUNCNAME(value_1, value_2, &result)); \
  expect = DEC(E); \
  S21_sPrintDec09(expect, strE); \
  S21_sPrintDec09(result, strR); \
  ck_assert_msg(s21_(is_equal)(expect, result), \
  "Failed\nexp:%02d EXPECT:%s\nexp:%02d RESULT:%s\n", \
  expect.exp, strE, result.exp, strR);

#define __ROUNDING_TEST(V, ETRN, RETTRN, ERND, RETRND, EFLR, RETFLR) \
  s21_decimal expectTrn = DEC(ETRN); \
  s21_decimal expectRnd = DEC(ERND); \
  s21_decimal expectFlr = DEC(EFLR); \
  s21_decimal resultTrn = {{404}}, resultRnd = {{404}}, resultFlr = {{404}}; \
  ck_assert_int_eq(RETTRN, s21_truncate(DEC(V), &resultTrn)); \
  ck_assert_int_eq(RETRND, s21_round(DEC(V), &resultRnd)); \
  ck_assert_int_eq(RETFLR, s21_floor(DEC(V), &resultFlr)); \
  char str[6][32]; \
  S21_sPrintDec09(expectTrn, str[0]); \
  S21_sPrintDec09(resultTrn, str[1]); \
  S21_sPrintDec09(expectRnd, str[2]); \
  S21_sPrintDec09(resultRnd, str[3]); \
  S21_sPrintDec09(expectFlr, str[4]); \
  S21_sPrintDec09(resultFlr, str[5]); \
  \
  ck_assert_msg(s21_(is_equal)(expectTrn, resultTrn), \
  "Failed\nexp:%02d EXPECTTRN:%s\nexp:%02d RESULTTRN:%s\n", \
  expectTrn.exp, str[0], resultFlr.exp, str[1]); \
  \
  ck_assert_msg(s21_(is_equal)(expectRnd, resultRnd), \
  "Failed\nexp:%02d EXPECTRND:%s\nexp:%02d RESULTRND:%s\n", \
  expectRnd.exp, str[2], resultFlr.exp, str[3]); \
  \
  ck_assert_msg(s21_(is_equal)(expectFlr, resultFlr), \
  "Failed\nexp:%02d EXPECTFLR:%s\nexp:%02d RESULTFLR:%s\n", \
  expectFlr.exp, str[4], resultFlr.exp, str[5]);

#define __DIV_INT(V1, V2, E, R) \
  s21_decimal value_1, value_2, expectResult, expectMod, result, mod;\
  value_1 = DEC(V1);\
  value_2 = DEC(V2);\
  expectResult = DEC(E);\
  expectMod = DEC(R);\
  mod = S21_div_integer(value_1, value_2, &result);\
  char strR[32];\
  char strM[32];\
  char strER[32];\
  char strEM[32];\
  S21_sPrintDec09(result, strR);\
  S21_sPrintDec09(expectResult, strER);\
  S21_sPrintDec09(expectMod, strEM);\
  S21_sPrintDec09(mod, strM);\
  ck_assert_msg(s21_(is_equal)(expectResult, result), \
  "Failed\nexp:%02d EXPECTRES:%s\nexp:%02d RESULTRES:%s\n", \
  expectResult.exp, strER, result.exp, strR);\
  ck_assert_msg(s21_(is_equal)(expectMod, mod), \
  "Failed\nexp:%02d EXPECTMOD:%s\nexp:%02d RESULTMOD:%s\n", \
  expectMod.exp, strEM, mod.exp, strM);

#define __DEC_AND_INT(V, I_E, R, D_E) \
  s21_decimal value = DEC(V); \
  s21_decimal dExpect = DEC(D_E); \
  int new_int = 404., ret; \
  ret = s21_from_decimal_to_int(value, &new_int); \
  s21_from_int_to_decimal(new_int, &value); \
  ck_assert_int_eq(I_E, new_int); \
  ck_assert_int_eq(ret,R); \
  char str[2][32]; \
  S21_sPrintDec09(dExpect, str[0]); \
  S21_sPrintDec09(value, str[1]); \
  ck_assert_msg(s21_(is_equal)(dExpect, value), \
  "Failed\nEXPECT:%s\nRESULT:%s", \
  str[0], str[1]);

#define __FLOAT_TO_DEC(V, D_E, R) \
  float value = V; \
  s21_decimal result = {{404}}; \
  s21_decimal result7 = {{404}}; \
  s21_decimal result23 = {{404}}; \
  s21_decimal resultEXPLMT = {{404}}; \
  s21_decimal dExpect7 = {{404}}; \
  s21_decimal dExpect23 = {{404}}; \
  s21_decimal dExpectEXPLMT = {{404}}; \
  \
  s21_decimal dExpect = DEC(D_E); \
  S21_rounding(dExpect, &dExpectEXPLMT, TRUNCATE, __EXPLMT); \
  S21_rounding(dExpect, &dExpect7, TRUNCATE, 7); \
  S21_rounding(dExpect, &dExpect23, TRUNCATE, 23); \
  int ret = s21_from_float_to_decimal(value, &result); \
  S21_rounding(result, &result7, TRUNCATE, 7); \
  S21_rounding(result, &result23, TRUNCATE, 23); \
  S21_rounding(result, &resultEXPLMT, TRUNCATE, __EXPLMT); \
  \
  ck_assert_int_eq(ret, R); \
  \
  char str[8][32]; \
  S21_sPrintDec09(dExpect, str[0]); \
  S21_sPrintDec09(dExpect7, str[1]); \
  S21_sPrintDec09(dExpect23, str[2]); \
  S21_sPrintDec09(dExpectEXPLMT, str[3]); \
  \
  S21_sPrintDec09(result, str[4]); \
  S21_sPrintDec09(result7, str[5]); \
  S21_sPrintDec09(result23, str[6]); \
  S21_sPrintDec09(resultEXPLMT, str[7]); \
  \
  ck_assert_msg(s21_(is_equal)(result7, dExpect7), \
  "Failed\nexp:%02d EXPECT7:%s\nexp:%02d RESULT7:%s",\
  dExpect7.exp, str[1], result7.exp, str[5]);
  // \
  // ck_assert_msg(s21_(is_equal)(result23, dExpect23), \
  // "Failed\nexp:%02d EXPECT23:%s\nexp:%02d RESULT23:%s",\
  // dExpect23.exp, str[2], result23.exp, str[6]); \
  // \
  // ck_assert_msg(s21_(is_equal)(resultEXPLMT, dExpectEXPLMT), \
  // "Failed\nexp:%02d EXPECT_EXPLMT:%s\nexp:%02d RESULT_EXPLMT:%s\nPRINTF(.%02df): %.*f",\
  // dExpectEXPLMT.exp, str[3], resultEXPLMT.exp, str[7], dExpectEXPLMT.exp+1, dExpectEXPLMT.exp+1, value);
  //
  // ck_assert_msg(s21_(is_equal)(result, dExpect), \
  // "Failed\nexp:%02d EXPECT:%s\nexp:%02d RESULT:%s",\
  // dExpect.exp, str[0], result.exp, str[3]);

#define __DEC_TO_FLOAT(V, F_E, R) \
s21_decimal value = DEC(V); \
int ret; \
float resFloat = 404; \
ret = s21_from_decimal_to_float(value, &resFloat); \
ck_assert_int_eq(ret, R); \
ck_assert_float_eq(resFloat, F_E);



#suite NULL_TEST
#tcase NULL_TEST

#test NULL_ADD
  s21_add((s21_decimal){{1}}, (s21_decimal){{1}}, NULL);
// #test NULL_SUB
//   s21_sub((s21_decimal){{1}}, (s21_decimal){{1}}, NULL);
#test NULL_MUL
  s21_mul((s21_decimal){{1}}, (s21_decimal){{1}}, NULL);
// #test NULL_DIV
//   s21_div((s21_decimal){{1}}, (s21_decimal){{1}}, NULL);
#test NULL_MOD
  s21_mod((s21_decimal) {{1}}, (s21_decimal) {{1}}, NULL);

// #test NULL_ROUND
//   s21_round((s21_decimal){{1}}, NULL);
#test NULL_TRUNCATE
  s21_truncate((s21_decimal){{1}}, NULL);
// #test NULL_FLOOR
//   s21_floor((s21_decimal){{1}}, NULL);
#test NULL_NEGATE
  s21_negate((s21_decimal){{1}}, NULL);

#test NULL_INT2DEC
  s21_from_int_to_decimal(1, NULL);
// #test NULL_DEC2INT
// s21_from_decimal_to_int((s21_decimal) {{1}}, NULL);
#test NULL_FLOAT2DEC
  s21_from_float_to_decimal(1, NULL);

#suite comparison
#tcase CMP

#test CMP_3_4
  __CMP("3.0", "4.", 1,    1,  0,    0, 0,   1)
        // V1,   V2, L, LoEQ, EQ, GoEQ, G, NEQ

#test MAX_MAX
  __CMP("79228162514264337593543950335.", // V1
        "79228162514264337593543950335.", // V2
         0,    1,  1,    1, 0,   0)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#test MIN_MIN
  __CMP("0.", "0.", 0,    1,  1,    1, 0,   0)// 
      //  V1,   V2, L, LoEQ, EQ, GoEQ, G, NEQ

#test NMAX_NMAX
  __CMP("-79228162514264337593543950335.", // V1
        "-79228162514264337593543950335.", // V2
         0,    1,  1,    1, 0,   0)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#test MIN_MAX
  __CMP("-79228162514264337593543950335.", // V1
        "79228162514264337593543950335.", // V2
         1,    1,  0,    0, 0,   1)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#test EXP_28_01
  __CMP("7.922 81625 14264 33759 35439 50335", // V1
        "7922 81625 14264 33759 35439 5033.5", // V2
         1,    1,  0,    0, 0,   1)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#test EXP_38_N38
  __CMP("7.922 81625 14264 33759 35439 50335 00000 0000", // V1
        "7922 81625 14264 33759 35439 50335 00000 0000.", // V2
         1,    1,  0,    0, 0,   1)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#test EXP_N38_N38
  __CMP("-7.922 81625 14264 33759 35439 50335 00000 0000", // V1
        "-7922 81625 14264 33.759 35439 50335 00000 0000", // V2
         0,    0,  0,    1, 1,   1)
      // L, LoEQ, EQ, GoEQ, G, NEQ

#suite changed_for_me
#tcase ADD_MNTSA

#test OK1_79330_005
  __arithmetic(S21_add_mntsa,                        // FUNCNAME 
              "79228162514264337593543950334.",      // V1
              "00000000000000000000000000001.",      // V2
              "79228162514264337593543950335.", 0);  // E, R
               
#test OK2_79330_000
  __arithmetic(S21_add_mntsa,                        // FUNCNAME 
              "79228162514264337593543950330.",      // V1
              "00000000000000000000000000000.",      // V2
              "79228162514264337593543950330.", 0);  // E, R

#test OVRFLW1
  __arithmetic(S21_add_mntsa,                        // FUNCNAME 
              "79228162514264337593543950335.",      // V1
              "00000000000000000000000000001.",      // V2
              "404.", 1);                            // E, R

#test MINUS_95033_50329
  __arithmetic(S21_add_mntsa,                              // FUNCNAME 
              "-7922  81625 14264 3.3759 35439 50329",     // V1
              "00000000000000000000000000001.",            // V2
              "-792281625142643.37593543950328", 0); // E, R

#test MINUS_79335_39167
  __arithmetic(S21_add_mntsa,                       // FUNCNAME 
              "79228162514264337593543950335.",     // V1
              "-39614081257132168796771975167.",    // V2
              "39614081257132168796771975168.", 0); // E, R

#test PLUS_79335_79335
  __arithmetic(S21_add_mntsa,                       // FUNCNAME 
              "79228162514264337593543950335.",     // V1
              "79228162514264337593543950335.",     // V2
              "404.", 1);                           // E, R

#test MINUS_15_149
  __arithmetic(S21_add_mntsa, " 15.", "-14.9", "-134.", 0); 
                //  FUNCNAME,     V1,      V2,       E, R
    
#test MINUS_79335_79335
  __arithmetic(S21_add_mntsa,                       // FUNCNAME 
              "79228162514264337593543950335.",     // V1
              "-79228162514264337593543950335.",    // V2
              "0.", 0);                             // E, R

#test MINUS_79335__MINUS_79335
  __arithmetic(S21_add_mntsa,                       // FUNCNAME 
              "-79228162514264337593543950335.",    // V1
              "-79228162514264337593543950335.",    // V2
              "404.", 2);                           // E, R

// #test MINUS_NOL
//   __arithmetic(S21_add_mntsa, "-79228162514264337593543950335.", "-1.", "-0.", 0); 
                //  FUNCNAME,                                 V1,   V2,      E, R

#test MINUS_0_79335
  __arithmetic(S21_add_mntsa, "0.",                     // FUNCNAME, V1
              "-79228162514264337593543950335.",        // V2
              "-79228162514264337593543950335.", 0);    // E, R


#tcase DIVINT

#test DIVINT_7_4
  __DIV_INT("7.",      "4.",   "1.", "3.");
//  expectResult, expectMod, result, mod

#test DIVINT_1_0
  __DIV_INT("1.",      "0.", "79228162514264337593543950335.", "1.");
 // expectResult, expectMod,                           result, mod

#test DIVINT_175_100
  __DIV_INT("175.",    "100.",   "1.", "75.");
   // expectResult, expectMod, result, mod


#tcase сhPrec

#test CHPREC1
  s21_decimal expect, result;
  result = DEC("-1.00000");
// s21_negate(value_1, &value_1);
  char strE[32];
  char strR[32];
  ck_assert_int_eq(0,
  S21_changePrecision(&result, -4));
  expect = DEC("-1.0");
#ifdef expUnlimit
  // expect = DEC("0.79228162514264337593543950335");
#endif
// s21_negate(expect, &expect);
  S21_sPrintDec09(expect, strE);
  S21_sPrintDec09(result, strR);
ck_assert_msg(s21_(is_equal)(expect, result), 
"Failed\nexp:%02d EXPECT:%s\nexp:%02d RESULT:%s\n", 
expect.exp, strE, result.exp, strR);

#test CHPREC2
  s21_decimal expect, result;
  result = DEC("-1.00001");
// s21_negate(value_1, &value_1);
  char strE[32];
  char strR[32];
  ck_assert_int_eq(1,
  S21_changePrecision(&result, -4));
  expect = DEC("-1.0");
#ifdef expUnlimit
  // expect = DEC("0.79228162514264337593543950335");
#endif
// s21_negate(expect, &expect);
  S21_sPrintDec09(expect, strE);
  S21_sPrintDec09(result, strR);
ck_assert_msg(s21_(is_equal)(expect, result), 
"Failed\nexp:%02d EXPECT:%s\nexp:%02d RESULT:%s\n", 
expect.exp, strE, result.exp, strR);

#suite for_all
#tcase ADD

#test ADD_RENAME1
  __arithmetic(s21_add,                              // FUNCNAME, важный
               "7922816251426433759354395033.",      // V1
               "0.5500000001",                       // V2
               "7922816251426433759354395033.5", 0); // E, R

#test ADD_RENAME_BANK_MINUS
  __arithmetic(s21_add,                                          // FUNCNAME, важный
               "-10000 00000 00000 00000 00000 0000.", "0.5001", // V1, V2
               "-99999 99999 99999 99999 99999 999.", 0);        // E, R

#test ADD_RENAME_SUB
__arithmetic(s21_add, "79228162514264337593543950335.", "0.91", "404.", 1);
         // FUNCNAME,                               V1,     V2,      E, R, важный

#test ADD_RENAME2
  __arithmetic(s21_add, "1.75001", "1.75", "3.50001", 0); 
          //  FUNCNAME,        V1,     V2,         E, R           

#test ADD_RENAME3
  __arithmetic(s21_add, "79228162514264337593543950335.", "0.5", "404.", 1);
          //  FUNCNAME,                               V1,    V2,      E, R, важный, переполнение после округления

#test ADD_RENAME4
  __arithmetic(s21_add,                                // FUNCNAME
              "79228162514264337593543950334.", "0.5", // V1, V2
              "79228162514264337593543950334.", 0);    // E, R             

#test ADD_RENAME5
  __arithmetic(s21_add,                                 // FUNCNAME
              "7922816251426433759354395033.3", "0.05", // V1, V2
              "7922816251426433759354395033.4", 0);     // E, R
               
#test ADD_RENAME6
  __arithmetic(s21_add,                              // FUNCNAME
              "792281625142643375935439503.", "0.5", // V1, V2
              "792281625142643375935439503.5", 0);   // E, R
               
#test ADD_RENAME7
  __arithmetic(s21_add,                               // FUNCNAME
              "-792281625142643375935439503.", "-1.", // V1, V2
              "-792281625142643375935439504.", 0);    // E, R      

#test ADD_RENAME8
  __arithmetic(s21_add,                                // FUNCNAME
              "-792281625142643375935439503.", "-0.5", // V1, V2
              "-792281625142643375935439503.5", 0);    // E, R           

#test ADD_RENAME9
  __arithmetic(s21_add,                               // FUNCNAME
              "-792281625142643375935439503.", "0.5", // V1, V2 
              "-792281625142643375935439502.5", 0)    // E, R

#test ADD_RENAME10
  __arithmetic(s21_add,                                  // FUNCNAME
              "79228162514264337593543950333.", "-100.", // V1, V2
              "79228162514264337593543950233.", 0);      // E, R

#test ADD_RENAME11
  __arithmetic(s21_add,                                // FUNCNAME
              "792281625142643375935439503.33", "-1.", // V1, V2 
              "792281625142643375935439502.33", 0);    // E, R

#test ADD_RENAME12
  __arithmetic(s21_add,                                 // FUNCNAME
              "79228162514264337593543950334.", "0.75", // V1, V2
              "79228162514264337593543950335.", 0);     // E, R

#test ADD_RENAME13
  __arithmetic(s21_add,                          // FUNCNAME
              "792281625142643375935.000005",    // V1
               "0.000005",                       // V2
              "792281625142643375935.00001", 0); // E, R

#test ADD_RENAME14
  __arithmetic(s21_add,                                 // FUNCNAME
              "7922816251426433759354395033.",  "0.15", // V1, V2
              "7922816251426433759354395033.2", 0);     // E, R

#test ADD_RENAME15
  __arithmetic(s21_add,                                 // FUNCNAME
              "-7922816251426433759354395033.", "0.15", // V1, V2
              "-7922816251426433759354395032.8", 0);    // E, R

#test ADD_RENAME16
  __arithmetic(s21_add,                                // FUNCNAME
              "79228162514264337593543950335.", "0.1", // V1, V2 
              "79228162514264337593543950335.", 0);    // E, R

#test ADD_RENAME17
  __arithmetic(s21_add, "0.15",                      // FUNCNAME, V1
              "-7922816251426433759354395033.",      // V2
              "-7922816251426433759354395032.8", 0); // E, R

#test ADD_RENAME18
  __arithmetic(s21_add,                             // FUNCNAME
              "7922816251426433759354395033.",      // V1
              "0.5500000001",                       // V2
              "7922816251426433759354395033.5", 0); // E, R

#test ADD_RENAME19
  __arithmetic(s21_add,                                // FUNCNAME
              "0.7922816251426433759354395033", "0.1", // V1, V2,
              "0.8922816251426433759354395033", 0);    // E, R

#test ADD_RENAME20
  __arithmetic(s21_add,                                 // FUNCNAME
              "0.79228162514264337593543950335", "0.1", // V1, V2, проходит
              "0.8922816251426433759354395034", 0);     // E, R

#test _ADD_RENAME21
  __arithmetic(s21_add,                                // FUNCNAME
              "7922816251426433759354395033.5", "0.5", // V1, V2, краевые переполнения после округления
              "7922816251426433759354395034.", 0);     // E, R

#test ADD_EXTREME_BANK1
  __arithmetic(s21_add,                           // FUNCNAME, важный
              ".79228162514264337593543950335",     // V1,
              ".7922816251426433759354395033",      // V2
              "1.5845632502852867518708790066", 0); // E, R, ...5

#test ADD_EXP39_ROUNDED_TO_28
  __arithmetic(s21_add,                                        // FUNCNAME, важный
              ".000000000007922816251426433759354395039",      // V1
              ".000000000002",                                 // V2
              ".00000000000 99228162514264337           ", 0); // E, R
           // ".00000000000 9922816251426433759354395039", 0); // E, R

#test ADD_RENAME24
  __arithmetic(s21_add,                                  // FUNCNAME
              "7922816251426433759354395032.5 ", "0.55", // V1, V2
              "7922816251426433759354395033.0 ", 0);     // E, R, 7922816251426433759354395033.05

#test ADD_RENAME25
  __arithmetic(s21_add, "1## #####.", ".001", "100 00000.001", 0); // FUNCNAME, V1, V2, E, R
                           // exp:-7, exp:03

#test ADD_RENAME26
  __arithmetic(s21_add,                                          // FUNCNAME
              " .0000079228162514264337593543950335",            // V1
              "-.0000079228162514264337593543950335", "0.", 0);  // V2, E, R 

#test _ADD_RENAME27
  __arithmetic(s21_add,                                // FUNCNAME
              "7922816251426433759354395033.1", "0.4", // V1, V2 
              "7922816251426433759354395033.5", 0)     // E, R

#test _ADD_RENAME28
  __arithmetic(s21_add,                                // FUNCNAME
              "7922816251426433759354395033.4", "1.5", // V1, V2
              "7922816251426433759354395035.", 0)      // E, R

#test ADD_RENAME30
  __arithmetic(s21_add,                               // FUNCNAME
              "-792281625142643375935439.234", "0.9", // V1,  V2
              "-792281625142643375935438.334", 0);    // E, R

#test ADD_RENAME31
  __arithmetic(s21_add,                            // FUNCNAME
              "7922816251426433759354395033.",     // V1
              "0.6",                               // V2
              "7922816251426433759354395034.", 0); // E, R

#test _ADD_FAIL_DRATINIE_PLUS_PLUS_09
  __arithmetic(s21_add,                            // FUNCNAME
              "0.5534023222112865484800000000",    // V1
              "0.5534023222112865484800000000",    // V2
              "1.1068046444225730969600000000", 0) // E, R 

#test _ADD_MINUS0
  __arithmetic(s21_add,                             // FUNCNAME
              "-7922816251426433759354395033.4",    // V1
              "-7922816251426433759354395033.4",    // V2
              "-15845632502852867518708790067.", 0) // E, R

#test _ADD_MINUS1
  __arithmetic(s21_add,                                  // FUNCNAME
              "7922816251426433759354395033.2", "-0.2",  // V1, V2                
              "7922816251426433759354395033.", 0)        // E, R

#test _ADD_MINUS2
  __arithmetic(s21_add,                          // FUNCNAME,   // хз почему . думаю пока что тут явно должно
              "-79228162514264337593543950335.", // V1,         // быть переполнение, N_INF == 2
              "-0.600", "404.", 2)               // V2, E, R,   // -79228162514264337593543950335.5

#test _ADD_MINUS3
  __arithmetic(s21_add,                                // FUNCNAME, важный
              "7922816251426433759354395033.", "-0.9", // V1, V2
              "7922816251426433759354395032.1", 0)     // E, R

#test _ADD_MINUS999
  __arithmetic(s21_add, "7922816251426433759354395033###", "1##", "404.", 1) 
           // FUNCNAME,                                V1,    V2,      E, R

#tcase SUB

#test SUB_1
  __arithmetic(s21_sub, "79228162514264337593543950335.", "-1.", "404.", 1);
        // FUNCNAME V1,                                      V2,      E, R


#tcase MUL

#test MUL_998
__arithmetic(s21_mul,                   // FUNCNAME
  "792.28162514264337593543950332",     // V1
  "  3.28162514264337593543950323",     // V2
  "2599.9713011224527705171740666", 0); // E, R

#test MUL_999
__arithmetic(s21_mul,    //FUNCNAME
  "-79228162514264337.", // V1
  "-79228162514264337.", // V2
  "404.", 1);            // E, R ...49569

#test MUL_1000
__arithmetic(s21_mul,                        // FUNCNAME
  "-79228162514264337.",                     // V1
  "0.00000 00000 00000 00000 00000 0001",    // V2
  "-0.00000 00000 0079228162514264337", 0);  // E, R

#test MUL_1001
__arithmetic(s21_mul,                          // FUNCNAME
  "0.00000000005",                             // V1
  "0.0000000000000000001",                     // V2
  "0.00000 00000 00000 00000 00000 00005", 0); // E, R

#test MUL_1002
__arithmetic(s21_mul,           // FUNCNAME
  "7922816251426433734535.",    // V1
  "7922816251426433734535789.", // V2
  "404.", 1);                   // E, R, ...541842307882773115

#test MUL_1003
__arithmetic(s21_mul,                        // FUNCNAME
  "79228162514264337593543950335.",          // V1
  "0.2",                                     // V2
  "1584 56325 02852 86751 87087 90067.", 0); // E, R

#test MUL_1004
__arithmetic(s21_mul,                          // FUNCNAME
  "0.79228162514264337",                       // V1
  "0.79228162514264337",                       // V2
  "0.62771 01735 38668 06697 84996 310", 0);   // E, R,  ...049569

#test MUL_61
__arithmetic(s21_mul,                          // FUNCNAME
  ".50126217744835361888867138761",            // V1
  "79228162514264337593543950335.",            // V2
  "39 7140 8125 7132 1687 9677 2975 178.", 0); // E, R

#test MUL_60
__arithmetic(s21_mul,                           // FUNCNAME
  ".50126217744835361888867138760",             // V1
  "79228162514264337593543950335.",             // V2
  "39 7140 8125 7132 1687 9677 2975 177.", 0); // E, R, ...09

#test MUL_59
__arithmetic(s21_mul,                          // FUNCNAME
  ".50126217744835361888867138759",            // V1
  "79228162514264337593543950335.",            // V2
  "39 7140 8125 7132 1687 9677 2975 176.", 0); // E, R

#test MUL_58
__arithmetic(s21_mul,                          // FUNCNAME
  ".50126217744835361888867138758",            // V1
  "79228162514264337593543950335.",            // V2
  "39 7140 8125 7132 1687 9677 2975 176.", 0); // E, R

#test MUL_57
__arithmetic(s21_mul,                          // FUNCNAME
  ".50126217744835361888867138757",            // V1
  "79228162514264337593543950335.",            // V2
  "39 7140 8125 7132 1687 9677 2975 175.", 0); // E, R, ...714

#tcase DIV

#test DIV_ZERO
__arithmetic(s21_div, "1.", "0.", "404.", 3);
         // FUNCNAME,    V1,  V2,      E, R
#test DIV_FROM_TG1
__arithmetic(s21_div, "354546.", "654.", "542.11926605504587155963302752", 0);
         // FUNCNAME,        V1,     V2,                                E, R

#test DIV_1
__arithmetic(s21_div,                    // FUNCNAME
  "  39714081257132168796772975175.",    // V1
  "  79228162514264337593543950335.",    // V2
  "0.50126217744835361888867138757", 0); // E, R

#test DIV_2
__arithmetic(s21_div,                                                      // FUNCNAME, важный
  " 1.", " 79228162514264337593543950335.",                                // V1, V2,   почемуто не по банковскому  
  ".0000 0000 0000 0000 0000 0000 0000 12621774483536188886587657045", 0); // E, R,     ...7044684  7044 вместо 7045

#test DIV_3
__arithmetic(s21_div,                        // FUNCNAME
  " 79228162514264337593543950335.", "1024.",        // V1, V2
  "7737 12524 55336 26718 11952 63.999", 0); // E, R, 0234375

#test DIV_4
__arithmetic(s21_div, "79228162514264337593543950335.", ".003","404.", 1);
         // FUNCNAME,                               V1,     V2,     E, R

#test DIV_5
__arithmetic(s21_div,                         // FUNCNAME
  "79228162514264337593540.", ".3",           // V1, V2
  "26409 38750 47547 79197 8466.66667 ", 0);  // E, R


#tcase MOD

#test MOD_135_10
__arithmetic(s21_mod, "135.", "10.", "5.", 0);
         // FUNCNAME,     V1,    V2,    E, R

#test MOD_0_1
__arithmetic(s21_mod, "0.", "1.", "0.", 0);
         // FUNCNAME,   V1,   V2,    E, R

#test MOD_SMALL_NEGATIVE
__arithmetic(s21_mod, "-153.", "2000.", "-153.", 0);
         // FUNCNAME,      V1,      V2,       E, R

#test MOD_NEGATIVE_DEL
__arithmetic(s21_mod, "-15.", "4.", "-3.", 0);
         // FUNCNAME,     V1,   V2,     E, R

#test MOD_POSITIVE_DEL
__arithmetic(s21_mod, "15.", "-4.", "3.", 0);
         // FUNCNAME,    V1,    V2,    E, R

#test MOD_NEGATIVE_2_DEL
__arithmetic(s21_mod, "-15.", "-4.", "-3.", 0);
         // FUNCNAME,     V1,    V2,     E, R

#test MOD_0_2
__arithmetic(s21_mod,                        // FUNCNAME
            "9123456789123456789123456789.", // V1
            "123456789123.",                 // V2
            "96206128407.", 0);              //E, R

#test MOD_0_3
__arithmetic(s21_mod,                            // FUNCNAME
            "9123456789123456789123456789.",     // V1
            "1234567891234545454545454545.",     // V2
            "481481550481638607305274974.", 0);  //E, R

#test MOD_0_4
__arithmetic(s21_mod,                              // FUNCNAME
            "-9123456789123456789123456789.",      // V2
            " 1234567891234545454545454545.",      // V1
            " -481481550481638607305274974.", 0);  //E, R
#test MOD_0_4_1
__arithmetic(s21_mod,                              // FUNCNAME
            "-91234567891234567.",                 // V1
            " 1234567891234545454545454545.",      // V2
            " -91234567891234567.", 0);            //E, R

#test MOD_28_28_NEGATIVE
__arithmetic(s21_mod,                            // FUNCNAME
            "-9123456789123456789123456789.",    // V1
            "-1234567891234545454545454545.",    // V2
            "-481481550481638607305274974.", 0); //E, R

#test MOD_28_28_NEGATIVE_FRAC
__arithmetic(s21_mod,                              // FUNCNAME
            "-9123456789123456789.123456789",      // V1
            "-1234567891234545454545454545.",      // V2
            "-9123456789123456789.123456789", 0);  //E, R

#test MOD_28_28
__arithmetic(s21_mod,                            // FUNCNAME
            "9123456789123456789123456789.",     // V1
            "9123456789123456789123456790.",     // V2
            "9123456789123456789123456789.", 0);

#test MOD_29_28
__arithmetic(s21_mod,                            // FUNCNAME
            "79228162514264337593543950335.",    // V1
            "9123456789123456789123456789.",     // V2
            "6240508201276683280556296023.", 0); //E, R

#test MOD_29_28_0
__arithmetic(s21_mod,                              // FUNCNAME
            "7922816251426433759354395033.5",      // V1
            "9123456789123456789123456789.",       // V2
            "7922816251426433759354395033.5", 0);  //E, R

#test MOD_29_28_1
__arithmetic(s21_mod,                             // FUNCNAME
            "792281625142643375935.43950335",     // V1
            "9123456789123456789123456789.",      // V2
            "792281625142643375935.43950335", 0); //E, R

#test MOD_29_28_2
__arithmetic(s21_mod,                             // FUNCNAME
            "7.9228162514264337593543950335",     // V1
            "9123456789123456789123456789.",      // V2
            "7.9228162514264337593543950335", 0); //E, R

#test MOD_28_29_0
__arithmetic(s21_mod,                            // FUNCNAME
            "7922816251426433759354395033.",     // V1
            "7922816251426433759354395033.4",    // V2
            "7922816251426433759354395033.", 0); //E, R

#test MOD_28_29_1
__arithmetic(s21_mod,                            // FUNCNAME
            "7922816251426433759354395033.",     // V1
            "7922816251426433759354395033.4",    // V2
            "7922816251426433759354395033.", 0); //E, R

#test MOD_29_29
__arithmetic(s21_mod,                                      // FUNCNAME
            "69228162514264337593543950337.",              // V1 
            "49228162514264337593543950335.",              // V2
            "20 000 000 000 000 000 000 000 000 002.", 0); //E, R

#test MOD_29_29_1
__arithmetic(s21_mod, "6.4",  "2.456", "1.488", 0);
         // FUNCNAME,    V1,       V2,       E, R

// #test MOD_29_29_2
// __arithmetic(s21_div, "3961408125713216879677197516775.", "5.", "7922816251426433759354395033.", 0);
            // FUNCNAME,                                 V1,   V2,     E, R


#tcase ROUNDING

#test ROUNDING1
  __ROUNDING_TEST("-79228 16251 42643 37593 54395 033.4",    // V
                  "-79228 16251 42643 37593 54395 033. ", 0, //trn
                  "-79228 16251 42643 37593 54395 033. ", 0, //rnd
                  "-79228 16251 42643 37593 54395 034. ", 0) //flr

#test ROUNDING2
  __ROUNDING_TEST("79228 16251 42643 37593 54395 03.9",   // V
                  "79228 16251 42643 37593 54395 03.", 0, //trn 
                  "79228 16251 42643 37593 54395 04.", 0, //rnd
                  "79228 16251 42643 37593 54395 03.", 0) //flr
                  
#test ROUNDING3
  __ROUNDING_TEST("0.5", "0.", 0, "1.", 0, "0.", 0)
                  //  V,  trn, R,  rnd, R,  flr, R
                   
#test ROUNDING4
  __ROUNDING_TEST("- 0.0000 00000 00000 00000 00000 010", "0.",  0, "0.",  0, "-1.", 0)
                                                    // V,   trn, R,  rnd,  R,   flr, R                   

#test ROUNDING5
  __ROUNDING_TEST("-5.", "-5.", 0, "-5.", 0, "-5.", 0)
                 //   V,   trn, R,   rnd, R,   flr, R
    
#test ROUNDING6
  __ROUNDING_TEST("-5.00000000", "-5.", 0, "-5.", 0, "-5.", 0)
                           // V,   trn, R,   rnd, R,   flr, R

#test ROUNDING7
  __ROUNDING_TEST("0.999 999 999 999 999 999", "0.", 0, "1.", 0, "0.", 0)
                                         // V,  trn, R,  rnd, R,  flr, R

#test ROUNDING_MINUS_15008
  __ROUNDING_TEST("-15.008", "-15.", 0, "-15.", 0, "-16.", 0)
                       // V,    trn, R,    rnd, R,    flr, R

#tcase DEC_AND_INT

#test DEC_AND_INT_1
  __DEC_AND_INT("2147483647.", 2147483647, 0, "2147483647.")
                         // V,        I_E, R,         D_E

#test DEC_AND_INT_2
  __DEC_AND_INT("0.",   0, 0,  "0.")
                // V, I_E, R, D_E
#test DEC_AND_INT_3
  __DEC_AND_INT("-0.",   0, 0,  "0.")
                 // V, I_E, R, D_E

#test DEC_AND_INT_4
  __DEC_AND_INT("-2147483648.", -2147483648, 0, "-2147483648.")
                          // V,         I_E, R,          D_E

#test DEC_AND_INT_5
  __DEC_AND_INT("-0.678457",   0, 0,  "0.")
                       // V, I_E, R, D_E

#tcase FLOAT_TO_DEC

#test FLOAT_TO_DEC_1_DOT_1
  __FLOAT_TO_DEC(1.1, "1.10000002384185791015625", 0) //  V, D_E, R
             
#test FLOAT_TO_DEC_MAX_ZERO_DOT_1
  __FLOAT_TO_DEC(0.00000000000000000000000000000000000001, // V,
                 "404.", 1) // D_E, R

#test FLOAT_TO_DEC_ZERO_DOT_27_ZERO_1
  __FLOAT_TO_DEC(0.0000000000000000000000000001, // V,
                "0.000 00000 00000 00000 00000 00001000000003 1710768509 710513471", 0) // D_E, R
              
#test FLOAT_TO_DEC_1_DOT_1_27_ZERO
  __FLOAT_TO_DEC(1.1000000000000000000000000000, // V,
                "1.10000002384185791015625", 0)  // D_E, R
  
#test FLOAT_TO_DEC_ZERO_DOT_1_27_ZERO
  __FLOAT_TO_DEC(0.1000000000000000000000000000, // V,
                "0.100000001490116119384765625", 0) // D_E, R

#test FLOAT_TO_DEC_1_DOT_28_ZERO
  __FLOAT_TO_DEC(1., "1.", 0) // V, D_E, R
   
#test FLOAT_TO_DEC_DOT_28_UNITS
  __FLOAT_TO_DEC(1.1111111111111111111111111111, // V,
                "1.111111164093017578125", 0) // D_E, R  

#test FLOAT_TO_DEC_10
__FLOAT_TO_DEC(10000000000000000000000000000000000000.0, // V,
              "404.", 1) // D_E, R 

#test FLOAT_TO_DEC_MAX_UNITS
__FLOAT_TO_DEC(11111111111111111111111111111111111111.1, // V,
              "404.", 1) // D_E, R
  
#test FLOAT_TO_DEC_F_EXP_2_126_VAL
  __FLOAT_TO_DEC(170141173319264429905852091742258462720., // V,
                "404.", 1) // D_E, R

#test FLOAT_TO_DEC_2_127_VAL
__FLOAT_TO_DEC(340282346638528859811704183484516925440., // V,
              "404.", 1) // D_E, R
   
#test FLOAT_TO_DEC_F_EXP_2_0_VAL
  __FLOAT_TO_DEC(1.00000011921, // V,
                "1.00000011920928955078125", 0) // D_E, R

#test FLOAT_TO_DEC_F_EXP_2_MINUS_126_VAL
  __FLOAT_TO_DEC(0.000000000000000000000000000000000000011754943508222875079687365372222456778186655567720875215087517062784172594547271728515625, // V,
                "404.", 1) // D_E, R
    
#test FLOAT_TO_DEC_F_EXP_2_127_VAL
__FLOAT_TO_DEC(340282346638528859811704183484516925440., // V,
              "404.", 1) // D_E, R

#test FLOAT_TO_DEC_F_EXP_2_8_VAL
  __FLOAT_TO_DEC(511.999969482, "511.999969482421875", 0) // V, D_E, R
  
#test FLOAT_TO_DEC_F_EXP_2_9_VAL
__FLOAT_TO_DEC( 1023.99993896, "1023.99993896484375", 0) // V, D_E, R
  
#test FLOAT_TO_DEC_F_EXP_2_10_VAL
  __FLOAT_TO_DEC(2047.99987793, "2047.9998779296875", 0) // V, D_E, R  

#tcase DEC2FLOAT

#test DEC_TO_FLOAT
  __DEC_TO_FLOAT("1.0123456789", 1.0123456789, 0) // V, F_E, R  

#test DEC_TO_FLOAT_PLOHO
  __DEC_TO_FLOAT("1.0123456789", 1.0123456789, 0) // V, F_E, R  

// #test DEC_TO_FLOAT_MAX_VAL_DEC
// __DEC_TO_FLOAT("79228157791897854723898736640.",    // V, важный
//                 79228157791897854723898736640., 0)  // F_E, R  

#test DEC_TO_FLOAT_MAX_VAL_FLOAT
__DEC_TO_FLOAT("9 14000 00000 00000 000.",  // V
                9140000000000000000., 0) // F_E, R  



#main-pre
  printf("\033[0;36m");  // бирюзовый (Passed Failed)
    
#main-post
  printf("\033[0;31m"); // красный (CHECK.H Failures: N)
  if (nf != 0) {
    printf("CHECK.H Failures: %d\n", nf);
  }
  printf("\033[0;35m");  // розовый (VALGRIND)
  return 0;
