#include "s21_decimal.h"

// Основа - BASED
// Функция для вычитания десятичных чисел.
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int finish = 0;  // Переменная для кода завершения операции.
  memset(&(result->bits), 0,
         sizeof(result->bits));  // Обнуление битов результата.
  int sign = take_sign(value_1, value_2);  // Получение знака операции.
  int compare = compare_s21_decimal(value_1, value_2);
  // Сравнение чисел value_1 и value_2.

  if (sign == 1) {
    set_1_bit(&value_2.bits[3], 31);
    finish = s21_add(value_1, value_2, result);
    // Выполнение операции сложения.
  } else if (sign == 2 && compare == -1) {
    set_0_bit(&value_2.bits[3], 31);
    finish = s21_add(value_1, value_2, result);
    // Выполнение операции сложения.
  } else if (sign == 2 && compare == 1) {
    set_0_bit(&value_1.bits[3], 31);
    finish = s21_add(value_1, value_2, result);
    // Выполнение операции сложения.
    set_1_bit(&result->bits[3], 31);
    // Установка бита знака в результе.
  } else if (sign == 3) {
    set_0_bit(&value_2.bits[3], 31);
    finish = s21_add(value_1, value_2, result);
    // Выполнение операции сложения.
  } else if (sign == 4) {
    set_0_bit(&value_1.bits[3], 31);
    finish = s21_add(value_1, value_2, result);
    // Выполнение операции сложения.
    set_1_bit(&result->bits[3], 31);
    // Установка бита знака в результе.
  }

  return finish;  // Возврат кода завершения операции.
}
