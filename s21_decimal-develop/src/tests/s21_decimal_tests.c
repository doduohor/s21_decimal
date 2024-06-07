#include <check.h>
#include <math.h>

#include "../s21_decimal.h"

#define MAX_UINT 4294967295

#define VOILA(x) \
  puts("\n" x);  \
  puts("=========================================");

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

#define COLOR_SUITE(x) "\033[1;37;45m" x "\033[0;0;0m"
#define COLOR_CASE(x) "\033[1;37;44m" x "\033[0;0;0m"

//=========================================================
// 4 арифметических оператора

// Сложение---------------------------------------------

START_TEST(add_1) {
  s21_decimal a = {{7, 0, 0, 0x00000000}};
  s21_decimal b = {{5, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 7, br = 5;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_2) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};
  s21_decimal b = {{7, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 5, br = 7;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_3) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = -5;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{7, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -5, br = -7;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_5) {
  s21_decimal a = {{7, 0, 0, 0x00000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 7, br = -5;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_6) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = 5;
  s21_add(a, b, &c);
  int cr = ar + br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(add_7) {
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  // int ar = -7, br = 5;
  int res = 2;
  int res_add = s21_add(a, b, &c);
  int cr = 0;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
  ck_assert_int_eq(res, res_add);
}
END_TEST

START_TEST(add_8) {
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 0x80000000}};
  s21_decimal b = {{4294967295, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  // int ar = -7, br = 5;
  int res = 2;
  int res_add = s21_add(a, b, &c);
  int cr = 0;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
  ck_assert_int_eq(res, res_add);
}
END_TEST

// START_TEST(add_9)
// {
//   s21_decimal a = {{-1, -1, -1, -2147483648}}; //
//   -79228162514264337593543950335 s21_decimal b = {.bits = {6, 0, 0,
// 65536
// }
// }
// ;
//   // 0.6 s21_decimal res_bits = {.bits = {0, 0, 0, 0}};

//   int res = s21_sub(a, b, &res_bits);

//   ck_assert_int_eq(res, 2);
//   ck_assert_uint_eq(res_bits.bits[0], (uint32_t)0);
//   ck_assert_uint_eq(res_bits.bits[1], (uint32_t)0);
//   ck_assert_uint_eq(res_bits.bits[2], (uint32_t)0);
//   ck_assert_uint_eq(res_bits.bits[3], (uint32_t)0);
// }
// END_TEST

START_TEST(add_10) {
  s21_decimal test_v_1 = {{4294967294, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_v_2 = {{1, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[1], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[2], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_11) {
  s21_decimal src1, src2, result;
  int a = -1234;
  float b = 1.234;
  float res_origin = -1232.766;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_12) {
  s21_decimal src1, src2, result;

  int a = -1234;
  float b = -1.234;
  float res_origin = -1235.234;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_13) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = -221.23401;
  float res_origin = -1455.234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_14) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 0.00234;
  float res_origin = -9402.9976600;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_15) {
  s21_decimal src1, src2, result;
  float a = -940.3;
  float b = 0.234;
  float res_origin = -940.0660000;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_16) {
  s21_decimal src1, src2, result;
  float a = -0.940301;
  float b = 22.023401;
  float res_origin = 21.0831;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_17) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = -112.0234;
  float res_origin = -112.9637;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_18) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0234;
  float res_origin = -1052.0234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_19) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_origin = -12140;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_20) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x300000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xF;
  src1.bits[0] = 0x67E4FEEF;
  src2.bits[3] = 0x300000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFF;
  src2.bits[0] = 0x67E4FFFF;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x300000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x10E;
  result_origin.bits[0] = 0xCFC9FEEE;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(add_21) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(add_22) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 0}};
  s21_decimal test_v_2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 99);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_23) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 131072}};
  s21_decimal test_v_2 = {{0, 1, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], MAX_UINT);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_24) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 131072}};
  s21_decimal test_v_2 = {{5, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967292);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_25) {
  s21_decimal test_v_1 = {{428, 0, 0, 0}};
  s21_decimal test_v_2 = {{165, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42965);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 0);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(s21_add_1) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 3;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 3;
  // src2 = 2;
  src1.bits[0] = 0x3;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x2;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 3;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x3;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x2;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x2;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0x1979;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x12189;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x13B02;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0x4;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5D19D1B;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5D19D1F;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0x3E9DF1E;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x3E9DF23;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0x590CC;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x590CB;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 98745654321;
  src1.bits[0] = 0x1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xFDB31C31;
  src2.bits[1] = 0x16;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFDB31C32;
  origin.bits[1] = 0x16;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0x4CD281C5;
  src1.bits[1] = 0x2;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4CD281C8;
  origin.bits[1] = 0x2;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0x89E7FFFF;
  src1.bits[1] = 0x8AC72304;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x89e80000;
  origin.bits[1] = 0x8AC72304;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615;
  // src2 = 1;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x1;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_16) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;
  src1.bits[0] = 0x82E25AED;
  src1.bits[1] = 0xF9E825AD;
  src1.bits[2] = 0xB03EF094;
  src1.bits[3] = 0x800e0000;
  src2.bits[0] = 0x340972E;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x712ADAED;
  origin.bits[1] = 0x2E3CE1F8;
  origin.bits[2] = 0xB03EEF6D;
  origin.bits[3] = 0x800e0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_18) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;
  src1.bits[0] = 0x4EE43976;
  src1.bits[1] = 0x4B35A1D9;
  src1.bits[2] = 0x19B974BF;
  src1.bits[3] = 0xF0000;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4EE43976;
  origin.bits[1] = 0x4B35A1D9;
  origin.bits[2] = 0x19B974BF;
  origin.bits[3] = 0xF0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_23) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_24) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_25) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_27) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0x5F08045B;
  src1.bits[1] = 0x6DF37F67;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3E9AC4E;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x62F1B0A9;
  origin.bits[1] = 0x6DF37F67;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_28) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0x27AA2EE1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1052e659;
  src2.bits[1] = 0x1F41F2;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x37FD153A;
  origin.bits[1] = 0x1F41F2;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_29) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;
  src1.bits[0] = 0xFE90D95F;
  src1.bits[1] = 0x846421e8;
  src1.bits[2] = 0x1;
  src1.bits[3] = 0x130000;
  src2.bits[0] = 0xD4AE3D8A;
  src2.bits[1] = 0x741427A3;
  src2.bits[2] = 0x84144;
  src2.bits[3] = 0x180000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x9A5CD2EA;
  origin.bits[1] = 0xBE524D13;
  origin.bits[2] = 0xA91E7;
  origin.bits[3] = 0x180000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_30) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;
  src1.bits[0] = 0x54403D8C;
  src1.bits[1] = 0x8B520559;
  src1.bits[2] = 0x1FA981AD;
  src1.bits[3] = 0x800C0000;
  src2.bits[0] = 0x65F24DAC;
  src2.bits[1] = 0x7A9AB;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80060000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xD5EE008C;
  origin.bits[1] = 0x780599AD;
  origin.bits[2] = 0x1FA98222;
  origin.bits[3] = 0x800C0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_31) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;
  src1.bits[0] = 0xB0F708D;
  src1.bits[1] = 0x96B05951;
  src1.bits[2] = 0x11A17B81;
  src1.bits[3] = 0x1C0000;
  src2.bits[0] = 0x17254C02;
  src2.bits[1] = 0xF5159B;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x110000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x70DD408D;
  origin.bits[1] = 0x5A9DE30A;
  origin.bits[2] = 0x27EBCC5A;
  origin.bits[3] = 0x1C0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_36) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x4FB46065;
  src2.bits[1] = 0x4236B661;
  src2.bits[2] = 0x7ABD8C9A;
  src2.bits[3] = 0x800C0000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4FB46065;
  origin.bits[1] = 0x4236B661;
  origin.bits[2] = 0x7ABD8C9A;
  origin.bits[3] = 0x800C0000;
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_40) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -79228162514264337593543950335;
  // src2 = 79228162514264337593543950335;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0xFFFFFFFF;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0xFFFFFFFF;
  src2.bits[1] = 0xFFFFFFFF;
  src2.bits[2] = 0xFFFFFFFF;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_44) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 546378;
  // src2 = 0;
  src1.bits[0] = 0x8564A;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x8564A;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_45) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 8976545415646545.5746845454;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xDDE10B0E;
  src2.bits[1] = 0x5416A02;
  src2.bits[2] = 0x4A4093;
  src2.bits[3] = 0xA0000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xDDE10B0E;
  origin.bits[1] = 0x5416A02;
  origin.bits[2] = 0x4A4093;
  origin.bits[3] = 0xA0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_51) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 0;
  src1.bits[0] = 0x1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x1;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

// START_TEST(s21_add_52)
// {
//   s21_decimal src1, src2, origin, result;
//   int value_type_result, value_type_origin;
//   // src1 = 0;
//   // src2 = 0;
//   src1.bits[0] = 0xB;
//   src1.bits[1] = 0x00;
//   src1.bits[2] = 0x00;
//   src1.bits[3] = 0x10000;
//   src2.bits[0] = 0xFFFFFFFF;
//   src2.bits[1] = 0xFFFFFFFF;
//   src2.bits[2] = 0xFFFFFFFF;
//   src2.bits[3] = 0x10000;
//   value_type_result = s21_add(src1, src2, &result);
//   value_type_origin = 0;
//   origin.bits[0] = 0x9999999B;
//   origin.bits[1] = 0x99999999;
//   origin.bits[2] = 0x19999999;
//   origin.bits[3] = 0x00;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(value_type_result, value_type_origin);
// }
// END_TEST

START_TEST(ss21_add_1) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 3;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_2) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 3;
  // src2 = 2;
  src1.bits[0] = 0x3;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x2;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_3) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 3;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x3;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_4) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x2;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_5) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0x4CD281C5;
  src1.bits[1] = 0x2;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4CD281C8;
  origin.bits[1] = 0x2;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_6) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x2;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_7) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0x1979;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x12189;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x13B02;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_8) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0x4;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5D19D1B;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5D19D1F;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_9) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0x3E9DF1E;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x3E9DF23;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_10) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0x590CC;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x590CB;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_11) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 98745654321;
  src1.bits[0] = 0x1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xFDB31C31;
  src2.bits[1] = 0x16;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFDB31C32;
  origin.bits[1] = 0x16;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_12) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0x4CD281C5;
  src1.bits[1] = 0x2;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4CD281C8;
  origin.bits[1] = 0x2;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_13) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0x89E7FFFF;
  src1.bits[1] = 0x8AC72304;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x89e80000;
  origin.bits[1] = 0x8AC72304;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_14) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615;
  // src2 = 1;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x1;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_15) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;
  src1.bits[0] = 0xFFFFFFF6;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0x9;
  src1.bits[3] = 0x10000;
  src2.bits[0] = 0x398BA562;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x3F7475CA;
  origin.bits[1] = 0x2;
  origin.bits[2] = 0xA;
  origin.bits[3] = 0x10000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

// START_TEST(ss21_add_16)
// {
//   s21_decimal src1, src2, origin, result;
//   int value_type_result, value_type_origin;
//   // src1 = -545454512454545.35265454545645;
//   // src2 = 54564654;
//   src1.bits[0] = 0x82E25AED;
//   src1.bits[1] = 0xF9E825AD;
//   src1.bits[2] = 0xB03EF094;
//   src1.bits[3] = 0x800e0000;
//   src2.bits[0] = 0x340972E;
//   src2.bits[1] = 0x00;
//   src2.bits[2] = 0x00;
//   src2.bits[3] = 0x00;
//   value_type_result = s21_add(src1, src2, &result);
//   value_type_origin = 0;
//   origin.bits[0] = 0x7FA1C3BF;
//   origin.bits[1] = 0xF9E825AD;
//   origin.bits[2] = 0xB03EF094;
//   origin.bits[3] = 0x800e0000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(value_type_result, value_type_origin);
// }
// END_TEST

START_TEST(ss21_add_17) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;
  src1.bits[0] = 0x4EE43976;
  src1.bits[1] = 0x4B35A1D9;
  src1.bits[2] = 0x19B974BF;
  src1.bits[3] = 0xF0000;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4EE43976;
  origin.bits[1] = 0x4B35A1D9;
  origin.bits[2] = 0x19B974BF;
  origin.bits[3] = 0xF0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_18) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_19) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_20) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_21) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0x5F08045B;
  src1.bits[1] = 0x6DF37F67;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3E9AC4E;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x62F1B0A9;
  origin.bits[1] = 0x6DF37F67;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_22) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0x27AA2EE1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1052e659;
  src2.bits[1] = 0x1F41F2;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x37FD153A;
  origin.bits[1] = 0x1F41F2;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_23) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;
  src1.bits[0] = 0xFE90D95F;
  src1.bits[1] = 0x846421e8;
  src1.bits[2] = 0x1;
  src1.bits[3] = 0x130000;
  src2.bits[0] = 0xD4AE3D8A;
  src2.bits[1] = 0x741427A3;
  src2.bits[2] = 0x84144;
  src2.bits[3] = 0x180000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x9A5CD2EA;
  origin.bits[1] = 0xBE524D13;
  origin.bits[2] = 0xA91E7;
  origin.bits[3] = 0x180000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_24) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;
  src1.bits[0] = 0x54403D8C;
  src1.bits[1] = 0x8B520559;
  src1.bits[2] = 0x1FA981AD;
  src1.bits[3] = 0x800C0000;
  src2.bits[0] = 0x65F24DAC;
  src2.bits[1] = 0x7A9AB;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80060000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xD5EE008C;
  origin.bits[1] = 0x780599AD;
  origin.bits[2] = 0x1FA98222;
  origin.bits[3] = 0x800C0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_25) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;
  src1.bits[0] = 0xB0F708D;
  src1.bits[1] = 0x96B05951;
  src1.bits[2] = 0x11A17B81;
  src1.bits[3] = 0x1C0000;
  src2.bits[0] = 0x17254C02;
  src2.bits[1] = 0xF5159B;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x110000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x70DD408D;
  origin.bits[1] = 0x5A9DE30A;
  origin.bits[2] = 0x27EBCC5A;
  origin.bits[3] = 0x1C0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_26) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x4FB46065;
  src2.bits[1] = 0x4236B661;
  src2.bits[2] = 0x7ABD8C9A;
  src2.bits[3] = 0x800C0000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x4FB46065;
  origin.bits[1] = 0x4236B661;
  origin.bits[2] = 0x7ABD8C9A;
  origin.bits[3] = 0x800C0000;
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_27) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -79228162514264337593543950335;
  // src2 = 79228162514264337593543950335;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0xFFFFFFFF;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0xFFFFFFFF;
  src2.bits[1] = 0xFFFFFFFF;
  src2.bits[2] = 0xFFFFFFFF;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_28) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 546378;
  // src2 = 0;
  src1.bits[0] = 0x8564A;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x8564A;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_29) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 8976545415646545.5746845454;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xDDE10B0E;
  src2.bits[1] = 0x5416A02;
  src2.bits[2] = 0x4A4093;
  src2.bits[3] = 0xA0000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xDDE10B0E;
  origin.bits[1] = 0x5416A02;
  origin.bits[2] = 0x4A4093;
  origin.bits[3] = 0xA0000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(ss21_add_30) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 0;
  src1.bits[0] = 0x1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x1;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

// Вычитание---------------------------------------------

START_TEST(sub_1) {
  s21_decimal a = {{10, 0, 0, 0x000000000}};
  s21_decimal b = {{5, 0, 0, 0x10000}};
  s21_decimal c = {{0, 0, 0, 0}};
  float ar = 10.0, br = 0.5;
  s21_sub(a, b, &c);
  float cr = (float)ar - (float)br;
  float C;
  s21_from_decimal_to_float(c, &C);
  ck_assert_float_eq(C, cr);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};
  s21_decimal b = {{7, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 5, br = 7;
  s21_sub(a, b, &c);
  int cr = ar - br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = -5;
  s21_sub(a, b, &c);
  int cr = ar - br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{7, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -5, br = -7;
  s21_sub(a, b, &c);
  int cr = ar - br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal a = {{7, 0, 0, 0x00000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 7, br = -5;
  s21_sub(a, b, &c);
  int cr = ar - br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = 5;
  s21_sub(a, b, &c);
  int cr = ar - br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x00010000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0x66F0;
  src2.bits[3] = 0x00030000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0x000451D6;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x00030000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0x0023E3EA;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal test_v_1 = {{1, 10, 0, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal test_v_1 = {{1, 4, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal test_v_1 = {{1, 0, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal test_v_1 = {{1, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  set_bit(&test_v_2, 127);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1234 + 1);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

// // Умножение---------------------------------------------

START_TEST(mul_1) {
  s21_decimal a = {{7, 0, 0, 0x000000000}};
  s21_decimal b = {{5, 0, 0, 0x000000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 7, br = 5;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};
  s21_decimal b = {{7, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 5, br = 7;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = -5;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{7, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -5, br = -7;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal a = {{7, 0, 0, 0x00000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 7, br = -5;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -7, br = 5;
  s21_mul(a, b, &c);
  int cr = ar * br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{10000, 0, 0, 131072}};
  s21_decimal val2 = {{100000, 0, 0, 131072}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(val1, val2, &res);

  ck_assert_int_eq(res.bits[0], 1000000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 131072);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 3;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x6;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 3;
  // src2 = 2;
  src1.bits[0] = 0x3;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x2;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x6;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 3;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0x2;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0x1979;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x12189;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x1CCF3AC1;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0x4;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5D19D1B;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x1746746C;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_8) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0x3E9DF1E;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x5;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x13915B96;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0x590CC;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x590CC;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_10) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 98745654321;
  src1.bits[0] = 0x1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xFDB31C31;
  src2.bits[1] = 0x16;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFDB31C31;
  origin.bits[1] = 0x16;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0x4CD281C5;
  src1.bits[1] = 0x2;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x3;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xE677854F;
  origin.bits[1] = 0x6;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_12) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0x89E7FFFF;
  src1.bits[1] = 0x8AC72304;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x89E7FFFF;
  origin.bits[1] = 0x8AC72304;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_13) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615;
  // src2 = 1;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFFFFFFFF;
  origin.bits[1] = 0xFFFFFFFF;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_14) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_15) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_16) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0x00;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x00;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_17) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0xFFFFFFFF;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x80000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFFFFFFFF;
  origin.bits[1] = 0xFFFFFFFF;
  origin.bits[2] = 0xFFFFFFFF;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(value_type_result, value_type_origin);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_mul_18) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0x5F08045B;
  src1.bits[1] = 0x6DF37F67;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x3E9AC4E;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0x5F3177BA;
  origin.bits[1] = 0x44FCDBB1;
  origin.bits[2] = 0x1AE371E;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_19) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0x27AA2EE1;
  src1.bits[1] = 0x00;
  src1.bits[2] = 0x00;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0x1052e659;
  src2.bits[1] = 0x1F41F2;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xC45A7239;
  origin.bits[1] = 0x648DECD3;
  origin.bits[2] = 0x4D7D3;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_20) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -79228162514264337593543950335;
  // src2 = 1;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0xFFFFFFFF;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0x1;
  src2.bits[1] = 0x00;
  src2.bits[2] = 0x00;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0xFFFFFFFF;
  origin.bits[1] = 0xFFFFFFFF;
  origin.bits[2] = 0xFFFFFFFF;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_22) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  src1.bits[0] = 0xFFFFFFFF;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[2] = 0xFFFFFFFF;
  src1.bits[3] = 0x00;
  src2.bits[0] = 0xFFFFFFFF;
  src2.bits[1] = 0xFFFFFFFF;
  src2.bits[2] = 0xFFFFFFFF;
  src2.bits[3] = 0x00;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 1;
  origin.bits[0] = 0x00;
  origin.bits[1] = 0x00;
  origin.bits[2] = 0x00;
  origin.bits[3] = 0x00;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_23) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_24) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_25) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0;
  float b = 9403.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 88416409;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21mul_7) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21mul_8) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21mul_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(s21_mul_test) {
  int value_type = 0;
  // Проверка на 0
  // 1
  s21_decimal num_11 = {{0, 0, 0, 0}};
  s21_decimal num_12 = {{0, 0, 0, 0}};
  s21_decimal result1 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_11, num_12, &result1);
  ck_assert_int_eq(result1.bits[0], 0);
  ck_assert_int_eq(result1.bits[1], 0);
  ck_assert_int_eq(result1.bits[2], 0);
  ck_assert_int_eq(result1.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // 2
  s21_decimal num_21 = {{0, 0, 0, 0}};
  s21_decimal num_22 = {{1, 0, 0, 0}};
  s21_decimal result2 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_21, num_22, &result2);
  ck_assert_int_eq(result2.bits[0], 0);
  ck_assert_int_eq(result2.bits[1], 0);
  ck_assert_int_eq(result2.bits[2], 0);
  ck_assert_int_eq(result2.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // 3
  s21_decimal num_31 = {{0, 0, 0, 0}};
  s21_decimal num_32 = {{1, 0, 0, 2147483648}};
  s21_decimal result3 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_31, num_32, &result3);
  ck_assert_int_eq(result3.bits[0], 0);
  ck_assert_int_eq(result3.bits[1], 0);
  ck_assert_int_eq(result3.bits[2], 0);
  ck_assert_int_eq(value_type, 0);

  // // ПРОВЕРКА НА 1
  // 7
  s21_decimal num_71 = {{1, 0, 0, 0}};
  s21_decimal num_72 = {{0, 0, 0, 0}};
  s21_decimal result7 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_71, num_72, &result7);
  ck_assert_int_eq(result7.bits[0], 0);
  ck_assert_int_eq(result7.bits[1], 0);
  ck_assert_int_eq(result7.bits[2], 0);
  ck_assert_int_eq(result7.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // 8
  s21_decimal num_81 = {{1, 0, 0, 0}};
  s21_decimal num_82 = {{1, 0, 0, 0}};
  s21_decimal result8 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_81, num_82, &result8);
  ck_assert_int_eq(result8.bits[0], 1);
  ck_assert_int_eq(result8.bits[1], 0);
  ck_assert_int_eq(result8.bits[2], 0);
  ck_assert_int_eq(result8.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // 9
  s21_decimal num_91 = {{1, 0, 0, 0}};
  s21_decimal num_92 = {{1, 0, 0, 2147483648}};
  s21_decimal result9 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_91, num_92, &result9);
  ck_assert_int_eq(result9.bits[0], 1);
  ck_assert_int_eq(result9.bits[1], 0);
  ck_assert_int_eq(result9.bits[2], 0);
  ck_assert_int_eq(result9.bits[3], 2147483648);
  ck_assert_int_eq(value_type, 0);

  // ПРОВЕРКА НА -1
  // 13
  s21_decimal num_131 = {{1, 0, 0, 2147483648}};
  s21_decimal num_132 = {{0, 0, 0, 0}};
  s21_decimal result13 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_131, num_132, &result13);
  ck_assert_int_eq(result13.bits[0], 0);
  ck_assert_int_eq(result13.bits[1], 0);
  ck_assert_int_eq(result13.bits[2], 0);
  ck_assert_int_eq(value_type, 0);

  // 14
  s21_decimal num_141 = {{1, 0, 0, 2147483648}};
  s21_decimal num_142 = {{1, 0, 0, 0}};
  s21_decimal result14 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_141, num_142, &result14);
  ck_assert_int_eq(result14.bits[0], 1);
  ck_assert_int_eq(result14.bits[1], 0);
  ck_assert_int_eq(result14.bits[2], 0);
  ck_assert_int_eq(result14.bits[3], 2147483648);
  ck_assert_int_eq(value_type, 0);

  // 15
  s21_decimal num_151 = {{1, 0, 0, 2147483648}};
  s21_decimal num_152 = {{1, 0, 0, 2147483648}};
  s21_decimal result15 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_151, num_152, &result15);
  ck_assert_int_eq(result15.bits[0], 1);
  ck_assert_int_eq(result15.bits[1], 0);
  ck_assert_int_eq(result15.bits[2], 0);
  ck_assert_int_eq(result15.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // НОРМАЛЬНЫЕ ТЕСТЫ
  // 37
  s21_decimal num_371 = {{125, 0, 0, 2147680256}};
  s21_decimal num_372 = {{4, 0, 0, 2147483648}};
  s21_decimal result37 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_371, num_372, &result37);
  ck_assert_int_eq(result37.bits[0], 500);
  ck_assert_int_eq(result37.bits[1], 0);
  ck_assert_int_eq(result37.bits[2], 0);
  ck_assert_int_eq(result37.bits[3], 196608);
  ck_assert_int_eq(value_type, 0);

  // 38
  s21_decimal num_381 = {{4294967295, 4294967295, 4294967295, 2147876864}};
  s21_decimal num_382 = {{0, 0, 0, 0}};
  s21_decimal result38 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_381, num_382, &result38);
  ck_assert_int_eq(result38.bits[0], 0);
  ck_assert_int_eq(result38.bits[1], 0);
  ck_assert_int_eq(result38.bits[2], 0);
  ck_assert_int_eq(result38.bits[3], 2147876864);
  ck_assert_int_eq(value_type, 0);

  // 39
  s21_decimal num_391 = {{4294967295, 0, 0, 0}};
  s21_decimal num_392 = {{2, 0, 0, 0}};
  s21_decimal result39 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_391, num_392, &result39);
  ck_assert_int_eq(result39.bits[0], 4294967294);
  ck_assert_int_eq(result39.bits[1], 1);
  ck_assert_int_eq(result39.bits[2], 0);
  ck_assert_int_eq(result39.bits[3], 0);
  ck_assert_int_eq(value_type, 0);

  // ПЕРЕПОЛНЕНИЯ
  // 40
  s21_decimal num_401 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_402 = {{2, 0, 0, 0}};
  s21_decimal result40 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_401, num_402, &result40);
  ck_assert_int_eq(result40.bits[3], 0);
  ck_assert_int_eq(value_type, 1);

  // 41
  s21_decimal num_411 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_412 = {{2, 0, 0, 2147483648}};
  s21_decimal result41 = {{0, 0, 0, 0}};
  value_type = s21_mul(num_411, num_412, &result41);
  ck_assert_int_eq(value_type, 1);
}

// START_TEST(s21mul_10) {
//   s21_decimal val1 = {{10000, 0, 0, 131072}};
//   s21_decimal val2 = {{100000, 0, 0, 131072}};
//   s21_decimal res = {{0, 0, 0, 0}};
//   s21_mul(val1, val2, &res);
//   ck_assert_int_eq(res.bits[0], 100000);
//   ck_assert_int_eq(res.bits[1], 0);
//   ck_assert_int_eq(res.bits[2], 0);
//   ck_assert_int_eq(res.bits[2], 0);
// }
// END_TEST

// // //Деление---------------------------------------------

START_TEST(div_1) {
  s21_decimal src1 = {{180, 0, 0, 0}};
  s21_decimal src2 = {{15, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 12);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

// START_TEST(div_3) {
//   s21_decimal src1 = {{S21_MAX_UINT, 0, 0, 0}};
//   s21_decimal src2 = {{2, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_div(src1, src2, &result);
//   ck_assert_int_eq(result.bits[0], 2147483648);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
// }
// END_TEST

START_TEST(div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);

  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal src1 = {{1000, 0, 0, 131072}};
  s21_decimal src2 = {{50, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal src1 = {{0, 12, MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal a = {{75, 0, 0, 0x000000000}};
  s21_decimal b = {{5, 0, 0, 0x000000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 75, br = 5;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(div_10) {
  s21_decimal a = {{56, 0, 0, 0x00000000}};
  s21_decimal b = {{7, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 56, br = 7;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(div_11) {
  s21_decimal a = {{75, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -75, br = -5;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(div_12) {
  s21_decimal a = {{56, 0, 0, 0x80000000}};
  s21_decimal b = {{7, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -56, br = -7;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(div_13) {
  s21_decimal a = {{75, 0, 0, 0x00000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = 75, br = -5;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

START_TEST(div_14) {
  s21_decimal a = {{75, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int ar = -75, br = 5;
  s21_div(a, b, &c);
  int cr = ar / br;
  int C;
  s21_from_decimal_to_int(c, &C);
  ck_assert_int_eq(C, cr);
}
END_TEST

// START_TEST(div_15)
// {
//   printf("\n|||||||||||||||||||||\n");
//   s21_decimal a = {{0, 0, 0x80000000, 0x00000000}};
//   s21_decimal b = {{1, 0, 0, 0x001c0000}};
//   s21_decimal c = {{0, 0, 0, 0}};
//   ck_assert_int_eq(1, s21_div(a, b, &c));
// }
// END_TEST

START_TEST(div_16) {
  s21_decimal a = {{0, 0, 0x80000000, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0x00000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_div(a, b, &c));
}
END_TEST

START_TEST(div_17) {
  s21_decimal a = {{0, 0, 0x80000000, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_div(a, b, &c));
}
END_TEST

START_TEST(div_18) {
  s21_decimal a = {{0, 0, 0x80000000, 0x00000000}};
  s21_decimal b = {{0, 0, 0, 0x800A0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_div(a, b, &c));
}
END_TEST

START_TEST(div_19) {
  s21_decimal a = {{2500, 0, 0, 0x00010000}};
  s21_decimal b = {{5000, 0, 0, 0x00030000}};
  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal cr = {{50, 0, 0, 0}};
  s21_div(a, b, &c);
  ck_assert_int_eq(1, s21_is_equal(c, cr));
}
END_TEST

// START_TEST(div_20)
// {
//   s21_decimal a = {{1, 0, 0, 0x00000000}};
//   s21_decimal b = {{3, 0, 0, 0x00000000}};
//   s21_decimal c = {{0, 0, 0, 0}};
//   // 180700362 347537611 89478485 scale = 28
//   s21_decimal cr = {{89478485, 347537611, 180700362, 0x1C0000}};
//   s21_div(a, b, &c);

//   ck_assert_int_eq(1, s21_is_equal(c, cr));
// }
// END_TEST

START_TEST(div_21) {
  s21_decimal a = {{4294967295, 4294967295, 4294967295,
                    0x80000000}};      // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_div(a, b, &res_bits);
  ck_assert_int_eq(res, 2);
  ck_assert_uint_eq(res_bits.bits[0], 0);
  ck_assert_uint_eq(res_bits.bits[1], 0);
  ck_assert_uint_eq(res_bits.bits[2], 0);
  ck_assert_uint_eq(res_bits.bits[3], 0);
}
END_TEST

// // //=========================================================
// // 6 операторов сравнения

// // Меньше---------------------------------------------

START_TEST(less_1) {
  s21_decimal test_v_1 = {{10, 0, 0, 0}};
  s21_decimal test_v_2 = {{15, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_2) {
  s21_decimal test_v_1 = {{6739, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_3) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_4) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_5) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_6) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_7) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_8) {
  s21_decimal test_v_1 = {{19876, 1, 0, 2147483648}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

// Меньше/равно---------------------------------------------

START_TEST(less_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_eq_5) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

// Больше---------------------------------------------

START_TEST(greater_1) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_2) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);
}
END_TEST

START_TEST(greater_3) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_4) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_5) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
}
END_TEST

// Больше/равно-----------------------------------------

START_TEST(greater_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(greater_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_5) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

// Равно-----------------------------------------

START_TEST(eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_5) {
  s21_decimal test_v_1 = {{1234, 1, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 2, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_6) {
  int otvet = 1;
  s21_decimal my_decimal1 = {{10, 0, 0, 0}};
  s21_decimal my_decimal2 = {{10, 0, 0, 0}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

START_TEST(eq_7) {
  int otvet = 0;
  s21_decimal my_decimal1 = {{1000, 0, 0, 0}};
  s21_decimal my_decimal2 = {{10, 0, 0, 0}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

START_TEST(eq_8) {
  int otvet = 0;
  s21_decimal my_decimal1 = {{5, 0, 0, 0x8000}};
  s21_decimal my_decimal2 = {{10, 0, 0, 0x8000}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

START_TEST(eq_9) {
  int otvet = 0;
  s21_decimal my_decimal1 = {{0, 0, 0, 0x80000000}};
  s21_decimal my_decimal2 = {{0, 0, 0, 0}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

START_TEST(eq_10) {
  int otvet = 1;
  s21_decimal my_decimal1 = {{0, 0, 0, 0x000A0000}};
  s21_decimal my_decimal2 = {{0, 0, 0, 0}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

START_TEST(eq_11) {
  int otvet = 0;
  s21_decimal my_decimal1 = {{0, 0, 0, 0x000A0000}};
  s21_decimal my_decimal2 = {{1, 0, 0, 0}};
  int my_otvet = s21_is_equal(my_decimal1, my_decimal2);
  ck_assert_uint_eq(my_otvet, otvet);
}
END_TEST

// Неравно-----------------------------------------

START_TEST(not_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(not_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(not_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(not_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(not_eq_5) {
  s21_decimal test_v_1 = {{1234, 1, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 2, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

//=========================================================
// 4 функции конвертации

// int -> decimal --------------------------------------

START_TEST(itod_1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_3) {
  s21_decimal result;
  s21_from_int_to_decimal(1234, &result);
  ck_assert_int_eq(result.bits[0], 1234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_5) {
  s21_decimal result;
  s21_from_int_to_decimal(__INT_MAX__, &result);
  ck_assert_int_eq(result.bits[0], __INT_MAX__);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_6) {
  s21_decimal result;
  s21_from_int_to_decimal(__INT_MAX__ + 0.1234234, &result);
  ck_assert_int_eq(result.bits[0], __INT_MAX__);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_7) {
  s21_decimal *dst = NULL;
  int result = s21_from_int_to_decimal(123, dst);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"

START_TEST(itod_8) {
  s21_decimal *dst = NULL;
  int result = s21_from_int_to_decimal(-__INT_MAX__ - 1, dst);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(itod_9) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  int param = 5;

  s21_from_int_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 0);
}
END_TEST

START_TEST(itod_10) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  int param = 2147483647;

  s21_from_int_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483647);
  ck_assert_float_eq(test_dec.bits[3], 0);
}
END_TEST

START_TEST(itod_11) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  int param = -2147483648;

  s21_from_int_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483648);
  ck_assert_float_eq(test_dec.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_12) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  int param = -5;

  s21_from_int_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_13) {
  s21_decimal val;
  int res = s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], 0x80000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0x80000000);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(itod_14) {
  s21_decimal val;
  int res = s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(res, 0);

  res = s21_from_int_to_decimal(-0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(res, 0);

  res = s21_from_int_to_decimal(+0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(itod_15) {
  s21_decimal val;

  int res = s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
  ck_assert_int_eq(res, 0);

  res = s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(itod_16) {
  s21_decimal val;
  int res = s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

#pragma GCC diagnostic pop

// float -> decimal --------------------------------------

START_TEST(ftod_1) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(ftod_2) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(ftod_3) {
  s21_decimal result;
  s21_from_float_to_decimal(1.02E+09, &result);
  ck_assert_int_eq(result.bits[0], 1020000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(ftod_4) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147745792);
}
END_TEST

START_TEST(ftod_5) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(ftod_6) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(-1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(ftod_7) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(ftod_8) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 5.0, need_param = 5.0;
  int need_3_bit = 0;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], need_param);
  ck_assert_float_eq(test_dec.bits[3], need_3_bit);
}
END_TEST

START_TEST(ftod_9) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 0.05;

  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 131072);
}
END_TEST

START_TEST(ftod_10) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 0.005;

  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 196608);
}
END_TEST

START_TEST(ftod_11) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = -0.5;

  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 2147549184);
}
END_TEST

START_TEST(ftod_12) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = -0.05;

  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5);
  ck_assert_float_eq(test_dec.bits[3], 2147614720);
}
END_TEST

START_TEST(ftod_13) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 50;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 50);
  ck_assert_float_eq(test_dec.bits[3], 0);
}
END_TEST

START_TEST(ftod_14) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 5000;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 5000);
  ck_assert_float_eq(test_dec.bits[3], 0);
}
END_TEST

START_TEST(ftod_15) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 2147483;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483);
  ck_assert_float_eq(test_dec.bits[3], 0);
}
END_TEST

START_TEST(ftod_16) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = 0.2147483;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483);
  ck_assert_float_eq(test_dec.bits[3], 458752);
}
END_TEST

START_TEST(ftod_17) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = -0.2147483;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483);
  ck_assert_float_eq(test_dec.bits[3], 458752 + 2147483648);
}
END_TEST

START_TEST(ftod_18) {
  s21_decimal test_dec = {{0, 0, 0, 0}};
  float param = -2147483;
  s21_from_float_to_decimal(param, &test_dec);
  ck_assert_float_eq(test_dec.bits[0], 2147483);
  ck_assert_float_eq(test_dec.bits[3], 2147483648);
}
END_TEST

// decimal -> int --------------------------------------

START_TEST(dtoi_1) {
  int number = 0;
  s21_decimal src = {{__INT_MAX__, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, __INT_MAX__);
}
END_TEST

START_TEST(dtoi_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(dtoi_3) {
  int number = 0;
  s21_decimal src = {{1234, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -1234);
}
END_TEST

START_TEST(dtoi_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 0);
}
END_TEST

START_TEST(dtoi_5) {
  int number = 0;
  s21_decimal src = {{100, 0, 0, 65536}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 10);
}
END_TEST

START_TEST(dtoi_6) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 65536}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 0);
}
END_TEST

START_TEST(dtoi_7) {
  int number = 0;
  s21_decimal src = {{1234567890, 0, 0, 21476802}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 0);
}
END_TEST

START_TEST(dtoi_8) {
  s21_decimal test_dec = {{20, 0, 0, 0}};
  int param = 0, need_param = 20, error = 0;
  int func_error = s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(param, need_param);
  ck_assert_int_eq(error, func_error);
}
END_TEST

START_TEST(dtoi_9) {
  s21_decimal test_dec = {{20, 0, 0, 2147483648}};
  int param;
  s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(param, -20);
}
END_TEST

START_TEST(dtoi_10) {
  s21_decimal test_dec = {{2147483648, 0, 0, 2147483648}};
  int param, need_param = -2147483648;
  s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(param, need_param);
}
END_TEST

START_TEST(dtoi_11) {
  s21_decimal test_dec = {{2147483647, 0, 1, 2147483648}};
  int param;
  int error = s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dtoi_12) {
  s21_decimal test_dec = {{2147483647, 1, 0, 2147483648}};
  int param;
  int error = s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dtoi_13) {
  s21_decimal test_dec = {{2147483647, 1, 0, 0x30000}};
  int param;
  s21_from_decimal_to_int(test_dec, &param);
  ck_assert_int_eq(param, 6442450);
}
END_TEST

// decimal -> float --------------------------------------

START_TEST(dtof_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(dtof_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(dtof_3) {
  float number = 0.0;
  s21_decimal src = {{MAX_UINT, MAX_UINT, 0, 0}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST
START_TEST(dtof_4) {
  s21_decimal test_dec = {{5, 0, 0, 2147483648}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, -5.0);
}
END_TEST

START_TEST(dtof_5) {
  s21_decimal test_dec = {{5, 0, 0, 0}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, 5.0);
}
END_TEST

START_TEST(dtof_6) {
  s21_decimal test_dec = {{5, 0, 0, 131072}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, 0.05);
}
END_TEST

START_TEST(dtof_7) {
  s21_decimal test_dec = {{5, 0, 0, 262144}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, 0.0005);
}
END_TEST

START_TEST(dtof_8) {
  s21_decimal test_dec = {{5, 0, 0, 2147549184}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, -0.5);
}
END_TEST

START_TEST(dtof_9) {
  s21_decimal test_dec = {{5, 0, 0, 2147614720}};
  float param = 0;

  s21_from_decimal_to_float(test_dec, &param);
  ck_assert_float_eq(param, -0.05);
}
END_TEST

// //=========================================================
// // 4 математические функции

// // floor_decimal --------------------------------------

START_TEST(floor_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal v_1 = {{679988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal v_1 = {{679988, 0, 0, 2147745796}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 25);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_floor_test) {
  s21_decimal value_1 = {{111000, 0, 0, 196608}};
  s21_decimal result_1 = {{0, 0, 0, 0}};
  int result = s21_floor(value_1, &result_1);
  ck_assert_int_eq(result_1.bits[0], 111);
  ck_assert_int_eq(result_1.bits[1], 0);
  ck_assert_int_eq(result_1.bits[2], 0);
  ck_assert_int_eq(result_1.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_2 = {{329573, 0, 0, 131072}};
  s21_decimal result_2 = {{0, 0, 0, 0}};
  result = s21_floor(value_2, &result_2);
  ck_assert_int_eq(result_2.bits[0], 3295);
  ck_assert_int_eq(result_2.bits[1], 0);
  ck_assert_int_eq(result_2.bits[2], 0);
  ck_assert_int_eq(result_2.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_3 = {{4234, 0, 0, 196608}};
  s21_decimal result_3 = {{0, 0, 0, 0}};
  result = s21_floor(value_3, &result_3);
  ck_assert_int_eq(result_3.bits[0], 4);
  ck_assert_int_eq(result_3.bits[1], 0);
  ck_assert_int_eq(result_3.bits[2], 0);
  ck_assert_int_eq(result_3.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_4 = {{1, 0, 0, 196608}};
  s21_decimal result_4 = {{0, 0, 0, 0}};
  result = s21_floor(value_4, &result_4);
  ck_assert_int_eq(result_4.bits[0], 0);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_5 = {{0, 0, 0, 196608}};
  s21_decimal result_5 = {{0, 0, 0, 0}};
  result = s21_floor(value_5, &result_5);
  ck_assert_int_eq(result_4.bits[0], 0);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_6 = {{10000000, 0, 0, 196608}};
  s21_decimal result_6 = {{0, 0, 0, 0}};
  result = s21_truncate(value_6, &result_6);
  ck_assert_int_eq(result_6.bits[0], 10000);
  ck_assert_int_eq(result_6.bits[1], 0);
  ck_assert_int_eq(result_6.bits[2], 0);
  ck_assert_int_eq(result_6.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_7 = {{10000, 0, 0, 196608}};
  s21_decimal result_7 = {{0, 0, 0, 0}};
  result = s21_floor(value_7, &result_7);
  ck_assert_int_eq(result_7.bits[0], 10);
  ck_assert_int_eq(result_7.bits[1], 0);
  ck_assert_int_eq(result_7.bits[2], 0);
  ck_assert_int_eq(result_7.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_8 = {{1000, 0, 0, 196608}};
  s21_decimal result_8 = {{0, 0, 0, 0}};
  result = s21_floor(value_8, &result_8);
  ck_assert_int_eq(result_8.bits[0], 1);
  ck_assert_int_eq(result_8.bits[1], 0);
  ck_assert_int_eq(result_8.bits[2], 0);
  ck_assert_int_eq(result_8.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_9 = {{100, 0, 0, 196608}};
  s21_decimal result_9 = {{0, 0, 0, 0}};
  result = s21_floor(value_9, &result_9);
  ck_assert_int_eq(result_9.bits[0], 0);
  ck_assert_int_eq(result_9.bits[1], 0);
  ck_assert_int_eq(result_9.bits[2], 0);
  ck_assert_int_eq(result_9.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_10 = {{48560, 0, 0, 2147745792}};
  s21_decimal result_10 = {{0, 0, 0, 0}};
  result = s21_floor(value_10, &result_10);
  ck_assert_int_eq(result_10.bits[0], 5);
  ck_assert_int_eq(result_10.bits[1], 0);
  ck_assert_int_eq(result_10.bits[2], 0);
  ck_assert_int_eq(result_10.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_11 = {{1000, 0, 0, 262144}};
  s21_decimal result_11 = {{0, 0, 0, 0}};
  result = s21_floor(value_11, &result_11);
  ck_assert_int_eq(result_11.bits[0], 0);
  ck_assert_int_eq(result_11.bits[1], 0);
  ck_assert_int_eq(result_11.bits[2], 0);
  ck_assert_int_eq(result_11.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_12 = {{10, 0, 0, 2147745792}};
  s21_decimal result_12 = {{0, 0, 0, 0}};
  result = s21_floor(value_12, &result_12);
  ck_assert_int_eq(result_12.bits[0], 1);
  ck_assert_int_eq(result_12.bits[1], 0);
  ck_assert_int_eq(result_12.bits[2], 0);
  ck_assert_int_eq(result_12.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_13 = {{23487565, 0, 0, 2147745792}};
  s21_decimal result_13 = {{0, 0, 0, 0}};
  result = s21_truncate(value_13, &result_13);
  ck_assert_int_eq(result_13.bits[0], 2348);
  ck_assert_int_eq(result_13.bits[1], 0);
  ck_assert_int_eq(result_13.bits[2], 0);
  ck_assert_int_eq(result_13.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_14 = {{4284967295, 0, 0, 589824}};
  s21_decimal result_14 = {{0, 0, 0, 0}};
  result = s21_truncate(value_14, &result_14);
  ck_assert_int_eq(result_14.bits[0], 4);
  ck_assert_int_eq(result_14.bits[1], 0);
  ck_assert_int_eq(result_14.bits[2], 0);
  ck_assert_int_eq(result_14.bits[3], 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

// // round_decimal --------------------------------------

START_TEST(round_1) {
  s21_decimal v_1 = {{5, 0, 1, 0}};
  // set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 5);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_2) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_3) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(round_4) {
  s21_decimal v_1 = {{0, 1, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 0);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_5) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 26);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test) {
  s21_decimal value_1 = {{5465567, 0, 0, 65536}};
  s21_decimal result_1 = {{0, 0, 0, 0}};
  int result = s21_round(value_1, &result_1);
  ck_assert_int_eq(result_1.bits[0], 546557);
  ck_assert_int_eq(result_1.bits[1], 0);
  ck_assert_int_eq(result_1.bits[2], 0);
  ck_assert_int_eq(result_1.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_2 = {{5462, 0, 0, 65536}};
  s21_decimal result_2 = {{0, 0, 0, 0}};
  result = s21_round(value_2, &result_2);
  ck_assert_int_eq(result_2.bits[0], 546);
  ck_assert_int_eq(result_2.bits[1], 0);
  ck_assert_int_eq(result_2.bits[2], 0);
  ck_assert_int_eq(result_2.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_3 = {{54622343, 0, 0, 65536}};
  s21_decimal result_3 = {{0, 0, 0, 0}};
  result = s21_round(value_3, &result_3);
  ck_assert_int_eq(result_3.bits[0], 5462234);
  ck_assert_int_eq(result_3.bits[1], 0);
  ck_assert_int_eq(result_3.bits[2], 0);
  ck_assert_int_eq(result_3.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_4 = {{546, 0, 0, 2147549184}};
  s21_decimal result_4 = {{0, 0, 0, 0}};
  result = s21_round(value_4, &result_4);
  ck_assert_int_eq(result_4.bits[0], 55);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_5 = {{541, 0, 0, 2147549184}};
  s21_decimal result_5 = {{0, 0, 0, 0}};
  result = s21_round(value_5, &result_5);
  ck_assert_int_eq(result_5.bits[0], 54);
  ck_assert_int_eq(result_5.bits[1], 0);
  ck_assert_int_eq(result_5.bits[2], 0);
  ck_assert_int_eq(result_5.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_9 = {{1, 0, 0, 262144}};
  s21_decimal result_9 = {{0, 0, 0, 0}};
  result = s21_round(value_9, &result_9);
  ck_assert_int_eq(result_9.bits[0], 0);
  ck_assert_int_eq(result_9.bits[1], 0);
  ck_assert_int_eq(result_9.bits[2], 0);
  ck_assert_int_eq(result_9.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_10 = {{15555, 0, 0, 2147549184}};
  s21_decimal result_10 = {{0, 0, 0, 0}};
  result = s21_round(value_10, &result_10);
  ck_assert_int_eq(result_10.bits[0], 1556);
  ck_assert_int_eq(result_10.bits[1], 0);
  ck_assert_int_eq(result_10.bits[2], 0);
  ck_assert_int_eq(result_10.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);
}
END_TEST
// // negate_decimal --------------------------------------

START_TEST(negate_1) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_negate_test) {
  s21_decimal value_1 = {{111000, 0, 0, 196608}};
  s21_decimal result_1 = {{0, 0, 0, 0}};
  int result = s21_negate(value_1, &result_1);
  ck_assert_int_eq(result_1.bits[0], 111000);
  ck_assert_int_eq(result_1.bits[1], 0);
  ck_assert_int_eq(result_1.bits[2], 0);
  ck_assert_int_eq(result_1.bits[3], 2147680256);
  ck_assert_int_eq(result, 0);

  s21_decimal value_2 = {{3535, 0, 0, 0}};
  s21_decimal result_2 = {{0, 0, 0, 0}};
  result = s21_negate(value_2, &result_2);
  ck_assert_int_eq(result_2.bits[0], 3535);
  ck_assert_int_eq(result_2.bits[1], 0);
  ck_assert_int_eq(result_2.bits[2], 0);
  ck_assert_int_eq(result_2.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_3 = {{3535, 0, 0, 2147483648}};
  s21_decimal result_3 = {{0, 0, 0, 0}};
  result = s21_negate(value_3, &result_3);
  ck_assert_int_eq(result_3.bits[0], 3535);
  ck_assert_int_eq(result_3.bits[1], 0);
  ck_assert_int_eq(result_3.bits[2], 0);
  ck_assert_int_eq(result_3.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_4 = {{111000, 0, 0, 2147680256}};
  s21_decimal result_4 = {{0, 0, 0, 0}};
  result = s21_negate(value_4, &result_4);
  ck_assert_int_eq(result_4.bits[0], 111000);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 196608);
  ck_assert_int_eq(result, 0);

  s21_decimal value_5 = {{111000, 0, 0, 196608}};
  s21_decimal result_5 = {{0, 0, 0, 0}};
  result = s21_negate(value_5, &result_5);
  ck_assert_int_eq(result_5.bits[0], 111000);
  ck_assert_int_eq(result_5.bits[1], 0);
  ck_assert_int_eq(result_5.bits[2], 0);
  ck_assert_int_eq(result_5.bits[3], 2147680256);
  ck_assert_int_eq(result, 0);

  s21_decimal value_6 = {{111000, 0, 0, 2147680256}};
  s21_decimal result_6 = {{0, 0, 0, 0}};
  result = s21_negate(value_6, &result_6);
  ck_assert_int_eq(result_6.bits[0], 111000);
  ck_assert_int_eq(result_6.bits[1], 0);
  ck_assert_int_eq(result_6.bits[2], 0);
  ck_assert_int_eq(result_6.bits[3], 196608);
  ck_assert_int_eq(result, 0);
}
END_TEST

// // truncate_decimal --------------------------------------

START_TEST(truncate_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal v_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-2744406, &v_1);
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 2744406);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_truncate_test) {
  s21_decimal value_1 = {{111000, 0, 0, 196608}};
  s21_decimal result_1 = {{0, 0, 0, 0}};
  int result = s21_truncate(value_1, &result_1);
  ck_assert_int_eq(result_1.bits[0], 111);
  ck_assert_int_eq(result_1.bits[1], 0);
  ck_assert_int_eq(result_1.bits[2], 0);
  ck_assert_int_eq(result_1.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_2 = {{329573, 0, 0, 131072}};
  s21_decimal result_2 = {{0, 0, 0, 0}};
  result = s21_truncate(value_2, &result_2);
  ck_assert_int_eq(result_2.bits[0], 3295);
  ck_assert_int_eq(result_2.bits[1], 0);
  ck_assert_int_eq(result_2.bits[2], 0);
  ck_assert_int_eq(result_2.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_3 = {{4234, 0, 0, 196608}};
  s21_decimal result_3 = {{0, 0, 0, 0}};
  result = s21_truncate(value_3, &result_3);
  ck_assert_int_eq(result_3.bits[0], 4);
  ck_assert_int_eq(result_3.bits[1], 0);
  ck_assert_int_eq(result_3.bits[2], 0);
  ck_assert_int_eq(result_3.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_4 = {{1, 0, 0, 196608}};
  s21_decimal result_4 = {{0, 0, 0, 0}};
  result = s21_truncate(value_4, &result_4);
  ck_assert_int_eq(result_4.bits[0], 0);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_5 = {{0, 0, 0, 196608}};
  s21_decimal result_5 = {{0, 0, 0, 0}};
  result = s21_truncate(value_5, &result_5);
  ck_assert_int_eq(result_4.bits[0], 0);
  ck_assert_int_eq(result_4.bits[1], 0);
  ck_assert_int_eq(result_4.bits[2], 0);
  ck_assert_int_eq(result_4.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_6 = {{10000000, 0, 0, 196608}};
  s21_decimal result_6 = {{0, 0, 0, 0}};
  result = s21_truncate(value_6, &result_6);
  ck_assert_int_eq(result_6.bits[0], 10000);
  ck_assert_int_eq(result_6.bits[1], 0);
  ck_assert_int_eq(result_6.bits[2], 0);
  ck_assert_int_eq(result_6.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_7 = {{10000, 0, 0, 196608}};
  s21_decimal result_7 = {{0, 0, 0, 0}};
  result = s21_truncate(value_7, &result_7);
  ck_assert_int_eq(result_7.bits[0], 10);
  ck_assert_int_eq(result_7.bits[1], 0);
  ck_assert_int_eq(result_7.bits[2], 0);
  ck_assert_int_eq(result_7.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_8 = {{1000, 0, 0, 196608}};
  s21_decimal result_8 = {{0, 0, 0, 0}};
  result = s21_truncate(value_8, &result_8);
  ck_assert_int_eq(result_8.bits[0], 1);
  ck_assert_int_eq(result_8.bits[1], 0);
  ck_assert_int_eq(result_8.bits[2], 0);
  ck_assert_int_eq(result_8.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_9 = {{100, 0, 0, 196608}};
  s21_decimal result_9 = {{0, 0, 0, 0}};
  result = s21_truncate(value_9, &result_9);
  ck_assert_int_eq(result_9.bits[0], 0);
  ck_assert_int_eq(result_9.bits[1], 0);
  ck_assert_int_eq(result_9.bits[2], 0);
  ck_assert_int_eq(result_9.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_10 = {{38560, 0, 0, 2147745792}};
  s21_decimal result_10 = {{0, 0, 0, 0}};
  result = s21_truncate(value_10, &result_10);
  ck_assert_int_eq(result_10.bits[0], 3);
  ck_assert_int_eq(result_10.bits[1], 0);
  ck_assert_int_eq(result_10.bits[2], 0);
  ck_assert_int_eq(result_10.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_11 = {{1000, 0, 0, 2147745792}};
  s21_decimal result_11 = {{0, 0, 0, 0}};
  result = s21_truncate(value_11, &result_11);
  ck_assert_int_eq(result_11.bits[0], 0);
  ck_assert_int_eq(result_11.bits[1], 0);
  ck_assert_int_eq(result_11.bits[2], 0);
  ck_assert_int_eq(result_11.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_12 = {{10, 0, 0, 2147745792}};
  s21_decimal result_12 = {{0, 0, 0, 0}};
  result = s21_truncate(value_12, &result_12);
  ck_assert_int_eq(result_12.bits[0], 0);
  ck_assert_int_eq(result_12.bits[1], 0);
  ck_assert_int_eq(result_12.bits[2], 0);
  ck_assert_int_eq(result_12.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_13 = {{23487565, 0, 0, 2147745792}};
  s21_decimal result_13 = {{0, 0, 0, 0}};
  result = s21_truncate(value_13, &result_13);
  ck_assert_int_eq(result_13.bits[0], 2348);
  ck_assert_int_eq(result_13.bits[1], 0);
  ck_assert_int_eq(result_13.bits[2], 0);
  ck_assert_int_eq(result_13.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);

  s21_decimal value_14 = {{S21_MAX_UINT, 0, 0, 589824}};
  s21_decimal result_14 = {{0, 0, 0, 0}};
  result = s21_truncate(value_14, &result_14);
  ck_assert_int_eq(result_14.bits[0], 4);
  ck_assert_int_eq(result_14.bits[1], 0);
  ck_assert_int_eq(result_14.bits[2], 0);
  ck_assert_int_eq(result_14.bits[3], 0);
  ck_assert_int_eq(result, 0);

  s21_decimal value_15 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};

  s21_decimal result_15 = {{0, 0, 0, 0}};
  result = s21_truncate(value_15, &result_15);
  ck_assert_int_eq(result_15.bits[0], S21_MAX_UINT);
  ck_assert_int_eq(result_15.bits[1], S21_MAX_UINT);
  ck_assert_int_eq(result_15.bits[2], S21_MAX_UINT);
  ck_assert_int_eq(result_15.bits[3], 0);
  ck_assert_int_eq(result, 1);
  s21_decimal value_16 = {{1546, 0, 0, 0}};
  s21_decimal result_16 = {{0, 0, 0, 0}};
  result = s21_truncate(value_16, &result_16);
  ck_assert_int_eq(result_16.bits[0], 1546);
  ck_assert_int_eq(result_16.bits[1], 0);
  ck_assert_int_eq(result_16.bits[2], 0);
  ck_assert_int_eq(result_16.bits[3], 0);
  ck_assert_int_eq(result, 0);
}

START_TEST(ttruncate_1) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 0, 0}};
  s21_decimal check_value = {{0, 0, 0, 0}};
  s21_decimal otvet = {{6, 0, 0, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_value);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_value.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_value.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_value.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_value.bits[0]);
}
END_TEST

START_TEST(ttruncate_2) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 0, 0}};
  s21_decimal check_value = {{0, 0, 0, 0}};
  s21_decimal otvet = {{6, 0, 0, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_value);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_value.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_value.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_value.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_value.bits[0]);
}
END_TEST

START_TEST(ttruncate_3) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 12, 65536}};
  s21_decimal check_value = {{0, 0, 0, 0}};
  s21_decimal otvet = {{858993459, 858993459, 1, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_value);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_value.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_value.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_value.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_value.bits[0]);
}
END_TEST

START_TEST(ttruncate_4) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 65536}};
  s21_decimal check_value = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0x99999999, 0x99999999, 0x19999999, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_value);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_value.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_value.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_value.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_value.bits[0]);
}
END_TEST

// // //=========================================================

// //=========================================================
// // 4 арифметических оператора

// // Сложение ---------------------------------------------

Suite *add(void) {
  Suite *s1_1 = suite_create(COLOR_SUITE("-- ADD --"));
  TCase *tc1 = tcase_create(COLOR_CASE("ADD"));

  tcase_add_test(tc1, add_1);
  tcase_add_test(tc1, add_2);
  tcase_add_test(tc1, add_3);
  tcase_add_test(tc1, add_4);
  tcase_add_test(tc1, add_5);
  tcase_add_test(tc1, add_6);
  tcase_add_test(tc1, add_7);
  tcase_add_test(tc1, add_8);
  // tcase_add_test(tc1, add_9);
  tcase_add_test(tc1, add_10);
  tcase_add_test(tc1, add_11);
  tcase_add_test(tc1, add_12);
  tcase_add_test(tc1, add_13);
  tcase_add_test(tc1, add_14);
  tcase_add_test(tc1, add_15);
  tcase_add_test(tc1, add_16);
  tcase_add_test(tc1, add_17);
  tcase_add_test(tc1, add_18);
  tcase_add_test(tc1, add_19);
  tcase_add_test(tc1, add_20);
  tcase_add_test(tc1, add_21);
  tcase_add_test(tc1, add_22);
  tcase_add_test(tc1, add_23);
  tcase_add_test(tc1, add_24);
  tcase_add_test(tc1, add_25);
  tcase_add_test(tc1, s21_add_1);
  tcase_add_test(tc1, s21_add_2);
  tcase_add_test(tc1, s21_add_3);
  tcase_add_test(tc1, s21_add_4);
  tcase_add_test(tc1, s21_add_6);
  tcase_add_test(tc1, s21_add_7);
  tcase_add_test(tc1, s21_add_8);
  tcase_add_test(tc1, s21_add_9);
  tcase_add_test(tc1, s21_add_10);
  tcase_add_test(tc1, s21_add_11);
  tcase_add_test(tc1, s21_add_12);
  tcase_add_test(tc1, s21_add_13);
  tcase_add_test(tc1, s21_add_14);
  tcase_add_test(tc1, s21_add_16);
  tcase_add_test(tc1, s21_add_18);
  tcase_add_test(tc1, s21_add_23);
  tcase_add_test(tc1, s21_add_24);
  tcase_add_test(tc1, s21_add_25);
  tcase_add_test(tc1, s21_add_27);
  tcase_add_test(tc1, s21_add_28);
  tcase_add_test(tc1, s21_add_29);
  tcase_add_test(tc1, s21_add_30);
  tcase_add_test(tc1, s21_add_31);
  tcase_add_test(tc1, s21_add_36);
  tcase_add_test(tc1, s21_add_40);
  tcase_add_test(tc1, s21_add_44);
  tcase_add_test(tc1, s21_add_45);
  tcase_add_test(tc1, s21_add_51);
  // tcase_add_test(tc1, s21_add_52);
  tcase_add_test(tc1, ss21_add_1);
  tcase_add_test(tc1, ss21_add_2);
  tcase_add_test(tc1, ss21_add_3);
  tcase_add_test(tc1, ss21_add_4);
  tcase_add_test(tc1, ss21_add_5);
  tcase_add_test(tc1, ss21_add_6);
  tcase_add_test(tc1, ss21_add_7);
  tcase_add_test(tc1, ss21_add_8);
  tcase_add_test(tc1, ss21_add_9);
  tcase_add_test(tc1, ss21_add_10);
  tcase_add_test(tc1, ss21_add_11);
  tcase_add_test(tc1, ss21_add_12);
  tcase_add_test(tc1, ss21_add_13);
  tcase_add_test(tc1, ss21_add_14);
  tcase_add_test(tc1, ss21_add_15);
  // tcase_add_test(tc1, ss21_add_16);
  tcase_add_test(tc1, ss21_add_17);
  tcase_add_test(tc1, ss21_add_18);
  tcase_add_test(tc1, ss21_add_19);
  tcase_add_test(tc1, ss21_add_20);
  tcase_add_test(tc1, ss21_add_21);
  tcase_add_test(tc1, ss21_add_22);
  tcase_add_test(tc1, ss21_add_23);
  tcase_add_test(tc1, ss21_add_24);
  tcase_add_test(tc1, ss21_add_25);
  tcase_add_test(tc1, ss21_add_26);
  tcase_add_test(tc1, ss21_add_27);
  tcase_add_test(tc1, ss21_add_28);
  tcase_add_test(tc1, ss21_add_29);
  tcase_add_test(tc1, ss21_add_30);

  suite_add_tcase(s1_1, tc1);
  return s1_1;
}

// // Вычитание ---------------------------------------------

Suite *sub(void) {
  Suite *s2 = suite_create(COLOR_SUITE("-- SUB --"));
  TCase *tc2 = tcase_create(COLOR_CASE("SUB"));

  tcase_add_test(tc2, sub_1);
  tcase_add_test(tc2, sub_2);
  tcase_add_test(tc2, sub_3);
  tcase_add_test(tc2, sub_4);
  tcase_add_test(tc2, sub_5);
  tcase_add_test(tc2, sub_6);
  tcase_add_test(tc2, sub_7);
  tcase_add_test(tc2, sub_8);
  tcase_add_test(tc2, sub_9);
  tcase_add_test(tc2, sub_10);
  tcase_add_test(tc2, sub_11);

  suite_add_tcase(s2, tc2);
  return s2;
}

// Умножение ---------------------------------------------

Suite *mul(void) {
  Suite *s3 = suite_create(COLOR_SUITE("-- MUL --"));
  TCase *tc3 = tcase_create(COLOR_CASE("MUL"));

  tcase_add_test(tc3, mul_1);
  tcase_add_test(tc3, mul_2);
  tcase_add_test(tc3, mul_3);
  tcase_add_test(tc3, mul_4);
  tcase_add_test(tc3, mul_5);
  tcase_add_test(tc3, mul_6);
  tcase_add_test(tc3, mul_7);
  tcase_add_test(tc3, mul_8);
  tcase_add_test(tc3, mul_9);
  tcase_add_test(tc3, mul_10);
  tcase_add_test(tc3, s21_mul_1);
  tcase_add_test(tc3, s21_mul_2);
  tcase_add_test(tc3, s21_mul_3);
  tcase_add_test(tc3, s21_mul_4);
  tcase_add_test(tc3, s21_mul_5);
  tcase_add_test(tc3, s21_mul_6);
  tcase_add_test(tc3, s21_mul_7);
  tcase_add_test(tc3, s21_mul_8);
  tcase_add_test(tc3, s21_mul_9);
  tcase_add_test(tc3, s21_mul_10);
  tcase_add_test(tc3, s21_mul_11);
  tcase_add_test(tc3, s21_mul_12);
  tcase_add_test(tc3, s21_mul_13);
  tcase_add_test(tc3, s21_mul_14);
  tcase_add_test(tc3, s21_mul_15);
  tcase_add_test(tc3, s21_mul_16);
  tcase_add_test(tc3, s21_mul_17);
  tcase_add_test(tc3, s21_mul_18);
  tcase_add_test(tc3, s21_mul_19);
  tcase_add_test(tc3, s21_mul_20);
  tcase_add_test(tc3, s21_mul_22);
  tcase_add_test(tc3, s21_mul_23);
  tcase_add_test(tc3, s21_mul_24);
  tcase_add_test(tc3, s21_mul_25);
  tcase_add_test(tc3, s21mul_1);
  tcase_add_test(tc3, s21mul_2);
  tcase_add_test(tc3, s21mul_3);
  tcase_add_test(tc3, s21mul_4);
  tcase_add_test(tc3, s21mul_5);
  tcase_add_test(tc3, s21mul_6);
  tcase_add_test(tc3, s21mul_7);
  tcase_add_test(tc3, s21mul_8);
  tcase_add_test(tc3, s21mul_9);
  tcase_add_test(tc3, s21_mul_test);
  // tcase_add_test(tc3, s21mul_10);

  suite_add_tcase(s3, tc3);
  return s3;
}

// Деление -----------------------------------------------

Suite *div21(void) {
  Suite *s4 = suite_create(COLOR_SUITE("-- DIV --"));
  TCase *tc4 = tcase_create(COLOR_CASE("DIV"));

  tcase_add_test(tc4, div_1);
  tcase_add_test(tc4, div_2);
  // tcase_add_test(tc4, div_3);
  tcase_add_test(tc4, div_4);
  tcase_add_test(tc4, div_5);
  tcase_add_test(tc4, div_6);
  tcase_add_test(tc4, div_7);
  tcase_add_test(tc4, div_8);
  tcase_add_test(tc4, div_9);
  tcase_add_test(tc4, div_10);
  tcase_add_test(tc4, div_11);
  tcase_add_test(tc4, div_12);
  tcase_add_test(tc4, div_13);
  tcase_add_test(tc4, div_14);
  // tcase_add_test(tc4, div_15);
  tcase_add_test(tc4, div_16);
  tcase_add_test(tc4, div_17);
  tcase_add_test(tc4, div_18);
  tcase_add_test(tc4, div_19);
  // tcase_add_test(tc4, div_20);
  tcase_add_test(tc4, div_21);

  suite_add_tcase(s4, tc4);
  return s4;
}

// //=========================================================
// // 6 операторов сравнения

// Меньше -----------------------------------------------

Suite *less(void) {
  Suite *s5 = suite_create(COLOR_SUITE("-- LESS --"));
  TCase *tc5 = tcase_create(COLOR_CASE("LESS"));

  tcase_add_test(tc5, less_1);
  tcase_add_test(tc5, less_2);
  tcase_add_test(tc5, less_3);
  tcase_add_test(tc5, less_4);
  tcase_add_test(tc5, less_5);
  tcase_add_test(tc5, less_6);
  tcase_add_test(tc5, less_7);
  tcase_add_test(tc5, less_8);

  suite_add_tcase(s5, tc5);
  return s5;
}

// Меньше/равно -----------------------------------------

Suite *less_eq(void) {
  Suite *s6 = suite_create(COLOR_SUITE("-- LESS_EQ --"));
  TCase *tc6 = tcase_create(COLOR_CASE("LESS_EQ"));

  tcase_add_test(tc6, less_eq_1);
  tcase_add_test(tc6, less_eq_2);
  tcase_add_test(tc6, less_eq_3);
  tcase_add_test(tc6, less_eq_4);
  tcase_add_test(tc6, less_eq_5);

  suite_add_tcase(s6, tc6);
  return s6;
}

// Больше -----------------------------------------------

Suite *greater(void) {
  Suite *s7 = suite_create(COLOR_SUITE("-- GR8R --"));
  TCase *tc7 = tcase_create(COLOR_CASE("GR8R"));

  tcase_add_test(tc7, greater_1);
  tcase_add_test(tc7, greater_2);
  tcase_add_test(tc7, greater_3);
  tcase_add_test(tc7, greater_4);
  tcase_add_test(tc7, greater_5);

  suite_add_tcase(s7, tc7);
  return s7;
}

// Больше/равно -----------------------------------------

Suite *greater_eq(void) {
  Suite *s8 = suite_create(COLOR_SUITE("-- GR8R_EQ --"));
  TCase *tc8 = tcase_create(COLOR_CASE("GR8R_EQ"));

  tcase_add_test(tc8, greater_eq_1);
  tcase_add_test(tc8, greater_eq_2);
  tcase_add_test(tc8, greater_eq_3);
  tcase_add_test(tc8, greater_eq_4);
  tcase_add_test(tc8, greater_eq_5);

  suite_add_tcase(s8, tc8);
  return s8;
}

// Равно -----------------------------------------------

Suite *eq(void) {
  Suite *s9 = suite_create(COLOR_SUITE("-- EQ --"));
  TCase *tc9 = tcase_create(COLOR_CASE("EQ"));

  tcase_add_test(tc9, eq_1);
  tcase_add_test(tc9, eq_2);
  tcase_add_test(tc9, eq_3);
  tcase_add_test(tc9, eq_4);
  tcase_add_test(tc9, eq_5);
  tcase_add_test(tc9, eq_6);
  tcase_add_test(tc9, eq_7);
  tcase_add_test(tc9, eq_8);
  tcase_add_test(tc9, eq_9);
  tcase_add_test(tc9, eq_10);
  tcase_add_test(tc9, eq_11);

  suite_add_tcase(s9, tc9);
  return s9;
}

// Неравно ---------------------------------------------

Suite * not_eq (void) {
  Suite *s10 = suite_create(COLOR_SUITE("-- !EQ --"));
  TCase *tc10 = tcase_create(COLOR_CASE("!EQ"));

  tcase_add_test(tc10, not_eq_1);
  tcase_add_test(tc10, not_eq_2);
  tcase_add_test(tc10, not_eq_3);
  tcase_add_test(tc10, not_eq_4);
  tcase_add_test(tc10, not_eq_5);

  suite_add_tcase(s10, tc10);
  return s10;
}

//=========================================================
// 4 функции конвертации

// int -> decimal --------------------------------------

Suite *itod(void) {
  Suite *s11 = suite_create(COLOR_SUITE("-- ITOD --"));
  TCase *tc11 = tcase_create(COLOR_CASE("ITOD"));

  tcase_add_test(tc11, itod_1);
  tcase_add_test(tc11, itod_2);
  tcase_add_test(tc11, itod_3);
  tcase_add_test(tc11, itod_4);
  tcase_add_test(tc11, itod_5);
  tcase_add_test(tc11, itod_6);
  tcase_add_test(tc11, itod_7);
  tcase_add_test(tc11, itod_8);
  tcase_add_test(tc11, itod_8);
  tcase_add_test(tc11, itod_9);
  tcase_add_test(tc11, itod_10);
  tcase_add_test(tc11, itod_11);
  tcase_add_test(tc11, itod_12);
  tcase_add_test(tc11, itod_13);
  tcase_add_test(tc11, itod_14);
  tcase_add_test(tc11, itod_15);
  tcase_add_test(tc11, itod_16);

  suite_add_tcase(s11, tc11);
  return s11;
}

// float -> decimal --------------------------------------

Suite *ftod(void) {
  Suite *s12 = suite_create(COLOR_SUITE("-- FTOD --"));
  TCase *tc12 = tcase_create(COLOR_CASE("FTOD"));

  tcase_add_test(tc12, ftod_1);
  tcase_add_test(tc12, ftod_2);
  tcase_add_test(tc12, ftod_3);
  tcase_add_test(tc12, ftod_4);
  tcase_add_test(tc12, ftod_5);
  tcase_add_test(tc12, ftod_6);
  tcase_add_test(tc12, ftod_7);
  tcase_add_test(tc12, ftod_8);
  tcase_add_test(tc12, ftod_9);
  tcase_add_test(tc12, ftod_10);
  tcase_add_test(tc12, ftod_11);
  tcase_add_test(tc12, ftod_12);
  tcase_add_test(tc12, ftod_13);
  tcase_add_test(tc12, ftod_14);
  tcase_add_test(tc12, ftod_15);
  tcase_add_test(tc12, ftod_16);
  tcase_add_test(tc12, ftod_17);
  tcase_add_test(tc12, ftod_18);

  suite_add_tcase(s12, tc12);
  return s12;
}

// decimal -> int --------------------------------------

Suite *dtoi(void) {
  Suite *s13 = suite_create(COLOR_SUITE("-- DTOI --"));
  TCase *tc13 = tcase_create(COLOR_CASE("DTOI"));

  tcase_add_test(tc13, dtoi_1);
  tcase_add_test(tc13, dtoi_2);
  tcase_add_test(tc13, dtoi_3);
  tcase_add_test(tc13, dtoi_4);
  tcase_add_test(tc13, dtoi_5);
  tcase_add_test(tc13, dtoi_6);
  tcase_add_test(tc13, dtoi_7);
  tcase_add_test(tc13, dtoi_8);
  tcase_add_test(tc13, dtoi_9);
  tcase_add_test(tc13, dtoi_10);
  tcase_add_test(tc13, dtoi_11);
  tcase_add_test(tc13, dtoi_12);
  tcase_add_test(tc13, dtoi_13);

  suite_add_tcase(s13, tc13);
  return s13;
}

// decimal -> float ------------------------------------

Suite *dtof(void) {
  Suite *s14 = suite_create(COLOR_SUITE("-- DTOF --"));
  TCase *tc14 = tcase_create(COLOR_CASE("DTOF"));

  tcase_add_test(tc14, dtof_1);
  tcase_add_test(tc14, dtof_2);
  tcase_add_test(tc14, dtof_3);
  tcase_add_test(tc14, dtof_4);
  tcase_add_test(tc14, dtof_5);
  tcase_add_test(tc14, dtof_6);
  tcase_add_test(tc14, dtof_7);
  tcase_add_test(tc14, dtof_8);
  tcase_add_test(tc14, dtof_9);

  suite_add_tcase(s14, tc14);
  return s14;
}

//=========================================================
// 4 матемаматические функции

Suite *floor_s(void) {
  Suite *s15 = suite_create(COLOR_SUITE("-- FLR --"));
  TCase *tc15 = tcase_create(COLOR_CASE("FLR"));

  tcase_add_test(tc15, floor_1);
  tcase_add_test(tc15, floor_2);
  tcase_add_test(tc15, floor_3);
  tcase_add_test(tc15, floor_4);
  tcase_add_test(tc15, s21_floor_test);

  suite_add_tcase(s15, tc15);
  return s15;
}

Suite *round_s(void) {
  Suite *s16 = suite_create(COLOR_SUITE("-- RND --"));
  TCase *tc16 = tcase_create(COLOR_CASE("RND"));

  tcase_add_test(tc16, round_1);
  tcase_add_test(tc16, round_2);
  tcase_add_test(tc16, round_3);
  tcase_add_test(tc16, round_4);
  tcase_add_test(tc16, round_5);
  tcase_add_test(tc16, s21_round_test);

  suite_add_tcase(s16, tc16);
  return s16;
}

Suite *negate(void) {
  Suite *s17 = suite_create(COLOR_SUITE("-- NEGT --"));
  TCase *tc17 = tcase_create(COLOR_CASE("NEGT"));

  tcase_add_test(tc17, negate_1);
  tcase_add_test(tc17, negate_2);
  tcase_add_test(tc17, s21_negate_test);

  suite_add_tcase(s17, tc17);
  return s17;
}

Suite *truncate(void) {
  Suite *s18 = suite_create(COLOR_SUITE("-- TRUNC --"));
  TCase *tc18 = tcase_create(COLOR_CASE("TRUNC"));

  tcase_add_test(tc18, truncate_1);
  tcase_add_test(tc18, truncate_2);
  tcase_add_test(tc18, s21_truncate_test);
  tcase_add_test(tc18, ttruncate_1);
  tcase_add_test(tc18, ttruncate_2);
  tcase_add_test(tc18, ttruncate_3);
  tcase_add_test(tc18, ttruncate_4);
  suite_add_tcase(s18, tc18);
  return s18;
}

//=========================================================

void case_test(Suite *s) {
  SRunner *all_test = srunner_create(s);
  srunner_set_fork_status(all_test, CK_NOFORK);
  srunner_run_all(all_test, CK_NORMAL);
  srunner_free(all_test);
}

int main() {
  int success = 0;

  VOILA("4 арифметических оператора:")
  case_test(add());
  case_test(sub());
  case_test(mul());
  case_test(div21());
  VOILA("6 операторов сравнения:")
  case_test(less());
  case_test(less_eq());
  case_test(greater());
  case_test(greater_eq());
  case_test(eq());
  case_test(not_eq ());
  VOILA("4 функции конвертации:")
  case_test(itod());
  case_test(ftod());
  case_test(dtoi());
  case_test(dtof());
  VOILA("4 математические функции:")
  case_test(floor_s());
  case_test(round_s());
  case_test(negate());
  case_test(truncate());

  return success;
}
