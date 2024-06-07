#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL_SIZE 4
#define NUM_255 255
#define SIGN_POS 127
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERR 1
#define TOO_LARGE 1
#define TOO_SMALL 2
#define S21_MAX_DECIMAL 0x7F

typedef enum { CONVERTATION_OK, CONVERTATION_ERROR } conv_res;

#define S21_MAX_UINT 4294967295
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

typedef struct {                    // bits[0] младшие 32 бита
  unsigned int bits[DECIMAL_SIZE];  // bits[1] средние 32 бита
} s21_decimal;                      // bits[2] старшие 32 бита
                // bits[3] содержит коэффициент масштабирования и знак

/*
                        about bits[3]
- Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю
- Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
указывает степень 10 для разделения целого числа
- Биты с 24 по 30 не используются и должны быть равны нулю
- Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный
*/

typedef union {
  float flt;
  unsigned int bits;
} lens_t;

// Функции конвертации
//  Преобразователи возвращают: 0 - OK 1 - ошибка конвертации
int s21_from_float_string(int whole, float fract, s21_decimal *value);
//  Из int в s21_decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst);
//  Из float в s21_decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst);
//  Из s21_decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
//  Из s21_decimal в float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Функции сравнения
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);

// Арифметические функции
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Другие функции
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

//  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ:
int get_bit(s21_decimal num, int index);
int set_null(s21_decimal *num, int index);
void count10_to_bin(int *count_10, int *count_10_bit);
int add_less_1010(const int *arr_help, const int *arr_10);
void add_element(int *arr_help, int *arr_10, const int *result_arr,
                 int *result_arr_copy, int *index, int *index_result,
                 int *start);
void sub_1010(int *arr_help, const int *arr_10, int *arr_help_copy);
void add_div_10(int *result_arr, int *exp_1, const int *count_bit);
void set_zero(s21_decimal *num);
int get_scale(s21_decimal num);
int add_main(s21_decimal value_1, int exp_1, s21_decimal value_2, int exp_2,
             s21_decimal *result);
void cicle(const int *value_arr, int *value_min_exp);
void slojenie(const int *value_min_exp, int *j, int *memory, int *index,
              int *result);
void slojenie_2_pervih_razryadov(const int *value_min_exp, int *j, int *memory,
                                 int *index, int *result);
int add_mul_1010(int *value_1_arr, int *value_2_arr, int *exp_1, int *exp_2);
int s21_is_greater_num(s21_decimal num1, s21_decimal num2, int result);
s21_decimal s21_superior_10(int power, s21_decimal *value);
int s21_10_conv(s21_decimal value);
void mult_10(s21_decimal value, s21_decimal *result);
void s21_rev_10_conv(s21_decimal *value, int result);
int s21_addiction_logic(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result);
int s21_shift(s21_decimal *number);
int compare_s21_decimal(const s21_decimal num1, const s21_decimal num2);
int take_sign(s21_decimal numb1, s21_decimal numb2);
int align_exponents(s21_decimal *num1, s21_decimal *num2);
int equal_bits(s21_decimal num1, s21_decimal num2);
void set_bit(s21_decimal *num, int index);
void set_1_bit(unsigned int *value, int BitNumber);
void set_1_bit_int(int *value, int BitNumber);
void set_0_bit(unsigned int *value, int BitNumber);
void set_0_bit_int(int *value, int BitNumber);
bool test_bit(unsigned int value, int BitNumber);
int compare_exp_bits(s21_decimal num1, s21_decimal num2);
int compare_last_bit(int bit1, int bit2);
unsigned int exp_decimal_bin2dec(s21_decimal dst);
int s21_is_less_num(s21_decimal num1, s21_decimal num2, int result);
int get_sign(s21_decimal *num);
void initialize_value_1_arr(int value_1_arr[]);
void convert_decimal_to_bits(s21_decimal src, int value_1_arr[]);
int calculate_count_bit(const int value_1_arr[]);
int divide_by_10(int value_1_arr[], int *exp_1, int *count_bit);
int check_bits(s21_decimal src);
int convert_bits_to_int(int value_1_arr[], int count_bit);
int get_signs(s21_decimal value_1, s21_decimal value_2, int sign_index);
void to_bit_arrays(s21_decimal value_1, s21_decimal value_2, int value_1_arr[],
                   int value_2_arr[], int result_arr[]);
int count_bits(int value_1_arr[], int value_2_arr[], int *count_bit_1,
               int *count_bit_2, int count_bit, int *index_1, int *index_2);
int perform_addition(const int *value_1_arr, const int *value_2_arr,
                     int *result_arr, int count_bit, int *index);
void perform_subtraction(int *value_1_arr, int *value_2_arr, int *result_arr,
                         int count_bit, int greater, int *index);
int round_and_check(int result_arr[], int exp_1, int count_bit, int *error,
                    int *index_1, int *index_2);
int set_exponent(int exp_1, s21_decimal *result);
int set_sign(int sign_index, const int result_arr[], s21_decimal *result,
             int greater);
void write_float_decimal_exp_more(const int *result, s21_decimal *dst,
                                  int index, int bit);
void perform_subtraction_lesser(const int *value_1_arr, int *value_2_arr,
                                int *result_arr, int count_bit, int *index);
void set_scale(s21_decimal *num, int exp);
void perform_subtraction_greater(int *value_1_arr, const int *value_2_arr,
                                 int *result_arr, int count_bit, int *index);
void print_dec(s21_decimal dec);

#endif  //  SRC_S21_DECIMAL_H_
