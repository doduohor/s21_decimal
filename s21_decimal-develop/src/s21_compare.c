#include "s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  int sign1 = get_sign(&num1);
  int sign2 = get_sign(&num2);

  if (sign1 != sign2) {
    res = 0;
  } else {
    align_exponents(&num1, &num2);
    res = equal_bits(num1, num2);
  }
  return res;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = -1;  // Изначально результат установлен на -1
  int sign_num1 = get_sign(&num1);  // Получаем знак числа num1
  int sign_num2 = get_sign(&num2);  // Получаем знак числа num2
                                    // Если оба числа положительные
  if (sign_num1 == sign_num2 && sign_num1 == 0) {
    // Вызываем функцию для сравнения чисел
    result = s21_is_less_num(num1, num2, result);
    // Если num1 отрицательное, а num2 положительное
  } else if (sign_num1 == 1 && sign_num2 == 0) {
    result = 1;  // num1 меньше num2, поэтому результат равен 1
                 // Если num1 положительное, а num2 отрицательное
  } else if (sign_num1 == 0 && sign_num2 == 1) {
    result = 0;  // num1 больше num2, поэтому результат равен 0
  } else if (sign_num1 == sign_num2 &&
             sign_num1 == 1) {  // Если оба числа отрицательные
    if (num1.bits[3] == num2.bits[3]) {  // Проверяем старший бит
      if (num1.bits[2] == num2.bits[2]) {  // Проверяем второй бит
        if (num1.bits[1] == num2.bits[1]) {  // Проверяем третий бит
          if (num1.bits[0] == num2.bits[0]) {  // Проверяем младший бит
            result = 0;  // Если все разряды равны, числа равны, поэтому
                         // результат равен 0
          } else {
            result = !s21_is_less_num(num1, num2, result);
            // Вызываем функцию для сравнения чисел (инвертируем результат)
          }
        } else {
          result = !s21_is_less_num(num1, num2, result);
          // Вызываем функцию для сравнения чисел (инвертируем результат)
        }
      } else {
        result = !s21_is_less_num(num1, num2, result);
        // Вызываем функцию для сравнения чисел (инвертируем результат)
      }
    } else {
      result = !s21_is_less_num(num1, num2, result);
      // Вызываем функцию для сравнения чисел (инвертируем результат)
    }
  }
  return result;  // Возвращаем результат
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  // Проверяем, являются ли числа num1 и num2 равными или num1 меньше num2.
  if (s21_is_equal(num1, num2) || s21_is_less(num1, num2)) {
    // Если условие выполняется, возвращаем 1, что означает "меньше или равно".
    res = 1;
  }
  // Если условие не выполняется, возвращаем 0, что означает "больше".
  return res;
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  // Проверяем, являются ли числа num1 и num2 равными или num1 больше num2.
  if (s21_is_equal(num1, num2) || s21_is_greater(num1, num2)) {
    // Если условие выполняется, возвращаем 1, что означает "больше или равно".
    res = 1;
  }
  // Если условие не выполняется, возвращаем 0, что означает "меньше".
  return res;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int result = -1;  // Изначально результат установлен на -1
  int sign_num1 = get_sign(&num1);  // Получаем знак числа num1
  int sign_num2 = get_sign(&num2);  // Получаем знак числа num2
  if (sign_num1 == sign_num2 &&
      sign_num1 == 0) {  // Если оба числа положительные
    // Вызываем функцию для сравнения чисел
    result = s21_is_greater_num(num1, num2, result);
    // Если num1 отрицательное, а num2 положительное
  } else if (sign_num1 == 1 && sign_num2 == 0) {
    result = 0;  // num1 меньше num2, поэтому результат равен 0
                 // Если num1 положительное, а num2 отрицательное
  } else if (sign_num1 == 0 && sign_num2 == 1) {
    result = 1;  // num1 больше num2, поэтому результат равен 1
                 // Если оба числа отрицательные
  } else if (sign_num1 == sign_num2 && sign_num1 == 1) {
    if (num1.bits[3] == num2.bits[3]) {
      if (num1.bits[2] == num2.bits[2]) {
        if (num1.bits[1] == num2.bits[1]) {
          if (num1.bits[0] == num2.bits[0]) {
            // Если все разряды равны, числа равны, поэтому результат равен 0
            result = 0;
          } else {
            result = !s21_is_greater_num(num1, num2, result);
            // Вызываем функцию для сравнения чисел (инвертируем результат)
          }
        } else {
          result = !s21_is_greater_num(num1, num2, result);
          // Вызываем функцию для сравнения чисел (инвертируем результат)
        }
      } else {
        result = !s21_is_greater_num(num1, num2, result);
        // Вызываем функцию для сравнения чисел (инвертируем результат)
      }
    } else {
      result = !s21_is_greater_num(num1, num2, result);
      // Вызываем функцию для сравнения чисел (инвертируем результат)
    }
  }
  return result;  // Возвращаем результат
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
  // Возвращаем отрицание результата функции s21_is_equal,
  // которая проверяет равенство чисел num1 и num2
}