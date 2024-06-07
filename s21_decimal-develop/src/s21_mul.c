#include "s21_decimal.h"

void swap_decimal(s21_decimal *num1, s21_decimal *num2) {
  s21_decimal temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}

int normali(int exp_1, int exp_2, int *exp_res) {
  int result = 0;
  if (exp_1 < 29 && exp_2 < 29)
    *exp_res = (exp_1 > exp_2) ? exp_1 : exp_2;
  else
    result = 1;
  return result;
}

// Функция для умножения десятичных чисел.
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;  // Переменная для кода результата операции.
  int normalize = 0;
  memset(&(result->bits), 0,
         sizeof(result->bits));  // Обнуление битов результата.

  // Проверка особых случаев для value_1:
  int exp_1 = get_scale(value_1);
  int exp_2 = get_scale(value_2);
  int exp_res = 0;
  normalize = normali(exp_1, exp_2, &exp_res);
  int sign = take_sign(value_1, value_2);  // Получение знака операции.
  // Установка бита знака в результе, если необходимо.
  if (sign == 3 || sign == 4) set_1_bit(&result->bits[3], 31);
  // print_dec(value_1);
  // print_dec(value_2);
  s21_decimal mass[96] = {0};
  int k = 0;
  // если первый меньше второго
  if (!s21_is_greater_or_equal(value_1, value_2))
    swap_decimal(&value_1, &value_2);
  int count_null = 0;
  // проходимся по каждому элементу меньшего децимала
  for (int i = 0; i < 96; i++) {
    int index = count_null;
    // если он равен единице - создаем клон первого децимала
    if (test_bit(value_2.bits[i / 32], i % 32)) {
      int g = 0, bsd_indx = 0;
      // индекс, по которому заполняем клона
      for (; index > 0; g++, index--) set_0_bit(&mass[k].bits[g / 32], g % 32);
      for (; g < 96; g++, bsd_indx++) {
        if (test_bit(value_1.bits[bsd_indx / 32], bsd_indx % 32))
          set_1_bit(&mass[k].bits[g / 32], g % 32);
        else
          set_0_bit(&mass[k].bits[g / 32], g % 32);
      }
      k++;
      count_null++;
    } else
      count_null++;
  }
  for (int j = 0; j < k; j++) {
    res = s21_add(*result, mass[j], result);
  }
  if (sign == 3 || sign == 4) set_1_bit(&result->bits[3], 31);
  if ((result->bits[2] == S21_MAX_UINT && result->bits[1] == S21_MAX_UINT &&
       result->bits[0] == S21_MAX_UINT - 1 && test_bit(result->bits[3], 31)) ||
      (normalize && test_bit(result->bits[3], 31)))
    res = 2;
  else if ((result->bits[2] == S21_MAX_UINT &&
            result->bits[1] == S21_MAX_UINT &&
            result->bits[0] == S21_MAX_UINT - 1 &&
            !test_bit(result->bits[3], 31)) ||
           (normalize && !test_bit(result->bits[3], 31)))
    res = 1;
  if (res != 0) set_zero(result);
  set_exponent(exp_res, result);
  // if (exp_1 > 0 || exp_2 > 0) set_exponent(100, result);
  // print_dec(*result);
  return res;  // Возврат кода результата операции.
}
