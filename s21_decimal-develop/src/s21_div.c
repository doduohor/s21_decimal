#include "s21_decimal.h"

unsigned long long int decimal_to_llu(s21_decimal dec) {
  unsigned long long int resNumber = 0;
  for (int i = 0; i < 96; i++) {
    if (test_bit(dec.bits[i / 32], i % 32)) resNumber |= (1ULL << i);
    // Используем побитовый сдвиг для вычисления степени двойки
  }
  return resNumber;
}

void llu_to_decimal(unsigned long long int lluNumb, s21_decimal *dec) {
  memset(&(dec->bits), 0, sizeof(dec->bits));
  for (int index = 0; index < 96 && lluNumb > 0; index++) {
    if (lluNumb & 1)
      set_1_bit(&dec->bits[index / 32], index % 32);
    else
      set_0_bit(&dec->bits[index / 32], index % 32);
    lluNumb >>= 1;
  }
}

// Функция для деления десятичных чисел.
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;  // Переменная для кода результата операции.
  memset(&(result->bits), 0,
         sizeof(result->bits));  // Обнуление битов результата.

  // Проверка особых случаев для value_1:
  if (value_1.bits[0] == UINT_MAX && value_1.bits[1] == UINT_MAX &&
      value_1.bits[2] == UINT_MAX && !test_bit(value_1.bits[3], 31))
    res = 1;  // Если value_1 равно положительной бесконечности.
  else if (value_1.bits[0] == UINT_MAX && value_1.bits[1] == UINT_MAX &&
           value_1.bits[2] == UINT_MAX && test_bit(value_1.bits[3], 31))
    res = 2;  // Если value_1 равно отрицательной бесконечности.
  else {
    unsigned long long int numb1 = 0, numb2 = 0;
    int exp1 = get_scale(value_1);  // Получение экспоненты value_1.
    int exp2 = get_scale(value_2);  // Получение экспоненты value_2.
    int sign = take_sign(value_1, value_2);  // Получение знака операции.

    // Преобразование value_1 и value_2 в целые числа для выполнения операции.
    numb1 = (decimal_to_llu(value_1)) / (int)pow(10, exp1);
    numb2 = (decimal_to_llu(value_2)) / (int)pow(10, exp2);

    if (numb2) {
      numb1 = numb1 / numb2;  // Выполнение целочисленного деления.
      llu_to_decimal(numb1,
                     result);  // Преобразование результата в десятичное число.

      // Установка бита знака в результе, если необходимо.
      if (sign == 3 || sign == 4) set_1_bit(&result->bits[3], 31);
    } else {
      long double dbl_numb1 = 0, dbl_numb2 = 0;
      dbl_numb1 = (decimal_to_llu(value_1)) / (double)pow(10, exp1);
      dbl_numb2 = (decimal_to_llu(value_2)) / (double)pow(10, exp2);

      if (dbl_numb1 == 0.0 && dbl_numb2 > 0.0)
        res = 1;  // Если value_1 равно 0 и value_2 больше 0.
      else if (dbl_numb1 >= S21_MAX_UINT && dbl_numb2 == 0.5)
        res = 1;  // Если value_1 больше либо равно максимальному целому
                  // значению и value_2 равно 0.5.
      else if (!dbl_numb2)
        res = 3;  // Если value_2 равно 0 (деление на ноль).
      else {
        dbl_numb1 = dbl_numb1 / dbl_numb2;  // Выполнение вещественного деления.
        numb1 = dbl_numb1;
        llu_to_decimal(numb1, result);
        // Преобразование результата в десятичное число.

        // Установка бита знака в результе, если необходимо.
        if (sign == 3 || sign == 4) set_1_bit(&result->bits[3], 31);
      }
    }
  }

  return res;  // Возврат кода результата операции.
}
